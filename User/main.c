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
	uint16_t DataR[2500] = {0};
	uint32_t count = 0;
	uint32_t pagestatus119;
	uint32_t pagestatus121;
	uint32_t pagestatus122;
	uint32_t pagestatus123;
	uint32_t pagestatus124;
	uint32_t pagestatus125;
	uint32_t pagestatus126;
	uint32_t pagestatus127;
	uint32_t pages;
int main(void) {

	Module_Init();		//Initialize Module &  BitzOS
//	HAL_FLASH_Unlock();
	uint8_t pages = PAGES_NUMBER;
//	EE_Format();
	EE_Init();

	uint16_t Data = 50;

//	HAL_FLASH_Unlock();
//	pages = START_PAGE;
//	uint32_t pageaddress1 = PAGE_ADDRESS(pages+1);
//	 pagestatus119 = GetPageState(pageaddress1);
//
//	uint32_t pageaddress2 = PAGE_ADDRESS(pages+2);
//	 pagestatus121 = GetPageState(pageaddress2);
//
//	uint32_t pageaddress3 = PAGE_ADDRESS(pages+3);
//	 pagestatus122 = GetPageState(pageaddress3);
//
//	uint32_t pageaddress4 = PAGE_ADDRESS(pages+4);
//	 pagestatus123 = GetPageState(pageaddress4);
//
//	uint32_t pageaddress5 = PAGE_ADDRESS(pages+5);
//	 pagestatus124 = GetPageState(pageaddress5);
//
//	uint32_t pageaddress6 = PAGE_ADDRESS(pages+6);
//	 pagestatus125 = GetPageState(pageaddress6);
//
//	uint32_t pageaddress7 = PAGE_ADDRESS(pages+7);
//	 pagestatus126 = GetPageState(pageaddress7);
//
//	uint32_t pageaddress8 = PAGE_ADDRESS(pages+8);
//	 pagestatus127 = GetPageState(pageaddress8);
//
//	 HAL_FLASH_Lock();
//    for(int i =1 ;i<=1008;i++)
//    {
//    	EE_WriteVariable(i,i);
////    	EE_ReadVariable(i,&DataR[i]);
//    	count++;
//    }
    for(int i=1; i<1008; i++)
    {
    		EE_ReadVariable(i,&DataR[i]);
    }
//
//
//    count=0;
//    for(int i =1 ;i<=1000;i++)
//    {
//    	EE_WriteVariable(i,i);
//    	count++;
//    }
//    for(int i=1; i<1000; i++)
//    {
//    		EE_ReadVariable(i,&DataR[i]);
//    }
////    HAL_FLASH_Lock();
//	HAL_FLASH_Unlock();
//	pages = START_PAGE;
//	 pageaddress1 = PAGE_ADDRESS(pages+1);
//	 pagestatus119 = GetPageState(pageaddress1);
//
//	 pageaddress2 = PAGE_ADDRESS(pages+2);
//	 pagestatus121 = GetPageState(pageaddress2);
//
//	 pageaddress3 = PAGE_ADDRESS(pages+3);
//	 pagestatus122 = GetPageState(pageaddress3);
//
//	 pageaddress4 = PAGE_ADDRESS(pages+4);
//	 pagestatus123 = GetPageState(pageaddress4);
//
//	 pageaddress5 = PAGE_ADDRESS(pages+5);
//	 pagestatus124 = GetPageState(pageaddress5);
//
//	 pageaddress6 = PAGE_ADDRESS(pages+6);
//	 pagestatus125 = GetPageState(pageaddress6);
//
//	 pageaddress7 = PAGE_ADDRESS(pages+7);
//	 pagestatus126 = GetPageState(pageaddress7);
//
//	 pageaddress8 = PAGE_ADDRESS(pages+8);
//	 pagestatus127 = GetPageState(pageaddress8);
//
//	 HAL_FLASH_Lock();
//    count = 0;
//    for(int i =1 ;i<2016;i++)
//    {
//    	EE_WriteVariable(1,i);
//    	count++;
//    }
//	EE_WriteVariable(_EE_NBASE,Data);
//	EE_ReadVariable(_EE_NBASE,&DataR[0]);
//
//	memset(DataR,0,500);
//	//2
//    for(int i=0; i<25; i++)
//    {
//    		EE_WriteVariable(_EE_PORT_DIR_BASE+i,i);
//    }
//
//    for(int i=0; i<25; i++)
//    {
//    		EE_ReadVariable(_EE_PORT_DIR_BASE+i,&DataR[i]);
//    }
//
//    memset(DataR,0,500);
//    //28
//    for(int i=0; i<125; i++)
//    {
//    		EE_WriteVariable(_EE_ALIAS_BASE+i,i);
//    }
//
//    for(int i=0; i<125; i++)
//    {
//    		EE_ReadVariable(_EE_ALIAS_BASE+i,&DataR[i]);
//    }
//
//    memset(DataR,0,500);
//    //153
//    for(int i=0; i<50; i++)
//    {
//    		EE_WriteVariable(_EE_GROUP_ALIAS_BASE+i,i);
//    }
//
//    for(int i=0; i<50; i++)
//    {
//    		EE_ReadVariable(_EE_GROUP_ALIAS_BASE+i,&DataR[i]);
//    }
//
//    memset(DataR,0,500);
//    //203
//    for(int i=0; i<25; i++)
//    {
//    		EE_WriteVariable(_EE_GROUP_MODULES_BASE+i,i);
//    }
//    for(int i=0; i<25; i++)
//    {
//    		EE_ReadVariable(_EE_GROUP_MODULES_BASE+i,&DataR[i]);
//    }
//
//    memset(DataR,0,500);
//    //228
//    for(int i=0; i<8; i++)
//    {
//    		EE_WriteVariable(_EE_DMA_STREAM_BASE+i,i);
//    }
//
//    for(int i=0; i<8; i++)
//    {
//    		EE_ReadVariable(_EE_DMA_STREAM_BASE+i,&DataR[i]);
//    }
//
//    memset(DataR,0,500);
//    //236
//    for(int i=0; i<40; i++)
//    {
//    		EE_WriteVariable(_EE_BUTTON_BASE+i,i);
//    }
//
//    for(int i=0; i<40; i++)
//	{
//			EE_ReadVariable(_EE_BUTTON_BASE+i,&DataR[i]);
//	}
//
//    memset(DataR,0,500);
//    //280
//    for(int i=0; i<2; i++)
//    {
//    		EE_WriteVariable(_EE_CLI_BAUD+i,i);
//    }
//    for(int i=0; i<2; i++)
//    {
//    		EE_ReadVariable(_EE_CLI_BAUD+i,&DataR[i]);
//    }
//
//    memset(DataR,0,500);
//    //500
//    for(int i=0; i<100; i++)
//    {
//    		EE_WriteVariable(_EE_MODULE_BASE+i,i);
//    }
//
//    for(int i=0; i<100; i++)
//    {
//    		EE_ReadVariable(_EE_MODULE_BASE+i,&DataR[i]);
//    }
//
//    memset(DataR,0,500);
//    //600
//    for(int i=0; i<424; i++)
//    {
//    		EE_WriteVariable(_EE_EMPTY_VAR_BASE+i,i);
//    }
//
//    for(int i=0; i<424; i++)
//    {
//    		EE_ReadVariable(_EE_EMPTY_VAR_BASE+i,&DataR[i]);
//    }

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

	AddPortButton(MOMENTARY_NO, 2);   //Define a button connected to port P1
	SetButtonEvents(2, 1, 0, 3, 0, 0, 0, 0, 0,1);    // Activate a click event and a pressed_for_x event for 3 seconds

	RGB_LED_sweep(RGB_SWEEP_BASIC, 2000, -1);

	// put your code here, to run repeatedly.
	while (1) {



	}
}

void buttonClickedCallback(uint8_t port){

	SendMessageToModule(2,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(4,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(7,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(8,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(9,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(10,CODE_PING, 0);
//	Delay_ms(20);

	Delay_ms(200);

	SendMessageToModule(2,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(4,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(7,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(8,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(9,CODE_PING, 0);
//	Delay_ms(20);

	SendMessageToModule(10,CODE_PING, 0);
//	Delay_ms(20);

//	SendMessageToModule(2,CODE_PING, 0);
//	Delay_ms(20);
//
//	SendMessageToModule(4,CODE_PING, 0);
//	Delay_ms(20);
//
//	SendMessageToModule(7,CODE_PING, 0);
//	Delay_ms(20);
//
//	SendMessageToModule(2,CODE_PING, 0);
//	Delay_ms(20);
//
//	SendMessageToModule(4,CODE_PING, 0);
//	Delay_ms(20);
//
//	SendMessageToModule(7,CODE_PING, 0);
//	Delay_ms(20);

}
/*-----------------------------------------------------------*/
