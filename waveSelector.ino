// Boot: GPIO + RoxMux begin for dual 74HC595 wave enables.
void init_waveSelector() {
  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
  pinMode(PIN_CLK, OUTPUT);
  waveSelectorMux.begin(PIN_DATA, PIN_LATCH, PIN_CLK, PIN_PWM);
  waveSelectorMux.setBrightness(255);
  waveSelectorMux.allOff();
}

// Update one wave family (0–3) or all (4) on the 595 mux from status flags.
void update_waveSelector(byte wave) {
  //if (saw2Status == 0) {
  //     Serial.println("entro al all on");
  //waveSelectorMux.allOff();
  // Pin arrays still hold 4 voice slots (hardware map). Monosynth NUM_VOICES=1:
  // only slot 0 follows status flags; unused slots are forced off (write 1).
  switch (wave) {
    case 0:
      for (int i = 0; i < 4; i++) {
        waveSelectorMux.writePin(sawPins[i], (i < NUM_VOICES) ? !sawStatus : 1);
      }
      break;
    case 1:
      for (int i = 0; i < 4; i++) {
        waveSelectorMux.writePin(saw2Pins[i], (i < NUM_VOICES) ? !saw2Status : 1);
      }
      break;
    case 2:
      for (int i = 0; i < 4; i++) {
        waveSelectorMux.writePin(triPins[i], (i < NUM_VOICES) ? !triStatus : 1);
      }
      break;
    case 3:
      for (int i = 0; i < 4; i++) {
        waveSelectorMux.writePin(sinePins[i], (i < NUM_VOICES) ? !sqr2Status : 1);
      }
      break;
    case 4:  // Update All
      for (int i = 0; i < 4; i++) {
        waveSelectorMux.writePin(sawPins[i], (i < NUM_VOICES) ? !sawStatus : 1);
        waveSelectorMux.writePin(saw2Pins[i], (i < NUM_VOICES) ? !saw2Status : 1);
        waveSelectorMux.writePin(triPins[i], (i < NUM_VOICES) ? !triStatus : 1);
        waveSelectorMux.writePin(sinePins[i], (i < NUM_VOICES) ? !sqr2Status : 1);
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