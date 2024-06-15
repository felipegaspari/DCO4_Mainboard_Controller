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
    VCA_PWM[i] = lin_to_log_table[ADSR1Level[i]];
  }
  // VCA_PWM[0] = 4095 - ADSR1Level[0] - VCALevel;
  // VCA_PWM[1] = 4095 - ADSR1Level[1] - VCALevel;

  // /* ***************************           VCF PWM          *****************************/
  for (byte i = 0; i < NUM_VOICES; i++) {
    if (VCFKeytrack > 0) {
      VCFKeytrackPerVoice[i] = 1 + (VCFKeytrackModifier * map(note[i], 0, 150, -60, 90));
      // DEBUG KEYTRACK
      //Serial.println((String)"VOICE N: " + i +  (String)"    VCFKeytrackPerVoice: " + VCFKeytrackPerVoice[i] + (String)"    VCFKeytrackModifier: " + VCFKeytrackModifier + (String)"    VCFKeytrack: " + VCFKeytrack);
    } else {
      VCFKeytrackPerVoice[i] = 1;
    }

    VCF_PWM[i] =
      //map(
        (int)constrain(
          (
            (
              ((float)ADSR2Level[i] * ADSR2toVCF_formula)
              + ((float)LFO2Level * LFO2toVCF_formula)
              + CUTOFF)
            * (1 - ((float)velocityToVCF * (127 - velocity[i])))
            * (float)VCFKeytrackPerVoice[i]),
          0, 4095); //,
        //0, 4095, ADSR_2_CC, 0);
  }

  // /* ***************************           PW PWM          *****************************/
  // for (byte i = 0; i < NUM_VOICES; i++) {
  //   PW_PWM[i] = (uint16_t)constrain(4095 - ((float)ADSR3Level[i] * ADSR3toPWM_formula) - ((float)LFO2Level * LFO2toPWM_formula) - PW /*+ RANDOMNESS1 + RANDOMNESS2*/, 0, 4095);
  // }

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

  htim15->setCaptureCompare(2, RESONANCE, TICK_COMPARE_FORMAT);         //RESO1
  htim2->setCaptureCompare(3, 4095 - VCA_PWM[0], TICK_COMPARE_FORMAT);  //RESO2
  htim3->setCaptureCompare(3, 4095 - VCA_PWM[0], TICK_COMPARE_FORMAT);  //RESO3
  htim5->setCaptureCompare(3, 4095 - VCA_PWM[0], TICK_COMPARE_FORMAT);  //RESO4

  //VCA?
  htim8->setCaptureCompare(1, VCA_PWM[0], TICK_COMPARE_FORMAT);
  htim4->setCaptureCompare(3, VCA_PWM[1], TICK_COMPARE_FORMAT);
  htim4->setCaptureCompare(1, VCA_PWM[2], TICK_COMPARE_FORMAT);
  htim12->setCaptureCompare(1, VCA_PWM[3], TICK_COMPARE_FORMAT);

  //MIX_BOARD:
  htim15->setCaptureCompare(1, SQR1Level, TICK_COMPARE_FORMAT);
  htim5->setCaptureCompare(2, SubLevel, TICK_COMPARE_FORMAT);  //SUB2
  htim5->setCaptureCompare(4, SubLevel, TICK_COMPARE_FORMAT);  //SUB1
  htim3->setCaptureCompare(4, SQR1Level, TICK_COMPARE_FORMAT);

  htim1->setCaptureCompare(1, SQR1Level, TICK_COMPARE_FORMAT);
  htim1->setCaptureCompare(2, SQR1Level, TICK_COMPARE_FORMAT);
  htim1->setCaptureCompare(3, SubLevel, TICK_COMPARE_FORMAT);  // SUB4
  htim2->setCaptureCompare(4, SubLevel, TICK_COMPARE_FORMAT);  // SUB3

  // PWM SUELTOS
  htim8->setCaptureCompare(2, 4095 - ssi2144_linear_table[VCF_PWM[0]], TICK_COMPARE_FORMAT);
  htim4->setCaptureCompare(4, 4095 - ssi2144_linear_table[VCF_PWM[1]], TICK_COMPARE_FORMAT);
  htim4->setCaptureCompare(2, 4095 - ssi2144_linear_table[VCF_PWM[2]], TICK_COMPARE_FORMAT);
#ifndef ENABLE_SPI

  htim12->setCaptureCompare(2, 4095 - ssi2144_linear_table[VCF_PWM[3]], TICK_COMPARE_FORMAT);  //  CONFLICT WITH SPI PIN !!
#endif

// SQUARE PW
#ifndef ENABLE_SPI
  htim3->setCaptureCompare(2, PW_PWM[0], TICK_COMPARE_FORMAT);
  htim2->setCaptureCompare(2, PW_PWM[0], TICK_COMPARE_FORMAT);
  htim2->setCaptureCompare(1, PW_PWM[0], TICK_COMPARE_FORMAT);
  htim8->setCaptureCompare(4, PW_PWM[0], TICK_COMPARE_FORMAT);
#endif


  // VCFKeytrackPerVoice[0] = 1;
  // VCFKeytrackPerVoice[1] = 1;
  //   VCFKeytrackPerVoice[2] = 1;
  // VCFKeytrackPerVoice[3] = 1;
  // VCF_PWM[0] = map((int)constrain(((((float)ADSR2Level[0] * ADSR2toVCF_formula) + CUTOFF)) * (1 - ((float)velocityToVCF * (127 - velocity[1]))) * (float)VCFKeytrackPerVoice[0], 0, 4095), 0, 4095, ADSR_2_CC - 50, 0);
  // VCF_PWM[1] = map((int)constrain(((((float)ADSR2Level[1] * ADSR2toVCF_formula) + ((float)LFO1Level * LFO1toVCF_formula) + ((float)LFO2Level * LFO2toVCF_formula) + CUTOFF)) * (1 - ((float)velocityToVCF * (127 - velocity[1]))) * (float)VCFKeytrackPerVoice[1], 0, 4095), 0, 4095, ADSR_2_CC - 50, 0);
  // VCF_PWM[2] = map((int)constrain(((((float)ADSR2Level[2] * ADSR2toVCF_formula) + ((float)LFO1Level * LFO1toVCF_formula) + ((float)LFO2Level * LFO2toVCF_formula) + CUTOFF)) * (1 - ((float)velocityToVCF * (127 - velocity[2]))) * (float)VCFKeytrackPerVoice[2], 0, 4095), 0, 4095, ADSR_2_CC - 50, 0);
  // VCF_PWM[3] = map((int)constrain(((((float)ADSR2Level[3] * ADSR2toVCF_formula) + ((float)LFO1Level * LFO1toVCF_formula) + ((float)LFO2Level * LFO2toVCF_formula) + CUTOFF)) * (1 - ((float)velocityToVCF * (127 - velocity[3]))) * (float)VCFKeytrackPerVoice[3], 0, 4095), 0, 4095, ADSR_2_CC - 50, 0);

  // VCF_PWM[0] = constrain(((((float)ADSR2Level[0] * ADSR2toVCF_formula) + CUTOFF) / 2), 0, 4095);
  // VCF_PWM[1] = constrain(((((float)ADSR2Level[1] * ADSR2toVCF_formula) + CUTOFF) / 2), 0, 4095);
  // VCF_PWM[2] = constrain(((((float)ADSR2Level[2] * ADSR2toVCF_formula) + CUTOFF) / 2), 0, 4095);
  // VCF_PWM[3] = constrain(((((float)ADSR2Level[3] * ADSR2toVCF_formula) + CUTOFF) / 2), 0, 4095);

  // VCF changed to VCA for testing
  htim3->setCaptureCompare(1, VCA_PWM[0], TICK_COMPARE_FORMAT);   //CUTOFF 1
  htim1->setCaptureCompare(4, VCA_PWM[1], TICK_COMPARE_FORMAT);   //CUTOFF 2
  htim13->setCaptureCompare(1, VCA_PWM[2], TICK_COMPARE_FORMAT);  //CUTOFF 3
  htim5->setCaptureCompare(1, VCA_PWM[3], TICK_COMPARE_FORMAT);   //CUTOFF 4

  // htim5->setCaptureCompare(1, CUTOFF, TICK_COMPARE_FORMAT);   //CUTOFF x?
  // htim3->setCaptureCompare(1, CUTOFF, TICK_COMPARE_FORMAT);   //CUTOFF 2
  // htim1->setCaptureCompare(4, CUTOFF, TICK_COMPARE_FORMAT);   //CUTOFF 1?
  // htim13->setCaptureCompare(1, CUTOFF, TICK_COMPARE_FORMAT);  //CUTOFF 1?

  if (timer1msFlag) {



    // mcp.fastWrite(lin_to_log_table[VCA_PWM[0]], SQR1Level, lin_to_log_table[VCA_PWM[0]], lin_to_log_table[VCA_PWM[0]]); // V1 OSC2, V2 OSC1, V2 OSC2, V3 OSC2
    // mcp2.fastWrite(SQR1Level, lin_to_log_table[VCA_PWM[0]], SQR1Level, SubLevel);  // V3 OSC1, V4 OSC2, V4 OSC1, SUB3
    // mcp3.fastWrite(SubLevel, SubLevel, SubLevel, SQR1Level); // SUB4, SUB1, SUB2, V1 OSC1

#ifdef ENABLE_SPI
    // // // RESO
    // BU2505FV_set_channel(9, RESONANCE / 4);   //  RESO 1
    // BU2505FV_set_channel(10, RESONANCE / 4);  //  RESO 2
    // BU2505FV_set_channel(2, RESONANCE / 4);   //  RESO 3
    // BU2505FV_set_channel(1, RESONANCE / 4);   //  RESO 4
    // // //LEVEL
    // BU2505FV_set_channel(3, lin_to_log_table[VCA_PWM[0]]);  // VCA 1
    // BU2505FV_set_channel(4, lin_to_log_table[VCA_PWM[0]]);  // VCA 2
    // BU2505FV_set_channel(6, lin_to_log_table[VCA_PWM[0]]);  // VCA 3
    // BU2505FV_set_channel(7, lin_to_log_table[VCA_PWM[0]]);  // VCA 4
#endif
  }
}

void mcpUpdate() {
  mcp.analogWrite(SQR1Level, SQR2Level, SQR1Level, SQR2Level);  // V1 OSC1, V2 OSC2, V2 OSC1, V3 OSC2
  mcp2.analogWrite(SQR1Level, SQR2Level, SQR1Level, SubLevel);  // V3 OSC1, V4 OSC2, V4 OSC1, SUB3
  mcp3.analogWrite(SubLevel, SubLevel, SubLevel, SQR2Level);    // SUB4, SUB1, SUB2, V1 OSC2
}
