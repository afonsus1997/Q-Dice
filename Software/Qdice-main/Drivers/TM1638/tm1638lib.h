/*
tm1638lib.h - Library for TM1638 Displays.

Copyright (C) 2011 Ricardo Batista (rjbatista <at> gmail <dot> com)
Adapted to STM8S by Klaas De Craemer 2012 (klaasdc <at> gmail <dot> com)

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "main.h"

#ifndef __TM1638_H
#define __TM1638_H

/* ********** TM16XX Generic ******** */

void TM1638_DeInit(	/*GPIO_TypeDef* displayPort,
										GPIO_Pin_TypeDef dataPin,
										GPIO_Pin_TypeDef clockPin,
										GPIO_Pin_TypeDef strobePin*/void);

/** Set the display (segments and LEDs) active or off and intensity (range from 0-7). */
void setupDisplay(uint8_t active, uint8_t intensity);

/** Set a single display at pos (starting at 0) to a digit (left to right) */
void setDisplayDigit(uint8_t digit, uint8_t pos, uint8_t dot, const uint8_t numberFont[]);

/** Set the display to an error message */
void setDisplayToError(void);

/** Clear  a single display at pos (starting at 0, left to right) */
void clearDisplayDigit(uint8_t pos, uint8_t dot);

/** Set the display to the values (left to right) */
void setDisplay(const uint8_t values[], uint8_t size);

/** Clear the display */
void clearDisplay(void);

/** Set the display to the string (defaults to built in font) */
void setDisplayToString(const char* string, const uint16_t dots, const uint8_t pos, const uint8_t font[]);

//void setDisplayToString(const String string, const word dots, const uint8_t pos, const uint8_t font[]);

void sendCommand(uint8_t cmd);

void sendData(uint8_t address, uint8_t data);

void sendChar(uint8_t pos, uint8_t data, uint8_t dot);

void send(uint8_t data);

uint8_t receive(void);

/* *********** TM1636 Specific ********** */

/** Set the display to a unsigned hexadecimal number (with or without leading zeros) */
void setDisplayToHexNumber(uint16_t number, uint8_t dots, uint8_t leadingZeros, const uint8_t numberFont[]);

/** Set the display to a unsigned decimal number (with or without leading zeros) */
void setDisplayToDecNumberAt(uint16_t number, uint8_t dots, uint8_t startingPos, uint8_t leadingZeros, const uint8_t numberFont[]);

/** Set the display to a unsigned decimal number (with or without leading zeros) */
void setDisplayToDecNumber(uint16_t number, uint8_t dots, uint8_t leadingZeros, const uint8_t numberFont[]);

/** Set the display to a signed decimal number (with or without leading zeros) */
void setDisplayToSignedDecNumber(int16_t number, uint8_t dots, uint8_t leadingZeros, const uint8_t numberFont[]);

/** Set the display to a unsigned binary number */
void setDisplayToBinNumber(uint8_t number, uint8_t dots, const uint8_t numberFont[]);

/** Set the LED at pos to color (TM1638_COLOR_RED, TM1638_COLOR_GREEN or both) */
void setLED(uint8_t color, uint8_t pos);

/** Set the LEDs. MSB byte for the green LEDs, LSB for the red LEDs */
void setLEDs(uint16_t leds);

/** Returns the pressed buttons as a bit set (left to right). */

#endif
