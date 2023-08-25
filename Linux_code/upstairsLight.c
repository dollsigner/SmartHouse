#include "controlDevices.h"
#define UPSTAIRSLIGHT 5

int upstairsLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);
	return 0;
}

int upstairsLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);
	return 0;
}

int upstairsLightInit(int pinNum)
{
	pinMode(pinNum,OUTPUT);
	digitalWrite(pinNum,HIGH);
	return 0;
}

int upstairsLightChangeStatus()
{
	return 0;
	
}

int upstairsLightReadStatus()
{
	return 0;
}

struct Devices upstairsLight = {
	.deviceName = "upstairsLight",
	.status = 0,
	.pinNum = UPSTAIRSLIGHT,
	.open = upstairsLightOpen,
	.close = upstairsLightClose,
	.deviceInit = upstairsLightInit,
	.changeStatus = upstairsLightChangeStatus,
	.readStatus = upstairsLightReadStatus
};


struct Devices* addupstairsLightToDeviceLink(struct Devices * phead)
{
	if(phead == NULL)
	{
		phead = &upstairsLight;
		return phead;
	}else {
		upstairsLight.next = phead;
		phead = &upstairsLight;
		return phead;
	}
}
