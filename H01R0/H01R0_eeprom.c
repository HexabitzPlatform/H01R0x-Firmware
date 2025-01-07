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

/* Global variable used to store variable value in read sequence */
uint16_t DataVar =0;

/* Variables used for Erase pages under interruption */
extern FLASH_ProcessTypeDef pFlash;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static uint16_t EE_VerifyPageFullWriteVariable(uint16_t VirtAddress,uint16_t Data);
static uint16_t EE_PageTransfer(uint16_t VirtAddress,uint16_t Data);
static uint16_t EE_FindValidPage(uint8_t Operation);


/**
 * @brief  Restore the pages to a known good state in case of page's status
 *   corruption after a power loss.
 * @param  None.
 * @retval - Flash error code: on write Flash error
 *         - FLASH_COMPLETE: on success
 */
uint16_t EE_Init(void){
	if(EE_OK != EEPROM_Init(EE_FORCED_ERASE))
		return HAL_ERROR;
	return HAL_OK;
}

/**
 * @brief  Returns the last stored variable data, if found, which correspond to
 *   the passed virtual address
 * @param  VirtAddress: Variable virtual address
 * @param  Data: Global variable contains the read variable value
 * @retval Success or error status:
 *           - 0: if variable was found
 *           - 1: if the variable was not found
 *           - NO_VALID_PAGE: if no valid page was found.
 */
uint16_t EE_ReadVariable(uint16_t VirtAddress,uint16_t *Data){
	uint16_t ReadStatus = 1;
	if(EE_INVALID_VIRTUALADDRESS != EE_ReadVariable16bits(VirtAddress, Data))
		return ReadStatus = 0;
	else
	/* Return ReadStatus value: (0: variable exist, 1: variable doesn't exist) */
		return ReadStatus = 1;
}

/**
 * @brief  Writes/upadtes variable data in EEPROM.
 * @param  VirtAddress: Variable virtual address
 * @param  Data: 16 bit data to be written
 * @retval Success or error status:
 *           - FLASH_COMPLETE: on success
 *           - PAGE_FULL: if valid page is full
 *           - NO_VALID_PAGE: if no valid page was found
 *           - Flash error code: on write Flash error
 */
uint16_t EE_WriteVariable(uint16_t VirtAddress,uint16_t Data){
	uint16_t Status =0;
	HAL_FLASH_Unlock();
	if(EE_INVALID_VIRTUALADDRESS != EE_WriteVariable16bits(VirtAddress, Data))
		return Status = 0;
	else
		return Status = 1;
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
	if(EE_ERASE_ERROR != EEPROM_Format(EE_FORCED_ERASE))
		return FlashStatus =HAL_OK;
	else
		return FlashStatus =HAL_ERROR;
}

/**
 * @brief  Find valid Page for write or read operation
 * @param  Operation: operation to achieve on the valid page.
 *   This parameter can be one of the following values:
 *     @arg READ_FROM_VALID_PAGE: read operation from valid page
 *     @arg WRITE_IN_VALID_PAGE: write operation from valid page
 * @retval Valid page number (PAGEA or PAGEB) or NO_VALID_PAGE in case
 *   of no valid page was found
 */
static uint16_t EE_FindValidPage(uint8_t Operation){
	uint32_t PageStatusA =6, PageStatusB =6;
	
	/* Get PageA actual status */
	PageStatusA =(*(__IO uint16_t* )PAGEA1_BASE_ADDRESS);
	
	/* Get PageB actual status */
	PageStatusB =(*(__IO uint16_t* )PAGEB1_BASE_ADDRESS);
	
	/* Write or read operation */
	switch(Operation){
		case WRITE_IN_VALID_PAGE: /* ---- Write operation ---- */
			if(PageStatusB == VALID_PAGE){
				/* PageA receiving data */
				if(PageStatusA == RECEIVE_DATA){
					return PAGEA; /* PageA valid */
				}
				else{
					return PAGEB; /* PageB valid */
				}
			}
			else if(PageStatusA == VALID_PAGE){
				/* PageB receiving data */
				if(PageStatusB == RECEIVE_DATA){
					return PAGEB; /* PageB valid */
				}
				else{
					return PAGEA; /* PageA valid */
				}
			}
			else{
				return NO_VALID_PAGE; /* No valid Page */
			}
			
		case READ_FROM_VALID_PAGE: /* ---- Read operation ---- */
			if(PageStatusA == VALID_PAGE){
				return PAGEA; /* PageA valid */
			}
			else if(PageStatusB == VALID_PAGE){
				return PAGEB; /* PageB valid */
			}
			else{
				return NO_VALID_PAGE; /* No valid Page */
			}
			
		default:
			return PAGEA; /* PageA valid */
	}
}

/**
 * @brief  Verify if active page is full and Writes variable in EEPROM.
 * @param  VirtAddress: 16 bit virtual address of the variable
 * @param  Data: 16 bit data to be written as variable value
 * @retval Success or error status:
 *           - FLASH_COMPLETE: on success
 *           - PAGE_FULL: if valid page is full
 *           - NO_VALID_PAGE: if no valid page was found
 *           - Flash error code: on write Flash error
 */
static uint16_t EE_VerifyPageFullWriteVariable(uint16_t VirtAddress,uint16_t Data){
	HAL_StatusTypeDef FlashStatus =HAL_OK;
	uint16_t ValidPage = PAGEA;
	uint32_t Address =0, PageEndAddress =0;
	
	HAL_FLASH_Unlock();
	
	/* Get valid Page for write operation */
	ValidPage =EE_FindValidPage(WRITE_IN_VALID_PAGE);
	
	/* Check if there is no valid page */
	if(ValidPage == NO_VALID_PAGE){
		return NO_VALID_PAGE;
	}
	
	/* Get the valid Page start Address */
	Address =(uint32_t )(EEPROM_START_ADDRESS + (uint32_t )(ValidPage * PAGE_SIZE));
	
	/* Get the valid Page end Address - Each page is twice pages size */
	PageEndAddress =(uint32_t )((EEPROM_START_ADDRESS - 2) + (uint32_t )((2 + ValidPage) * PAGE_SIZE));
	
	/* Check each active page address starting from begining */
	while(Address < PageEndAddress){
		/* Verify if Address and Address+2 contents are 0xFFFFFFFF */
		if((*(__IO uint32_t* )Address) == 0xFFFFFFFF){
			/* Set variable data */
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,Address,Data);
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
			
			/* Set variable virtual address */
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,Address + 8,VirtAddress);
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
			
			/* Return program operation status */
			return pFlash.ErrorCode;
		}
		else{
			/* Next address location */
			Address =Address + 8;
		}
	}
	
	HAL_FLASH_Lock();
	
	/* Return PAGE_FULL in case the valid page is full */
	return PAGE_FULL;
}

/**
 * @brief  Transfers last updated variables data from the full Page to
 *   an empty one.
 * @param  VirtAddress: 16 bit virtual address of the variable
 * @param  Data: 16 bit data to be written as variable value
 * @retval Success or error status:
 *           - FLASH_COMPLETE: on success
 *           - PAGE_FULL: if valid page is full
 *           - NO_VALID_PAGE: if no valid page was found
 *           - Flash error code: on write Flash error
 */
static uint16_t EE_PageTransfer(uint16_t VirtAddress,uint16_t Data){
	HAL_StatusTypeDef FlashStatus =HAL_OK;
	uint32_t NewPageAddress =0, OldPageAddress =0;
	uint16_t ValidPage = PAGEA, VarIdx =0;
	uint16_t EepromStatus =0, ReadStatus =0;
	
	HAL_FLASH_Unlock();
	
	/* Get active Page for read operation */
	ValidPage =EE_FindValidPage(READ_FROM_VALID_PAGE);
	
	if(ValidPage == PAGEB) /* PageB valid */
	{
		/* New page address where variable will be moved to */
		NewPageAddress = PAGEA1_BASE_ADDRESS;
		
		/* Old page address where variable will be taken from */
		OldPageAddress = PAGEB1_BASE_ADDRESS;
	}
	else if(ValidPage == PAGEA) /* PageA valid */
	{
		/* New page address where variable will be moved to */
		NewPageAddress = PAGEB1_BASE_ADDRESS;
		
		/* Old page address where variable will be taken from */
		OldPageAddress = PAGEA1_BASE_ADDRESS;
	}
	else{
		return NO_VALID_PAGE; /* No valid Page */
	}
	
	/* Set the new Page status to RECEIVE_DATA status */
	//HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,NewPageAddress,RECEIVE_DATA);
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
	
	/* Write the variable passed as parameter in the new active page */
	EepromStatus =EE_VerifyPageFullWriteVariable(VirtAddress,Data);
	/* If program operation was failed, a Flash error code is returned */
	if(EepromStatus != HAL_OK){
		return EepromStatus;
	}
	
	/* Transfer process: transfer variables from old to the new active page */
	for(VarIdx =1; VarIdx <= NumOfEEPROMvar; VarIdx++){
		if(VarIdx != VirtAddress) /* Check each variable except the one passed as parameter */
		{
			/* Read the other last variable updates */
			ReadStatus =EE_ReadVariable(VarIdx,&DataVar);
			/* In case variable corresponding to the virtual address was found */
			if(ReadStatus != 0x1){
				/* Transfer the variable to the new active page */
				EepromStatus =EE_VerifyPageFullWriteVariable(VarIdx,DataVar);
				/* If program operation was failed, a Flash error code is returned */
				if(EepromStatus != HAL_OK){
					return EepromStatus;
				}
			}
		}
	}
	
	/* Erase the old Page: Set old Page status to ERASED status */
	FLASH_PageErase(FLASH_BANK_1,OldPageAddress);
	//TOBECHECKED
	/* Wait for last operation to be completed */
	FlashStatus =FLASH_WaitForLastOperation((uint32_t )HAL_FLASH_TIMEOUT_VALUE);
	/* If erase operation was failed, a Flash error code is returned */
	if(FlashStatus != HAL_OK){
		return pFlash.ErrorCode;
	}
	else{
		/* Erase the other half of the old Page: Set old Page status to ERASED status */
		FLASH_PageErase(FLASH_BANK_1,OldPageAddress + PAGE_SIZE);
		//TOBECHECKED
		FlashStatus =FLASH_WaitForLastOperation((uint32_t )HAL_FLASH_TIMEOUT_VALUE);
		if(FlashStatus != HAL_OK){
			return pFlash.ErrorCode;
		}
		else{
			/* Operation is completed, disable the PER Bit */
			CLEAR_BIT(FLASH->CR,FLASH_CR_PER);
		}
	}
	
	/* Set new Page status to VALID_PAGE status */
	//HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,NewPageAddress,VALID_PAGE);
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
