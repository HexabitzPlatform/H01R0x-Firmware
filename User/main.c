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

int main(void) {

	Module_Init();		//Initialize Module &  BitzOS

	//Don't place your code here.
	for (;;) {
	}
}

/*-----------------------------------------------------------*/

/* User Task */
void UserTask(void *argument) {

	AddPortButton(MOMENTARY_NO, 2);   //Define a button connected to port P1
	SetButtonEvents(2, 1, 0, 3, 0, 0, 0, 0, 0,1);    // Activate a click event and a pressed_for_x event for 3 seconds

	RGB_LED_sweep(RGB_SWEEP_BASIC, 2000, -1);

	// put your code here, to run repeatedly.
	while (1) {



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
