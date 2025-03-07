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
uint8_t y;
extern RTC_HandleTypeDef RtcHandle;
/* User Task */
void UserTask(void *argument) {

//	AddPortButton(MOMENTARY_NO, 2);   //Define a button connected to port P1
//	SetButtonEvents(2, 0, 1, 0, 0, 0, 0, 0, 0,0);
//#if ( _module == 1 )
//	AddPortButton(MOMENTARY_NO, 2);   //Define a button connected to port P1
//	SetButtonEvents(2, 1, 0, 3, 0, 0, 0, 0, 0,1);    // Activate a click event and a pressed_for_x event for 3 seconds
//#endif

//	RGB_LED_sweep(RGB_SWEEP_BASIC, 2000, -1);
//	Unbridge(5, 6);
//	Bridge(5, 6);
//	BOS_CalendarConfig(uint8_t month,uint8_t day,uint16_t year,uint8_t weekday,uint8_t seconds,uint8_t minutes,uint8_t hours,uint8_t AMPM,int8_t daylightsaving);

	// put your code here, to run repeatedly.
	while (1) {
		GetTimeDate();
		if(f == 1)
		{
//			  HAL_RTC_DeInit(&RtcHandle);
//			  RtcHandle.Init.HourFormat = RTC_HOURFORMAT_12;
//			  HAL_RTC_Init(&RtcHandle);
			BOS_CalendarConfig(1,1,2025,1,55,59,12,2,0);
			f=0;
		}

		else if(f == 2)
		{
//			  HAL_RTC_DeInit(&RtcHandle);
//			  RtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;
//			  HAL_RTC_Init(&RtcHandle);
			BOS_CalendarConfig(1,1,2025,1,55,59,12,0,0);
			f=0;
		}

		else if(f == 3)
		{
//			  HAL_RTC_DeInit(&RtcHandle);
//			  RtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;
//			  HAL_RTC_Init(&RtcHandle);
			BOS_CalendarConfig(1,1,2025,1,55,59,13,0,0);
			f=0;
		}
		else if(f == 4)
		{
//			  HAL_RTC_DeInit(&RtcHandle);
//			  RtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;
//			  HAL_RTC_Init(&RtcHandle);
			BOS_CalendarConfig(1,1,2025,1,55,59,23,0,0);
			f=0;
		}

//		if(f==1)
//		{
//			RemovePortButton(2);
//			f=0;
//		}
//
//		if(f==2)
//		{
////			AddPortButton(ONOFF_NO, 2);
//			AddButton(2, MOMENTARY_NO, CLICKED);
//			f=0;
//		}
//
//		if(f==3)
//		{
////			AddPortButton(ONOFF_NO, 2);
//			AddButton(2, MOMENTARY_NO, DBL_CLICKED);
//			f=0;
//		}
//
//		if(f==4)
//		{
////			AddPortButton(ONOFF_NO, 2);
//			AddButton(2, MOMENTARY_NO, RELEASED);
//			f=0;
//		}


//		else if(f==2)
//		{
//			/* clicked */
//			SetButtonEvents(2, 1, 0, 0, 0, 0, 0, 0, 0,0);
//			f=0;
//		}
//		else if(f==3)
//		{
//			/* double clicked */
//			SetButtonEvents(2, 0, 1, 0, 0, 0, 0, 0, 0,0);
//			f=0;
//		}
//		else if(f==4)
//		{
//			/* pressed x1 */
//			SetButtonEvents(2, 0, 0, 1, 0, 0, 0, 0, 0,0);
//			f=0;
//		}
//		else if(f==5)
//		{
//			/* pressed x2 */
//			SetButtonEvents(2, 0, 0, 0, 1, 0, 0, 0, 0,0);
//			f=0;
//		}
//		else if(f==6)
//		{
//			/* pressed x3 */
//			SetButtonEvents(2, 0, 0, 0, 0, 1, 0, 0, 0,0);
//			f=0;
//		}
//		else if(f==7)
//		{
//			/* relesed y1 */
//			SetButtonEvents(2, 0, 0, 0, 0, 0, 1, 0, 0,0);
//			f=0;
//		}
//		else if(f==8)
//		{
//			/* relesed y2 */
//			SetButtonEvents(2, 0, 0, 0, 0, 0, 0, 1, 0,0);
//			f=0;
//		}
//		else if(f==9)
//		{
//			/* relesed y3 */
//			SetButtonEvents(2, 0, 0, 0, 0, 0, 0, 0, 1,0);
//			f=0;
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
/*-----------------------------------------------------------*/
//void buttonPressedCallback(uint8_t port){
//	y=1;
//	IND_blink(100);
//}
//void buttonReleasedCallback(uint8_t port){
//	y=2;
//	IND_blink(100);
//}
void buttonClickedCallback(uint8_t port){
	y=3;
	IND_blink(100);
}

void buttonDblClickedCallback(uint8_t port){
	y=4;
	IND_blink(100);
}

void buttonPressedForXCallback(uint8_t port, uint8_t eventType){
	y=5;
	IND_blink(100);
}

void buttonReleasedForYCallback(uint8_t port, uint8_t eventType){
	y=6;
	IND_blink(100);
}
