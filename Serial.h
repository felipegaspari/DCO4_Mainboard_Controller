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

// STM32 Arduino core 3.x already instantiates Uart Serial1/2/8 (see core Serial.cpp).
// Do not construct HardwareSerial SerialN(...) here — that clashes with `extern Uart SerialN`.
// Remap pins with setRx/setTx before begin() in setup().
#define MB_SERIAL1_RX PA10  // Screen
#define MB_SERIAL1_TX PA9
#define MB_SERIAL2_RX PD6   // DCO
#define MB_SERIAL2_TX PD5
#define MB_SERIAL8_RX PE0   // Input
#define MB_SERIAL8_TX PE1

float freq;

byte finishByte = 1;

bool sendDetune2Flag = false;
bool serial_send_portamentoFlag = false;
bool serial_send_oscSyncModeFlag = false;
bool serial_send_OSC1IntervalFlag = false;
bool serial_send_OSC2IntervalFlag = false;
bool serial_send_LFO1SpeedFlag = false;
bool serial_send_LFO1toDCOFlag = false;
bool serial_send_LFO1toDCOWaveChangeFlag = false;
bool serialSendADSR3ControlValuesFlag = false;
bool serialSendADSR3toDCOFlag = false;
bool serialSendADSR3ToOscSelectFlag = false;
bool serialSendVoiceModeFlag = false;
bool serialSendUnisonDetuneFlag = false;
bool serialSendPWMPotsControlManualFlag = false;
bool serialSendPWFlag = false;
bool serialSendLFO2ToPWMFlag = false;

// Small outgoing param queues for DCO link (used by sendSerial()).
// Named *Buf to avoid clashing with ParamId wrapper function names.
uint8_t  serialSendParamByteToDCOBuf[2];
uint16_t serialSendParamToDCOBuf[2];

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