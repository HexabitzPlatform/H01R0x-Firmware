/*
 BitzOS (BOS) V0.3.6 - Copyright (C) 2017-2024 Hexabitz
 All rights reserved

 File Name     : BOS_eeprom.c
 Description   : Source code for providing all the EEPROM emulation firmware functions.

 */
/* Includes ------------------------------------------------------------------*/
#include "BOS.h"
#include "H01R0_eeprom.h"
#include "eeprom_emul.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Variables used for Erase pages under interruption */
extern FLASH_ProcessTypeDef pFlash;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Restore the pages to a known good state in case of page's status
 *   corruption after a power loss.
 * @param  None.
 * @retval - Flash error code: on write Flash error
 *         - FLASH_COMPLETE: on success
 */
uint16_t EE_Init(void){
	HAL_FLASH_Unlock();
	if(EE_OK != EEPROM_Init(EE_FORCED_ERASE))
		return HAL_ERROR;
	HAL_FLASH_Lock();
	return HAL_OK;
}

/**
 * @brief  Returns the last stored variable data, if found, which correspond to
 *   the passed virtual address
 * @param  VirtAddress: Variable virtual address
 * @param  Data: Global variable contains the read variable value
 * @retval Success or error status:
 *           - EE_OK.
 *           - EE_INVALID_VIRTUALADDRESS.
 *           - EE_ERROR_NOACTIVE_PAGE.
 */
uint16_t EE_ReadVariable(uint16_t VirtAddress,uint16_t *Data){

	uint16_t ReadStatus = 0;
	ReadStatus = EE_ReadVariable16bits(VirtAddress, Data);
	if(EE_OK == ReadStatus)
		return EE_OK;
	else if(EE_INVALID_VIRTUALADDRESS == ReadStatus)
		return EE_INVALID_VIRTUALADDRESS;
	else if(EE_ERROR_NOACTIVE_PAGE == ReadStatus)
		return EE_ERROR_NOACTIVE_PAGE;
	else
		return ReadStatus;
}

/**
 * @brief  Writes/upadtes variable data in EEPROM.
 * @param  VirtAddress: Variable virtual address
 * @param  Data: 16 bit data to be written
 * @retval Success or error status:
 *           - EE_OK.
 *           - EE_INVALID_VIRTUALADDRESS.
 *           - EE_PAGE_FULL.
 */
uint16_t EE_WriteVariable(uint16_t VirtAddress,uint16_t Data){

	uint16_t WriteStatus = 0;
	HAL_FLASH_Unlock();

	WriteStatus = EE_WriteVariable16bits(VirtAddress, Data);
	if(EE_OK == WriteStatus)
		return EE_OK;
	else if(EE_INVALID_VIRTUALADDRESS == WriteStatus)
		return EE_INVALID_VIRTUALADDRESS;
	else if(EE_PAGE_FULL == WriteStatus)
		return EE_PAGE_FULL;
	else
		return WriteStatus;

	HAL_FLASH_Lock();
}

/**
 * @brief  Erases PAGEA and PAGEB and writes VALID_PAGE header to PAGEA
 * @param  None
 * @retval Status of the last operation (Flash write or erase) done during
 *         EEPROM formating
 */
uint16_t EE_Format(void){
	HAL_StatusTypeDef FlashStatus =HAL_OK;
	HAL_FLASH_Unlock();
	if(EE_ERASE_ERROR != EEPROM_Format(EE_FORCED_ERASE))
	{
		HAL_FLASH_Lock();
		return FlashStatus =HAL_OK;
	}
	else
	{
		HAL_FLASH_Lock();
		return FlashStatus =HAL_ERROR;
	}

}

/**
 * @brief  Writes/upadtes variable data in Flash.
 * @param  Address: Variable address
 * @param  Data: 16 bit data to be written
 * @retval Success or error status:
 *           - FLASH_COMPLETE: on success
 *           - PAGE_FULL: if valid page is full
 *           - NO_VALID_PAGE: if no valid page was found
 *           - Flash error code: on write Flash error
 */
uint16_t Flash_WriteVariable(uint32_t Address,uint16_t Data){
	HAL_StatusTypeDef FlashStatus =HAL_OK;
	
	HAL_FLASH_Unlock();
	
	/* Set variable data */
	//HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,Address,Data);
	//TOBECHECKED
	/* Wait for last operation to be completed */
	FlashStatus =FLASH_WaitForLastOperation((uint32_t )HAL_FLASH_TIMEOUT_VALUE);
	/* If program operation was failed, a Flash error code is returned */
	if(FlashStatus != HAL_OK){
		return pFlash.ErrorCode;
	}
	else{
		/* If the program operation is completed, disable the PG Bit */
		CLEAR_BIT(FLASH->CR,FLASH_CR_PG);
	}
	
	HAL_FLASH_Lock();
	
	/* Return last operation flash status */
	return FlashStatus;
}

/* Erase sector if force write is requested */
BOS_Status EraseSector(uint32_t sector ) {
	BOS_Status result = BOS_OK;
	HAL_StatusTypeDef status;

		FLASH_EraseInitTypeDef erase;
		uint32_t eraseError;
		erase.TypeErase = FLASH_TYPEERASE_PAGES;
		//erase.PageAddress =sector;
		erase.Page =sector;
		//TOBECHECKED
		erase.NbPages =1;
		status =HAL_FLASHEx_Erase(&erase,&eraseError);
		if(status != HAL_OK || eraseError != 0xFFFFFFFF)
			responseStatus =BOS_ERR_REMOTE_WRITE_FLASH;

	return result;
}


/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
