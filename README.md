# Project Title: LED Pattern Display

## Description
This project uses an ATmega32 MCU with an 8MHz clock to display LED patterns. A character is received through USART (with a baud rate of 9600), converted to a number, and the corresponding LED pattern is displayed on 8 LEDs. The patterns are flexible, user-configurable, and can be of any length.

## Installation
1. Ensure you have an ATmega32 MCU and a USB TTL or equivalent for USART connection.
2. Wire up the MCU and LEDs as per the project's specifications.
3. Navigate to the project folder and type `make` to compile. The .hex and .elf files will be in the `program` folder within the created build folder.

## Usage
Transmit a character via USART to the MCU. This character is converted to a number corresponding to an LED pattern, which is then displayed on the 8 connected LEDs.
