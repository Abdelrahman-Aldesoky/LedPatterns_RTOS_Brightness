/******************LED Private*******************/
/**********Author: Abdelrahman Mohamed.**********/
/********************Ver.: 01********************/
/****************Date:17/08/2023.****************/
/************************************************/

#ifndef LED_PRIVATE_H_
#define LED_PRIVATE_H_

#define VALID_LED_PATTERN (Global_u8ReceivedState > Local_u8ActiveLEDsState && Global_u8ReceivedState < Local_u8TotalNoOfPatterns) || Global_u8ReceivedState == 0
#define EOP -1

#endif
