void sendParams() {

  // ENABLE IF DETUNE1 is serial
  // DETUNE1 = ((float)LFO1Level * LFO1toDCO_formula) + ((float)ADSR3Level[0] * ADSR3toDETUNE1_formula) + 1 /* + RANDOMNESS1*/;
  // if (DETUNE1 < 0) {
  //   DETUNE1 = 0;
  // }
  DETUNE2 = (uint8_t)((float)(LFO2Level + LFO2_CC_HALF) / 4096 * LFO2toOSC2DETUNE) + OSC2Detune;
  //DETUNE1 = 2.00f;
  //DETUNE2 = 127;

  byte *b = (byte *)&DETUNE1;
  byte dataArray[5];
  byte ndata = 0;

  dataArray[0] = b[0];
  dataArray[1] = b[1];
  dataArray[2] = b[2];
  dataArray[3] = b[3];
  dataArray[4] = (uint8_t)DETUNE2;

  if (Serial2.availableForWrite() > 5) {
    Serial2.write((char *)"p");
    Serial2.write(dataArray, 5);
  }
}

void sendSerial() {
  // if (sendDetune2Flag) {
  //   if (Serial2.availableForWrite() > 1) {
  //     DETUNE2 = (uint8_t)((float)(LFO2Level + LFO2_CC_HALF) / 4096 * LFO2toOSC2DETUNE) + OSC2Detune;
  //     byte byteArray[2] = { (uint8_t)'q', (uint8_t)DETUNE2 };
  //     Serial2.write(byteArray, 2);
  //     sendDetune2Flag = false;
  //   }
  // }

  // if (serial_send_portamentoFlag) {
  //   if (Serial2.availableForWrite() > 1) {
  //     byte byteArray[2] = { (uint8_t)'r', portamentoTime };
  //     Serial2.write(byteArray, 2);
  //     serial_send_portamentoFlag = false;
  //   }
  // }

  // if (serial_send_oscSyncModeFlag) {
  //   if (Serial2.availableForWrite() > 1) {
  //     byte byteArray[2] = { (uint8_t)'t', oscSyncMode };
  //     Serial2.write(byteArray, 2);
  //     serial_send_oscSyncModeFlag = false;
  //   }
  // }

  // if (serial_send_OSC1IntervalFlag) {
  //   if (Serial2.availableForWrite() > 1) {
  //     byte byteArray[2] = { (uint8_t)'y', OSC1Interval };
  //     Serial2.write(byteArray, 2);
  //     serial_send_OSC1IntervalFlag = false;
  //   }
  // }

  // if (serial_send_OSC2IntervalFlag) {
  //   if (Serial2.availableForWrite() > 1) {
  //     byte byteArray[2] = { (uint8_t)'z', OSC2Interval };
  //     Serial2.write(byteArray, 2);
  //     serial_send_OSC2IntervalFlag = false;
  //   }
  // }

  // if (serial_send_LFO1SpeedFlag) {
  //   if (Serial2.availableForWrite() > 2) {
  //     byte *b = (byte *)&LFO1SpeedVal;
  //     byte byteArray[3] = { (byte)'l', b[0], b[1] };
  //     Serial2.write(byteArray, 3);
  //     serial_send_LFO1SpeedFlag = false;
  //   }
  // }

  // if (serial_send_LFO1toDCOFlag) {
  //   if (Serial2.availableForWrite() > 2) {
  //     byte *b = (byte *)&LFO1toDCOVal;
  //     byte byteArray[3] = { (byte)'m', b[0], b[1] };
  //     Serial2.write(byteArray, 3);
  //     serial_send_LFO1toDCOFlag = false;
  //   }
  // }

  // if (serial_send_LFO1toDCOWaveChangeFlag) {
  //   if (Serial2.availableForWrite() > 1) {
  //     byte byteArray[2] = { (uint8_t)'b', LFO1Waveform };
  //     Serial2.write(byteArray, 2);
  //     serial_send_LFO1toDCOWaveChangeFlag = false;
  //   }
  // }

  if (serialSendADSR3ControlValuesFlag == true) {
    if (Serial2.availableForWrite() > 4) {
      byte ADSR3BytesArray[5];
      ADSR3BytesArray[0] = (byte)'s';
      ADSR3BytesArray[1] = (byte)(ADSR3_attack / 16);
      ADSR3BytesArray[2] = (byte)(ADSR3_decay / 16);
      ADSR3BytesArray[3] = (byte)(ADSR3_sustain / 16);
      ADSR3BytesArray[4] = (byte)(ADSR3_release / 16);
      //Serial2.write((char *)"s");
      Serial2.write(ADSR3BytesArray, 5);
      serialSendADSR3ControlValuesFlag = false;
    }
  }

  // if (serialSendADSR3toDCOFlag) {
  //   if (Serial2.availableForWrite() > 2) {
  //     byte *b = (byte *)&ADSR3toDETUNE1;
  //     byte byteArray[3] = { (byte)'w', b[0], b[1] };
  //     Serial2.write(byteArray, 3);
  //     serialSendADSR3toDCOFlag = false;
  //   }
  // }
  // if (serialSendADSR3ToOscSelectFlag) {
  //   if (Serial2.availableForWrite() > 1) {
  //     byte byteArray[2] = { (byte)'c', ADSR3ToOscSelect };
  //     Serial2.write(byteArray, 2);
  //     serialSendADSR3ToOscSelectFlag = false;
  //   }
  // }
  // if (serialSendVoiceModeFlag) {
  //   if (Serial2.availableForWrite() > 1) {
  //     byte byteArray[2] = { (byte)'d', voiceMode };
  //     Serial2.write(byteArray, 2);
  //     serialSendVoiceModeFlag = false;
  //   }
  // }
  // if (serialSendUnisonDetuneFlag) {
  //   if (Serial2.availableForWrite() > 1) {
  //     byte byteArray[2] = { (byte)'e', (uint8_t)unisonDetune };
  //     Serial2.write(byteArray, 2);
  //     serialSendUnisonDetuneFlag = false;
  //   }
  // }
  if (serialSendPWFlag == true) {
    if (Serial2.availableForWrite() > 1) {
      byte *b = (byte *)&PW;
      byte byteArray[3] = { (byte)'f', b[0], b[1] };
      Serial2.write(byteArray, 3);
      serialSendPWFlag = false;
    }
  }
  // if (serialSendLFO2ToPWMFlag) {
  //   if (Serial2.availableForWrite() > 1) {
  //     byte *b = (byte *)&LFO2toPWM;
  //     byte byteArray[3] = { (byte)'h', b[0], b[1] };
  //     Serial2.write(byteArray, 3);
  //     serialSendLFO2ToPWMFlag = false;
  //   }
  // }
  // if (serialSendPWMPotsControlManualFlag) {
  //   if (Serial2.availableForWrite() > 1) {
  //     byte byteArray[2] = { (byte)'j', (uint8_t)PWMPotsControlManual };
  //     Serial2.write(byteArray, 2);
  //     serialSendPWMPotsControlManualFlag = false;
  //   }
  // }

  if (serialSendParamByteToDCO[0] > 0) {
    byte bytesArray[4] = { (uint8_t)'w', serialSendParamByteToDCO[0], serialSendParamByteToDCO[1], finishByte };
    Serial2.write(bytesArray, 4);

    serialSendParamByteToDCO[0] = 0;
    serialSendParamByteToDCO[1] = 0;
  }

  if (serialSendParamToDCO[0] > 0) {
    byte bytesArray[5] = { (uint8_t)'p', (uint8_t)serialSendParamToDCO[0], highByte(serialSendParamToDCO[1]), lowByte(serialSendParamToDCO[1]), finishByte };
    Serial2.write(bytesArray, 5);

    serialSendParamToDCO[0] = 0;
  }
}

void serial_send_param_change(byte param, uint16_t paramValue) {

  byte bytesArray[5] = { (uint8_t)'p', param, highByte(paramValue), lowByte(paramValue), finishByte };
#ifdef ENABLE_SERIAL1
  while (Serial1.availableForWrite() < 5) {}
  Serial1.write(bytesArray, 5);
#endif
}

void serialSendParam32ToDCO(byte paramNumber, uint32_t paramValue) {

uint8_t *b = (uint8_t *)&paramValue;

  byte bytesArray[7] = { (uint8_t)'x', paramNumber, b[0], b[1], b[2], b[3], finishByte };
  while (Serial2.availableForWrite() < 7) {}
  Serial2.write(bytesArray, 7);
}

void serialSendParam32ToScreen(byte paramNumber, uint32_t paramValue) {

uint8_t *b = (uint8_t *)&paramValue;

  byte bytesArray[7] = { (uint8_t)'x', paramNumber, b[0], b[1], b[2], b[3], finishByte };
  while (Serial1.availableForWrite() < 7) {}
  Serial1.write(bytesArray, 7);
}

void serialSendParamByteToDCOFunction(byte paramNumber, byte paramValue)
{
 while(Serial2.availableForWrite() < 4) {};
  byte bytesArray[4] = {(uint8_t)'w', paramNumber, paramValue, finishByte};
  Serial2.write(bytesArray, 4);
}

void serialSendParamToDCOFunction(uint8_t paramNumber, int paramValue)
{
  while(Serial2.availableForWrite() < 5) {};
  byte bytesArray[5] = {(uint8_t)'p', (uint8_t)paramNumber, highByte(paramValue), lowByte(paramValue), finishByte};
  Serial2.write(bytesArray, 5);
}