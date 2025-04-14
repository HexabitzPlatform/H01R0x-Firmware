/*
 BitzOS (BOS) V0.4.0 - Copyright (C) 2017-2025 Hexabitz
 All rights reserved

 File Name     : H01R0.c
 Description   : Source code for module H01R0.
 (Description_of_module)

 (Description of Special module peripheral configuration):
 >>
 >>
 >>

 */

/* Includes ****************************************************************/
#include "BOS.h"
#include "H01R0_inputs.h"

/* Exported Typedef ********************************************************/
/* Define UART variables */
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart6;

/* RGB Timers variables */
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

TaskHandle_t RGBledTaskHandle = NULL;

/* Private Variables *******************************************************/
uint8_t rgbColor = 0;
uint8_t rgbLedMode = 0;
uint8_t rgbLedState = 0;
uint8_t rgbRed = 0, rgbGreen = 0, rgbBlue = 0;
int16_t rgbCount = 0;
uint32_t rgbDC = 0;
uint32_t rgbPeriod = 0;

/* Module Parameters */
ModuleParam_t ModuleParam[NUM_MODULE_PARAMS] = { 0 };

/* Private Function Prototypes *********************************************/
void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void MX_TIM4_Init(void);
void Module_Peripheral_Init(void);
uint8_t ClearROtopology(void);
Module_Status Module_MessagingTask(uint16_t code, uint8_t port, uint8_t src, uint8_t dst, uint8_t shift);

/* Local Function Prototypes ***********************************************/
void RGBdim(uint8_t mode);
void RGBpulse(uint8_t mode);
void RGBledTask(void *argument);
void RGBsweepFine(void);
void RGBsweepBasic(void);
Module_Status startPWM(uint8_t red, uint8_t green, uint8_t blue, uint8_t intensity);

/* Create CLI commands *****************************************************/
portBASE_TYPE demoCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString);
portBASE_TYPE onCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString);
portBASE_TYPE offCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString);
portBASE_TYPE colorCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString);
portBASE_TYPE RGBCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString);
portBASE_TYPE toggleCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString);
portBASE_TYPE pulseColorCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString);
portBASE_TYPE pulseRGBCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString);
portBASE_TYPE sweepCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString);
portBASE_TYPE dimCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString);

/* CLI command structure ***************************************************/
/* CLI command structure : demo */
const CLI_Command_Definition_t demoCommandDefinition = { (const int8_t*) "demo", /* The command string to type. */
(const int8_t*) "demo:\r\n Run a demo program to test module functionality\r\n\r\n", demoCommand, /* The function to run. */
0 /* No parameters are expected. */
};

/***************************************************************************/
/* CLI command structure : on */
const CLI_Command_Definition_t onCommandDefinition = { (const int8_t*) "on", /* The command string to type. */
(const int8_t*) "on:\r\n Turn RGB LED on (white color) at a specific intensity (0-100%) (1st par.)\r\n\r\n", onCommand, /* The function to run. */
1 /* One parameter is expected. */
};

/***************************************************************************/
/* CLI command structure : off */
const CLI_Command_Definition_t offCommandDefinition = { (const int8_t*) "off", /* The command string to type. */
(const int8_t*) "off:\r\n Turn RGB LED off\r\n\r\n", offCommand, /* The function to run. */
0 /* No parameters are expected. */
};

/***************************************************************************/
/* CLI command structure : color */
const CLI_Command_Definition_t colorCommandDefinition =
		{ (const int8_t*) "color", /* The command string to type. */
				(const int8_t*) "color:\r\n Set RGB LED color (1st par.) at a specific intensity (0-100%) (2nd par.)\n\rRegistered colors are:\
					\r\nblack, white, red, blue, green, yellow, cyan, and magenta \r\n\r\n",
				colorCommand, /* The function to run. */
				2 /* Two parameters are expected. */
		};

/***************************************************************************/
/* CLI command structure : RGB */
const CLI_Command_Definition_t RGBCommandDefinition =
		{ (const int8_t*) "rgb", /* The command string to type. */
				(const int8_t*) "RGB:\r\n Set RGB LED red (1st par.), green (2nd par.), and blue (3rd par.) values (0-255) at a specific intensity (0-100%) (4th par.)\r\n\r\n",
				RGBCommand, /* The function to run. */
				4 /* Four parameters are expected. */
		};

/***************************************************************************/
/* CLI command structure : toggle */
const CLI_Command_Definition_t toggleCommandDefinition = { (const int8_t*) "toggle", /* The command string to type. */
(const int8_t*) "toggle:\r\n Toggle RGB LED (white color) at a specific intensity (0-100%) (1st par.)\r\n\r\n",
		toggleCommand, /* The function to run. */
		1 /* One parameter is expected. */
};

/***************************************************************************/
/* CLI command structure : pulseColor */
const CLI_Command_Definition_t pulseColorCommandDefinition =
		{ (const int8_t*) "pulsecolor", /* The command string to type. */
				(const int8_t*) "pulseColor:\r\n Send a pulse on RGB LED using a specific color (1st par.), pulse period (ms) (2nd par.), pulse duty cycle (ms) (3rd par.) \
					 and pulse repeat times (4th par.) (type 'inf' for periodic signal)\r\n\r\n",
				pulseColorCommand, /* The function to run. */
				4 /* Four parameters are expected. */
		};

/***************************************************************************/
/* CLI command structure : pulseRGB */
const CLI_Command_Definition_t pulseRGBCommandDefinition =
		{ (const int8_t*) "pulsergb", /* The command string to type. */
				(const int8_t*) "pulseRGB:\r\n Send a pulse on RGB LED using RGB values (1st, 2nd and 3rd par.) (0-255), pulse period (ms) (4th par.), pulse duty cycle (ms) (5th par.) \
					 and pulse repeat times (6th par.) (type 'inf' for periodic signal)\r\n\r\n",
				pulseRGBCommand, /* The function to run. */
				6 /* Six parameters are expected. */
		};

/***************************************************************************/
/* CLI command structure : sweep */
const CLI_Command_Definition_t sweepCommandDefinition =
		{ (const int8_t*) "sweep", /* The command string to type. */
				(const int8_t*) "sweep:\r\n Perform color sweep on RGB LED using a specific sweep mode ('basic': sweep basic color only, 'fine': sweep all colors) (1st par.), sweep period (ms) (2nd par.) \
					 and sweep repeat times (3rd par.) (type 'inf' for periodic signal)\r\n\r\n",
				sweepCommand, /* The function to run. */
				3 /* Three parameters are expected. */
		};

/***************************************************************************/
/* CLI command structure : dim */
const CLI_Command_Definition_t dimCommandDefinition =
		{ (const int8_t*) "dim", /* The command string to type. */
				(const int8_t*) "dim:\r\n Dim a specific color (1st par.) on RGB LED using a specific dim mode ('up', 'upwait', 'down', 'downwait', 'updown', 'downup', 'updownwait', 'downupwait') (2nd par.), \
					 sweep period (ms) (3rd par.), wait time (ms) (4th par.) and dim repeat times (5th par.) (type 'inf' for periodic signal)\r\n\r\n",
				dimCommand, /* The function to run. */
				5 /* Five parameters are expected. */
		};

/***************************************************************************/
/************************ Private function Definitions *********************/
/***************************************************************************/
/* @brief  System Clock Configuration
 *         This function configures the system clock as follows:
 *            - System Clock source            = PLL (HSE)
 *            - SYSCLK(Hz)                     = 64000000
 *            - HCLK(Hz)                       = 64000000
 *            - AHB Prescaler                  = 1
 *            - APB1 Prescaler                 = 1
 *            - HSE Frequency(Hz)              = 8000000
 *            - PLLM                           = 1
 *            - PLLN                           = 16
 *            - PLLP                           = 2
 *            - Flash Latency(WS)              = 2
 *            - Clock Source for UART1,UART2,UART3 = 16MHz (HSI)
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage */
	HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE; // Enable both HSI and HSE oscillators
	RCC_OscInitStruct.HSEState = RCC_HSE_ON; // Enable HSE (External High-Speed Oscillator)
	RCC_OscInitStruct.HSIState = RCC_HSI_ON; // Enable HSI (Internal High-Speed Oscillator)
	RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1; // No division on HSI
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT; // Default calibration value for HSI
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON; // Enable PLL
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE; // Set PLL source to HSE
	RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1; // Prescaler for PLL input
	RCC_OscInitStruct.PLL.PLLN = 16; // Multiplication factor for PLL
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2; // PLLP division factor
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2; // PLLQ division factor
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2; // PLLR division factor
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	/** Initializes the CPU, AHB and APB buses clocks */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; // Select PLL as the system clock source
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; // AHB Prescaler set to 1
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1; // APB1 Prescaler set to 1

	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2); // Configure system clocks with flash latency of 2 WS
}

/***************************************************************************/
/* enable stop mode regarding only UART1 , UART2 , and UART3 */
BOS_Status EnableStopModebyUARTx(uint8_t port) {

	UART_WakeUpTypeDef WakeUpSelection;
	UART_HandleTypeDef *huart = GetUart(port);

	if ((huart->Instance == USART1) || (huart->Instance == USART2) || (huart->Instance == USART3)) {

		/* make sure that no UART transfer is on-going */
		while (__HAL_UART_GET_FLAG(huart, USART_ISR_BUSY) == SET);

		/* make sure that UART is ready to receive */
		while (__HAL_UART_GET_FLAG(huart, USART_ISR_REACK) == RESET);

		/* set the wake-up event:
		 * specify wake-up on start-bit detection */
		WakeUpSelection.WakeUpEvent = UART_WAKEUP_ON_STARTBIT;
		HAL_UARTEx_StopModeWakeUpSourceConfig(huart, WakeUpSelection);

		/* Enable the UART Wake UP from stop mode Interrupt */
		__HAL_UART_ENABLE_IT(huart, UART_IT_WUF);

		/* enable MCU wake-up by LPUART */
		HAL_UARTEx_EnableStopMode(huart);

		/* enter STOP mode */
		HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
	} else
		return BOS_ERROR;

}

/***************************************************************************/
/* Enable standby mode regarding wake-up pins:
 * WKUP1: PA0  pin
 * WKUP4: PA2  pin
 * WKUP6: PB5  pin
 * WKUP2: PC13 pin
 * NRST pin
 *  */
BOS_Status EnableStandbyModebyWakeupPinx(WakeupPins_t wakeupPins) {

	/* Clear the WUF FLAG */
	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WUF);

	/* Enable the WAKEUP PIN */
	switch (wakeupPins) {

	case PA0_PIN:
		HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1); /* PA0 */
		break;

	case PA2_PIN:
		HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN4); /* PA2 */
		break;

	case PB5_PIN:
		HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN6); /* PB5 */
		break;

	case PC13_PIN:
		HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN2); /* PC13 */
		break;

	case NRST_PIN:
		/* do no thing*/
		break;
	}

	/* Enable SRAM content retention in Standby mode */
	HAL_PWREx_EnableSRAMRetention();

	/* Finally enter the standby mode */
	HAL_PWR_EnterSTANDBYMode();

	return BOS_OK;
}

/***************************************************************************/
/* Disable standby mode regarding wake-up pins:
 * WKUP1: PA0  pin
 * WKUP4: PA2  pin
 * WKUP6: PB5  pin
 * WKUP2: PC13 pin
 * NRST pin
 *  */
BOS_Status DisableStandbyModeWakeupPinx(WakeupPins_t wakeupPins) {

	/* The standby wake-up is same as a system RESET:
	 * The entire code runs from the beginning just as if it was a RESET.
	 * The only difference between a reset and a STANDBY wake-up is that, when the MCU wakes-up,
	 * The SBF status flag in the PWR power control/status register (PWR_CSR) is set */
	if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET) {
		/* clear the flag */
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);

		/* Disable  Wake-up Pinx */
		switch (wakeupPins) {

		case PA0_PIN:
			HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1); /* PA0 */
			break;

		case PA2_PIN:
			HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN4); /* PA2 */
			break;

		case PB5_PIN:
			HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN6); /* PB5 */
			break;

		case PC13_PIN:
			HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN2); /* PC13 */
			break;

		case NRST_PIN:
			/* do no thing*/
			break;
		}

		IND_blink(1000);

	} else
		return BOS_OK;

}

/***************************************************************************/
/* Save Command Topology in Flash RO */
uint8_t SaveTopologyToRO(void) {

	HAL_StatusTypeDef flashStatus = HAL_OK;

	/* flashAdd is initialized with 8 because the first memory room in topology page
	 * is reserved for module's ID */
	uint16_t flashAdd = 8;
	uint16_t temp = 0;

	/* Unlock the FLASH control register access */
	HAL_FLASH_Unlock();

	/* Erase Topology page */
	FLASH_PageErase(FLASH_BANK_2, TOPOLOGY_PAGE_NUM);

	/* Wait for an Erase operation to complete */
	flashStatus = FLASH_WaitForLastOperation((uint32_t) HAL_FLASH_TIMEOUT_VALUE);

	if (flashStatus != HAL_OK) {
		/* return FLASH error code */
		return pFlash.ErrorCode;
	}

	else {
		/* Operation is completed, disable the PER Bit */
		CLEAR_BIT(FLASH->CR, FLASH_CR_PER);
	}

	/* Save module's ID and topology */
	if (myID) {

		/* Save module's ID */
		temp = (uint16_t) (N << 8) + myID;

		/* Save module's ID in Flash memory */
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, TOPOLOGY_START_ADDRESS, temp);

		/* Wait for a Write operation to complete */
		flashStatus = FLASH_WaitForLastOperation((uint32_t) HAL_FLASH_TIMEOUT_VALUE);

		if (flashStatus != HAL_OK) {
			/* return FLASH error code */
			return pFlash.ErrorCode;
		}

		else {
			/* If the program operation is completed, disable the PG Bit */
			CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
		}

		/* Save topology */
		for (uint8_t row = 1; row <= N; row++) {
			for (uint8_t column = 0; column <= MAX_NUM_OF_PORTS; column++) {
				/* Check the module serial number
				 * Note: there isn't a module has serial number 0
				 */
				if (Array[row - 1][0]) {
					/* Save each element in topology Array in Flash memory */
					HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, TOPOLOGY_START_ADDRESS + flashAdd,
							Array[row - 1][column]);
					/* Wait for a Write operation to complete */
					flashStatus = FLASH_WaitForLastOperation((uint32_t) HAL_FLASH_TIMEOUT_VALUE);
					if (flashStatus != HAL_OK) {
						/* return FLASH error code */
						return pFlash.ErrorCode;
					} else {
						/* If the program operation is completed, disable the PG Bit */
						CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
						/* update new flash memory address */
						flashAdd += 8;
					}
				}
			}
		}
	}
	/* Lock the FLASH control register access */
	HAL_FLASH_Lock();
}

/***************************************************************************/
/* Save Command Snippets in Flash RO */
uint8_t SaveSnippetsToRO(void) {
	HAL_StatusTypeDef FlashStatus = HAL_OK;
	uint8_t snipBuffer[sizeof(Snippet_t) + 1] = { 0 };

	/* Unlock the FLASH control register access */
	HAL_FLASH_Unlock();
	/* Erase Snippets page */
	FLASH_PageErase(FLASH_BANK_2, SNIPPETS_PAGE_NUM);
	/* Wait for an Erase operation to complete */
	FlashStatus = FLASH_WaitForLastOperation((uint32_t) HAL_FLASH_TIMEOUT_VALUE);

	if (FlashStatus != HAL_OK) {
		/* return FLASH error code */
		return pFlash.ErrorCode;
	} else {
		/* Operation is completed, disable the PER Bit */
		CLEAR_BIT(FLASH->CR, FLASH_CR_PER);
	}

	/* Save Command Snippets */
	int currentAdd = SNIPPETS_START_ADDRESS;
	for (uint8_t index = 0; index < NumOfRecordedSnippets; index++) {
		/* Check if Snippet condition is true or false */
		if (Snippets[index].Condition.ConditionType) {
			/* A marker to separate Snippets */
			snipBuffer[0] = 0xFE;
			memcpy((uint32_t*) &snipBuffer[1], (uint8_t*) &Snippets[index], sizeof(Snippet_t));
			/* Copy the snippet struct buffer (20 x NumOfRecordedSnippets). Note this is assuming sizeof(Snippet_t) is even */
			for (uint8_t j = 0; j < (sizeof(Snippet_t) / 4); j++) {
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, currentAdd, *(uint64_t*) &snipBuffer[j * 8]);
				FlashStatus = FLASH_WaitForLastOperation((uint32_t) HAL_FLASH_TIMEOUT_VALUE);
				if (FlashStatus != HAL_OK) {
					return pFlash.ErrorCode;
				} else {
					/* If the program operation is completed, disable the PG Bit */
					CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
					currentAdd += 8;
				}
			}
			/* Copy the snippet commands buffer. Always an even number. Note the string termination char might be skipped */
			for (uint8_t j = 0; j < ((strlen(Snippets[index].CMD) + 1) / 4); j++) {
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, currentAdd, *(uint64_t*) (Snippets[index].CMD + j * 4));
				FlashStatus = FLASH_WaitForLastOperation((uint32_t) HAL_FLASH_TIMEOUT_VALUE);
				if (FlashStatus != HAL_OK) {
					return pFlash.ErrorCode;
				} else {
					/* If the program operation is completed, disable the PG Bit */
					CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
					currentAdd += 8;
				}
			}
		}
	}
	/* Lock the FLASH control register access */
	HAL_FLASH_Lock();
}

/***************************************************************************/
/* Clear Array topology in SRAM and Flash RO */
uint8_t ClearROtopology(void) {
	/* Clear the Array */
	memset(Array, 0, sizeof(Array));
	N = 1;
	myID = 0;

	return SaveTopologyToRO();
}

/***************************************************************************/
/* Trigger ST factory bootloader update for a remote module */
void RemoteBootloaderUpdate(uint8_t src, uint8_t dst, uint8_t inport, uint8_t outport) {

	uint8_t myOutport = 0, lastModule = 0;
	int8_t *pcOutputString;

	/* 1. Get Route to destination module */
	myOutport = FindRoute(myID, dst);
	if (outport && dst == myID) { /* This is a 'via port' update and I'm the last module */
		myOutport = outport;
		lastModule = myID;
	} else if (outport == 0) { /* This is a remote update */
		if (NumberOfHops(dst)== 1)
		lastModule = myID;
		else
		lastModule = Route[NumberOfHops(dst)-1]; /* previous module = Route[Number of hops - 1] */
	}

	/* 2. If this is the source of the message, show status on the CLI */
	if (src == myID) {
		/* Obtain the address of the output buffer.  Note there is no mutual
		 * exclusion on this buffer as it is assumed only one command console
		 * interface will be used at any one time. */
		pcOutputString = FreeRTOS_CLIGetOutputBuffer();

		if (outport == 0)		// This is a remote module update
			sprintf((char*) pcOutputString, pcRemoteBootloaderUpdateMessage, dst);
		else
			// This is a 'via port' remote update
			sprintf((char*) pcOutputString, pcRemoteBootloaderUpdateViaPortMessage, dst, outport);

		strcat((char*) pcOutputString, pcRemoteBootloaderUpdateWarningMessage);
		writePxITMutex(inport, (char*) pcOutputString, strlen((char*) pcOutputString), cmd50ms);
		Delay_ms(100);
	}

	/* 3. Setup my inport and outport for bootloader update */
	SetupPortForRemoteBootloaderUpdate(inport);
	SetupPortForRemoteBootloaderUpdate(myOutport);

	/* 5. Build a DMA stream between my inport and outport */
	StartScastDMAStream(inport, myID, myOutport, myID, BIDIRECTIONAL, 0xFFFFFFFF, 0xFFFFFFFF, false);
}

/***************************************************************************/
/* Setup a port for remote ST factory bootloader update:
 * Set baudrate to 57600
 * Enable even parity
 * Set datasize to 9 bits
 */
void SetupPortForRemoteBootloaderUpdate(uint8_t port){

	UART_HandleTypeDef *huart =GetUart(port);
	HAL_UART_DeInit(huart);
	huart->Init.Parity = UART_PARITY_EVEN;
	huart->Init.WordLength = UART_WORDLENGTH_9B;
	HAL_UART_Init(huart);

	/* The CLI port RXNE interrupt might be disabled so enable here again to be sure */
	__HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);

}

/***************************************************************************/
/* H01R0 module initialization */
void Module_Peripheral_Init(void) {
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/* Array ports */
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	MX_USART3_UART_Init();
	MX_USART4_UART_Init();
	MX_USART5_UART_Init();
	MX_USART6_UART_Init();

	MX_TIM3_Init();
	MX_TIM2_Init();
	MX_TIM4_Init();

	/* Circulating DMA Channels ON All Module */
	for (int i = 1; i <= NUM_OF_PORTS; i++) {
		if (GetUart(i) == &huart1) {
			dmaIndex[i - 1] = &(DMA1_Channel1->CNDTR);
		} else if (GetUart(i) == &huart2) {
			dmaIndex[i - 1] = &(DMA1_Channel2->CNDTR);
		} else if (GetUart(i) == &huart3) {
			dmaIndex[i - 1] = &(DMA1_Channel3->CNDTR);
		} else if (GetUart(i) == &huart4) {
			dmaIndex[i - 1] = &(DMA1_Channel4->CNDTR);
		} else if (GetUart(i) == &huart5) {
			dmaIndex[i - 1] = &(DMA1_Channel5->CNDTR);
		} else if (GetUart(i) == &huart6) {
			dmaIndex[i - 1] = &(DMA1_Channel6->CNDTR);
		}
	}

	/* Create module special task (if needed) */
	if (RGBledTaskHandle == NULL)
		xTaskCreate(RGBledTask, (const char*) "RGBledTask", configMINIMAL_STACK_SIZE, NULL,
				osPriorityNormal - osPriorityIdle, &RGBledTaskHandle);
}

/***************************************************************************/
/* H01R0 message processing task */
Module_Status Module_MessagingTask(uint16_t code, uint8_t port, uint8_t src, uint8_t dst, uint8_t shift) {
	Module_Status result = H01R0_OK;
	uint32_t period = 0;
	uint32_t dc = 0;
	int32_t repeat = 0;

	switch (code) {
	case CODE_H01R0_ON:
		LedOn(cMessage[port - 1][shift]);
		break;

	case CODE_H01R0_OFF:
		LedOff();
		break;

	case CODE_H01R0_TOGGLE:
		if (rgbLedState)
			LedOff();
		else
			LedOn(cMessage[port - 1][shift]);
		break;

	case CODE_H01R0_COLOR:
		if (cMessage[port - 1][shift] == 0) {
			/* Color definition from color list */
			SetColor(cMessage[port - 1][1 + shift], cMessage[port - 1][2 + shift]);
		} else if (cMessage[port - 1][shift] == 1) {
			/* RGB color */
			SetRGB(cMessage[port - 1][1 + shift], cMessage[port - 1][2 + shift], cMessage[port - 1][3 + shift], cMessage[port - 1][4 + shift]);
		}
		break;

	case CODE_H01R0_PULSE:
		if (cMessage[port - 1][shift] == 0) {
			/* Color definition from color list */
			period = ((uint32_t) cMessage[port - 1][2 + shift]) + ((uint32_t) cMessage[port - 1][3 + shift] << 8)
					+ ((uint32_t) cMessage[port - 1][4 + shift] << 16)
					+ ((uint32_t) cMessage[port - 1][5 + shift] << 24);
			dc = ((uint32_t) cMessage[port - 1][6 + shift]) + ((uint32_t) cMessage[port - 1][7 + shift] << 8)
					+ ((uint32_t) cMessage[port - 1][8 + shift] << 16)
					+ ((uint32_t) cMessage[port - 1][9 + shift] << 24);
			repeat = ((uint32_t) cMessage[port - 1][10 + shift]) + ((uint32_t) cMessage[port - 1][11 + shift] << 8)
					+ ((uint32_t) cMessage[port - 1][12 + shift] << 16)
					+ ((uint32_t) cMessage[port - 1][13 + shift] << 24);
			SetPulseColor(cMessage[port - 1][1 + shift], period, dc, repeat);
		} else if (cMessage[port - 1][shift] == 1) {
			/* RGB color */
			period = ((uint32_t) cMessage[port - 1][4 + shift]) + ((uint32_t) cMessage[port - 1][5 + shift] << 8)
					+ ((uint32_t) cMessage[port - 1][6 + shift] << 16)
					+ ((uint32_t) cMessage[port - 1][7 + shift] << 24);
			dc = ((uint32_t) cMessage[port - 1][8 + shift]) + ((uint32_t) cMessage[port - 1][9 + shift] << 8)
					+ ((uint32_t) cMessage[port - 1][10 + shift] << 16)
					+ ((uint32_t) cMessage[port - 1][11 + shift] << 24);
			repeat = ((uint32_t) cMessage[port - 1][12 + shift]) + ((uint32_t) cMessage[port - 1][13 + shift] << 8)
					+ ((uint32_t) cMessage[port - 1][14 + shift] << 16)
					+ ((uint32_t) cMessage[port - 1][15 + shift] << 24);
			SetPulseRGB(cMessage[port - 1][1 + shift], cMessage[port - 1][2 + shift],
					cMessage[port - 1][3 + shift], period, dc, repeat);
		}
		break;

	case CODE_H01R0_SWEEP:

		period = ((uint32_t) cMessage[port - 1][1 + shift]) + ((uint32_t) cMessage[port - 1][2 + shift] << 8)
				+ ((uint32_t) cMessage[port - 1][3 + shift] << 16) + ((uint32_t) cMessage[port - 1][4 + shift] << 24);
		repeat = ((uint32_t) cMessage[port - 1][5 + shift]) + ((uint32_t) cMessage[port - 1][6 + shift] << 8)
				+ ((uint32_t) cMessage[port - 1][7 + shift] << 16) + ((uint32_t) cMessage[port - 1][8 + shift] << 24);
		LedSweep(cMessage[port - 1][shift], period, repeat);

		break;

	case CODE_H01R0_DIM:
		period = ((uint32_t) cMessage[port - 1][2 + shift]) + ((uint32_t) cMessage[port - 1][3 + shift] << 8)
				+ ((uint32_t) cMessage[port - 1][4 + shift] << 16) + ((uint32_t) cMessage[port - 1][5 + shift] << 24);
		dc = ((uint32_t) cMessage[port - 1][6 + shift]) + ((uint32_t) cMessage[port - 1][7 + shift] << 8)
				+ ((uint32_t) cMessage[port - 1][8 + shift] << 16) + ((uint32_t) cMessage[port - 1][9 + shift] << 24);
		repeat = ((uint32_t) cMessage[port - 1][10 + shift]) + ((uint32_t) cMessage[port - 1][11 + shift] << 8)
				+ ((uint32_t) cMessage[port - 1][12 + shift] << 16) + ((uint32_t) cMessage[port - 1][13 + shift] << 24);
		LedDim(cMessage[port - 1][shift], cMessage[port - 1][1 + shift], period, dc, repeat);

		break;
	default:
		result = H01R0_ERR_UnknownMessage;
		break;
	}

	return result;
}
/***************************************************************************/
/* Get the port for a given UART */
uint8_t GetPort(UART_HandleTypeDef *huart) {

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
	else if (huart->Instance == USART6)
		return P6;

	return 0;
}

/***************************************************************************/
/* Register this module CLI Commands */
void RegisterModuleCLICommands(void) {
	FreeRTOS_CLIRegisterCommand(&demoCommandDefinition);
	FreeRTOS_CLIRegisterCommand(&onCommandDefinition);
	FreeRTOS_CLIRegisterCommand(&offCommandDefinition);
	FreeRTOS_CLIRegisterCommand(&colorCommandDefinition);
	FreeRTOS_CLIRegisterCommand(&RGBCommandDefinition);
	FreeRTOS_CLIRegisterCommand(&toggleCommandDefinition);
	FreeRTOS_CLIRegisterCommand(&pulseColorCommandDefinition);
	FreeRTOS_CLIRegisterCommand(&pulseRGBCommandDefinition);
	FreeRTOS_CLIRegisterCommand(&sweepCommandDefinition);
	FreeRTOS_CLIRegisterCommand(&dimCommandDefinition);
}

/***************************************************************************/
/* Samples a module parameter value based on parameter index.
 * paramIndex: Index of the parameter (1-based index).
 * value: Pointer to store the sampled float value.
 */
Module_Status GetModuleParameter(uint8_t paramIndex, float *value) {
	Module_Status status = BOS_OK;

	switch (paramIndex) {

	/* Invalid parameter index */
	default:
		status = BOS_ERR_WrongParam;
		break;
	}

	return status;
}

/***************************************************************************/
/* RGBledTask function */
void RGBledTask(void *argument) {

	/* Infinite loop */
	for (;;) {
		/* Switch RGB LED according to its mode */
		switch (rgbLedMode) {
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

/***************************************************************************/
/****************************** Local Functions ****************************/
/***************************************************************************/
/* Load and start red LED PWM
 * red Duty cycle of red LED (0-255).
 * green Duty cycle of green LED (0-255).
 * blue Duty cycle of blue LED (0-255).
 * intensity RGB LED intensity (0-100).
 */
Module_Status startPWM(uint8_t red, uint8_t green, uint8_t blue, uint8_t intensity) {
	uint32_t period = (PWM_TIMER_CLOCK / RGB_PWM_FREQ) - 1;

	/* PWM period */
	htim2.Instance->ARR = period;
	htim3.Instance->ARR = period;
	htim4.Instance->ARR = period;

	/* PWM duty cycle */
	htim2.Instance->CCR1 = ((intensity / 100.0f) * ((uint8_t) red / 255.0f) * period);
	htim3.Instance->CCR1 = ((intensity / 100.0f) * ((uint8_t) blue / 255.0f) * period);
	htim4.Instance->CCR2 = ((intensity / 100.0f) * ((uint8_t) green / 255.0f) * period);

	if (HAL_TIM_PWM_Start(&htim2, RGB_RED_TIM_CH) != HAL_OK)
		return H01R0_ERROR;

	if (HAL_TIM_PWM_Start(&htim3, RGB_BLUE_TIM_CH) != HAL_OK)
		return H01R0_ERROR;

	if (HAL_TIM_PWM_Start(&htim4, RGB_GREEN_TIM_CH) != HAL_OK)
		return H01R0_ERROR;

	return H01R0_OK;
}

/***************************************************************************/
/* Pulse the RGB LED */
void RGBpulse(uint8_t mode) {
	uint8_t temp = 0;

	if (rgbCount > 0 || rgbCount == -1) {

		if (mode == RGB_PULSE_RGB)
			SetRGB(rgbRed, rgbGreen, rgbBlue, 100);
		else if (mode == RGB_PULSE_COLOR)
			SetColor(rgbColor, 100);

		osDelay(rgbDC);
		temp = rgbLedMode; /* Backup rgbLedMode so that it's not reset */
		LedOff();
		rgbLedMode = temp;
		osDelay(rgbPeriod - rgbDC);

		if (rgbCount > 0)
			rgbCount--;
	} else {
		rgbLedMode = 0;
	}
}

/***************************************************************************/
/* RGB LED basic color sweep */
void RGBsweepBasic(void) {
	static uint32_t temp;

	temp = rgbPeriod / 6;

	if (rgbCount > 0 || rgbCount == -1) {
		SetColor(RED, 100);
		osDelay(temp);
		SetColor(YELLOW, 100);
		osDelay(temp);
		SetColor(GREEN, 100);
		osDelay(temp);
		SetColor(CYAN, 100);
		osDelay(temp);
		SetColor(BLUE, 100);
		osDelay(temp);
		SetColor(MAGENTA, 100);
		osDelay(temp);

		if (rgbCount > 0)
			rgbCount--;
	} else {
		LedOff();
	}
}

/***************************************************************************/
/* RGB LED fine color sweep */
void RGBsweepFine(void) {
	static uint32_t temp;

	temp = rgbPeriod / 6;

	if (rgbCount > 0 || rgbCount == -1) {
		/* Red */
		for (uint8_t i = 0; i < 255; i++) {
			SetRGB(255, i, 0, 100);
			osDelay(ceil(temp / 255));
		}
		/* Yellow */
		for (uint8_t i = 255; i > 0; i--) {
			SetRGB(i, 255, 0, 100);
			osDelay(ceil(temp / 255));
		}
		/* Green */
		for (uint8_t i = 0; i < 255; i++) {
			SetRGB(0, 255, i, 100);
			osDelay(ceil(temp / 255));
		}
		/* Cyan */
		for (uint8_t i = 255; i > 0; i--) {
			SetRGB(0, i, 255, 100);
			osDelay(ceil(temp / 255));
		}
		/* Blue */
		for (uint8_t i = 0; i < 255; i++) {
			SetRGB(i, 0, 255, 100);
			osDelay(ceil(temp / 255));
		}
		/* Magenta */
		for (uint8_t i = 255; i > 0; i--) {
			SetRGB(255, 0, i, 100);
			osDelay(ceil(temp / 255));
		}

		if (rgbCount > 0)
			rgbCount--;
	} else {
		LedOff();
	}
}

/***************************************************************************/
/* Dim the RGB LED */
void RGBdim(uint8_t mode) {
	uint8_t temp = 0;

	if (rgbCount > 0 || rgbCount == -1) {
		temp = rgbLedMode; /* Store mode so that it's not reset */
		if (mode == RGB_DIM_UP) {
			for (uint8_t i = 0; i <= 100; i++) {
				SetColor(rgbColor, i);
				osDelay(rgbPeriod / 100);
			}
		} else if (mode == RGB_DIM_UP_WAIT) {
			for (uint8_t i = 0; i <= 100; i++) {
				SetColor(rgbColor, i);
				osDelay((rgbPeriod - rgbDC) / 100);
			}
			osDelay(rgbDC);
		} else if (mode == RGB_DIM_DOWN) {
			for (uint8_t i = 101; i > 0; i--) {
				SetColor(rgbColor, i - 1);
				osDelay(rgbPeriod / 100);
			}
		} else if (mode == RGB_DIM_DOWN_WAIT) {
			for (uint8_t i = 101; i > 0; i--) {
				SetColor(rgbColor, i - 1);
				osDelay((rgbPeriod - rgbDC) / 100);
			}
			osDelay(rgbDC);
		} else if (mode == RGB_DIM_UP_DOWN) {
			for (uint8_t i = 0; i <= 100; i++) {
				SetColor(rgbColor, i);
				osDelay(rgbPeriod / 200);
			}
			for (uint8_t i = 101; i > 0; i--) {
				SetColor(rgbColor, i - 1);
				osDelay(rgbPeriod / 200);
			}
		} else if (mode == RGB_DIM_DOWN_UP) {
			for (uint8_t i = 101; i > 0; i--) {
				SetColor(rgbColor, i - 1);
				osDelay(rgbPeriod / 200);
			}
			for (uint8_t i = 0; i <= 100; i++) {
				SetColor(rgbColor, i);
				osDelay(rgbPeriod / 200);
			}
		} else if (mode == RGB_DIM_UP_DOWN_WAIT) {
			for (uint8_t i = 0; i <= 100; i++) {
				SetColor(rgbColor, i);
				osDelay((rgbPeriod - rgbDC) / 200);
			}
			for (uint8_t i = 101; i > 0; i--) {
				SetColor(rgbColor, i - 1);
				osDelay((rgbPeriod - rgbDC) / 200);
			}
			osDelay(rgbDC);
		} else if (mode == RGB_DIM_DOWN_UP_WAIT) {
			for (uint8_t i = 101; i > 0; i--) {
				SetColor(rgbColor, i - 1);
				osDelay((rgbPeriod - rgbDC) / 200);
			}
			for (uint8_t i = 0; i <= 100; i++) {
				SetColor(rgbColor, i);
				osDelay((rgbPeriod - rgbDC) / 200);
			}
			osDelay(rgbDC);
			rgbLedMode = temp;
		}

		if (rgbCount > 0)
			rgbCount--;
	} else {
		rgbLedMode = 0;
	}
}

/***************************************************************************/
/***************************** General Functions ***************************/
/***************************************************************************/
/* Turn on RGB LED (white color) */
Module_Status LedOn(uint8_t intensity) {
	Module_Status result = H01R0_OK;

	if (intensity == 0) {
		htim2.Instance->CCR1 = 0;
		htim3.Instance->CCR1 = 0;
		htim4.Instance->CCR2 = 0;

		rgbLedState = 0;

		return H01R0_OK;
	} else if (intensity <= 100) {
		result = startPWM(255, 255, 255, intensity);

		if (result == H01R0_OK)
			rgbLedState = 1;

		return result;
	} else
		return H01R0_ERR_WrongIntensity;

}

/***************************************************************************/
/* Turn off RGB LED  */
Module_Status LedOff(void) {

	HAL_TIM_PWM_Stop(&htim2, RGB_RED_TIM_CH);
	HAL_TIM_PWM_Stop(&htim3, RGB_BLUE_TIM_CH);
	HAL_TIM_PWM_Stop(&htim4, RGB_GREEN_TIM_CH);

	htim2.Instance->CCR1 = 0;
	htim3.Instance->CCR1 = 0;
	htim4.Instance->CCR2 = 0;

	rgbLedState = 0;
	rgbLedMode = 0;

	return H01R0_OK;
}

/***************************************************************************/
/* Toggle RGB LED  */
Module_Status LedToggle(uint8_t intensity) {
	Module_Status result = H01R0_OK;

	if (rgbLedState)
		result = LedOff();
	else
		result = LedOn(intensity);

	return result;
}

/***************************************************************************/
/* Set RGB colors on LED (continuously) using PWM intensity modulation */
Module_Status SetRGB(uint8_t red, uint8_t green, uint8_t blue, uint8_t intensity) {
	if (intensity == 0)
		return LedOn(0);
	else if (intensity > 100)
		return H01R0_ERR_WrongIntensity;
	else
		return startPWM(red, green, blue, intensity);
}

/***************************************************************************/
/* Set LED color from a predefined color list (continuously) */
Module_Status SetColor(uint8_t color, uint8_t intensity) {
	Module_Status result = H01R0_OK;

	if (!intensity)
		return LedOn(0);
	else if (intensity > 100)
		return H01R0_ERR_WrongIntensity;
	else {
		switch (color) {
		case BLACK:
			result = LedOff();
			break;

		case WHITE:
			result = LedOn(intensity);
			break;

		case RED:
			result = SetRGB(255, 0, 0, intensity);
			break;

		case BLUE:
			result = SetRGB(0, 0, 255, intensity);
			break;

		case YELLOW:
			result = SetRGB(255, 255, 0, intensity);
			break;

		case CYAN:
			result = SetRGB(0, 255, 255, intensity);
			break;

		case MAGENTA:
			result = SetRGB(255, 0, 255, intensity);
			break;

		case GREEN:
			result = SetRGB(0, 255, 0, intensity);
			break;

		default:
			result = H01R0_ERR_WrongColor;
			break;
		}
	}

	return result;
}

/***************************************************************************/
/* Activate the RGB LED pulse command with RGB values. Set repeat to -1 for periodic signals */
Module_Status SetPulseRGB(uint8_t red, uint8_t green, uint8_t blue, uint32_t period, uint32_t dc, int32_t repeat) {
	Module_Status result = H01R0_OK;

	rgbRed = red;
	rgbGreen = green;
	rgbBlue = blue;
	rgbPeriod = period;
	rgbDC = dc;
	rgbCount = repeat;

	rgbLedMode = RGB_PULSE_RGB;

	return result;
}

/***************************************************************************/
/* Activate the RGB LED pulse command with a specific color. Set repeat to -1 for periodic signals */
Module_Status SetPulseColor(uint8_t color, uint32_t period, uint32_t dc, int32_t repeat) {
	Module_Status result = H01R0_OK;

	rgbColor = color;
	rgbPeriod = period;
	rgbDC = dc;
	rgbCount = repeat;

	rgbLedMode = RGB_PULSE_COLOR;

	return result;
}

/***************************************************************************/
/* Activate the RGB LED sweep mode. Set repeat to -1 for periodic signals.
 * Minimum period for fine sweep is 6 x 256 = 1536 ms
 */
Module_Status LedSweep(uint8_t mode, uint32_t period, int32_t repeat) {

	if (mode == 3 || mode == 4) {

		Module_Status result = H01R0_OK;

		rgbPeriod = period;
		rgbCount = repeat;
		rgbLedMode = mode;

		return result;
	} else {
		return H01R0_ERR_WrongMode;
	}
}

/***************************************************************************/
/* Activate RGB LED dim mode using one of the basic colors. Set repeat to -1 for periodic signals */
Module_Status LedDim(uint8_t color, uint8_t mode, uint32_t period, uint32_t wait, int32_t repeat) {
	if (mode >= 5 && mode <= 12) {
		Module_Status result = H01R0_OK;

		rgbColor = color;
		rgbPeriod = period;
		rgbDC = wait;
		rgbCount = repeat;
		rgbLedMode = mode;

		return result;
	} else {
		return H01R0_ERR_WrongMode;
	}
}

/***************************************************************************/
/********************************* Commands ********************************/
/***************************************************************************/
portBASE_TYPE demoCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString) {
	static const int8_t *pcRedMessage = (int8_t*) "Red LED is on\r\n";
	static const int8_t *pcGreenMessage = (int8_t*) "Green LED is on\r\n";
	static const int8_t *pcBlueMessage = (int8_t*) "Blue LED is on";

	/* Remove compile time warnings about unused parameters, and check the
	 write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	 write buffer length is adequate, so does not check for buffer overflows. */
	(void) pcCommandString;
	(void) xWriteBufferLen;
	configASSERT(pcWriteBuffer);

	/* Respond to the command */
	LedOff();
	SetColor(RED, 50);
	writePxMutex(pcPort, (char*) pcRedMessage, strlen((char*) pcRedMessage), 10, 10);
	Delay_ms(1000);
	LedOff();
	SetColor(GREEN, 50);
	writePxMutex(pcPort, (char*) pcGreenMessage, strlen((char*) pcGreenMessage), 10, 10);
	Delay_ms(1000);
	LedOff();
	SetColor(BLUE, 50);
	writePxMutex(pcPort, (char*) pcBlueMessage, strlen((char*) pcBlueMessage), 10, 10);
	Delay_ms(1000);
	LedOff();
	strcpy((char*) pcWriteBuffer, "\r\n");

	/* There is no more data to return after this single string, so return
	 pdFALSE. */
	return pdFALSE;
}

/***************************************************************************/
portBASE_TYPE onCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString) {
	Module_Status result = H01R0_OK;

	int8_t *pcParameterString1;
	portBASE_TYPE xParameterStringLength1 = 0;
	uint8_t intensity = 0;
	static const int8_t *pcOKMessage = (int8_t*) "RGB LED is on at intensity %d%%\r\n";
	static const int8_t *pcWrongIntensityMessage = (int8_t*) "Wrong intensity!\n\r";

	/* Remove compile time warnings about unused parameters, and check the
	 write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	 write buffer length is adequate, so does not check for buffer overflows. */
	(void) xWriteBufferLen;
	configASSERT(pcWriteBuffer);

	/* Obtain the 1st parameter string. */
	pcParameterString1 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, /* The command string itself. */
	1, /* Return the first parameter. */
	&xParameterStringLength1 /* Store the parameter string length. */
	);
	intensity = (uint8_t) atol((char*) pcParameterString1);

	result = LedOn(intensity);

	/* Respond to the command */
	if (result == H01R0_OK)
		sprintf((char*) pcWriteBuffer, (char*) pcOKMessage, intensity);
	else if (result == H01R0_ERR_WrongIntensity)
		strcpy((char*) pcWriteBuffer, (char*) pcWrongIntensityMessage);

	/* There is no more data to return after this single string, so return
	 pdFALSE. */
	return pdFALSE;
}

/***************************************************************************/
portBASE_TYPE offCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString) {
	static const int8_t *pcMessage = (int8_t*) "RGB LED is off\r\n";

	/* Remove compile time warnings about unused parameters, and check the
	 write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	 write buffer length is adequate, so does not check for buffer overflows. */
	(void) pcCommandString;
	(void) xWriteBufferLen;
	configASSERT(pcWriteBuffer);

	/* Respond to the command */
	strcpy((char*) pcWriteBuffer, (char*) pcMessage);
	LedOff();

	/* There is no more data to return after this single string, so return
	 pdFALSE. */
	return pdFALSE;
}

/***************************************************************************/
portBASE_TYPE colorCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString) {
	Module_Status result = H01R0_OK;
	uint8_t color = 0;
	uint8_t intensity = 0;
	char par[15] = { 0 };
	static int8_t *pcParameterString1, *pcParameterString2;
	portBASE_TYPE xParameterStringLength1 = 0, xParameterStringLength2 = 0;

	static const int8_t *pcOKMessage = (int8_t*) "RGB LED color is %s at intensity %d%%\n\r";
	static const int8_t *pcWrongColorMessage = (int8_t*) "Unknown color!\n\r";
	static const int8_t *pcWrongIntensityMessage = (int8_t*) "Wrong intensity!\n\r";

	/* Remove compile time warnings about unused parameters, and check the
	 write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	 write buffer length is adequate, so does not check for buffer overflows. */
	(void) xWriteBufferLen;
	configASSERT(pcWriteBuffer);

	/* Obtain the 1st parameter string. */
	pcParameterString1 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, /* The command string itself. */
	1, /* Return the first parameter. */
	&xParameterStringLength1 /* Store the parameter string length. */
	);
	/* Read the color value. */
	if (!strncmp((const char*) pcParameterString1, "black", xParameterStringLength1))
		color = BLACK;
	else if (!strncmp((const char*) pcParameterString1, "white", xParameterStringLength1))
		color = WHITE;
	else if (!strncmp((const char*) pcParameterString1, "red", xParameterStringLength1))
		color = RED;
	else if (!strncmp((const char*) pcParameterString1, "blue", xParameterStringLength1))
		color = BLUE;
	else if (!strncmp((const char*) pcParameterString1, "yellow", xParameterStringLength1))
		color = YELLOW;
	else if (!strncmp((const char*) pcParameterString1, "cyan", xParameterStringLength1))
		color = CYAN;
	else if (!strncmp((const char*) pcParameterString1, "magenta", xParameterStringLength1))
		color = MAGENTA;
	else if (!strncmp((const char*) pcParameterString1, "green", xParameterStringLength1))
		color = GREEN;

	/* Obtain the 2nd parameter string. */
	pcParameterString2 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 2, &xParameterStringLength2);
	intensity = (uint8_t) atol((char*) pcParameterString2);

	result = SetColor(color, intensity);

	/* Respond to the command */
	if (result == H01R0_OK) {
		/* Isolate first parameter string */
		strncpy(par, (char*) pcParameterString1, xParameterStringLength1);
		sprintf((char*) pcWriteBuffer, (char*) pcOKMessage, par, intensity);
	} else if (result == H01R0_ERR_WrongColor)
		strcpy((char*) pcWriteBuffer, (char*) pcWrongColorMessage);
	else if (result == H01R0_ERR_WrongIntensity)
		strcpy((char*) pcWriteBuffer, (char*) pcWrongIntensityMessage);

	/* There is no more data to return after this single string, so return
	 pdFALSE. */
	return pdFALSE;
}

/***************************************************************************/
portBASE_TYPE RGBCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString) {
	Module_Status result = H01R0_OK;
	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;
	uint8_t intensity = 0;
	static int8_t *pcParameterString1, *pcParameterString2, *pcParameterString3, *pcParameterString4;
	portBASE_TYPE xParameterStringLength1 = 0, xParameterStringLength2 = 0;
	portBASE_TYPE xParameterStringLength3 = 0, xParameterStringLength4 = 0;

	static const int8_t *pcOKMessage = (int8_t*) "RGB LED is (%d, %d, %d) at intensity %d%%\n\r";
	static const int8_t *pcWrongColorMessage = (int8_t*) "Wrong color value!\n\r";
	static const int8_t *pcWrongIntensityMessage = (int8_t*) "Wrong intensity!\n\r";

	/* Remove compile time warnings about unused parameters, and check the
	 write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	 write buffer length is adequate, so does not check for buffer overflows. */
	(void) xWriteBufferLen;
	configASSERT(pcWriteBuffer);

	/* Obtain the 1st parameter string. */
	pcParameterString1 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParameterStringLength1);
	red = (uint8_t) atol((char*) pcParameterString1);

	/* Obtain the 2nd parameter string. */
	pcParameterString2 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 2, &xParameterStringLength2);
	green = (uint8_t) atol((char*) pcParameterString2);

	/* Obtain the 3rd parameter string. */
	pcParameterString3 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 3, &xParameterStringLength3);
	blue = (uint8_t) atol((char*) pcParameterString3);

	/* Obtain the 4th parameter string. */
	pcParameterString4 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 4, &xParameterStringLength4);
	intensity = (uint8_t) atol((char*) pcParameterString4);

	result = SetRGB(red, green, blue, intensity);

	/* Respond to the command */
	if (result == H01R0_OK)
		sprintf((char*) pcWriteBuffer, (char*) pcOKMessage, red, green, blue, intensity);
	else if (result == H01R0_ERR_WrongColor)
		strcpy((char*) pcWriteBuffer, (char*) pcWrongColorMessage);
	else if (result == H01R0_ERR_WrongIntensity)
		strcpy((char*) pcWriteBuffer, (char*) pcWrongIntensityMessage);

	/* There is no more data to return after this single string, so return
	 pdFALSE. */
	return pdFALSE;
}

/***************************************************************************/
portBASE_TYPE toggleCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString) {
	Module_Status result = H01R0_OK;

	int8_t *pcParameterString1;
	portBASE_TYPE xParameterStringLength1 = 0;
	uint8_t intensity = 0;
	static const int8_t *pcOK1Message = (int8_t*) "RGB LED is on at intensity %d%%\r\n";
	static const int8_t *pcOK0Message = (int8_t*) "RGB LED is off\r\n";
	static const int8_t *pcWrongIntensityMessage = (int8_t*) "Wrong intensity!\n\r";

	/* Remove compile time warnings about unused parameters, and check the
	 write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	 write buffer length is adequate, so does not check for buffer overflows. */
	(void) xWriteBufferLen;
	configASSERT(pcWriteBuffer);

	/* Obtain the 1st parameter string. */
	pcParameterString1 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, /* The command string itself. */
	1, /* Return the first parameter. */
	&xParameterStringLength1 /* Store the parameter string length. */
	);
	intensity = (uint8_t) atol((char*) pcParameterString1);

	result = LedToggle(intensity);

	/* Respond to the command */
	if ((result == H01R0_OK) && rgbLedState)
		sprintf((char*) pcWriteBuffer, (char*) pcOK1Message, intensity);
	else if ((result == H01R0_OK) && !rgbLedState)
		sprintf((char*) pcWriteBuffer, (char*) pcOK0Message, intensity);
	else if (result == H01R0_ERR_WrongIntensity)
		strcpy((char*) pcWriteBuffer, (char*) pcWrongIntensityMessage);

	/* There is no more data to return after this single string, so return
	 pdFALSE. */
	return pdFALSE;
}

/***************************************************************************/
portBASE_TYPE pulseColorCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString) {
	Module_Status result = H01R0_OK;
	uint8_t color = 0;
	uint32_t period = 0, dc = 0;
	int32_t repeat = 0;
	char par[15] = { 0 };
	static int8_t *pcParameterString1, *pcParameterString2, *pcParameterString3, *pcParameterString4;
	portBASE_TYPE xParameterStringLength1 = 0, xParameterStringLength2 = 0;
	portBASE_TYPE xParameterStringLength3 = 0, xParameterStringLength4 = 0;

	static const int8_t *pcMessage =
			(int8_t*) "A %s pulse with period %d ms and duty cycle %d ms is generated %d times\n\r";
	static const int8_t *pcMessageInf =
			(int8_t*) "A %s pulse with period %d ms and duty cycle %d ms is generated periodically\n\r";

	/* Remove compile time warnings about unused parameters, and check the
	 write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	 write buffer length is adequate, so does not check for buffer overflows. */
	(void) xWriteBufferLen;
	configASSERT(pcWriteBuffer);

	/* Obtain the 1st parameter string. */
	pcParameterString1 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParameterStringLength1);
	/* Read the color value. */
	if (!strncmp((const char*) pcParameterString1, "black", xParameterStringLength1))
		color = BLACK;
	else if (!strncmp((const char*) pcParameterString1, "white", xParameterStringLength1))
		color = WHITE;
	else if (!strncmp((const char*) pcParameterString1, "red", xParameterStringLength1))
		color = RED;
	else if (!strncmp((const char*) pcParameterString1, "blue", xParameterStringLength1))
		color = BLUE;
	else if (!strncmp((const char*) pcParameterString1, "yellow", xParameterStringLength1))
		color = YELLOW;
	else if (!strncmp((const char*) pcParameterString1, "cyan", xParameterStringLength1))
		color = CYAN;
	else if (!strncmp((const char*) pcParameterString1, "magenta", xParameterStringLength1))
		color = MAGENTA;
	else if (!strncmp((const char*) pcParameterString1, "green", xParameterStringLength1))
		color = GREEN;

	/* Obtain the 2nd parameter string. */
	pcParameterString2 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 2, &xParameterStringLength2);
	period = (uint32_t) atol((char*) pcParameterString2);

	/* Obtain the 3rd parameter string. */
	pcParameterString3 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 3, &xParameterStringLength3);
	dc = (uint32_t) atol((char*) pcParameterString3);

	/* Obtain the 4th parameter string. */
	pcParameterString4 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 4, &xParameterStringLength4);
	if (!strcmp((char*) pcParameterString4, "inf"))
		repeat = -1;
	else
		repeat = (int32_t) atol((char*) pcParameterString4);

	result = SetPulseColor(color, period, dc, repeat);

	/* Respond to the command */
	if (result == H01R0_OK) {
		/* Isolate first parameter string */
		strncpy(par, (char*) pcParameterString1, xParameterStringLength1);
		if (repeat == -1)
			sprintf((char*) pcWriteBuffer, (char*) pcMessageInf, par, period, dc);
		else
			sprintf((char*) pcWriteBuffer, (char*) pcMessage, par, period, dc, repeat);
	}

	/* There is no more data to return after this single string, so return
	 pdFALSE. */
	return pdFALSE;
}

/***************************************************************************/
portBASE_TYPE pulseRGBCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString) {
	Module_Status result = H01R0_OK;
	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;
	uint32_t period = 0, dc = 0;
	int32_t repeat = 0;
	static int8_t *pcParameterString1, *pcParameterString2, *pcParameterString3, *pcParameterString4;
	static int8_t *pcParameterString5, *pcParameterString6;
	portBASE_TYPE xParameterStringLength1 = 0, xParameterStringLength2 = 0, xParameterStringLength3 = 0;
	portBASE_TYPE xParameterStringLength4 = 0, xParameterStringLength5 = 0, xParameterStringLength6 = 0;

	static const int8_t *pcMessage =
			(int8_t*) "A (%d, %d, %d) RGB pulse with period %d ms and duty cycle %d ms is generated %d times\n\r";
	static const int8_t *pcMessageInf =
			(int8_t*) "A (%d, %d, %d) RGB pulse with period %d ms and duty cycle %d ms is generated periodically\n\r";

	/* Remove compile time warnings about unused parameters, and check the
	 write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	 write buffer length is adequate, so does not check for buffer overflows. */
	(void) xWriteBufferLen;
	configASSERT(pcWriteBuffer);

	/* Obtain the 1st parameter string. */
	pcParameterString1 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParameterStringLength1);
	red = (uint8_t) atol((char*) pcParameterString1);

	/* Obtain the 2nd parameter string. */
	pcParameterString2 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 2, &xParameterStringLength2);
	green = (uint8_t) atol((char*) pcParameterString2);

	/* Obtain the 3rd parameter string. */
	pcParameterString3 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 3, &xParameterStringLength3);
	blue = (uint8_t) atol((char*) pcParameterString3);

	/* Obtain the 4th parameter string. */
	pcParameterString4 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 4, &xParameterStringLength4);
	period = (uint32_t) atol((char*) pcParameterString4);

	/* Obtain the 5th parameter string. */
	pcParameterString5 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 5, &xParameterStringLength5);
	dc = (uint32_t) atol((char*) pcParameterString5);

	/* Obtain the 6th parameter string. */
	pcParameterString6 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 6, &xParameterStringLength6);
	if (!strcmp((char*) pcParameterString6, "inf"))
		repeat = -1;
	else
		repeat = (int32_t) atol((char*) pcParameterString6);

	result = SetPulseRGB(red, green, blue, period, dc, repeat);

	/* Respond to the command */
	if (result == H01R0_OK) {
		if (repeat == -1)
			sprintf((char*) pcWriteBuffer, (char*) pcMessageInf, red, green, blue, period, dc);
		else
			sprintf((char*) pcWriteBuffer, (char*) pcMessage, red, green, blue, period, dc, repeat);
	}

	/* There is no more data to return after this single string, so return
	 pdFALSE. */
	return pdFALSE;
}

/***************************************************************************/
portBASE_TYPE sweepCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString) {
	Module_Status result = H01R0_OK;
	uint8_t mode = 0;
	uint32_t period = 0;
	int32_t repeat = 0;
	char par[15] = { 0 };
	static int8_t *pcParameterString1, *pcParameterString2, *pcParameterString3;
	portBASE_TYPE xParameterStringLength1 = 0, xParameterStringLength2 = 0, xParameterStringLength3 = 0;

	static const int8_t *pcMessage =
			(int8_t*) "The RGB LED performs a %s color sweep with period %d ms. The sweep is repeated %d times\n\r";
	static const int8_t *pcMessageInf =
			(int8_t*) "The RGB LED performs a %s color sweep with period %d ms. The sweep is repeated periodically\n\r";

	/* Remove compile time warnings about unused parameters, and check the
	 write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	 write buffer length is adequate, so does not check for buffer overflows. */
	(void) xWriteBufferLen;
	configASSERT(pcWriteBuffer);

	/* Obtain the 1st parameter string. */
	pcParameterString1 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParameterStringLength1);
	if (!strncmp((char*) pcParameterString1, "basic", xParameterStringLength1))
		mode = RGB_SWEEP_BASIC;
	else if (!strncmp((char*) pcParameterString1, "fine", xParameterStringLength1))
		mode = RGB_SWEEP_FINE;

	/* Obtain the 2nd parameter string. */
	pcParameterString2 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 2, &xParameterStringLength2);
	period = (uint32_t) atol((char*) pcParameterString2);

	/* Obtain the 3rd parameter string. */
	pcParameterString3 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 3, &xParameterStringLength3);
	if (!strcmp((char*) pcParameterString3, "inf"))
		repeat = -1;
	else
		repeat = (int32_t) atol((char*) pcParameterString3);

	result = LedSweep(mode, period, repeat);

	/* Respond to the command */
	if (result == H01R0_OK) {
		/* Isolate first parameter string */
		strncpy(par, (char*) pcParameterString1, xParameterStringLength1);
		if (repeat == -1)
			sprintf((char*) pcWriteBuffer, (char*) pcMessageInf, par, period);
		else
			sprintf((char*) pcWriteBuffer, (char*) pcMessage, par, period, repeat);
	}

	/* There is no more data to return after this single string, so return
	 pdFALSE. */
	return pdFALSE;
}

/***************************************************************************/
portBASE_TYPE dimCommand(int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString) {
	Module_Status result = H01R0_OK;
	uint8_t color = 0, mode = 0;
	uint32_t period = 0, wait = 0;
	int32_t repeat = 0;
	static int8_t *pcParameterString1, *pcParameterString2, *pcParameterString3, *pcParameterString4,
			*pcParameterString5;
	portBASE_TYPE xParameterStringLength1 = 0, xParameterStringLength2 = 0, xParameterStringLength3 = 0;
	portBASE_TYPE xParameterStringLength4 = 0, xParameterStringLength5 = 0;
	char par1[15] = { 0 }, par2[15] = { 0 };

	static const int8_t *pcMessage =
			(int8_t*) "The RGB LED dims a %s color with period %d ms and wait time %d ms. The dim mode is %s and the dim cycle is repeated %d times\n\r";
	static const int8_t *pcMessageInf =
			(int8_t*) "The RGB LED dims a %s color with period %d ms and wait time %d ms. The dim mode is %s and the dim cycle is repeated periodically\n\r";

	/* Remove compile time warnings about unused parameters, and check the
	 write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	 write buffer length is adequate, so does not check for buffer overflows. */
	(void) xWriteBufferLen;
	configASSERT(pcWriteBuffer);

	/* Obtain the 1st parameter string. */
	pcParameterString1 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParameterStringLength1);
	/* Read the color value. */
	if (!strncmp((const char*) pcParameterString1, "black", xParameterStringLength1))
		color = BLACK;
	else if (!strncmp((const char*) pcParameterString1, "white", xParameterStringLength1))
		color = WHITE;
	else if (!strncmp((const char*) pcParameterString1, "red", xParameterStringLength1))
		color = RED;
	else if (!strncmp((const char*) pcParameterString1, "blue", xParameterStringLength1))
		color = BLUE;
	else if (!strncmp((const char*) pcParameterString1, "yellow", xParameterStringLength1))
		color = YELLOW;
	else if (!strncmp((const char*) pcParameterString1, "cyan", xParameterStringLength1))
		color = CYAN;
	else if (!strncmp((const char*) pcParameterString1, "magenta", xParameterStringLength1))
		color = MAGENTA;
	else if (!strncmp((const char*) pcParameterString1, "green", xParameterStringLength1))
		color = GREEN;

	/* Obtain the 2nd parameter string. */
	pcParameterString2 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 2, &xParameterStringLength2);
	if (!strncmp((char*) pcParameterString2, "up", xParameterStringLength2))
		mode = RGB_DIM_UP;
	else if (!strncmp((char*) pcParameterString2, "upwait", xParameterStringLength2))
		mode = RGB_DIM_UP_WAIT;
	else if (!strncmp((char*) pcParameterString2, "down", xParameterStringLength2))
		mode = RGB_DIM_DOWN;
	else if (!strncmp((char*) pcParameterString2, "downwait", xParameterStringLength2))
		mode = RGB_DIM_DOWN_WAIT;
	else if (!strncmp((char*) pcParameterString2, "updown", xParameterStringLength2))
		mode = RGB_DIM_UP_DOWN;
	else if (!strncmp((char*) pcParameterString2, "downup", xParameterStringLength2))
		mode = RGB_DIM_DOWN_UP;
	else if (!strncmp((char*) pcParameterString2, "updownwait", xParameterStringLength2))
		mode = RGB_DIM_UP_DOWN_WAIT;
	else if (!strncmp((char*) pcParameterString2, "downupwait", xParameterStringLength2))
		mode = RGB_DIM_DOWN_UP_WAIT;

	/* Obtain the 3rd parameter string. */
	pcParameterString3 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 3, &xParameterStringLength3);
	period = (uint32_t) atol((char*) pcParameterString3);

	/* Obtain the 4th parameter string. */
	pcParameterString4 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 4, &xParameterStringLength4);
	wait = (uint32_t) atol((char*) pcParameterString4);

	/* Obtain the 5th parameter string. */
	pcParameterString5 = (int8_t*) FreeRTOS_CLIGetParameter(pcCommandString, 5, &xParameterStringLength5);
	if (!strcmp((char*) pcParameterString5, "inf"))
		repeat = -1;
	else
		repeat = (int32_t) atol((char*) pcParameterString5);

	result = LedDim(color, mode, period, wait, repeat);

	/* Respond to the command */
	if (result == H01R0_OK) {
		/* Isolate first and second parameter strings. */
		strncpy(par1, (char*) pcParameterString1, xParameterStringLength1);
		strncpy(par2, (char*) pcParameterString2, xParameterStringLength2);
		if (repeat == -1)
			sprintf((char*) pcWriteBuffer, (char*) pcMessageInf, par1, period, wait, par2);
		else
			sprintf((char*) pcWriteBuffer, (char*) pcMessage, par1, period, wait, par2, repeat);
	}

	/* There is no more data to return after this single string, so return
	 pdFALSE. */
	return pdFALSE;
}

/***************************************************************************/
/***************** (C) COPYRIGHT HEXABITZ ***** END OF FILE ****************/
