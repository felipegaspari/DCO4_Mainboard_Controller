void setPWMOuts() {
#include "include_all.h"
  // /* ***************************           VCA PWM          *****************************/
  // uint16_t RESONANCE = somevalue - someothervalue;
  // bool RESONANCEAmpCompensation = true;

  if (timer1msFlag) {
    static constexpr int DEFAULT_VCA_COMPENSATION = 100;
    if (RESONANCEAmpCompensation) {
      static constexpr int MAX_RESONANCE = 2300;
      static constexpr int MIN_RESONANCE = 50;
      static constexpr int MAX_VCA_COMPENSATION = 315;
      static constexpr float COMPENSATION_FACTOR = 0.14;
      VCAResonanceCompensation = (RESONANCE >= MIN_RESONANCE) ? (MAX_VCA_COMPENSATION - ((RESONANCE - MIN_RESONANCE) * COMPENSATION_FACTOR)) : MAX_VCA_COMPENSATION;
    } else {
      VCAResonanceCompensation = DEFAULT_VCA_COMPENSATION;
    }
  }

  for (byte i = 0; i < NUM_VOICES; i++) {
    //VCA_PWM[i] = 4095 - (map((int)constrain((((float)ADSR1Level[i] * ADSR1toVCA_formula /* * (1.27 - (velocityToVCA * (127 - velocity[i])))*/) + ((float)LFO1Level * LFO1toVCA_formula) /*+ ((float)LFO2Level / 512 * LFO2toVCA)*/ + VCALevel /*+ RANDOMNESS1 + RANDOMNESS2*/), 0, 4095), 0, 4095, 0, 1820) * VCAResonanceCompensation);
    //VCA_PWM[i] = map(AS2164_VCA_linearize_table[ADSR1Level[i]], 0, 4095, VCAResonanceCompensation, 4095);//
    VCA_PWM[i] = linearInterpolation(AS2164_VCA_linearize_table[ADSR1Level[i]], 0, 4095, VCAResonanceCompensation, 4095 - VCALevel);
  }


  // /* ***************************           VCF PWM          *****************************/

  float ADSR2toVCFcalculated = 0.0f;

  if (timer1msFlag) {
    if (VCFKeytrack != 0) {
      for (byte i = 0; i < NUM_VOICES; i++) {
        VCFKeytrackPerVoice[i] = 1.00f + (float)(VCFKeytrackModifier * map(note[i], 0, 150, -60, 90));
      }
    } else {
      for (byte i = 0; i < NUM_VOICES; i++) {
        VCFKeytrackPerVoice[i] = 1;
      }
    }
  }

  // OLD CODE
  // for (byte i = 0; i < NUM_VOICES; i++) {
  //   ADSR2toVCFcalculated = (float)ADSR2Level[i] * ADSR2toVCF_formula;
  //   VCF_PWM[i] =
  //     4095 - (int)constrain(((ADSR2toVCFcalculated + ((float)LFO2Level * LFO2toVCF_formula) + CUTOFF + VCF_DRIFT[i]) * (1 - ((float)velocityToVCF * (127 - velocity[i]))) * (float)VCFKeytrackPerVoice[i]), 0, 4095);
  // }

  float LFO2toVCF = (float)LFO2Level * LFO2toVCF_formula;
  float velocityFactor[NUM_VOICES];

  for (byte i = 0; i < NUM_VOICES; i++) {
    if (velocityToVCFVal == 0) {
      velocityFactor[i] = 1;
    } else {
      velocityFactor[i] = 1 - ((float)velocityToVCF * (127 - velocity[i]));
    }
    float ADSR2toVCFcalculated = (float)ADSR2Level[i] * ADSR2toVCF_formula;
    float combinedValue = ADSR2toVCFcalculated + LFO2toVCF + CUTOFF + VCF_DRIFT[i];
    float finalValue = combinedValue * velocityFactor[i] * (float)VCFKeytrackPerVoice[i];
    VCF_PWM[i] = 4095 - (int)constrain(finalValue, 0, 4095);
  }

  // /* ***************************           PW PWM          *****************************/

  // RESONANCE
  htim4->setCaptureCompare(1, RESONANCE, TICK_COMPARE_FORMAT);  // RESO1
  htim8->setCaptureCompare(1, RESONANCE, TICK_COMPARE_FORMAT);  // RESO2
  htim5->setCaptureCompare(1, RESONANCE, TICK_COMPARE_FORMAT);  // RESO3
  htim3->setCaptureCompare(1, RESONANCE, TICK_COMPARE_FORMAT);  // RESO4

  // CUTOFF
  htim12->setCaptureCompare(1, VCF_PWM[0], TICK_COMPARE_FORMAT);  // CUTOFF1
  htim4->setCaptureCompare(3, VCF_PWM[1], TICK_COMPARE_FORMAT);   // CUTOFF2
  htim15->setCaptureCompare(2, VCF_PWM[2], TICK_COMPARE_FORMAT);  // CUTOFF3
  htim5->setCaptureCompare(3, VCF_PWM[3], TICK_COMPARE_FORMAT);   // CUTOFF4

  // VCA
  htim3->setCaptureCompare(3, VCA_PWM[3], TICK_COMPARE_FORMAT);
  htim13->setCaptureCompare(1, VCA_PWM[1], TICK_COMPARE_FORMAT);
  htim2->setCaptureCompare(3, VCA_PWM[0], TICK_COMPARE_FORMAT);
  htim1->setCaptureCompare(4, VCA_PWM[2], TICK_COMPARE_FORMAT);


  if (timer1msFlag) {

#ifdef ENABLE_SPI

#endif
  }
}

void setPWMOutsManualCalibration() {

  for (int i = 0; i < 4; i++) {
        waveSelectorMux.writePin(sawPins[i], 1);
        waveSelectorMux.writePin(saw2Pins[i], 1);
        waveSelectorMux.writePin(triPins[i], 1);
        waveSelectorMux.writePin(sinePins[i], 1);
      }

  uint8_t currentCalibrationOscillator = (uint8_t)manualCalibrationStage / 2;
  uint8_t currentCalibrationVoice = (uint8_t)manualCalibrationStage  / 4;

  if (((uint8_t)manualCalibrationStage % 2) == 0) {
    if ((currentCalibrationOscillator % 2) == 0) {
      SQR1Level = 50;
      SQR2Level = 4095;
      waveSelectorMux.writePin(sawPins[currentCalibrationVoice], 0);
    } else {
      SQR1Level = 4095;
      SQR2Level = 50;
      waveSelectorMux.writePin(saw2Pins[currentCalibrationVoice], 0);
    }
  } else {
    if ((currentCalibrationOscillator % 2) == 0) {
      SQR1Level = 50;
      SQR2Level = 4095;
      waveSelectorMux.writePin(triPins[currentCalibrationVoice], 0);
    } else {
      SQR1Level = 4095;
      SQR2Level = 50;
      waveSelectorMux.writePin(sinePins[currentCalibrationVoice], 0);
    }
  }

  uint16_t RESONANCE_manual_calibration = 0;
  uint16_t CUTOFF_manual_calibration = 0;
  uint16_t VCA_manual_calibration[] = { 4095, 4095, 4095, 4095 };

  VCA_manual_calibration[currentCalibrationVoice] = 150;

  // RESONANCE
  htim4->setCaptureCompare(1, RESONANCE_manual_calibration, TICK_COMPARE_FORMAT);  // RESO1
  htim8->setCaptureCompare(1, RESONANCE_manual_calibration, TICK_COMPARE_FORMAT);  // RESO2
  htim5->setCaptureCompare(1, RESONANCE_manual_calibration, TICK_COMPARE_FORMAT);  // RESO3
  htim3->setCaptureCompare(1, RESONANCE_manual_calibration, TICK_COMPARE_FORMAT);  // RESO4



  // CUTOFF
  htim12->setCaptureCompare(1, CUTOFF_manual_calibration, TICK_COMPARE_FORMAT);  // CUTOFF1
  htim4->setCaptureCompare(3, CUTOFF_manual_calibration, TICK_COMPARE_FORMAT);   // CUTOFF2
  htim15->setCaptureCompare(2, CUTOFF_manual_calibration, TICK_COMPARE_FORMAT);  // CUTOFF3
  htim5->setCaptureCompare(3, CUTOFF_manual_calibration, TICK_COMPARE_FORMAT);   // CUTOFF4

  // VCA

  htim3->setCaptureCompare(3, VCA_manual_calibration[3], TICK_COMPARE_FORMAT);
  htim13->setCaptureCompare(1, VCA_manual_calibration[1], TICK_COMPARE_FORMAT);
  htim2->setCaptureCompare(3, VCA_manual_calibration[0], TICK_COMPARE_FORMAT);
  htim1->setCaptureCompare(4, VCA_manual_calibration[2], TICK_COMPARE_FORMAT);


  waveSelectorMux.update();
  mcpUpdate();
}

void mcpUpdate() {
  mcp.analogWrite(SQR1Level, SQR2Level, SQR1Level, SQR2Level);  // V1 OSC1, V2 OSC2, V2 OSC1, V3 OSC2
  mcp2.analogWrite(SQR1Level, SQR2Level, SQR1Level, SubLevel);  // V3 OSC1, V4 OSC2, V4 OSC1, SUB3
  mcp3.analogWrite(SubLevel, SubLevel, SubLevel, SQR2Level);    // SUB4, SUB1, SUB2, V1 OSC2
}

uint16_t linearInterpolation(uint16_t value, uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1) {
  // Ensure x1 is not equal to x0 to avoid division by zero
  if (x1 == x0) {
    return y0;
  }

  // Calculate the interpolation using integer arithmetic
  uint32_t numerator = (uint32_t)(value - x0) * (y1 - y0);
  uint16_t result = y0 + (numerator / (x1 - x0));

  return result;
}