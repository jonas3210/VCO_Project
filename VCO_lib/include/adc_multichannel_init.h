/**
******************************************************************************
  * @file    adc_multichannel_init.h
  * @author  Frieder Jespers
  * @version V.0.0
  * @date    01/09/2016
  * @brief   This file contains the headers of ADC Init
  ******************************************************************************
  * @copy
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_MULTICHANNEL_INIT_H
#define __ADC_MULTICHANNEL_INIT_H

/* Includes ------------------------------------------------------------------*/
#include <Global_Variables.h>
#include <stm32f4xx_adc.h>
#include <stm32f4xx_dma.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <math.h>
#include <stdio.h>
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
//ADC Input Values
#define INPUT_FREQUENCY_FINE_VALUE ADC_Values[5]
#define INPUT_AUDIO_VALUE ADC_Values[1]
#define INPUT_MIX_VALUE ADC_Values[3]
#define INPUT_FM_VALUE ADC_Values[4]
#define INPUT_PWM_VALUE ADC_Values[0]
#define INPUT_FREQUENCY_COARSE_VALUE ADC_Values[6]
#define INPUT_WAVESHAPE_VALUE ADC_Values[2]

#define ADC_VALUE_CHANGE_THRESHOLD 32 //Defines noise Level of Inputs for stable ADC Values
//Amount of ADC-Channels
#define CHANNEL_AMOUNT 7


volatile uint16_t ADC_Buffer[CHANNEL_AMOUNT];//ADC Buffer with control input values
volatile uint16_t ADC_Values[CHANNEL_AMOUNT];//ADC Values after Stabilization

/* Exported functions ------------------------------------------------------- */

void ADC1_Poti_Init(void);//Init of Multichannel-ADC1-Input
void Get_ADC_Values(void);
#endif /* __ADC_MULTICHANNEL_INIT_H */
