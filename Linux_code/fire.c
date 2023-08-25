#include "controlDevices.h"
#define FIRECONTROL 8

int fireControlOpen(int pinNum)
{
	//digitalWrite(pinNum,LOW);
	return 0;
}

int fireControlClose(int pinNum)
{
	//digitalWrite(pinNum,HIGH);
	return 0;
}

int fireControlInit(int pinNum)
{
	pinMode(pinNum,INPUT);
	digitalWrite(pinNum,HIGH);
	return 0;
}

int fireControlChangeStatus()
{
	return 0;
}

int fireControlReadStatus(int pinNum)
{
	return digitalRead(pinNum);
}

struct Devices fireControl = {
	.deviceName = "fireControl",
	.pinNum = FIRECONTROL,
	.open = fireControlOpen,
	.close = fireControlClose,
	.deviceInit = fireControlInit,
	.changeStatus = fireControlChangeStatus,
	.readStatus = fireControlReadStatus
};


struct Devices* addfireControlToDeviceLink(struct Devices * phead)
{
	if(phead == NULL)
	{
		phead = &fireControl;
		return phead;
	}else {
		fireControl.next = phead;
		phead = &fireControl;
		return phead;
	}
}