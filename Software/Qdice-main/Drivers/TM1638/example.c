///* MAIN.C file */
//#include "tm1638lib.h"
//extern const u8 FONT_DEFAULT[];
//extern const u8 NUMBER_FONT[];
//
//void main(void){
//	u8 keys = 0b10010001;
//	//u16 ledtest = 0b1010101001010101;
//
//	/* Switch to 16Mhz Crystal Osc clock */
//	CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, DISABLE);
//
//	/* Setup GPIOs */
//	GPIO_DeInit(GPIOD);
//	GPIO_Init(GPIOD, GPIO_PIN_0 , GPIO_MODE_OUT_PP_LOW_FAST);//Setup LED pin of Discovery board
//
//	TM1638_DeInit();
//	//setDisplayToError();
//	//setDisplayToString("ABC", 0, 0, FONT_DEFAULT);
//	setDisplayToDecNumber(12345, 0, FALSE, NUMBER_FONT);
//	setDisplayToString("P", 0, 0, FONT_DEFAULT);
//
//	//setLEDs( ((keys & 0x0F) << 8) | (keys & 0x0F));
//	setLEDs( 0b0000000011111111);
//	//setLEDs(ledtest);
//
//	/* Main loop */
//  while (1){
//		keys = getButtons();
//		setLEDs(0b1111111100000000 | keys);
//	}
//}
