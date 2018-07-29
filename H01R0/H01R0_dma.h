/*
    BitzOS (BOS) V0.1.4 - Copyright (C) 2018 Hexabitz
    All rights reserved
		
    File Name     : H01R0_dma.h
    Description   : Peripheral DMA setup header file.
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef H01R0_dma_H
#define H01R0_dma_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
	 
	 
/* Check which DMA interrupt occured */	 
#define HAL_DMA_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  ((((__HANDLE__)->ISR & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)


/* External variables --------------------------------------------------------*/

/* Export DMA structs */
extern DMA_HandleTypeDef msgRxDMA1, msgRxDMA2, msgRxDMA3, msgRxDMA4, msgRxDMA5, msgRxDMA6;
extern DMA_HandleTypeDef msgTxDMA1;
extern DMA_HandleTypeDef streamRxDMA1, streamRxDMA2, streamRxDMA3, streamRxDMA4;
extern DMA_HandleTypeDef streamTxDMA1, streamTxDMA2, streamTxDMA3, streamTxDMA4;
extern DMA_HandleTypeDef frontendDMA1, frontendDMA2, frontendDMA3;
	 
/* External function prototypes ----------------------------------------------*/
extern void DMA_Init(void);
extern void DMA_MSG_RX_CH_Init(DMA_HandleTypeDef *hDMA, DMA_Channel_TypeDef *ch);
extern void DMA_MSG_TX_CH_Init(DMA_HandleTypeDef *hDMA, DMA_Channel_TypeDef *ch);
extern void DMA_STREAM_CH_Init(DMA_HandleTypeDef *hDMA, DMA_Channel_TypeDef *ch);
extern void DMA_MSG_RX_Setup(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hDMA);
extern void DMA_MSG_TX_Setup(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hDMA);
extern void StopStreamDMA(uint8_t streamNum);


#ifdef __cplusplus
}
#endif

#endif /* H01R0_dma_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
