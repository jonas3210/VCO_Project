/********************************************************************************
  * @file    sevenSegment.h
  * @author  Christopher Ottens
  * @version V.0.0
  * @date    08.10.16
  * @brief   This file contains headers and function prototypes of sevenSegment.c
*********************************************************************************/

/*------------------Define to prevent recursive inclusion-----------------------*/
#ifndef __ADC_MULTICHANNEL_INIT_H
#define __ADC_MULTICHANNEL_INIT_H

/*---------------------------------Includes-------------------------------------*/
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

/*-------------------------------Exported macro --------------------------------*/
#define sevenSegmentTwoDisplayZero 	GPIO_SetBits(GPIOB,GPIO_Pin_15);GPIO_SetBits(GPIOB,GPIO_Pin_13);GPIO_SetBits(GPIOE,GPIO_Pin_14);\
									GPIO_SetBits(GPIOB,GPIO_Pin_12);GPIO_SetBits(GPIOB,GPIO_Pin_14);GPIO_SetBits(GPIOD,GPIO_Pin_9);

#define sevenSegmentTwoDisplayOne  	GPIO_SetBits(GPIOB,GPIO_Pin_13);GPIO_SetBits(GPIOE,GPIO_Pin_14);

#define sevenSegmentTwoDisplayTwo  	GPIO_SetBits(GPIOB,GPIO_Pin_15);GPIO_SetBits(GPIOB,GPIO_Pin_13);GPIO_SetBits(GPIOD,GPIO_Pin_11);\
									GPIO_SetBits(GPIOB,GPIO_Pin_14);GPIO_SetBits(GPIOB,GPIO_Pin_12);

#define sevenSegmentTwoDisplayThree	GPIO_SetBits(GPIOB,GPIO_Pin_15);GPIO_SetBits(GPIOB,GPIO_Pin_13);GPIO_SetBits(GPIOD,GPIO_Pin_11);\
									GPIO_SetBits(GPIOE,GPIO_Pin_14);GPIO_SetBits(GPIOB,GPIO_Pin_12);

#define sevenSegmentTwoDisplayFour	GPIO_SetBits(GPIOD,GPIO_Pin_9);GPIO_SetBits(GPIOD,GPIO_Pin_11);GPIO_SetBits(GPIOB,GPIO_Pin_13);\
									GPIO_SetBits(GPIOE,GPIO_Pin_14);

#define sevenSegmentTwoDisplayFive	GPIO_SetBits(GPIOB,GPIO_Pin_15);GPIO_SetBits(GPIOD,GPIO_Pin_9);GPIO_SetBits(GPIOD,GPIO_Pin_11);\
									GPIO_SetBits(GPIOE,GPIO_Pin_14);GPIO_SetBits(GPIOB,GPIO_Pin_12);

#define sevenSegmentTwoDisplaySix	GPIO_SetBits(GPIOB,GPIO_Pin_15);GPIO_SetBits(GPIOD,GPIO_Pin_9);GPIO_SetBits(GPIOB,GPIO_Pin_14);\
									GPIO_SetBits(GPIOD,GPIO_Pin_11);GPIO_SetBits(GPIOE,GPIO_Pin_14);GPIO_SetBits(GPIOB,GPIO_Pin_12);

#define sevenSegmentTwoDisplaySeven	GPIO_SetBits(GPIOB,GPIO_Pin_15);GPIO_SetBits(GPIOB,GPIO_Pin_13);GPIO_SetBits(GPIOE,GPIO_Pin_14);

#define sevenSegmentTwoDisplayEight	GPIO_SetBits(GPIOB,GPIO_Pin_15);GPIO_SetBits(GPIOB,GPIO_Pin_13);GPIO_SetBits(GPIOE,GPIO_Pin_14);\
									GPIO_SetBits(GPIOB,GPIO_Pin_12);GPIO_SetBits(GPIOB,GPIO_Pin_14);GPIO_SetBits(GPIOD,GPIO_Pin_9); \
									GPIO_SetBits(GPIOD,GPIO_Pin_11);

#define sevenSegmentTwoDisplayNine	GPIO_SetBits(GPIOB,GPIO_Pin_15);GPIO_SetBits(GPIOB,GPIO_Pin_13);GPIO_SetBits(GPIOE,GPIO_Pin_14);\
									GPIO_SetBits(GPIOD,GPIO_Pin_9);GPIO_SetBits(GPIOD,GPIO_Pin_11);GPIO_SetBits(GPIOB,GPIO_Pin_12);

#define sevenSegmentOneDisplayZero 	GPIO_SetBits(GPIOE,GPIO_Pin_13);GPIO_SetBits(GPIOE,GPIO_Pin_11);GPIO_SetBits(GPIOD,GPIO_Pin_10);\
									GPIO_SetBits(GPIOD,GPIO_Pin_12);GPIO_SetBits(GPIOD,GPIO_Pin_14);GPIO_SetBits(GPIOE,GPIO_Pin_15);

#define sevenSegmentOneDisplayOne  	GPIO_SetBits(GPIOE,GPIO_Pin_11);GPIO_SetBits(GPIOD,GPIO_Pin_10);

#define sevenSegmentOneDisplayTwo  	GPIO_SetBits(GPIOE,GPIO_Pin_13);GPIO_SetBits(GPIOE,GPIO_Pin_11);GPIO_SetBits(GPIOB,GPIO_Pin_11);\
									GPIO_SetBits(GPIOE,GPIO_Pin_15);GPIO_SetBits(GPIOD,GPIO_Pin_12);

#define sevenSegmentOneDisplayThree	GPIO_SetBits(GPIOE,GPIO_Pin_13);GPIO_SetBits(GPIOE,GPIO_Pin_11);GPIO_SetBits(GPIOB,GPIO_Pin_11);\
									GPIO_SetBits(GPIOD,GPIO_Pin_10);GPIO_SetBits(GPIOD,GPIO_Pin_12);

#define sevenSegmentOneDisplayFour	GPIO_SetBits(GPIOE,GPIO_Pin_15);GPIO_SetBits(GPIOE,GPIO_Pin_11);GPIO_SetBits(GPIOB,GPIO_Pin_11);\
									GPIO_SetBits(GPIOD,GPIO_Pin_10);

#define sevenSegmentOneDisplayFive	GPIO_SetBits(GPIOE,GPIO_Pin_13);GPIO_SetBits(GPIOE,GPIO_Pin_15);GPIO_SetBits(GPIOB,GPIO_Pin_11);\
									GPIO_SetBits(GPIOD,GPIO_Pin_10);GPIO_SetBits(GPIOD,GPIO_Pin_12);

#define sevenSegmentOneDisplaySix	GPIO_SetBits(GPIOE,GPIO_Pin_15);GPIO_SetBits(GPIOB,GPIO_Pin_11);GPIO_SetBits(GPIOD,GPIO_Pin_10);\
									GPIO_SetBits(GPIOD,GPIO_Pin_12);GPIO_SetBits(GPIOD,GPIO_Pin_14);

#define sevenSegmentOneDisplaySeven	GPIO_SetBits(GPIOE,GPIO_Pin_13);GPIO_SetBits(GPIOE,GPIO_Pin_11);GPIO_SetBits(GPIOD,GPIO_Pin_10);

#define sevenSegmentOneDisplayEight	GPIO_SetBits(GPIOE,GPIO_Pin_13);GPIO_SetBits(GPIOE,GPIO_Pin_11);GPIO_SetBits(GPIOD,GPIO_Pin_10);\
									GPIO_SetBits(GPIOD,GPIO_Pin_12);GPIO_SetBits(GPIOD,GPIO_Pin_14);GPIO_SetBits(GPIOE,GPIO_Pin_15);\
									GPIO_SetBits(GPIOB,GPIO_Pin_11);

#define sevenSegmentOneDisplayNine	GPIO_SetBits(GPIOE,GPIO_Pin_13);GPIO_SetBits(GPIOE,GPIO_Pin_11);GPIO_SetBits(GPIOD,GPIO_Pin_10);\
									GPIO_SetBits(GPIOD,GPIO_Pin_12);GPIO_SetBits(GPIOE,GPIO_Pin_15);GPIO_SetBits(GPIOB,GPIO_Pin_11);

#define sevenSegmentReset			GPIO_ResetBits(GPIOE,GPIO_Pin_11);GPIO_ResetBits(GPIOE,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_15);\
									GPIO_ResetBits(GPIOB,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_14);GPIO_ResetBits(GPIOB,GPIO_Pin_12);\
									GPIO_ResetBits(GPIOB,GPIO_Pin_14);GPIO_ResetBits(GPIOD,GPIO_Pin_9);GPIO_ResetBits(GPIOB,GPIO_Pin_11);\
									GPIO_ResetBits(GPIOD,GPIO_Pin_11);GPIO_ResetBits(GPIOD,GPIO_Pin_10);GPIO_ResetBits(GPIOD,GPIO_Pin_12);\
									GPIO_ResetBits(GPIOD,GPIO_Pin_14);GPIO_ResetBits(GPIOE,GPIO_Pin_15);GPIO_ResetBits(GPIOB,GPIO_Pin_15);\
									GPIO_ResetBits(GPIOD,GPIO_Pin_11);

/*-----------------------------Exported functions-------------------------------*/
void sevenSegmentInit(void);
void sevenSegmentIntToDisplay(int intToDisplay);

#endif
