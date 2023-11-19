/******************LED Program*******************/
/**********Author: Abdelrahman Mohamed.**********/
/********************Ver.: 01********************/
/****************Date:17/08/2023.****************/
/************************************************/

#include "../inc/STD_TYPES.h"
#include "../inc/BIT_MATH.h"
#include "DIO_interface.h"
#include "USART_interface.h"
#include "LED_private.h"
#include "LED_config.h"
#include "LED_interface.h"

#include "FreeRTOS.h"
#include "task.h"

/*Global Variable To hold the received char or input from UART
mapping it to my array of structs index's */
u8 Global_u8ReceivedState = 0;

/*Creating array of structs named patterns
each struct can hold an array for the pattern of light and the used delay for that pattern
you can check the struct in LED_interface.h File*/
LedPattern Patterns[] =
	{
		/*index 0 in my array of structs will contain the off signal default behaviour*/
		{0, 1000, {0, -1}},
		/*index 1 in my array of structs contains flashing pattern with 500ms delay.*/
		{1, 500, {255, 0, -1}},

		/*index 2 in my array of structs contains moving left with 250ms delay.*/
		{0, 250, {128, 64, 32, 16, 8, 4, 2, 1, -1}},

		/*index 3 in my array of structs contains moving right with 250ms delay.*/
		{0, 250, {1, 2, 4, 8, 16, 32, 64, 128, -1}},

		/*index 4, Two LEDs converging with 300ms delay.*/
		{0, 300, {24, 36, 66, 129, -1}},

		/*index 5, Two LEDs diverging with 300ms delay.*/
		{0, 250, {129, 66, 36, 24, -1}},

		/*index 6, Ping Pong with 250ms delay.*/
		{0, 300, {2, 8, 32, 128, 64, 16, 4, 1, -1}},

		/*index 7, Snake effect with 300ms delay.*/
		{0, 300, {224, 112, 56, 28, 14, 7, 131, 193, -1}},

		/*index 8, converging and diverging with 300ms delay.*/
		{0, 300, {129, 195, 231, 255, 255, 231, 195, -1}}};

void LED_voidInit(void)
{
	/*Set Led Port direction as output*/
	DIO_voidSetPortDirection(LED_PORT, PORT_DIRECTION_OUTPUT);
}

/*Checking what does my UDR register in UART Holds it gets called on received data on interrupts*/
void LED_voidCheckState(void)
{
	Global_u8ReceivedState = (USART_u8ReceiveDataOnInterrupt() - '0');
}

/*My main Function that acts upon my global variable that holds what state
my lEDs should be animating.*/
void LED_voidActivatePattern(void *ptr)
{
	/*just a variable for future use if needed in case of a condition
	 *that tells me i can only show the patterns that is higher in the index and not lower.*/
	u8 static Local_u8ActiveLEDsState = 0;
	/*Variable to hold my pattern Length*/
	u8 static Local_u8PatternLength = 0;
	/*Getting the total number of my patterns instead of hardcoding it*/
	u8 static const Local_u8TotalNoOfPatterns = sizeof(Patterns) / sizeof(Patterns[0]);

	while (1)
	{
		/*if Received state same as active state keep the pattern displayed*/
		if (Global_u8ReceivedState == Local_u8ActiveLEDsState)
		{
			/*for loop to display "turn on LEDs" based on the received pattern with the correct delay*/
			for (u8 Local_u8Iterator = 0; Local_u8Iterator < Local_u8PatternLength; Local_u8Iterator++)
			{
				DIO_voidSetPortValue(LED_PORT, Patterns[Local_u8ActiveLEDsState].pattern[Local_u8Iterator]);
				for (u8 j = Patterns[Local_u8ActiveLEDsState].brightness; j < 255 && j != 0; j++)
				{
					DIO_voidSetPortValue(LED_PORT, ~(Patterns[Local_u8ActiveLEDsState].pattern[Local_u8Iterator]));
					vTaskDelay(j);
				}
				vTaskDelay(Patterns[Local_u8ActiveLEDsState].delay);
			}
		} /*if received pattern is one of the patterns in my array of structs
			 changed the active state and update the pattern length for correctness of display*/
		else if (Global_u8ReceivedState < Local_u8TotalNoOfPatterns && Global_u8ReceivedState >= 0)
		{
			Local_u8PatternLength = 0;
			Local_u8ActiveLEDsState = Global_u8ReceivedState;
			/*Getting the Actual Pattern Length for the choosen Pattern*/
			while ((Patterns[Local_u8ActiveLEDsState].pattern[Local_u8PatternLength]) != -1)
			{
				Local_u8PatternLength++;
			}
		} /*if none of the above must be an error turn all the lEDs on*/
		else
		{
			/*error pattern*/
			DIO_voidSetPortValue(LED_PORT, PORT_VALUE_HIGH);
		}
		vTaskDelay(1);
	}
}
