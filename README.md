# LED Pattern Display

## Description
This project uses an ATmega32 MCU with an 8MHz clock to display LED patterns. A character is received through USART (with a baud rate of 9600), converted to a number, and the corresponding LED pattern is displayed on 8 LEDs. The patterns are flexible, user-configurable, and can be of any length. The system operates on a FreeRTOS scheduler with a 1ms time slice, ensuring timely and accurate pattern displays.

## Project Components
The project is composed of several components that work together to create the LED animations:

1. **USART Interface**: This component is responsible for receiving user input through USART. It operates at a baud rate of 9600.

2. **LED Interface**: This component controls the LED patterns. It is flexible and allows the user to configure the patterns.

3. **FreeRTOS Scheduler**: The system operates on a FreeRTOS scheduler that is set to a 1ms time slice. This ensures that the LED animations are checked and executed every 1ms.

4. **LED Animation Function**: A generic function is scheduled to run every 1ms to check and execute the required LED animations based on user input. The function is designed in such a way that higher animation numbers take precedence over lower ones.

## Installation
1. Ensure you have an ATmega32 MCU and a USB TTL or equivalent for USART connection.
2. Wire up the MCU and LEDs as per the project's specifications.
3. Navigate to the project folder and type `make` to compile. The .hex and .elf files will be in the `program` folder within the created build folder.

## Usage
Transmit a character via USART to the MCU. This character is converted to a number corresponding to a LED pattern, which is then displayed on the 8 connected LEDs. The system checks and updates the LED animations every 1ms, ensuring smooth and accurate animations. Higher animation numbers take precedence over lower ones, and an animation number of 0 resets the LED state to off. If an invalid character is received, the system continues displaying the last valid pattern.
