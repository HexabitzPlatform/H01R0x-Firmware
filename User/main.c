/*
 BitzOS (BOS) V0.3.6 - Copyright (C) 2017-2024 Hexabitz
 All rights reserved

 File Name     : main.c
 Description   : Main program body.
 */
/* Includes ------------------------------------------------------------------*/
#include "BOS.h"
#include "eeprom_emul.h"
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Main function ------------------------------------------------------------*/
	uint16_t DataR[500] = {0};
int main(void) {

	Module_Init();		//Initialize Module &  BitzOS
//	HAL_FLASH_Unlock();
	uint8_t pages = PAGES_NUMBER;
//	EE_Format();
	EE_Init();

	uint16_t Data = 50;

    uint32_t counter = 0;

	EE_WriteVariable(_EE_NBASE,Data);
	EE_ReadVariable(_EE_NBASE,&DataR[0]);

	memset(DataR,0,500);
	//2
    for(int i=0; i<25; i++)
    {
    		EE_WriteVariable(_EE_PORT_DIR_BASE+i,i);
    }

    for(int i=0; i<25; i++)
    {
    		EE_ReadVariable(_EE_PORT_DIR_BASE+i,&DataR[i]);
    }

    memset(DataR,0,500);
    //28
    for(int i=0; i<125; i++)
    {
    		EE_WriteVariable(_EE_ALIAS_BASE+i,i);
    }

    for(int i=0; i<125; i++)
    {
    		EE_ReadVariable(_EE_ALIAS_BASE+i,&DataR[i]);
    }

    memset(DataR,0,500);
    //153
    for(int i=0; i<50; i++)
    {
    		EE_WriteVariable(_EE_GROUP_ALIAS_BASE+i,i);
    }

    for(int i=0; i<50; i++)
    {
    		EE_ReadVariable(_EE_GROUP_ALIAS_BASE+i,&DataR[i]);
    }

    memset(DataR,0,500);
    //203
    for(int i=0; i<25; i++)
    {
    		EE_WriteVariable(_EE_GROUP_MODULES_BASE+i,i);
    }
    for(int i=0; i<25; i++)
    {
    		EE_ReadVariable(_EE_GROUP_MODULES_BASE+i,&DataR[i]);
    }

    memset(DataR,0,500);
    //228
    for(int i=0; i<8; i++)
    {
    		EE_WriteVariable(_EE_DMA_STREAM_BASE+i,i);
    }

    for(int i=0; i<8; i++)
    {
    		EE_ReadVariable(_EE_DMA_STREAM_BASE+i,&DataR[i]);
    }

    memset(DataR,0,500);
    //236
    for(int i=0; i<40; i++)
    {
    		EE_WriteVariable(_EE_BUTTON_BASE+i,i);
    }

    for(int i=0; i<40; i++)
	{
			EE_ReadVariable(_EE_BUTTON_BASE+i,&DataR[i]);
	}

    memset(DataR,0,500);
    //280
    for(int i=0; i<2; i++)
    {
    		EE_WriteVariable(_EE_CLI_BAUD+i,i);
    }
    for(int i=0; i<2; i++)
    {
    		EE_ReadVariable(_EE_CLI_BAUD+i,&DataR[i]);
    }

    memset(DataR,0,500);
    //500
    for(int i=0; i<100; i++)
    {
    		EE_WriteVariable(_EE_MODULE_BASE+i,i);
    }

    for(int i=0; i<100; i++)
    {
    		EE_ReadVariable(_EE_MODULE_BASE+i,&DataR[i]);
    }

    memset(DataR,0,500);
    //600
    for(int i=0; i<424; i++)
    {
    		EE_WriteVariable(_EE_EMPTY_VAR_BASE+i,i);
    }

    for(int i=0; i<424; i++)
    {
    		EE_ReadVariable(_EE_EMPTY_VAR_BASE+i,&DataR[i]);
    }

//	Data = 20;
////	EE_WriteVariable(_EE_PORT_DIR_BASE,Data);
//	EE_ReadVariable(_EE_PORT_DIR_BASE,&DataR);
//
//	Data = 30;
////	EE_WriteVariable(_EE_ALIAS_BASE,Data);
//	EE_ReadVariable(_EE_ALIAS_BASE,&DataR);
//
//	Data = 40;
////	EE_WriteVariable(_EE_GROUP_ALIAS_BASE,Data);
//	EE_ReadVariable(_EE_GROUP_ALIAS_BASE,&DataR);
//
//	Data = 50;
////	EE_WriteVariable(_EE_GROUP_MODULES_BASE,Data);
//	EE_ReadVariable(_EE_GROUP_MODULES_BASE,&DataR);
//
//	Data = 60;
////	EE_WriteVariable(_EE_DMA_STREAM_BASE,Data);
//	EE_ReadVariable(_EE_DMA_STREAM_BASE,&DataR);
//
//	Data = 70;
////	EE_WriteVariable(_EE_BUTTON_BASE,Data);
//	EE_ReadVariable(_EE_BUTTON_BASE,&DataR);
//
//	Data = 80;
////	EE_WriteVariable(_EE_PARAMS_BASE,Data);
//	EE_ReadVariable(_EE_PARAMS_BASE,&DataR);
//
//	Data = 90;
////	EE_WriteVariable(_EE_PARAMS_DEBOUNCE,Data);
//	EE_ReadVariable(_EE_PARAMS_DEBOUNCE,&DataR);
//
//	Data = 100;
////	EE_WriteVariable(_EE_PARAMS_SINGLE_CLICK,Data);
//	EE_ReadVariable(_EE_PARAMS_SINGLE_CLICK,&DataR);
//
//	Data = 110;
////	EE_WriteVariable(_EE_PARAMS_DBL_CLICK,Data);
//	EE_ReadVariable(_EE_PARAMS_DBL_CLICK,&DataR);
//
//	Data = 120;
////	EE_WriteVariable(_EE_CLI_BAUD,Data);
//	EE_ReadVariable(_EE_CLI_BAUD,&DataR);
//
//	Data = 130;
////	EE_WriteVariable(_EE_PARAMS_RTC,Data);
//	EE_ReadVariable(_EE_PARAMS_RTC,&DataR);
//
//	Data = 140;
////	EE_WriteVariable(_EE_PARAMS_DISABLE_CLI,Data);
//	EE_ReadVariable(_EE_PARAMS_DISABLE_CLI,&DataR);
//
//	Data = 150;
////	EE_WriteVariable(_EE_PARAMS_Messaging,Data);
//	EE_ReadVariable(_EE_PARAMS_Messaging,&DataR);
//
//
//	Data = 200;
//	EE_WriteVariable(5000,Data);
//	EE_ReadVariable(5000,&DataR);



//	for(int i = 1; i<2040; i++)
//	{
//			EE_WriteVariable(i,Data);
//			counter++;
////			EE_ReadVariable(i,&DataR);
//	}
//	counter = 0;
//	for(int i = 1; i<2040; i++)
//	{
//			EE_WriteVariable(i,Data);
//			counter++;
////			EE_ReadVariable(i,&DataR);
//	}
//	counter = 0;
//	for(int i = 1; i<2040; i++)
//	{
//			EE_WriteVariable(i,Data);
//			counter++;
////			EE_ReadVariable(i,&DataR);
//	}
//	counter = 0;
//	for(int i = 1; i<2040; i++)
//	{
//			EE_WriteVariable(i,Data);
//			counter++;
////			EE_ReadVariable(i,&DataR);
//	}




//	for(int i = 1; i<2040; i++)
//	{
//			EE_WriteVariable(i,Data);
//			EE_ReadVariable(i,&DataR);
//	}
//
//	for(int i = 1; i<2040; i++)
//	{
//			EE_WriteVariable(i,Data);
//			EE_ReadVariable(i,&DataR);
//	}
//
//	for(int i = 1; i<2040; i++)
//	{
//			EE_WriteVariable(i,Data);
//			EE_ReadVariable(i,&DataR);
//	}
//
//	for(int i = 1; i<2040; i++)
//	{
//			EE_WriteVariable(i,Data);
//			EE_ReadVariable(i,&DataR);
//	}

//	HAL_FLASH_Lock();
	//Don't place your code here.
	for (;;) {
	}
}

/*-----------------------------------------------------------*/

/* User Task */
void UserTask(void *argument) {

	// put your code here, to run repeatedly.
	while (1) {

	}
}

/*-----------------------------------------------------------*/
