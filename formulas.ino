//1 VCFKeytrack
//2 ADSR2toVCF
//4 LFO2toVCF
//7 LFO1toVCA

// Recompute a modulation depth/keytrack formula scalar (see case index comments above).
void formula_update(byte formulaN) {
  switch (formulaN) {
    case 1:
      if (VCFKeytrack != 0) {
        VCFKeytrackModifier = (float)VCFKeytrack / 8000.00f;
      } else {
        VCFKeytrackModifier = 1;
      }
      break;
    case 2:
      ADSR2toVCF_formula = (float)1 / 512 * ADSR2toVCF;
      break;
    case 4:
      LFO2toVCF_formula = (float)1 / 512 * LFO2toVCF;
      break;
    case 7:
      LFO1toVCA_formula = (float)1 / 512 * LFO1toVCA;
      break;
  }
}

// Recompute LFO speed/depth control curves (exp converters) and apply to LFO objects.
void controls_formula_update(byte formulaN) {
  switch (formulaN) {
    case 1:
      LFO1Speed = expConverterFloat(LFO1SpeedVal, 5000);
      LFO1_class.setMode0Freq(LFO1Speed, micros());
      break;
    case 2:
      LFO2Speed = expConverterFloat(LFO2SpeedVal, 5000);
      LFO2_class.setMode0Freq(LFO2Speed, micros());
      break;
    case 3:
      LFO1toDCO = expConverterFloat(LFO1toDCOVal, 500);
      break;
    case 4:
      LFO2toVCF = expConverter(LFO2toVCFVal, 500);
      break;
    case 31:
      LFO1toVCF = expConverter(LFO1toVCFVal, 500);  // NO usar para pots (si son log), solo para encoder
      break;
  }
}
