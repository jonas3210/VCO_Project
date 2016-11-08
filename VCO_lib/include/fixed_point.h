/**
  ******************************************************************************
  * @file    fixed_point.h
  * @author  Frieder Jespers
  * @version V1.0.0
  * @date    28/10/2016
  * @brief   This file contains fixed point operation and cast macros
  ******************************************************************************
  * @copy https://www.youtube.com/watch?v=npQF28g6s_k
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FIXED_POINT_H
#define __FIXED_POINT_H
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
//#include "wavetables.h"
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SCALE 16 //Scale for fixed point numbers(amount of Bits for fractional part)
#define  FIXED_FRACTION_MASK 0xffff //0xffffffff >> (32-SCALE);//Mask to blend out int part
#define FIXED_INT_MASK 0xffff0000 //-1 ^ Fixed_Fraction_Mask;//Mask to blend out frac part
/* Private macro -------------------------------------------------------------*/
#define DOUBLE_TO_FIXED(x) (int32_t)((x) * (double)(1<<SCALE))//convert double type to fixed point
#define FIXED_TO_DOUBLE(x) ((double)(x)/(double)(1<<SCALE))//convert fixed to double
#define INT_TO_FIXED(x) ((x)<<SCALE)//convert int to fixed
#define FIXED_TO_INT(x) ((x)>>SCALE)// convert fixed to int
#define FIXED_FRACTION_PART(x) ((x) & FIXED_FRACTION_MASK) // builds fraction part
#define FIXED_INT_PART(x) ((x) & FIXED_INT_MASK)//builds int part

#define FIXED_MUL(x, y) ((((x)>>8)*((y)>>8))>>0)//Fixed point Multiplication
#define FIXED_DIV(x, y)(((x)<<7)/((y)>>9))//Fixed point Division

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#endif /*__FIXED_POINT_H */
