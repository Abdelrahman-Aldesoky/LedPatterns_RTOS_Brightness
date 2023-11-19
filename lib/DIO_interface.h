/*****************DIO Interface.*****************/
/**********Author: Abdelrahman Mohamed.**********/
/********************Ver.: 01********************/
/****************Date:16/08/2023.****************/
/************************************************/

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

void DIO_voidSetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction);
void DIO_voidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8PinNo, u8 Copy_u8Direction);
void DIO_voidSetPortValue(u8 Copy_u8Port, u8 Copy_u8Value);
void DIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8PinNo, u8 Copy_u8PinValue);
u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8PinNo);

#define PORT_DIRECTION_OUTPUT 0XFF
#define PORT_DIRECTION_INPUT 0X00

#define PORT_VALUE_HIGH 0XFF
#define PORT_VALUE_LOW 0X00

#define PIN_DIRECTION_OUTPUT 1
#define PIN_DIRECTION_INPUT 0

#define PIN_VALUE_HIGH 1
#define PIN_VALUE_LOW 0

#define PORTA_REG 1
#define PORTB_REG 2
#define PORTC_REG 3
#define PORTD_REG 4

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#endif
