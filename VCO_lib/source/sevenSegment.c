/********************************************************************************
  * @file    sevenSegment.c
  * @author  Christopher Ottens
  * @version V.0.0
  * @date    08.10.16
  * @brief   This file contains the function to drive the seven segment display
*********************************************************************************/

#include "sevenSegment.h"

/**
 * This function executes the initialization that is necessary to drive the seven segment display
 */
void sevenSegmentInit(void)
{
	  GPIO_InitTypeDef  GPIO_InitStructure;

	  // Clock Enable for Port B,D,E
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	  // Config PB 11,12,13,14,15  as Digital Output
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);

	  // Config PE 11,12,13,14,15  as Digital Output
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOE, &GPIO_InitStructure);

	  // Config PD 8,9,10,11,12,14  as Digital Output
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_14;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/**
 * This function converts the input integer into two int values to select which pin have to get activated to display the actual Bank
 */
void sevenSegmentIntToDisplay(int intToDisplay)
{
	int intToDisplaySegOne, intToDisplaySegTwo;

	intToDisplaySegOne = (int) (intToDisplay/10);
	intToDisplaySegTwo = intToDisplay-(intToDisplaySegOne*10);

	switch(intToDisplaySegOne)
	{
		case 0:		sevenSegmentOneDisplayZero;
					break;

		case 1:		sevenSegmentOneDisplayOne;
					break;

		case 2:		sevenSegmentOneDisplayTwo;
					break;

		case 3:		sevenSegmentOneDisplayThree;
					break;

		case 4:		sevenSegmentOneDisplayFour;
					break;

		case 5:		sevenSegmentOneDisplayFive;
					break;

		case 6:		sevenSegmentOneDisplaySix;
					break;

		case 7:		sevenSegmentOneDisplaySeven;
					break;

		case 8:		sevenSegmentOneDisplayEight;
					break;

		case 9:		sevenSegmentOneDisplayNine;
					break;
	}

	switch(intToDisplaySegTwo)
	{
		case 0:		sevenSegmentTwoDisplayZero;
					break;

		case 1:		sevenSegmentTwoDisplayOne;
					break;

		case 2:		sevenSegmentTwoDisplayTwo;
					break;

		case 3:		sevenSegmentTwoDisplayThree;
					break;

		case 4:		sevenSegmentTwoDisplayFour;
					break;

		case 5:		sevenSegmentTwoDisplayFive;
					break;

		case 6:		sevenSegmentTwoDisplaySix;
					break;

		case 7:		sevenSegmentTwoDisplaySeven;
					break;

		case 8:		sevenSegmentTwoDisplayEight;
					break;

		case 9:		sevenSegmentTwoDisplayNine;
					break;
	}
}

