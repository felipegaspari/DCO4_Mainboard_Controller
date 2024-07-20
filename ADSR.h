#ifndef __ADSR_DCO_H__
#define __ADSR_DCO_H__

#define ADSR_1_DACSIZE 4096
#define ADSR_2_DACSIZE 4096
#define ADSR_3_DACSIZE 4096

#define ARRAY_SIZE 4096

// struct Point {
//   float x, y;
// };


int _curve0_table[ARRAY_SIZE];
int _curve1_table[ARRAY_SIZE];
int _curve2_table[ARRAY_SIZE];
int _curve3_table[ARRAY_SIZE];
int _curve4_table[ARRAY_SIZE];
int _curve5_table[ARRAY_SIZE];
int _curve6_table[ARRAY_SIZE];
int _curve7_table[ARRAY_SIZE];
int *_curve_tables[8] = { _curve0_table, _curve1_table, _curve2_table, _curve3_table, _curve4_table, _curve5_table, _curve6_table, _curve7_table };

#include <adsr_fela_bezier.h>

void adsrCreateTables(float maxVal, int numPoints) {

  Point A = { 0, maxVal };  // Punto inicial
  Point B = { maxVal, 0 };
  Point P1[8] = { { 250, 1500 }, { 840, 1780 }, { 400, 430 }, { 2170, 3610 }, { 400, 1380 }, { 1140, 3750 }, { 200, 2700 }, { 0, 4095 } };
  Point P2[8] = { { 1500, 250 }, { 1160, 210 }, { 920, 420 }, { 3730, 2610 }, { 3830, 2890 }, { 1850, 1080 }, { 720, 3050 }, { 4095, 0 } };

  for (int j = 0; j < 8; j++) {

    float multiplier = (float)(maxVal + 1) / (float)(numPoints - 1);

    // Imprimir los puntos de la curva
    for (float i = 0; i < numPoints; i++) {
      float xTarget = multiplier * i;
      float yResult = findYForX(A, P1[j], P2[j], B, xTarget);

      _curve_tables[j][(int)i] = (int)round(yResult);
    }
  }
}


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


uint8_t ADSR1AttackCurveVal;
uint8_t ADSR1DecayCurveVal;
uint8_t ADSR2AttackCurveVal;
uint8_t ADSR2DecayCurveVal;

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
adsr adsr1_voice_0(ADSR_1_CC, ADSR1_curve1, ADSR1_curve2, false,1,2,1); adsr adsr2_voice_0(ADSR_2_CC, ADSR2_curve1, ADSR2_curve2,false,4,6,1); adsr adsr3_voice_0(ADSR_3_CC, ADSR3_curve1, ADSR3_curve2, false,0,0,1);
adsr adsr1_voice_1(ADSR_1_CC, ADSR1_curve1, ADSR1_curve2, false,1,2,1); adsr adsr2_voice_1(ADSR_2_CC, ADSR2_curve1, ADSR2_curve2,false,4,6,1); adsr adsr3_voice_1(ADSR_3_CC, ADSR3_curve1, ADSR3_curve2, false,0,0,1);
adsr adsr1_voice_2(ADSR_1_CC, ADSR1_curve1, ADSR1_curve2, false,1,2,1); adsr adsr2_voice_2(ADSR_2_CC, ADSR2_curve1, ADSR2_curve2,false,4,6,1); adsr adsr3_voice_2(ADSR_3_CC, ADSR3_curve1, ADSR3_curve2, false,0,0,1);
adsr adsr1_voice_3(ADSR_1_CC, ADSR1_curve1, ADSR1_curve2, false,1,2,1); adsr adsr2_voice_3(ADSR_2_CC, ADSR2_curve1, ADSR2_curve2,false,4,6,1); adsr adsr3_voice_3(ADSR_3_CC, ADSR3_curve1, ADSR3_curve2, false,0,0,1);

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
