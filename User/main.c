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
uint8_t f;
/* User Task */
void UserTask(void *argument) {

//#if ( _module == 1 )
//	AddPortButton(MOMENTARY_NO, 2);   //Define a button connected to port P1
//	SetButtonEvents(2, 1, 0, 3, 0, 0, 0, 0, 0,1);    // Activate a click event and a pressed_for_x event for 3 seconds
//#endif

//	RGB_LED_sweep(RGB_SWEEP_BASIC, 2000, -1);
//	Unbridge(5, 6);
//	Bridge(5, 6);

	// put your code here, to run repeatedly.
	while (1) {
		if(f==1)
		{
			RemovePortButton(2);
			f=0;
		}
		else if(f==2)
		{
			AddButton(2, MOMENTARY_NO, CLICKED);
			f=0;
		}
		else if(f==3)
		{
			AddButton(2, MOMENTARY_NO, DBL_CLICKED);
			f=0;
		}
		else if(f==4)
		{
			AddButton(2, MOMENTARY_NO, RELEASED);
			f=0;
		}
		else if(f==5){
			AddButton(3, MOMENTARY_NO, DBL_CLICKED);
			f=0;
		}
		else if(f==6){
			AddButton(5, MOMENTARY_NO, DBL_CLICKED);
			f=0;
		}
		else if(f==7){
			AddButton(6, MOMENTARY_NO, DBL_CLICKED);
			f=0;
		}
		if(f==8)
		{
			RemovePortButton(3);
			f=0;
		}
		if(f==9)
		{
			RemovePortButton(5);
			f=0;
		}
		if(f==10)
		{
			RemovePortButton(6);
			f=0;
		}
		else if(f==11){
			AddButton(1, MOMENTARY_NO, DBL_CLICKED);
			f=0;
		}
		else if(f==12){
			AddButton(4, MOMENTARY_NO, DBL_CLICKED);
			f=0;
		}
		if(f==13)
		{
			RemovePortButton(1);
			f=0;
		}
		if(f==14)
		{
			RemovePortButton(4);
			f=0;
		}
//		else if(f==2)
//		{
//			AddButton(2, MOMENTARY_NO, DBL_CLICKED);
//		}

		// Get the APB1 peripheral clock frequency (used for peripherals like UART and TIMx in some cases)
//		 apb1ClockFreq = HAL_RCC_GetPCLK1Freq();
//
//		// Get the AHB clock frequency (HCLK), which is used for the CPU, memory, and other controllers
//		 ahbClockFreq = HAL_RCC_GetHCLKFreq();
//
//		// Get the system clock frequency (SYSCLK), which serves as the main clock source for the system
//		 systemClockFreq = HAL_RCC_GetSysClockFreq();

		//
//		BackEndTaskWaterMark = uxTaskGetStackHighWaterMark(BackEndTaskHandle);
//		//
//		UserTaskWaterMark = uxTaskGetStackHighWaterMark(UserTaskHandle);
//		//
//		defaultTaskWaterMark = uxTaskGetStackHighWaterMark(defaultTaskHandle);
//		//
//		P3MsgTaskWaterMark = uxTaskGetStackHighWaterMark(P3MsgTaskHandle);
//		//
//		P5MsgTaskWaterMark = uxTaskGetStackHighWaterMark(P5MsgTaskHandle);

	}
}
//void buttonReleasedCallback(uint8_t port)
//{
//	IND_blink(100);
//}
void buttonClickedCallback(uint8_t port) {
	IND_blink(100);
}
void buttonDblClickedCallback(uint8_t port){
	IND_blink(100);
}
/*-----------------------------------------------------------*/
