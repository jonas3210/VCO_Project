/********************************************************************************
  * @file    incrementGiver.h
  * @author  Danny MacAllister
  * @version V.0.0
  * @date    01.11.16
  * @brief   This file contains headers and function prototypes of incrementGiver.h
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

/*-------------------------------Exported variables-----------------------------*/
struct incrementState
{
 bool isActivated;
 bool lastStateA10;
 bool actualStateA10;
 bool actualStateC8;
 int timeCount;
};

struct keyState
{
 bool isActivated;
 bool lastState;
 bool actualState;
 bool stateChanged;
 int timeCount;
 int timeHolded;
};

/*-------------------------------Exported macro---------------------------------*/
//#define bankValue
#define timeToSave 1000



/*-----------------------------Exported functions-------------------------------*/
void debounceKeyInit(void);
void TIM3_IRQHandler(void);

//#endif
