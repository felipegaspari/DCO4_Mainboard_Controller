#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "serial_param_protocol.h"
#include "serial_protocol.h"
#include "serial_input_protocol.h"
#include "serial_parser.h"

#define ENABLE_SERIAL
#define ENABLE_SERIAL1
#define ENABLE_SERIAL2
#define ENABLE_SERIAL8

#ifdef ENABLE_SERIAL1
HardwareSerial Serial1(PA10, PA9); // TO SCREEN CONTROLLER
#endif

#ifdef ENABLE_SERIAL2
HardwareSerial Serial2(PD6, PD5); // TO DCO
#endif

#ifdef ENABLE_SERIAL8
HardwareSerial Serial8(PE0, PE1); // TO INPUT BOARD
#endif

byte finishByte = 1;

bool serialSendADSR3ControlValuesFlag = false;
bool serialSendPWFlag = false;

#endif

/*
SIGNAL LIST:

1 LOAD (PRESET SCROLL)
2 LOAD/SAVE EXIT
3 SAVE
4 SAVE - SET NAME
5 SAVE - COMPLETE
6 SAVE - SET NAME - CHAR SELECTION
7
8

*/
