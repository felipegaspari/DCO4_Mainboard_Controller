// Removed unused code from Serial2.ino

// --- from Serial2.ino: commented flag-based sendSerial dump + dead queues + unused helpers ---
// ~99 µs: flush pending ADSR3 ('s'), PW ('f'), and buffered 'w'/'p' frames to DCO.
// (Commented legacy flag flushes + never-filled Buf branches + unused TX helpers.)

  // if (sendDetune2Flag) { ... }
  // if (serial_send_portamentoFlag) { ... }
  // if (serial_send_oscSyncModeFlag) { ... }
  // if (serial_send_OSC1IntervalFlag) { ... }
  // if (serial_send_OSC2IntervalFlag) { ... }
  // if (serial_send_LFO1SpeedFlag) { ... }
  // if (serial_send_LFO1toDCOFlag) { ... }
  // if (serial_send_LFO1toDCOWaveChangeFlag) { ... }
  // if (serialSendADSR3toDCOFlag) { ... }
  // if (serialSendADSR3ToOscSelectFlag) { ... }
  // if (serialSendVoiceModeFlag) { ... }
  // if (serialSendUnisonDetuneFlag) { ... }
  // if (serialSendLFO2ToPWMFlag) { ... }
  // if (serialSendPWMPotsControlManualFlag) { ... }

  // if (serialSendParamByteToDCOBuf[0] > 0) { ... }
  // if (serialSendParamToDCOBuf[0] > 0) { ... }

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

inline void serialSendParamByteToScreen(byte paramNumber, byte paramValue)
{
 while(Serial1.availableForWrite() < 4) {};
  byte bytesArray[4] = {(uint8_t)'y', paramNumber, paramValue, finishByte};
  Serial1.write(bytesArray, 4);
}

inline void serial_send_param_change(ParamId id, uint16_t paramValue) {
  serial_send_param_change(static_cast<byte>(id), paramValue);
}

inline void serialSendParam32ToDCO(ParamId id, uint32_t paramValue) {
  serialSendParam32ToDCO(static_cast<byte>(id), paramValue);
}

inline void serialSendParamByteToScreen(ParamId id, byte paramValue) {
  serialSendParamByteToScreen(static_cast<byte>(id), paramValue);
}

inline void serialSendParamByteToDCO(ParamId id, byte paramValue) {
  serialSendParamByteToDCOFunction(static_cast<byte>(id), paramValue);
}

inline void serialSendParamToDCO(ParamId id, int paramValue) {
  serialSendParamToDCOFunction(static_cast<byte>(id), paramValue);
}
