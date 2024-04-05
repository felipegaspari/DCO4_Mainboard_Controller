#ifndef __SERIAL_H__
#define __SERIAL_H__

#define ENABLE_SERIAL
#define ENABLE_SERIAL1
#define ENABLE_SERIAL2
//#define ENABLE_SERIAL8

#ifdef ENABLE_SERIAL1
// RX TX
//HardwareSerial Serial1(PA10, PA9);
#endif

#ifdef ENABLE_SERIAL2
// RX TX
HardwareSerial Serial2(PA3, PA2); // TO DCO
#endif

#ifdef ENABLE_SERIAL8
// RX TX
HardwareSerial Serial8(PE0, PE1);
#endif

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