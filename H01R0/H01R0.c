/*
 BitzOS (BOS) V0.2.7 - Copyright (C) 2017-2022 Hexabitz
 All rights reserved

 File Name     : H01R0.c
 Description   : Source code for module H01R0.
 	 	 	 	 (Description_of_module)

(Description of Special module peripheral configuration):
>>
>>
>>

 */

/* Includes ------------------------------------------------------------------*/
#include "BOS.h"
#include "H01R0_inputs.h"
/* Define UART variables */
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart6;

/* Exported variables */
extern FLASH_ProcessTypeDef pFlash;
extern uint8_t numOfRecordedSnippets;

/* Module exported parameters ------------------------------------------------*/
module_param_t modParam[NUM_MODULE_PARAMS] ={{.paramPtr = NULL, .paramFormat =FMT_FLOAT, .paramName =""}};

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
void MX_TIM1_Init(void);
void MX_TIM2_Init(void);
//TIM_HandleTypeDef htim16;
uint8_t globalRed =0, globalGreen =0, globalBlue =0;
uint8_t RGB_LED_State =0, rgbLedMode =0, rgbColor =0, rgbRed =0, rgbGreen =0, rgbBlue =0;
uint32_t rgbPeriod =0, rgbDC =0;
int16_t rgbCount =0;
uint8_t color =0, intensity_LED =0, intensity_RGB =0, mode =0;
TaskHandle_t RGBledTaskHandle = NULL;
/* Private function prototypes -----------------------------------------------*/
void ExecuteMonitor(void);

void RGBledTask(void *argument);
void RGBpulse(uint8_t mode);
void RGBsweepBasic(void);
void RGBsweepFine(void);
void RGBdim(uint8_t mode);
/* Create CLI commands --------------------------------------------------------*/

/*-----------------------------------------------------------*/

/* -----------------------------------------------------------------------
 |												 Private Functions	 														|
 ----------------------------------------------------------------------- 
 */

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow : 
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 48000000
 *            HCLK(Hz)                       = 48000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 1
 *            HSE Frequency(Hz)              = 8000000
 *            PREDIV                         = 1
 *            PLLMUL                         = 6
 *            Flash Latency(WS)              = 1
 * @param  None
 * @retval None
 */
void SystemClock_Config(void){
	  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	  /** Configure the main internal regulator output voltage
	  */
	  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
	  /** Initializes the RCC Oscillators according to the specified parameters
	  * in the RCC_OscInitTypeDef structure.
	  */
	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
	  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
	  RCC_OscInitStruct.PLL.PLLN = 12;
	  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	 HAL_RCC_OscConfig(&RCC_OscInitStruct);

	  /** Initializes the CPU, AHB and APB buses clocks
	  */
	  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	                              |RCC_CLOCKTYPE_PCLK1;
	  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	 HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

	  /** Initializes the peripherals clocks
	  */
	  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USART2;
	  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
	  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
	  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_TIM1;
	    PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLKSOURCE_PCLK1;
	  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
		__HAL_RCC_PWR_CLK_ENABLE();
		HAL_PWR_EnableBkUpAccess();
		__HAL_RCC_TIM1_CLK_ENABLE();
		  __HAL_RCC_TIM2_CLK_ENABLE();

		HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

		HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

		__SYSCFG_CLK_ENABLE()
		;
	  HAL_NVIC_SetPriority(SysTick_IRQn,0,0);
	
}

/*-----------------------------------------------------------*/


/* --- Save array topology and Command Snippets in Flash RO --- 
 */
uint8_t SaveToRO(void){
	BOS_Status result =BOS_OK;
	HAL_StatusTypeDef FlashStatus =HAL_OK;
	uint16_t add =2, temp =0;
	uint8_t snipBuffer[sizeof(snippet_t) + 1] ={0};
	
	HAL_FLASH_Unlock();
	
	/* Erase RO area */
	FLASH_PageErase(FLASH_BANK_1,RO_START_ADDRESS);
	//TOBECHECKED
	FlashStatus =FLASH_WaitForLastOperation((uint32_t ) HAL_FLASH_TIMEOUT_VALUE);
	if(FlashStatus != HAL_OK){
		return pFlash.ErrorCode;
	}
	else{
		/* Operation is completed, disable the PER Bit */
		CLEAR_BIT(FLASH->CR,FLASH_CR_PER);
	}
	
	/* Save number of modules and myID */
	if(myID){
		temp =(uint16_t )(N << 8) + myID;
		//HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,RO_START_ADDRESS,temp);
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,RO_START_ADDRESS,temp);
		//TOBECHECKED
		FlashStatus =FLASH_WaitForLastOperation((uint32_t ) HAL_FLASH_TIMEOUT_VALUE);
		if(FlashStatus != HAL_OK){
			return pFlash.ErrorCode;
		}
		else{
			/* If the program operation is completed, disable the PG Bit */
			CLEAR_BIT(FLASH->CR,FLASH_CR_PG);
		}
		
		/* Save topology */
		for(uint8_t i =1; i <= N; i++){
			for(uint8_t j =0; j <= MaxNumOfPorts; j++){
				if(array[i - 1][0]){
					HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,              //HALFWORD
						//TOBECHECKED
					RO_START_ADDRESS + add,array[i - 1][j]);
					add +=2;
					FlashStatus =FLASH_WaitForLastOperation((uint32_t ) HAL_FLASH_TIMEOUT_VALUE);
					if(FlashStatus != HAL_OK){
						return pFlash.ErrorCode;
					}
					else{
						/* If the program operation is completed, disable the PG Bit */
						CLEAR_BIT(FLASH->CR,FLASH_CR_PG);
					}
				}
			}
		}
	}
	
	// Save Command Snippets
	int currentAdd = RO_MID_ADDRESS;
	for(uint8_t s =0; s < numOfRecordedSnippets; s++){
		if(snippets[s].cond.conditionType){
			snipBuffer[0] =0xFE;		// A marker to separate Snippets
			memcpy((uint8_t* )&snipBuffer[1],(uint8_t* )&snippets[s],sizeof(snippet_t));
			// Copy the snippet struct buffer (20 x numOfRecordedSnippets). Note this is assuming sizeof(snippet_t) is even.
			for(uint8_t j =0; j < (sizeof(snippet_t) / 2); j++){
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,currentAdd,*(uint16_t* )&snipBuffer[j * 2]);
				//HALFWORD
				//TOBECHECKED
				FlashStatus =FLASH_WaitForLastOperation((uint32_t ) HAL_FLASH_TIMEOUT_VALUE);
				if(FlashStatus != HAL_OK){
					return pFlash.ErrorCode;
				}
				else{
					/* If the program operation is completed, disable the PG Bit */
					CLEAR_BIT(FLASH->CR,FLASH_CR_PG);
					currentAdd +=2;
				}
			}
			// Copy the snippet commands buffer. Always an even number. Note the string termination char might be skipped
			for(uint8_t j =0; j < ((strlen(snippets[s].cmd) + 1) / 2); j++){
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,currentAdd,*(uint16_t* )(snippets[s].cmd + j * 2));
				//HALFWORD
				//TOBECHECKED
				FlashStatus =FLASH_WaitForLastOperation((uint32_t ) HAL_FLASH_TIMEOUT_VALUE);
				if(FlashStatus != HAL_OK){
					return pFlash.ErrorCode;
				}
				else{
					/* If the program operation is completed, disable the PG Bit */
					CLEAR_BIT(FLASH->CR,FLASH_CR_PG);
					currentAdd +=2;
				}
			}
		}
	}
	
	HAL_FLASH_Lock();
	
	return result;
}

/* --- Clear array topology in SRAM and Flash RO --- 
 */
uint8_t ClearROtopology(void){
	// Clear the array 
	memset(array,0,sizeof(array));
	N =1;
	myID =0;
	
	return SaveToRO();
}
/*-----------------------------------------------------------*/

/* --- Trigger ST factory bootloader update for a remote module.
 */
void remoteBootloaderUpdate(uint8_t src,uint8_t dst,uint8_t inport,uint8_t outport){

	uint8_t myOutport =0, lastModule =0;
	int8_t *pcOutputString;

	/* 1. Get route to destination module */
	myOutport =FindRoute(myID,dst);
	if(outport && dst == myID){ /* This is a 'via port' update and I'm the last module */
		myOutport =outport;
		lastModule =myID;
	}
	else if(outport == 0){ /* This is a remote update */
		if(NumberOfHops(dst)== 1)
		lastModule = myID;
		else
		lastModule = route[NumberOfHops(dst)-1]; /* previous module = route[Number of hops - 1] */
	}

	/* 2. If this is the source of the message, show status on the CLI */
	if(src == myID){
		/* Obtain the address of the output buffer.  Note there is no mutual
		 exclusion on this buffer as it is assumed only one command console
		 interface will be used at any one time. */
		pcOutputString =FreeRTOS_CLIGetOutputBuffer();

		if(outport == 0)		// This is a remote module update
			sprintf((char* )pcOutputString,pcRemoteBootloaderUpdateMessage,dst);
		else
			// This is a 'via port' remote update
			sprintf((char* )pcOutputString,pcRemoteBootloaderUpdateViaPortMessage,dst,outport);

		strcat((char* )pcOutputString,pcRemoteBootloaderUpdateWarningMessage);
		writePxITMutex(inport,(char* )pcOutputString,strlen((char* )pcOutputString),cmd50ms);
		Delay_ms(100);
	}

	/* 3. Setup my inport and outport for bootloader update */
	SetupPortForRemoteBootloaderUpdate(inport);
	SetupPortForRemoteBootloaderUpdate(myOutport);


	/* 5. Build a DMA stream between my inport and outport */
	StartScastDMAStream(inport,myID,myOutport,myID,BIDIRECTIONAL,0xFFFFFFFF,0xFFFFFFFF,false);
}

/*-----------------------------------------------------------*/

/* --- Setup a port for remote ST factory bootloader update:
 - Set baudrate to 57600
 - Enable even parity
 - Set datasize to 9 bits
 */
void SetupPortForRemoteBootloaderUpdate(uint8_t port){
	UART_HandleTypeDef *huart =GetUart(port);

	huart->Init.BaudRate =57600;
	huart->Init.Parity = UART_PARITY_EVEN;
	huart->Init.WordLength = UART_WORDLENGTH_9B;
	HAL_UART_Init(huart);

	/* The CLI port RXNE interrupt might be disabled so enable here again to be sure */
	__HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);
}

/* --- H01R0 module initialization.
 */
void Module_Peripheral_Init(void){
	 __HAL_RCC_GPIOB_CLK_ENABLE();
	 __HAL_RCC_GPIOA_CLK_ENABLE();
	/* Array ports */
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	MX_USART3_UART_Init();
	MX_USART4_UART_Init();
	MX_USART5_UART_Init();
	MX_USART6_UART_Init();
	MX_TIM1_Init();
	MX_TIM2_Init();

	/* Create module special task (if needed) */
	if(RGBledTaskHandle == NULL)
			xTaskCreate(RGBledTask,(const char* ) "RGBledTask",configMINIMAL_STACK_SIZE,NULL,osPriorityNormal - osPriorityIdle,&RGBledTaskHandle);
}

/*-----------------------------------------------------------*/
/* --- H01R0 message processing task.
 */
Module_Status Module_MessagingTask(uint16_t code,uint8_t port,uint8_t src,uint8_t dst,uint8_t shift){
	Module_Status result =H01R0_OK;


	switch(code){

		default:
			result =H01R0_ERR_UnknownMessage;
			break;
	}
	
	return result;
}
/* --- Get the port for a given UART. 
 */
uint8_t GetPort(UART_HandleTypeDef *huart){

	if(huart->Instance == USART4)
		return P1;
	else if(huart->Instance == USART2)
		return P2;
	else if(huart->Instance == USART3)
		return P3;
	else if(huart->Instance == USART1)
		return P4;
	else if(huart->Instance == USART5)
		return P5;
	else if(huart->Instance == USART6)
		return P6;
	
	return 0;
}

/*-----------------------------------------------------------*/
/* RGBledTask function */
void RGBledTask(void *argument){

	/* Infinite loop */
	for(;;){
		/* Switch RGB LED according to its mode */
		switch(rgbLedMode){
			case RGB_PULSE_RGB:
				RGBpulse(rgbLedMode);
				break;

			case RGB_PULSE_COLOR:
				RGBpulse(rgbLedMode);
				break;

			case RGB_SWEEP_BASIC:
				RGBsweepBasic();
				break;

			case RGB_SWEEP_FINE:
				RGBsweepFine();
				break;

			case RGB_DIM_UP:
				RGBdim(rgbLedMode);
				break;

			case RGB_DIM_UP_WAIT:
				RGBdim(rgbLedMode);
				break;

			case RGB_DIM_DOWN:
				RGBdim(rgbLedMode);
				break;

			case RGB_DIM_DOWN_WAIT:
				RGBdim(rgbLedMode);
				break;

			case RGB_DIM_UP_DOWN:
				RGBdim(rgbLedMode);
				break;

			case RGB_DIM_DOWN_UP:
				RGBdim(rgbLedMode);
				break;

			case RGB_DIM_UP_DOWN_WAIT:
				RGBdim(rgbLedMode);
				break;

			case RGB_DIM_DOWN_UP_WAIT:
				RGBdim(rgbLedMode);
				break;

			default:
				osDelay(10);
				break;
		}

		taskYIELD();
	}
}
/* --- Register this module CLI Commands
 */
void RegisterModuleCLICommands(void){

}

/*-----------------------------------------------------------*/


/* Module special task function (if needed) */
//void Module_Special_Task(void *argument){
//
//	/* Infinite loop */
//	uint8_t cases; // Test variable.
//	for(;;){
//		/*  */
//		switch(cases){
//
//
//			default:
//				osDelay(10);
//				break;
//		}
//
//		taskYIELD();
//	}
//
//}


/*-----------------------------------------------------------*/



/*-----------------------------------------------------------*/

/* -----------------------------------------------------------------------
 |								  APIs							          | 																 	|
/* -----------------------------------------------------------------------
 */
Module_Status RGB_LED_on(uint8_t intensity){
	Module_Status result =H01R0_OK;

	if(intensity == 0){
		htim1.Instance->CCR2 =0;
		htim2.Instance->CCR3 =0;
		htim1.Instance->CCR4 =0;

		RGB_LED_State =0;

		return H01R0_OK;
	}
	else if(intensity <= 100){
		result =startPWM(0,255,0,intensity);

		if(result == H01R0_OK)
			RGB_LED_State =1;

		return result;
	}
	else
		return H01R0_ERR_WrongIntensity;

}
Module_Status RGB_LED_off(void){
	if(HAL_TIM_Base_Stop(&htim1) != HAL_OK)
		return H01R0_ERROR;
	if(HAL_TIM_Base_Stop(&htim2) != HAL_OK)
			return H01R0_ERROR;

	htim1.Instance->CCR2 =0;
	htim2.Instance->CCR3 =0;
	htim1.Instance->CCR4 =0;

	RGB_LED_State =0;
	rgbLedMode =0;

	return H01R0_OK;
}
/* --- Set LED color from a predefined color list (continuously)
 using PWM intensity modulation.
 */
Module_Status RGB_LED_setColor(uint8_t color,uint8_t intensity){
	Module_Status result =H01R0_OK;

	if(!intensity)
		return RGB_LED_on(0);
	else if(intensity > 100)
		return H01R0_ERR_WrongIntensity;
	else{
		switch(color){
			case BLACK:
				result =RGB_LED_off();
				break;
			case WHITE:
				result =RGB_LED_on(intensity);
				break;
			case RED:
				result =RGB_LED_setRGB(0,0,255,intensity);
				break;
			case BLUE:
				result =RGB_LED_setRGB(255,0,0,intensity);
				break;
			case YELLOW:
				result =RGB_LED_setRGB(0,255,255,intensity);
				break;
			case CYAN:
				result =RGB_LED_setRGB(255,255,0,intensity);
				break;
			case MAGENTA:
				result =RGB_LED_setRGB(0,0,0,intensity);
				break;
			case GREEN:
				result =RGB_LED_setRGB(255,255,255,intensity);
				break;
			default:
				result =H01R0_ERR_WrongColor;
				break;
		}
	}

	return result;
}
/*-----------------------------------------------------------*/
/* --- Set RGB colors on LED (continuously) using PWM intensity modulation.
 */
Module_Status RGB_LED_setRGB(uint8_t red,uint8_t green,uint8_t blue,uint8_t intensity){
	if(intensity == 0)
		return RGB_LED_on(0);
	else if(intensity > 100)
		return H01R0_ERR_WrongIntensity;
	else
		return startPWM(red,green,blue,intensity);
}
/*-----------------------------------------------------------*/
/* --- Load and start red LED PWM ---
 Inputs:
 red Duty cycle of red LED (0-255).
 green Duty cycle of green LED (0-255).
 blue Duty cycle of blue LED (0-255).
 intensity RGB LED intensity (0-100).
 */
Module_Status startPWM(uint8_t red,uint8_t green,uint8_t blue,uint8_t intensity){
	uint32_t period = PWM_TIMER_CLOCK / RGB_PWM_FREQ;

	/* PWM period */
	htim1.Instance->ARR =period - 1;
	htim2.Instance->ARR =period - 1;
	 htim1.Instance->BDTR = 0;
	/* PWM duty cycle */
	htim1.Instance->CCR2 =((float )intensity / 100.0f) * ((float )red / 255.0f) * period;
	htim2.Instance->CCR3 =((float )intensity / 100.0f) * ((float )green / 255.0f) * period;
	htim1.Instance->CCR4 =((float )intensity / 100.0f) * ((float )blue / 255.0f) * period;
if(red!=255){
	if(HAL_TIMEx_PWMN_Start(&htim1,_RGB_RED_TIM_CH) != HAL_OK)
		return H01R0_ERROR;
	if(HAL_TIM_PWM_Start(&htim1,_RGB_RED_TIM_CH) != HAL_OK)
			return H01R0_ERROR;}
if(green!=0){
	if(HAL_TIM_PWM_Start(&htim2,_RGB_GREEN_TIM_CH) != HAL_OK)
		return H01R0_ERROR;}
	if(blue!=255){
	if(HAL_TIMEx_PWMN_Start(&htim1,_RGB_BLUE_TIM_CH) != HAL_OK)
		return H01R0_ERROR;
	if(HAL_TIM_PWM_Start(&htim1,_RGB_BLUE_TIM_CH) != HAL_OK)
				return H01R0_ERROR;}

	return H01R0_OK;
}
/*-----------------------------------------------------------*/

/* --- Pulse the RGB LED ---
 */
void RGBpulse(uint8_t mode){
	uint8_t temp =0;

	if(rgbCount > 0 || rgbCount == -1){
		if(mode == RGB_PULSE_RGB)
			RGB_LED_setRGB(rgbRed,rgbGreen,rgbBlue,100);
		else if(mode == RGB_PULSE_COLOR)
			RGB_LED_setColor(rgbColor,100);
		osDelay(rgbDC);
		temp =rgbLedMode; /* Backup rgbLedMode so that it's not reset */
		RGB_LED_off();
		rgbLedMode =temp;
		osDelay(rgbPeriod - rgbDC);

		if(rgbCount > 0)
			rgbCount--;
	}
	else{
		rgbLedMode =0;
	}
}

/*-----------------------------------------------------------*/

/* --- RGB LED basic color sweep ---
 */
void RGBsweepBasic(void){
	static uint32_t temp;

	temp =rgbPeriod / 6;

	if(rgbCount > 0 || rgbCount == -1){
		RGB_LED_setColor(RED,100);
		osDelay(temp);
		RGB_LED_setColor(YELLOW,100);
		osDelay(temp);
		RGB_LED_setColor(GREEN,100);
		osDelay(temp);
		RGB_LED_setColor(CYAN,100);
		osDelay(temp);
		RGB_LED_setColor(BLUE,100);
		osDelay(temp);
		RGB_LED_setColor(MAGENTA,100);
		osDelay(temp);

		if(rgbCount > 0)
			rgbCount--;
	}
	else{
		RGB_LED_off();
	}
}

/*-----------------------------------------------------------*/

/* --- RGB LED fine color sweep ---
 */
void RGBsweepFine(void){
	static uint32_t temp;

	temp =rgbPeriod / 6;

	if(rgbCount > 0 || rgbCount == -1){
		/* Red */
		for(uint8_t i =0; i < 255; i++){
			RGB_LED_setRGB(255,i,0,100);
			osDelay(ceil(temp / 255));
		}
		/* Yellow */
		for(uint8_t i =255; i > 0; i--){
			RGB_LED_setRGB(i,255,0,100);
			osDelay(ceil(temp / 255));
		}
		/* Green */
		for(uint8_t i =0; i < 255; i++){
			RGB_LED_setRGB(0,255,i,100);
			osDelay(ceil(temp / 255));
		}
		/* Cyan */
		for(uint8_t i =255; i > 0; i--){
			RGB_LED_setRGB(0,i,255,100);
			osDelay(ceil(temp / 255));
		}
		/* Blue */
		for(uint8_t i =0; i < 255; i++){
			RGB_LED_setRGB(i,0,255,100);
			osDelay(ceil(temp / 255));
		}
		/* Magenta */
		for(uint8_t i =255; i > 0; i--){
			RGB_LED_setRGB(255,0,i,100);
			osDelay(ceil(temp / 255));
		}

		if(rgbCount > 0)
			rgbCount--;
	}
	else{
		RGB_LED_off();
	}
}

/*-----------------------------------------------------------*/
/* --- Dim the RGB LED ---
 */
void RGBdim(uint8_t mode){
	uint8_t temp =0;

	if(rgbCount > 0 || rgbCount == -1){
		temp =rgbLedMode; /* Store mode so that it's not reset */
		if(mode == RGB_DIM_UP){
			for(uint8_t i =0; i <= 100; i++){
				RGB_LED_setColor(rgbColor,i);
				osDelay(rgbPeriod / 100);
			}
		}
		else if(mode == RGB_DIM_UP_WAIT){
			for(uint8_t i =0; i <= 100; i++){
				RGB_LED_setColor(rgbColor,i);
				osDelay((rgbPeriod - rgbDC) / 100);
			}
			osDelay(rgbDC);
		}
		else if(mode == RGB_DIM_DOWN){
			for(uint8_t i =101; i > 0; i--){
				RGB_LED_setColor(rgbColor,i - 1);
				osDelay(rgbPeriod / 100);
			}
		}
		else if(mode == RGB_DIM_DOWN_WAIT){
			for(uint8_t i =101; i > 0; i--){
				RGB_LED_setColor(rgbColor,i - 1);
				osDelay((rgbPeriod - rgbDC) / 100);
			}
			osDelay(rgbDC);
		}
		else if(mode == RGB_DIM_UP_DOWN){
			for(uint8_t i =0; i <= 100; i++){
				RGB_LED_setColor(rgbColor,i);
				osDelay(rgbPeriod / 200);
			}
			for(uint8_t i =101; i > 0; i--){
				RGB_LED_setColor(rgbColor,i - 1);
				osDelay(rgbPeriod / 200);
			}
		}
		else if(mode == RGB_DIM_DOWN_UP){
			for(uint8_t i =101; i > 0; i--){
				RGB_LED_setColor(rgbColor,i - 1);
				osDelay(rgbPeriod / 200);
			}
			for(uint8_t i =0; i <= 100; i++){
				RGB_LED_setColor(rgbColor,i);
				osDelay(rgbPeriod / 200);
			}
		}
		else if(mode == RGB_DIM_UP_DOWN_WAIT){
			for(uint8_t i =0; i <= 100; i++){
				RGB_LED_setColor(rgbColor,i);
				osDelay((rgbPeriod - rgbDC) / 200);
			}
			for(uint8_t i =101; i > 0; i--){
				RGB_LED_setColor(rgbColor,i - 1);
				osDelay((rgbPeriod - rgbDC) / 200);
			}
			osDelay(rgbDC);
		}
		else if(mode == RGB_DIM_DOWN_UP_WAIT){
			for(uint8_t i =101; i > 0; i--){
				RGB_LED_setColor(rgbColor,i - 1);
				osDelay((rgbPeriod - rgbDC) / 200);
			}
			for(uint8_t i =0; i <= 100; i++){
				RGB_LED_setColor(rgbColor,i);
				osDelay((rgbPeriod - rgbDC) / 200);
			}
			osDelay(rgbDC);
			rgbLedMode =temp;
		}

		if(rgbCount > 0)
			rgbCount--;
	}
	else{
		rgbLedMode =0;
	}
}
/* -----------------------------------------------------------------------
 |								Commands							      |
   -----------------------------------------------------------------------
 */



/*-----------------------------------------------------------*/

/************************ (C) COPYRIGHT HEXABITZ *****END OF FILE****/
