inline void sendSerial() {
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
      byte dataArray[9];

    dataArray[0] = (uint8_t)'s';
    dataArray[1] = highByte(ADSR3_attack);
    dataArray[2] = lowByte(ADSR3_attack);
    dataArray[3] = highByte(ADSR3_decay);
    dataArray[4] = lowByte(ADSR3_decay);
    dataArray[5] = highByte(ADSR3_sustain);
    dataArray[6] = lowByte(ADSR3_sustain);
    dataArray[7] = highByte(ADSR3_release);
    dataArray[8] = lowByte(ADSR3_release);

    Serial2.write(dataArray, 9);
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

  if (serialSendParamByteToDCOBuf[0] > 0) {
    byte bytesArray[4] = { (uint8_t)'w', serialSendParamByteToDCOBuf[0], serialSendParamByteToDCOBuf[1], finishByte };
    Serial2.write(bytesArray, 4);

    serialSendParamByteToDCOBuf[0] = 0;
    serialSendParamByteToDCOBuf[1] = 0;
  }

  if (serialSendParamToDCOBuf[0] > 0) {
    byte bytesArray[5] = { (uint8_t)'p', (uint8_t)serialSendParamToDCOBuf[0], highByte(serialSendParamToDCOBuf[1]), lowByte(serialSendParamToDCOBuf[1]), finishByte };
    Serial2.write(bytesArray, 5);

    serialSendParamToDCOBuf[0] = 0;
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

// Send 32-bit param to the input controller over Serial8 (mainboard side).
void serialSendParam32ToInput(byte paramNumber, uint32_t paramValue) {
  uint8_t *b = (uint8_t *)&paramValue;
  byte bytesArray[7] = { (uint8_t)'x', paramNumber, b[0], b[1], b[2], b[3], finishByte };
#ifdef ENABLE_SERIAL8
  while (Serial8.availableForWrite() < 7) {}
  Serial8.write(bytesArray, 7);
#endif
}

inline void serialSendParamByteToScreen(byte paramNumber, byte paramValue)
{
 while(Serial1.availableForWrite() < 4) {};
  byte bytesArray[4] = {(uint8_t)'y', paramNumber, paramValue, finishByte};
  Serial1.write(bytesArray, 4);
}

inline void serialSendParamByteToDCOFunction(byte paramNumber, byte paramValue)
{
 while(Serial2.availableForWrite() < 4) {};
  byte bytesArray[4] = {(uint8_t)'w', paramNumber, paramValue, finishByte};
  Serial2.write(bytesArray, 4);
}

inline void serialSendParamToDCOFunction(uint8_t paramNumber, int paramValue)
{
  while(Serial2.availableForWrite() < 5) {};
  byte bytesArray[5] = {(uint8_t)'p', (uint8_t)paramNumber, highByte(paramValue), lowByte(paramValue), finishByte};
  Serial2.write(bytesArray, 5);
}

// -------------------------------------------------------------------
// ParamId-friendly overloads for outgoing parameter sends
// -------------------------------------------------------------------

// Send 16-bit param to screen using ParamId.
inline void serial_send_param_change(ParamId id, uint16_t paramValue) {
  serial_send_param_change(static_cast<byte>(id), paramValue);
}

// Send 32-bit param to DCO using ParamId.
inline void serialSendParam32ToDCO(ParamId id, uint32_t paramValue) {
  serialSendParam32ToDCO(static_cast<byte>(id), paramValue);
}

// Send 32-bit param to Screen using ParamId.
inline void serialSendParam32ToScreen(ParamId id, uint32_t paramValue) {
  serialSendParam32ToScreen(static_cast<byte>(id), paramValue);
}

// Send 32-bit param to Input Controller using ParamId (over Serial8).
inline void serialSendParam32ToInput(ParamId id, uint32_t paramValue) {
  serialSendParam32ToInput(static_cast<byte>(id), paramValue);
}

// Send 8-bit param to Screen using ParamId.
inline void serialSendParamByteToScreen(ParamId id, byte paramValue) {
  serialSendParamByteToScreen(static_cast<byte>(id), paramValue);
}

// Send 8-bit param to DCO using ParamId.
inline void serialSendParamByteToDCO(ParamId id, byte paramValue) {
  serialSendParamByteToDCOFunction(static_cast<byte>(id), paramValue);
}

// Send 16-bit param to DCO using ParamId.
inline void serialSendParamToDCO(ParamId id, int paramValue) {
  serialSendParamToDCOFunction(static_cast<byte>(id), paramValue);
}