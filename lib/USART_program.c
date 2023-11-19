/*****************USART_PROGRAM******************/
/********Authors: Amira Magdy,Abdelrahman********/
/******************Ver.: 0.0.1.******************/
/****************Date:13/09/2023.****************/
/************************************************/

#include "../inc/STD_TYPES.h"
#include "../inc/BIT_MATH.h"
#include "DIO_interface.h"
#include "GIE_interface.h"
#include "USART_private.h"
#include "USART_config.h"
#include "USART_interface.h"

/*Global ptr to function for the callback*/
static void (*Global_ptrtofunc)(void) = NULL;

void USART_voidInit(void)
{
	/*Enable Global interrupts since iam going to be using interrupts on Receive*/
	GIE_voidEnable();

	/*Enable RXCIE interrupt on Receive
	 *Enable RXEN Receive
	 *Enable TXEN Transmit*/
	UCSRB |= (1 << UCSRB_RXCIE) | (1 << UCSRB_RXEN) | (1 << UCSRB_TXEN);

	/*Select 8 Bit Character Size*/
	UCSRC |= (1 << UCSRC_URSEL) | (1 << UCSRC_UCSZ0) | (1 << UCSRC_UCSZ1);

	/*Set Baud Rate for 9600*/
	UBRRL = 51;
	UBRRH = 0;
}

/*just for abstraction to get my data from UDR without directly including my private
file in other files*/
u8 USART_u8ReceiveDataOnInterrupt(void)
{
	return UDR;
}

/*my call back function for UART*/
u8 USART_u8SetCallBack(void (*Copy_ptrtofunc)(void))
{
	u8 Local_u8Errorstate = OK;
	if (Copy_ptrtofunc != NULL)
	{
		Global_ptrtofunc = Copy_ptrtofunc;
	}
	else
	{
		Local_u8Errorstate = NOK;
	}
	return Local_u8Errorstate;
}

/*Interrupt Handler*/
void __vector_13(void) __attribute__((signal));

void __vector_13(void)
{
	if (Global_ptrtofunc != NULL)
	{
		Global_ptrtofunc();
	}
}