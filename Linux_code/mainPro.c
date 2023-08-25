#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>
#include "controlDevices.h"
#include "inputCommands.h"

struct Devices *pdeviceHEAD = NULL;
struct InputCommander *pcommanderHEAD = NULL;
static int fireStatus = 0;



//设备工厂接口
struct Devices * findDeviceByName(char *name, struct Devices *pdeviceHEAD)
{
	struct Devices * temp = pdeviceHEAD;
	while(temp != NULL)
	{
		if(strcmp(temp->deviceName,name) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

//指令工厂接口
struct InputCommander * findCommanderByName(char *name, struct InputCommander *pcommanderHEAD)
{
	struct InputCommander * temp = pcommanderHEAD;
	while(temp != NULL)
	{
		if(strcmp(temp->commandName,name) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

//语音控制线程
void *voiceThreadHandler(void *data)
{
	int nread = 0;
	struct InputCommander *voiceHandler;
	voiceHandler = findCommanderByName("voice",pcommanderHEAD);
	if(voiceHandler == NULL)
	{
		printf("can't find voice command!\n");
	}else if(voiceHandler->init(voiceHandler) == -1) {
		printf("voice init failed!\n");
	}else {
		printf("voice init succeed!\n");
		while(1)
		{
			nread = voiceHandler->getCommand(voiceHandler);
			if(nread != 0)
			{
				printf("voice recieve command: %s\n", voiceHandler->command);
				
			}else {
				printf("no datas from voice!\n");
			}
		}
	}
}

//socket控制线程
struct InputCommander *socketHandler;
int c_fd;
int c_fd2;

void *socketWriteThread(void *data)
{
	struct Devices *temp = findDeviceByName("fireControl",pdeviceHEAD);
	if(temp == NULL)
	{
		pthread_exit(NULL);
	}
	char *sendBuff = NULL;
	while(1)
	{
		if(fireStatus == 1)
		{
			sendBuff = "fire ON";
			write(c_fd2, sendBuff, strlen(sendBuff));
		}else{
			sendBuff = "fire OFF";
			write(c_fd2, sendBuff, strlen(sendBuff));
		}
		sleep(3);
	}
}

void *socketReadThread(void *data)
{
	pthread_t socketWrite;
	
	int n_read = 0;
	memset(socketHandler->command, '\0' ,sizeof(socketHandler->command));
	n_read = read(c_fd, socketHandler->command, sizeof(socketHandler->command));
	if(n_read == -1)
	{
		printf("n_read failed!\n");
	}else if(n_read > 0)
	{
		printf("n_get %d\n",n_read);
		printf("get command: %s\n",socketHandler->command);
		
		if(strcmp(socketHandler->command,"textClient") == 0)
		{
			//1.客户端为text接收数据，进入write线程
			c_fd2 = c_fd;
			pthread_create(&socketWrite, NULL, socketWriteThread, NULL);
		}else {
			//2.客户端为button发送数据，继续read
			struct Devices* temp = findDeviceByName(socketHandler->command,pdeviceHEAD);
			if(temp == NULL)
			{
				printf("remote command erro, cannot find device!\n");
			}else{
				printf("deviceName: %s\n",temp->deviceName);
				temp->deviceInit(temp->pinNum);
				if(temp->status == 0){
					temp->open(temp->pinNum);
					temp->status = 1;
				}else {
					temp->close(temp->pinNum);
					temp->status = 0;
				}
			}
		}
		
		
		
	}else {
		printf("time out, client quit!\n");  
	}
}



void *socketThreadHandler(void *data)
{
	int clen;
	pthread_t socketRead;
	
	struct sockaddr_in c_addr;
	memset(&c_addr,0,sizeof(struct sockaddr_in));
	clen = sizeof(struct sockaddr_in);
	
	socketHandler = findCommanderByName("socketServer",pcommanderHEAD);
	if(socketHandler == NULL)
	{
		printf("can't find socketServer command!\n");
	}else if(socketHandler->init(socketHandler) == -1) {
		printf("socketServer init failed!\n");
	}else {
		printf("socketServer init succeed!\n");
		printf("socketServer is listening\n");
		while(1)
		{
			c_fd = accept(socketHandler->s_fd, (struct sockaddr *)&c_addr, &clen);
			pthread_create(&socketRead, NULL, socketReadThread, NULL);
		}
	}
}

void *fireThreadHandler(void *data)
{
	struct Devices *temp = findDeviceByName("fireControl",pdeviceHEAD);
	if(temp == NULL)
	{
		pthread_exit(NULL);
	}
	while(1) 
	{
		if(temp->readStatus(temp->pinNum) == 0)
		{
			printf("fire!fire!fire!\n");
			fireStatus = 1;
		}else {
			//printf("nofire\n");
			fireStatus = 0;
		}
		sleep(1);
	}
}

int main()
{
	signal(SIGPIPE, SIG_IGN);
	//wiringPi库初始化
	if(wiringPiSetup() == -1)
	{
		printf("wiringPiSetup failed!\n");
		exit(-1);
	}
	printf("wiringPiSetup succeed!\n");
	
	//定义变量
	char name[128];
	pthread_t voice_thread;
	pthread_t socket_thread;
	pthread_t fireCheck_thread;
	
	//1.设备工厂初始化
	pdeviceHEAD = addBathRoomLightToDeviceLink(pdeviceHEAD);
	pdeviceHEAD = addupstairsLightToDeviceLink(pdeviceHEAD);
	pdeviceHEAD = addrestaurantLightToDeviceLink(pdeviceHEAD);
	pdeviceHEAD = addlivingroomLightToDeviceLink(pdeviceHEAD);
	pdeviceHEAD = addfireControlToDeviceLink(pdeviceHEAD);
	
	//2.指令工厂初始化
	pcommanderHEAD = addvoiceControlToInputCommandLink(pcommanderHEAD);
	pcommanderHEAD = addsocketControlToInputCommandLink(pcommanderHEAD);
	
	//3.语音线程
	pthread_create(&voice_thread,NULL,voiceThreadHandler,NULL);
	//4.socket线程
	pthread_create(&socket_thread,NULL,socketThreadHandler,NULL);
	//5.检查fire线程
	pthread_create(&fireCheck_thread,NULL,fireThreadHandler,NULL);
	
	struct Devices *temp = NULL;
	
	while(1)
	{
		memset(name,'\0',sizeof(name));
		printf("Input the device name you want to open!\n");
		scanf("%s",name);
		temp = findDeviceByName(name,pdeviceHEAD);
		if(temp == NULL)
		{
			printf("No such device!\n");
		}else {
			printf("deviceName: %s\n",temp->deviceName);
			temp->deviceInit(temp->pinNum);
			if(strcmp(temp->deviceName,"fireControl") == 0)
			{
				if(temp->readStatus(temp->pinNum) == 0)
				{
					printf("fire!fire!fire!\n");
				}else {
					//printf("no fire here!\n");
				}
			}else if(temp->status == 0){
				temp->open(temp->pinNum);
				temp->status = 1;
			}else {
				temp->close(temp->pinNum);
				temp->status = 0;
			}
		}
	}
}
