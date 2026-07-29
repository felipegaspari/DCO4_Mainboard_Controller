// Removed unused code from LFO.h

// --- orphan LFO3 / unused mod-amount globals + void LFO3() ---
static constexpr uint16_t LF01_CC_THIRD = LFO1_CC / 3;
static constexpr uint16_t LFO3_CC = 4095;
static constexpr uint16_t LFO3_CC_HALF = LFO2_CC / 2;

uint16_t LFO1toPWM;
uint16_t LFO1toDETUNE1;
uint16_t LFO1toDETUNE2;
uint16_t LFO2toVCA;
uint16_t LFO2toDETUNE1;

int16_t LFO3Level;
byte     LFO3Waveform;
float    LFO3Speed;
uint16_t LFO3toVCF;
uint16_t LFO3toVCA;
uint16_t LFO3toPWM;
float    LFO3toDCO;
uint16_t LFO3toDETUNE1;
uint16_t LFO3toDETUNE2;
uint16_t LFO3toSQR1;
uint16_t LFO3toSQR2;
uint16_t LFO3toSUB;

void LFO3();
float LFO2toDCO;
