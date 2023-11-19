/*****************USART_PRIVATE******************/
/********Authors: Amira Magdy,Abdelrahman********/
/******************Ver.: 0.0.1.******************/
/****************Date:13/09/2023.****************/
/************************************************/

#ifndef _USART_PRIVATE_H_
#define _USART_PRIVATE_H_

#define UDR *((volatile u8 *)0X2C)
/*************************************************************************/
#define UCSRA *((volatile u8 *)0X2B)
#define UCSRA_RXC 7
#define UCSRA_TXC 6
#define UCSRA_UDRE 5
#define UCSRA_U2X 1
/*************************************************************************/
#define UCSRB *((volatile u8 *)0X2A)
#define UCSRB_RXCIE 7
#define UCSRB_TXCIE 6
#define UCSRB_RXEN 4
#define UCSRB_TXEN 3
#define UCSRB_UCSZ2 2
/*************************************************************************/
#define UCSRC *((volatile u8 *)0X40)
#define UCSRC_URSEL 7
#define UCSRC_USBS 3
#define UCSRC_UCSZ1 2
#define UCSRC_UCSZ0 1
/*************************************************************************/
#define UBRRH *((volatile u8 *)0X40)
#define UBRRL *((volatile u8 *)0X29)

#endif
