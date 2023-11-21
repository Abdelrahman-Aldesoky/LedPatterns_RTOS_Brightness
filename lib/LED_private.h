/******************LED Private*******************/
/**********Author: Abdelrahman Mohamed.**********/
/********************Ver.: 01********************/
/****************Date:17/08/2023.****************/
/************************************************/

#ifndef LED_PRIVATE_H_
#define LED_PRIVATE_H_

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
#define VALID_LED_PATTERN (Global_u8ReceivedState > Local_u8ActiveLEDsState &&    \
                           Global_u8ReceivedState < Local_u8TotalNoOfPatterns) || \
                              Global_u8ReceivedState == 0

/*just my end of pattern Constant to check upon to see if i reached end of pattern sequence*/
#define EOP -1

#endif
