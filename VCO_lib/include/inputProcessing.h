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
#include "sevenSegment.h"
#include "Global_Variables.h"

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
 bool lastStateC8;
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

volatile bool holdActive;
volatile bool linlogActive;
volatile bool out1Active;
volatile bool out2Active;
volatile bool recActive;
volatile bool encoderActive;


/*-------------------------------Exported macro---------------------------------*/
#define BUTTON_AMOUNT 6

#define INPUT_BUTTON_HOLD holdActive
#define INPUT_BUTTON_LINLOG linlogActive
#define INPUT_BUTTON_OUT1 out1Active
#define INPUT_BUTTON_OUT2 out2Active
#define INPUT_BUTTON_REC recActive
#define INPUT_BUTTON_ENCODER encoderActive
#define timeToSave 3000

#define LED_HOLD_ON GPIO_ResetBits(GPIOD, GPIO_Pin_7)
#define LED_HOLD_OFF GPIO_SetBits(GPIOD, GPIO_Pin_7)
#define LED_LINLOG_ON GPIO_ResetBits(GPIOB, GPIO_Pin_4)
#define LED_LINLOG_OFF GPIO_SetBits(GPIOB, GPIO_Pin_4)
#define LED_REC_ON GPIO_ResetBits(GPIOD, GPIO_Pin_5)
#define LED_REC_OFF GPIO_SetBits(GPIOD, GPIO_Pin_5)
#define LED_SAVE_ON GPIO_ResetBits(GPIOE, GPIO_Pin_6)
#define LED_SAVE_OFF GPIO_SetBits(GPIOE, GPIO_Pin_6)
#define LED_SAVE_TOGGLE GPIO_ToggleBits(GPIOE, GPIO_Pin_6)
#define LED_LOAD_ON GPIO_ResetBits(GPIOC, GPIO_Pin_13)
#define LED_LOAD_OFF GPIO_SetBits(GPIOC, GPIO_Pin_13)
#define LED_LOAD_TOGGLE GPIO_ToggleBits(GPIOC, GPIO_Pin_13)
#define LED_ORIGIN_ON GPIO_ResetBits(GPIOE, GPIO_Pin_4)
#define LED_ORIGIN_OFF GPIO_SetBits(GPIOE, GPIO_Pin_4)
#define LED_OUT1_ON GPIO_ResetBits(GPIOD, GPIO_Pin_3)
#define LED_OUT1_OFF GPIO_SetBits(GPIOD, GPIO_Pin_3)
#define LED_OUT2_ON GPIO_ResetBits(GPIOD, GPIO_Pin_1)
#define LED_OUT2_OFF GPIO_SetBits(GPIOD, GPIO_Pin_1)//Time that the increment Key needs to be pressed to safe the actual settings to the displayed bank

/*-----------------------------Exported functions-------------------------------*/
void inputProcessingInit(void);								//Initialisation
void TIM7_IRQHandler(void);									//Interrupt-Function

//#endif
