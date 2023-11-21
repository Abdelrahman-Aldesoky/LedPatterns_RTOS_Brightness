/*
 * main.c
 *
 *  Created on: Sep 24, 2023
 *      Author: Abdelrahman Mohamed
 */
#include "../inc/STD_TYPES.h"
#include "../inc/BIT_MATH.h"
#include "../lib/LED_interface.h"
#include "../lib/USART_interface.h"
#include "../lib/FreeRTOS.h"
#include "../lib/task.h"

int main(void)
{
	/*Initialize USART for interrupts and 9600 baud rate */
	USART_voidInit();
	/*Initialize LEDs Port as output*/
	LED_voidInit();
	/*Set my USART call back function to check the char Received it only interrupts upon Receiving new char*/
	USART_u8SetCallBack(LED_voidCheckState);
	/*Create an Rtos Task*/
	xTaskCreate(LED_voidActivatePattern, NULL, 200, NULL, 5, NULL);
	/*Start Rtos*/
	vTaskStartScheduler();
	while (1)
	{
	}
	return 0;
}