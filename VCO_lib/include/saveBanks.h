/********************************************************************************
  * @file    saveBanks.h
  * @author  Christopher Ottens
  * @version V.0.0
  * @date    14.12.16
  * @brief   This file contains the functionheaders and defines to save the bank structures
*********************************************************************************/

/*------------------Define to prevent recursive inclusion-----------------------*/
//#ifndef /*ERROR*/
//#define

/*---------------------------------Includes-------------------------------------*/
#include "misc.h"
#include "eeprom.h"
#include "stm32f4xx_flash.h"
#include "Global_Variables.h"

/*-------------------------------Exported variables-----------------------------*/
int VirtAddVarTab[2100];
/*-------------------------------Exported macro---------------------------------*/
#define NUMBER_OF_BANKVALUES 0

/*-----------------------------Exported functions-------------------------------*/
void saveBanksInit(void);
void saveBank(void);
void loadBank(void);

//#endif
