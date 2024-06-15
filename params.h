#ifndef __PARAMS_H__
#define __PARAMS_H__

bool noteStart[NUM_VOICES];
bool noteEnd[NUM_VOICES];
byte velocity[NUM_VOICES];
byte note[NUM_VOICES];

byte currentVoice = 0;

byte noiseLevel = 0;

bool sineStatus = 0;
bool triStatus = 0;
bool sawStatus = 0;
bool saw2Status = 0;
bool sqr1Status = 0;
bool sqr2Status = 0;
bool SUBStatus = 1;

byte waveStatus;

// control variables
byte faderRow1Mode = 0;
bool faderRow1ControlManual = false;

byte faderRow2Mode = 0;
bool faderRow2ControlManual = false;

byte VCFPots = 0;
bool VCFPotsControlManual = false;

byte VCAPots = 0;
bool VCAPotsControlManual = false;

byte PWMPots = 0;
bool PWMPotsControlManual = false;

bool allControlsManual = false;

bool ADSR3Enabled = false;

bool presetSelect = false;
bool presetSave = false;
bool presetSaved = true;

uint8_t presetSelectVal = 0;
byte presetChar = 0;
byte charSelectVal = 0;

byte presetNameVal[17] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32 };
byte loadedName[17];

bool funcKeyOn = false;

// encoder values

int16_t VCFKeytrackVal;

int16_t SQR1LevelVal;
int16_t SQR2LevelVal;
int16_t SubLevelVal;

int16_t unisonDetune;

int16_t VCALevelVal;


int8_t velocityToVCFVal = 0;
int8_t velocityToVCAVal = 0;
int8_t velocityToPWMVal = 0;

int16_t LFO1toDCOVal;
int16_t LFO2toDCOVal;
int16_t LFO3toDCOVal;

int16_t LFO1toVCAVal;

int16_t LFO1SpeedVal;
int16_t LFO2SpeedVal;
int16_t LFO3SpeedVal;

int16_t LFO1toVCFVal;
int16_t LFO2toVCFVal;
int16_t LFO3toVCFVal;

int8_t ADSR3ToOscSelect;

int16_t calibrationVal;
bool calibrationMode = false;
//

float velocityToVCF = 0;
float velocityToVCA = 0;
float velocityToPWM = 0;

uint16_t aftertouch = 0;
byte portamentoTime = 0;
byte portamentoMode = 0;

volatile float VCAResonanceCompensation = 0;
bool RESONANCEAmpCompensation = true;

bool VCFADSRRestart = true;
bool VCAADSRRestart = true;

byte VCFKeytrack = 0;
float VCFKeytrackModifier = 1;
float VCFKeytrackPerVoice[NUM_VOICES];
byte oscSyncMode = 0;
byte voiceMode = 0;

byte presetName[17] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32 };
String presetNameString;
byte currentPreset;



#endif
