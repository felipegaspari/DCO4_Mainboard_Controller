#ifndef __ADSR_H__
#define __ADSR_H__

#define ADSR_1_DACSIZE 4095
#define ADSR_2_DACSIZE 4095
#define ADSR_3_DACSIZE 4095

static const uint16_t ADSR_1_CC = 4095;
static const uint16_t ADSR_2_CC = 4095;
static const uint16_t ADSR_3_CC = 4095;

float ADSRMaxLevel = ADSR_1_CC;

uint16_t ADSRMinLevel = 0;

uint16_t ADSR1_attack;
uint16_t ADSR1_decay;
uint16_t ADSR1_sustain;
uint16_t ADSR1_release;
uint16_t ADSR2_attack;
uint16_t ADSR2_decay;
uint16_t ADSR2_sustain;
uint16_t ADSR2_release;
uint16_t ADSR3_attack;
uint16_t ADSR3_decay;           
uint16_t ADSR3_sustain;         
uint16_t ADSR3_release;

byte ADSR1_curve2Val = 0;
byte ADSR2_curve2Val = 0;

float ADSR1_curve1 = 0.999;
float ADSR1_curve2 = 0.997;
//float ADSR1_curve2 = 0.995;
float ADSR2_curve1 = 0.999f;
float ADSR2_curve2 = 0.9985f;
float ADSR3_curve1 = 0.997;
float ADSR3_curve2 = 0.997;

unsigned long tADSR;
unsigned long tADSR_params;

uint16_t ADSR1Level[NUM_VOICES];
uint16_t ADSR2Level[NUM_VOICES];
uint16_t ADSR3Level[NUM_VOICES];

int16_t ADSR1toVCA;
int16_t ADSR1toVCF;
int16_t ADSR1toPWM;
int16_t ADSR1toDETUNE1;
int16_t ADSR1toDETUNE2;

int16_t ADSR2toVCA;
int16_t ADSR2toVCF;
int16_t ADSR2toPWM;
int16_t ADSR2toDETUNE1;
int16_t ADSR2toDETUNE2;

int16_t ADSR3toVCA;
int16_t ADSR3toVCF;
int16_t ADSR3toPWM;
int16_t ADSR3toDETUNE1;
int16_t ADSR3toDETUNE2;

int16_t ADSR3toSQR1;
int16_t ADSR3toSQR2;
int16_t ADSR3toSUB;

adsr adsr1_voice_0(ADSR_1_CC, ADSR1_curve1, ADSR1_curve2); adsr adsr2_voice_0(ADSR_2_DACSIZE, ADSR2_curve1, ADSR2_curve2); 


//bool OSCPhaseLock = false;

struct ADSRStruct {
adsr adsr1_voice;
adsr adsr2_voice;
};

ADSRStruct ADSRVoices[] = {
{adsr1_voice_0, adsr2_voice_0},

// {adsr1_voice_4, adsr2_voice_4, adsr3_voice_4},
// {adsr1_voice_5, adsr2_voice_5, adsr3_voice_5},
};
#endif
