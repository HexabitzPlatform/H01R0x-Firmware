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
uint32_t apb1ClockFreq, ahbClockFreq, systemClockFreq;
/* User Task */
void UserTask(void *argument) {

	// put your code here, to run repeatedly.
	while (1) {

		// Get the APB1 peripheral clock frequency (used for peripherals like UART and TIMx in some cases)
		 apb1ClockFreq = HAL_RCC_GetPCLK1Freq();

		// Get the AHB clock frequency (HCLK), which is used for the CPU, memory, and other controllers
		 ahbClockFreq = HAL_RCC_GetHCLKFreq();

		// Get the system clock frequency (SYSCLK), which serves as the main clock source for the system
		 systemClockFreq = HAL_RCC_GetSysClockFreq();


	}
}

/*-----------------------------------------------------------*/
