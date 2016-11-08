/********************************************************************************
  * @file    inputProcessing.c
  * @author  Christopher Ottens and Danny MacAllister
  * @version V.0.0
  * @date    07.11.16
  * @brief   This file contains function that are needed to debounce the input Keys
*********************************************************************************/

#include "inputProcessing.h"

/**
 * This function executes the initialization that is necessary to debounce the keys
 */
void inputProcessingInit(void)
{

//GPIO-Initialization
	GPIO_InitTypeDef  GPIO_InitStructure;

	// Clock Enable for Port A,B,C,D
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

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
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// Config PA 8,14  as Digital Input
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 /*| GPIO_Pin_14*/;
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

	GPIO_SetBits(GPIOD,GPIO_Pin_15);

}

/**
 * This function gets executed when the Timer 7 sents an Interrupt, it debounces the Keys and evaluates them
 */
void TIM7_IRQHandler(void)
{
	static struct keyState inputKeys[5];
	static struct incrementState incrementGiver;
	static struct incrementKeyState incrementKey;
	int i = 0;

	//Function-Part to debounce the five input keys
	inputKeys[0].actualState = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);											//Read the Keys and save the actual state
	inputKeys[1].actualState = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5);
	inputKeys[2].actualState = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0);
	inputKeys[3].actualState = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2);
	inputKeys[4].actualState = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6);

	for (i=0;i<5;i++)
	{
	 inputKeys[i].gotPressed = 0;
	 if(inputKeys[i].timeCount > 0)																				//Key Locked ? =>  lower Time locked
	 {
		 inputKeys[i].timeCount--;
	 }
	 if((inputKeys[i].lastState == 1) && (inputKeys[i].actualState == 0) && (inputKeys[i].timeCount == 0))		//Falling edge and key unlocked
	 {
		 inputKeys[i].gotPressed = 1;																			//Set key pressed
		 inputKeys[i].timeCount = 10;																			//Lock key for xms
	 }
	 inputKeys[i].lastState = inputKeys[i].actualState;
	}

	/*holdActive = inputKeys[0].gotPressed ^ holdActive;														//If Key was pressed Toggle State
	linlogActive = inputKeys[1].gotPressed ^ linlogActive;
	out2Active = inputKeys[2].gotPressed ^ out2Active;
	out1Active = inputKeys[3].gotPressed ^ out1Active;
	recActive = inputKeys[4].gotPressed ^ recActive;*/

	//Function-Part to debounce and evaluate the increment sensor
	incrementGiver.actualStateA8 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8);										//Read the actual input states of the increment sensor
	incrementGiver.actualStateC8 = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8);

	if(incrementGiver.timeCount > 0)																			//Key Locked ? =>  lower Time locked
	{
		incrementGiver.timeCount--;
	}
	else
	{
		incrementGiver.actualStateA8 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8);
		if((incrementGiver.lastStateA8 == 0) && (incrementGiver.actualStateA8 == 1))							//If the increment Giver is turned Left
		{																										//a lower bank is displayed/choosed
			incrementGiver.timeCount = 10;																		//if it is turned right a higher bank is choosed
			if(incrementGiver.actualStateC8 == 1)
			{
				if(bankValue > 0)																				//Possible bank values 0-99
				{
					//bankValue--;
				}
				else
				{
					bankValue = 99;
				}
				//sevenSegmentIntToDisplay(bankValue)															//Changed Bankvalue gets displayed on seven segment display
			}
			else
			{
				if(bankValue < 99)
				{
					//bankValue++;
				}
				else
				{
					bankValue = 0;
				}
				//sevenSegmentIntToDisplay(bankValue)
			}
		}
	}

	incrementGiver.lastStateA8 = incrementGiver.actualStateA8;													//Save actual State as last state

	//Function-Part to debounce and evaluate the increment sensor key
	if(incrementKey.timeCount > 0)																				//Key locked ? => lower time locked
	{
		incrementKey.timeCount--;
	}
	else																										//Else check if
	{
		incrementKey.actualState = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
		if((incrementKey.lastState == 0) && (incrementKey.actualState == 1))									//there was a status change
		{
			incrementKey.stateChanged = 1;
			incrementKey.timeCount = 10;
			incrementKey.timeHolded = 0;
		}
		if((incrementKey.lastState == 1) && (incrementKey.actualState == 1) && (incrementKey.stateChanged ==1))	//the button was holded for timeToSave
		{
			incrementKey.timeHolded = incrementKey.timeHolded + 10;
			incrementKey.timeCount = 10;
			if(incrementKey.timeHolded >= timeToSave)
			{
				GPIO_ToggleBits(GPIOD,GPIO_Pin_15);																//Save Bank
				incrementKey.stateChanged = 0;
			}
		}
		if((incrementKey.lastState == 0) && (incrementKey.actualState == 0) && (incrementKey.stateChanged ==1))	//the button was pressed
		{
			incrementKey.stateChanged = 0;
			if(incrementKey.timeHolded < timeToSave)
			{
				GPIO_ToggleBits(GPIOD,GPIO_Pin_12); //Bank auswählen											//choose bank
			}
		}
	}

	incrementKey.lastState = incrementKey.actualState;

	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);																	//Clear Interrupt Flag
}
