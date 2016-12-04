/********************************************************************************
  * @file    saveBanks.c
  * @author  Christopher Ottens
  * @version V.0.0
  * @date    19.11.16
  * @brief   This file contains the functions to save the bank structures
*********************************************************************************/
/*
/**
 *
 *
void saveBanksInit(void)
{
	/* Unlock the Flash Program Erase controller */
	//FLASH_Unlock();

	/* EEPROM Init */
	//EE_Init();
//}

/**
 *	This function saves the actual values of the vco-struct
 *
void saveBank(void)
{
	int16_t tempShifted;

	//VCO1
	tempShifted = ((int16_t) vco1.Phase_Shift >> 16 );			//Phase_Shift Bit 31-16
	EE_WriteVariable(adressTable[selectedBank][0],tempShifted);
	tempShifted2 = (uint16_t) vco1.Phase_Shift;					//Phase_Shift Bit 15-0
	EE_WriteVariable(adressTable[selectedBank][1],tempShifted2);

	tempShifted = ((int16_t) vco1.Octave_Index >> 16 );		//Octave_Index Bit 31-16
	EE_WriteVariable(adressTable[selectedBank][2],tempShifted);
	tempShifted2 = (uint16_t) vco1.Octave_Index;					//Octave_Index Bit 15-0
	EE_WriteVariable(adressTable[selectedBank][3],tempShifted2);

	tempShifted = ((int16_t) vco1.Phase_Mod_Value >> 16 );		//Phase_Mod_Value Bit 31-16
	EE_WriteVariable(adressTable[selectedBank][4],tempShifted);
	tempShifted2 = (uint16_t) vco1.PhaseModValue;				//Phase_Mod_Value Bit 15-0
	EE_WriteVariable(adressTable[selectedBank][5],tempShifted2);

	tempShifted = ((int16_t) vco1.Shape_Value >> 16 );			//Shape_Value Bit 31-16
	EE_WriteVariable(adressTable[selectedBank][6],tempShifted);
	tempShifted2 = (uint16_t) vco1.Shape_Value;					//Shape_Value Bit 15-0
	EE_WriteVariable(adressTable[selectedBank][7],tempShifted2);

	tempShifted = (int16_t) vco1.FM_Value;						//FM_Value
	EE_WriteVariable(adressTable[selectedBank][8],tempShifted);

	tempShifted = ((int16_t) vco1.Mix_Value >> 16 );			//Mix_Value Bit 31-16
	EE_WriteVariable(adressTable[selectedBank][9],tempShifted);
	tempShifted2 = (uint16_t) vco1.Mix_Value;					//Mix_Value Bit 15-0
	EE_WriteVariable(adressTable[selectedBank][10],tempShifted2);

	//VCO2
	tempShifted = ((int16_t) vco2.Phase_Shift >> 16 );			//Phase_Shift Bit 31-16
	EE_WriteVariable(adressTable[selectedBank][11],tempShifted);
	tempShifted2 = (uint16_t) vco2.Phase_Shift;					//Phase_Shift Bit 15-0
	EE_WriteVariable(adressTable[selectedBank][12],tempShifted2);

	tempShifted = ((int16_t) vco2.Octave_Index >> 16 );		//Octave_Index Bit 31-16
	EE_WriteVariable(adressTable[selectedBank][13],tempShifted);
	tempShifted2 = (uint16_t) vco2.Octave_Index;					//Octave_Index Bit 15-0
	EE_WriteVariable(adressTable[selectedBank][14],tempShifted2);

	tempShifted = ((int16_t) vco2.Phase_Mod_Value >> 16 );		//Phase_Mod_Value Bit 31-16
	EE_WriteVariable(adressTable[selectedBank][15],tempShifted);
	tempShifted2 = (uint16_t) vco2.PhaseModValue;				//Phase_Mod_Value Bit 15-0
	EE_WriteVariable(adressTable[selectedBank][16],tempShifted2);

	tempShifted = ((int16_t) vco2.Shape_Value >> 16 );			//Shape_Value Bit 31-16
	EE_WriteVariable(adressTable[selectedBank][17],tempShifted);
	tempShifted2 = (uint16_t) vco2.Shape_Value;					//Shape_Value Bit 15-0
	EE_WriteVariable(adressTable[selectedBank][18],tempShifted2);

	tempShifted = (int16_t) vco2.FM_Value;						//FM_Value
	EE_WriteVariable(adressTable[selectedBank][19],tempShifted);

	tempShifted = ((int16_t) vco2.Mix_Value >> 16 );			//Mix_Value Bit 31-16
	EE_WriteVariable(adressTable[selectedBank][20],tempShifted);
	tempShifted2 = (uint16_t) vco2.Mix_Value;					//Mix_Value Bit 15-0
	EE_WriteVariable(adressTable[selectedBank][21],tempShifted2);

}

/**
 *	This function loads a saved bank(the actual bank) and transfers it values into the vco-struct
 *
void loadBank(void)
{
	int16_t tempPartOne;
	uint16_t tempPartTwo;

	VCO1_Lock.Shape_Lock = 1;
	VCO1_Lock.Freq_Lock = 1;
	VCO1_Lock.Freq_Fine_Lock = 1;
	VCO1_Lock.FM_Lock = 1;
	VCO1_Lock.Phase_Lock = 1;
	VCO1_Lock.Mix_Lock = 1;
	VCO1_Lock.Audio_Lock = 1;

	VCO2_Lock.Shape_Lock = 1;
	VCO2_Lock.Freq_Lock = 1;
	VCO2_Lock.Freq_Fine_Lock = 1;
	VCO2_Lock.FM_Lock = 1;
	VCO2_Lock.Phase_Lock = 1;
	VCO2_Lock.Mix_Lock = 1;
	VCO2_Lock.Audio_Lock = 1;

	//VCO1
	EE_ReadVariable(adressTable[selectedBank][0],tempPartOne);	//Phase_Shift
	EE_ReadVariable(adressTable[selectedBank][1],tempPartTwo);
	vco1.Phase_Shift = ( (int32_t) tempPartOne << 16 ) | tempPartTwo;

	EE_ReadVariable(adressTable[selectedBank][2],tempPartOne);	//Octave_Index
	EE_ReadVariable(adressTable[selectedBank][3],tempPartTwo);
	vco1.Octave_Index = ( (int32_t) tempPartOne << 16 ) | tempPartTwo;

	EE_ReadVariable(adressTable[selectedBank][4],tempPartOne);	//Phase_Mod_Value
	EE_ReadVariable(adressTable[selectedBank][5],tempPartTwo);
	vco1.Phase_Mod_Value = ( (int32_t) tempPartOne << 16 ) | tempPartTwo;

	EE_ReadVariable(adressTable[selectedBank][6],tempPartOne);	//Shape_Value
	EE_ReadVariable(adressTable[selectedBank][7],tempPartTwo);
	vco1.Shape_Value = ( (int32_t) tempPartOne << 16 ) | tempPartTwo;

	EE_ReadVariable(adressTable[selectedBank][8],tempPartOne);	//FM_Value
	vco1.FM_Value = tempPartOne;

	EE_ReadVariable(adressTable[selectedBank][9],tempPartOne);	//Mix_Value
	EE_ReadVariable(adressTable[selectedBank][10],tempPartTwo);
	vco1.Mix_Value = ( (int32_t) tempPartOne << 16 ) | tempPartTwo;

	//VCO2
	EE_ReadVariable(adressTable[selectedBank][11],tempPartOne);	//Phase_Shift
	EE_ReadVariable(adressTable[selectedBank][12],tempPartTwo);
	vco2.Phase_Shift = ( (int32_t) tempPartOne << 16 ) | tempPartTwo;

	EE_ReadVariable(adressTable[selectedBank][13],tempPartOne);	//Octave_Index
	EE_ReadVariable(adressTable[selectedBank][14],tempPartTwo);
	vco2.Octave_Index = ( (int32_t) tempPartOne << 16 ) | tempPartTwo;

	EE_ReadVariable(adressTable[selectedBank][15],tempPartOne);	//Phase_Mod_Value
	EE_ReadVariable(adressTable[selectedBank][16],tempPartTwo);
	vco2.Phase_Mod_Value = ( (int32_t) tempPartOne << 16 ) | tempPartTwo;

	EE_ReadVariable(adressTable[selectedBank][17],tempPartOne);	//Shape_Value
	EE_ReadVariable(adressTable[selectedBank][18],tempPartTwo);
	vco2.Shape_Value = ( (int32_t) tempPartOne << 16 ) | tempPartTwo;

	EE_ReadVariable(adressTable[selectedBank][19],tempPartOne);	//FM_Value
	vco2.FM_Value = tempPartOne;

	EE_ReadVariable(adressTable[selectedBank][20],tempPartOne);	//Mix_Value
	EE_ReadVariable(adressTable[selectedBank][21],tempPartTwo);
	vco2.Mix_Value = ( (int32_t) tempPartOne << 16 ) | tempPartTwo;

}
*/
