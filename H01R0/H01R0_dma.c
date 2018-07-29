/*
    BitzOS (BOS) V0.1.4 - Copyright (C) 2018 Hexabitz
    All rights reserved
		
    File Name     : H01R0_dma.c
    Description   : Peripheral DMA setup source file.
*/

/* Includes ------------------------------------------------------------------*/
#include "BOS.h"



/*----------------------------------------------------------------------------*/
/* Configure DMA                                                              */
/*----------------------------------------------------------------------------*/


/* Variables ---------------------------------------------------------*/

/* DMA structs. Number of structs depends on available DMA channels and array ports where some channels might be reconfigured. 
		- Update for non-standard MCUs 
*/
DMA_HandleTypeDef msgRxDMA1, msgRxDMA2, msgRxDMA3, msgRxDMA4, msgRxDMA5, msgRxDMA6;
DMA_HandleTypeDef msgTxDMA1, msgTxDMA2, msgTxDMA3;
DMA_HandleTypeDef streamDMA1, streamDMA2, streamDMA3, streamDMA4, streamDMA5, streamDMA6;
DMA_HandleTypeDef frontendDMA1, frontendDMA2, frontendDMA3;

UART_HandleTypeDef* dmaStreamDst[6] = {0};
uint32_t dmaStreamCount[6] = {0};
uint32_t dmaStreamTotal[6] = {0};

/* Private function prototypes -----------------------------------------------*/
void SetupDMAInterrupts(DMA_HandleTypeDef *hDMA, uint8_t priority);
void RemapAndLinkDMAtoUARTRx(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hDMA);
void RemapAndLinkDMAtoUARTTx(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hDMA);

/*-----------------------------------------------------------*/

/** 
  * Initialize the DMAs
  */
void DMA_Init(void) 
{
	/* DMA controller clock enable */
	__DMA1_CLK_ENABLE();
	__DMA2_CLK_ENABLE();
	
	/* Initialize messaging RX DMAs x 6 - Update for non-standard MCUs */
#ifdef _P1
	DMA_MSG_RX_CH_Init(&msgRxDMA1, DMA1_Channel1);
#endif
#ifdef _P2	
	DMA_MSG_RX_CH_Init(&msgRxDMA2, DMA1_Channel3);
#endif
#ifdef _P3		
	DMA_MSG_RX_CH_Init(&msgRxDMA3, DMA1_Channel5);
#endif
#ifdef _P4		
	DMA_MSG_RX_CH_Init(&msgRxDMA4, DMA1_Channel6);
#endif
#ifdef _P5		
	DMA_MSG_RX_CH_Init(&msgRxDMA5, DMA2_Channel2);
#endif
#ifdef _P6		
	DMA_MSG_RX_CH_Init(&msgRxDMA6, DMA2_Channel3);
#endif	

	/* Initialize messaging TX DMAs x 3 */
	DMA_MSG_TX_CH_Init(&msgTxDMA1, DMA1_Channel2);
	DMA_STREAM_CH_Init(&msgTxDMA2, DMA1_Channel4);
	DMA_STREAM_CH_Init(&msgTxDMA3, DMA1_Channel7);	
	
	/* Initialize streaming RX DMAs x 0 */
	// No more channels. Dynamically reconfigure from messaging RX DMAs.
	
	/* Initialize frontend DMAs x 3 */
	//DMA_FRONTEND_CH_Init(&frontendDMA1, DMA2_Channel5);
	
}

/*-----------------------------------------------------------*/
/* Initialization functions ---------------------------------*/
/*-----------------------------------------------------------*/

/* Initialize a messaging RX DMA channel */
void DMA_MSG_RX_CH_Init(DMA_HandleTypeDef *hDMA, DMA_Channel_TypeDef *ch)
{
	hDMA->Instance = ch;
	hDMA->Init.Direction = DMA_PERIPH_TO_MEMORY;
	hDMA->Init.PeriphInc = DMA_PINC_DISABLE;
	hDMA->Init.MemInc = DMA_MINC_ENABLE;
	hDMA->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hDMA->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hDMA->Init.Mode = DMA_CIRCULAR; 
	hDMA->Init.Priority = MSG_DMA_PRIORITY;
	
	HAL_DMA_Init(hDMA);		
}

/*-----------------------------------------------------------*/

/* Initialize a messaging TX DMA channel */
void DMA_MSG_TX_CH_Init(DMA_HandleTypeDef *hDMA, DMA_Channel_TypeDef *ch)
{
	hDMA->Instance = ch;
	hDMA->Init.Direction = DMA_MEMORY_TO_PERIPH;
	hDMA->Init.PeriphInc = DMA_PINC_DISABLE;
	hDMA->Init.MemInc = DMA_MINC_ENABLE;
	hDMA->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hDMA->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hDMA->Init.Mode = DMA_NORMAL; 
	hDMA->Init.Priority = MSG_DMA_PRIORITY;
	
	HAL_DMA_Init(hDMA);		
}

/*-----------------------------------------------------------*/

/* Initialize a streaming DMA channel (RX only) */
void DMA_STREAM_CH_Init(DMA_HandleTypeDef *hDMA, DMA_Channel_TypeDef *ch)
{
	hDMA->Instance = ch;
	hDMA->Init.Direction = DMA_PERIPH_TO_MEMORY;
	hDMA->Init.PeriphInc = DMA_PINC_DISABLE;
	hDMA->Init.MemInc = DMA_MINC_DISABLE;
	hDMA->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hDMA->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hDMA->Init.Mode = DMA_CIRCULAR; 
	hDMA->Init.Priority = STREAM_DMA_PRIORITY;
	
	HAL_DMA_Init(hDMA);		
}

/*-----------------------------------------------------------*/

/* Initialize a frontend DMA channel - modify based on frontend needs */
void DMA_FRONTEND_CH_Init(DMA_HandleTypeDef *hDMA, DMA_Channel_TypeDef *ch)
{
	hDMA->Instance = ch;
	hDMA->Init.Direction = DMA_PERIPH_TO_MEMORY;
	hDMA->Init.PeriphInc = DMA_PINC_DISABLE;
	hDMA->Init.MemInc = DMA_MINC_DISABLE;
	hDMA->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hDMA->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hDMA->Init.Mode = DMA_CIRCULAR; 
	hDMA->Init.Priority = FRONTEND_DMA_PRIORITY;
	
	HAL_DMA_Init(hDMA);		
}

/*-----------------------------------------------------------*/
/* Setup functions ------------------------------------------*/
/*-----------------------------------------------------------*/

/* Messaging DMA RX setup (port-to-memory) */
void DMA_MSG_RX_Setup(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hDMA)
{	
	/* Remap and link to UART Rx */
	RemapAndLinkDMAtoUARTRx(huart, hDMA);
	
	/* Setup DMA interrupts */
	SetupDMAInterrupts(hDMA, MSG_DMA_INT_PRIORITY);
	
	/* Start DMA stream	*/	
	HAL_UART_Receive_DMA(huart, (uint8_t *)&UARTRxBuf[GetPort(huart)-1], MSG_RX_BUF_SIZE);			
}

/*-----------------------------------------------------------*/

/* Messaging DMA TX setup (port-to-memory) */
void DMA_MSG_TX_Setup(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hDMA)
{	
	/* Remap and link to UART Tx */
	RemapAndLinkDMAtoUARTTx(huart, hDMA);
	
	/* Setup DMA interrupts */
	SetupDMAInterrupts(hDMA, MSG_DMA_INT_PRIORITY);
	
	/* Start DMA stream	when needed */	
}

/*-----------------------------------------------------------*/

/* Streaming DMA setup (port-to-port) */
void DMA_STREAM_Setup(uint8_t streamNum, UART_HandleTypeDef* huartSrc, UART_HandleTypeDef* huartDst, uint8_t num)
{	
	DMA_HandleTypeDef *hDMA;
	
	/* Select DMA struct */
	switch (streamNum)
	{
		case 1: hDMA = &streamDMA1; break;
		case 2: hDMA = &streamDMA2; break;
		case 3: hDMA = &streamDMA3; break;
		case 4: hDMA = &streamDMA4; break;
		case 5: hDMA = &streamDMA5; break;
		case 6: hDMA = &streamDMA6; break;
		default: break;
	}
	
	/* Remap and link to UART RX */
	RemapAndLinkDMAtoUARTRx(huartSrc, hDMA);
	
	/* Setup DMA interrupts */
	SetupDMAInterrupts(hDMA, STREAM_DMA_INT_PRIORITY);
	
	/* Start DMA stream	*/	
	dmaStreamDst[streamNum-1] = huartDst;
	huartSrc->State = HAL_UART_STATE_READY;
	HAL_UART_Receive_DMA(huartSrc, (uint8_t *)(&(huartDst->Instance->TDR)), num);
	
	/* Lock the ports */
	portStatus[GetPort(huartSrc)] = STREAM;
	portStatus[GetPort(huartDst)] = STREAM;
	
	/* Initialize counter */
	dmaStreamCount[streamNum-1] = 0;
}

/*-----------------------------------------------------------*/
/* Private functions ----------------------------------------*/
/*-----------------------------------------------------------*/

/* Setup DMA interrupts  */
void SetupDMAInterrupts(DMA_HandleTypeDef *hDMA, uint8_t priority)
{
	switch ((uint32_t)hDMA->Instance)
	{
		case (uint32_t)DMA1_Channel1:
			HAL_NVIC_SetPriority(DMA1_Ch1_IRQn, priority, 0);
			HAL_NVIC_EnableIRQ(DMA1_Ch1_IRQn);	
			break;
		
		case (uint32_t)DMA1_Channel2:
		case (uint32_t)DMA1_Channel3:
		case (uint32_t)DMA2_Channel1:
		case (uint32_t)DMA2_Channel2:
			HAL_NVIC_SetPriority(DMA1_Ch2_3_DMA2_Ch1_2_IRQn, priority, 0);
			HAL_NVIC_EnableIRQ(DMA1_Ch2_3_DMA2_Ch1_2_IRQn);				
			break;
			
		case (uint32_t)DMA1_Channel4:
		case (uint32_t)DMA1_Channel5:
		case (uint32_t)DMA1_Channel6:
		case (uint32_t)DMA1_Channel7:
		case (uint32_t)DMA2_Channel3:
		case (uint32_t)DMA2_Channel4:
		case (uint32_t)DMA2_Channel5:
			HAL_NVIC_SetPriority(DMA1_Ch4_7_DMA2_Ch3_5_IRQn, priority, 0);
			HAL_NVIC_EnableIRQ(DMA1_Ch4_7_DMA2_Ch3_5_IRQn);			
			break;
		
		default:
			break;
	}			
}

/*-----------------------------------------------------------*/

/* --- Stop a DMA stream --- 
*/
void StopStreamDMA(uint8_t streamNum)
{
	DMA_HandleTypeDef *hDMA;
	
	/* Select DMA struct */
	switch (streamNum)
	{
		case 1: hDMA = &streamDMA1; break;
		case 2: hDMA = &streamDMA2; break;
		case 3: hDMA = &streamDMA3; break;
		case 4: hDMA = &streamDMA4; break;
		case 5: hDMA = &streamDMA5; break;
		case 6: hDMA = &streamDMA6; break;
		default: break;
	}
	
	HAL_DMA_Abort(hDMA);
	hDMA->Instance->CNDTR = 0;
	dmaStreamCount[streamNum-1] = 0;
	dmaStreamTotal[streamNum-1] = 0;
	portStatus[GetPort(hDMA->Parent)] = FREE; 
	portStatus[GetPort(dmaStreamDst[streamNum-1])] = FREE;	
	
	/* Read these ports again */
	HAL_UART_Receive_IT(hDMA->Parent, (uint8_t *)&cRxedChar, 1);		// TODO update
	HAL_UART_Receive_IT(dmaStreamDst[streamNum-1], (uint8_t *)&cRxedChar, 1);
	dmaStreamDst[streamNum-1] = 0;	
}


/*-----------------------------------------------------------*/

/* Remap and link the UART RX and DMA structs */
void RemapAndLinkDMAtoUARTRx(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hDMA)
{
	// USART 1
	if (huart->Instance == USART1 && hDMA->Instance == DMA1_Channel1) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH1_USART1_RX);
	} else if (huart->Instance == USART1 && hDMA->Instance == DMA1_Channel3) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH3_USART1_RX);
	} else if (huart->Instance == USART1 && hDMA->Instance == DMA1_Channel5) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH5_USART1_RX);		
	} else if (huart->Instance == USART1 && hDMA->Instance == DMA1_Channel6) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH6_USART1_RX);	
	} else if (huart->Instance == USART1 && hDMA->Instance == DMA2_Channel2) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH2_USART1_RX);	
	} else if (huart->Instance == USART1 && hDMA->Instance == DMA2_Channel3) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH3_USART1_RX);	
	// USART 2	
	} else if (huart->Instance == USART2 && hDMA->Instance == DMA1_Channel1) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH1_USART2_RX);
	} else if (huart->Instance == USART2 && hDMA->Instance == DMA1_Channel3) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH3_USART2_RX);
	} else if (huart->Instance == USART2 && hDMA->Instance == DMA1_Channel5) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH5_USART2_RX);		
	} else if (huart->Instance == USART2 && hDMA->Instance == DMA1_Channel6) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH6_USART2_RX);	
	} else if (huart->Instance == USART2 && hDMA->Instance == DMA2_Channel2) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH2_USART2_RX);	
	} else if (huart->Instance == USART2 && hDMA->Instance == DMA2_Channel3) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH3_USART2_RX);	
	// USART 3	
	} else if (huart->Instance == USART3 && hDMA->Instance == DMA1_Channel1) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH1_USART3_RX);
	} else if (huart->Instance == USART3 && hDMA->Instance == DMA1_Channel3) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH3_USART3_RX);
	} else if (huart->Instance == USART3 && hDMA->Instance == DMA1_Channel5) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH5_USART3_RX);		
	} else if (huart->Instance == USART3 && hDMA->Instance == DMA1_Channel6) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH6_USART3_RX);	
	} else if (huart->Instance == USART3 && hDMA->Instance == DMA2_Channel2) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH2_USART3_RX);	
	} else if (huart->Instance == USART3 && hDMA->Instance == DMA2_Channel3) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH3_USART3_RX);			
	// USART 4	
	} else if (huart->Instance == USART4 && hDMA->Instance == DMA1_Channel1) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH1_USART4_RX);
	} else if (huart->Instance == USART4 && hDMA->Instance == DMA1_Channel3) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH3_USART4_RX);
	} else if (huart->Instance == USART4 && hDMA->Instance == DMA1_Channel5) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH5_USART4_RX);		
	} else if (huart->Instance == USART4 && hDMA->Instance == DMA1_Channel6) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH6_USART4_RX);	
	} else if (huart->Instance == USART4 && hDMA->Instance == DMA2_Channel2) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH2_USART4_RX);	
	} else if (huart->Instance == USART4 && hDMA->Instance == DMA2_Channel3) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH3_USART4_RX);				
	// USART 5	
	} else if (huart->Instance == USART5 && hDMA->Instance == DMA1_Channel1) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH1_USART5_RX);
	} else if (huart->Instance == USART5 && hDMA->Instance == DMA1_Channel3) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH3_USART5_RX);
	} else if (huart->Instance == USART5 && hDMA->Instance == DMA1_Channel5) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH5_USART5_RX);		
	} else if (huart->Instance == USART5 && hDMA->Instance == DMA1_Channel6) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH6_USART5_RX);	
	} else if (huart->Instance == USART5 && hDMA->Instance == DMA2_Channel2) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH2_USART5_RX);	
	} else if (huart->Instance == USART5 && hDMA->Instance == DMA2_Channel3) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH3_USART5_RX);					
	// USART 6	
	} else if (huart->Instance == USART6 && hDMA->Instance == DMA1_Channel1) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH1_USART6_RX);
	} else if (huart->Instance == USART6 && hDMA->Instance == DMA1_Channel3) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH3_USART6_RX);
	} else if (huart->Instance == USART6 && hDMA->Instance == DMA1_Channel5) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH5_USART6_RX);		
	} else if (huart->Instance == USART6 && hDMA->Instance == DMA1_Channel6) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH6_USART6_RX);	
	} else if (huart->Instance == USART6 && hDMA->Instance == DMA2_Channel2) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH2_USART6_RX);	
	} else if (huart->Instance == USART6 && hDMA->Instance == DMA2_Channel3) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH3_USART6_RX);					
	// USART 7	
	} else if (huart->Instance == USART7 && hDMA->Instance == DMA1_Channel1) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH1_USART7_RX);
	} else if (huart->Instance == USART7 && hDMA->Instance == DMA1_Channel3) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH3_USART7_RX);
	} else if (huart->Instance == USART7 && hDMA->Instance == DMA1_Channel5) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH5_USART7_RX);		
	} else if (huart->Instance == USART7 && hDMA->Instance == DMA1_Channel6) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH6_USART7_RX);	
	} else if (huart->Instance == USART7 && hDMA->Instance == DMA2_Channel2) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH2_USART7_RX);	
	} else if (huart->Instance == USART7 && hDMA->Instance == DMA2_Channel3) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH3_USART7_RX);				
	// USART 8	
	} else if (huart->Instance == USART8 && hDMA->Instance == DMA1_Channel1) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH1_USART8_RX);
	} else if (huart->Instance == USART8 && hDMA->Instance == DMA1_Channel3) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH3_USART8_RX);
	} else if (huart->Instance == USART8 && hDMA->Instance == DMA1_Channel5) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH5_USART8_RX);		
	} else if (huart->Instance == USART8 && hDMA->Instance == DMA1_Channel6) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH6_USART8_RX);	
	} else if (huart->Instance == USART8 && hDMA->Instance == DMA2_Channel2) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH2_USART8_RX);	
	} else if (huart->Instance == USART8 && hDMA->Instance == DMA2_Channel3) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH3_USART8_RX);					
	}		
	
	__HAL_LINKDMA(huart,hdmarx,*hDMA);	
}

/*-----------------------------------------------------------*/

/* Remap and link the UART TX and DMA structs */
void RemapAndLinkDMAtoUARTTx(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hDMA)
{
	// USART 1
	if (huart->Instance == USART1 && hDMA->Instance == DMA1_Channel2) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH2_USART1_TX);
	} else if (huart->Instance == USART1 && hDMA->Instance == DMA1_Channel4) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH4_USART1_TX);
	} else if (huart->Instance == USART1 && hDMA->Instance == DMA1_Channel7) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH7_USART1_TX);		
	} else if (huart->Instance == USART1 && hDMA->Instance == DMA2_Channel1) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH1_USART1_TX);	
	} else if (huart->Instance == USART1 && hDMA->Instance == DMA2_Channel4) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH4_USART1_TX);	
	} else if (huart->Instance == USART1 && hDMA->Instance == DMA2_Channel5) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH5_USART1_TX);	
	// USART 2	
	} else if (huart->Instance == USART2 && hDMA->Instance == DMA1_Channel2) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH2_USART2_TX);
	} else if (huart->Instance == USART2 && hDMA->Instance == DMA1_Channel4) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH4_USART2_TX);
	} else if (huart->Instance == USART2 && hDMA->Instance == DMA1_Channel7) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH7_USART2_TX);		
	} else if (huart->Instance == USART2 && hDMA->Instance == DMA2_Channel1) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH1_USART2_TX);	
	} else if (huart->Instance == USART2 && hDMA->Instance == DMA2_Channel4) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH4_USART2_TX);	
	} else if (huart->Instance == USART2 && hDMA->Instance == DMA2_Channel5) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH5_USART2_TX);	
	// USART 3	
	} else if (huart->Instance == USART3 && hDMA->Instance == DMA1_Channel2) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH2_USART3_TX);
	} else if (huart->Instance == USART3 && hDMA->Instance == DMA1_Channel4) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH4_USART3_TX);
	} else if (huart->Instance == USART3 && hDMA->Instance == DMA1_Channel7) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH7_USART3_TX);		
	} else if (huart->Instance == USART3 && hDMA->Instance == DMA2_Channel1) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH1_USART3_TX);	
	} else if (huart->Instance == USART3 && hDMA->Instance == DMA2_Channel4) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH4_USART3_TX);	
	} else if (huart->Instance == USART3 && hDMA->Instance == DMA2_Channel5) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH5_USART3_TX);			
	// USART 4	
	} else if (huart->Instance == USART4 && hDMA->Instance == DMA1_Channel2) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH2_USART4_TX);
	} else if (huart->Instance == USART4 && hDMA->Instance == DMA1_Channel4) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH4_USART4_TX);
	} else if (huart->Instance == USART4 && hDMA->Instance == DMA1_Channel7) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH7_USART4_TX);		
	} else if (huart->Instance == USART4 && hDMA->Instance == DMA2_Channel1) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH1_USART4_TX);	
	} else if (huart->Instance == USART4 && hDMA->Instance == DMA2_Channel4) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH4_USART4_TX);	
	} else if (huart->Instance == USART4 && hDMA->Instance == DMA2_Channel5) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH5_USART4_TX);				
	// USART 5	
	} else if (huart->Instance == USART5 && hDMA->Instance == DMA1_Channel2) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH2_USART5_TX);
	} else if (huart->Instance == USART5 && hDMA->Instance == DMA1_Channel4) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH4_USART5_TX);
	} else if (huart->Instance == USART5 && hDMA->Instance == DMA1_Channel7) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH7_USART5_TX);		
	} else if (huart->Instance == USART5 && hDMA->Instance == DMA2_Channel1) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH1_USART5_TX);	
	} else if (huart->Instance == USART5 && hDMA->Instance == DMA2_Channel4) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH4_USART5_TX);	
	} else if (huart->Instance == USART5 && hDMA->Instance == DMA2_Channel5) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH5_USART5_TX);					
	// USART 6	
	} else if (huart->Instance == USART6 && hDMA->Instance == DMA1_Channel2) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH2_USART6_TX);
	} else if (huart->Instance == USART6 && hDMA->Instance == DMA1_Channel4) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH4_USART6_TX);
	} else if (huart->Instance == USART6 && hDMA->Instance == DMA1_Channel7) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH7_USART6_TX);		
	} else if (huart->Instance == USART6 && hDMA->Instance == DMA2_Channel1) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH1_USART6_TX);	
	} else if (huart->Instance == USART6 && hDMA->Instance == DMA2_Channel4) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH4_USART6_TX);	
	} else if (huart->Instance == USART6 && hDMA->Instance == DMA2_Channel5) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH5_USART6_TX);					
	// USART 7	
	} else if (huart->Instance == USART7 && hDMA->Instance == DMA1_Channel2) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH2_USART7_TX);
	} else if (huart->Instance == USART7 && hDMA->Instance == DMA1_Channel4) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH4_USART7_TX);
	} else if (huart->Instance == USART7 && hDMA->Instance == DMA1_Channel7) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH7_USART7_TX);		
	} else if (huart->Instance == USART7 && hDMA->Instance == DMA2_Channel1) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH1_USART7_TX);	
	} else if (huart->Instance == USART7 && hDMA->Instance == DMA2_Channel4) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH4_USART7_TX);	
	} else if (huart->Instance == USART7 && hDMA->Instance == DMA2_Channel5) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH5_USART7_TX);				
	// USART 8	
	} else if (huart->Instance == USART8 && hDMA->Instance == DMA1_Channel2) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH2_USART8_TX);
	} else if (huart->Instance == USART8 && hDMA->Instance == DMA1_Channel4) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH4_USART8_TX);
	} else if (huart->Instance == USART8 && hDMA->Instance == DMA1_Channel7) {
		__HAL_DMA1_REMAP(HAL_DMA1_CH7_USART8_TX);		
	} else if (huart->Instance == USART8 && hDMA->Instance == DMA2_Channel1) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH1_USART8_TX);	
	} else if (huart->Instance == USART8 && hDMA->Instance == DMA2_Channel4) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH4_USART8_TX);	
	} else if (huart->Instance == USART8 && hDMA->Instance == DMA2_Channel5) {
		__HAL_DMA2_REMAP(HAL_DMA2_CH5_USART8_TX);					
	}		
	
	__HAL_LINKDMA(huart,hdmatx,*hDMA);	
}

/*-----------------------------------------------------------*/



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
