/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2015 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
	
/*
		MODIFIED by Hexabitz for BitzOS (BOS) V0.2.1 - Copyright (C) 2017-2020 Hexabitz
    All rights reserved
*/

/* Includes ------------------------------------------------------------------*/
#include "BOS.h"

GPIO_InitTypeDef mypin;

/* Private variables ---------------------------------------------------------*/
uint8_t in[8];
/* Private function prototypes -----------------------------------------------*/
void GPIO_config(void);
/* Main functions ------------------------------------------------------------*/

int main(void)
{

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all user peripherals */

	/* Initialize BitzOS */
	BOS_Init();

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  while (1)
  {


  }


}

/*-----------------------------------------------------------*/

/* User Task */
void UserTask(void * argument)
{

//	GPIO_config();
	HAL_ADCEx_Calibration_Start(&hadc);
  HAL_ADC_Start_DMA(&hadc,(uint32_t *)in,8);
  /* Infinite loop */
  for(;;)
  {

	}
}
void GPIO_config(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	mypin.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4;
	mypin.Mode=GPIO_MODE_ANALOG;
	mypin.Pull= GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&mypin);
}
/*-----------------------------------------------------------*/

/************************ (C) COPYRIGHT HEXABITZ *****END OF FILE****/
