#ifndef __LFO_H__
#define __LFO_H__

#include <mo-lfo.h>        // required for function generation

//static constexpr uint16_t PWM_CC = 4096;
static constexpr uint16_t LFO1_CC = 4095;
static constexpr uint16_t LFO1_CC_HALF = LFO1_CC / 2;
static constexpr uint16_t LFO2_CC = 4095;
static constexpr uint16_t LFO2_CC_HALF = LFO2_CC / 2;

static constexpr uint16_t LFO_DRIFT_CC = 1000;
static constexpr uint16_t LFO_DRIFT_CC_HALF = LFO_DRIFT_CC/ 2;

//////////////// LFO ian ////////////////////////////////////////

lfo             LFO1_class(LFO1_CC + 1);
lfo             LFO2_class(LFO2_CC + 1); 
//lfo             LFO3_class(LFO3_CC + 1); 

lfo LFO_DRIFT_CLASS[NUM_VOICES] = {
  lfo(LFO_DRIFT_CC),
  // Monosynth NUM_VOICES=1: unused DCO4 drift LFO slots kept commented for reference.
  // lfo(LFO_DRIFT_CC),
  // lfo(LFO_DRIFT_CC),
  // lfo(LFO_DRIFT_CC)
};

/////////////////////////////////////////////////////////////////

byte LFO_DRIFT_WAVEFORM = 2;
float LFO_DRIFT_SPEED_OFFSET[NUM_VOICES];
float LFO_DRIFT_SPEED = 0.4;
volatile int16_t LFO_DRIFT_LEVEL[NUM_VOICES];
volatile int16_t VCF_DRIFT[NUM_VOICES];

int16_t      LFO1Level;
byte     LFO1Waveform;
float    LFO1Speed;
uint16_t LFO1toVCF;
uint16_t LFO1toVCA = 0;
int16_t    LFO1toDCO;

int16_t LFO2Level;
byte     LFO2Waveform;
float    LFO2Speed;
uint16_t LFO2toVCF;
uint16_t LFO2toPWM;
uint16_t LFO2toOSC2DETUNE;
uint16_t LFO2toOSC3DETUNE;

void LFO1();
void LFO2();

#endif
