/*
 BitzOS (BOS) V0.3.1 - Copyright (C) 2017-2024 Hexabitz
 All rights reserved

 File Name     : H01R0_timers.c
 Description   : Peripheral timers setup source file.

 Required MCU resources :

 >> Timer 16 for micro-sec delay.
 >> Timer 17 for milli-sec delay.

 */

/* Includes ------------------------------------------------------------------*/
#include "BOS.h"

/*----------------------------------------------------------------------------*/
/* Configure Timers                                                              */
/*----------------------------------------------------------------------------*/

/* Variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStruct = {0};
TIM_HandleTypeDef htim16; /* micro-second delay counter */
TIM_HandleTypeDef htim17; /* milli-second delay counter */

extern TIM_HandleTypeDef htim2;  /* Timer for RGB red */
extern TIM_HandleTypeDef htim3;  /* Timer for RGB blue */
extern TIM_HandleTypeDef htim4;  /* Timer for RGB green */


extern void MX_TIM2_Init(void);
extern void MX_TIM3_Init(void);
extern void MX_TIM4_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/*-----------------------------------------------------------*/
/* TIM2 init function */
void MX_TIM2_Init(void)
{

	/* USER CODE BEGIN TIM2_Init 0 */
	__TIM2_CLK_ENABLE();
	/* USER CODE END TIM2_Init 0 */

	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};
	TIM_ClockConfigTypeDef sClockSourceConfig;

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = (uint32_t )(HAL_RCC_GetSysClockFreq() / PWM_TIMER_CLOCK) - 1;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 1023;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_PWM_Init(&htim2);

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&htim2,&sClockSourceConfig);

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC,_RGB_RED_TIM_CH);

	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */

	HAL_TIM_MspPostInit(&htim2);

	/* TIM2 clock enable */
	__HAL_RCC_TIM2_CLK_ENABLE();

	/* TIM2 interrupt Init */
	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);

}

/*-----------------------------------------------------------*/
/* TIM3 init function */
void MX_TIM3_Init(void)
{

	/* USER CODE BEGIN TIM3_Init 0 */
	__TIM3_CLK_ENABLE();
	/* USER CODE END TIM3_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	/* USER CODE BEGIN TIM3_Init 1 */

	/* USER CODE END TIM3_Init 1 */
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = (uint32_t )(HAL_RCC_GetSysClockFreq() / PWM_TIMER_CLOCK) - 1;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 1023;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_Base_Init(&htim3);

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig);

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig);

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, _RGB_BLUE_TIM_CH);

	/* USER CODE BEGIN TIM3_Init 2 */

	/* USER CODE END TIM3_Init 2 */
	HAL_TIM_MspPostInit(&htim3);

	/* TIM3 clock enable */
	 __HAL_RCC_TIM3_CLK_ENABLE();

	 /* TIM3 interrupt Init */
	 HAL_NVIC_SetPriority(TIM3_TIM4_IRQn, 0, 0);
	 HAL_NVIC_EnableIRQ(TIM3_TIM4_IRQn);

}
/*-----------------------------------------------------------*/
/* TIM4 init function */
void MX_TIM4_Init(void)
{
	/* USER CODE BEGIN TIM4_Init 0 */
	__TIM4_CLK_ENABLE();
	/* USER CODE END TIM4_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	/* USER CODE BEGIN TIM4_Init 1 */

	/* USER CODE END TIM4_Init 1 */
	htim4.Instance = TIM4;
	htim4.Init.Prescaler = (uint32_t )(HAL_RCC_GetSysClockFreq() / PWM_TIMER_CLOCK) - 1;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.Period = 1023;
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_Base_Init(&htim4);

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig);

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig);

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, _RGB_GREEN_TIM_CH);

	/* USER CODE BEGIN TIM4_Init 2 */

	/* USER CODE END TIM4_Init 2 */
	HAL_TIM_MspPostInit(&htim4);

	/* TIM4 clock enable */
	  __HAL_RCC_TIM4_CLK_ENABLE();

	  /* TIM4 interrupt Init */
	  HAL_NVIC_SetPriority(TIM3_TIM4_IRQn, 0, 0);
	  HAL_NVIC_EnableIRQ(TIM3_TIM4_IRQn);

}
/*-----------------------------------------------------------*/

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{

GPIO_InitTypeDef GPIO_InitStruct = {0};
if(timHandle->Instance==TIM2)
{
	/* USER CODE BEGIN TIM2_MspPostInit 0 */

	/* USER CODE END TIM2_MspPostInit 0 */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	/**TIM2 GPIO Configuration
	PA15     ------> TIM2_CH1
	*/
	GPIO_InitStruct.Pin = _RGB_RED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM2;
	HAL_GPIO_Init(_RGB_RED_PORT, &GPIO_InitStruct);

	/* USER CODE BEGIN TIM2_MspPostInit 1 */

	/* USER CODE END TIM2_MspPostInit 1 */
}

else if(timHandle->Instance==TIM3)
{
	/* USER CODE BEGIN TIM3_MspPostInit 0 */

	/* USER CODE END TIM3_MspPostInit 0 */

	__HAL_RCC_GPIOA_CLK_ENABLE();
	/**TIM3 GPIO Configuration
	PA6     ------> TIM3_CH1
	*/
	GPIO_InitStruct.Pin = _RGB_BLUE_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
	HAL_GPIO_Init(_RGB_BLUE_PORT, &GPIO_InitStruct);

	/* USER CODE BEGIN TIM3_MspPostInit 1 */

	/* USER CODE END TIM3_MspPostInit 1 */
}

else if(timHandle->Instance==TIM4)
{
	/* USER CODE BEGIN TIM4_MspPostInit 0 */

	/* USER CODE END TIM4_MspPostInit 0 */

	__HAL_RCC_GPIOB_CLK_ENABLE();
	/**TIM4 GPIO Configuration
	PB7     ------> TIM4_CH2
	*/
	GPIO_InitStruct.Pin = _RGB_GREEN_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF9_TIM4;
	HAL_GPIO_Init(_RGB_GREEN_PORT, &GPIO_InitStruct);

	/* USER CODE BEGIN TIM4_MspPostInit 1 */

	/* USER CODE END TIM4_MspPostInit 1 */
}

}

/*-----------------------------------------------------------*/
/*  Micro-seconds timebase init function - TIM16 (16-bit)
 */
void TIM_USEC_Init(void){

	__TIM16_CLK_ENABLE();

	htim16.Instance = TIM16;
	htim16.Init.Prescaler = 47;
	htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim16.Init.Period = 0XFFFF;
	htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim16.Init.RepetitionCounter = 0;
	htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_Base_Init(&htim16);

	HAL_TIM_Base_Start(&htim16);

}
/*-------------------------------------------------------------*/
/*  Milli-seconds timebase init function - TIM17 (16-bit)
 */
void TIM_MSEC_Init(void){

	__TIM17_CLK_ENABLE();
	htim17.Instance = TIM17;
	htim17.Init.Prescaler = 47999;
	htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim17.Init.Period = 0xFFFF;
	htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim17.Init.RepetitionCounter = 0;
	htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	HAL_TIM_Base_Init(&htim17);
	
	HAL_TIM_Base_Start(&htim17);
}

/*-----------------------------------------------------------*/

/* --- Load and start micro-second delay counter --- 
 */
void StartMicroDelay(uint16_t Delay){
	uint32_t t0 =0;
	
	portENTER_CRITICAL();
	
	if(Delay){
		t0 =htim16.Instance->CNT;
		
		while(htim16.Instance->CNT - t0 <= Delay){};
	}

	portEXIT_CRITICAL();
}

/*-----------------------------------------------------------*/

/* --- Load and start milli-second delay counter --- 
 */
void StartMilliDelay(uint16_t Delay){
	uint32_t t0 =0;
	
	portENTER_CRITICAL();
	
	if(Delay){
		t0 =htim17.Instance->CNT;
		
		while(htim17.Instance->CNT - t0 <= Delay){};
	}

	portEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/************************ (C) COPYRIGHT HEXABITZ *****END OF FILE****/
