#include<wiringSerial.h>
#include<unistd.h>
#include<string.h>
#include "inputCommands.h"

int voiceInit(struct InputCommander *voicer)
{
	int fd;
	if((fd = serialOpen(voicer->deviceName,115200)) < 0)
	{
		printf("serialOpen erro!\n");
		return -1;
	}
	voicer->fd = fd;
	return fd;
}

int voiceGetCommand(struct InputCommander *voicer)
{
	int nread = 0;
	memset(voicer->command, '\0', sizeof(voicer->command));
	nread = read(voicer->fd, voicer->command, sizeof(voicer->command));
	if(nread == 0)
	{
		printf("uart for voice read time out!\n");
		return 0;
	}else {
		return nread;
	}
}


struct InputCommander voiceControl = {
	.commandName = "voice",
	.command = {'\0'},
	.deviceName = "/dev/ttyS0",
	.init = voiceInit,
	.getCommand = voiceGetCommand,
	.log = {'\0'},
	.next = NULL
};

struct InputCommander *addvoiceControlToInputCommandLink(struct InputCommander *phead)
{
	if(phead == NULL)
	{
		return &voiceControl;
	}else {
		voiceControl.next = phead;
		phead = &voiceControl;
		return phead;
	}
}
