#ifndef __SCREEN_H__
#define __SCREEN_H__

#define DISP1_ACTIVE 0
#define TM_ACTIVE 0
#define TM2_ACTIVE 0  

#define CLK1 PB14
#define DIO1 PB15

//#if TM_ACTIVE
//#include <TM1637_driver.h>
//
//TM1637 tm(CLK1, DIO1);
//
#if TM2_ACTIVE
#include </home/felipe/Arduino/libraries/TM16xx_LEDs_and_Buttons/src/TM1637.h>
#include <TM16xxDisplay.h>
TM1637 module(DIO1, CLK1);
TM16xxDisplay display(&module, 4);
#endif

#if DISP1_ACTIVE
#include <U8g2lib.h>
#include <Wire.h>
//#include <SPI.h>
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2_1(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1309_128X64_NONAME2_F_4W_HW_SPI u8g2_1(U8G2_R2, /* cs=*/PC4, /* dc=*/PC5, /* reset=*/U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2_1(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2_1(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

#endif

volatile uint16_t valor1Screen;

bool drawTMStringFlag;
String drawTMStringVal;
bool drawTMFlag;
volatile int drawTMVal;

bool blinkChar = false;

void initScreen();
void drawScreen();

#endif
