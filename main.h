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
#include <Global_Variables.h>
#include <stm32f4xx_adc.h>
#include <stm32f4xx_dma.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include "adc_multichannel_init.h"
#include "codec_configuration.h"
#include"debounceKey.h"
#include "wavetables.h"
#include "fixed_point.h"
#include <math.h>
#include "sevenSegment.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define LED_HOLD_ON GPIO_ResetBits(GPIOD, GPIO_Pin_7)
#define LED_HOLD_OFF GPIO_SetBits(GPIOD, GPIO_Pin_7)
#define LED_LINLOG_ON GPIO_ResetBits(GPIOB, GPIO_Pin_4)
#define LED_LINLOG_OFF GPIO_SetBits(GPIOB, GPIO_Pin_4)
#define LED_REC_ON GPIO_ResetBits(GPIOD, GPIO_Pin_5)
#define LED_REC_OFF GPIO_SetBits(GPIOD, GPIO_Pin_5)
#define LED_SAVE_ON GPIO_ResetBits(GPIOE, GPIO_Pin_6)
#define LED_SAVE_OFF GPIO_SetBits(GPIOE, GPIO_Pin_6)
#define LED_LOAD_ON GPIO_ResetBits(GPIOC, GPIO_Pin_13)
#define LED_LOAD_OFF GPIO_SetBits(GPIOC, GPIO_Pin_13)
#define LED_ORIGIN_ON GPIO_ResetBits(GPIOE, GPIO_Pin_4)
#define LED_ORIGIN_OFF GPIO_SetBits(GPIOE, GPIO_Pin_4)
#define LED_OUT1_ON GPIO_ResetBits(GPIOD, GPIO_Pin_3)
#define LED_OUT1_OFF GPIO_SetBits(GPIOD, GPIO_Pin_3)
#define LED_OUT2_ON GPIO_ResetBits(GPIOD, GPIO_Pin_1)
#define LED_OUT2_OFF GPIO_SetBits(GPIOD, GPIO_Pin_1)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


