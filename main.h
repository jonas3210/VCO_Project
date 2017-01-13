/**
  ******************************************************************************
  * @file    main.h
  * @author  Frieder Jespers
  * @version V1.0.0
  * @date    03/09/2016
  * @brief   This file contains main includes and declarations
  ******************************************************************************
  * @copy
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <Global_Variables.h>
#include <stm32f4xx_adc.h>
#include <stm32f4xx_dma.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_flash.h>
#include "adc_multichannel_init.h"
#include "codec_configuration.h"
#include "eeprom.h"
#include "saveBanks.h"
#include"inputProcessing.h"
#include "wavetables.h"
#include "fixed_point.h"
#include "sevenSegment.h"



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define sevenSegmentReset			GPIO_SetBits(GPIOE,GPIO_Pin_9);GPIO_SetBits(GPIOE,GPIO_Pin_7);GPIO_SetBits(GPIOB,GPIO_Pin_12);\
									GPIO_SetBits(GPIOB,GPIO_Pin_14);GPIO_SetBits(GPIOD,GPIO_Pin_10);GPIO_SetBits(GPIOE,GPIO_Pin_11);\
									GPIO_SetBits(GPIOE,GPIO_Pin_13);GPIO_SetBits(GPIOB,GPIO_Pin_11);GPIO_SetBits(GPIOE,GPIO_Pin_15);\
									GPIO_SetBits(GPIOE,GPIO_Pin_10);GPIO_SetBits(GPIOE,GPIO_Pin_14);GPIO_SetBits(GPIOB,GPIO_Pin_10);\
									GPIO_SetBits(GPIOD,GPIO_Pin_11);GPIO_SetBits(GPIOB,GPIO_Pin_13);GPIO_SetBits(GPIOB,GPIO_Pin_15);\
									GPIO_SetBits(GPIOE,GPIO_Pin_8);
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
uint16_t Linear_Interpolation(int32_t Accumulator,const int16_t Table[],uint16_t Table_Size);
int32_t Subtable_Interpolation(int32_t Accumulator, int32_t Ocatve_Index,const int16_t Tables[][2048], uint16_t Table_Size);
int32_t Waveshape_Modulation(VCO VCO);
int16_t Mix_Modulation(int32_t Sample1, int32_t Sample2, int32_t Mix_Value);
void LED_Init(void);
void LED_Button_Test(void);
void VCO_Lock_Init(void);
void Increment_Encoder_Test(void);
void Button_Processing(void);
/* Private functions ---------------------------------------------------------*/


