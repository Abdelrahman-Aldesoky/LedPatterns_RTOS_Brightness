/*******************BIT MATH.********************/
/**********Author: Abdelrahman Mohamed.**********/
/********************Ver.: 01********************/
/****************Date:14/08/2023.****************/
/************************************************/

#ifndef _BIT_MATH_H
#define _BIT_MATH_H

#define SET_BIT(REG, BIT_NO) REG = REG | (1 << BIT_NO)
#define CLR_BIT(REG, BIT_NO) REG = REG & (~(1 << BIT_NO))
#define TOG_BIT(REG, BIT_NO) REG = REG ^ (1 << BIT_NO)
#define GET_BIT(REG, BIT_NO) (REG >> BIT_NO) & 1

#endif
