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
each struct can hold an array for the pattern sequence and the used delay for that pattern
you can check the struct in LED_interface.h File
user can configure the MAX_PATTERN_LENGTH from there Also its flexible and auto detects
the length on its own but you must provide the EOP flag at the end of your Pattern
user can add up to 255 patterns and its only limited by the Total Number of patterns variable.
you can change its type and put more patterns
if you have more than 8 LEDs adjust your pattern numbers accordingly
each number represent 8 bit binary or a port in my atmega32 */
LedPattern Patterns[] =
	{
		/*index start in my array of structs will contain the off signal default behaviour and if i want to reset*/
		{0, 1, {0, EOP}},

		/*index 1 in my array of structs contains flashing pattern with 500ms delay.*/
		{0, 500, {255, 0, EOP}},

		/*index 2 in my array of structs contains moving left with 250ms delay.*/
		{0, 250, {128, 64, 32, 16, 8, 4, 2, 1, EOP}},

		/*index 3 in my array of structs contains moving right with 250ms delay.*/
		{0, 250, {1, 2, 4, 8, 16, 32, 64, 128, EOP}},

		/*index 4, Snake effect with 300ms delay.*/
		{3, 300, {224, 112, 56, 28, 14, 7, 131, 193, EOP}},

		/*index 5, Two LEDs converging with 300ms delay.*/
		{0, 300, {24, 36, 66, 129, EOP}},

		/*index 6, Two LEDs diverging with 300ms delay.*/
		{0, 250, {129, 66, 36, 24, EOP}},

		/*index 7, Ping Pong with 250ms delay.*/
		{0, 300, {2, 8, 32, 128, 64, 16, 4, 1, EOP}},

		/*index 8, converging and diverging with 300ms delay.*/
		{0, 300, {129, 195, 231, 255, 255, 231, 195, EOP}},

		/*index 9, brightening and dimming slowly according to the gradient steps*/
		{14, 1000, {0, 255, EOP}}};

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
my LEDs should be animating.*/
void LED_voidActivatePattern(void *ptr)
{
	/* Local_u8ActiveLEDsState holds the index of the currently active LED pattern. */
	u8 static Local_u8ActiveLEDsState = 0;

	/* Local_u8Iterator is used to iterate over the elements of pattern array of the currently active pattern. */
	u8 static Local_u8Iterator = 0;

	/* Local_u16ElapsedTime measures the time that has passed since the last pattern change. It's increased every millisecond. */
	u16 static Local_u16ElapsedTime = 0;

	/* Local_u8TotalNoOfPatterns holds the total number of available LED patterns. */
	u8 static const Local_u8TotalNoOfPatterns = sizeof(Patterns) / sizeof(Patterns[0]);

	/* Local_u8StepsCounter is used to count the gradient steps for the brightening and dimming effect. */
	u8 static Local_u8StepsCounter = 0;

	/* Local_u8OnTimeDuration calculates the duration for which the LED should be on during each gradient step. */
	u8 Local_u8OnTimeDuration = 0;
	while (1)
	{
		/* The VALID_LED_PATTERN macro checks if the user's chosen pattern
		 * (Global_u8ReceivedState) is valid for activation. There are three conditions
		 * for a pattern to be considered valid:
		 * 1. The chosen pattern index (Global_u8ReceivedState) should be greater than
		 *    the index of the currently active pattern (Local_u8ActiveLEDsState). This
		 *    means that the user can only switch to a pattern with a higher index number.
		 * 2. The chosen pattern index should be less than the total number of available
		 *    patterns (Local_u8TotalNoOfPatterns). This ensures that the user doesn't
		 *    choose a pattern index that is out of bounds.
		 * 3. The chosen pattern index can be 0. This is because pattern 0 is the default
		 *    off pattern, which allows the user to reset the LED state.
		 * If any of these conditions are met, the macro returns true, indicating that
		 * the chosen pattern is valid. */
		if (VALID_LED_PATTERN)
		{
			/*This line sets the currently active LED pattern to the user's chosen pattern. */
			Local_u8ActiveLEDsState = Global_u8ReceivedState;
			/* This line resets the Iterator for the pattern array if the pattern changes. */
			Local_u8Iterator = 0;
			/* This line resets the elapsed time if the pattern changes. */
			Local_u16ElapsedTime = 0;
		}

		/* This If condition checks if the elapsed time has reached the delay time of the current pattern element.
		 * If so, it moves to the next element in the pattern by increasing the iterator and resets the elapsed time. */
		if (Local_u16ElapsedTime == Patterns[Local_u8ActiveLEDsState].delay)
		{
			Local_u8Iterator++;
			Local_u16ElapsedTime = 0;
		}

		/* This if condition checks if the iterator has reached the end of the pattern (marked by EOP or -1).
		 * You can Check EOP in my Private file.
		 * If so, it resets the iterator to start the pattern from the beginning and so on. */
		if (Patterns[Local_u8ActiveLEDsState].pattern[Local_u8Iterator] == EOP)
		{
			Local_u8Iterator = 0;
		}

		/* Local_u8OnTimeDuration calculates the on-time duration for each gradient step. */
		/* If the number of gradient steps is 0, the LED displays the pattern at full brightness without any gradient effect. */
		Local_u8OnTimeDuration = ((Local_u16ElapsedTime *
								   Patterns[Local_u8ActiveLEDsState].GradientSteps) /
								  Patterns[Local_u8ActiveLEDsState].delay);

		/*software PWM kinda with the complement*/
		if (Local_u8StepsCounter < Local_u8OnTimeDuration)
		{
			if (Patterns[Local_u8ActiveLEDsState].GradientSteps <= 3)
			{
				DIO_voidSetPortValue(LED_PORT, PORT_VALUE_LOW);
			}
			else
			{
				DIO_voidSetPortValue(LED_PORT, ~(Patterns[Local_u8ActiveLEDsState].pattern[Local_u8Iterator]));
			}
		}
		else
		{
			DIO_voidSetPortValue(LED_PORT, Patterns[Local_u8ActiveLEDsState].pattern[Local_u8Iterator]);
		}

		/* The steps counter is incremented after each iteration. */
		Local_u8StepsCounter++;

		/* If the steps counter reaches the total number of gradient steps, it's reset to 0. */
		if (Local_u8StepsCounter >= Patterns[Local_u8ActiveLEDsState].GradientSteps)
		{
			Local_u8StepsCounter = 0;
		}

		/* Increase the elapsed time by 1ms and put the task to sleep for 1ms.
		 * This allows for 1ms checks if the pattern has changed or not. */
		Local_u16ElapsedTime++;
		vTaskDelay(1);
	}
}
