#include <adsr.h>

#define NUM_VOICES 4

#define PIN_SAW1 70
#define PIN_SAW2 70
#define PIN_TRI 70
#define PIN_SIN 70

byte OSC1Interval = 24;
byte OSC2Interval = 24;
uint16_t OSC2Detune = 255;

float DETUNE1;
float DETUNE2;
uint16_t PW;

uint16_t SubLevel;
uint16_t SQR1Level;
uint16_t SQR2Level;

uint16_t RESONANCE;
uint16_t CUTOFF = 1024;
uint16_t VCALevel = 0;

//#define ENABLE_SD

#include "Arduino.h"
#include "params.h"
#include "auxiliary.h"
#include "PWM.h"
#include "ADSR.h"
#include "LFO.h"
#include "Timers.h"
#include "Timers_millis.h"
#include "Serial.h"

#include "Screen.h"

#include "flashData.h"
//#include "autotune.h"
#include "formulas.h"
#include "waveSelector.h"


//static const float clockFreq = 168000000;

uint16_t random1;
uint16_t random2;
//uint16_t randomnessIntensity1 = 25;
//uint16_t randomnessIntensity2 = 0;
uint16_t randomnessIntensity1 = 0;
uint16_t randomnessIntensity2 = 0;
float RANDOMNESS1 = 0;
float RANDOMNESS2 = 0;

uint32_t tiempodeejecucion;

void setup() {

  init_aux();

  init_timers();

  init_LFOs();

  init_ADSR();

  initScreen();

  initEEPROM();

  init_waveSelector();

  //initAutotune();

#ifdef ENABLE_SERIAL
  Serial.begin(2000000);
#endif
#ifdef ENABLE_SERIAL1
  Serial1.begin(2500000);
#endif
#ifdef ENABLE_SERIAL2
  Serial2.begin(2500000);
#endif
#ifdef ENABLE_SERIAL8
  Serial8.begin(2500000);
#endif

  serial_send_preset_scroll(currentPreset, presetName);

  noteStart[0] = 0;
  noteEnd[0] = 1;

    for (int i = 0; i < 20; i++) {
    formula_update(i);
    controls_formula_update(i);
  }
}

void loop() {
  //if (h < 254) { h++;} else { h = 0;}
  //   if  (timer200msFlag) {
  //  drawTM(potMedian[7]);
  //    }

  unsigned long loopStartTime = micros();

  random1 = random(0, 150);
  random2 = random(0, 40);

  //RANDOMNESS1 = (float)random1 / 1440000 * randomnessIntensity1;
  //RANDOMNESS2 = random2 * randomnessIntensity2;

  memset(noteEnd, 0, sizeof(noteEnd));
  memset(noteStart, 0, sizeof(noteStart));

  millisTimer();

  if (timer99microsFlag) {
    sendDetune2Flag = true;
    read_serial_1();
    read_serial_8();
  }

  // if (timer1msFlag) {

  // }

  if (timer1msFlag) {
    if (ADSR3Enabled && ADSR3toDETUNE1 != 0) {
      serialSendADSR3ControlValuesFlag = true;
    }
      if (PWMPotsControlManual) {
      serialSendPWFlag = true;
    }
    // formula_update(3);
    // formula_update(2);
  }

  read_serial_2();

  if (timer99microsFlag == 1) {

    // LFO1();
    // LFO2();
  }

  LFO1();
  LFO2();

  ADSR_update();

  setPWMOuts();

  sendSerial();

  //unsigned long tiempodeejecuciontotal = micros() - loopStartTime;

  //if (tiempodeejecuciontotal > 10) {
  //Serial.println(tiempodeejecuciontotal);
  //}


  if (timer200msFlag) {
    //serial_send_param_change(22, ADSR1Level[0]);
    //drawTM(RESONANCE);
    //drawTM(CUTOFF);
    //drawTMScreen(true);
    //serial_send_param_change(15, ADSR3toDETUNE1_formula * 100000);
    // Serial.print((String) " - CUTOFF: " + CUTOFF);
    // Serial.print((String) " - RESONANCE: " + RESONANCE);
    // Serial.print((String) " - ADSR2 TO VCF: " + ADSR2toVCF);
    // Serial.print((String) " - LFO1toVCF: " + LFO1toVCF);
    // Serial.print((String) " - ADSR1toVCA: " + ADSR1toVCA);
    // Serial.println((String) " - PW: " + PW + (String) " - CUTOFF: " + CUTOFF + (String) " - RESONANCE: " + RESONANCE + (String) " - ADSR2 TO VCF: " + ADSR2toVCF +  (String) " - ADSR2 RELEASE: " + ADSR2_release + (String) " - VCF_PWM: " + VCF_PWM[0]);
    // Serial.println();
    // Serial.println((String) " - SQR1Level: " + SQR1Level);
  }

  // if (tiempodeejecuciontotal > 600) {
  //     drawTM(tiempodeejecuciontotal);
  //     drawTMScreen(true);
  //   }

  // if (tiempodeejecucion > 2) {
  // drawTMScreen(true);
  // }

#ifdef ENABLE_SERIAL
  //drawTM(tiempodeejecucion);
  if (1 == 2) {
    //if ( SPIval == 111) {
    //if (timer99microsFlag) {58
    //if (timer31msFlag) {
    // if (tiempodeejecuciontotal > 100 ) {
    //    contadorLatencia++;
    //    float tiemposobrelatencia = (float) micros() / contadorLatencia; // baseline = 5000
    //if (noteEnd[0] == 1) {
    //    Serial.print(tiempodeejecuciontotal);
    //    tiempodeejecucionMedian.add(tiempodeejecuciontotal);
    //    tiempodeejecucionMedian2.add(tiempodeejecucionMedian.getMedian());
    //    Serial.print(tiempodeejecucionMedian.getMedian());
    //    Serial.print((String)" - t_j : " + tiempodeejecucion);
    //    //    Serial.print((String)" - t / l : " + tiemposobrelatencia);
    //    //    Serial.print((String)" - noteStart" + noteStart[0]);
    //    //    Serial.print((String)" - noteEnd" + noteEnd[0]);
    //    //  //Serial.print((String) " - LFO1Level" + LFO1Level);
    //    ////  Serial.print((String)"- VCF_LFO_INT: " + VCFLFOIntensityLog);
    //    Serial.print((String)"- Fader raw : " + muxFadersRaw[4]);
    //    Serial.print((String)"- Fader median : " + faderMedian[4]);
    //   Serial.print((String)"- Attack2: " + ADSR2_attack);
    //   Serial.print((String)"- Decay2: " + ADSR2_decay);
    //   Serial.print((String)"- Sustain2: " + ADSR2_sustain);
    //    //  Serial.print((String)"- enc1: " + encVal[0]);
    //    //Serial.print((String)" - enc2: " + encVal[1]);
    //    Serial.print((String)" - enc3: " + encVal[2]);
    //    Serial.print((String)" - enc4: " + encVal[3]);
    //    Serial.print((String)" - enc5: " + encVal[4]);
    Serial.print((String) " - CUTOFF: " + CUTOFF);
    Serial.print((String) " - ADSR2 TO VCF: " + ADSR2toVCF);
    //    Serial.print((String)" - LFO TO VCF: " + LFO1toVCF);
    //    Serial.print((String)" - LFO1 TO DCO: " + LFO1toDCO);
    //    Serial.print((String)" - LFO1 SPEED: " + LFO1Speed);
    //    Serial.print((String)" - LFO1 LEVEL: " + LFO1Level);
    //    Serial.print((String)"- DETUNE1 : ");
    //    Serial.print(DETUNE1, 4);
    //Serial.print((String)"- OSC2 DETUNE : " + OSC2Detune);
    //Serial.print((String)" - PW : " + PW);
    //Serial.print((String)" - LFO1toPWM : " + LFO1toPWM);
    //Serial.print((String)" - ADSR1toPWM : " + ADSR1toPWM);
    //Serial.print((String)"- velocity : " + velocity[0]);
    //Serial.print((String)"- freq : " + freq);
    //    Serial.print("HOLA");
    //Serial.print((String)" -enc6" + encVal[5]);
    // Serial.print(note[0]);
    //Serial.print(analogRead(PC0));
    Serial.println();
  }
#endif
}
