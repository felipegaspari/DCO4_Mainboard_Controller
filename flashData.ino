void initEEPROM() {

#ifdef ENABLE_SD
  while (!SD.begin(SD_DETECT_PIN)) {
    delay(10);
  }

  fileBank1 = SD.open("presetBank1", FILE_READ);
  if (fileBank1) {
  } else {
    fileBank1 = SD.open("presetBank1", FILE_WRITE);
    fileBank1.write(presetBank1Buffer, flashBankSize);
    fileBank1.close();
  }

  fileBank1.read(presetBank1Buffer, flashBankSize);

  fileBank1.close();

  for (int i = 0; i < flashPresetSize; i++) {
    flashData[i] = presetBank1Buffer[i];
  }

#else
  eeprom_buffer_fill();
  for (int i = 0; i < flashPresetSize; i++) {
    flashData[i] = eeprom_buffered_read_byte(i);
  }
#endif
  loadPreset(1);
}

void load_preset_name(byte destinationPreset) {

  uint16_t startByteN = destinationPreset * flashPresetSize;

#ifdef ENABLE_SD

  loadedName[0] = presetBank1Buffer[119 + startByteN];
  loadedName[1] = presetBank1Buffer[120 + startByteN];
  loadedName[2] = presetBank1Buffer[121 + startByteN];
  loadedName[3] = presetBank1Buffer[122 + startByteN];
  loadedName[4] = presetBank1Buffer[123 + startByteN];
  loadedName[5] = presetBank1Buffer[124 + startByteN];
  loadedName[6] = presetBank1Buffer[125 + startByteN];
  loadedName[7] = presetBank1Buffer[126 + startByteN];
  loadedName[8] = presetBank1Buffer[127 + startByteN];
  loadedName[9] = presetBank1Buffer[128 + startByteN];
  loadedName[10] = presetBank1Buffer[129 + startByteN];
  loadedName[11] = presetBank1Buffer[130 + startByteN];

#else

  loadedName[0] = eeprom_buffered_read_byte(119 + startByteN);
  loadedName[1] = eeprom_buffered_read_byte(120 + startByteN);
  loadedName[2] = eeprom_buffered_read_byte(121 + startByteN);
  loadedName[3] = eeprom_buffered_read_byte(122 + startByteN);
  loadedName[4] = eeprom_buffered_read_byte(123 + startByteN);
  loadedName[5] = eeprom_buffered_read_byte(124 + startByteN);
  loadedName[6] = eeprom_buffered_read_byte(125 + startByteN);
  loadedName[7] = eeprom_buffered_read_byte(126 + startByteN);
  loadedName[8] = eeprom_buffered_read_byte(127 + startByteN);
  loadedName[9] = eeprom_buffered_read_byte(128 + startByteN);
  loadedName[10] = eeprom_buffered_read_byte(129 + startByteN);
  loadedName[11] = eeprom_buffered_read_byte(130 + startByteN);

#endif
}

void writePreset(uint16_t presetN) {

  faderRow1ControlManual = false;
  faderRow2ControlManual = false;
  VCFPotsControlManual = false;
  PWMPotsControlManual = false;
  VCAPotsControlManual = false;

  uint16_t startByteN = presetN * flashPresetSize;
  byte *b;
  //byte OSC1Interval = 24; 1
  //byte OSC2Interval = 24; 1
  //byte OSC2Detune = 127;  1
  //float DETUNE1;  4
  //float DETUNE2;  4
  //uint16_t PW;  2

  //volatile uint16_t SubLevel; 2
  //volatile uint16_t SQR1Level = 2048; 2
  //volatile uint16_t SQR2Level;  2

  //volatile uint16_t RESONANCE;  2
  //volatile int CUTOFF =1024;  4   /// TOTAL 25

  flashData[0] = OSC1Interval;
  flashData[1] = OSC2Interval;
  flashData[2] = OSC2Detune;
  flashData[3] = highByte(PW);
  flashData[4] = lowByte(PW);
  flashData[5] = highByte(SubLevel);
  flashData[6] = lowByte(SubLevel);
  flashData[7] = highByte(SQR1Level);
  flashData[8] = lowByte(SQR1Level);
  flashData[9] = highByte(SQR2Level);
  flashData[10] = lowByte(SQR2Level);
  flashData[11] = highByte(RESONANCE);
  flashData[12] = lowByte(RESONANCE);
  flashData[13] = highByte(CUTOFF);
  flashData[14] = lowByte(CUTOFF);

  flashData[15] = voiceMode;
 flashData[16] = (uint8_t)unisonDetune;

  // ADSR1
  flashData[17] = highByte(ADSR1toVCA);
  flashData[18] = lowByte(ADSR1toVCA);
  flashData[19] = highByte(ADSR1toVCF);
  flashData[20] = lowByte(ADSR1toVCF);
  flashData[21] = highByte(ADSR1toPWM);
  flashData[22] = lowByte(ADSR1toPWM);
  flashData[23] = highByte(ADSR1toDETUNE1);
  flashData[24] = lowByte(ADSR1toDETUNE1);
  flashData[25] = highByte(ADSR1toDETUNE2);
  flashData[26] = lowByte(ADSR1toDETUNE2);
  //ADSR2
  flashData[27] = highByte(ADSR2toVCA);
  flashData[28] = lowByte(ADSR2toVCA);
  flashData[29] = highByte(ADSR2toVCF);
  flashData[30] = lowByte(ADSR2toVCF);
  flashData[31] = highByte(ADSR2toPWM);
  flashData[32] = lowByte(ADSR2toPWM);
  flashData[33] = highByte(ADSR2toDETUNE1);
  flashData[34] = lowByte(ADSR2toDETUNE1);
  flashData[35] = highByte(ADSR2toDETUNE2);
  flashData[36] = lowByte(ADSR2toDETUNE2);
  //ADSR3
  flashData[37] = highByte(ADSR3toVCA);
  flashData[38] = lowByte(ADSR3toVCA);
  flashData[39] = highByte(ADSR3toVCF);
  flashData[40] = lowByte(ADSR3toVCF);
  flashData[41] = highByte(ADSR3toPWM);
  flashData[42] = lowByte(ADSR3toPWM);
  flashData[43] = highByte(ADSR3toDETUNE1);
  flashData[44] = lowByte(ADSR3toDETUNE1);
  flashData[45] = ADSR3ToOscSelect;
  flashData[46] = 0;

  flashData[47] = highByte(ADSR1_attack);
  flashData[48] = lowByte(ADSR1_attack);
  flashData[49] = highByte(ADSR1_decay);
  flashData[50] = lowByte(ADSR1_decay);
  flashData[51] = highByte(ADSR1_sustain);
  flashData[52] = lowByte(ADSR1_sustain);
  flashData[53] = highByte(ADSR1_release);
  flashData[54] = lowByte(ADSR1_release);

  flashData[55] = highByte(ADSR2_attack);
  flashData[56] = lowByte(ADSR2_attack);
  flashData[57] = highByte(ADSR2_decay);
  flashData[58] = lowByte(ADSR2_decay);
  flashData[59] = highByte(ADSR2_sustain);
  flashData[60] = lowByte(ADSR2_sustain);
  flashData[61] = highByte(ADSR2_release);
  flashData[62] = lowByte(ADSR2_release);

  flashData[63] = highByte(ADSR3_attack);
  flashData[64] = lowByte(ADSR3_attack);
  flashData[65] = highByte(ADSR3_decay);
  flashData[66] = lowByte(ADSR3_decay);
  flashData[67] = highByte(ADSR3_sustain);
  flashData[68] = lowByte(ADSR3_sustain);
  flashData[69] = highByte(ADSR3_release);
  flashData[70] = lowByte(ADSR3_release);

  // LFO1
  flashData[71] = highByte(LFO1SpeedVal);
  flashData[72] = lowByte(LFO1SpeedVal);
  flashData[73] = highByte(LFO1toDCOVal);
  flashData[74] = lowByte(LFO1toDCOVal);
  flashData[75] = highByte(LFO1toVCF);
  flashData[76] = lowByte(LFO1toVCF);
  flashData[77] = highByte(LFO1toVCA);
  flashData[78] = lowByte(LFO1toVCA);
  flashData[79] = highByte(LFO1toPWM);
  flashData[80] = lowByte(LFO1toPWM);
  flashData[81] = highByte(0);
  flashData[82] = lowByte(0);

  // LFO2
  flashData[83] = highByte(LFO2SpeedVal);
  flashData[84] = lowByte(LFO2SpeedVal);
  flashData[85] = highByte(LFO2toDCOVal);
  flashData[86] = lowByte(LFO2toDCOVal);
  flashData[87] = highByte(LFO2toVCFVal);
  flashData[88] = lowByte(LFO2toVCFVal);
  flashData[89] = highByte(LFO2toVCA);
  flashData[90] = lowByte(LFO2toVCA);
  flashData[91] = highByte(LFO2toPWM);
  flashData[92] = lowByte(LFO2toPWM);
  flashData[93] = highByte(LFO2toOSC2DETUNE);
  flashData[94] = lowByte(LFO2toOSC2DETUNE);

  // LFO3
  flashData[95] = highByte(LFO3SpeedVal);
  flashData[96] = lowByte(LFO3SpeedVal);
  flashData[97] = highByte(LFO3toDCOVal);
  flashData[98] = lowByte(LFO3toDCOVal);
  flashData[99] = highByte(LFO3toVCF);
  flashData[100] = lowByte(LFO3toVCF);
  flashData[101] = highByte(LFO3toVCA);
  flashData[102] = lowByte(LFO3toVCA);
  flashData[103] = highByte(LFO3toPWM);
  flashData[104] = lowByte(LFO3toPWM);
  flashData[105] = highByte(0);
  flashData[106] = lowByte(0);
  flashData[107] = LFO1Waveform;
  flashData[108] = LFO2Waveform;
  flashData[109] = LFO3Waveform;

  bitWrite(flashData[110], 0, sawStatus);
  bitWrite(flashData[110], 1, triStatus);
  bitWrite(flashData[110], 2, sineStatus);
  bitWrite(flashData[110], 3, sqr1Status);
  bitWrite(flashData[110], 4, saw2Status);
  bitWrite(flashData[110], 5, sqr2Status);

  bitWrite(flashData[111], 0, RESONANCEAmpCompensation);
  bitWrite(flashData[111], 1, VCAADSRRestart);
  bitWrite(flashData[111], 2, VCFADSRRestart);

  flashData[112] = velocityToVCFVal;
  flashData[113] = velocityToVCAVal;
  flashData[114] = velocityToPWMVal;

  flashData[115] = portamentoTime;
  flashData[116] = portamentoMode;
  flashData[117] = oscSyncMode;
  flashData[118] = VCFKeytrack;

  flashData[119] = presetName[0];
  flashData[120] = presetName[1];
  flashData[121] = presetName[2];
  flashData[122] = presetName[3];
  flashData[123] = presetName[4];
  flashData[124] = presetName[5];
  flashData[125] = presetName[6];
  flashData[126] = presetName[7];
  flashData[127] = presetName[8];
  flashData[128] = presetName[9];
  flashData[129] = presetName[10];
  flashData[130] = presetName[11];


  //byte noiseLevel;
  //uint16_t aftertouch;

#ifdef ENABLE_SD
  for (int i = 0; i < flashPresetSize; i++) {
    presetBank1Buffer[i + startByteN] = flashData[i];
  }
  fileBank1 = SD.open("presetBank1", FILE_WRITE);
  fileBank1.seek(startByteN);
  fileBank1.write(flashData, flashPresetSize);
  fileBank1.close();

#else

  for (int i = 0; i < flashPresetSize; i++) {
    eeprom_buffered_write_byte(i + startByteN, flashData[i]);
  }
  eeprom_buffer_flush();

#endif

  presetSave = false;
  presetSaved = true;

  faderRow2ControlManual = false;
  faderRow1ControlManual = false;
  VCFPotsControlManual = false;
  VCAPotsControlManual = false;
  PWMPotsControlManual = false;

  currentPreset = presetN;
  presetSelectVal = currentPreset;
}

void loadPreset(uint16_t presetN) {
  //eeprom_buffer_fill();

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
  OSC1Interval = flashData[0];
  OSC2Interval = flashData[1];
  OSC2Detune = flashData[2];

  PW = word(flashData[3], flashData[4]);
  SubLevel = word(flashData[5], flashData[6]);
  SQR1Level = word(flashData[7], flashData[8]);
  SQR2Level = word(flashData[9], flashData[10]);
  RESONANCE = word(flashData[11], flashData[12]);
  CUTOFF = word(flashData[13], flashData[14]);

  voiceMode = flashData[15];
  unisonDetune = (int16_t)flashData[16];

  ADSR1toVCA = word(flashData[17], flashData[18]);
  ADSR1toVCF = word(flashData[19], flashData[20]);
  ADSR1toPWM = word(flashData[21], flashData[22]);
  ADSR1toDETUNE1 = word(flashData[23], flashData[24]);
  ADSR1toDETUNE2 = word(flashData[25], flashData[26]);
  //ADSR2
  ADSR2toVCA = word(flashData[27], flashData[28]);
  ADSR2toVCF = word(flashData[29], flashData[30]);
  ADSR2toPWM = word(flashData[31], flashData[32]);
  ADSR2toDETUNE1 = word(flashData[33], flashData[34]);
  ADSR2toDETUNE2 = word(flashData[35], flashData[36]);
  //ADSR3
  ADSR3toVCA = word(flashData[37], flashData[38]);
  ADSR3toVCF = word(flashData[39], flashData[40]);
  ADSR3toPWM = word(flashData[41], flashData[42]);
  ADSR3toDETUNE1 = word(flashData[43], flashData[44]);
  ADSR3ToOscSelect = flashData[45];

  // flashData[46]

  ADSR1_attack = word(flashData[47], flashData[48]);
  ADSR1_decay = word(flashData[49], flashData[50]);
  ADSR1_sustain = word(flashData[51], flashData[52]);
  ADSR1_release = word(flashData[53], flashData[54]);

  ADSR2_attack = word(flashData[55], flashData[56]);
  ADSR2_decay = word(flashData[57], flashData[58]);
  ADSR2_sustain = word(flashData[59], flashData[60]);
  ADSR2_release = word(flashData[61], flashData[62]);

  ADSR3_attack = word(flashData[63], flashData[64]);
  ADSR3_decay = word(flashData[65], flashData[66]);
  ADSR3_sustain = word(flashData[67], flashData[68]);
  ADSR3_release = word(flashData[69], flashData[70]);



  // LFO1

  LFO1SpeedVal = word(flashData[71], flashData[72]);
  LFO1toDCOVal = word(flashData[73], flashData[74]);
  LFO1toVCF = word(flashData[75], flashData[76]);
  LFO1toVCA = word(flashData[77], flashData[78]);
  LFO1toPWM = word(flashData[79], flashData[80]);
  LFO1toDETUNE2 = word(flashData[81], flashData[82]);
  // LFO2
  LFO2SpeedVal = word(flashData[83], flashData[84]);
  LFO2toDCOVal = word(flashData[85], flashData[86]);
  LFO2toVCFVal = word(flashData[87], flashData[88]);
  LFO2toVCA = word(flashData[89], flashData[90]);
  LFO2toPWM = word(flashData[91], flashData[92]);
  LFO2toDETUNE2 = word(flashData[93], flashData[94]);
  //LFO3
  LFO3SpeedVal = word(flashData[95], flashData[96]);
  LFO3toDCOVal = word(flashData[97], flashData[98]);
  LFO3toVCF = word(flashData[99], flashData[100]);
  LFO3toVCA = word(flashData[101], flashData[102]);
  LFO3toPWM = word(flashData[103], flashData[104]);
  LFO3toDETUNE2 = word(flashData[105], flashData[106]);

  LFO1Waveform = flashData[107];
  LFO2Waveform = flashData[108];
  LFO3Waveform = flashData[109];

  sawStatus = bitRead(flashData[110], 0);
  triStatus = bitRead(flashData[110], 1);
  sineStatus = bitRead(flashData[110], 2);
  sqr1Status = bitRead(flashData[110], 3);
  saw2Status = bitRead(flashData[110], 4);
  sqr2Status = bitRead(flashData[110], 5);

  RESONANCEAmpCompensation = bitRead(flashData[111], 0);
  VCAADSRRestart = bitRead(flashData[111], 1);
  VCFADSRRestart = bitRead(flashData[111], 2);

  velocityToVCFVal = flashData[112];
  velocityToVCAVal = flashData[113];
  velocityToPWMVal = flashData[114];

  portamentoTime = flashData[115];
  portamentoMode = flashData[116];
  oscSyncMode = flashData[117];
  VCFKeytrack = flashData[118];

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


  velocityToVCF = velocityToVCFVal * 0.0005;
  velocityToVCA = velocityToVCAVal * 0.0005;
  //velocityToPWM =



  /*   Move parameters to encoder variables */
  portamentoTimeVal = portamentoTime;

  VCFKeytrackVal = (int16_t)VCFKeytrack;

  SQR1LevelVal = (int16_t)(4096 - SQR1Level) / 32;
  SQR2LevelVal = (int16_t)(4096 - SQR2Level) / 32;
  SubLevelVal = (int16_t)(4096 - SubLevel) / 32;

  OSC1IntervalVal = OSC1Interval;
  OSC2IntervalVal = OSC2Interval;
  OSC2DetuneVal = OSC2Detune;

  VCALevelVal = VCALevel;

  ADSR3toDETUNE1Val = ADSR3toDETUNE1;
  ADSR3toPWMVal = ADSR3toPWM;

  LFO1toVCAVal = LFO1toVCA;

  LFO2toOSC2DETUNEVal = LFO2toOSC2DETUNE;

  LFO1toPWMVal = LFO1toPWM;
  LFO2toPWMVal = LFO2toPWM;
  LFO3toPWMVal = LFO3toPWM;

  LFO1WaveformVal = LFO1Waveform;
  LFO2WaveformVal = LFO2Waveform;
  LFO3WaveformVal = LFO3Waveform;

  oscSyncModeVal = oscSyncMode;

  /* NOT IMPLEMENTED
  ADSR1toVCA =
  ADSR1toVCF = 
  //ADSR2
  ADSR2toVCA = word(flashData[27], flashData[28]);
  ADSR2toVCF = word(flashData[29], flashData[30]);
  ADSR2toPWM = word(flashData[31], flashData[32]);
  ADSR2toDETUNE1 = word(flashData[33], flashData[34]);
  ADSR2toDETUNE2 = word(flashData[35], flashData[36]);
  //ADSR3
  ADSR3toVCA = word(flashData[37], flashData[38]);
  ADSR3toVCF = word(flashData[39], flashData[40]);
  ADSR3toDETUNE2 = word(flashData[45], flashData[46]);

  LFO1toVCFVal = expConverterReverse(LFO1toVCF, 500);
  // REVISAR !! LFO2toVCFVal = expConverterReverse(LFO2toVCF, 500);

*/
  /* --------------------------------- */


  digitalWrite(PIN_TRI, triStatus);
  digitalWrite(PIN_SIN, sineStatus);
  digitalWrite(PIN_SAW1, sawStatus);
  digitalWrite(PIN_SAW2, saw2Status);

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
