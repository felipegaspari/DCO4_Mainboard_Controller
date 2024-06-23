void init_ADSR() {
  for (int i = 0; i < NUM_VOICES; i++) {
    ADSRVoices[i].adsr1_voice.setAttack(ADSR1_attack);    // initialize attack
    ADSRVoices[i].adsr1_voice.setDecay(ADSR1_decay);      // initialize decay
    ADSRVoices[i].adsr1_voice.setSustain(ADSR1_sustain);  // initialize sustain
    ADSRVoices[i].adsr1_voice.setRelease(ADSR1_release);
    ADSRVoices[i].adsr1_voice.setResetAttack(VCAADSRRestart);

    ADSRVoices[i].adsr2_voice.setAttack(ADSR2_attack);    // initialize attack
    ADSRVoices[i].adsr2_voice.setDecay(ADSR2_decay);      // initialize decay
    ADSRVoices[i].adsr2_voice.setSustain(ADSR2_sustain);  // initialize sustain
    ADSRVoices[i].adsr2_voice.setRelease(ADSR2_release);
    ADSRVoices[i].adsr2_voice.setResetAttack(VCFADSRRestart);

    ADSRVoices[i].adsr3_voice.setAttack(ADSR3_attack);    // initialize attack
    ADSRVoices[i].adsr3_voice.setDecay(ADSR3_decay);      // initialize decay
    ADSRVoices[i].adsr3_voice.setSustain(ADSR3_sustain);  // initialize sustain
    ADSRVoices[i].adsr3_voice.setRelease(ADSR3_release);
    ADSRVoices[i].adsr3_voice.setResetAttack(true);
  }
}

void ADSR_update() {
  tADSR = micros();
  for (int i = 0; i < NUM_VOICES; i++) {
    if (noteEnd[i] == 1) {
      ADSRVoices[i].adsr1_voice.noteOff(tADSR - 1);
      ADSRVoices[i].adsr2_voice.noteOff(tADSR - 1);
      ADSRVoices[i].adsr3_voice.noteOff(tADSR - 1);
    } else if (noteStart[i] == 1) {
      ADSRVoices[i].adsr1_voice.noteOff(tADSR - 1);
      ADSRVoices[i].adsr1_voice.setAttack(ADSR1_attack * 1000);
      ADSRVoices[i].adsr1_voice.setDecay(ADSR1_decay * 1000);
      ADSRVoices[i].adsr1_voice.setRelease(ADSR1_release * 1000);
      ADSRVoices[i].adsr1_voice.noteOn(tADSR);
      
      ADSRVoices[i].adsr2_voice.noteOff(tADSR - 1);
      ADSRVoices[i].adsr2_voice.setAttack(ADSR2_attack * 1000);
      ADSRVoices[i].adsr2_voice.setDecay(ADSR2_decay * 1000);
      ADSRVoices[i].adsr2_voice.setRelease(ADSR2_release * 1000);
      ADSRVoices[i].adsr2_voice.noteOn(tADSR);

      ADSRVoices[i].adsr3_voice.noteOff(tADSR - 1);
      ADSRVoices[i].adsr3_voice.setAttack(ADSR3_attack * 1000);
      ADSRVoices[i].adsr3_voice.setDecay(ADSR3_decay * 1000);
      ADSRVoices[i].adsr3_voice.setRelease(ADSR3_release * 1000);
      ADSRVoices[i].adsr3_voice.noteOn(tADSR);
    }
    tADSR = micros();
    ADSR1Level[i] = ADSRVoices[i].adsr1_voice.getWave(tADSR);
    ADSR2Level[i] = ADSRVoices[i].adsr2_voice.getWave(tADSR);
    ADSR3Level[i] = ADSRVoices[i].adsr3_voice.getWave(tADSR);
  }
  ADSR_set_parameters();
}

void ADSR_set_parameters() {
  if ((tADSR - tADSR_params) > 5000) {
    for (int i = 0; i < NUM_VOICES; i++) {
      ADSRVoices[i].adsr1_voice.setSustain(ADSR1_sustain);
      ADSRVoices[i].adsr2_voice.setSustain(ADSR2_sustain);
      ADSRVoices[i].adsr3_voice.setSustain(ADSR3_sustain);
    }
    tADSR_params = tADSR;
  }
}

void ADSR1_set_restart() {
  for (int i = 0; i < NUM_VOICES; i++) {
    ADSRVoices[i].adsr1_voice.setResetAttack(VCAADSRRestart);
  }
}

void ADSR2_set_restart() {
  for (int i = 0; i < NUM_VOICES; i++) {
    ADSRVoices[i].adsr2_voice.setResetAttack(VCFADSRRestart);
  }
}

void ADSR1_change_attack_curve(uint8_t adsrCurveAttack) {
  for (int i = 0; i < NUM_VOICES; i++) {
    ADSRVoices[i].adsr1_voice.adsrCurveAttack(adsrCurveAttack, ADSR_1_CC, ARRAY_SIZE);
    ADSRVoices[i].adsr1_voice.setAttack(ADSR1_attack);    // initialize attack
    ADSRVoices[i].adsr1_voice.setDecay(ADSR1_decay);      // initialize decay
    ADSRVoices[i].adsr1_voice.setSustain(ADSR1_sustain);  // initialize sustain
    ADSRVoices[i].adsr1_voice.setRelease(ADSR1_release);
    ADSRVoices[i].adsr1_voice.setResetAttack(VCAADSRRestart);
  }
}

void ADSR1_change_decay_curve(uint8_t adsrCurveDecay) {
  for (int i = 0; i < NUM_VOICES; i++) {
    //ADSRVoices[i].adsr1_voice.changeCurves(ADSR_1_DACSIZE, ADSR1_curve1, ADSR1_curve2);
    ADSRVoices[i].adsr1_voice.adsrCurveDecayRelease(adsrCurveDecay, ADSR_1_CC, ARRAY_SIZE);
    ADSRVoices[i].adsr1_voice.setAttack(ADSR1_attack);    // initialize attack
    ADSRVoices[i].adsr1_voice.setDecay(ADSR1_decay);      // initialize decay
    ADSRVoices[i].adsr1_voice.setSustain(ADSR1_sustain);  // initialize sustain
    ADSRVoices[i].adsr1_voice.setRelease(ADSR1_release);
    ADSRVoices[i].adsr1_voice.setResetAttack(VCAADSRRestart);
  }
}

void ADSR2_change_attack_curve(uint8_t adsrCurveAttack) {
  for (int i = 0; i < NUM_VOICES; i++) {
    ADSRVoices[i].adsr2_voice.adsrCurveAttack(adsrCurveAttack, ADSR_2_CC, ARRAY_SIZE);
    ADSRVoices[i].adsr2_voice.setAttack(ADSR2_attack);    // initialize attack
    ADSRVoices[i].adsr2_voice.setDecay(ADSR2_decay);      // initialize decay
    ADSRVoices[i].adsr2_voice.setSustain(ADSR2_sustain);  // initialize sustain
    ADSRVoices[i].adsr2_voice.setRelease(ADSR2_release);
    ADSRVoices[i].adsr2_voice.setResetAttack(VCFADSRRestart);
  }
}

void ADSR2_change_decay_curve(uint8_t adsrCurveDecay) {
  for (int i = 0; i < NUM_VOICES; i++) {
    ADSRVoices[i].adsr2_voice.adsrCurveDecayRelease(adsrCurveDecay, ADSR_2_CC, ARRAY_SIZE);
    ADSRVoices[i].adsr2_voice.setAttack(ADSR2_attack);    // initialize attack
    ADSRVoices[i].adsr2_voice.setDecay(ADSR2_decay);      // initialize decay
    ADSRVoices[i].adsr2_voice.setSustain(ADSR2_sustain);  // initialize sustain
    ADSRVoices[i].adsr2_voice.setRelease(ADSR2_release);
    ADSRVoices[i].adsr2_voice.setResetAttack(VCFADSRRestart);
  }
}