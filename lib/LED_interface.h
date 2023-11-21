/*****************LED Interface******************/
/**********Author: Abdelrahman Mohamed.**********/
/********************Ver.: 01********************/
/****************Date:17/08/2023.****************/
/************************************************/

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

/*Max Pattern Length it can be increased to any number but you must mark the end of pattern with EOP*/
#define MAX_PATTERN_LENGTH 10

/*Struct for my patterns it contains array for the pattern and its corresponding delay*/
typedef struct
{
    /*If pattern got Gradient like dimming and brightening put a number between 4-30
     *in here the numbers came after trial and error for my delay*/
    u8 GradientSteps;

    /*Delay between each part of the sequence inside the pattern*/
    u16 delay;

    /*array for the pattern sequence max length is set to 10 but you can always increase it
     *if you want longer Patterns*/
    s16 pattern[MAX_PATTERN_LENGTH];
} LedPattern;

void LED_voidInit(void);
void LED_voidCheckState(void);
void LED_voidActivatePattern(void *ptr);

#endif