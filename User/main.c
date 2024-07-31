/*
 BitzOS (BOS) V0.3.5 - Copyright (C) 2017-2024 Hexabitz
 All rights reserved

 File Name     : main.c
 Description   : Main program body.
 */
/* Includes ------------------------------------------------------------------*/
#include "BOS.h"

/* Private variables ---------------------------------------------------------*/
extern uint8_t WakeupFromStopFlag;
uint32_t u ;
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

	EnableStopModebyUARTx(P2);

	// put your code here, to run repeatedly.
	while (1) {


//		if (WakeupFromStopFlag) {
//			SystemClock_Config();
//
//			HAL_Delay(2000);
//			IND_blink(500);
//			WakeupFromStopFlag = 0;
//			u = HAL_RCC_GetSysClockFreq();
//		}

//		EnableStopMode(P2);
//		HAL_Delay(100);
	}
}

/*-----------------------------------------------------------*/
