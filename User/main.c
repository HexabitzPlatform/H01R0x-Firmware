/*
 BitzOS (BOS) V0.3.5 - Copyright (C) 2017-2024 Hexabitz
 All rights reserved

 File Name     : main.c
 Description   : Main program body.
 */
/* Includes ------------------------------------------------------------------*/
#include "BOS.h"

/* Private variables ---------------------------------------------------------*/
uint32_t buff[4];
float dataS;
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

	// put your code here, to run repeatedly.
	while (1) {

//		SendMessageToModule(2, CODE_PING, 0);
//		Delay_ms(100);
//		SendMessageToModule(3, CODE_PING, 0);
//		Delay_ms(100);
//		ReadDataFromSensorModule(3, CODE_H0AR9_SAMPLE_COLOR, 3, &buff[0]); // 3 * uint16_t

//		ReadDataFromSensorModule(3, CODE_H0AR9_SAMPLE_DISTANCE, 1, &buff[0]);  // 1 * uint16_t
//
		ReadDataFromSensorModule(3, CODE_H0AR9_SAMPLE_TEMP, 1, &buff[0]);   // 1 * float
		dataS = *((float *) &buff);
//		ReadDataFromSensorModule(3, CODE_H0AR9_SAMPLE_HUMIDITY, 1, &buff[0]);  // 1 * float


	}
}

/*-----------------------------------------------------------*/
