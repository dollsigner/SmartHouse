#include<wiringSerial.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

#include "inputCommands.h"

int socketInit(struct InputCommander *socketMes)
{
	int s_fd;
	int c_fd;
	
	struct sockaddr_in s_addr;
	struct sockaddr_in c_addr;
	
	memset(&s_addr,0,sizeof(struct sockaddr_in));
	memset(&c_addr,0,sizeof(struct sockaddr_in));
	
	//1.socket
	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(s_fd == -1)
	{
		perror("socket erro!\n");
		exit(-1);
	}
	
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(atoi(socketMes->port));
	inet_aton(socketMes->ipAddress,&s_addr.sin_addr);
	
	//2.bind
	bind(s_fd,(struct sockaddr *)&s_addr,sizeof(struct sockaddr_in));
	
	//3.listen
	listen(s_fd,10);
	socketMes->s_fd = s_fd;
	
	return s_fd;
}

int socketGetCommand(struct InputCommander *socketMes)
{
	//4.accept
	int c_fd;
	int n_read;
	struct sockaddr_in c_addr;
	memset(&c_addr,0,sizeof(struct sockaddr_in));
	int clen = sizeof(struct sockaddr_in);
	
	c_fd = accept(socketMes->s_fd, (struct sockaddr *)&c_addr, &clen);
	
	//5.read
	n_read = read(c_fd, socketMes->command, sizeof(socketMes->command));
	if(n_read == -1)
	{
		printf("n_read failed!\n");
	}else if(n_read > 0)
	{
		printf("n_get %d\n",n_read);
	}else {
		printf("time out, client quit!\n");
	}
	
	return n_read;
}


struct InputCommander socketControl = {
	.commandName = "socketServer",
	.command = {'\0'},
	.port = "8088",
	.ipAddress = "192.168.31.20",
	.init = socketInit,
	.getCommand = socketGetCommand,
	.log = {'\0'},
	.next = NULL
};

struct InputCommander *addsocketControlToInputCommandLink(struct InputCommander *phead)
{
	if(phead == NULL)
	{
		return &socketControl;
	}else {
		socketControl.next = phead;
		phead = &socketControl;
		return phead;
	}
}
