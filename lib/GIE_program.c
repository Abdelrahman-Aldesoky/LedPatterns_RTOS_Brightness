/******************GIE Program*******************/
/**********Author: Abdelrahman Mohamed.**********/
/********************Ver.: 01********************/
/****************Date:30/08/2023.****************/
/************************************************/

#include "../inc/STD_TYPES.h"
#include "../inc/BIT_MATH.h"
#include "GIE_private.h"
#include "GIE_config.h"
#include "GIE_interface.h"

void GIE_voidEnable(void)
{
	SET_BIT(SREG, SREG_I);
}

void GIE_voidDisable(void)
{
	CLR_BIT(SREG, SREG_I);
}
