void init_waveSelector() {
  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
  pinMode(PIN_CLK, OUTPUT);
  waveSelectorMux.begin(PIN_DATA, PIN_LATCH, PIN_CLK, PIN_PWM);
  waveSelectorMux.setBrightness(255);
  waveSelectorMux.allOff();
}

void update_waveSelector(byte wave) {
  //if (saw2Status == 0) {
  //     Serial.println("entro al all on");
  //waveSelectorMux.allOff();
  switch (wave) {
    case 0:
      for (int i = 0; i < 4; i++) {
        waveSelectorMux.writePin(sawPins[i], sawStatus);
      }
      break;
    case 1:
      for (int i = 0; i < 4; i++) {
        waveSelectorMux.writePin(saw2Pins[i], saw2Status);
      }
      break;
    case 2:
      for (int i = 0; i < 4; i++) {
        waveSelectorMux.writePin(triPins[i], triStatus);
      }
      break;
    case 3:
      for (int i = 0; i < 4; i++) {
        waveSelectorMux.writePin(sinePins[i], sineStatus);
      }
      break;
    case 4:  // Update All
      for (int i = 0; i < 4; i++) {
        waveSelectorMux.writePin(sawPins[i], sawStatus);
        waveSelectorMux.writePin(saw2Pins[i], saw2Status);
        waveSelectorMux.writePin(triPins[i], triStatus);
        waveSelectorMux.writePin(sinePins[i], sineStatus);
      }
      break;
    default:
      break;
  }
  // for (int i = 0; i < 16; i++) {
  //  waveSelectorMux.writePin(i, saw2Status);
  // }
  //   }

  //   if (saw2Status == 1) {
  //        Serial.println("entro al all off");
  //     waveSelectorMux.allOff();
  //   }

  //   Serial.println("antes del ultimo update");
  waveSelectorMux.update();
}