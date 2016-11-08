/**
  ******************************************************************************
  * @file    adc_multichannel_init.c
  * @author  Frieder Jespers
  * @version V1.0.0
  * @date    03/09/2016
  * @brief   This file contains the initialization for ADC-Multichannel-use with DMA-Controller
  ******************************************************************************
  * @copy
  */

/* Includes ------------------------------------------------------------------*/
#include "adc_multichannel_init.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

//*******************************************************************
/**
  * @brief  Initialization of Hardware for ADC-Read: GPIO, ADC, DMA
  * Get Values from the following defines:
  * INPUT_FREQUENCY_FINE_VALUE
  * INPUT_AUDIO_VALUE
  * INPUT_MIX_VALUE
  * INPUT_FM_VALUE
  * INPUT_PWM_VALUE
  * INPUT_FREQUENCY_COARSE_VALUE
  * INPUT_WAVESHAPE_VALUE
  * @param  None
  * @retval None
  */
void ADC1_Poti_Init(void){

	//********************************************************
	//Clock Configuration
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // Enable Clock for ADC1, GPIO PORT A-C
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2| RCC_AHB1Periph_GPIOA| RCC_AHB1Periph_GPIOB| RCC_AHB1Periph_GPIOC, ENABLE);
	
	//********************************************************
	//GPIO Configuration
	GPIO_InitTypeDef GPIO_InitStruct; // Struct for GPIO_Init

	GPIO_StructInit(&GPIO_InitStruct);//reset init Structure
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;//Select Channel 1-3
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;//Select Analog input mode
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//GPIO Speed 50MHz
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;//No Pullup Resistor
	GPIO_Init(GPIOA, &GPIO_InitStruct);//load setted values to Hardwareregister

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;//Select Channel 8-9
	GPIO_Init(GPIOB, &GPIO_InitStruct);//load setted values to Hardwareregister

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;//Select Channel 11-12
	GPIO_Init(GPIOC, &GPIO_InitStruct);//load setted values to Hardwareregister

	//********************************************************
	//Structures for Initialization
	ADC_InitTypeDef ADC_Init_Struct;//Struct for ADC Init
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	DMA_InitTypeDef DMA_InitStruct;

	//***************************************************************
	//DMA Init
	DMA_DeInit(DMA2_Stream0);
	DMA_InitStruct.DMA_Channel = DMA_Channel_0;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;//
	DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)&ADC_Buffer;//Target adress
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;//Direction from ADC to memory
	DMA_InitStruct.DMA_BufferSize = CHANNEL_AMOUNT;//Buffersize = Amount of channels
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;// No peripheral adress increment
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;//adress increment in memory
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;// ADC1 Data size 16Bit
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//Memory data size 16Bit
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_Low;//Low priority
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;//Fifomode disabled
	DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0, &DMA_InitStruct);//load values into register
	DMA_Cmd(DMA2_Stream0, ENABLE);//Enable DMA2_Stream0

	//*******************************************************************
	//ADC Commont Init
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;//
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div2;//
	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStruct);
	
	//*******************************************************************
	//ADC1 Init
	ADC_Init_Struct.ADC_Resolution = ADC_Resolution_12b; // ADC Resolution 12Bit
	ADC_Init_Struct.ADC_ScanConvMode = ENABLE;// Convert multiple Channels
	ADC_Init_Struct.ADC_ContinuousConvMode = ENABLE;//continuous conversion mode
	ADC_Init_Struct.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;//no external triggering
	ADC_Init_Struct.ADC_DataAlign = ADC_DataAlign_Left;//
	ADC_Init_Struct.ADC_NbrOfConversion = CHANNEL_AMOUNT;//Amount of Channels
	ADC_Init(ADC1, &ADC_Init_Struct); //load set values to Hardware register

	//*******************************************************************
	//Channelconfiguration
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_480Cycles);//PA1
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_480Cycles);//PA2
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 3, ADC_SampleTime_480Cycles);//PA3
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 4, ADC_SampleTime_480Cycles);//PB0
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 5, ADC_SampleTime_480Cycles);//PB1
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 6, ADC_SampleTime_480Cycles);//PC1
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 7, ADC_SampleTime_480Cycles);//PC2

	ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE);// Enable DMA request after last transfer

	ADC_DMACmd(ADC1, ENABLE);//Enable DMA for ADC1
	ADC_Cmd(ADC1, ENABLE);//Enable ADC1


	//Calibration
	/*ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));// Wait until reset finished
	ADC_StartCalibration(ADC1);//Start Calibration
	while(ADC_GetCalibrationStatus(ADC1));//wait until calibration is complete
	*/
	ADC_SoftwareStartConv(ADC1);
}
void Get_ADC_Values(void){
	for(int i=0; i<CHANNEL_AMOUNT;i++){
		if(fabs((ADC_Buffer[i]>>4)-ADC_Values[i])>ADC_VALUE_CHANGE_THRESHOLD){
			ADC_Values[i]=(ADC_Buffer[i]>>4);
		}
	}
}
