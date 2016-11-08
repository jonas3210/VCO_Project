/********************************************************************************
  * @file    debounceKey.c
  * @author  Christopher Ottens
  * @version V.0.2
  * @date    30.10.16
  * @brief   This file contains the functions to debounce the Keys
*********************************************************************************/

#include "debounceKey.h"

/**
 * This function executes the initialization that is necessary to debounce the keys
 */
void debounceKeyInit(void)
{

//GPIO-Initialization
	GPIO_InitTypeDef  GPIO_InitStructure;

	// Clock Enable for Port B,D
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	// Config PB 3,5  as Digital Input
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// Config PD 0,2,6  as Digital Input
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

//Timer 7 Initialization
	TIM_TimeBaseInitTypeDef TIM_TimeBase_InitStructure;

	// Clock Enable for Timer 7
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

	// Config Timer 7 f=1kHz
	TIM_TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBase_InitStructure.TIM_Period = 84;
	TIM_TimeBase_InitStructure.TIM_Prescaler = 1000;
	TIM_TimeBaseInit(TIM7, &TIM_TimeBase_InitStructure);
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);

//Interrupt-Controller Initialization
 	NVIC_InitTypeDef NVIC_InitStructure;

	// Config NVIC
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	NVIC_Init(&NVIC_InitStructure);

// Start Timer 7
 	TIM_Cmd(TIM7, ENABLE);

}

/**
 * This function gets executed when the Timer 7 sents an Interrupt, it debounces the Keys that have been pressed
 */
void TIM7_IRQHandler(void)
{
	static struct keyState inputKeys[5];
	int i = 0;

	inputKeys[0].actualState = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);
	inputKeys[1].actualState = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5);
	inputKeys[2].actualState = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0);
	inputKeys[3].actualState = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2);
	inputKeys[4].actualState = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6);
	for (i=0;i<5;i++)
	{
	 inputKeys[i].gotPressed = 0;
	 if(inputKeys[i].timeCount > 0)
	 {
		 inputKeys[i].timeCount--;
	 }
	 if((inputKeys[i].lastState == 1) && (inputKeys[i].actualState == 0) && (inputKeys[i].timeCount == 0))
	 {
		 inputKeys[i].gotPressed = 1;
		 inputKeys[i].timeCount = 10;
	 }
	 inputKeys[i].lastState = inputKeys[i].actualState;
	}
	holdActive = inputKeys[0].gotPressed ^ holdActive;
	linlogActive = inputKeys[1].gotPressed ^ linlogActive;
	out2Active = inputKeys[2].gotPressed ^ out2Active;
	out1Active = inputKeys[3].gotPressed ^ out1Active;
	recActive = inputKeys[4].gotPressed ^ recActive;
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);

}
