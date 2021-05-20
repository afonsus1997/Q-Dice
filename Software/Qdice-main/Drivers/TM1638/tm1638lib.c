/*
tm1638lib.c - Library implementation for TM1638 Displays.

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
#include "tm1638lib.h"
//#include "tm1638fonts.h"

#define PORT			GPIOB
#define CLOCK			GPIO_PIN_7
#define DATA			GPIO_PIN_9
#define STROBE		GPIO_PIN_8

#define TM1638_COLOR_RED    1
#define TM1638_COLOR_GREEN  2

uint8_t intensity = 7;
uint8_t displays = 8;

void GPIO_WriteHigh(uint16_t pin){
	HAL_GPIO_WritePin(GPIOB, pin, 1);
}

void GPIO_WriteLow(uint16_t pin){
	HAL_GPIO_WritePin(GPIOB, pin, 0);
}

void TM1638_DeInit(	/*GPIO_TypeDef* displayPort,
										GPIO_Pin_TypeDef dataPin,
										GPIO_Pin_TypeDef clockPin,
										GPIO_Pin_TypeDef strobePin*/void){	
	uint8_t activateDisplay = 1;
	uint8_t i=0;

	
	GPIO_WriteHigh(STROBE);
	GPIO_WriteHigh(CLOCK);
	
  sendCommand(0x40);
  sendCommand(0x80 | (activateDisplay ? 8 : 0) | intensity);
	
	GPIO_WriteLow(STROBE);
  send(0xC0);
  for (i=0; i<16; i++) {
    send(0x00);
  }
	GPIO_WriteHigh(STROBE);
}

/** Set the display (segments and LEDs) active or off and intensity (range from 0-7). */
void setupDisplay(uint8_t active, uint8_t intensity){
  sendCommand(0x80 | (active ? 8 : 0) | intensity);

  GPIO_WriteLow(STROBE);
  GPIO_WriteLow(CLOCK);
  GPIO_WriteHigh(CLOCK);
	GPIO_WriteHigh(STROBE);
}

void setDisplayDigit(uint8_t digit, uint8_t pos, uint8_t dot, const uint8_t numberFont[]){
  sendChar(pos, numberFont[digit & 0xF], dot);
}

void setDisplayToError(void){
	uint8_t i=0;
	//setDisplay(ERROR_DATA, 8);

	for (i=8; i<displays; i++) {
	    clearDisplayDigit(i, 0);
	}
}

void clearDisplayDigit(uint8_t pos, uint8_t dot){
  sendChar(pos, 0, dot);
}

void setDisplay(const uint8_t values[], uint8_t size){
	uint8_t i=0;
  for (i = 0; i<size; i++) {
    sendChar(i, values[i], 0);
  }
}

void clearDisplay(void){
	uint8_t i=0;
  for (i = 0; i<displays; i++) {
    sendData(i << 1, 0);
  }
}

void setDisplayToString(const char* string, const uint16_t dots, const uint8_t pos, const uint8_t font[]){
	uint8_t i=0;
  for (i = 0; i<displays - pos; i++) {
  	if (string[i] != '\0') {
			sendChar(i + pos, font[string[i] - 32], (dots & (1 << (displays - i - 1))) != 0);
		} else {
			break;
		}
  }
}

/*void setDisplayToString(const String string, const word dots, const uint8_t pos, const uint8_t font[]){
  int stringLength = string.length();

  for (int i = 0; i < displays - pos; i++) {
    if (i < stringLength) {
      sendChar(i + pos, font[string.charAt(i) - 32], (dots & (1 << (displays - i - 1))) != 0);
    } else {
      break;
    }
  }
}*/

void sendCommand(uint8_t cmd){
	GPIO_WriteLow(STROBE);
  send(cmd);
	GPIO_WriteHigh(STROBE);
}

void sendData(uint8_t address, uint8_t data){
  sendCommand(0x44);
	GPIO_WriteLow(STROBE);
  send(0xC0 | address);
  send(data);
	GPIO_WriteHigh(STROBE);
}

void sendChar(uint8_t pos, uint8_t data, uint8_t dot){
	sendData(pos << 1, data | (dot ? 0b10000000 : 0));
}

void send(uint8_t data){
	uint8_t i=0;
  for (i=0; i<8; i++) {
		GPIO_WriteLow(CLOCK);
		if (data & 1){
			GPIO_WriteHigh(DATA);
		} else {
			GPIO_WriteLow(DATA);
		}
    data >>= 1;
		GPIO_WriteHigh(CLOCK);
  }
}



//}


uint8_t receive(void){
  uint8_t temp = 0;
	uint8_t i = 0;
	uint8_t input = 0;

  // Pull-up on, input mode on

	GPIO_WriteHigh(DATA);

  for (i = 0; i < 8; i++) {
    temp >>= 1;

		GPIO_WriteLow(CLOCK);
	
		nop();nop();nop();

		input = GPIO_ReadInputData(PORT) & DATA;
	
		if (input > 0){
			GPIO_WriteReverse(GPIOD, GPIO_PIN_0);
			temp |= 0x80;
		}
		GPIO_WriteHigh(CLOCK);
  }

  // Pull-up off, output mode on
	GPIO_WriteLow(DATA);
  return temp;
}


/* ************************************
 * LEDS
 * ************************************ */

void setDisplayToHexNumber(uint16_t number, uint8_t dots, uint8_t leadingZeros, const uint8_t numberFont[]){
	uint8_t i=0;
  for (i = 0; i < displays; i++){
		if (!leadingZeros && number == 0){
			clearDisplayDigit(displays - i - 1, (dots & (1 << i)) != 0);
		} else {
			setDisplayDigit(number & 0xF, displays - i - 1, (dots & (1 << i)) != 0, numberFont);
			number >>= 4;
		}
	}
}

void setDisplayToDecNumberAt(uint16_t number, uint8_t dots, uint8_t startingPos, uint8_t leadingZeros, const uint8_t numberFont[]){
	uint8_t i=0;
  if (number > 99999999L){
    setDisplayToError();
  } else {
    for (i=0; i<displays - startingPos; i++){
      if (number != 0) {
        setDisplayDigit(number % 10, displays - i - 1, (dots & (1 << i)) != 0, numberFont);
        number /= 10;
      } else {
				if (leadingZeros) {
					setDisplayDigit(0, displays - i - 1, (dots & (1 << i)) != 0, numberFont);
				} else {
					clearDisplayDigit(displays - i - 1, (dots & (1 << i)) != 0);
				}
      }
    }
  }
}

void setDisplayToDecNumber(uint16_t number, uint8_t dots, uint8_t leadingZeros,	const uint8_t numberFont[]){
	setDisplayToDecNumberAt(number, dots, 0, leadingZeros, numberFont);
}

void setDisplayToSignedDecNumber(int16_t number, uint8_t dots, uint8_t leadingZeros, const uint8_t numberFont[]){
	if (number >= 0) {
		setDisplayToDecNumberAt(number, dots, 0, leadingZeros, numberFont);
	} else {
		if (-number > 9999999L) {
		    setDisplayToError();
		} else {
			setDisplayToDecNumberAt(-number, dots, 1, leadingZeros, numberFont);
//			sendChar(0, MINUS, (dots & (0x80)) != 0);
		}
	}
}

void setDisplayToBinNumber(uint8_t number, uint8_t dots, const uint8_t numberFont[]){
	uint8_t i=0;
  for (i = 0; i<displays; i++) {
    setDisplayDigit((number & (1 << i)) == 0 ? 0 : 1, displays - i - 1, (dots & (1 << i)) != 0, numberFont);
  }
}

void setLED(uint8_t color, uint8_t pos){
    sendData((pos << 1) + 1, color);
}

void setLEDs(uint16_t leds){
	uint8_t i=0;
	uint8_t color=0;
  for (i=0; i<displays; i++) {
    color = 0;

    if ((leds & (1 << i)) != 0) {
      color |= TM1638_COLOR_RED;
    }

    if ((leds & (1 << (i + 8))) != 0) {
      color |= TM1638_COLOR_GREEN;
    }

    setLED(color, i);
  }
}

