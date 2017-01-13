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

#define HARDWARE_VERSION 1 //0 // Definition of hardwareversion -> Different 7-Segment Pins

/*-------------------------------Exported macro --------------------------------*/
#if HARDWARE_VERSION == 0
#define sevenSegmentTwoDisplayZero 	GPIO_ResetBits(GPIOB,GPIO_Pin_15);GPIO_ResetBits(GPIOD,GPIO_Pin_9);GPIO_ResetBits(GPIOB,GPIO_Pin_14);\
									GPIO_ResetBits(GPIOD,GPIO_Pin_11);GPIO_ResetBits(GPIOE,GPIO_Pin_14);GPIO_ResetBits(GPIOB,GPIO_Pin_12);

#define sevenSegmentTwoDisplayOne  	GPIO_ResetBits(GPIOE,GPIO_Pin_14);GPIO_ResetBits(GPIOD,GPIO_Pin_11);

#define sevenSegmentTwoDisplayTwo  	GPIO_ResetBits(GPIOD,GPIO_Pin_9);GPIO_ResetBits(GPIOB,GPIO_Pin_13);GPIO_ResetBits(GPIOD,GPIO_Pin_11);\
									GPIO_ResetBits(GPIOB,GPIO_Pin_14);GPIO_ResetBits(GPIOB,GPIO_Pin_12);

#define sevenSegmentTwoDisplayThree	GPIO_ResetBits(GPIOD,GPIO_Pin_9);GPIO_ResetBits(GPIOB,GPIO_Pin_13);GPIO_ResetBits(GPIOD,GPIO_Pin_11);\
									GPIO_ResetBits(GPIOE,GPIO_Pin_14);GPIO_ResetBits(GPIOB,GPIO_Pin_12);

#define sevenSegmentTwoDisplayFour	GPIO_ResetBits(GPIOB,GPIO_Pin_15);GPIO_ResetBits(GPIOD,GPIO_Pin_11);GPIO_ResetBits(GPIOB,GPIO_Pin_13);\
									GPIO_ResetBits(GPIOE,GPIO_Pin_14);

#define sevenSegmentTwoDisplayFive	GPIO_ResetBits(GPIOB,GPIO_Pin_15);GPIO_ResetBits(GPIOD,GPIO_Pin_9);GPIO_ResetBits(GPIOB,GPIO_Pin_13);\
									GPIO_ResetBits(GPIOE,GPIO_Pin_14);GPIO_ResetBits(GPIOB,GPIO_Pin_12);

#define sevenSegmentTwoDisplaySix	GPIO_ResetBits(GPIOB,GPIO_Pin_15);GPIO_ResetBits(GPIOD,GPIO_Pin_9);GPIO_ResetBits(GPIOB,GPIO_Pin_14);\
									GPIO_ResetBits(GPIOB,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_14);GPIO_ResetBits(GPIOB,GPIO_Pin_12);

#define sevenSegmentTwoDisplaySeven	GPIO_ResetBits(GPIOD,GPIO_Pin_9);GPIO_ResetBits(GPIOE,GPIO_Pin_14);GPIO_ResetBits(GPIOD,GPIO_Pin_11);

#define sevenSegmentTwoDisplayEight	GPIO_ResetBits(GPIOB,GPIO_Pin_15);GPIO_ResetBits(GPIOB,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_14);\
									GPIO_ResetBits(GPIOB,GPIO_Pin_12);GPIO_ResetBits(GPIOB,GPIO_Pin_14);GPIO_ResetBits(GPIOD,GPIO_Pin_9); \
									GPIO_ResetBits(GPIOD,GPIO_Pin_11);

#define sevenSegmentTwoDisplayNine	GPIO_ResetBits(GPIOB,GPIO_Pin_15);GPIO_ResetBits(GPIOB,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_14);\
									GPIO_ResetBits(GPIOD,GPIO_Pin_9);GPIO_ResetBits(GPIOD,GPIO_Pin_11);GPIO_ResetBits(GPIOB,GPIO_Pin_12);

#define sevenSegmentOneDisplayZero 	GPIO_ResetBits(GPIOE,GPIO_Pin_13);GPIO_ResetBits(GPIOD,GPIO_Pin_10);GPIO_ResetBits(GPIOB,GPIO_Pin_11);\
									GPIO_ResetBits(GPIOE,GPIO_Pin_15);GPIO_ResetBits(GPIOD,GPIO_Pin_12);GPIO_ResetBits(GPIOD,GPIO_Pin_14);

#define sevenSegmentOneDisplayOne  	GPIO_ResetBits(GPIOB,GPIO_Pin_11);GPIO_ResetBits(GPIOD,GPIO_Pin_10);

#define sevenSegmentOneDisplayTwo  	GPIO_ResetBits(GPIOE,GPIO_Pin_15);GPIO_ResetBits(GPIOB,GPIO_Pin_11);GPIO_ResetBits(GPIOE,GPIO_Pin_11);\
									GPIO_ResetBits(GPIOD,GPIO_Pin_14);GPIO_ResetBits(GPIOD,GPIO_Pin_12);

#define sevenSegmentOneDisplayThree	GPIO_ResetBits(GPIOE,GPIO_Pin_15);GPIO_ResetBits(GPIOB,GPIO_Pin_11);GPIO_ResetBits(GPIOD,GPIO_Pin_10);\
									GPIO_ResetBits(GPIOD,GPIO_Pin_12);GPIO_ResetBits(GPIOE,GPIO_Pin_11);

#define sevenSegmentOneDisplayFour	GPIO_ResetBits(GPIOE,GPIO_Pin_13);GPIO_ResetBits(GPIOB,GPIO_Pin_11);GPIO_ResetBits(GPIOD,GPIO_Pin_10);\
									GPIO_ResetBits(GPIOE,GPIO_Pin_11);

#define sevenSegmentOneDisplayFive	GPIO_ResetBits(GPIOE,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_11);GPIO_ResetBits(GPIOD,GPIO_Pin_10);\
									GPIO_ResetBits(GPIOD,GPIO_Pin_12);GPIO_ResetBits(GPIOE,GPIO_Pin_15);\

#define sevenSegmentOneDisplaySix	GPIO_ResetBits(GPIOE,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_11);GPIO_ResetBits(GPIOD,GPIO_Pin_10);\
									GPIO_ResetBits(GPIOD,GPIO_Pin_12);GPIO_ResetBits(GPIOD,GPIO_Pin_14);GPIO_ResetBits(GPIOE,GPIO_Pin_15);\

#define sevenSegmentOneDisplaySeven	GPIO_ResetBits(GPIOB,GPIO_Pin_11);GPIO_ResetBits(GPIOD,GPIO_Pin_10);GPIO_ResetBits(GPIOE,GPIO_Pin_15);

#define sevenSegmentOneDisplayEight	GPIO_ResetBits(GPIOE,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_11);GPIO_ResetBits(GPIOD,GPIO_Pin_10);\
									GPIO_ResetBits(GPIOD,GPIO_Pin_12);GPIO_ResetBits(GPIOD,GPIO_Pin_14);GPIO_ResetBits(GPIOE,GPIO_Pin_15);\
									GPIO_ResetBits(GPIOB,GPIO_Pin_11);

#define sevenSegmentOneDisplayNine	GPIO_ResetBits(GPIOE,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_11);GPIO_ResetBits(GPIOD,GPIO_Pin_10);\
									GPIO_ResetBits(GPIOD,GPIO_Pin_12);GPIO_ResetBits(GPIOE,GPIO_Pin_15);GPIO_ResetBits(GPIOB,GPIO_Pin_11);

#define sevenSegmentReset			GPIO_SetBits(GPIOE,GPIO_Pin_11);GPIO_SetBits(GPIOE,GPIO_Pin_13);GPIO_SetBits(GPIOE,GPIO_Pin_15);\
									GPIO_SetBits(GPIOB,GPIO_Pin_13);GPIO_SetBits(GPIOE,GPIO_Pin_14);GPIO_SetBits(GPIOB,GPIO_Pin_12);\
									GPIO_SetBits(GPIOB,GPIO_Pin_14);GPIO_SetBits(GPIOD,GPIO_Pin_9);GPIO_SetBits(GPIOB,GPIO_Pin_11);\
									GPIO_SetBits(GPIOD,GPIO_Pin_11);GPIO_SetBits(GPIOD,GPIO_Pin_10);GPIO_SetBits(GPIOD,GPIO_Pin_12);\
									GPIO_SetBits(GPIOD,GPIO_Pin_14);GPIO_SetBits(GPIOE,GPIO_Pin_15);GPIO_SetBits(GPIOB,GPIO_Pin_15);\
									GPIO_SetBits(GPIOD,GPIO_Pin_11);GPIO_SetBits(GPIOD,GPIO_Pin_8);GPIO_SetBits(GPIOE,GPIO_Pin_12);
#endif
#if HARDWARE_VERSION == 1
#define sevenSegmentOneDisplayZero 	GPIO_ResetBits(GPIOE,GPIO_Pin_11);GPIO_ResetBits(GPIOE,GPIO_Pin_13);GPIO_ResetBits(GPIOB,GPIO_Pin_12);\
									GPIO_ResetBits(GPIOB,GPIO_Pin_14);GPIO_ResetBits(GPIOD,GPIO_Pin_10);GPIO_ResetBits(GPIOE,GPIO_Pin_9);

#define sevenSegmentOneDisplayOne  	GPIO_ResetBits(GPIOE,GPIO_Pin_13);GPIO_ResetBits(GPIOB,GPIO_Pin_12);

#define sevenSegmentOneDisplayTwo  	GPIO_ResetBits(GPIOE,GPIO_Pin_11);GPIO_ResetBits(GPIOE,GPIO_Pin_13);GPIO_ResetBits(GPIOB,GPIO_Pin_14);\
									GPIO_ResetBits(GPIOD,GPIO_Pin_10);GPIO_ResetBits(GPIOE,GPIO_Pin_7);

#define sevenSegmentOneDisplayThree	GPIO_ResetBits(GPIOE,GPIO_Pin_11);GPIO_ResetBits(GPIOE,GPIO_Pin_13);GPIO_ResetBits(GPIOB,GPIO_Pin_12);\
									GPIO_ResetBits(GPIOB,GPIO_Pin_14);GPIO_ResetBits(GPIOE,GPIO_Pin_7);

#define sevenSegmentOneDisplayFour	GPIO_ResetBits(GPIOE,GPIO_Pin_13);GPIO_ResetBits(GPIOB,GPIO_Pin_12);GPIO_ResetBits(GPIOE,GPIO_Pin_9);\
									GPIO_ResetBits(GPIOE,GPIO_Pin_7);

#define sevenSegmentOneDisplayFive	GPIO_ResetBits(GPIOE,GPIO_Pin_11);GPIO_ResetBits(GPIOB,GPIO_Pin_12);GPIO_ResetBits(GPIOB,GPIO_Pin_14);\
									GPIO_ResetBits(GPIOE,GPIO_Pin_9);GPIO_ResetBits(GPIOE,GPIO_Pin_7);

#define sevenSegmentOneDisplaySix	GPIO_ResetBits(GPIOE,GPIO_Pin_11);GPIO_ResetBits(GPIOB,GPIO_Pin_12);GPIO_ResetBits(GPIOB,GPIO_Pin_14);\
									GPIO_ResetBits(GPIOD,GPIO_Pin_10);GPIO_ResetBits(GPIOE,GPIO_Pin_9);GPIO_ResetBits(GPIOE,GPIO_Pin_7);

#define sevenSegmentOneDisplaySeven	GPIO_ResetBits(GPIOE,GPIO_Pin_11);GPIO_ResetBits(GPIOE,GPIO_Pin_13);GPIO_ResetBits(GPIOB,GPIO_Pin_12);

#define sevenSegmentOneDisplayEight	GPIO_ResetBits(GPIOE,GPIO_Pin_11);GPIO_ResetBits(GPIOE,GPIO_Pin_13);GPIO_ResetBits(GPIOB,GPIO_Pin_12);\
									GPIO_ResetBits(GPIOB,GPIO_Pin_14);GPIO_ResetBits(GPIOD,GPIO_Pin_10);GPIO_ResetBits(GPIOE,GPIO_Pin_9);\
									GPIO_ResetBits(GPIOE,GPIO_Pin_7);

#define sevenSegmentOneDisplayNine	GPIO_ResetBits(GPIOE,GPIO_Pin_11);GPIO_ResetBits(GPIOE,GPIO_Pin_13);GPIO_ResetBits(GPIOB,GPIO_Pin_12);\
									GPIO_ResetBits(GPIOB,GPIO_Pin_14);GPIO_ResetBits(GPIOE,GPIO_Pin_9);GPIO_ResetBits(GPIOE,GPIO_Pin_7);

#define sevenSegmentTwoDisplayZero 	GPIO_ResetBits(GPIOD,GPIO_Pin_11);GPIO_ResetBits(GPIOB,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_10);\
									GPIO_ResetBits(GPIOE,GPIO_Pin_14);GPIO_ResetBits(GPIOB,GPIO_Pin_10);GPIO_ResetBits(GPIOB,GPIO_Pin_11);

#define sevenSegmentTwoDisplayOne  	GPIO_ResetBits(GPIOB,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_10);

#define sevenSegmentTwoDisplayTwo  	GPIO_ResetBits(GPIOD,GPIO_Pin_11);GPIO_ResetBits(GPIOB,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_14);\
									GPIO_ResetBits(GPIOB,GPIO_Pin_10);GPIO_ResetBits(GPIOE,GPIO_Pin_15);

#define sevenSegmentTwoDisplayThree	GPIO_ResetBits(GPIOD,GPIO_Pin_11);GPIO_ResetBits(GPIOB,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_10);\
									GPIO_ResetBits(GPIOE,GPIO_Pin_14);GPIO_ResetBits(GPIOE,GPIO_Pin_15);

#define sevenSegmentTwoDisplayFour	GPIO_ResetBits(GPIOB,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_10);GPIO_ResetBits(GPIOB,GPIO_Pin_11);\
									GPIO_ResetBits(GPIOE,GPIO_Pin_15);

#define sevenSegmentTwoDisplayFive	GPIO_ResetBits(GPIOD,GPIO_Pin_11);GPIO_ResetBits(GPIOE,GPIO_Pin_10);GPIO_ResetBits(GPIOE,GPIO_Pin_14);\
									GPIO_ResetBits(GPIOB,GPIO_Pin_11);GPIO_ResetBits(GPIOE,GPIO_Pin_15);

#define sevenSegmentTwoDisplaySix	GPIO_ResetBits(GPIOD,GPIO_Pin_11);GPIO_ResetBits(GPIOE,GPIO_Pin_10);GPIO_ResetBits(GPIOE,GPIO_Pin_14);\
									GPIO_ResetBits(GPIOB,GPIO_Pin_10);GPIO_ResetBits(GPIOB,GPIO_Pin_11);GPIO_ResetBits(GPIOE,GPIO_Pin_15);

#define sevenSegmentTwoDisplaySeven	GPIO_ResetBits(GPIOD,GPIO_Pin_11);GPIO_ResetBits(GPIOB,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_10);\


#define sevenSegmentTwoDisplayEight	GPIO_ResetBits(GPIOD,GPIO_Pin_11);GPIO_ResetBits(GPIOB,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_10);\
									GPIO_ResetBits(GPIOE,GPIO_Pin_14);GPIO_ResetBits(GPIOB,GPIO_Pin_10);GPIO_ResetBits(GPIOB,GPIO_Pin_11);\
									GPIO_ResetBits(GPIOE,GPIO_Pin_15);

#define sevenSegmentTwoDisplayNine	GPIO_ResetBits(GPIOD,GPIO_Pin_11);GPIO_ResetBits(GPIOB,GPIO_Pin_13);GPIO_ResetBits(GPIOE,GPIO_Pin_10);\
									GPIO_ResetBits(GPIOE,GPIO_Pin_14);GPIO_ResetBits(GPIOB,GPIO_Pin_11);GPIO_ResetBits(GPIOE,GPIO_Pin_15);

#define sevenSegmentReset			GPIO_SetBits(GPIOE,GPIO_Pin_9);GPIO_SetBits(GPIOE,GPIO_Pin_7);GPIO_SetBits(GPIOB,GPIO_Pin_12);\
									GPIO_SetBits(GPIOB,GPIO_Pin_14);GPIO_SetBits(GPIOD,GPIO_Pin_10);GPIO_SetBits(GPIOE,GPIO_Pin_11);\
									GPIO_SetBits(GPIOE,GPIO_Pin_13);GPIO_SetBits(GPIOB,GPIO_Pin_11);GPIO_SetBits(GPIOE,GPIO_Pin_15);\
									GPIO_SetBits(GPIOE,GPIO_Pin_10);GPIO_SetBits(GPIOE,GPIO_Pin_14);GPIO_SetBits(GPIOB,GPIO_Pin_10);\
									GPIO_SetBits(GPIOD,GPIO_Pin_11);GPIO_SetBits(GPIOB,GPIO_Pin_13);GPIO_SetBits(GPIOB,GPIO_Pin_15);\
									GPIO_SetBits(GPIOE,GPIO_Pin_8);
#endif
/*-----------------------------Exported functions-------------------------------*/
void sevenSegmentInit(void);
void sevenSegmentIntToDisplay(int intToDisplay);

#endif
