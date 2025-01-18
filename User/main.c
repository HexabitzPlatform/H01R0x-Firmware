/*
 BitzOS (BOS) V0.3.6 - Copyright (C) 2017-2024 Hexabitz
 All rights reserved

 File Name     : main.c
 Description   : Main program body.
 */
/* Includes ------------------------------------------------------------------*/
#include "BOS.h"
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Main function ------------------------------------------------------------*/
	uint16_t DataR[2500] = {0};
	uint32_t count = 0;
	uint32_t pagestatus119;
	uint32_t pagestatus120;
	uint32_t pagestatus121;
	uint32_t pagestatus122;
	uint32_t pagestatus123;
	uint32_t pagestatus124;
	uint32_t pagestatus125;
	uint32_t pagestatus126;
	uint8_t flag1 = 0;
	BOS_Status status;
int main(void) {

	Module_Init();		//Initialize Module &  BitzOS
	EE_Format();
	//Don't place your code here.
	for (;;) {
	}
}

/*-----------------------------------------------------------*/

/* User Task */
void UserTask(void *argument) {

	while (1) {

	if(flag1 == 1)
	{
		for(int i=1; i<1000; i++)
		{
			status = EE_WriteVariable(i,i);
			pagestatus119 = GetPageState(0x807B800);
			pagestatus120 = GetPageState(0x807C000);
			pagestatus121 = GetPageState(0x807C800);
			pagestatus122 = GetPageState(0x807D000);
			pagestatus123 = GetPageState(0x807D800);
			pagestatus124 = GetPageState(0x807E000);
			pagestatus125 = GetPageState(0x807E800);
			pagestatus126 = GetPageState(0x807F000);
			count++;
		}
	}
		for(int i=1; i<1000; i++)
		{
			EE_ReadVariable(i,&DataR[i]);
			pagestatus119 = GetPageState(0x807B800);
			pagestatus120 = GetPageState(0x807C000);
			pagestatus121 = GetPageState(0x807C800);
			pagestatus122 = GetPageState(0x807D000);
			pagestatus123 = GetPageState(0x807D800);
			pagestatus124 = GetPageState(0x807E000);
			pagestatus125 = GetPageState(0x807E800);
			pagestatus126 = GetPageState(0x807F000);

		}

	}
}

/*-----------------------------------------------------------*/
