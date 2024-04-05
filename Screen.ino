void initScreen() {

#if TM_ACTIVE
  tm.init();
  tm.setBrightness(1);
  delay(10);
  tm.clearScreen();
  tm.display("HOLA");
  delay(10);
#endif

#if TM2_ACTIVE
  module.setupDisplay(true, 1);
  //module.setDisplayToString("HOLA");
  display.print("HOLA");
#endif

#if DISP1_ACTIVE
  u8g2_1.setBusClock(1000000);
  u8g2_1.begin();
  u8g2_1.setDrawColor(2);
  u8g2_1.setFontMode(2);
  u8g2_1.clearBuffer();
  u8g2_1.setFont(u8g2_font_balthasar_titling_nbp_tr);


  u8g2_1.setCursor(0, 26);
  u8g2_1.print(ADSR2_attack);
  //u8g2_1.drawBox(0, 0, 128, 64);
  u8g2_1.sendBuffer();
  delay(10);
#endif
}

void drawScreen() {
  //#if TM_ACTIVE
  //  tm.display("    ");
  //  tm.display(valor1Screen, true, 4 - sizeof(valor1Screen));
  //#endif

#if DISP1_ACTIVE
  u8g2_1.clearBuffer();  // clear the uint16_ternal memory
  u8g2_1.setFont(u8g2_font_balthasar_titling_nbp_tr);
  //u8g2_1.setFont(u8g2_font_calibration_gothic_nbp_tn);
  //u8g2_1.setFont(u8g2_font_VCR_OSD_tu );
  //u8g2_1.setFont(psilent22);

  u8g2_1.setCursor(0, 26);
  u8g2_1.print(ADSR2_attack);

  u8g2_1.setCursor(0, 58);
  u8g2_1.print(LFO1Speed);

  u8g2_1.setCursor(34, 26);
  u8g2_1.print(ADSR2_decay);

  u8g2_1.setCursor(34, 58);
  u8g2_1.print(LFO1toPWM);

  u8g2_1.setCursor(68, 26);
  u8g2_1.print(ADSR2_sustain);

  u8g2_1.setCursor(68, 58);
  u8g2_1.print(ADSR2toVCF);

  u8g2_1.setCursor(102, 26);
  u8g2_1.print(ADSR2_release);

  u8g2_1.setCursor(102, 58);
  u8g2_1.print(CUTOFF);


  u8g2_1.setFont(u8g2_font_4x6_mf);
  u8g2_1.setCursor(0, 36);
  u8g2_1.print(F("LFO"));
  u8g2_1.setCursor(34, 36);
  u8g2_1.print(F("PWM"));
  u8g2_1.setCursor(68, 36);
  u8g2_1.print(F("ENV2"));
  u8g2_1.setCursor(102, 36);
  u8g2_1.print(F("CUTOFF"));
  //
  u8g2_1.setCursor(0, 8);
  u8g2_1.print(F("A"));
  u8g2_1.setCursor(34, 8);
  u8g2_1.print(F("D"));
  u8g2_1.setCursor(68, 8);
  u8g2_1.print(F("S"));
  u8g2_1.setCursor(102, 8);
  u8g2_1.print(F("R"));

  u8g2_1.sendBuffer();  // transfer uint16_ternal memory to the display
#endif
}

void drawTM(int valor) {
#if TM_ACTIVE
  tm.display("    ");
  tm.display(valor, false, 4 - sizeof(valor));
  //  tm.display(valor);
#endif
#if TM2_ACTIVE
  //module.clearDisplay();
  drawTMVal = valor;
  drawTMFlag = true;
  //  display.clear();
  //  display.setDisplayToSignedDecNumber(valor, 0, false);
#endif
}

void drawTMFloat(float valor) {
#if TM_ACTIVE
  tm.display("    ");
  tm.display(valor, true, (2 - sizeof(valor)));
#endif
#if TM2_ACTIVE
  display.clear();
  display.setDisplayToSignedDecNumber(valor, 0, false);
#endif
}

void drawTMString(String valor) {
#if TM2_ACTIVE
  drawTMStringVal = valor;
  drawTMStringFlag = true;
  //display.setDisplayToString(valor);
#endif
}

void drawTMScreen(bool rightNow) {
  if (rightNow) {
//     if (!presetSaved) {
//       blinkChar = !blinkChar;
//       byte presetName4Chars[4];
//       for (byte i = 0; i < 4; i++) {
//         presetName4Chars[i] = presetNameVal[i];
//       }
//       if (blinkChar) {
//         presetName4Chars[presetChar] = 32;
//       }

// #if TM2_ACTIVE
//       display.setDisplayToString(String((char*)presetName4Chars));
// #endif
#if TM2_ACTIVE
    if (drawTMFlag) {
      display.clear();
      display.setDisplayToSignedDecNumber(drawTMVal, 0, false);
      drawTMFlag = false;
    }
    if (drawTMStringFlag) {
      display.setDisplayToString(drawTMStringVal);
      drawTMStringFlag = false;
    }
#endif
  } else {
#if TM2_ACTIVE
    if (drawTMFlag) {
      display.clear();
      display.setDisplayToSignedDecNumber(drawTMVal, 0, false);
      drawTMFlag = false;
    }
    if (drawTMStringFlag) {
      display.setDisplayToString(drawTMStringVal);
      drawTMStringFlag = false;
    }
#endif
  }
}
