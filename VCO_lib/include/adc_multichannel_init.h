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
#include <fixed_point.h>
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
//ADC Input Values
#define INPUT_FREQUENCY_FINE_VALUE ADC_Values[5]
#define INPUT_AUDIO_VALUE ADC_Values[1]
#define INPUT_MIX_VALUE ADC_Values[3]
#define INPUT_FM_VALUE ADC_Values[4]
#define INPUT_PHASE_VALUE ADC_Values[0]
#define INPUT_FREQUENCY_COARSE_VALUE ADC_Values[6]
#define INPUT_WAVESHAPE_VALUE ADC_Values[2]
#define INPUT_FM_MIX_VALUE ADC_Values[7]
//ADC Input Mean Values
#define INPUT_FREQUENCY_FINE_MEAN_VALUE ADC_Mean_Values[5]
#define INPUT_AUDIO_MEAN_VALUE ADC_Mean_Values[1]
#define INPUT_MIX_MEAN_VALUE ADC_Mean_Values[3]
#define INPUT_FM_MEAN_VALUE ADC_Mean_Values[4]
#define INPUT_PHASE_MEAN_VALUE ADC_Mean_Values[0]
#define INPUT_FREQUENCY_COARSE_MEAN_VALUE ADC_Mean_Values[6]
#define INPUT_WAVESHAPE_MEAN_VALUE ADC_Mean_Values[2]
#define INPUT_FM_MIX_MEAN_VALUE ADC_Mean_Values[7]

#define ADC_VALUE_CHANGE_THRESHOLD 2 //Defines noise Level of Inputs for stable ADC Values
#define ADC_MEAN_VALUE_CHANGE_THRESHOLD 11 //Defines noise Level of Inputs for stable ADC Values
#define LOCK_THRESHOLD 10//Defines necessary value change for unlock parameter
//Amount of ADC-Channels
#define CHANNEL_AMOUNT 8

#define ADC_RESOLUTION 4096

#define MEAN_SIZE 128 //Number of Values for floating mean

#define ADC_FREQ_CORRECTION_FACTOR 1.072
#define ADC_FREQ__FINE_CORRECTION_FACTOR 1.039
#define ADC_PHASE_CORRECTION_FACTOR 1.072
#define ADC_SHAPE_CORRECTION_FACTOR 1.087
#define ADC_MIX_CORRECTION_FACTOR 1.07
#define ADC_FM_CORRECTION_FACTOR 1
#define ADC_FM_MIX_CORRECTION_FACTOR 1
#define ADC_AUDIO_CORRECTION_FACTOR 1

volatile int ADC_Correction_Factor[CHANNEL_AMOUNT];

		/*
		ADC_PHASE_CORRECTION_FACTOR,
		ADC_AUDIO_CORRECTION_FACTOR,
		ADC_SHAPE_CORRECTION_FACTOR,
		ADC_MIX_CORRECTION_FACTOR,
		ADC_FM_CORRECTION_FACTOR,
		ADC_FREQ__FINE_CORRECTION_FACTOR,
		ADC_FREQ_CORRECTION_FACTOR,
		ADC_FM_MIX_CORRECTION_FACTOR*/

volatile uint16_t Input_Mean_Buffer[CHANNEL_AMOUNT][MEAN_SIZE];

volatile uint16_t ADC_Mean_Values[CHANNEL_AMOUNT];


volatile uint16_t ADC_Buffer[CHANNEL_AMOUNT];//ADC Buffer with control input values
volatile uint16_t ADC_Values[CHANNEL_AMOUNT];//ADC Values after Stabilization
volatile uint16_t ADC_Differences[CHANNEL_AMOUNT];// ADC Value differences to last Value
volatile uint16_t ADC_Mean_Differences[CHANNEL_AMOUNT];// ADC Value differences to last Value




/* Exported functions ------------------------------------------------------- */

void ADC1_Poti_Init(void);//Init of Multichannel-ADC1-Input
void Get_ADC_Values(void);//REfresh ADC Values
Parameter_Lock Get_Lock_Values(Parameter_Lock VCO_Temp_Lock);//Refresh Pot Lock Values
void Get_Mean_Values(void);//Refresh ADC Mean Values
#endif /* __ADC_MULTICHANNEL_INIT_H */
