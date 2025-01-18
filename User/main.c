/*
 BitzOS (BOS) V0.3.6 - Copyright (C) 2017-2024 Hexabitz
 All rights reserved

 File Name     : main.c
 Description   : Main program body.
 */
/* Includes ------------------------------------------------------------------*/
#include "BOS.h"
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Main function ------------------------------------------------------------*/
	uint16_t DataR[2500] = {0};
	uint32_t count = 0;
	uint32_t pagestatus119;
	uint32_t pagestatus120;
	uint32_t pagestatus121;
	uint32_t pagestatus122;
	uint32_t pagestatus123;
	uint32_t pagestatus124;
	uint32_t pagestatus125;
	uint32_t pagestatus126;
	uint8_t flag1 = 0;
	BOS_Status status;
int main(void) {

	Module_Init();		//Initialize Module &  BitzOS
	EE_Format();
	//Don't place your code here.
	for (;;) {
	}
}

/*-----------------------------------------------------------*/

/* User Task */
void UserTask(void *argument) {

<<<<<<< HEAD
	AddPortButton(MOMENTARY_NO, 2);   //Define a button connected to port P1
	SetButtonEvents(2, 1, 0, 3, 0, 0, 0, 0, 0,1);    // Activate a click event and a pressed_for_x event for 3 seconds

	RGB_LED_sweep(RGB_SWEEP_BASIC, 2000, -1);

	// put your code here, to run repeatedly.
	while (1) {


=======
	while (1) {

	if(flag1 == 1)
	{
		for(int i=1; i<1000; i++)
		{
			status = EE_WriteVariable(i,i);
			pagestatus119 = GetPageState(0x807B800);
			pagestatus120 = GetPageState(0x807C000);
			pagestatus121 = GetPageState(0x807C800);
			pagestatus122 = GetPageState(0x807D000);
			pagestatus123 = GetPageState(0x807D800);
			pagestatus124 = GetPageState(0x807E000);
			pagestatus125 = GetPageState(0x807E800);
			pagestatus126 = GetPageState(0x807F000);
			count++;
		}
	}
		for(int i=1; i<1000; i++)
		{
			EE_ReadVariable(i,&DataR[i]);
			pagestatus119 = GetPageState(0x807B800);
			pagestatus120 = GetPageState(0x807C000);
			pagestatus121 = GetPageState(0x807C800);
			pagestatus122 = GetPageState(0x807D000);
			pagestatus123 = GetPageState(0x807D800);
			pagestatus124 = GetPageState(0x807E000);
			pagestatus125 = GetPageState(0x807E800);
			pagestatus126 = GetPageState(0x807F000);

		}
>>>>>>> EEPROM

	}
}

void buttonClickedCallback(uint8_t port){

	SendMessageToModule(2,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(4,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(7,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(8,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(9,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(10,CODE_PING, 0);
//	Delay_ms(20);

	Delay_ms(200);

	SendMessageToModule(2,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(4,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(7,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(8,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(9,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(10,CODE_PING, 0);
//	Delay_ms(20);

//	SendMessageToModule(2,CODE_PING, 0);
//	Delay_ms(20);
//
//	SendMessageToModule(4,CODE_PING, 0);
//	Delay_ms(20);
//
//	SendMessageToModule(7,CODE_PING, 0);
//	Delay_ms(20);
//
//	SendMessageToModule(2,CODE_PING, 0);
//	Delay_ms(20);
//
//	SendMessageToModule(4,CODE_PING, 0);
//	Delay_ms(20);
//
//	SendMessageToModule(7,CODE_PING, 0);
//	Delay_ms(20);

}
/*-----------------------------------------------------------*/
