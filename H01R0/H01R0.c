/*
    BitzOS (BOS) V0.1.6 - Copyright (C) 2017-2019 Hexabitz
    All rights reserved

    File Name     : H01R0.c
    Description   : Source code for module H01R0.
										RGB LED (Cree CLVBA-FKA-CC1F1L1BB7R3R3)
		
		Required MCU resources : 
		
			>> USARTs 1,2,3,4,5,6 for module ports.
			>> Timer 3 (Ch2-Ch4) for RGB PWM.
			>> GPIOB 0, GPIOB 1, GPIOA 7 for RGB LED.
			
*/
	
/* Includes ------------------------------------------------------------------*/
#include "BOS.h"


/* Define UART variables */
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart6;

/* Module exported parameters ------------------------------------------------*/
module_param_t modParam[NUM_MODULE_PARAMS] = {{.paramPtr=NULL, .paramFormat=FMT_FLOAT, .paramName=""}};

/* Private variables ---------------------------------------------------------*/


TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim16;
uint8_t globalRed = 0, globalGreen = 0, globalBlue = 0;

uint8_t RGB_LED_State = 0, rgbLedMode = 0, rgbColor = 0, rgbRed = 0, rgbGreen = 0, rgbBlue = 0; 
uint32_t rgbPeriod = 0, rgbDC = 0; int16_t rgbCount = 0;
TaskHandle_t RGBledTaskHandle = NULL;

/* Private function prototypes -----------------------------------------------*/	

void RGBledTask(void * argument);
void RGBpulse(uint8_t mode);
void RGBsweepBasic(void);
void RGBsweepFine(void);
void RGBdim(uint8_t mode);
void TIM3_Init(void);


/* Create CLI commands --------------------------------------------------------*/

portBASE_TYPE demoCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
portBASE_TYPE onCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
portBASE_TYPE offCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
portBASE_TYPE colorCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
portBASE_TYPE RGBCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
portBASE_TYPE toggleCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
portBASE_TYPE pulseColorCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
portBASE_TYPE pulseRGBCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
portBASE_TYPE sweepCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
portBASE_TYPE dimCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );

/* CLI command structure : demo */
const CLI_Command_Definition_t demoCommandDefinition =
{
	( const int8_t * ) "demo", /* The command string to type. */
	( const int8_t * ) "demo:\r\n Run a demo program to test module functionality\r\n\r\n",
	demoCommand, /* The function to run. */
	0 /* No parameters are expected. */
};
/*-----------------------------------------------------------*/
/* CLI command structure : on */
const CLI_Command_Definition_t onCommandDefinition =
{
	( const int8_t * ) "on", /* The command string to type. */
	( const int8_t * ) "on:\r\n Turn RGB LED on (white color) at a specific intensity (0-100%) (1st par.)\r\n\r\n",
	onCommand, /* The function to run. */
	1 /* One parameter is expected. */
};
/*-----------------------------------------------------------*/
/* CLI command structure : off */
const CLI_Command_Definition_t offCommandDefinition =
{
	( const int8_t * ) "off", /* The command string to type. */
	( const int8_t * ) "off:\r\n Turn RGB LED off\r\n\r\n",
	offCommand, /* The function to run. */
	0 /* No parameters are expected. */
};
/*-----------------------------------------------------------*/
/* CLI command structure : color */
const CLI_Command_Definition_t colorCommandDefinition =
{
	( const int8_t * ) "color", /* The command string to type. */
	( const int8_t * ) "color:\r\n Set RGB LED color (1st par.) at a specific intensity (0-100%) (2nd par.)\n\rRegistered colors are:\
\r\nblack, white, red, blue, green, yellow, cyan, and magenta \r\n\r\n",
	colorCommand, /* The function to run. */
	2 /* Two parameters are expected. */
};
/*-----------------------------------------------------------*/
/* CLI command structure : RGB */
const CLI_Command_Definition_t RGBCommandDefinition =
{
	( const int8_t * ) "rgb", /* The command string to type. */
	( const int8_t * ) "RGB:\r\n Set RGB LED red (1st par.), green (2nd par.), and blue (3rd par.) values (0-255) at a specific intensity (0-100%) (4th par.)\r\n\r\n",
	RGBCommand, /* The function to run. */
	4 /* Four parameters are expected. */
};
/*-----------------------------------------------------------*/
/* CLI command structure : toggle */
const CLI_Command_Definition_t toggleCommandDefinition =
{
	( const int8_t * ) "toggle", /* The command string to type. */
	( const int8_t * ) "toggle:\r\n Toggle RGB LED (white color) at a specific intensity (0-100%) (1st par.)\r\n\r\n",
	toggleCommand, /* The function to run. */
	1 /* One parameter is expected. */
};
/*-----------------------------------------------------------*/
/* CLI command structure : pulseColor */
const CLI_Command_Definition_t pulseColorCommandDefinition =
{
	( const int8_t * ) "pulsecolor", /* The command string to type. */
	( const int8_t * ) "pulseColor:\r\n Send a pulse on RGB LED using a specific color (1st par.), pulse period (ms) (2nd par.), pulse duty cycle (ms) (3rd par.) \
and pulse repeat times (4th par.) (type 'inf' for periodic signal)\r\n\r\n",
	pulseColorCommand, /* The function to run. */
	4 /* Four parameters are expected. */
};
/*-----------------------------------------------------------*/
/* CLI command structure : pulseRGB */
const CLI_Command_Definition_t pulseRGBCommandDefinition =
{
	( const int8_t * ) "pulsergb", /* The command string to type. */
	( const int8_t * ) "pulseRGB:\r\n Send a pulse on RGB LED using RGB values (1st, 2nd and 3rd par.) (0-255), pulse period (ms) (4th par.), pulse duty cycle (ms) (5th par.) \
and pulse repeat times (6th par.) (type 'inf' for periodic signal)\r\n\r\n",
	pulseRGBCommand, /* The function to run. */
	6 /* Six parameters are expected. */
};
/*-----------------------------------------------------------*/
/* CLI command structure : sweep */
const CLI_Command_Definition_t sweepCommandDefinition =
{
	( const int8_t * ) "sweep", /* The command string to type. */
		( const int8_t * ) "sweep:\r\n Perform color sweep on RGB LED using a specific sweep mode ('basic': sweep basic color only, 'fine': sweep all colors) (1st par.), sweep period (ms) (2nd par.) \
and sweep repeat times (3rd par.) (type 'inf' for periodic signal)\r\n\r\n",
	sweepCommand, /* The function to run. */
	3 /* Three parameters are expected. */
};
/*-----------------------------------------------------------*/
/* CLI command structure : dim */
const CLI_Command_Definition_t dimCommandDefinition =
{
	( const int8_t * ) "dim", /* The command string to type. */
		( const int8_t * ) "dim:\r\n Dim a specific color (1st par.) on RGB LED using a specific dim mode ('up', 'upwait', 'down', 'downwait', 'updown', 'downup', 'updownwait', 'downupwait') (2nd par.), \
sweep period (ms) (3rd par.), wait time (ms) (4th par.) and dim repeat times (5th par.) (type 'inf' for periodic signal)\r\n\r\n",
	dimCommand, /* The function to run. */
	5 /* Five parameters are expected. */
};
/*-----------------------------------------------------------*/

/* -----------------------------------------------------------------------
	|												 Private Functions	 														|
   ----------------------------------------------------------------------- 
*/

/* --- H01R0 module initialization. 
*/
void Module_Init(void)
{
	/* Peripheral clock enable */
	_RGB_RED_GPIO_CLK();
	_RGB_GREEN_GPIO_CLK();
	_RGB_BLUE_GPIO_CLK();
	
	/* Array ports */
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_USART4_UART_Init();
  MX_USART5_UART_Init();
#ifdef H01R0	
  MX_USART6_UART_Init();
#endif
	
	/* LED PWM Timer */
	TIM3_Init();
	
	/* Create the RGB LED task */
	if (RGBledTaskHandle == NULL)
		xTaskCreate(RGBledTask, (const char *) "RGBledTask", configMINIMAL_STACK_SIZE, NULL, osPriorityNormal-osPriorityIdle, &RGBledTaskHandle);
}

/*-----------------------------------------------------------*/

/* --- H01R0 message processing task. 
*/
Module_Status Module_MessagingTask(uint16_t code, uint8_t port, uint8_t src, uint8_t dst, uint8_t shift)
{
	Module_Status result = H01R0_OK;
	uint32_t period = 0; uint32_t dc = 0; int32_t repeat = 0;
	
	switch (code)
	{
		case CODE_H01R0_ON :
			RGB_LED_on(cMessage[port-1][shift]);
			break;
		
		case CODE_H01R0_OFF :
			RGB_LED_off();
			break;
		
		case CODE_H01R0_TOGGLE :
			if (RGB_LED_State)
				RGB_LED_off();
			else
				RGB_LED_on(cMessage[port-1][shift]);
			break;

		case CODE_H01R0_COLOR :
			if (cMessage[port-1][shift] == 0) {
			/* Color definition from color list */
				RGB_LED_setColor(cMessage[port-1][1+shift], cMessage[port-1][2+shift]);
			} else if (cMessage[port-1][shift] == 1) {
			/* RGB color */
				RGB_LED_setRGB(cMessage[port-1][1+shift], cMessage[port-1][2+shift], cMessage[port-1][3+shift], cMessage[port-1][4+shift]);			
			}	
			break;
		
		case CODE_H01R0_PULSE :
			if (cMessage[port-1][shift] == 0) {
			/* Color definition from color list */
				period = ( (uint32_t) cMessage[port-1][2+shift] << 24 ) + ( (uint32_t) cMessage[port-1][3+shift] << 16 ) + ( (uint32_t) cMessage[port-1][4+shift] << 8 ) + cMessage[port-1][5+shift];
				dc = ( (uint32_t) cMessage[port-1][6+shift] << 24 ) + ( (uint32_t) cMessage[port-1][7+shift] << 16 ) + ( (uint32_t) cMessage[port-1][8+shift] << 8 ) + cMessage[port-1][9+shift];
				repeat = ( (uint32_t) cMessage[port-1][10+shift] << 24 ) + ( (uint32_t) cMessage[port-1][11+shift] << 16 ) + ( (uint32_t) cMessage[port-1][12+shift] << 8 ) + cMessage[port-1][13+shift];
				RGB_LED_pulseColor(cMessage[port-1][1+shift], period, dc, repeat);
			} else if (cMessage[port-1][shift] == 1) {
			/* RGB color */
				period = ( (uint32_t) cMessage[port-1][4+shift] << 24 ) + ( (uint32_t) cMessage[port-1][5+shift] << 16 ) + ( (uint32_t) cMessage[port-1][6+shift] << 8 ) + cMessage[port-1][7+shift];
				dc = ( (uint32_t) cMessage[port-1][8+shift] << 24 ) + ( (uint32_t) cMessage[port-1][9+shift] << 16 ) + ( (uint32_t) cMessage[port-1][10+shift] << 8 ) + cMessage[port-1][11+shift];
				repeat = ( (uint32_t) cMessage[port-1][12+shift] << 24 ) + ( (uint32_t) cMessage[port-1][13+shift] << 16 ) + ( (uint32_t) cMessage[port-1][14+shift] << 8 ) + cMessage[port-1][15+shift];
				RGB_LED_pulseRGB(cMessage[port-1][1+shift], cMessage[port-1][2+shift], cMessage[port-1][3+shift], period, dc, repeat);			
			}				
			break;
			
		case CODE_H01R0_SWEEP :
			period = ( (uint32_t) cMessage[port-1][1+shift] << 24 ) + ( (uint32_t) cMessage[port-1][2+shift] << 16 ) + ( (uint32_t) cMessage[port-1][3+shift] << 8 ) + cMessage[port-1][4+shift];
			repeat = ( (uint32_t) cMessage[port-1][5+shift] << 24 ) + ( (uint32_t) cMessage[port-1][6+shift] << 16 ) + ( (uint32_t) cMessage[port-1][7+shift] << 8 ) + cMessage[port-1][8+shift];
			RGB_LED_sweep(cMessage[port-1][shift], period, repeat);
			break;
		
		case CODE_H01R0_DIM :
			period = ( (uint32_t) cMessage[port-1][2+shift] << 24 ) + ( (uint32_t) cMessage[port-1][3+shift] << 16 ) + ( (uint32_t) cMessage[port-1][4+shift] << 8 ) + cMessage[port-1][5+shift];
			dc = ( (uint32_t) cMessage[port-1][6+shift] << 24 ) + ( (uint32_t) cMessage[port-1][7+shift] << 16 ) + ( (uint32_t) cMessage[port-1][8+shift] << 8 ) + cMessage[port-1][9+shift];
			repeat = ( (uint32_t) cMessage[port-1][10+shift] << 24 ) + ( (uint32_t) cMessage[port-1][11+shift] << 16 ) + ( (uint32_t) cMessage[port-1][12+shift] << 8 ) + cMessage[port-1][13+shift];
			RGB_LED_dim(cMessage[port-1][shift], cMessage[port-1][1+shift], period, dc, repeat);
			break;
		
		default:
			result = H01R0_ERR_UnknownMessage;
			break;
	}			

	return result;	
}

/*-----------------------------------------------------------*/

/* --- Register this module CLI Commands 
*/
void RegisterModuleCLICommands(void)
{
	FreeRTOS_CLIRegisterCommand( &demoCommandDefinition );
	FreeRTOS_CLIRegisterCommand( &onCommandDefinition );
	FreeRTOS_CLIRegisterCommand( &offCommandDefinition );
	FreeRTOS_CLIRegisterCommand( &colorCommandDefinition );
	FreeRTOS_CLIRegisterCommand( &RGBCommandDefinition );
	FreeRTOS_CLIRegisterCommand( &toggleCommandDefinition );
	FreeRTOS_CLIRegisterCommand( &pulseColorCommandDefinition );
	FreeRTOS_CLIRegisterCommand( &pulseRGBCommandDefinition );
	FreeRTOS_CLIRegisterCommand( &sweepCommandDefinition );
	FreeRTOS_CLIRegisterCommand( &dimCommandDefinition );
}

/*-----------------------------------------------------------*/

/* --- Get the port for a given UART. 
*/
uint8_t GetPort(UART_HandleTypeDef *huart)
{
#ifdef H01R0
	if (huart->Instance == USART4)
		return P1;
	else if (huart->Instance == USART2)
		return P2;
	else if (huart->Instance == USART6)
		return P3;
	else if (huart->Instance == USART3)
		return P4;
	else if (huart->Instance == USART1)
		return P5;
	else if (huart->Instance == USART5)
		return P6;
#endif
#ifdef P01R0
	if (huart->Instance == USART4)
		return P1;
	else if (huart->Instance == USART2)
		return P2;
	else if (huart->Instance == USART3)
		return P3;
	else if (huart->Instance == USART1)
		return P4;
	else if (huart->Instance == USART5)
		return P5;	
#endif	
	
	return 0;
}

/*-----------------------------------------------------------*/

/* RGBledTask function */
void RGBledTask(void * argument)
{

  /* Infinite loop */
  for(;;)
  {
		/* Switch RGB LED according to its mode */
		switch (rgbLedMode)
		{
			case RGB_PULSE_RGB :			
				RGBpulse(rgbLedMode);
				break;
			
			case RGB_PULSE_COLOR :
				RGBpulse(rgbLedMode);
				break;
			
			case RGB_SWEEP_BASIC :
				RGBsweepBasic();
				break;

			case RGB_SWEEP_FINE :
				RGBsweepFine();
				break;
			
			case RGB_DIM_UP :
				RGBdim(rgbLedMode);
				break;
			
			case RGB_DIM_UP_WAIT :
				RGBdim(rgbLedMode);
				break;
			
			case RGB_DIM_DOWN :
				RGBdim(rgbLedMode);
				break;
			
			case RGB_DIM_DOWN_WAIT :
				RGBdim(rgbLedMode);
				break;
			
			case RGB_DIM_UP_DOWN :
				RGBdim(rgbLedMode);
				break;
			
			case RGB_DIM_DOWN_UP :
				RGBdim(rgbLedMode);
				break;
			
			case RGB_DIM_UP_DOWN_WAIT :
				RGBdim(rgbLedMode);
				break;
			
			case RGB_DIM_DOWN_UP_WAIT :
				RGBdim(rgbLedMode);
				break;
			
			default:
				osDelay(10);
				break;
		}
		
		taskYIELD();
  }	

}

/*-----------------------------------------------------------*/

/* TIM3 init function - Front-end RED LED PWM Timer 16-bit 
*/
void TIM3_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
	
	/* Peripheral clock enable */
  __TIM3_CLK_ENABLE();
	
	/**TIM3 GPIO Configuration    
	*/
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Pin = _RGB_RED_PIN;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
	HAL_GPIO_Init(_RGB_RED_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = _RGB_GREEN_PIN;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
	HAL_GPIO_Init(_RGB_GREEN_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = _RGB_BLUE_PIN;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
	HAL_GPIO_Init(_RGB_BLUE_PORT, &GPIO_InitStruct);
	
	/* Peripheral interrupt init */
	HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);

	/* Timer base configuration - 1 MHz */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = (uint32_t)(HAL_RCC_GetSysClockFreq()/PWM_TIMER_CLOCK) - 1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 0;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htim3);

	/* Timer PWM configuration */
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig);
  HAL_TIM_PWM_Init(&htim3);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig);

	/* Timer PWM channels */
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, _RGB_RED_TIM_CH);
	HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, _RGB_GREEN_TIM_CH);
	HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, _RGB_BLUE_TIM_CH);

}

/*-----------------------------------------------------------*/
/* --- Load and start red LED PWM ---
			Inputs:
					red Duty cycle of red LED (0-255).
					green Duty cycle of green LED (0-255).
					blue Duty cycle of blue LED (0-255).
					intensity RGB LED intensity (0-100).
*/
Module_Status startPWM(uint8_t red, uint8_t green, uint8_t blue, uint8_t intensity)
{
	uint32_t period = PWM_TIMER_CLOCK / RGB_PWM_FREQ;
	
	/* PWM period */
	htim3.Instance->ARR = period - 1;
	
	/* PWM duty cycle */
	htim3.Instance->CCR2 = ((float)intensity/100.0f) * ((float)red/255.0f) * period;
	htim3.Instance->CCR3 = ((float)intensity/100.0f) * ((float)green/255.0f) * period;
	htim3.Instance->CCR4 = ((float)intensity/100.0f) * ((float)blue/255.0f) * period;

	if (HAL_TIM_PWM_Start(&htim3, _RGB_RED_TIM_CH) != HAL_OK)	
		return	H01R0_ERROR;
	if (HAL_TIM_PWM_Start(&htim3, _RGB_GREEN_TIM_CH) != HAL_OK)	
		return	H01R0_ERROR;
	if (HAL_TIM_PWM_Start(&htim3, _RGB_BLUE_TIM_CH) != HAL_OK)	
		return	H01R0_ERROR;
	
	return	H01R0_OK;
}

/*-----------------------------------------------------------*/

/* --- Pulse the RGB LED --- 
*/
void RGBpulse(uint8_t mode)
{
	uint8_t temp = 0;
	
	if (rgbCount > 0 || rgbCount == -1) 
	{
		if (mode == RGB_PULSE_RGB)
			RGB_LED_setRGB(rgbRed, rgbGreen, rgbBlue, 100);
		else if (mode == RGB_PULSE_COLOR)
			RGB_LED_setColor(rgbColor, 100);	
		osDelay(rgbDC);
		temp = rgbLedMode;			/* Backup rgbLedMode so that it's not reset */
		RGB_LED_off();
		rgbLedMode = temp;
		osDelay(rgbPeriod-rgbDC);
		
		if (rgbCount > 0)
			rgbCount--;
	} 
	else 
	{
		rgbLedMode = 0;
	}
}

/*-----------------------------------------------------------*/

/* --- RGB LED basic color sweep --- 
*/
void RGBsweepBasic(void)
{
	static uint32_t temp;
		
	temp = rgbPeriod/6;
	
	if (rgbCount > 0 || rgbCount == -1) 
	{
		RGB_LED_setColor(RED, 100);
		osDelay(temp);
		RGB_LED_setColor(YELLOW, 100);
		osDelay(temp);
		RGB_LED_setColor(GREEN, 100);
		osDelay(temp);
		RGB_LED_setColor(CYAN, 100);
		osDelay(temp);
		RGB_LED_setColor(BLUE, 100);
		osDelay(temp);
		RGB_LED_setColor(MAGENTA, 100);
		osDelay(temp);
	
		if (rgbCount > 0)
			rgbCount--;
	} 
	else 
	{
		RGB_LED_off();
	}
}

/*-----------------------------------------------------------*/

/* --- RGB LED fine color sweep --- 
*/
void RGBsweepFine(void)
{
	static uint32_t temp;
		
	temp = rgbPeriod/6;
	
	if (rgbCount > 0 || rgbCount == -1) 
	{
		/* Red */
		for(uint8_t i=0 ; i<255 ; i++)
		{
			RGB_LED_setRGB(255, i, 0, 100);	
			osDelay(ceil(temp/255));
		}	
		/* Yellow */		
		for(uint8_t i=255 ; i>0 ; i--)
		{
			RGB_LED_setRGB(i, 255, 0, 100);
			osDelay(ceil(temp/255));
		}
		/* Green */
		for(uint8_t i=0 ; i<255 ; i++)
		{		
			RGB_LED_setRGB(0, 255, i, 100);
			osDelay(ceil(temp/255));
		}		
		/* Cyan */
		for(uint8_t i=255 ; i>0 ; i--)
		{		
			RGB_LED_setRGB(0, i, 255, 100);
			osDelay(ceil(temp/255));
		}
		/* Blue */
		for(uint8_t i=0 ; i<255 ; i++)
		{			
			RGB_LED_setRGB(i, 0, 255, 100);
			osDelay(ceil(temp/255));
		}		
		/* Magenta */
		for(uint8_t i=255 ; i>0 ; i--)
		{			
			RGB_LED_setRGB(255, 0, i, 100);
			osDelay(ceil(temp/255));
		}	
	
		if (rgbCount > 0)
			rgbCount--;
	} 
	else 
	{
		RGB_LED_off();
	}
}

/*-----------------------------------------------------------*/

/* --- Dim the RGB LED --- 
*/
void RGBdim(uint8_t mode)
{
	uint8_t temp = 0;
	
	if (rgbCount > 0 || rgbCount == -1) 
	{
		temp = rgbLedMode;			/* Store mode so that it's not reset */
		if (mode == RGB_DIM_UP) {
			for(uint8_t i=0 ; i<=100 ; i++)
			{
				RGB_LED_setColor(rgbColor, i);	
				osDelay(rgbPeriod/100);
			}	
		} else if (mode == RGB_DIM_UP_WAIT) {
			for(uint8_t i=0 ; i<=100 ; i++)
			{
				RGB_LED_setColor(rgbColor, i);	
				osDelay((rgbPeriod-rgbDC)/100);
			}				
			osDelay(rgbDC);		
		} else if (mode == RGB_DIM_DOWN) {
			for(uint8_t i=101 ; i>0 ; i--)
			{
				RGB_LED_setColor(rgbColor, i-1);	
				osDelay(rgbPeriod/100);
			}			
		} else if (mode == RGB_DIM_DOWN_WAIT) {
			for(uint8_t i=101 ; i>0 ; i--)
			{
				RGB_LED_setColor(rgbColor, i-1);	
				osDelay((rgbPeriod-rgbDC)/100);
			}	
			osDelay(rgbDC);
		} else if (mode == RGB_DIM_UP_DOWN) {
			for(uint8_t i=0 ; i<=100 ; i++)
			{
				RGB_LED_setColor(rgbColor, i);	
				osDelay(rgbPeriod/200);
			}				
			for(uint8_t i=101 ; i>0 ; i--)
			{
				RGB_LED_setColor(rgbColor, i-1);	
				osDelay(rgbPeriod/200);
			}				
		} else if (mode == RGB_DIM_DOWN_UP) {
			for(uint8_t i=101 ; i>0 ; i--)
			{
				RGB_LED_setColor(rgbColor, i-1);	
				osDelay(rgbPeriod/200);
			}					
			for(uint8_t i=0 ; i<=100 ; i++)
			{
				RGB_LED_setColor(rgbColor, i);	
				osDelay(rgbPeriod/200);
			}				
		} else if (mode == RGB_DIM_UP_DOWN_WAIT) {
			for(uint8_t i=0 ; i<=100 ; i++)
			{
				RGB_LED_setColor(rgbColor, i);	
				osDelay((rgbPeriod-rgbDC)/200);
			}				
			for(uint8_t i=101 ; i>0 ; i--)
			{
				RGB_LED_setColor(rgbColor, i-1);	
				osDelay((rgbPeriod-rgbDC)/200);
			}		
			osDelay(rgbDC);
		} else if (mode == RGB_DIM_DOWN_UP_WAIT) {
			for(uint8_t i=101 ; i>0 ; i--)
			{
				RGB_LED_setColor(rgbColor, i-1);	
				osDelay((rgbPeriod-rgbDC)/200);
			}				
			for(uint8_t i=0 ; i<=100 ; i++)
			{
				RGB_LED_setColor(rgbColor, i);	
				osDelay((rgbPeriod-rgbDC)/200);
			}	
			osDelay(rgbDC);
			rgbLedMode = temp;
		}

		if (rgbCount > 0)
			rgbCount--;
	} 
	else 
	{
		rgbLedMode = 0;
	}
}

/*-----------------------------------------------------------*/

/* -----------------------------------------------------------------------
	|																APIs	 																 	|
   ----------------------------------------------------------------------- 
*/

/* --- Turn on RGB LED (white color) --- 
*/
Module_Status RGB_LED_on(uint8_t intensity)
{
	Module_Status result = H01R0_OK;
	
	if (intensity == 0) 
	{	
		htim3.Instance->CCR2 = 0;
		htim3.Instance->CCR3 = 0;
		htim3.Instance->CCR4 = 0;	

		RGB_LED_State = 0;
		
		return H01R0_OK;		
	} 
	else if (intensity <= 100)
	{
		result = startPWM(255, 255, 255, intensity);
		
		if (result == H01R0_OK)	RGB_LED_State = 1;
		
		return result; 
	}
	else
		return H01R0_ERR_WrongIntensity;
	
}

/*-----------------------------------------------------------*/

/* --- Turn off RGB LED --- 
*/
Module_Status RGB_LED_off(void)
{
	if (HAL_TIM_Base_Stop(&htim3) != HAL_OK)	
		return H01R0_ERROR;
	
	htim3.Instance->CCR2 = 0;
	htim3.Instance->CCR3 = 0;
	htim3.Instance->CCR4 = 0;	
	
	RGB_LED_State = 0;
	rgbLedMode = 0;
	
	return H01R0_OK;
}

/*-----------------------------------------------------------*/

/* --- Toggle RGB LED --- 
*/
Module_Status RGB_LED_toggle(uint8_t intensity)
{
	Module_Status result = H01R0_OK;
	
	if (RGB_LED_State)
		result = RGB_LED_off();
	else
		result = RGB_LED_on(intensity);
	
	return result;
}

/*-----------------------------------------------------------*/

/* --- Set RGB colors on LED (continuously) using PWM intensity modulation. 
*/
Module_Status RGB_LED_setRGB(uint8_t red, uint8_t green, uint8_t blue, uint8_t intensity)
{
	if (intensity == 0) 	
		return RGB_LED_on(0);
	else if (intensity > 100) 
		return H01R0_ERR_WrongIntensity;
	else
		return startPWM(red, green, blue, intensity);
}

/*-----------------------------------------------------------*/

/* --- Set LED color from a predefined color list (continuously) 
				using PWM intensity modulation. 
*/
Module_Status RGB_LED_setColor(uint8_t color, uint8_t intensity)
{
	Module_Status result = H01R0_OK;
	
	if (!intensity) 
		return RGB_LED_on(0);
	else if (intensity > 100) 
		return H01R0_ERR_WrongIntensity;
	else 
	{	
		switch (color)
		{
			case BLACK 		: result = RGB_LED_off();
				break;
			case WHITE 		: result = RGB_LED_on(intensity);
				break;
			case RED 			: result = RGB_LED_setRGB(255,0,0,intensity);
				break;
			case BLUE 		: result = RGB_LED_setRGB(0,0,255,intensity);
				break;
			case YELLOW 	: result = RGB_LED_setRGB(255,255,0,intensity);
				break;
			case CYAN 		: result = RGB_LED_setRGB(0,255,255,intensity);
				break;
			case MAGENTA 	: result = RGB_LED_setRGB(255,0,255,intensity);
				break;
			case GREEN 		: result = RGB_LED_setRGB(0,255,0,intensity);
				break;
			default				:	result = H01R0_ERR_WrongColor;
				break;
		}
	}
	
	return result;
}

/*-----------------------------------------------------------*/

/* --- Activate the RGB LED pulse command with RGB values. Set repeat to -1 for periodic signals --- 
*/
Module_Status RGB_LED_pulseRGB(uint8_t red, uint8_t green, uint8_t blue, uint32_t period, uint32_t dc, int32_t repeat)
{
	Module_Status result = H01R0_OK;
	
	rgbRed = red; rgbGreen = green; rgbBlue = blue;
	rgbPeriod = period; rgbDC = dc; rgbCount = repeat;
	
	rgbLedMode = RGB_PULSE_RGB;
	
	return result;
}

/*-----------------------------------------------------------*/

/* --- Activate the RGB LED pulse command with a specific color. Set repeat to -1 for periodic signals --- 
*/
Module_Status RGB_LED_pulseColor(uint8_t color, uint32_t period, uint32_t dc, int32_t repeat)
{
	Module_Status result = H01R0_OK;
	
	rgbColor = color;
	rgbPeriod = period; rgbDC = dc; rgbCount = repeat;
	
	rgbLedMode = RGB_PULSE_COLOR;
	
	return result;
}

/*-----------------------------------------------------------*/

/* --- Activate the RGB LED sweep mode. Set repeat to -1 for periodic signals. Minimum period for fine sweep is 6 x 256 = 1536 ms --- 
*/
Module_Status RGB_LED_sweep(uint8_t mode, uint32_t period, int32_t repeat)
{
	if (mode == 3 || mode == 4)
	{		
	Module_Status result = H01R0_OK;
	
	rgbPeriod = period; rgbCount = repeat;
	rgbLedMode = mode;

	return result;
	}
	else
	{
		return H01R0_ERR_WrongMode;
	}
}

/*-----------------------------------------------------------*/

/* --- Activate RGB LED dim mode using one of the basic colors. Set repeat to -1 for periodic signals --- 
*/
Module_Status RGB_LED_dim(uint8_t color, uint8_t mode, uint32_t period, uint32_t wait, int32_t repeat)
{
	if (mode >= 5 && mode <= 12)
	{	
	Module_Status result = H01R0_OK;
	
	rgbColor = color;
	rgbPeriod = period; rgbDC = wait; rgbCount = repeat;
	rgbLedMode = mode;
	
	return result;
	}
	else
	{
		return H01R0_ERR_WrongMode;
	}
}

/*-----------------------------------------------------------*/


/* -----------------------------------------------------------------------
	|															Commands																 	|
   ----------------------------------------------------------------------- 
*/

portBASE_TYPE demoCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	static const int8_t *pcRedMessage = ( int8_t * ) "Red LED is on\r\n";
	static const int8_t *pcGreenMessage = ( int8_t * ) "Green LED is on\r\n";
	static const int8_t *pcBlueMessage = ( int8_t * ) "Blue LED is on";
	
	/* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
	( void ) pcCommandString;
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );

	/* Respond to the command */
	RGB_LED_off(); RGB_LED_setColor(RED, 50);
	writePxMutex(PcPort, ( char * ) pcRedMessage, strlen(( char * ) pcRedMessage), 10, 10);
	Delay_ms(1000);
	RGB_LED_off(); RGB_LED_setColor(GREEN, 50);
	writePxMutex(PcPort, ( char * ) pcGreenMessage, strlen(( char * ) pcGreenMessage), 10, 10);
	Delay_ms(1000);	
	RGB_LED_off(); RGB_LED_setColor(BLUE, 50);
	writePxMutex(PcPort, ( char * ) pcBlueMessage, strlen(( char * ) pcBlueMessage), 10, 10);
	Delay_ms(1000);	
	RGB_LED_off();
	strcpy( ( char * ) pcWriteBuffer, "\r\n");
	
	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}

/*-----------------------------------------------------------*/

portBASE_TYPE onCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	Module_Status result = H01R0_OK;
	
	int8_t *pcParameterString1; portBASE_TYPE xParameterStringLength1 = 0; 
	uint8_t intensity = 0;
	static const int8_t *pcOKMessage = ( int8_t * ) "RGB LED is on at intensity %d%%\r\n";
	static const int8_t *pcWrongIntensityMessage = ( int8_t * ) "Wrong intensity!\n\r";
	
	/* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );
	
	/* Obtain the 1st parameter string. */
	pcParameterString1 = ( int8_t * ) FreeRTOS_CLIGetParameter
								(
									pcCommandString,		/* The command string itself. */
									1,						/* Return the first parameter. */
									&xParameterStringLength1	/* Store the parameter string length. */
								);
	intensity = ( uint8_t ) atol( ( char * ) pcParameterString1 );
	
	result = RGB_LED_on(intensity);	
	
	/* Respond to the command */
	if (result == H01R0_OK)
		sprintf( ( char * ) pcWriteBuffer, ( char * ) pcOKMessage, intensity);
	else if (result == H01R0_ERR_WrongIntensity)
		strcpy( ( char * ) pcWriteBuffer, ( char * ) pcWrongIntensityMessage);
	
	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}

/*-----------------------------------------------------------*/

portBASE_TYPE offCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	static const int8_t *pcMessage = ( int8_t * ) "RGB LED is off\r\n";
	
	/* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
	( void ) pcCommandString;
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );

	/* Respond to the command */
	strcpy( ( char * ) pcWriteBuffer, ( char * ) pcMessage);
	RGB_LED_off();	
	
	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}

/*-----------------------------------------------------------*/

portBASE_TYPE colorCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	Module_Status result = H01R0_OK;
	uint8_t color = 0; uint8_t intensity = 0; char par[15] = {0};
	static int8_t *pcParameterString1, *pcParameterString2; 
	portBASE_TYPE xParameterStringLength1 = 0, xParameterStringLength2 = 0;
	
	static const int8_t *pcOKMessage = ( int8_t * ) "RGB LED color is %s at intensity %d%%\n\r";
	static const int8_t *pcWrongColorMessage = ( int8_t * ) "Unknown color!\n\r";
	static const int8_t *pcWrongIntensityMessage = ( int8_t * ) "Wrong intensity!\n\r";
	
	/* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );
	
	/* Obtain the 1st parameter string. */
	pcParameterString1 = ( int8_t * ) FreeRTOS_CLIGetParameter
								(
									pcCommandString,		/* The command string itself. */
									1,						/* Return the first parameter. */
									&xParameterStringLength1	/* Store the parameter string length. */
								);
	/* Read the color value. */
	if (!strncmp((const char *)pcParameterString1, "black", xParameterStringLength1))
		color = BLACK;
	else if (!strncmp(( const char *)pcParameterString1, "white", xParameterStringLength1))
		color = WHITE;
	else if (!strncmp((const char *)pcParameterString1, "red", xParameterStringLength1))
		color = RED;
	else if (!strncmp((const char *) pcParameterString1, "blue", xParameterStringLength1))
		color = BLUE;
	else if (!strncmp((const char *) pcParameterString1, "yellow", xParameterStringLength1))
		color = YELLOW;
	else if (!strncmp((const char *) pcParameterString1, "cyan", xParameterStringLength1))
		color = CYAN;
	else if (!strncmp((const char *) pcParameterString1, "magenta", xParameterStringLength1))
		color = MAGENTA;
	else if (!strncmp((const char *) pcParameterString1, "green", xParameterStringLength1))
		color = GREEN;
	
	/* Obtain the 2nd parameter string. */
	pcParameterString2 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 2, &xParameterStringLength2);
	intensity = ( uint8_t ) atol( ( char * ) pcParameterString2 );
	
	result = RGB_LED_setColor(color, intensity);
	
	/* Respond to the command */
	if (result == H01R0_OK) 
	{
		/* Isolate first parameter string */
		strncpy(par, ( char * ) pcParameterString1, xParameterStringLength1);
		sprintf( ( char * ) pcWriteBuffer, ( char * ) pcOKMessage, par, intensity);
	}
	else if (result == H01R0_ERR_WrongColor)
		strcpy( ( char * ) pcWriteBuffer, ( char * ) pcWrongColorMessage);
	else if (result == H01R0_ERR_WrongIntensity)
		strcpy( ( char * ) pcWriteBuffer, ( char * ) pcWrongIntensityMessage);
	

	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}

/*-----------------------------------------------------------*/

portBASE_TYPE RGBCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	Module_Status result = H01R0_OK;
	uint8_t red = 0; uint8_t green = 0; uint8_t blue = 0; uint8_t intensity = 0; 
	static int8_t *pcParameterString1, *pcParameterString2, *pcParameterString3, *pcParameterString4; 
	portBASE_TYPE xParameterStringLength1 = 0, xParameterStringLength2 = 0;
	portBASE_TYPE xParameterStringLength3 = 0, xParameterStringLength4 = 0;
	
	static const int8_t *pcOKMessage = ( int8_t * ) "RGB LED is (%d, %d, %d) at intensity %d%%\n\r";
	static const int8_t *pcWrongColorMessage = ( int8_t * ) "Wrong color value!\n\r";
	static const int8_t *pcWrongIntensityMessage = ( int8_t * ) "Wrong intensity!\n\r";
	
	/* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );
	
	/* Obtain the 1st parameter string. */
	pcParameterString1 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 1, &xParameterStringLength1);
	red = ( uint8_t ) atol( ( char * ) pcParameterString1 );
	
	/* Obtain the 2nd parameter string. */
	pcParameterString2 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 2, &xParameterStringLength2);
	green = ( uint8_t ) atol( ( char * ) pcParameterString2 );
	
	/* Obtain the 3rd parameter string. */
	pcParameterString3 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 3, &xParameterStringLength3);
	blue = ( uint8_t ) atol( ( char * ) pcParameterString3 );
	
	/* Obtain the 4th parameter string. */
	pcParameterString4 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 4, &xParameterStringLength4);
	intensity = ( uint8_t ) atol( ( char * ) pcParameterString4 );
	
	result = RGB_LED_setRGB(red, green, blue, intensity);
	
	/* Respond to the command */
	if (result == H01R0_OK) 
		sprintf( ( char * ) pcWriteBuffer, ( char * ) pcOKMessage, red, green, blue, intensity);
	else if (result == H01R0_ERR_WrongColor)
		strcpy( ( char * ) pcWriteBuffer, ( char * ) pcWrongColorMessage);
	else if (result == H01R0_ERR_WrongIntensity)
		strcpy( ( char * ) pcWriteBuffer, ( char * ) pcWrongIntensityMessage);
	

	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}

/*-----------------------------------------------------------*/

portBASE_TYPE toggleCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	Module_Status result = H01R0_OK;
	
	int8_t *pcParameterString1; portBASE_TYPE xParameterStringLength1 = 0; 
	uint8_t intensity = 0;
	static const int8_t *pcOK1Message = ( int8_t * ) "RGB LED is on at intensity %d%%\r\n";
	static const int8_t *pcOK0Message = ( int8_t * ) "RGB LED is off\r\n";
	static const int8_t *pcWrongIntensityMessage = ( int8_t * ) "Wrong intensity!\n\r";
	
	/* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );
	
	/* Obtain the 1st parameter string. */
	pcParameterString1 = ( int8_t * ) FreeRTOS_CLIGetParameter
								(
									pcCommandString,		/* The command string itself. */
									1,						/* Return the first parameter. */
									&xParameterStringLength1	/* Store the parameter string length. */
								);
	intensity = ( uint8_t ) atol( ( char * ) pcParameterString1 );
	
	result = RGB_LED_toggle(intensity);	
	
	/* Respond to the command */
	if ( (result == H01R0_OK) && RGB_LED_State)
		sprintf( ( char * ) pcWriteBuffer, ( char * ) pcOK1Message, intensity);
	else if ( (result == H01R0_OK) && !RGB_LED_State)
		sprintf( ( char * ) pcWriteBuffer, ( char * ) pcOK0Message, intensity);
	else if (result == H01R0_ERR_WrongIntensity)
		strcpy( ( char * ) pcWriteBuffer, ( char * ) pcWrongIntensityMessage);
	
	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}

/*-----------------------------------------------------------*/

portBASE_TYPE pulseColorCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	Module_Status result = H01R0_OK;
	uint8_t color = 0; uint32_t period = 0, dc = 0; int32_t repeat = 0; char par[15] = {0};
	static int8_t *pcParameterString1, *pcParameterString2, *pcParameterString3, *pcParameterString4; 
	portBASE_TYPE xParameterStringLength1 = 0, xParameterStringLength2 = 0;
	portBASE_TYPE xParameterStringLength3 = 0, xParameterStringLength4 = 0;
	
	static const int8_t *pcMessage = ( int8_t * ) "A %s pulse with period %d ms and duty cycle %d ms is generated %d times\n\r";
	static const int8_t *pcMessageInf = ( int8_t * ) "A %s pulse with period %d ms and duty cycle %d ms is generated periodically\n\r";
	
	/* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );
	
	/* Obtain the 1st parameter string. */
	pcParameterString1 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 1, &xParameterStringLength1);
	/* Read the color value. */
	if (!strncmp((const char *)pcParameterString1, "black", xParameterStringLength1))
		color = BLACK;
	else if (!strncmp(( const char *)pcParameterString1, "white", xParameterStringLength1))
		color = WHITE;
	else if (!strncmp((const char *)pcParameterString1, "red", xParameterStringLength1))
		color = RED;
	else if (!strncmp((const char *) pcParameterString1, "blue", xParameterStringLength1))
		color = BLUE;
	else if (!strncmp((const char *) pcParameterString1, "yellow", xParameterStringLength1))
		color = YELLOW;
	else if (!strncmp((const char *) pcParameterString1, "cyan", xParameterStringLength1))
		color = CYAN;
	else if (!strncmp((const char *) pcParameterString1, "magenta", xParameterStringLength1))
		color = MAGENTA;
	else if (!strncmp((const char *) pcParameterString1, "green", xParameterStringLength1))
		color = GREEN;
	
	/* Obtain the 2nd parameter string. */
	pcParameterString2 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 2, &xParameterStringLength2);
	period = ( uint32_t ) atol( ( char * ) pcParameterString2 );
	
	/* Obtain the 3rd parameter string. */
	pcParameterString3 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 3, &xParameterStringLength3);
	dc = ( uint32_t ) atol( ( char * ) pcParameterString3 );
	
	/* Obtain the 4th parameter string. */
	pcParameterString4 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 4, &xParameterStringLength4);
	if (!strcmp( ( char * ) pcParameterString4, "inf"))
		repeat = -1;
	else
		repeat = ( int32_t ) atol( ( char * ) pcParameterString4 );
	
	result = RGB_LED_pulseColor(color, period, dc, repeat);
	
	/* Respond to the command */
	if (result == H01R0_OK) 
	{
		/* Isolate first parameter string */
		strncpy(par, ( char * ) pcParameterString1, xParameterStringLength1);
		if (repeat == -1)
			sprintf( ( char * ) pcWriteBuffer, ( char * ) pcMessageInf, par, period, dc);
		else
			sprintf( ( char * ) pcWriteBuffer, ( char * ) pcMessage, par, period, dc, repeat);
	}

	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}

/*-----------------------------------------------------------*/

portBASE_TYPE pulseRGBCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	Module_Status result = H01R0_OK;
	uint8_t red = 0; uint8_t green = 0; uint8_t blue = 0; uint32_t period = 0, dc = 0; int32_t repeat = 0;
	static int8_t *pcParameterString1, *pcParameterString2, *pcParameterString3, *pcParameterString4; 
	static int8_t *pcParameterString5, *pcParameterString6;
	portBASE_TYPE xParameterStringLength1 = 0, xParameterStringLength2 = 0, xParameterStringLength3 = 0;
	portBASE_TYPE xParameterStringLength4 = 0, xParameterStringLength5 = 0, xParameterStringLength6 = 0;
	
	static const int8_t *pcMessage = ( int8_t * ) "A (%d, %d, %d) RGB pulse with period %d ms and duty cycle %d ms is generated %d times\n\r";
	static const int8_t *pcMessageInf = ( int8_t * ) "A (%d, %d, %d) RGB pulse with period %d ms and duty cycle %d ms is generated periodically\n\r";
	
	/* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );
	
	/* Obtain the 1st parameter string. */
	pcParameterString1 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 1, &xParameterStringLength1);
	red = ( uint8_t ) atol( ( char * ) pcParameterString1 );
	
	/* Obtain the 2nd parameter string. */
	pcParameterString2 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 2, &xParameterStringLength2);
	green = ( uint8_t ) atol( ( char * ) pcParameterString2 );
	
	/* Obtain the 3rd parameter string. */
	pcParameterString3 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 3, &xParameterStringLength3);
	blue = ( uint8_t ) atol( ( char * ) pcParameterString3 );
	
	/* Obtain the 4th parameter string. */
	pcParameterString4 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 4, &xParameterStringLength4);
	period = ( uint32_t ) atol( ( char * ) pcParameterString4 );
	
	/* Obtain the 5th parameter string. */
	pcParameterString5 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 5, &xParameterStringLength5);
	dc = ( uint32_t ) atol( ( char * ) pcParameterString5 );
	
	/* Obtain the 6th parameter string. */
	pcParameterString6 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 6, &xParameterStringLength6);
	if (!strcmp( ( char * ) pcParameterString6, "inf"))
		repeat = -1;
	else
		repeat = ( int32_t ) atol( ( char * ) pcParameterString6 );
	
	result = RGB_LED_pulseRGB(red, green, blue, period, dc, repeat);
	
	/* Respond to the command */
	if (result == H01R0_OK) 
	{
		if (repeat == -1)
			sprintf( ( char * ) pcWriteBuffer, ( char * ) pcMessageInf, red, green, blue, period, dc);
		else
			sprintf( ( char * ) pcWriteBuffer, ( char * ) pcMessage, red, green, blue, period, dc, repeat);
	}

	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}

/*-----------------------------------------------------------*/

portBASE_TYPE sweepCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	Module_Status result = H01R0_OK;
	uint8_t mode = 0; uint32_t period = 0; int32_t repeat = 0; char par[15] = {0};
	static int8_t *pcParameterString1, *pcParameterString2, *pcParameterString3; 
	portBASE_TYPE xParameterStringLength1 = 0, xParameterStringLength2 = 0, xParameterStringLength3 = 0;
	
	static const int8_t *pcMessage = ( int8_t * ) "The RGB LED performs a %s color sweep with period %d ms. The sweep is repeated %d times\n\r";
	static const int8_t *pcMessageInf = ( int8_t * ) "The RGB LED performs a %s color sweep with period %d ms. The sweep is repeated periodically\n\r";
	
	/* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );
	
	/* Obtain the 1st parameter string. */
	pcParameterString1 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 1, &xParameterStringLength1);
	if (!strncmp( ( char * ) pcParameterString1, "basic", xParameterStringLength1))
		mode = RGB_SWEEP_BASIC;
	else if (!strncmp( ( char * ) pcParameterString1, "fine", xParameterStringLength1))
		mode = RGB_SWEEP_FINE;
	
	/* Obtain the 2nd parameter string. */
	pcParameterString2 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 2, &xParameterStringLength2);
	period = ( uint32_t ) atol( ( char * ) pcParameterString2 );
	
	/* Obtain the 3rd parameter string. */
	pcParameterString3 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 3, &xParameterStringLength3);
	if (!strcmp( ( char * ) pcParameterString3, "inf"))
		repeat = -1;
	else
		repeat = ( int32_t ) atol( ( char * ) pcParameterString3 );
	
	result = RGB_LED_sweep(mode, period, repeat);
	
	/* Respond to the command */
	if (result == H01R0_OK) 
	{	
		/* Isolate first parameter string */
		strncpy(par, ( char * ) pcParameterString1, xParameterStringLength1); 
		if (repeat == -1)
			sprintf( ( char * ) pcWriteBuffer, ( char * ) pcMessageInf, par, period);
		else
			sprintf( ( char * ) pcWriteBuffer, ( char * ) pcMessage, par, period, repeat);
	}
	
	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}

/*-----------------------------------------------------------*/

portBASE_TYPE dimCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	Module_Status result = H01R0_OK;
	uint8_t color = 0, mode = 0; uint32_t period = 0, wait = 0; int32_t repeat = 0;
	static int8_t *pcParameterString1, *pcParameterString2, *pcParameterString3, *pcParameterString4 , *pcParameterString5; 
	portBASE_TYPE xParameterStringLength1 = 0, xParameterStringLength2 = 0, xParameterStringLength3 = 0; 
	portBASE_TYPE xParameterStringLength4 = 0, xParameterStringLength5 = 0;
	char par1[15] = {0}, par2[15] = {0};
	
	static const int8_t *pcMessage = ( int8_t * ) "The RGB LED dims a %s color with period %d ms and wait time %d ms. The dim mode is %s and the dim cycle is repeated %d times\n\r";
	static const int8_t *pcMessageInf = ( int8_t * ) "The RGB LED dims a %s color with period %d ms and wait time %d ms. The dim mode is %s and the dim cycle is repeated periodically\n\r";
	
	/* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );
	
	/* Obtain the 1st parameter string. */
	pcParameterString1 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 1, &xParameterStringLength1);
	/* Read the color value. */
	if (!strncmp((const char *)pcParameterString1, "black", xParameterStringLength1))
		color = BLACK;
	else if (!strncmp(( const char *)pcParameterString1, "white", xParameterStringLength1))
		color = WHITE;
	else if (!strncmp((const char *)pcParameterString1, "red", xParameterStringLength1))
		color = RED;
	else if (!strncmp((const char *) pcParameterString1, "blue", xParameterStringLength1))
		color = BLUE;
	else if (!strncmp((const char *) pcParameterString1, "yellow", xParameterStringLength1))
		color = YELLOW;
	else if (!strncmp((const char *) pcParameterString1, "cyan", xParameterStringLength1))
		color = CYAN;
	else if (!strncmp((const char *) pcParameterString1, "magenta", xParameterStringLength1))
		color = MAGENTA;
	else if (!strncmp((const char *) pcParameterString1, "green", xParameterStringLength1))
		color = GREEN;
	
	/* Obtain the 2nd parameter string. */
	pcParameterString2 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 2, &xParameterStringLength2);
	if (!strncmp( ( char * ) pcParameterString2, "up", xParameterStringLength2))
		mode = RGB_DIM_UP;
	else if (!strncmp( ( char * ) pcParameterString2, "upwait", xParameterStringLength2))
		mode = RGB_DIM_UP_WAIT;
	else if (!strncmp( ( char * ) pcParameterString2, "down", xParameterStringLength2))
		mode = RGB_DIM_DOWN;
	else if (!strncmp( ( char * ) pcParameterString2, "downwait", xParameterStringLength2))
		mode = RGB_DIM_DOWN_WAIT;
	else if (!strncmp( ( char * ) pcParameterString2, "updown", xParameterStringLength2))
		mode = RGB_DIM_UP_DOWN;
	else if (!strncmp( ( char * ) pcParameterString2, "downup", xParameterStringLength2))
		mode = RGB_DIM_DOWN_UP;
	else if (!strncmp( ( char * ) pcParameterString2, "updownwait", xParameterStringLength2))
		mode = RGB_DIM_UP_DOWN_WAIT;
	else if (!strncmp( ( char * ) pcParameterString2, "downupwait", xParameterStringLength2))
		mode = RGB_DIM_DOWN_UP_WAIT;
	
	/* Obtain the 3rd parameter string. */
	pcParameterString3 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 3, &xParameterStringLength3);
	period = ( uint32_t ) atol( ( char * ) pcParameterString3 );

	/* Obtain the 4th parameter string. */
	pcParameterString4 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 4, &xParameterStringLength4);
	wait = ( uint32_t ) atol( ( char * ) pcParameterString4 );
	
	/* Obtain the 5th parameter string. */
	pcParameterString5 = ( int8_t * ) FreeRTOS_CLIGetParameter (pcCommandString, 5, &xParameterStringLength5);
	if (!strcmp( ( char * ) pcParameterString5, "inf"))
		repeat = -1;
	else
		repeat = ( int32_t ) atol( ( char * ) pcParameterString5 );
	
	result = RGB_LED_dim(color, mode, period, wait, repeat);
	
	/* Respond to the command */
	if (result == H01R0_OK) 
	{	
		/* Isolate first and second parameter strings. */
		strncpy(par1, ( char * ) pcParameterString1, xParameterStringLength1);
		strncpy(par2, ( char * ) pcParameterString2, xParameterStringLength2);
		if (repeat == -1)
			sprintf( ( char * ) pcWriteBuffer, ( char * ) pcMessageInf, par1, period, wait, par2);
		else
			sprintf( ( char * ) pcWriteBuffer, ( char * ) pcMessage, par1, period, wait, par2, repeat);
	}
	
	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}

/*-----------------------------------------------------------*/


/************************ (C) COPYRIGHT HEXABITZ *****END OF FILE****/
