#include "controlDevices.h"
#define LIVINGROOMLIGHT 7

int livingroomLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);
	return 0;
}

int livingroomLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);
	return 0;
}

int livingroomLightInit(int pinNum)
{
	pinMode(pinNum,OUTPUT);
	digitalWrite(pinNum,HIGH);
	return 0;
}

int livingroomLightChangeStatus()
{
	return 0;
	
}

int livingroomLightReadStatus()
{
	return 0;
}

struct Devices livingroomLight = {
	.deviceName = "livingroomLight",
	.status = 0,
	.pinNum = LIVINGROOMLIGHT,
	.open = livingroomLightOpen,
	.close = livingroomLightClose,
	.deviceInit = livingroomLightInit,
	.changeStatus = livingroomLightChangeStatus,
	.readStatus = livingroomLightReadStatus
};


struct Devices* addlivingroomLightToDeviceLink(struct Devices * phead)
{
	if(phead == NULL)
	{
		phead = &livingroomLight;
		return phead;
	}else {
		livingroomLight.next = phead;
		phead = &livingroomLight;
		return phead;
	}
}