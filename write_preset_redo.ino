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