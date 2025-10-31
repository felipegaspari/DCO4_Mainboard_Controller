inline void update_parameters(byte paramNumber, int32_t paramValue) {
  switch (paramNumber) {
    case 1:
      sawStatus = paramValue;
      update_waveSelector(0);
      break;
    case 2:
      saw2Status = paramValue;
      update_waveSelector(1);
      break;
    case 3:
      triStatus = paramValue;
      update_waveSelector(2);
      break;
    case 4:
      sineStatus = paramValue;
      //update_waveSelector(3);
      break;
    case 5:
      sqr1Status = paramValue;
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      //update_waveSelector(4);
      break;
    case 6:
      sqr2Status = paramValue;
      update_waveSelector(3);
      break;
    case 7:
      RESONANCEAmpCompensation = paramValue;
      break;
    case 8:
      VCAADSRRestart = paramValue;
      ADSR1_set_restart();
      break;
    case 9:
      VCFADSRRestart = paramValue;
      ADSR2_set_restart();
      break;
    case 10:
      ADSR3ToOscSelect = paramValue;
      //serialSendParamByteToDCO[0] = paramNumber;
      //serialSendParamByteToDCO[1] = paramValue;
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;
    case 11:
      LFO1Waveform = paramValue;
      LFO1_class.setWaveForm(LFO1Waveform);
      //serialSendParamByteToDCO[0] = paramNumber;
      //serialSendParamByteToDCO[1] = paramValue;
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;
    case 12:
      LFO2Waveform = paramValue;
      LFO2_class.setWaveForm(LFO2Waveform);
      //serialSendParamByteToDCO[0] = paramNumber;
      //serialSendParamByteToDCO[1] = paramValue;
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;
    case 13:
      OSC1Interval = paramValue;
      //serialSendParamByteToDCO[0] = paramNumber;
      //serialSendParamByteToDCO[1] = paramValue;
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;
    case 14:
      OSC2Interval = paramValue;
      //serialSendParamByteToDCO[0] = paramNumber;
      //serialSendParamByteToDCO[1] = paramValue;
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;
    case 15:
      OSC2Detune = paramValue;
      //serialSendParamToDCO[0] = paramNumber;
      //serialSendParamToDCO[1] = paramValue;
      serialSendParamToDCOFunction(paramNumber, paramValue);
      break;
    case 16:
      LFO2toOSC2DETUNE = paramValue;
      //serialSendParamByteToDCO[0] = paramNumber;
      //serialSendParamByteToDCO[1] = paramValue;
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;
    case 17:
      oscSyncMode = paramValue;
      //serialSendParamByteToDCO[0] = paramNumber;
      //serialSendParamByteToDCO[1] = paramValue;
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;
    case 18:
      portamentoTime = paramValue;
      //serialSendParamByteToDCO[0] = paramNumber;
      //serialSendParamByteToDCO[1] = paramValue;
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;
    case 19:
      VCFKeytrack = (int16_t)paramValue;
      formula_update(1);
      break;
    case 20:
      velocityToVCFVal = paramValue;
      velocityToVCF = velocityToVCFVal * 0.0003935;
      break;
    case 21:
      velocityToVCAVal = paramValue;
      velocityToVCA = velocityToVCAVal * 0.0003935;
      break;
    case 22:
      SQR1LevelVal = paramValue;
      SQR1Level = lin_to_log_128[SQR1LevelVal];
      mcpUpdate();
      break;
      break;
    case 23:
      SQR2LevelVal = paramValue;
      SQR2Level = lin_to_log_128[SQR2LevelVal];
      mcpUpdate();
      break;
    case 24:
      SubLevelVal = paramValue;
      SubLevel = constrain((SubLevelVal * 32), 0, 4095);
      mcpUpdate();
      break;
    case 25:
      // = paramValue " CALIBRATION VAL";
      break;
    case 26:
      voiceMode = paramValue;
      //serialSendParamByteToDCO[0] = paramNumber;
      //serialSendParamByteToDCO[1] = paramValue;
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;
    case 27:
      unisonDetune = paramValue;
      //serialSendParamByteToDCO[0] = paramNumber;
      //serialSendParamByteToDCO[1] = paramValue;
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;

    case 28:
      analogDrift = paramValue;
      //serialSendParamByteToDCO[0] = paramNumber;
      //serialSendParamByteToDCO[1] = paramValue;
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;

    case 29:
      analogDriftSpeed = paramValue;
      //serialSendParamByteToDCO[0] = paramNumber;
      //serialSendParamByteToDCO[1] = paramValue;
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;

    case 30:
      analogDriftSpread = paramValue;
      //serialSendParamByteToDCO[0] = paramNumber;
      //serialSendParamByteToDCO[1] = paramValue;
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;

    case 31:  // syncMode
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;

    case 40:
      LFO1toDCOVal = paramValue;
      //serialSendParamToDCO[0] = paramNumber;
      //serialSendParamToDCO[1] = paramValue;
      serialSendParamToDCOFunction(paramNumber, paramValue);
      break;
    case 41:
      LFO1SpeedVal = paramValue;
      controls_formula_update(1);
      //serialSendParamToDCO[0] = paramNumber;
      //serialSendParamToDCO[1] = paramValue;
      serialSendParamToDCOFunction(paramNumber, paramValue);
      break;
    case 42:
      LFO2SpeedVal = paramValue;
      controls_formula_update(2);
      //serialSendParamToDCO[0] = paramNumber;
      //serialSendParamToDCO[1] = paramValue;
      serialSendParamToDCOFunction(paramNumber, paramValue);
      break;
    case 43:
      VCALevel = constrain(paramValue * 32, 0, 4095);
      break;
    case 44:
      LFO1toVCA = paramValue;
      formula_update(7);
      break;
    case 45:
      LFO2toPWM = paramValue;
      //serialSendParamToDCO[0] = paramNumber;
      //serialSendParamToDCO[1] = paramValue;
      serialSendParamToDCOFunction(paramNumber, paramValue);
      break;
    case 46:
      ADSR3toPWM = paramValue - 512;
      //serialSendParamToDCO[0] = paramNumber;
      //serialSendParamToDCO[1] = paramValue;
      serialSendParamToDCOFunction(paramNumber, paramValue);
      break;
    case 47:
      ADSR3toDETUNE1 = paramValue;
      //serialSendParamToDCO[0] = paramNumber;
      //serialSendParamToDCO[1] = paramValue;
      serialSendParamToDCOFunction(paramNumber, paramValue);
      break;
    case 48:
      // = paramValue " ADSR1 Attack Curve";
      ADSR1AttackCurveVal = paramValue;
      ADSR1_change_attack_curve(ADSR1AttackCurveVal);
      break;
    case 49:
      // = paramValue " ADSR1 Decay Curve";
      ADSR1DecayCurveVal = paramValue;
      ADSR1_change_decay_curve(ADSR1DecayCurveVal);
      break;
    case 50:
      // = paramValue " ADSR1 Attack Curve";
      ADSR2AttackCurveVal = paramValue;
      ADSR2_change_attack_curve(ADSR2AttackCurveVal);
      break;
    case 51:
      // = paramValue " ADSR2 Decay Curve";
      ADSR2DecayCurveVal = paramValue;
      ADSR2_change_decay_curve(ADSR2DecayCurveVal);
      break;
    case 124:
      PWMPotsControlManual = paramValue;
      //serialSendParamByteToDCO[0] = paramNumber;
      //serialSendParamByteToDCO[1] = paramValue;
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;
    case 126:
      ADSR3Enabled = paramValue;
      break;
    case 127:
      //= paramValue " FUNCTION KEY";
      break;

    case 150:
      calibrationFlag = paramValue;
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;
    case 151:
      manualCalibrationFlag = paramValue;
      calibrationFlag = paramValue;
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;
    case 152:
      manualCalibrationStage = (uint8_t)paramValue;
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;
    case 153:  // manual calibration offset
      serialSendParamByteToDCOFunction(paramNumber, paramValue);
      break;
    case 154:  // gap from DCO
      serialSendParam32ToScreen(paramNumber, (int32_t)paramValue);
      break;

    //    MENU ACTIONS:
    
    // case 190:   // MENU POSITION
    // serialSendParamByteToScreen(paramNumber, paramValue);
    //   break;

    // case 191:   // 
    // serialSendParamByteToScreen(paramNumber, paramValue);
    //   break;

    // case 192:   // 
    // serialSendParamByteToScreen(paramNumber, paramValue);
    //   break;

    // case 193:   // 
    // serialSendParamByteToScreen(paramNumber, paramValue);
    //   break;

    // case 199:   // EXIT CURRENT MENU
    // serialSendParamByteToScreen(paramNumber, paramValue);
    //   break;
    // case 200:   // CALIBRATION MENU
    // serialSendParamByteToScreen(paramNumber, paramValue);
    //   break;

      // case 140:                         // scroll preset
      //   {
      //     byte presetNameScroll[12];
      //     get_preset_name(paramValue, presetNameScroll);
      //     serial_send_preset_scroll(paramValue, presetNameScroll);
      //     break;
      //   }
      // case 141:                         // load preset
      //   {
      //     loadPreset(paramValue);
      //     serial_send_preset_scroll(paramValue, presetName);
      //     break;
      //   }
      // case 142:  //  write preset
      //   writePreset(paramValue);
      //   serial_send_signal(5);
      //   break;



      // case 885:
      //   = paramValue " VOICE MODE";
      //   break;
      // case 886:
      //   = paramValue " UNISON DETUNE";
      //   break;

      // case 990:
      //   = paramValue " PW";
      //   break;
      // case 991:
      //   = paramValue " LFO3 Speed";
      //   break;
      // case 992:
      //   = paramValue " LFO3 Shape";
      //   break;
      // case 994:
      //   = paramValue " ADSR3 Restart";
      //   break;


    default:
      break;
  }
}