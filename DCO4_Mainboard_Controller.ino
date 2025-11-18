#define NUM_VOICES 4

// PINS reserved for SDMMC: PD2, PC12,PC8, PC9, PC10,PC11

//#define LD_PIN PD_9

//#define ENABLE_SPI

#define ENABLE_SD

#include "Arduino.h"

#include <stdint.h>

#include "params_def.h"
#include "param_router.h"

#include "params.h"
#include "auxiliary.h"
#include "PWM.h"
#include "ADSR.h"
#include "LFO.h"
#include "Timers.h"
#include "Timers_millis.h"
#include "Serial.h"

//#include "Screen.h"

#include "flashData.h"

#include "formulas.h"
#include "tables.h"
#include "waveSelector.h"

#ifdef ENABLE_SPI
#include "SPI_settings.h"
#endif

//#include "autotune.h"

// #define RUNNING_AVERAGE
// Optional microsecond benchmarking using RunningAverage, similar to DCO4_DCO.
// To activate these measurements, define RUNNING_AVERAGE (e.g. in auxiliary.h or build flags).
/* BENCHMARK REFERENCE NOVEMBER 2025
--------------------------------
MAINBOARD LOOP TIMING (us avg)
--------------------------------
Loop total:          7.49
millisTimer():       -0.00
Serial 1+8 block:    1.34
Serial 2:            0.01
1ms flag block:      0.86
LFO1+LFO2:           0.54
ADSR_update():       3.66
PWM outputs:         3.85
sendSerial():        0.25
*/

#ifdef RUNNING_AVERAGE
#include "RunningAverage.h"

// RunningAverage objects for main loop timing measurements (2000 samples each)
RunningAverage ra_main_loop_total(2000);
RunningAverage ra_main_millisTimer(2000);
RunningAverage ra_main_serial_1_8(2000);
RunningAverage ra_main_serial_2(2000);
RunningAverage ra_main_1ms_block(2000);
RunningAverage ra_main_LFOs(2000);
RunningAverage ra_main_ADSR(2000);
RunningAverage ra_main_PWM(2000);
RunningAverage ra_main_sendSerial(2000);

// Forward declaration for periodic debug printout
void print_mainboard_loop_timings();
#endif

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
  init_DRIFT_LFOs();

  init_ADSR();

#ifdef ENABLE_SCREEN
  initScreen();
#endif

  // init tables:
  generateBezierArray({ 0, 4095 }, { 4095, 0 }, { 150, 1420 }, { -235, 815 }, 4096, AS2164_VCA_linearize_table);

  // ADSR Faders Table
  for (int i = 0; i < LIN_TO_EXP_TABLE_SIZE; i++) {
    linToExpLookup[i] = linearToExponential(i, 50, maxADSRControlValue);
  }

  init_waveSelector();

  init_MCP4728();

#ifdef ENABLE_SPI
//init_BU2505FV();
#endif

  //  initEEPROM();

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

  //serial_send_preset_scroll(currentPreset, presetName);

  noteStart[0] = 0;
  noteEnd[0] = 1;

  for (int i = 0; i < 10; i++) {
    formula_update(i);
    controls_formula_update(i);
  }

  VCFKeytrack = 0;
  velocityToVCF = 0;
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

#ifdef RUNNING_AVERAGE
  unsigned long t_millisTimer = micros();
#endif
  millisTimer();
#ifdef RUNNING_AVERAGE
  ra_main_millisTimer.addValue((float)(micros() - t_millisTimer));
#endif

  if (timer223microsFlag) {
#ifdef RUNNING_AVERAGE
    unsigned long t_serial_1_8 = micros();
#endif
    read_serial_1();
    read_serial_8();
#ifdef RUNNING_AVERAGE
    ra_main_serial_1_8.addValue((float)(micros() - t_serial_1_8));
#endif
  }

  // if (timer1msFlag) {

  // }

  if (timer1msFlag) {
#ifdef RUNNING_AVERAGE
    unsigned long t_1ms_block = micros();
#endif
    // Periodically refresh ADSR3 values on the DCO whenever ADSR3 is enabled.
    // This restores the old behavior where ADSR3 control data was sent
    // continuously (not only when a new block was received from the input board).
    if (ADSR3Enabled) {
      serialSendADSR3ControlValuesFlag = true;
    }
    if (PWMPotsControlManual) {
      serialSendPWFlag = true;
    }
    DRIFT_LFOs();
    // formula_update(4);
    // formula_update(2);
#ifdef RUNNING_AVERAGE
    ra_main_1ms_block.addValue((float)(micros() - t_1ms_block));
#endif
  }

  // Serial 2 (always processed)
#ifdef RUNNING_AVERAGE
  unsigned long t_serial_2 = micros();
#endif
  read_serial_2();
#ifdef RUNNING_AVERAGE
  ra_main_serial_2.addValue((float)(micros() - t_serial_2));
#endif

  // LFOs
#ifdef RUNNING_AVERAGE
  unsigned long t_LFOs = micros();
#endif
  LFO1();
  LFO2();
#ifdef RUNNING_AVERAGE
  ra_main_LFOs.addValue((float)(micros() - t_LFOs));
#endif

  // ADSR
#ifdef RUNNING_AVERAGE
  unsigned long t_ADSR = micros();
#endif
  ADSR_update();
#ifdef RUNNING_AVERAGE
  ra_main_ADSR.addValue((float)(micros() - t_ADSR));
#endif

  // PWM outputs
#ifdef RUNNING_AVERAGE
  unsigned long t_PWM = micros();
#endif
  if (manualCalibrationFlag == false) {
    setPWMOuts();
  } else {
    setPWMOutsManualCalibration();
  }
#ifdef RUNNING_AVERAGE
  ra_main_PWM.addValue((float)(micros() - t_PWM));
#endif

  // Outgoing serial to other boards
  if (timer99microsFlag == 1) {
#ifdef RUNNING_AVERAGE
    unsigned long t_sendSerial = micros();
#endif
    sendSerial();
#ifdef RUNNING_AVERAGE
    ra_main_sendSerial.addValue((float)(micros() - t_sendSerial));
#endif
  }

  // Total loop duration (microseconds)
#ifdef RUNNING_AVERAGE
  ra_main_loop_total.addValue((float)(micros() - loopStartTime));
#endif


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

#ifdef RUNNING_AVERAGE
  // Print timing statistics periodically when benchmarking is enabled
  if (timer500msFlag) {
    print_mainboard_loop_timings();
  }
#endif

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

#ifdef RUNNING_AVERAGE
void print_mainboard_loop_timings() {
  Serial.println("--------------------------------");
  Serial.println("MAINBOARD LOOP TIMING (us avg)");
  Serial.println("--------------------------------");
  Serial.println((String) "Loop total:          " + ra_main_loop_total.getFastAverage());
  Serial.println((String) "millisTimer():       " + ra_main_millisTimer.getFastAverage());
  Serial.println((String) "Serial 1+8 block:    " + ra_main_serial_1_8.getFastAverage());
  Serial.println((String) "Serial 2:            " + ra_main_serial_2.getFastAverage());
  Serial.println((String) "1ms flag block:      " + ra_main_1ms_block.getFastAverage());
  Serial.println((String) "LFO1+LFO2:           " + ra_main_LFOs.getFastAverage());
  Serial.println((String) "ADSR_update():       " + ra_main_ADSR.getFastAverage());
  Serial.println((String) "PWM outputs:         " + ra_main_PWM.getFastAverage());
  Serial.println((String) "sendSerial():        " + ra_main_sendSerial.getFastAverage());
  Serial.println();
}
#endif
