void loadPreset(uint16_t presetN) {

  byte unused_data;
  uint16_t unused_data_uint16_t;
  // eeprom_buffer_fill();

  faderRow1ControlManual = false;
  faderRow2ControlManual = false;
  VCFPotsControlManual = false;
  VCAPotsControlManual = false;
  PWMPotsControlManual = false;

  float a;
  int b;

  uint16_t startByteN = presetN * flashPresetSize;

#ifdef ENABLE_SD
  for (int i = 0; i < flashPresetSize; i++) {
    flashData[i] = presetBank1Buffer[i + startByteN];
  }
#else
  for (int i = 0; i < flashPresetSize; i++) {
    flashData[i] = eeprom_buffered_read_byte(i + startByteN);
  }
#endif

  // bits
  sawStatus = bitRead(flashData[0], 0);
  saw2Status = bitRead(flashData[0], 1);
  triStatus = bitRead(flashData[0], 2);
  sineStatus = bitRead(flashData[0], 3);
  sqr1Status = bitRead(flashData[0], 4);
  sqr2Status = bitRead(flashData[0], 5);
  RESONANCEAmpCompensation = bitRead(flashData[0], 6);
  VCAADSRRestart = bitRead(flashData[0], 7);

  VCFADSRRestart = bitRead(flashData[1], 0);
  PWMPotsControlManual = bitRead(flashData[1], 1);
  ADSR3Enabled = bitRead(flashData[1], 2);
  unused_data = bitRead(flashData[1], 3);
  unused_data = bitRead(flashData[1], 4);
  unused_data = bitRead(flashData[1], 5);
  unused_data = bitRead(flashData[1], 6);
  unused_data = bitRead(flashData[1], 7);

  unused_data = flashData[2];
  unused_data = flashData[3];
  unused_data = flashData[4];
  unused_data = flashData[5];

  // bytes
  LFO1Waveform = flashData[6];
  LFO2Waveform = flashData[7];
  OSC1Interval = flashData[8];
  OSC2Interval = flashData[9];
  oscSyncMode = flashData[10];
  portamentoTime = flashData[11];
  voiceMode = flashData[12];

  // int8_t
  ADSR3ToOscSelect = flashData[13];
  velocityToVCFVal = flashData[14];
  velocityToVCAVal = flashData[15];

  unused_data = flashData[16];
  unused_data = flashData[17];
  unused_data = flashData[18];
  unused_data = flashData[19];
  unused_data = flashData[20];
  unused_data = flashData[21];
  unused_data = flashData[22];
  unused_data = flashData[23];
  unused_data = flashData[24];
  unused_data = flashData[25];
  unused_data = flashData[26];
  unused_data = flashData[27];
  unused_data = flashData[28];
  unused_data = flashData[29];

  // int16_t
  VCFKeytrack = word(flashData[30], flashData[31]);
  SQR1LevelVal = word(flashData[32], flashData[33]);
  SQR2LevelVal = word(flashData[34], flashData[35]);
  SubLevelVal = word(flashData[36], flashData[37]);
  unisonDetune = word(flashData[38], flashData[39]);
  LFO1toDCOVal = word(flashData[40], flashData[41]);
  LFO1SpeedVal = word(flashData[42], flashData[43]);
  LFO2SpeedVal = word(flashData[44], flashData[45]);
  ADSR3toPWM = word(flashData[46], flashData[47]);
  ADSR3toDETUNE1 = word(flashData[48], flashData[49]);

  unused_data_uint16_t = word(flashData[50], flashData[51]);
  unused_data_uint16_t = word(flashData[52], flashData[53]);
  unused_data_uint16_t = word(flashData[54], flashData[55]);
  unused_data_uint16_t = word(flashData[56], flashData[57]);
  unused_data_uint16_t = word(flashData[58], flashData[59]);
  unused_data_uint16_t = word(flashData[60], flashData[61]);

  // uint16_t
  OSC2Detune = word(flashData[62], flashData[63]);
  LFO2toOSC2DETUNE = word(flashData[64], flashData[65]);
  VCALevel = word(flashData[66], flashData[67]);
  LFO1toVCA = word(flashData[68], flashData[69]);
  LFO2toPWM = word(flashData[70], flashData[71]);

  unused_data_uint16_t = word(flashData[72], flashData[73]);
  
  CUTOFF = word(flashData[74], flashData[75]);
  RESONANCE = word(flashData[76], flashData[77]);
  ADSR2toVCF = word(flashData[78], flashData[79]);
  LFO2toVCF = word(flashData[80], flashData[81]);
  ADSR1toVCA = word(flashData[82], flashData[83]);
  PW = word(flashData[84], flashData[85]);

  unused_data_uint16_t = word(flashData[86], flashData[87]);

  ADSR1_attack = word(flashData[88], flashData[89]);
  ADSR1_decay = word(flashData[90], flashData[91]);
  ADSR1_sustain = word(flashData[92], flashData[93]);
  ADSR1_release = word(flashData[94], flashData[95]);

  ADSR2_attack = word(flashData[96], flashData[97]);
  ADSR2_decay = word(flashData[98], flashData[99]);
  ADSR2_sustain = word(flashData[100], flashData[101]);
  ADSR2_release = word(flashData[102], flashData[103]);

  ADSR3_attack = word(flashData[104], flashData[105]);
  ADSR3_decay = word(flashData[106], flashData[107]);
  ADSR3_sustain = word(flashData[108], flashData[109]);
  ADSR3_release = word(flashData[110], flashData[111]);

  unused_data_uint16_t = word(flashData[112], flashData[113]);
  unused_data_uint16_t = word(flashData[114], flashData[115]);
  unused_data_uint16_t = word(flashData[116], flashData[117]);

  unused_data = flashData[118];

  presetName[0] = flashData[119];
  presetName[1] = flashData[120];
  presetName[2] = flashData[121];
  presetName[3] = flashData[122];
  presetName[4] = flashData[123];
  presetName[5] = flashData[124];
  presetName[6] = flashData[125];
  presetName[7] = flashData[126];
  presetName[8] = flashData[127];
  presetName[9] = flashData[128];
  presetName[10] = flashData[129];
  presetName[11] = flashData[130];

  /**********************************************************************************/

  /*   Move parameters to encoder variables */


  ADSR2_set_restart();

  for (int i = 0; i < 20; i++) {
    formula_update(i);
    controls_formula_update(i);
  }

  LFO1_class.setWaveForm(LFO1Waveform);
  LFO2_class.setWaveForm(LFO2Waveform);

  sendDetune2Flag = true;
  serial_send_portamentoFlag = true;
  serial_send_oscSyncModeFlag = true;
  serial_send_OSC1IntervalFlag = true;
  serial_send_OSC2IntervalFlag = true;
  serial_send_LFO1SpeedFlag = true;
  serial_send_LFO1toDCOFlag = true;
  serial_send_LFO1toDCOWaveChangeFlag = true;
  serialSendADSR3ControlValuesFlag = true;
  serialSendADSR3toDCOFlag = true;
  serialSendADSR3ToOscSelectFlag = true;
  serialSendVoiceModeFlag = true;
  serialSendUnisonDetuneFlag = true;

  sendSerial();
  delayMicroseconds(100);
  sendSerial();

  presetNameString = String((char *)presetName);

  currentPreset = presetN;
  presetSelectVal = currentPreset;
}