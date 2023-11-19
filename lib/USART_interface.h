/***************USART_INTERFACE******************/
/********Authors: Amira Magdy,Abdelrahman********/
/******************Ver.: 0.0.1.******************/
/****************Date:13/09/2023.****************/
/************************************************/

#ifndef _USART_INTERFACE_H_
#define _USART_INTERFACE_H_

void USART_voidInit(void);
u8 USART_u8ReceiveDataOnInterrupt(void);
u8 USART_u8SetCallBack(void (*Copy_ptrtofunc)(void));

#endif
