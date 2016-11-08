/********************************************************************************
  * @file    incrementGiver.c
  * @author  Danny MacAllister
  * @version V.0.0
  * @date    01.11.16
  * @brief   This file contains the functions to evaluate the Increment Giver
*********************************************************************************/

#include "incrementGiver.h"

/**
 * This function executes the initialization that is necessary to debounce the keys
 */
void debounceKeyInit(void)
{
//GPIO-Initialization
	GPIO_InitTypeDef  GPIO_InitStructure;

	// Clock Enable for Port A,C
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	// Config PA 10,14  as Digital Input
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// Config PC 8  as Digital Input
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

//Timer 7 Initialization
	TIM_TimeBaseInitTypeDef TIM_TimeBase_InitStructure;

	// Clock Enable for Timer 3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	// Config Timer 3 f=1kHz
	TIM_TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBase_InitStructure.TIM_Period = 84;
	TIM_TimeBase_InitStructure.TIM_Prescaler = 1000;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBase_InitStructure);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

//Interrupt-Controller Initialization
 	NVIC_InitTypeDef NVIC_InitStructure;

	// Config NVIC
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0E;
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	NVIC_Init(&NVIC_InitStructure);

// Start Timer 3
 	TIM_Cmd(TIM3, ENABLE);

}

/**
 * This function gets executed when the Timer 3 sents an Interrupt, evaluates the increment giver
 */
void TIM3_IRQHandler(void)
{
	static struct incrementState incrementGiver;
	static struct keyState incrementKey;

	//Increment
	incrementGiver.actualStateA10 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10);
	incrementGiver.actualStateC8 = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8);

	if(incrementGiver.timeCount > 0)
	{
		incrementGiver.timeCount--;
	}
	else
	{
		incrementGiver.actualStateA10 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10);
		if((incrementGiver.lastStateA10 == 0) && (incrementGiver.actualStateA10 == 1))
		{
			incrementGiver.timeCount = 10;
			if(incrementGiver.actualStateC8 == 1)
			{
				//bankValue--;
			}
			else
			{
				//bankValue++;
			}
		}
	}
	incrementGiver.lastStateA10 = incrementGiver.actualStateA10;

	//Key
	if(incrementKey.timeCount > 0)
	{
		incrementKey.timeCount--;
	}
	else
	{
		incrementKey.actualState = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
		if((incrementKey.lastState == 0) && (incrementKey.actualState == 1))
		{
			incrementKey.stateChanged = 1;
			incrementKey.timeCount = 10;
			incrementKey.timeHolded = 0;
		}
		if((incrementKey.lastState == 1) && (incrementKey.actualState == 1) && (incrementKey.stateChanged ==1))
		{
			incrementKey.timeHolded = incrementKey.timeHolded + 10;
			incrementKey.timeCount = 10;
			if(incrementKey.timeHolded >= timeToSave)
			{
				GPIO_ToggleBits(GPIOD,GPIO_Pin_15);		//Bank speichern
				incrementKey.stateChanged = 0;
			}
		}
		if((incrementKey.lastState == 0) && (incrementKey.actualState == 0) && (incrementKey.stateChanged ==1))
		{
			incrementKey.stateChanged = 0;
			if(incrementKey.timeHolded < timeToSave)
			{
				GPIO_ToggleBits(GPIOD,GPIO_Pin_12); //Bank auswählen
			}
		}
	}

	incrementKey.lastState = incrementKey.actualState;


	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	GPIO_SetBits(GPIOD,GPIO_Pin_14);
}
