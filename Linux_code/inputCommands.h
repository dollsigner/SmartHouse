#include<stdio.h>
#include<stdlib.h>
#include<wiringPi.h>

struct InputCommander
{
	char commandName[128];
	char command[32];
	char deviceName[32];
	int (*init)(struct InputCommander *commander);
	int (*getCommand)(struct InputCommander *commander);
	int fd;
	int s_fd;
	char log[1024];
	char port[12];
	char ipAddress[32];

	struct InputCommander *next;
};

struct InputCommander *addvoiceControlToInputCommandLink(struct InputCommander *phead);
struct InputCommander *addsocketControlToInputCommandLink(struct InputCommander *phead);
