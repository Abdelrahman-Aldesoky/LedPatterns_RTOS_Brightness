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
	USART_voidInit();
	LED_voidInit();
	USART_u8SetCallBack(LED_voidCheckState);

	xTaskCreate(LED_voidActivatePattern, NULL, 200, NULL, 5, NULL);

	vTaskStartScheduler();
	while (1)
	{
	}
	return 0;
}
