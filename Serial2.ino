// ~99 µs: flush pending ADSR3 ('s') and PW ('f') frames to DCO.
inline void sendSerial() {
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

  if (serialSendPWFlag == true) {
    if (Serial2.availableForWrite() > 1) {
      byte *b = (byte *)&PW;
      byte byteArray[3] = { (byte)'f', b[0], b[1] };
      Serial2.write(byteArray, 3);
      serialSendPWFlag = false;
    }
  }
}

// Blocking 'x' (32-bit) to Screen (e.g. gap from DCO).
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

// Immediate 'w' (8-bit) to DCO — used by many apply_param_* forwards.
inline void serialSendParamByteToDCOFunction(byte paramNumber, byte paramValue)
{
 while(Serial2.availableForWrite() < 4) {};
  byte bytesArray[4] = {(uint8_t)'w', paramNumber, paramValue, finishByte};
  Serial2.write(bytesArray, 4);
}

// Immediate 'p' (16-bit) to DCO — used by several apply_param_* forwards.
inline void serialSendParamToDCOFunction(uint8_t paramNumber, int paramValue)
{
  while(Serial2.availableForWrite() < 5) {};
  byte bytesArray[5] = {(uint8_t)'p', (uint8_t)paramNumber, highByte(paramValue), lowByte(paramValue), finishByte};
  Serial2.write(bytesArray, 5);
}

// -------------------------------------------------------------------
// ParamId-friendly overloads for outgoing parameter sends
// -------------------------------------------------------------------

// Send 32-bit param to Screen using ParamId.
inline void serialSendParam32ToScreen(ParamId id, uint32_t paramValue) {
  serialSendParam32ToScreen(static_cast<byte>(id), paramValue);
}

// Send 32-bit param to Input Controller using ParamId (over Serial8).
inline void serialSendParam32ToInput(ParamId id, uint32_t paramValue) {
  serialSendParam32ToInput(static_cast<byte>(id), paramValue);
}
