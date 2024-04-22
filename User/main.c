/*
 BitzOS (BOS) V0.3.1 - Copyright (C) 2017-2024 Hexabitz
 All rights reserved

 File Name     : main.c
 Description   : Main program body.
 */
/* Includes ------------------------------------------------------------------*/
#include "BOS.h"

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Main function ------------------------------------------------------------*/

int main(void){

	Module_Init();		//Initialize Module &  BitzOS

	//Don't place your code here.
	for(;;){}
}

/*-----------------------------------------------------------*/
uint32_t period = (PWM_TIMER_CLOCK / RGB_PWM_FREQ)-1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
/* User Task */
void UserTask(void *argument){
//	MX_TIM2_Init();
//	MX_TIM3_Init();
//	MX_TIM4_Init();
	// put your code here, to run repeatedly.
	while (1) {
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, SET);
//		startPWM(255, 255, 255, 10);
//		htim3.Instance->ARR = period;
//		htim3.Instance->CCR1 = 1000;
//	HAL_TIM_PWM_Start(&htim3, _RGB_BLUE_TIM_CH);
		RGB_LED_sweep(RGB_SWEEP_FINE, 10000, -1);
	}
}

/*-----------------------------------------------------------*/
