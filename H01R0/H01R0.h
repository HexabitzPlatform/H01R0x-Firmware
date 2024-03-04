/*
 BitzOS (BOS) V0.3.1 - Copyright (C) 2017-2024 Hexabitz
 All rights reserved
 
 File Name     : H01R0.h
 Description   : Header file for module H01R0.
 	 	 	 	 (Description_of_module)

(Description of Special module peripheral configuration):
>>
>>
>>

 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef H01R0_H
#define H01R0_H

/* Includes ------------------------------------------------------------------*/
#include "BOS.h"
#include "H01R0_MemoryMap.h"
#include "H01R0_uart.h"
#include "H01R0_gpio.h"
#include "H01R0_dma.h"
#include "H01R0_inputs.h"
#include "H01R0_eeprom.h"
/* Exported definitions -------------------------------------------------------*/

#define	modulePN		_H01R0


/* Port-related definitions */
#define	NumOfPorts			6

#define P_PROG 				P2						/* ST factory bootloader UART */

/* Define available ports */
#define _P1 
#define _P2 
#define _P3 
#define _P4 
#define _P5 
#define _P6

/* Define available USARTs */
#define _Usart1 1
#define _Usart2 1
#define _Usart3 1
#define _Usart4 1
#define _Usart5 1
#define _Usart6	1


/* Port-UART mapping */

#define P1uart &huart4
#define P2uart &huart2
#define P3uart &huart3
#define P4uart &huart1
#define P5uart &huart5
#define P6uart &huart6


/* Port Definitions */
#define	USART1_TX_PIN		GPIO_PIN_9
#define	USART1_RX_PIN		GPIO_PIN_10
#define	USART1_TX_PORT		GPIOA
#define	USART1_RX_PORT		GPIOA
#define	USART1_AF			GPIO_AF1_USART1

#define	USART2_TX_PIN		GPIO_PIN_2
#define	USART2_RX_PIN		GPIO_PIN_3
#define	USART2_TX_PORT		GPIOA
#define	USART2_RX_PORT		GPIOA
#define	USART2_AF			GPIO_AF1_USART2

#define	USART3_TX_PIN		GPIO_PIN_10
#define	USART3_RX_PIN		GPIO_PIN_11
#define	USART3_TX_PORT		GPIOB
#define	USART3_RX_PORT		GPIOB
#define	USART3_AF			GPIO_AF4_USART3

#define	USART4_TX_PIN		GPIO_PIN_0
#define	USART4_RX_PIN		GPIO_PIN_1
#define	USART4_TX_PORT		GPIOA
#define	USART4_RX_PORT		GPIOA
#define	USART4_AF			GPIO_AF4_USART4

#define	USART5_TX_PIN		GPIO_PIN_3
#define	USART5_RX_PIN		GPIO_PIN_2
#define	USART5_TX_PORT		GPIOD
#define	USART5_RX_PORT		GPIOD
#define	USART5_AF			GPIO_AF3_USART5

#define	USART6_TX_PIN		GPIO_PIN_8
#define	USART6_RX_PIN		GPIO_PIN_9
#define	USART6_TX_PORT		GPIOB
#define	USART6_RX_PORT		GPIOB
#define	USART6_AF			GPIO_AF8_USART6

/* Module-specific Definitions */

#define NUM_MODULE_PARAMS						1
#define _RGB_RED_PORT							GPIOA
#define _RGB_RED_PIN							GPIO_PIN_15
#define _RGB_RED_TIM_CH							TIM_CHANNEL_1
#define _RGB_RED_GPIO_CLK()						__GPIOA_CLK_ENABLE();
#define _RGB_GREEN_PORT							GPIOB
#define _RGB_GREEN_PIN							GPIO_PIN_7
#define _RGB_GREEN_TIM_CH						TIM_CHANNEL_2
#define _RGB_GREEN_GPIO_CLK()					__GPIOB_CLK_ENABLE();
#define _RGB_BLUE_PORT							GPIOA
#define _RGB_BLUE_PIN							GPIO_PIN_6
#define _RGB_BLUE_TIM_CH						TIM_CHANNEL_1
#define _RGB_BLUE_GPIO_CLK()					__GPIOA_CLK_ENABLE();

#define PWM_TIMER_CLOCK							122880			//freq 120 HZ at ARR 1023
#define RGB_PWM_FREQ							120
#define RGB_PWM_PERIOD							((float) (1/RGB_PWM_FREQ) )

/* Module EEPROM Variables */

// Module Addressing Space 500 - 599
#define _EE_MODULE							500		

/* Module_Status Type Definition */
typedef enum {
	H01R0_OK =0, H01R0_ERR_UnknownMessage, H01R0_ERR_WrongColor, H01R0_ERR_WrongIntensity, H01R0_ERR_WrongMode, H01R0_ERROR =255
} Module_Status;

/* Indicator LED */
#define _IND_LED_PORT			GPIOB
#define _IND_LED_PIN			GPIO_PIN_14

/* Export UART variables */
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart6;

/* Define UART Init prototypes */
extern void MX_USART1_UART_Init(void);
extern void MX_USART2_UART_Init(void);
extern void MX_USART3_UART_Init(void);
extern void MX_USART4_UART_Init(void);
extern void MX_USART5_UART_Init(void);
extern void MX_USART6_UART_Init(void);
extern void SystemClock_Config(void);
extern void ExecuteMonitor(void);




extern uint8_t RGB_LED_State, RGB_LED_Intensity_Old;
extern uint8_t rgbLedMode, rgbRed, rgbGreen, rgbBlue, rgbColor;
extern uint32_t rgbPeriod, rgbDC;
extern int16_t rgbCount;

/* -----------------------------------------------------------------------
 |								  APIs							          |  																 	|
/* -----------------------------------------------------------------------
 */
extern Module_Status startPWM(uint8_t red,uint8_t green,uint8_t blue,uint8_t intensity);
extern Module_Status RGB_LED_on(uint8_t intensity);
extern Module_Status RGB_LED_off(void);
extern Module_Status RGB_LED_toggle(uint8_t intensity);
extern Module_Status RGB_LED_setColor(uint8_t color,uint8_t intensity);
extern Module_Status RGB_LED_setRGB(uint8_t red,uint8_t green,uint8_t blue,uint8_t intensity);
extern Module_Status RGB_LED_pulseRGB(uint8_t red,uint8_t green,uint8_t blue,uint32_t period,uint32_t dc,int32_t repeat);
extern Module_Status RGB_LED_pulseColor(uint8_t color,uint32_t period,uint32_t dc,int32_t repeat);
extern Module_Status RGB_LED_sweep(uint8_t mode,uint32_t period,int32_t repeat);
extern Module_Status RGB_LED_dim(uint8_t color,uint8_t mode,uint32_t period,uint32_t wait,int32_t repeat);
void SetupPortForRemoteBootloaderUpdate(uint8_t port);
void remoteBootloaderUpdate(uint8_t src,uint8_t dst,uint8_t inport,uint8_t outport);

/* -----------------------------------------------------------------------
 |								Commands							      |															 	|
/* -----------------------------------------------------------------------
 */


#endif /* H01R0_H */

/************************ (C) COPYRIGHT HEXABITZ *****END OF FILE****/
