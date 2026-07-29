// Removed unused code from Serial.h

// --- from Serial.h: dead send flags, queues, unused freq ---
float freq;

bool sendDetune2Flag = false;
bool serial_send_portamentoFlag = false;
bool serial_send_oscSyncModeFlag = false;
bool serial_send_OSC1IntervalFlag = false;
bool serial_send_OSC2IntervalFlag = false;
bool serial_send_LFO1SpeedFlag = false;
bool serial_send_LFO1toDCOFlag = false;
bool serial_send_LFO1toDCOWaveChangeFlag = false;
bool serialSendADSR3toDCOFlag = false;
bool serialSendADSR3ToOscSelectFlag = false;
bool serialSendVoiceModeFlag = false;
bool serialSendUnisonDetuneFlag = false;
bool serialSendPWMPotsControlManualFlag = false;
bool serialSendLFO2ToPWMFlag = false;

// Small outgoing param queues for DCO link (used by sendSerial()).
// Named *Buf to avoid clashing with ParamId wrapper function names.
uint8_t  serialSendParamByteToDCOBuf[2];
uint16_t serialSendParamToDCOBuf[2];
