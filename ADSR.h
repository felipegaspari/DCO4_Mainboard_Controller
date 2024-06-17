#ifndef __ADSR_DCO_H__
#define __ADSR_DCO_H__

#define ADSR_1_DACSIZE 4096
#define ADSR_2_DACSIZE 4096
#define ADSR_3_DACSIZE 4096

#define ARRAY_SIZE 1024

#include <adsr_fela_bezier.h>

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

//#define ATTACK_ALPHA 0.9975			// varies between 0.9 (steep curve) and 0.9995 (straight line)
//#define ATTACK_DECAY_RELEASE 0.997          // fits to ARRAY_SIZE 1024

float ADSR1_curve1 = 0.9995f;
float ADSR1_curve2 = 0.9995f;
//float ADSR1_curve2 = 0.995;
float ADSR2_curve1 = 0.997f;
float ADSR2_curve2 = 0.997f;
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


// adsr(maxVal for example 4095, not used, not used, bool linear, attack curve, decay_release curve)
adsr adsr1_voice_0(ADSR_1_CC, ADSR1_curve1, ADSR1_curve2, false,1,2); adsr adsr2_voice_0(ADSR_2_CC, ADSR2_curve1, ADSR2_curve2,false,4,2); adsr adsr3_voice_0(ADSR_3_CC, ADSR3_curve1, ADSR3_curve2, false,0,0);
adsr adsr1_voice_1(ADSR_1_CC, ADSR1_curve1, ADSR1_curve2, false,1,2); adsr adsr2_voice_1(ADSR_2_CC, ADSR2_curve1, ADSR2_curve2,false,4,2); adsr adsr3_voice_1(ADSR_3_CC, ADSR3_curve1, ADSR3_curve2, false,0,0);
adsr adsr1_voice_2(ADSR_1_CC, ADSR1_curve1, ADSR1_curve2, false,1,2); adsr adsr2_voice_2(ADSR_2_CC, ADSR2_curve1, ADSR2_curve2,false,4,2); adsr adsr3_voice_2(ADSR_3_CC, ADSR3_curve1, ADSR3_curve2, false,0,0);
adsr adsr1_voice_3(ADSR_1_CC, ADSR1_curve1, ADSR1_curve2, false,1,2); adsr adsr2_voice_3(ADSR_2_CC, ADSR2_curve1, ADSR2_curve2,false,4,2); adsr adsr3_voice_3(ADSR_3_CC, ADSR3_curve1, ADSR3_curve2, false,0,0);

//bool OSCPhaseLock = false;

struct ADSRStruct {
adsr adsr1_voice;
adsr adsr2_voice;
adsr adsr3_voice;
};

ADSRStruct ADSRVoices[] = {
{adsr1_voice_0, adsr2_voice_0, adsr3_voice_0},
{adsr1_voice_1, adsr2_voice_1, adsr3_voice_1},
{adsr1_voice_2, adsr2_voice_2, adsr3_voice_2},
{adsr1_voice_3, adsr2_voice_3, adsr3_voice_3},
// {adsr1_voice_4, adsr2_voice_4, adsr3_voice_4},
// {adsr1_voice_5, adsr2_voice_5, adsr3_voice_5},
};
#endif
