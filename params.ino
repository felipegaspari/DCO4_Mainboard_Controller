void update_parameters(byte paramNumber, int16_t paramValue) {
  switch (paramNumber) {
    case 1:
      sawStatus = paramValue;
      //digitalWrite(PIN_SAW1, sawStatus);
      update_waveSelector(0);
      break;
    case 2:
      saw2Status = paramValue;
      update_waveSelector(1);
      //digitalWrite(PIN_SAW2, saw2Status);
      break;
    case 3:
      triStatus = paramValue;
      update_waveSelector(2);
      //digitalWrite(PIN_TRI, triStatus);
      break;
    case 4:
      sineStatus = paramValue;
      update_waveSelector(3);
      //digitalWrite(PIN_SIN, sineStatus);
      break;
    case 5:
      sqr1Status = paramValue;
      update_waveSelector(4);
      break;
    case 6:
      sqr2Status = paramValue;
      update_waveSelector(5);
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
      serialSendParamByteToDCO[0] = paramNumber;
      serialSendParamByteToDCO[1] = paramValue;
      break;
    case 11:
      LFO1Waveform = paramValue;
      LFO1_class.setWaveForm(LFO1Waveform);
      serialSendParamByteToDCO[0] = paramNumber;
      serialSendParamByteToDCO[1] = paramValue;
      break;
    case 12:
      LFO2Waveform = paramValue;
      LFO2_class.setWaveForm(LFO2Waveform);
      serialSendParamByteToDCO[0] = paramNumber;
      serialSendParamByteToDCO[1] = paramValue;
      break;
    case 13:
      OSC1Interval = paramValue;
      serialSendParamByteToDCO[0] = paramNumber;
      serialSendParamByteToDCO[1] = paramValue;
      break;
    case 14:
      OSC2Interval = paramValue;
      serialSendParamByteToDCO[0] = paramNumber;
      serialSendParamByteToDCO[1] = paramValue;
      break;
    case 15:
      OSC2Detune = paramValue;
      serialSendParamToDCO[0] = paramNumber;
      serialSendParamToDCO[1] = paramValue;
      break;
    case 16:
      LFO2toOSC2DETUNE = paramValue;
      serialSendParamByteToDCO[0] = paramNumber;
      serialSendParamByteToDCO[1] = (byte)paramValue;
      break;
    case 17:
      oscSyncMode = paramValue;
      serialSendParamByteToDCO[0] = paramNumber;
      serialSendParamByteToDCO[1] = paramValue;
      break;
    case 18:
      portamentoTime = paramValue;
      serialSendParamByteToDCO[0] = paramNumber;
      serialSendParamByteToDCO[1] = paramValue;
      break;
    case 19:
      VCFKeytrack = paramValue;
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
      SQR1Level = 4096 - (SQR1LevelVal * 32);
      break;
    case 23:
      SQR2LevelVal = paramValue;
      SQR2Level = 4096 - (SQR2LevelVal * 32);
      break;
    case 24:
      SubLevelVal = paramValue;
      SubLevel = 4096 - (SubLevelVal * 32);
      break;
    case 25:
      // = paramValue " CALIBRATION VAL";
      break;
    case 26:
      voiceMode = paramValue;
      serialSendParamByteToDCO[0] = paramNumber;
      serialSendParamByteToDCO[1] = paramValue;
      break;
    case 27:
      unisonDetune = paramValue;
      serialSendParamByteToDCO[0] = paramNumber;
      serialSendParamByteToDCO[1] = paramValue;
      break;


    case 40:
      LFO1toDCOVal = paramValue;
      controls_formula_update(3);
      serialSendParamByteToDCO[0] = paramNumber;
      serialSendParamByteToDCO[1] = paramValue;
      break;
    case 41:
      LFO1SpeedVal = paramValue;
      controls_formula_update(1);
      serialSendParamToDCO[0] = paramNumber;
      serialSendParamToDCO[1] = paramValue;
      break;
    case 42:
      LFO2SpeedVal = paramValue;
      controls_formula_update(2);
      serialSendParamToDCO[0] = paramNumber;
      serialSendParamToDCO[1] = paramValue;
      break;
    case 43:
      VCALevel = paramValue * 32;
      break;
    case 44:
      LFO1toVCA = paramValue;
      break;
    case 45:
      LFO2toPWM = paramValue;
      formula_update(11);
      serialSendParamToDCO[0] = paramNumber;
      serialSendParamToDCO[1] = paramValue;
      break;
    case 46:
      ADSR3toPWM = paramValue - 512;
      serialSendParamToDCO[0] = paramNumber;
      serialSendParamToDCO[1] = paramValue;
      break;
    case 47:
      ADSR3toDETUNE1 = paramValue;
      formula_update(10);
      serialSendParamToDCO[0] = paramNumber;
      serialSendParamToDCO[1] = paramValue;
      break;
    case 48:
      // = paramValue " ADSR1 Curve";
      break;
    case 49:
      // = paramValue " ADSR2 Curve";
      break;

    case 124:
      PWMPotsControlManual = paramValue;
      serialSendParamByteToDCO[0] = paramNumber;
      serialSendParamByteToDCO[1] = paramValue;
      break;
    case 126:
      ADSR3Enabled = paramValue;
      break;
    case 127:
      //= paramValue " FUNCTION KEY";
      break;


      // case 101:
      //   = paramValue " CALIB MODE";
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
      // case 995:
      //   = paramValue " VCA -> LEVEL";
      //   break;

    default:
      break;
  }
}