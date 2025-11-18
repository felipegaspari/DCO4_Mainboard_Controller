// Central parameter router for the mainboard.
//
// This module maps numeric parameter IDs (used over Serial between MCUs and UI)
// to concrete state changes on the mainboard (local DSP/control) and forwards
// a subset of parameters on to the DCO or screen when needed.
//
// Parameter IDs and their numeric values are defined in params_def.h so that
// all MCUs share a consistent view of the parameter space.
//
// High-level flow:
//   1) Some control source (input board, screen, DCO, MIDI, etc.) decides that
//      parameter P should change to value V.
//   2) That source sends P and V over a Serial link (usually via 'p'/'w'/'x').
//   3) The mainboard receives the frame, decodes P and V, and calls:
//         update_parameters(paramNumber, paramValue);
//   4) update_parameters() looks up paramNumber in paramTable[] and calls
//      the corresponding apply_param_*() function.
//   5) That function updates mainboard-local state and optionally forwards the
//      parameter to the DCO or screen.
//
// How to add or modify a parameter on the mainboard:
//   1) Define or reuse a ParamId in params_def.h (for mainboard + DCO + tools).
//   2) Implement a new apply_param_*() function below that:
//        - Accepts int32_t (the raw transport value; fits 'x' 32‑bit cases).
//        - Updates the appropriate globals / DSP structures.
//        - Computes any derived values (e.g. float gains, fixed-point scales).
//        - Calls serialSendParam*() helpers if it should be forwarded.
//   3) Add an entry to paramTable[] mapping your ParamId to the new function.
//   4) Make sure all senders use the same ParamId and appropriate value range.


// ---- Apply functions for each parameter -----------------------------

// 1: saw on/off
static void apply_param_saw_status(int32_t v) {
  sawStatus = (v != 0);
  update_waveSelector(0);
}

// 2: saw2 on/off
static void apply_param_saw2_status(int32_t v) {
  saw2Status = (v != 0);
  update_waveSelector(1);
}

// 3: tri on/off
static void apply_param_tri_status(int32_t v) {
  triStatus = (v != 0);
  update_waveSelector(2);
}

// 4: sine on/off
static void apply_param_sine_status(int32_t v) {
  sineStatus = (v != 0);
  // original code had commented-out update_waveSelector(3)
}

// 5: sqr1 on/off, also forward to DCO
static void apply_param_sqr1_status(int32_t v) {
  sqr1Status = (v != 0);
  serialSendParamByteToDCOFunction(PARAM_SQR1_STATUS, (uint8_t)v);
}

// 6: sqr2 on/off
static void apply_param_sqr2_status(int32_t v) {
  sqr2Status = (v != 0);
  update_waveSelector(3);
}

// 7: resonance amp compensation enable
static void apply_param_resonance_comp(int32_t v) {
  RESONANCEAmpCompensation = (v != 0);
}

// 8: VCA ADSR restart flag
static void apply_param_vca_adsr_restart(int32_t v) {
  VCAADSRRestart = (v != 0);
  ADSR1_set_restart();
}

// 9: VCF ADSR restart flag
static void apply_param_vcf_adsr_restart(int32_t v) {
  VCFADSRRestart = (v != 0);
  ADSR2_set_restart();
}

// 10: ADSR3 to oscillator selection, forward to DCO
static void apply_param_adsr3_to_osc_select(int32_t v) {
  ADSR3ToOscSelect = (int8_t)v;
  serialSendParamByteToDCOFunction(PARAM_ADSR3_TO_OSC_SELECT, (uint8_t)v);
}

// 11: LFO1 waveform, set locally and forward to DCO
static void apply_param_lfo1_waveform(int32_t v) {
  LFO1Waveform = (int8_t)v;
  LFO1_class.setWaveForm(LFO1Waveform);
  serialSendParamByteToDCOFunction(PARAM_LFO1_WAVEFORM, (uint8_t)v);
}

// 12: LFO2 waveform, set locally and forward to DCO
static void apply_param_lfo2_waveform(int32_t v) {
  LFO2Waveform = (int8_t)v;
  LFO2_class.setWaveForm(LFO2Waveform);
  serialSendParamByteToDCOFunction(PARAM_LFO2_WAVEFORM, (uint8_t)v);
}

// 13: OSC1 interval (semitone offset), forward to DCO
static void apply_param_osc1_interval(int32_t v) {
  OSC1Interval = (int8_t)v;
  serialSendParamByteToDCOFunction(PARAM_OSC1_INTERVAL, (uint8_t)v);
}

// 14: OSC2 interval, forward to DCO
static void apply_param_osc2_interval(int32_t v) {
  OSC2Interval = (int8_t)v;
  serialSendParamByteToDCOFunction(PARAM_OSC2_INTERVAL, (uint8_t)v);
}

// 15: OSC2 detune amount, forward to DCO as 16-bit
static void apply_param_osc2_detune(int32_t v) {
  OSC2Detune = (int16_t)v;
  serialSendParamToDCOFunction(PARAM_OSC2_DETUNE_VAL, (int16_t)v);
}

// 16: LFO2 amount -> OSC2 detune, forward to DCO
static void apply_param_lfo2_to_detune2(int32_t v) {
  LFO2toOSC2DETUNE = (int16_t)v;
  serialSendParamByteToDCOFunction(PARAM_LFO2_TO_DETUNE2, (uint8_t)v);
}

// 17: osc sync mode, forward to DCO
static void apply_param_osc_sync_mode(int32_t v) {
  oscSyncMode = (uint8_t)v;
  serialSendParamByteToDCOFunction(PARAM_OSC_SYNC_MODE, (uint8_t)v);
}

// 18: portamento time, forward to DCO
static void apply_param_portamento_time(int32_t v) {
  portamentoTime = (uint8_t)v;
  serialSendParamByteToDCOFunction(PARAM_PORTAMENTO_TIME, (uint8_t)v);
}

// 19: VCF keytrack
static void apply_param_vcf_keytrack(int32_t v) {
  VCFKeytrack = (int16_t)v;
  formula_update(1);
}

// 20: velocity to VCF
static void apply_param_velocity_to_vcf(int32_t v) {
  velocityToVCFVal = (int8_t)v;
  velocityToVCF = velocityToVCFVal * 0.0003935f;
}

// 21: velocity to VCA
static void apply_param_velocity_to_vca(int32_t v) {
  velocityToVCAVal = (int8_t)v;
  velocityToVCA = velocityToVCAVal * 0.0003935f;
}

// 22: SQR1 level
static void apply_param_sqr1_level(int32_t v) {
  SQR1LevelVal = (int16_t)v;
  SQR1Level = lin_to_log_128[SQR1LevelVal];
  mcpUpdate();
}

// 23: SQR2 level
static void apply_param_sqr2_level(int32_t v) {
  SQR2LevelVal = (int16_t)v;
  SQR2Level = lin_to_log_128[SQR2LevelVal];
  mcpUpdate();
}

// 24: Sub level
static void apply_param_sub_level(int32_t v) {
  SubLevelVal = (int16_t)v;
  SubLevel = constrain(SubLevelVal * 32, 0, 4095);
  mcpUpdate();
}

// 25: calibration value (reserved here)
static void apply_param_calibration_value(int32_t /*v*/) {
  // no-op on mainboard; preserved for compatibility
}

// 26: voice mode, forward to DCO
static void apply_param_voice_mode(int32_t v) {
  voiceMode = (uint8_t)v;
  serialSendParamByteToDCOFunction(PARAM_VOICE_MODE, (uint8_t)v);
}

// 27: unison detune, forward to DCO
static void apply_param_unison_detune(int32_t v) {
  unisonDetune = (int16_t)v;
  serialSendParamByteToDCOFunction(PARAM_UNISON_DETUNE, (uint8_t)v);
}

// 28: analog drift amount, forward to DCO
static void apply_param_analog_drift_amount(int32_t v) {
  analogDrift = (int8_t)v;
  serialSendParamByteToDCOFunction(PARAM_ANALOG_DRIFT_AMOUNT, (uint8_t)v);
}

// 29: analog drift speed, forward to DCO
static void apply_param_analog_drift_speed(int32_t v) {
  analogDriftSpeed = (int16_t)v;
  serialSendParamByteToDCOFunction(PARAM_ANALOG_DRIFT_SPEED, (uint8_t)v);
}

// 30: analog drift spread, forward to DCO
static void apply_param_analog_drift_spread(int32_t v) {
  analogDriftSpread = (int8_t)v;
  serialSendParamByteToDCOFunction(PARAM_ANALOG_DRIFT_SPREAD, (uint8_t)v);
}

// 31: sync mode (forward-only; DCO handles behavior)
static void apply_param_sync_mode(int32_t v) {
  serialSendParamByteToDCOFunction(PARAM_SYNC_MODE, (uint8_t)v);
}

// 40: LFO1 -> DCO, forward to DCO
static void apply_param_lfo1_to_dco(int32_t v) {
  LFO1toDCOVal = (int16_t)v;
  serialSendParamToDCOFunction(PARAM_LFO1_TO_DCO, (int16_t)v);
}

// 41: LFO1 speed, local formula + forward to DCO
static void apply_param_lfo1_speed(int32_t v) {
  LFO1SpeedVal = (int16_t)v;
  controls_formula_update(1);
  serialSendParamToDCOFunction(PARAM_LFO1_SPEED, (int16_t)v);
}

// 42: LFO2 speed, local formula + forward to DCO
static void apply_param_lfo2_speed(int32_t v) {
  LFO2SpeedVal = (int16_t)v;
  controls_formula_update(2);
  serialSendParamToDCOFunction(PARAM_LFO2_SPEED, (int16_t)v);
}

// 43: VCA level (raw, 0..127 mapped to 0..4095)
static void apply_param_vca_level(int32_t v) {
  VCALevelVal = (int16_t)v;
  VCALevel = constrain(VCALevelVal * 32, 0, 4095);
}

// 44: LFO1 -> VCA amount
static void apply_param_lfo1_to_vca(int32_t v) {
  LFO1toVCA = (int16_t)v;
  formula_update(7);
}

// 45: LFO2 -> PWM, forward to DCO as 16-bit
static void apply_param_lfo2_to_pw(int32_t v) {
  LFO2toPWM = (int16_t)v;
  serialSendParamToDCOFunction(PARAM_LFO2_TO_PW, (int16_t)v);
}

// 46: ADSR3 -> PWM, offset by 512, forward to DCO
static void apply_param_adsr3_to_pwm(int32_t v) {
  ADSR3toPWM = (int16_t)v - 512;
  serialSendParamToDCOFunction(PARAM_ADSR3_TO_PWM, (int16_t)v);
}

// 47: ADSR3 -> DETUNE1, forward to DCO
static void apply_param_adsr3_to_detune1(int32_t v) {
  ADSR3toDETUNE1 = (int16_t)v;
  serialSendParamToDCOFunction(PARAM_ADSR3_TO_DETUNE1, (int16_t)v);
}

// 48/49/50/51: ADSR curve parameters (mainboard-local only)
static void apply_param_adsr1_attack_curve(int32_t v) {
  ADSR1AttackCurveVal = (int16_t)v;
  ADSR1_change_attack_curve(ADSR1AttackCurveVal);
}

static void apply_param_adsr1_decay_curve(int32_t v) {
  ADSR1DecayCurveVal = (int16_t)v;
  ADSR1_change_decay_curve(ADSR1DecayCurveVal);
}

static void apply_param_adsr2_attack_curve(int32_t v) {
  ADSR2AttackCurveVal = (int16_t)v;
  ADSR2_change_attack_curve(ADSR2AttackCurveVal);
}

static void apply_param_adsr2_decay_curve(int32_t v) {
  ADSR2DecayCurveVal = (int16_t)v;
  ADSR2_change_decay_curve(ADSR2DecayCurveVal);
}

// 124: PWM pots manual flag, forward to DCO
static void apply_param_pwm_pots_manual(int32_t v) {
  PWMPotsControlManual = (v != 0);
  serialSendParamByteToDCOFunction(PARAM_PWM_POTS_CONTROL_MANUAL, (uint8_t)v);
}

// 126: ADSR3 enabled flag
static void apply_param_adsr3_enabled(int32_t v) {
  ADSR3Enabled = (v != 0);
}

// 127: function key (UI-level, currently unused)
static void apply_param_function_key(int32_t /*v*/) {
  // no-op here; handled in higher-level UI code if needed
}

// 150: calibration flag, forward to DCO
static void apply_param_calibration_flag(int32_t v) {
  calibrationFlag = (v != 0);
  serialSendParamByteToDCOFunction(PARAM_CALIBRATION_FLAG, (uint8_t)v);
}

// 151: manual calibration flag, forward to DCO
static void apply_param_manual_calibration_flag(int32_t v) {
  manualCalibrationFlag = (v != 0);
  calibrationFlag = (v != 0);
  serialSendParamByteToDCOFunction(PARAM_MANUAL_CALIBRATION_FLAG, (uint8_t)v);
}

// 152: manual calibration stage, forward to DCO
static void apply_param_manual_calibration_stage(int32_t v) {
  manualCalibrationStage = (int8_t)v;
  serialSendParamByteToDCOFunction(PARAM_MANUAL_CALIBRATION_STAGE, (uint8_t)v);
}

// 153: manual calibration offset, forward to DCO
static void apply_param_manual_calibration_offset(int32_t v) {
  serialSendParamByteToDCOFunction(PARAM_MANUAL_CALIBRATION_OFFSET, (uint8_t)v);
}

// 154: 32-bit "gap from DCO" value, forward to screen as 32-bit
static void apply_param_gap_from_dco(int32_t v) {
  serialSendParam32ToScreen(PARAM_GAP_FROM_DCO, (uint32_t)v);
}

// 155: manual calibration offsets reported from DCO (packed index/offset),
// forwarded unchanged to the screen so the UI can sync its local offsets.
static void apply_param_manual_calibration_offset_from_dco(int32_t v) {
  // v's lower 16 bits: [index:8 | offset:8]; keep as-is for the screen.
  serialSendParam32ToScreen(PARAM_MANUAL_CALIBRATION_OFFSET_FROM_DCO,
                            (uint32_t)(uint16_t)v);
}

// ---- Parameter table ------------------------------------------------

static const ParamDescriptorT<int32_t> paramTable[] = {
  { PARAM_SAW_STATUS,               apply_param_saw_status },
  { PARAM_SAW2_STATUS,              apply_param_saw2_status },
  { PARAM_TRI_STATUS,               apply_param_tri_status },
  { PARAM_SINE_STATUS,              apply_param_sine_status },

  { PARAM_SQR1_STATUS,              apply_param_sqr1_status },
  { PARAM_SQR2_STATUS,              apply_param_sqr2_status },

  { PARAM_RESONANCE_COMPENSATION,   apply_param_resonance_comp },
  { PARAM_VCA_ADSR_RESTART,         apply_param_vca_adsr_restart },
  { PARAM_VCF_ADSR_RESTART,         apply_param_vcf_adsr_restart },

  { PARAM_ADSR3_TO_OSC_SELECT,      apply_param_adsr3_to_osc_select },
  { PARAM_LFO1_WAVEFORM,            apply_param_lfo1_waveform },
  { PARAM_LFO2_WAVEFORM,            apply_param_lfo2_waveform },
  { PARAM_OSC1_INTERVAL,            apply_param_osc1_interval },
  { PARAM_OSC2_INTERVAL,            apply_param_osc2_interval },
  { PARAM_OSC2_DETUNE_VAL,          apply_param_osc2_detune },
  { PARAM_LFO2_TO_DETUNE2,          apply_param_lfo2_to_detune2 },
  { PARAM_OSC_SYNC_MODE,            apply_param_osc_sync_mode },
  { PARAM_PORTAMENTO_TIME,          apply_param_portamento_time },

  { PARAM_VCF_KEYTRACK,             apply_param_vcf_keytrack },
  { PARAM_VELOCITY_TO_VCF,          apply_param_velocity_to_vcf },
  { PARAM_VELOCITY_TO_VCA,          apply_param_velocity_to_vca },
  { PARAM_SQR1_LEVEL,               apply_param_sqr1_level },
  { PARAM_SQR2_LEVEL,               apply_param_sqr2_level },
  { PARAM_SUB_LEVEL,                apply_param_sub_level },

  { PARAM_CALIBRATION_VALUE,        apply_param_calibration_value },

  { PARAM_VOICE_MODE,               apply_param_voice_mode },
  { PARAM_UNISON_DETUNE,            apply_param_unison_detune },
  { PARAM_ANALOG_DRIFT_AMOUNT,      apply_param_analog_drift_amount },
  { PARAM_ANALOG_DRIFT_SPEED,       apply_param_analog_drift_speed },
  { PARAM_ANALOG_DRIFT_SPREAD,      apply_param_analog_drift_spread },
  { PARAM_SYNC_MODE,                apply_param_sync_mode },

  { PARAM_LFO1_TO_DCO,              apply_param_lfo1_to_dco },
  { PARAM_LFO1_SPEED,               apply_param_lfo1_speed },
  { PARAM_LFO2_SPEED,               apply_param_lfo2_speed },

  { PARAM_VCA_LEVEL,                apply_param_vca_level },
  { PARAM_LFO1_TO_VCA,              apply_param_lfo1_to_vca },

  { PARAM_LFO2_TO_PW,               apply_param_lfo2_to_pw },
  { PARAM_ADSR3_TO_PWM,             apply_param_adsr3_to_pwm },
  { PARAM_ADSR3_TO_DETUNE1,         apply_param_adsr3_to_detune1 },

  { PARAM_ADSR1_ATTACK_CURVE,       apply_param_adsr1_attack_curve },
  { PARAM_ADSR1_DECAY_CURVE,        apply_param_adsr1_decay_curve },
  { PARAM_ADSR2_ATTACK_CURVE,       apply_param_adsr2_attack_curve },
  { PARAM_ADSR2_DECAY_CURVE,        apply_param_adsr2_decay_curve },

  { PARAM_PWM_POTS_CONTROL_MANUAL,  apply_param_pwm_pots_manual },
  { PARAM_ADSR3_ENABLED,            apply_param_adsr3_enabled },
  { PARAM_FUNCTION_KEY,             apply_param_function_key },

  { PARAM_CALIBRATION_FLAG,         apply_param_calibration_flag },
  { PARAM_MANUAL_CALIBRATION_FLAG,  apply_param_manual_calibration_flag },
  { PARAM_MANUAL_CALIBRATION_STAGE, apply_param_manual_calibration_stage },
  { PARAM_MANUAL_CALIBRATION_OFFSET,apply_param_manual_calibration_offset },

  { PARAM_GAP_FROM_DCO,             apply_param_gap_from_dco },
  { PARAM_MANUAL_CALIBRATION_OFFSET_FROM_DCO,
                                   apply_param_manual_calibration_offset_from_dco }
};

static const size_t paramTableSize =
  sizeof(paramTable) / sizeof(paramTable[0]);

// Public entry point: called from Serial handlers.
inline void update_parameters(byte paramNumber, int32_t paramValue) {
  param_router_apply<int32_t>(paramTable, paramTableSize,
                              static_cast<uint16_t>(paramNumber),
                              paramValue);
}


