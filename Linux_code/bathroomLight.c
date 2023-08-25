#include "controlDevices.h"
#define BATHROOMLIGHT 2

int bathroomLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);
	return 0;
}

int bathroomLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);
	return 0;
}

int bathroomLightInit(int pinNum)
{
	pinMode(pinNum,OUTPUT);
	digitalWrite(pinNum,HIGH);
	return 0;
}

int bathroomLightChangeStatus()
{
	return 0;
	
}

int bathroomLightReadStatus()
{
	return 0;
}

struct Devices bathroomLight = {
	.deviceName = "bathroomLight",
	.status = 0,
	.pinNum = BATHROOMLIGHT,
	.open = bathroomLightOpen,
	.close = bathroomLightClose,
	.deviceInit = bathroomLightInit,
	.changeStatus = bathroomLightChangeStatus,
	.readStatus = bathroomLightReadStatus
};


struct Devices* addBathRoomLightToDeviceLink(struct Devices * phead)
{
	if(phead == NULL)
	{
		phead = &bathroomLight;
		return phead;
	}else {
		bathroomLight.next = phead;
		phead = &bathroomLight;
		return phead;
	}
}

