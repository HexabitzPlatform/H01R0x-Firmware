/*
 BitzOS (BOS) V0.4.0 - Copyright (C) 2017-2025 Hexabitz
 All rights reserved

 File Name     : main.c
 Description   : Main program body.
 */

/* Includes ****************************************************************/
#include "BOS.h"

/* Private variables *******************************************************/
float adcValue1 = 0;
float adcValue2 = 0;
float adcValue3 = 0;
float adcValue4 = 0;
float percentageAdcValue1 = 0;
float percentageAdcValue2 = 0;
float percentageAdcValue3 = 0;
float percentageAdcValue4 = 0;
/* Private Function Prototypes *********************************************/

/* Main Function ***********************************************************/
int main(void){

	/* Initialize Module &  BitzOS */
	Module_Init();

	/* Don't place your code here */
	for(;;){
	}
}

/***************************************************************************/
/* User Task */
void UserTask(void *argument){
	 ADCSelectPort(P1);
	 ADCSelectPort(P2);
	/* put your code here, to run repeatedly. */
	while(1){
			ReadADCChannel(P1, TOP, &adcValue1);
			ReadADCChannel(P1, BOTTOM, &adcValue2);
			ReadADCChannel(P2, TOP, &adcValue3);
			ReadADCChannel(P2, BOTTOM, &adcValue4);

			GetReadPercentage(P1, TOP, &percentageAdcValue1);
			GetReadPercentage(P1, BOTTOM, &percentageAdcValue2);
			GetReadPercentage(P2, TOP, &percentageAdcValue3);
			GetReadPercentage(P2, BOTTOM, &percentageAdcValue4);

}
}

/***************************************************************************/
/***************** (C) COPYRIGHT HEXABITZ ***** END OF FILE ****************/
