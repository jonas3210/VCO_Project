/********************************************************************************
  * @file    debounceKey.h
  * @author  Christopher Ottens
  * @version V.0.2
  * @date    30.10.16
  * @brief   This file contains headers and function prototypes of debounceKey.c
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

/*-------------------------------Exported variables-----------------------------*/
struct keyState
{
 bool isActivated;
 bool lastState;
 bool actualState;
 bool gotPressed;
 int timeCount;
};

volatile bool holdActive;
volatile bool linlogActive;
volatile bool out1Active;
volatile bool out2Active;
volatile bool recActive;
/*-------------------------------Exported macro---------------------------------*/
#define INPUT_BUTTON_HOLD holdActive
#define INPUT_BUTTON_LINLOG linlogActive
#define INPUT_BUTTON_OUT1 out1Active
#define INPUT_BUTTON_OUT2 out2Active
#define INPUT_BUTTON_REC recActive
/*-----------------------------Exported functions-------------------------------*/
void debounceKeyInit(void);
void TIM7_IRQHandler(void);

//#endif
