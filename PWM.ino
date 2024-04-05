void setPWMOuts() {

  //CUTOFF;
  //
  //ADSR1Level[8];
  //ADSR1toVCA;
  //ADSR1toVCF;
  //ADSR1toPWM;
  //ADSR1toDETUNE1;
  //ADSR1toDETUNE2;
  //
  //ADSR2Level[8];
  //ADSR2toVCA;
  //ADSR2toVCF;
  //ADSR2toPWM;
  //ADSR2toDETUNE1;
  //ADSR2toDETUNE2;
  //
  //VCF_PWM[8];
  //VCA_PWM[8];
  //PW_PWM[8];
  //
  //RESONANCE_PWM;
  //
  //SQR1_PWM;
  //SQR2_PWM;
  //SUB_PWM;
  //
  //LFO1Level;
  //LFO1Speed;
  //LFO1toVCF;
  //LFO1toVCA;
  //LFO1toPWM;
  //LFO1toDETUNE1;
  //LFO1toDETUNE2;
  //
  //LFO2Level;
  //LFO2Speed;
  //LFO2toVCF;
  //LFO2toVCA;
  //LFO2toPWM;
  //LFO2toDETUNE1;
  //LFO2toDETUNE2;
  //
  //LFO3Level;
  //LFO3Speed;
  //LFO3toVCF;
  //LFO3toVCA;
  //LFO3toPWM;
  //LFO3toDETUNE1;
  //LFO3toDETUNE2;
  //
  //VCF_PWM[8];
  //VCA_PWM[8];
  //PW_PWM[8];
  //
  //RESONANCE_PWM;
  //
  //SQR1_PWM;
  //SQR2_PWM;
  //SUB_PWM;



  // /* ***************************           VCA PWM          *****************************/
  if (!RESONANCEAmpCompensation) {
    VCAResonanceCompensation = 2.25;
  }
  for (byte i = 0; i < NUM_VOICES; i++) {
    VCA_PWM[i] = 4095 - (map((int)constrain((((float)ADSR1Level[i] * ADSR1toVCA_formula /* * (1.27 - (velocityToVCA * (127 - velocity[i])))*/) + ((float)LFO1Level * LFO1toVCA_formula) /*+ ((float)LFO2Level / 512 * LFO2toVCA)*/ + VCALevel /*+ RANDOMNESS1 + RANDOMNESS2*/), 0, 4095), 0, 4095, 0, 1820) * VCAResonanceCompensation);
    VCA_PWM[i] = ADSR1Level[i];
  }
  // VCA_PWM[0] = 4095 - ADSR1Level[0] - VCALevel;
  // VCA_PWM[1] = 4095 - ADSR1Level[1] - VCALevel;

  // /* ***************************           VCF PWM          *****************************/
  for (byte i = 0; i < NUM_VOICES; i++) {
    // if (VCFKeytrack > 0) {
    //   VCFKeytrackPerVoice[i] = 1 + (VCFKeytrackModifier * map(note[i], 0, 150, -60, 90));
    // } else {
    VCFKeytrackPerVoice[i] = 1;
    // }
    VCF_PWM[i] = map((int)constrain(((((float)ADSR2Level[i] * ADSR2toVCF_formula) + ((float)LFO2Level * LFO2toVCF_formula) + CUTOFF)) * (1 - ((float)velocityToVCF * (127 - 126))) * (float)VCFKeytrackPerVoice[i], 0, 4095), 0, 4095, ADSR_2_CC - 50, 0);
    // + RANDOMNESS1 + RANDOMNESS2
  }

  // /* ***************************           PW PWM          *****************************/
  for (byte i = 0; i < NUM_VOICES; i++) {
    PW_PWM[i] = (uint16_t)constrain(4095 - ((float)ADSR3Level[i] * ADSR3toPWM_formula) - ((float)LFO2Level * LFO2toPWM_formula) - PW /*+ RANDOMNESS1 + RANDOMNESS2*/, 0, 4095);
  }

  // htim5->setCaptureCompare(2, VCA_PWM[0], TICK_COMPARE_FORMAT); // VCA 1
  // htim2->setCaptureCompare(3, VCF_PWM[0], TICK_COMPARE_FORMAT); // VCF 1
  // htim3->setCaptureCompare(2, PW_PWM[0], TICK_COMPARE_FORMAT); // PWM 1

  // htim5->setCaptureCompare(4, VCA_PWM[1], TICK_COMPARE_FORMAT); // VCA 2
  // htim2->setCaptureCompare(4, VCF_PWM[1], TICK_COMPARE_FORMAT); // VCF 2
  // htim2->setCaptureCompare(2, PW_PWM[1], TICK_COMPARE_FORMAT); // PWM 2

  // if (SUBStatus) {
  //   htim1->setCaptureCompare(4, SubLevel, TICK_COMPARE_FORMAT);
  // } else {
  //   htim1->setCaptureCompare(4, 4095, TICK_COMPARE_FORMAT);
  // }
  // if (sqr1Status) {
  //   htim3->setCaptureCompare(3, SQR1Level, TICK_COMPARE_FORMAT);
  // } else {
  //   htim3->setCaptureCompare(3, 4095, TICK_COMPARE_FORMAT);
  // }
  // if (sqr2Status) {
  //   htim13->setCaptureCompare(1, SQR2Level, TICK_COMPARE_FORMAT);
  // } else {
  //   htim13->setCaptureCompare(1, 4095, TICK_COMPARE_FORMAT);
  // }

  //TEST MOTHERBOARD:
  //RESO/VCF

  //VCA?


  //MIX_BOARD:


  // PWM SUELTOS


  // SQUARE PW

  ;
  // htim2->setCaptureCompare(2, VCF_PWM[0] /*map(LFO1Level,0,4095,0,3500)*/, TICK_COMPARE_FORMAT);
  TIM2->CCR2 = VCF_PWM[0];
  // htim3->setCaptureCompare(1, analogRead(PA0), TICK_COMPARE_FORMAT);
  TIM3->CCR1 = RESONANCE;
  //htim3->setCaptureCompare(2, PW, TICK_COMPARE_FORMAT);
  TIM3->CCR2 = PW;
  //htim4->setCaptureCompare(1, PW, TICK_COMPARE_FORMAT);
  TIM4->CCR1 = PW;


  htim4->setCaptureCompare(2, CUTOFF, TICK_COMPARE_FORMAT);
  htim4->setCaptureCompare(3, CUTOFF, TICK_COMPARE_FORMAT);
  htim4->setCaptureCompare(4, RESONANCE, TICK_COMPARE_FORMAT);
  htim2->setCaptureCompare(3, RESONANCE, TICK_COMPARE_FORMAT);
}
