#ifndef __LFO_H__
#define __LFO_H__

#include <lfo.h>        // required for function generation

//static const uint16_t PWM_CC = 4096;
static const uint16_t LFO1_CC = 1024;
static const uint16_t LFO1_CC_HALF = LFO1_CC / 2;
static const uint16_t LF01_CC_THIRD = LFO1_CC / 3;
static const uint16_t LFO2_CC = 1024;
static const uint16_t LFO2_CC_HALF = LFO2_CC / 2;
static const uint16_t LFO3_CC = 1024;
static const uint16_t LFO3_CC_HALF = LFO2_CC / 2;

//////////////// LFO ian ////////////////////////////////////////

lfo             LFO1_class(LFO1_CC + 1);
lfo             LFO2_class(LFO2_CC + 1); 
//lfo             LFO3_class(LFO3_CC + 1); 

/////////////////////////////////////////////////////////////////

int16_t      LFO1Level;
byte     LFO1Waveform;
float    LFO1Speed;
uint16_t LFO1toVCF;
uint16_t LFO1toVCA = 0;
uint16_t LFO1toPWM;
float    LFO1toDCO;
uint16_t LFO1toDETUNE1;
uint16_t LFO1toDETUNE2;

int16_t LFO2Level;
byte     LFO2Waveform;
float    LFO2Speed;
uint16_t LFO2toVCF;
uint16_t LFO2toVCA;
uint16_t LFO2toPWM;
float    LFO2toDCO;
uint16_t LFO2toDETUNE1;
uint16_t LFO2toDETUNE2;
uint16_t LFO2toOSC2DETUNE;

int16_t LFO3Level;
byte     LFO3Waveform;
float    LFO3Speed;
uint16_t LFO3toVCF;
uint16_t LFO3toVCA;
uint16_t LFO3toPWM;
float    LFO3toDCO;
uint16_t LFO3toDETUNE1;
uint16_t LFO3toDETUNE2;

uint16_t LFO3toSQR1;
uint16_t LFO3toSQR2;
uint16_t LFO3toSUB;

void LFO1();
void LFO2();
void LFO3();

#endif
