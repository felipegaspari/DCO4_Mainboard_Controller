// Removed unused code from ADSR.h

// --- unused ADSR level/curve/mod-amount globals (never read on Mainboard CV path) ---
float ADSRMaxLevel = ADSR_1_CC;
uint16_t ADSRMinLevel = 0;
byte ADSR1_curve2Val = 0;
byte ADSR2_curve2Val = 0;

int16_t ADSR1toVCF;
int16_t ADSR1toPWM;
int16_t ADSR1toDETUNE1;
int16_t ADSR1toDETUNE2;

int16_t ADSR2toVCA;
int16_t ADSR2toPWM;
int16_t ADSR2toDETUNE1;
int16_t ADSR2toDETUNE2;

int16_t ADSR3toVCA;
int16_t ADSR3toVCF;
int16_t ADSR3toDETUNE2;

int16_t ADSR3toSQR1;
int16_t ADSR3toSQR2;
int16_t ADSR3toSUB;
