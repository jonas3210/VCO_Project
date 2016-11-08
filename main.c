/**
 ******************************************************************************
 * @file    main.c
 * @author  Frieder Jespers
 * @version V.0.0
 * @date    02/09/2016
 * @brief   This file contains the main function
 ******************************************************************************
 *****************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** *****************************************************************************/
/* function prototypes ------------------------------------------------------------------*/
uint16_t Linear_Interpolation(int32_t Accumulator, int16_t Table[],uint16_t Table_Size);
int32_t Subtable_Interpolation(int32_t Accumulator,int32_t Ocatve_Index, int16_t Tables[][2048], uint16_t Table_Size);
int32_t Waveshape_Modulation(VCO VCO);
int16_t Mix_Modulation(int32_t Sample1, int32_t Sample2, int32_t Mix_Value);
void LED_Init(void);
void LED_Button_Test(void);
/* main function--------------------------------------------------------------*/
/**
 *
 */

int main(void) {
	SystemInit();

	//*******************************************************************
	// GPIO Init for Transfer Blinking LED

	LED_Init();
	//*******************************************************************
	// Init of ADC
	ADC1_Poti_Init();

	//*******************************************************************
	// Init of Audio Transfer
	codec_Init(); // Hardware Init for Codec Communication
	codec_Configuration(); // Codec Init for Audio Transfer
	codec_DMA_Init(); // DMA Init for I2S Communication
	debounceKeyInit();
	//sevenSegmentInit();

	const int32_t Fixed_Table_Size = INT_TO_FIXED(TABLE_SIZE);
	GPIO_SetBits(GPIOE, GPIO_Pin_11);

	while (1) {
		Get_ADC_Values();
		LED_Button_Test();
		//sevenSegmentIntToDisplay(1);
		if(INPUT_BUTTON_OUT1){
			VCO1.Phase_Shift = DOUBLE_TO_FIXED(CV_FACTOR_1 * pow(2,(INPUT_FREQUENCY_COARSE_VALUE+(INPUT_FREQUENCY_FINE_VALUE>>3)) * CV_FACTOR_2)*4); //Phase scaling for 1V/Octave CV
			VCO1.Octave_Index = DOUBLE_TO_FIXED((INPUT_FREQUENCY_COARSE_VALUE+(INPUT_FREQUENCY_FINE_VALUE>>3))/409.5);
			VCO1.Mix_Value = DOUBLE_TO_FIXED(INPUT_MIX_VALUE/4095.0);
			VCO1.Shape_Value = DOUBLE_TO_FIXED(INPUT_WAVESHAPE_VALUE/1365.0);

		}
		if(INPUT_BUTTON_OUT2){
			VCO2.Phase_Shift = DOUBLE_TO_FIXED(CV_FACTOR_1 * pow(2,(INPUT_FREQUENCY_COARSE_VALUE+(INPUT_FREQUENCY_FINE_VALUE>>3)) * CV_FACTOR_2)*4); //Phase scaling for 1V/Octave CV
			VCO2.Octave_Index = DOUBLE_TO_FIXED((INPUT_FREQUENCY_COARSE_VALUE+(INPUT_FREQUENCY_FINE_VALUE>>3))/409.5);
			VCO2.Mix_Value = DOUBLE_TO_FIXED(INPUT_MIX_VALUE/4095.0);
			VCO2.Shape_Value = DOUBLE_TO_FIXED(INPUT_WAVESHAPE_VALUE/1365.0);
		}
		//After Data transfer Complete begin Calculation of new Values
		if (Transfer_Complete_Flag) {
			for (int i = 0; i < I2S_BUFFERSIZE / 2; i++) {
				int32_t VCO1_Waveshaped_Sample = Waveshape_Modulation(VCO1);
				int32_t VCO2_Waveshaped_Sample = Waveshape_Modulation(VCO2);
				VCO1.Output_Buffer[i] = Mix_Modulation(VCO1_Waveshaped_Sample,VCO2_Waveshaped_Sample,VCO1.Mix_Value);//(int16_t) FIXED_TO_INT(FIXED_MUL(temp1, INT_TO_FIXED(1)-VCO1.Mix_Value)+FIXED_MUL(temp2, VCO1.Mix_Value)); //crossfading the two tables
				VCO2.Output_Buffer[i] = Mix_Modulation(VCO1_Waveshaped_Sample,VCO2_Waveshaped_Sample,VCO1.Mix_Value);//(int16_t) FIXED_TO_INT(FIXED_MUL(temp1, INT_TO_FIXED(1)-VCO1.Mix_Value)+FIXED_MUL(temp2, VCO1.Mix_Value));//Mix_Modulation(VCO1_Waveshaped_Sample,VCO2_Waveshaped_Sample,VCO1.Mix_Value);//(int16_t) FIXED_TO_INT(FIXED_MUL(temp2, INT_TO_FIXED(1)-VCO2.Mix_Value)+FIXED_MUL(temp1, VCO2.Mix_Value)); //crossfading the two tables
				//VCO1.Output_Buffer[i] = Subtable_Interpolation(VCO1.Phase_Accumulator, VCO1.Octave_Index,Table_Triangle_Wave, TABLE_SIZE); //Linear_Interpolation(VCO1.Phase_Accumulator,Table_Saw_Wave[(int16_t)Int_Octave_Index],TABLE_SIZE);//////Copy new values
				//VCO2.Output_Buffer[i] = Subtable_Interpolation(VCO2.Phase_Accumulator, VCO2.Octave_Index,Table_Saw_Wave, TABLE_SIZE); //Linear_Interpolation(VCO2.Phase_Accumulator,Table_Saw_Wave[(int16_t)Int_Octave_Index],TABLE_SIZE);//Copy new values
				VCO1.Phase_Accumulator = VCO1.Phase_Accumulator + VCO1.Phase_Shift;
				VCO2.Phase_Accumulator = VCO2.Phase_Accumulator + VCO2.Phase_Shift;
				if ((VCO1.Phase_Accumulator) >= Fixed_Table_Size)
					VCO1.Phase_Accumulator -= Fixed_Table_Size; //Wrap around when reached half Buffer size
				if ((VCO2.Phase_Accumulator) >= Fixed_Table_Size)
					VCO2.Phase_Accumulator -= Fixed_Table_Size;
			}
			Transfer_Complete_Flag = 0;
		}
		//printf("Freq: %d, Freq fine: %d, PWM: %d, Shape: %d, FM: %d, Mix: %d,\n", INPUT_FREQUENCY_COARSE_VALUE,INPUT_FREQUENCY_FINE_VALUE, INPUT_PWM_VALUE, INPUT_WAVESHAPE_VALUE, INPUT_FM_VALUE, INPUT_MIX_VALUE);
	}
}

//*******************************************************************
/**
 * @brief  Function interpolates between the two samples closest to the fraction number
 * @param  Accumulator: Phase Accumulator of VCO
 * @param  Table: Pointer to Subtable
 * @param  TABLE_SIZE: Size of Subtable
 * @retval Interpolated int32_t sample value
 */
uint16_t Linear_Interpolation(int32_t Accumulator, int16_t Table[],
		uint16_t Table_Size) {
	int32_t Integer_Part = FIXED_TO_INT(FIXED_INT_PART(Accumulator)); //Get int Part
	int32_t Fractual_Part = FIXED_FRACTION_PART(Accumulator); //get fraction part
	int32_t Sample0 = INT_TO_FIXED(Table[Integer_Part]); //get first sample
	int32_t Sample1;
	if (Integer_Part + 1 < Table_Size) { //wrap around at the end of the table
		Sample1 = INT_TO_FIXED(Table[Integer_Part+1]);
	} else {
		INT_TO_FIXED(Sample1 = Table[0]);
	}
	return (int16_t)FIXED_TO_INT(Sample0+ FIXED_MUL(Sample1-Sample0, Fractual_Part)); //calculate linear interpolated result sample
}

//*******************************************************************
/**
 * @brief  Function builds weighted mean between two sub wavetables to reduce hearable energie difference(losses of harmonic frequencies) between the tables
 * @param  Accumulator: Phase Accumulator of VCO
 * @param  Octave_Index: Index for Octave(Subwavetable)
 * @param  Tables: Waveform Array with Subtables(10)
 * @param  TABLE_SIZE: Size of Subtable
 * @retval Interpolated int32_t sample value
 */
int32_t Subtable_Interpolation(int32_t Accumulator,int32_t Ocatve_Index,
		int16_t Tables[][2048], uint16_t Table_Size) {
	int32_t Integer_Part = FIXED_TO_INT(FIXED_INT_PART(Ocatve_Index)); //Get int Part
	int32_t Fractual_Part = FIXED_FRACTION_PART(Ocatve_Index); //get fraction part
	int32_t Low_Subtable_Sample =
			INT_TO_FIXED(Linear_Interpolation(Accumulator,Tables[Integer_Part],TABLE_SIZE)); //Interpolate lower subtable
	int32_t High_Subtable_Sample =
			INT_TO_FIXED(Linear_Interpolation(Accumulator,Tables[Integer_Part+1],TABLE_SIZE)); //Interpolate higher subtable
	return (FIXED_MUL(Low_Subtable_Sample, INT_TO_FIXED(1)-Fractual_Part)+FIXED_MUL(High_Subtable_Sample, Fractual_Part)); //crossfading the two tables
	//!!!!!!!!!< To do: improvement of crossfading, maybe use somehow logarithmic scale
}

//*******************************************************************
/**
 * @brief  Function crossfades between the different waveshapes
 * @param  VCO: VCO for waveshaping
 * @retval Waveshaped int32_t sample value
 */
int32_t Waveshape_Modulation(VCO VCO_Temp){
	int32_t Shape1_Value,Shape2_Value;
	int32_t Waveshape_Integer_Part = FIXED_TO_INT(FIXED_INT_PART(VCO_Temp.Shape_Value)); //Get int Part
	int32_t Waveshape_Fractual_Part = FIXED_FRACTION_PART(VCO_Temp.Shape_Value); //get fraction part
	switch(Waveshape_Integer_Part){
		case 0: Shape1_Value = INT_TO_FIXED(Linear_Interpolation(VCO_Temp.Phase_Accumulator,Table_Sine_Wave,TABLE_SIZE));
				Shape2_Value = Subtable_Interpolation(VCO_Temp.Phase_Accumulator,VCO_Temp.Octave_Index,Table_Triangle_Wave, TABLE_SIZE);
				return(FIXED_MUL(Shape1_Value, INT_TO_FIXED(1)-Waveshape_Fractual_Part)+FIXED_MUL(Shape2_Value, Waveshape_Fractual_Part));//Linear_Interpolation(VCO1.Phase_Accumulator,Table_Saw_Wave[(int16_t)Int_Octave_Index],TABLE_SIZE);//////Copy new values
		case 1: Shape1_Value = Subtable_Interpolation(VCO_Temp.Phase_Accumulator,VCO_Temp.Octave_Index,Table_Triangle_Wave, TABLE_SIZE);
				Shape2_Value = Subtable_Interpolation(VCO_Temp.Phase_Accumulator,VCO_Temp.Octave_Index,Table_Rect_Wave, TABLE_SIZE);
				return (FIXED_MUL(Shape1_Value, INT_TO_FIXED(1)-Waveshape_Fractual_Part)+FIXED_MUL(Shape2_Value, Waveshape_Fractual_Part));
		case 2: Shape1_Value = Subtable_Interpolation(VCO_Temp.Phase_Accumulator,VCO_Temp.Octave_Index,Table_Rect_Wave, TABLE_SIZE);
				Shape2_Value = Subtable_Interpolation(VCO_Temp.Phase_Accumulator,VCO_Temp.Octave_Index,Table_Saw_Wave, TABLE_SIZE);
				return (FIXED_MUL(Shape1_Value, INT_TO_FIXED(1)-Waveshape_Fractual_Part)+FIXED_MUL(Shape2_Value, Waveshape_Fractual_Part));
		case 3: return Subtable_Interpolation(VCO_Temp.Phase_Accumulator,VCO_Temp.Octave_Index,Table_Saw_Wave, TABLE_SIZE);
		default: return 0;
	}
}

//*******************************************************************
/**
 * @brief  Function crossfades between two Samples
 * @param  Sample1
 * @param  Sample2
 * @param  Mix_Value: Value for crossfading Position
 * @retval Mixed int16_t sample value
 */
int16_t Mix_Modulation(int32_t Sample1, int32_t Sample2, int32_t Mix_Value){
	return(int16_t) FIXED_TO_INT(FIXED_MUL(Sample1, INT_TO_FIXED(1)-Mix_Value)+FIXED_MUL(Sample2, Mix_Value));
}

//*******************************************************************
/**
 * @brief  Initialize LED Pins
 */
void LED_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); //Clock enable PortD
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // Output Mode
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; //LED linlog
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // Push Pull Mode
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // No pull resistors
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	LED_LINLOG_OFF;


	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); //Clock enable PortC
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // Output Mode
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //Load LED
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // Push Pull Mode
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // No pull resistors
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	LED_LOAD_OFF;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //Clock enable PortD
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // Output Mode
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5
			| GPIO_Pin_7 | GPIO_Pin_12 | GPIO_Pin_13; //LED Out2, LED Out1, LED REC, LED Hold, Onboard LEDs green and orange
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // Push Pull Mode
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // No pull resistors
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	LED_OUT1_OFF;
	LED_OUT2_OFF;
	LED_REC_OFF;
	LED_HOLD_OFF;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); //Clock enable PortE
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // Output Mode
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6|GPIO_Pin_11; //LED Origin, LED save
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // Push Pull Mode
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // No pull resistors
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	LED_ORIGIN_OFF;
	LED_SAVE_OFF;
}

//*******************************************************************
/**
 * @brief  Test function for Push Buttons and LEDs
 */
void LED_Button_Test(void) {
	if (INPUT_BUTTON_HOLD) {
		LED_HOLD_ON;
	} else {
		LED_HOLD_OFF;
	}
	if (INPUT_BUTTON_LINLOG) {
		LED_LINLOG_ON;
	} else {
		LED_LINLOG_OFF;
	}
	if (INPUT_BUTTON_OUT1) {
		LED_OUT1_ON;
	} else {
		LED_OUT1_OFF;
	}
	if (INPUT_BUTTON_OUT2) {
		LED_OUT2_ON;
	} else {
		LED_OUT2_OFF;
	}
	if (INPUT_BUTTON_REC) {
		LED_REC_ON;
	} else {
		LED_REC_OFF;
	}
}
