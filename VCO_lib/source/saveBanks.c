/********************************************************************************
  * @file    saveBanks.c
  * @author  Christopher Ottens
  * @version V.0.0
  * @date    14.12.16
  * @brief   This file contains the functions to save the bank structures
*********************************************************************************/

#include "saveBanks.h"

/**
 *
 */
void saveBanksInit(void)
{
	int i;

	//Generate AdressTable
	for(i=0;i<2100;i++)
	{
		VirtAddVarTab[i] = i;
	}

	/* Unlock the Flash Program Erase controller */
	FLASH_Unlock();

	/* EEPROM Init */
	EE_Init();
}

/**
 * This functions loads the parameters of VCO1 and VCO2
 */
void saveBank()
{
	int16_t tempShifted;

	//VCO1
	tempShifted = ((uint16_t) VCO1.Phase_Shift >> 16 );			//Phase_Shift Bit 31-16
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21],tempShifted);
	tempShifted = (uint16_t) VCO1.Phase_Shift;					//Phase_Shift Bit 15-0
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+1],tempShifted);

	tempShifted = ((uint16_t) VCO1.Octave_Index >> 16 );		//Octave_Index Bit 31-16
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+2],tempShifted);
	tempShifted = (uint16_t) VCO1.Octave_Index;					//Octave_Index Bit 15-0
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+3],tempShifted);

	tempShifted = ((uint16_t) VCO1.Phase_Mod_Value >> 16 );		//Phase_Mod_Value Bit 31-16
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+4],tempShifted);
	tempShifted = (uint16_t) VCO1.Phase_Mod_Value;				//Phase_Mod_Value Bit 15-0
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+5],tempShifted);

	tempShifted = ((uint16_t) VCO1.Shape_Value >> 16 );			//Shape_Value Bit 31-16
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+6],tempShifted);
	tempShifted = (uint16_t) VCO1.Shape_Value;					//Shape_Value Bit 15-0
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+7],tempShifted);

	tempShifted = (uint16_t) VCO1.FM_Value;						//FM_Value
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+8],tempShifted);

	tempShifted = ((uint16_t) VCO1.Mix_Value >> 16 );			//Mix_Value Bit 31-16
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+9],tempShifted);
	tempShifted = (uint16_t) VCO1.Mix_Value;					//Mix_Value Bit 15-0
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+10],tempShifted);

	//VCO2
	tempShifted = ((uint16_t) VCO2.Phase_Shift >> 16 );			//Phase_Shift Bit 31-16
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+11],tempShifted);
	tempShifted = (uint16_t) VCO2.Phase_Shift;					//Phase_Shift Bit 15-0
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+12],tempShifted);

	tempShifted = ((uint16_t) VCO2.Octave_Index >> 16 );		//Octave_Index Bit 31-16
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+13],tempShifted);
	tempShifted = (uint16_t) VCO2.Octave_Index;					//Octave_Index Bit 15-0
	EE_WriteVariable((Bank_Value*21+14),tempShifted);

	tempShifted = ((uint16_t) VCO2.Phase_Mod_Value >> 16 );		//Phase_Mod_Value Bit 31-16
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+15],tempShifted);
	tempShifted = (uint16_t) VCO2.Phase_Mod_Value;				//Phase_Mod_Value Bit 15-0
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+16],tempShifted);

	tempShifted = ((uint16_t) VCO2.Shape_Value >> 16 );			//Shape_Value Bit 31-16
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+17],tempShifted);
	tempShifted = (uint16_t) VCO2.Shape_Value;					//Shape_Value Bit 15-0
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+18],tempShifted);

	tempShifted = (uint16_t) VCO2.FM_Value;						//FM_Value
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+19],tempShifted);

	tempShifted = ((uint16_t) VCO2.Mix_Value >> 16 );			//Mix_Value Bit 31-16
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+20],tempShifted);
	tempShifted = (uint16_t) VCO2.Mix_Value;					//Mix_Value Bit 15-0
	EE_WriteVariable(VirtAddVarTab[Bank_Value*21+21],tempShifted);
}

/**
 * This functions loads the parameters of VCO1 and VCO2
 */
void loadBank(void)
{
	uint16_t tempLoaded1,tempLoaded2;

	VCO1_Lock.Shape_Lock = true;
	VCO1_Lock.Freq_Lock = true;
	VCO1_Lock.Freq_Fine_Lock = true;
	VCO1_Lock.FM_Lock = true;
	VCO1_Lock.Phase_Lock = true;
	VCO1_Lock.Mix_Lock = true;
	VCO1_Lock.Audio_Lock = true;

	VCO2_Lock.Shape_Lock = true;
	VCO2_Lock.Freq_Lock = true;
	VCO2_Lock.Freq_Fine_Lock = true;
	VCO2_Lock.FM_Lock = true;
	VCO2_Lock.Phase_Lock = true;
	VCO2_Lock.Mix_Lock = true;
	VCO2_Lock.Audio_Lock = true;

	//VCO1
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21], &tempLoaded1);
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+1], &tempLoaded2);
	VCO1.Phase_Shift = (((uint32_t) tempLoaded1) << 16 ) | tempLoaded2;
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+2], &tempLoaded1);
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+3], &tempLoaded2);
	VCO1.Octave_Index = (((uint32_t) tempLoaded1) << 16 ) | tempLoaded2;
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+4], &tempLoaded1);
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+5], &tempLoaded2);
	VCO1.Phase_Mod_Value = (((uint32_t) tempLoaded1) << 16 ) | tempLoaded2;
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+6], &tempLoaded1);
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+7], &tempLoaded2);
	VCO1.Shape_Value = (((uint32_t) tempLoaded1) << 16 ) | tempLoaded2;
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+8], &tempLoaded1);
	VCO1.FM_Value = tempLoaded1;
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+9], &tempLoaded1);
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+10], &tempLoaded2);
	VCO1.Mix_Value = (((uint32_t) tempLoaded1) << 16 ) | tempLoaded2;

	//VCO2
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+11], &tempLoaded1);
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+12], &tempLoaded2);
	VCO2.Phase_Shift = (((uint32_t) tempLoaded1) << 16 ) | tempLoaded2;
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+13], &tempLoaded1);
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+14], &tempLoaded2);
	VCO2.Octave_Index = (((uint32_t) tempLoaded1) << 16 ) | tempLoaded2;
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+15], &tempLoaded1);
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+16], &tempLoaded2);
	VCO2.Phase_Mod_Value = (((uint32_t) tempLoaded1) << 16 ) | tempLoaded2;
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+17], &tempLoaded1);
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+18], &tempLoaded2);
	VCO2.Shape_Value = (((uint32_t) tempLoaded1) << 16 ) | tempLoaded2;
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+19], &tempLoaded1);
	VCO2.FM_Value = tempLoaded1;
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+20], &tempLoaded1);
	EE_ReadVariable(VirtAddVarTab[Bank_Value*21+21], &tempLoaded2);
	VCO2.Mix_Value = (((uint32_t) tempLoaded1) << 16 ) | tempLoaded2;
}

