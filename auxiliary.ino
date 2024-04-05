void init_aux() {

}

uint16_t faderExpConverter(uint16_t readingValue) {
  uint16_t pow3Calc = readingValue / 4;
  uint16_t expValOut = pow3Calc * pow3Calc * pow3Calc / 20000;
  return expValOut;
}

float expConverterFloat(uint16_t readingValue, uint16_t curve) {
  uint16_t pow3Calc = readingValue;
  float expValOut = (float)pow3Calc * pow3Calc / curve;
  if (expValOut < 0.005) {
    expValOut = 0;
  }
  return expValOut;
}

uint16_t expConverter(uint16_t readingValue, uint16_t curve) {
  uint16_t pow3Calc = readingValue;
  uint16_t expValOut = (float)pow3Calc * pow3Calc / curve;
  if (expValOut < 0.1) {
    expValOut = 0;
  }
  return expValOut;
}

uint16_t expConverterReverse(uint16_t readingValue, uint16_t curve) {
  uint16_t expValOut = sqrt((float)readingValue / curve);
  return expValOut;
}

uint16_t expConverterFloatReverse(float readingValue, uint16_t curve) {
  uint16_t expValOut = sqrt(readingValue / curve);
  return expValOut;
}