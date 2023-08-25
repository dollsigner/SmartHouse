#include "controlDevices.h"
#define RESTAURANTLIGHT 6

int restaurantLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);
	return 0;
}

int restaurantLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);
	return 0;
}

int restaurantLightInit(int pinNum)
{
	pinMode(pinNum,OUTPUT);
	digitalWrite(pinNum,HIGH);
	return 0;
}

int restaurantLightChangeStatus()
{
	return 0;
	
}

int restaurantLightReadStatus()
{
	return 0;
}

struct Devices restaurantLight = {
	.deviceName = "restaurantLight",
	.status = 0,
	.pinNum = RESTAURANTLIGHT,
	.open = restaurantLightOpen,
	.close = restaurantLightClose,
	.deviceInit = restaurantLightInit,
	.changeStatus = restaurantLightChangeStatus,
	.readStatus = restaurantLightReadStatus
};


struct Devices* addrestaurantLightToDeviceLink(struct Devices * phead)
{
	if(phead == NULL)
	{
		phead = &restaurantLight;
		return phead;
	}else {
		restaurantLight.next = phead;
		phead = &restaurantLight;
		return phead;
	}
}