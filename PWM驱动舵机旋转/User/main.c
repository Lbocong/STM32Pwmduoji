#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Servo.h"
#include "Key.h"

uint8_t KeyNum;
float Angle;

int main(void)
{
	
	Servo_Init();
	
	Servo_SetAngle(180);
}
	
	

