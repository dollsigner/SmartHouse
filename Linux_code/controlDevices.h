#include<stdio.h>
#include<stdlib.h>
#include<wiringPi.h>

struct Devices
{
	char deviceName[128];
	int status;
	int pinNum;

	int (*open)(int pinNum);
	int (*close)(int pinNum);
	int (*deviceInit)(int pinNum);

	int (*readStatus)();
	int (*changeStatus)(int status);
	
	void (*readTempHumi)();
	
	struct Devices *next;
};

struct Devices *addBathRoomLightToDeviceLink(struct Devices * phead);
struct Devices* addupstairsLightToDeviceLink(struct Devices * phead);
struct Devices* addrestaurantLightToDeviceLink(struct Devices * phead);
struct Devices* addlivingroomLightToDeviceLink(struct Devices * phead);
struct Devices* addfireControlToDeviceLink(struct Devices * phead);


