/*
 BitzOS (BOS) V0.3.6 - Copyright (C) 2017-2024 Hexabitz
 All rights reserved

 File Name     : main.c
 Description   : Main program body.
 */
/* Includes ------------------------------------------------------------------*/
#include "BOS.h"

/* Private variables ---------------------------------------------------------*/
uint16_t  Distance;
uint32_t buff[3];
float X, Y, Z;
float X1, Y1, Z1;

uint32_t defaultTaskWaterMark;
uint32_t UserTaskWaterMark;
uint32_t BackEndTaskWaterMark;
uint32_t P1MsgTaskWaterMark;
uint32_t P2MsgTaskWaterMark;
uint32_t P3MsgTaskWaterMark;
uint32_t P4MsgTaskWaterMark;
uint32_t P5MsgTaskWaterMark;
uint32_t P6MsgTaskWaterMark;

/* Private function prototypes -----------------------------------------------*/
extern TaskHandle_t defaultTaskHandle;
extern TaskHandle_t UserTaskHandle;
extern TaskHandle_t BackEndTaskHandle;


extern TaskHandle_t P1MsgTaskHandle;
extern TaskHandle_t P2MsgTaskHandle;
extern TaskHandle_t P3MsgTaskHandle;
extern TaskHandle_t P4MsgTaskHandle;
extern TaskHandle_t P5MsgTaskHandle;
extern TaskHandle_t P6MsgTaskHandle;
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

#if ( _module == 1 )
	AddPortButton(MOMENTARY_NO, 2);   //Define a button connected to port P1
	SetButtonEvents(2, 1, 0, 3, 0, 0, 0, 0, 0,1);    // Activate a click event and a pressed_for_x event for 3 seconds
#endif

	RGB_LED_sweep(RGB_SWEEP_BASIC, 2000, -1);

	// put your code here, to run repeatedly.
	while (1) {
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

		/* Read Distance from TOF Module H08R7 */
		ReadDataFromSensorModule(7, CODE_H08R7_SAMPLE_PORT, (uint32_t *) & Distance, 200);
		Delay_ms(300);

		/* Read ACC data from IMU Module H0BR4 */
		ReadDataFromSensorModule(2, CODE_H0BR4_SAMPLE_ACC, &buff[0], 200);
		X = *((float*) &buff[0]);
		Y = *((float*) &buff[1]);
		Z = *((float*) &buff[2]);
		Delay_ms(300);

		/* Read GYRO data from IMU Module H0BR4 */
		ReadDataFromSensorModule(2, CODE_H0BR4_SAMPLE_GYRO, &buff[0], 200);
		X = *((float*) &buff[0]);
		Y = *((float*) &buff[1]);
		Z = *((float*) &buff[2]);
		Delay_ms(300);

		/* Read GYRO data from IMU Module H0BR4 */
		ReadDataFromSensorModule(10, CODE_H0BR4_SAMPLE_GYRO, &buff[0], 200);
		X1 = *((float*) &buff[0]);
		Y1 = *((float*) &buff[1]);
		Z1 = *((float*) &buff[2]);
		Delay_ms(300);

	}
}

#if ( _module == 1 )
void buttonClickedCallback(uint8_t port){

	SendMessageToModule(2,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(4,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(5,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(6,CODE_PING, 0);
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

	SendMessageToModule(5,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(6,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(7,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(8,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(9,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(10,CODE_PING, 0);
//	Delay_ms(20);

}
#endif
/*-----------------------------------------------------------*/
