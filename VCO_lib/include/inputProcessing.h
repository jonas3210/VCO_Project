/********************************************************************************
  * @file    inputProcessing.h
  * @author  Christopher Ottens and Danny MacAllister
  * @version V.0.0
  * @date    07.11.16
  * @brief   This file contains headers and function prototypes of inputProcessing.c
*********************************************************************************/

/*------------------Define to prevent recursive inclusion-----------------------*/
//#ifndef /*ERROR*/
//#define

/*---------------------------------Includes-------------------------------------*/
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include "stm32f4xx_tim.h"
#include "misc.h"
#include <stdbool.h>
#include "global.h"
#include "sevenSegment.h"

/*-------------------------------Exported variables-----------------------------*/
struct keyState												//Structure that contains the variables that are needed to debounce a key
{
 bool isActivated;											//Key is activated(if there is a function to enable/disable it)
 bool lastState;											//Last state(pressed/unpressed)
 bool actualState;											//Actual state
 bool gotPressed;											//Key was Pressed ?
 int timeCount;												//Time that the Key is locked
};

struct incrementState										//Structure that contains the variables that are needed to debounce an evaluate the increment sensor
{
 bool isActivated;											//Key is activated(if there is a function to enable/disable it)
 bool lastStateA8;											//Last state(pressed/unpressed)
 bool actualStateA8;										//Actual state A8
 bool actualStateC8;										//Actual state C8
 int timeCount;												//Time that the increment sensor is locked
};

struct incrementKeyState									//Structure that contains the variables for the increment Key
{
 bool isActivated;											//Key is activated(if there is a function to enable/disable it)
 bool lastState;											//Last state(pressed/unpressed)
 bool actualState;											//Actual state
 bool stateChanged;											//State changed since last call
 int timeCount;												//Time that the Key is locked
 int timeHolded;											//Time the key was pressed
};

/*-------------------------------Exported macro---------------------------------*/
//#define holdActive		gloablVariable					//hold active
//#define linlogActive	gloablVariable						//lin or log mode active
//#define out2Active		gloablVariable					//Output-Line 2 active
//#define out1Active		gloablVariable					//Output-Line 1 active
//#define recActive		gloablVariable						//rec mode active
//#define bankValue											//Actual selected bank
#define timeToSave 1000										//Time that the increment Key needs to be pressed to safe the actual settings to the displayed bank

/*-----------------------------Exported functions-------------------------------*/
void inputProcessingInit(void);								//Initialisation
void TIM7_IRQHandler(void);									//Interrupt-Function

//#endif
