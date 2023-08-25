#include<stdio.h>
#include<wiringPi.h>
#include<string.h>

#define IN1 2
#define IN2 5
#define IN3 6
#define IN4 8

int main()
{
        wiringPiSetup();
        printf("输入0/1: 0-断开 1-导通\n");
        pinMode(IN1,OUTPUT);
        pinMode(IN2,OUTPUT);
        pinMode(IN3,OUTPUT);
        pinMode(IN4,OUTPUT);
        int cmd;
        while(1)
        {
                scanf("%d",&cmd);
                switch(cmd)
                {
						case 1:
								digitalWrite(IN1,LOW);
								break;
                        case 10:
                                digitalWrite(IN1,HIGH);
                                break;
                        case 2:
                                digitalWrite(IN2,LOW);
                                break;
						case 20:
								digitalWrite(IN2,HIGH);
								break;
								
						case 3:
								digitalWrite(IN3,LOW);
								break;
						case 30:
								digitalWrite(IN3,HIGH);
								break;
						case 4:
								digitalWrite(IN4,LOW);
								break;
						case 40:
								digitalWrite(IN4,HIGH);
								break;
						case 5: 
								digitalWrite(IN1,LOW);
								digitalWrite(IN2,LOW);
								digitalWrite(IN3,LOW);
								digitalWrite(IN4,LOW);
								break;
						case 50:
								digitalWrite(IN1,HIGH);
								digitalWrite(IN2,HIGH);
								digitalWrite(IN3,HIGH);
								digitalWrite(IN4,HIGH);
								break;
						
                        default:
                                printf("输入错误\n");
                                break;

                }
        }
        return 0;
