#ifndef __WAVESELECTOR_H__
#define __WAVESELECTOR_H__

#include <RoxMux.h>

Rox74HC595<2> waveSelectorMux;

// pins for 74HC595
// #define PIN_DATA    PE_4 // pin 14 on 74HC595 (DATA)   / DS
// #define PIN_LATCH   PE_2  // pin 12 on 74HC595 (LATCH) / ST
// #define PIN_CLK     PE_3  // pin 11 on 74HC595 (CLK)   / SH
#define PIN_DATA PE4   // pin 14 on 74HC595 (DATA)   / DS
#define PIN_LATCH PE2  // pin 12 on 74HC595 (LATCH) / ST
#define PIN_CLK PE3    // pin 11 on 74HC595 (CLK)   / SH
#define PIN_PWM -1

uint8_t saw1Pin = 0;
uint8_t saw1_2Pin = 5;
uint8_t tri1Pin = 0;
uint8_t sine1Pin = 0;

uint8_t saw2Pin = 0;
uint8_t saw2_2Pin = 0;
uint8_t tri2Pin = 0;
uint8_t sine2Pin = 0;

uint8_t saw3Pin = 0;
uint8_t saw3_2Pin = 0;
uint8_t tri3Pin = 0;
uint8_t sine3Pin = 0;

uint8_t saw4Pin = 0;
uint8_t saw4_2Pin = 0;
uint8_t tri4Pin = 0;
uint8_t sine4Pin = 0;

uint8_t triPins[4] = { 2, 6, 10, 14 };
uint8_t sinePins[4] = { 1, 5, 9, 13 };
uint8_t saw2Pins[4] = { 0, 4, 8, 12 };
uint8_t sawPins[4] = { 3, 7, 11, 15 };

// uint8_t sawPins[4] = { 8, 8, 8, 8 };
// uint8_t saw2Pins[4] = { 9, 9, 9, 9 };
// uint8_t triPins[4] = { 10, 10, 10, 10 };
// uint8_t sinePins[4] = { 11, 11, 11, 11 };


#endif