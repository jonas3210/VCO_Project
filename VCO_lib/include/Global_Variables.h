/**
******************************************************************************
  * @file    global_variables.h
  * @author  Frieder Jespers
  * @version V.0.0
  * @date    02/09/2016
  * @brief   This file contains all global variables of the VCO Project
  ******************************************************************************
  * @copy
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GLOBAL_VARIABLES_H
#define __GLOBAL_VARIABLES_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
/* Global defines -------------------------------------------------------------*/
//Sample Frequency
#define SAMPLE_FREQUENCY 48000;
//Output frequency
#define OUTPUT_FREQUENCY 10000

#define TUNING_WORD (uint32_t)(OUTPUT_FREQUENCY*2^32/SAMPLE_FREQUENCY)
//I2S Buffersize
#define I2S_BUFFERSIZE 1024
#define TABLE_SIZE 2048

#define ADC_RESOLUTION 4096

#define TONE_FREQUENCY_C0 16.3516 //Fundamental C0 Tone frequency

#define CV_FACTOR_1 0.1744170667//(I2S_BUFFERSIZE*TONE_FREQUENCY_C0/(2*SAMPLE_FREQUENCY))
#define CV_FACTOR_2 0.0024420024//0.0097751712//10/(ADC_RESOLUTION-1)
#define PI 3.14159265359

/* Exported types ------------------------------------------------------------*/
typedef struct{
	int16_t Output_Buffer[I2S_BUFFERSIZE/2];//Output Buffer Channel1
	int32_t Phase_Accumulator;
	int32_t Phase_Shift;
	int32_t Octave_Index;
	int16_t PWM_Value;
	int32_t Shape_Value;
	int16_t FM_Value;
	int32_t Mix_Value;
}VCO;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/

VCO VCO1;
VCO VCO2;

volatile int16_t i2s_Out[I2S_BUFFERSIZE];//I2S Output Buffer

volatile uint8_t Transfer_Complete_Flag;//Flag for I2S Transmission finished -> Start point of wave calculation
#endif /* __GLOBAL_VARIABLES_H */
