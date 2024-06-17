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
  PWMPotsControlManual = bitRead(flashData[1], 1);  // makes no sense, should be off after loading or writing presets
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

  unisonDetune = flashData[16];
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
  unused_data_uint16_t = word(flashData[38], flashData[39]);
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
  /////////////////// START NEW STUFF //
  update_waveSelector(4);  // 4 = Update All
                           // RESONANCEAmpCompensation
  ADSR1_set_restart();     // VCAADSRRestart

  ADSR2_set_restart();  // VCFADSRRestart

  // ADSR3Enabled
  serialSendParamByteToDCOFunction(124, 0);  // PWM control Manual off after loading

  LFO1_class.setWaveForm(LFO1Waveform);  // LFO1Waveform
  serialSendParamByteToDCOFunction(11, LFO1Waveform);

  LFO2_class.setWaveForm(LFO2Waveform);  // LFO2Waveform
  serialSendParamByteToDCOFunction(12, LFO2Waveform);

  serialSendParamByteToDCOFunction(13, OSC1Interval);

  serialSendParamByteToDCOFunction(14, OSC2Interval);

  serialSendParamByteToDCOFunction(17, oscSyncMode);

  serialSendParamByteToDCOFunction(18, portamentoTime);

  serialSendParamByteToDCOFunction(26, voiceMode);

  serialSendParamByteToDCOFunction(10, ADSR3ToOscSelect);

  velocityToVCF = velocityToVCFVal * 0.0003935;

  velocityToVCA = velocityToVCAVal * 0.0003935;

  serialSendParamByteToDCOFunction(27, unisonDetune);  //  unisonDetune

  //// int16_t

  // VCFKeytrack // formula_update(1);

  SQR1Level = lin_to_log_128[SQR1LevelVal];  // SQR1LevelVal  // mcpUpdate();

  SQR2Level = lin_to_log_128[SQR2LevelVal];  // SQR2LevelVal  // mcpUpdate();

  SubLevel = constrain((SubLevelVal * 32), 0, 4095);  // SubLevelVal  // mcpUpdate();

  serialSendParamToDCOFunction(40, LFO1toDCOVal);  // LFO1toDCOVal  // controls_formula_update(3);

  serialSendParamToDCOFunction(41, LFO1SpeedVal);  // LFO1SpeedVal  // controls_formula_update(1);

  serialSendParamToDCOFunction(42, LFO2SpeedVal);  // LFO2SpeedVal  // controls_formula_update(2);

  serialSendParamToDCOFunction(46, ADSR3toPWM - 512);  // ADSR3toPWM

  serialSendParamToDCOFunction(47, ADSR3toDETUNE1);  // ADSR3toDETUNE1

  serialSendParamToDCOFunction(15, OSC2Detune);  // OSC2Detune

  serialSendParamToDCOFunction(16, LFO2toOSC2DETUNE);  // LFO2toOSC2DETUNE

  // VCALevel // VCALevel = paramValue * 32;

  // LFO1toVCA

  serialSendParamToDCOFunction(45, LFO2toPWM);  // LFO2toPWM // formula_update(11);


  // CUTOFF                   ------  PARAM GROUP VCF
  // RESONANCE                ------  PARAM GROUP VCF
  // ADSR2toVCF               ------  PARAM GROUP VCF
  // LFO2toVCF                ------  PARAM GROUP VCF
  // formula_update(4);       ------  PARAM GROUP VCF
  // formula_update(2);       ------  PARAM GROUP VCF

  // ADSR1toVCA
  // PW

  //  ADSR1_attack
  //  ADSR1_decay
  //  ADSR1_sustain
  //  ADSR1_release

  //  ADSR2_attack
  //  ADSR2_decay
  //  ADSR2_sustain
  //  ADSR2_release

  //  ADSR3_attack
  //  ADSR3_decay
  //  ADSR3_sustain
  //  ADSR3_release

  serialSendADSR3ControlValuesFlag == true;
  serialSendPWFlag = true;

  sendSerial();

  controls_formula_update(1);  // LFO1Speed
  controls_formula_update(2);  // LFO2Speed

  formula_update(1);  // VCFKeytrack
  formula_update(2);  // ADSR2toVCF_formula
  formula_update(4);  // LFO2toVCF_formula
  formula_update(8);  // ADSR1toVCA_formula

  mcpUpdate();

  //////////////// END NEW STUFF

  presetNameString = String((char *)presetName);

  currentPreset = presetN;
  presetSelectVal = currentPreset;

  serial_send_preset_scroll(currentPreset, presetName);
}

void get_preset_name(byte presetN, byte (&myarray)[12]) {
#ifdef ENABLE_SD
  uint16_t startByteN = presetN * flashPresetSize;
  for (int i = 0; i < 12; i++) {
    myarray[i] = presetBank1Buffer[startByteN + 119 + i];
  }
#endif
}

void writePreset(uint16_t presetN)
{

    uint16_t startByteN = presetN * flashPresetSize;
    byte *b;


    // bits
    bitWrite(flashData[0], 0, sawStatus);
    bitWrite(flashData[0], 1, saw2Status);
    bitWrite(flashData[0], 2, triStatus);
    bitWrite(flashData[0], 3, sineStatus);
    bitWrite(flashData[0], 4, sqr1Status);
    bitWrite(flashData[0], 5, sqr2Status);
    bitWrite(flashData[0], 6, RESONANCEAmpCompensation);
    bitWrite(flashData[0], 7, VCAADSRRestart);

    bitWrite(flashData[1], 0, VCFADSRRestart);
    bitWrite(flashData[1], 1, PWMPotsControlManual);
    bitWrite(flashData[1], 2, ADSR3Enabled);
    bitWrite(flashData[1], 3, 0);
    bitWrite(flashData[1], 4, 0);
    bitWrite(flashData[1], 5, 0);
    bitWrite(flashData[1], 6, 0);
    bitWrite(flashData[1], 7, 0);
    flashData[2] = 0;
    flashData[3] = 0;
    flashData[4] = 0;
    flashData[5] = 0;
    // bytes
    flashData[6] = LFO1Waveform;
    flashData[7] = LFO2Waveform;
    flashData[8] = OSC1Interval;
    flashData[9] = OSC2Interval;
    flashData[10] = oscSyncMode;
    flashData[11] = portamentoTime;
    flashData[12] = voiceMode;
    // int8_t
    flashData[13] = (byte)ADSR3ToOscSelect;
    flashData[14] = (byte)velocityToVCFVal;
    flashData[15] = (byte)velocityToVCAVal;
    flashData[16] = (byte)unisonDetune;
    flashData[17] = 0;
    flashData[18] = 0;
    flashData[19] = 0;
    flashData[20] = 0;
    flashData[21] = 0;
    flashData[22] = 0;
    flashData[23] = 0;
    flashData[24] = 0;
    flashData[25] = 0;
    flashData[26] = 0;
    flashData[27] = 0;
    flashData[28] = 0;
    flashData[29] = 0;
    // int16_t
    flashData[30] = highByte(VCFKeytrack);
    flashData[31] = lowByte(VCFKeytrack);
    flashData[32] = highByte(SQR1LevelVal);
    flashData[33] = lowByte(SQR1LevelVal);
    flashData[34] = highByte(SQR2LevelVal);
    flashData[35] = lowByte(SQR2LevelVal);
    flashData[36] = highByte(SubLevelVal);
    flashData[37] = lowByte(SubLevelVal);
    flashData[38] = highByte(0);
    flashData[39] = lowByte(0);
    flashData[40] = highByte(LFO1toDCOVal);
    flashData[41] = lowByte(LFO1toDCOVal);
    flashData[42] = highByte(LFO1SpeedVal);
    flashData[43] = lowByte(LFO1SpeedVal);
    flashData[44] = highByte(LFO2SpeedVal);
    flashData[45] = lowByte(LFO2SpeedVal);
    flashData[46] = highByte(ADSR3toPWM);
    flashData[47] = lowByte(ADSR3toPWM);
    flashData[48] = highByte(ADSR3toDETUNE1);
    flashData[49] = lowByte(ADSR3toDETUNE1);
    flashData[50] = 0;
    flashData[51] = 0;
    flashData[52] = 0;
    flashData[53] = 0;
    flashData[54] = 0;
    flashData[55] = 0;
    flashData[56] = 0;
    flashData[57] = 0;
    flashData[58] = 0;
    flashData[59] = 0;
    flashData[60] = 0;
    flashData[61] = 0;

    // uint16_t
    flashData[62] = highByte(OSC2Detune);
    flashData[63] = lowByte(OSC2Detune);
    flashData[64] = highByte(LFO2toOSC2DETUNE);
    flashData[65] = lowByte(LFO2toOSC2DETUNE);
    flashData[66] = highByte(VCALevel);
    flashData[67] = lowByte(VCALevel);
    flashData[68] = highByte(LFO1toVCA);
    flashData[69] = lowByte(LFO1toVCA);
    flashData[70] = highByte(LFO2toPWM);
    flashData[71] = lowByte(LFO2toPWM);

    flashData[72] = highByte(0);
    flashData[73] = lowByte(0);

    flashData[74] = highByte(CUTOFF);
    flashData[75] = lowByte(CUTOFF);
    flashData[76] = highByte(RESONANCE);
    flashData[77] = lowByte(RESONANCE);
    flashData[78] = highByte(ADSR2toVCF);
    flashData[79] = lowByte(ADSR2toVCF);
    flashData[80] = highByte(LFO2toVCF);
    flashData[81] = lowByte(LFO2toVCF);
    flashData[82] = highByte(ADSR1toVCA);
    flashData[83] = lowByte(ADSR1toVCA);
    flashData[84] = highByte(PW);
    flashData[85] = lowByte(PW);
    flashData[86] = highByte(0);
    flashData[87] = lowByte(0);
    flashData[88] = highByte(ADSR1_attack);
    flashData[89] = lowByte(ADSR1_attack);
    flashData[90] = highByte(ADSR1_decay);
    flashData[91] = lowByte(ADSR1_decay);
    flashData[92] = highByte(ADSR1_sustain);
    flashData[93] = lowByte(ADSR1_sustain);
    flashData[94] = highByte(ADSR1_release);
    flashData[95] = lowByte(ADSR1_release);
    flashData[96] = highByte(ADSR2_attack);
    flashData[97] = lowByte(ADSR2_attack);
    flashData[98] = highByte(ADSR2_decay);
    flashData[99] = lowByte(ADSR2_decay);
    flashData[100] = highByte(ADSR2_sustain);
    flashData[101] = lowByte(ADSR2_sustain);
    flashData[102] = highByte(ADSR2_release);
    flashData[103] = lowByte(ADSR2_release);
    flashData[104] = highByte(ADSR3_attack);
    flashData[105] = lowByte(ADSR3_attack);
    flashData[106] = highByte(ADSR3_decay);
    flashData[107] = lowByte(ADSR3_decay);
    flashData[108] = highByte(ADSR3_sustain);
    flashData[109] = lowByte(ADSR3_sustain);
    flashData[110] = highByte(ADSR3_release);
    flashData[111] = lowByte(ADSR3_release);
    flashData[112] = highByte(0);
    flashData[113] = lowByte(0);
    flashData[114] = highByte(0);
    flashData[115] = lowByte(0);
    flashData[116] = highByte(0);
    flashData[117] = lowByte(0);

    flashData[118] = 0;

///
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

    // byte noiseLevel;
    // uint16_t aftertouch;

#ifdef ENABLE_SD
    for (int i = 0; i < flashPresetSize; i++)
    {
        presetBank1Buffer[i + startByteN] = flashData[i];
    }
    fileBank1 = SD.open("presetBank1", FILE_WRITE);
    fileBank1.seek(startByteN);
    fileBank1.write(flashData, flashPresetSize);
    fileBank1.close();

#else

    for (int i = 0; i < flashPresetSize; i++)
    {
        eeprom_buffered_write_byte(i + startByteN, flashData[i]);
    }
    eeprom_buffer_flush();

#endif

    presetSave = false;
    presetSaved = true;

    currentPreset = presetN;
    presetSelectVal = currentPreset;
}


/*
/*
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
  flashData[2void writePreset(uint16_t presetN) {

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

  // ADSR18] = lowByte(ADSR2toVCA);
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
*/
//*/

/*
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


  //*********************************************************************************


  velocityToVCF = velocityToVCFVal * 0.0005;
  velocityToVCA = velocityToVCAVal * 0.0005;
  //velocityToPWM =



  //*   Move parameters to encoder variables *
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

  // // NOT IMPLEMENTED
  // ADSR1toVCA =
  // ADSR1toVCF = 
  // //ADSR2
  // ADSR2toVCA = word(flashData[27], flashData[28]);
  // ADSR2toVCF = word(flashData[29], flashData[30]);
  // ADSR2toPWM = word(flashData[31], flashData[32]);
  // ADSR2toDETUNE1 = word(flashData[33], flashData[34]);
  // ADSR2toDETUNE2 = word(flashData[35], flashData[36]);
  // //ADSR3
  // ADSR3toVCA = word(flashData[37], flashData[38]);
  // ADSR3toVCF = word(flashData[39], flashData[40]);
  // ADSR3toDETUNE2 = word(flashData[45], flashData[46]);

  // LFO1toVCFVal = expConverterReverse(LFO1toVCF, 500);
  // // REVISAR !! LFO2toVCFVal = expConverterReverse(LFO2toVCF, 500);


  // * --------------------------------- 


  // digitalWrite(PIN_TRI, triStatus);
  // digitalWrite(PIN_SIN, sineStatus);
  // digitalWrite(PIN_SAW1, sawStatus);
  // digitalWrite(PIN_SAW2, saw2Status);

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
*/