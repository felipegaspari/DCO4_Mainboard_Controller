void sendUint16(uint16_t f) {
  byte *b = (byte *)&f;
  while (Serial2.availableForWrite() < 1) {}
  Serial2.write((char *)"u");
  while (Serial2.availableForWrite() < 1) {}
  Serial2.write(b, 2);
}

void sendFloat(float f) {
  byte *b = (byte *)&f;
  while (Serial2.availableForWrite() < 4) {}
  Serial2.print("t");
  byte ndata = 0;
  for (int i = 0; i < 4; i++) {
    while (Serial2.availableForWrite() < 1) {}
    Serial2.write(b[i]);
  }
  return;
}

void sendOK() {
  while (Serial2.availableForWrite() < 1) {}
  Serial2.write((char *)"k");
  //Serial.println("Sent OK");
}

void serial_send_calibration_mode() {
  byte calibrationModeByte;
  if (calibrationFlag) {
    calibrationModeByte = 255;
  } else {
    calibrationModeByte = 222;
  }
  Serial2.write((char *)"a");
  Serial2.write(calibrationModeByte);
  Serial2.flush();
  //Serial.println("Sent autotune on");
}

void serial_send_signal(byte signal) {
#ifdef ENABLE_SERIAL1
  while (Serial1.availableForWrite() < 1) {}
  Serial1.write((char *)"s");
  while (Serial1.availableForWrite() < 1) {}
  Serial1.write(signal);
#endif
}



void serial_send_preset_scroll(byte presetNumber, byte presetNameSerial[]) {

#ifdef ENABLE_SERIAL1
  while (Serial1.availableForWrite() < 1) {}
  Serial1.write((char *)"q");
  while (Serial1.availableForWrite() < 1) {}
  Serial1.write(presetNumber);
  while (Serial1.availableForWrite() < 1) {}
  Serial1.write(presetNameSerial, 8);
  while (Serial1.availableForWrite() < 1) {}
  Serial1.write(finishByte);
#endif
}

void serial_send_save_char_select(byte serialPresetChar) {
#ifdef ENABLE_SERIAL1
  while (Serial1.availableForWrite() < 1) {}
  Serial1.write((char *)"c");
  while (Serial1.availableForWrite() < 1) {}
  Serial1.write(serialPresetChar);
#endif
}

void read_serial_1() {
#ifdef ENABLE_SERIAL1
  while (Serial1.available() > 0) {
    char commandCharacter = Serial1.read();  //we use characters (letters) for controlling the switch-case
    switch (commandCharacter) {
        //     case 'r':
        // {
        //   byte presetNameBytes[8] = { 32, 32, 32, 32, 32, 32, 32, 32 };
        //   while (Serial1.available() < 1) {}
        //   presetNumber = Serial1.read();
        //   while (Serial1.available() < 1) {}

        //   Serial1.readBytes(presetNameBytes, 8);
        //   for (int i = 0; i < 8; i++) {
        //     presetName[i] = presetNameBytes[i];
        //   }
        //   break;
        // }
        // case 's':
        //   {
        //     while (Serial1.available() < 1) {}
        //     serialSignal = Serial1.read();
        //     switch(serialSignal) {
        //       case 0:
        //       break;
        //       case 1:
        //       break;
        //       case 2:
        //       break;
        //       case 3:
        //       break;
        //       case 4:
        //       // should get the number to save
        //       break;
        //       case 5:
        //       writePreset(0);
        //       break;
        //     }

        //     break;
        //   }

      default:
        break;
    }
  }
#endif
}

void read_serial_2() {
#ifdef ENABLE_SERIAL2
  while (Serial2.available() > 0) {
    char commandCharacter = Serial2.read();  //we use characters (letters) for controlling the switch-case
    switch (commandCharacter) {

      case 'n':
        {
          byte byteArray[3];
          while (Serial2.available() < 3) {}
          Serial2.readBytes(byteArray, 3);

          byte voice_n = byteArray[0];
          velocity[voice_n] = byteArray[1];
          note[voice_n] = byteArray[2];

          noteStart[voice_n] = 1;
          noteEnd[voice_n] = 0;
          break;
        }
      case 'o':
        {
          byte voice_n;
          while (Serial2.available() < 1) {}
          voice_n = Serial2.read();
          noteEnd[voice_n] = 1;
          noteStart[voice_n] = 0;
          break;
        }
      case 'p':
        {
          byte paramBytes[3];
          byte finishByte = 1;
          byte readByte = 0;

          while (Serial2.available() < 1) {}

          Serial2.readBytes(paramBytes, 3);

          while (readByte != finishByte) {
            readByte = Serial2.read();
          }

          uint8_t paramNumber = paramBytes[0];
          int16_t paramValue = (int16_t)word(paramBytes[1], paramBytes[2]);

          update_parameters(paramNumber, paramValue);

          break;
        }
      case 'w':
        {
          byte paramBytes[2];
          byte finishByte = 1;
          byte readByte = 0;

          while (Serial2.available() < 1) {}

          Serial2.readBytes(paramBytes, 2);

          while (readByte != finishByte) {
            readByte = Serial2.read();
          }

          uint8_t paramNumber = paramBytes[0];
          int16_t paramValue = paramBytes[1];

          update_parameters(paramNumber, (uint16_t)paramValue);
          break;
        }
      case 'x':
        {
          byte paramBytes[5];
          byte paramValueArray[4];
          byte finishByte = 1;
          byte readByte = 0;
          uint32_t paramValue32;

          while (Serial2.available() < 1) {}

          Serial2.readBytes(paramBytes, 5);

          while (readByte != finishByte) {
            readByte = Serial2.read();
          }

          uint8_t paramNumber = paramBytes[0];
          paramValueArray[0] = paramBytes[1];
          paramValueArray[1] = paramBytes[2];
          paramValueArray[2] = paramBytes[3];
          paramValueArray[3] = paramBytes[4];

          memcpy(&paramValue32, paramValueArray, 4);

          update_parameters(paramNumber, (int32_t)paramValue32);
          break;
        }
        // case 'g':
        //   {
        //     byte byteArray[4];
        //     while (Serial2.available() < 4) {}
        //     Serial2.readBytes(byteArray, 4);
        //     float receivedValueFloat;
        //     memcpy (&receivedValueFloat, byteArray, 4);

        //     //serial_send_param_change_32(154, (uint32_t)receivedValueFloat);
        //     break;
        //   }
    }
  }
#endif
}

void read_serial_8() {
#ifdef ENABLE_SERIAL8
  while (Serial8.available() > 0) {
    char commandCharacter = Serial8.read();  //we use characters (letters) for controlling the switch-case

    switch (commandCharacter) {
      case 'a':
        {
          byte byteArray[8];
          Serial8.readBytes(byteArray, 8);


          //MAP AND CONSTRAIN functions should be implemented on the input board.
          ADSR1_attack = word(byteArray[0], byteArray[1]);  //map(constrain(word(byteArray[0], byteArray[1]), 20, 4075), 20, 4075, 0, 4095);
          ADSR1_decay = word(byteArray[2], byteArray[3]);   //map(constrain(word(byteArray[2], byteArray[3]), 20, 4075), 20, 4075, 0, 4095);
          ADSR1_sustain = word(byteArray[4], byteArray[5]);
          ADSR1_release = word(byteArray[6], byteArray[7]);  //map(constrain(word(byteArray[6], byteArray[7]), 15, 4075), 15, 4075, 0, 4095);
          break;
        }
      case 'b':
        {
          byte byteArray[8];
          Serial8.readBytes(byteArray, 8);

          ADSR2_attack = word(byteArray[0], byteArray[1]);  //map(constrain(word(byteArray[0], byteArray[1]), 20, 4075), 20, 4075, 5, 4095);
          ADSR2_decay = word(byteArray[2], byteArray[3]);   //map(constrain(word(byteArray[2], byteArray[3]), 20, 4075), 20, 4075, 0, 4095);
          ADSR2_sustain = word(byteArray[4], byteArray[5]);
          ADSR2_release = word(byteArray[6], byteArray[7]);  //map(constrain(word(byteArray[6], byteArray[7]), 20, 4075), 20, 4075, 13, 4095);
          break;
        }
      case 'c':
        {
          byte byteArray[8];
          Serial8.readBytes(byteArray, 8);

          ADSR3_attack = word(byteArray[0], byteArray[1]);  //map(constrain(word(byteArray[0], byteArray[1]), 20, 4075), 20, 4075, 5, 4095);
          ADSR3_decay = word(byteArray[2], byteArray[3]);   //map(constrain(word(byteArray[2], byteArray[3]), 20, 4075), 20, 4075, 0, 4095);
          ADSR3_sustain = word(byteArray[4], byteArray[5]);
          ADSR3_release = word(byteArray[6], byteArray[7]);  //map(constrain(word(byteArray[6], byteArray[7]), 20, 4075), 20, 4075, 13, 4095);
          break;
        }
      case 'd':
        {
          byte byteArray[8];
          Serial8.readBytes(byteArray, 8);

          CUTOFF = word(byteArray[0], byteArray[1]);
          RESONANCE = word(byteArray[2], byteArray[3]);
          ADSR2toVCF = word(byteArray[4], byteArray[5]);
          LFO2toVCF = word(byteArray[6], byteArray[7]);
          formula_update(4);
          formula_update(2);
          break;
        }
      case 'e':
        {
          byte byteArray[2];
          Serial8.readBytes(byteArray, 2);

          ADSR1toVCA = word(byteArray[0], byteArray[1]);
          break;
        }
      case 'f':
        {
          byte byteArray[2];
          Serial8.readBytes(byteArray, 2);

          PW = word(byteArray[0], byteArray[1]);
          break;
        }

      case 'p':
        {
          byte paramBytes[3];
          byte finishByte = 1;
          byte readByte = 0;

          while (Serial8.available() < 1) {}

          Serial8.readBytes(paramBytes, 3);

          while (readByte != finishByte) {
            readByte = Serial8.read();
          }

          uint8_t paramNumber = paramBytes[0];
          int16_t paramValue = (int16_t)word(paramBytes[1], paramBytes[2]);

          update_parameters(paramNumber, paramValue);

          break;
        }
      case 'w':
        {
          byte paramBytes[2];
          byte finishByte = 1;
          byte readByte = 0;

          while (Serial8.available() < 1) {}

          Serial8.readBytes(paramBytes, 2);

          while (readByte != finishByte) {
            readByte = Serial8.read();
          }

          uint8_t paramNumber = paramBytes[0];
          int16_t paramValue = paramBytes[1];

          update_parameters(paramNumber, (uint16_t)paramValue);
          break;
        }
      case 'q':
        {
          byte finishByte = 1;
          byte readByte = 0;
          byte presetNameBytes[8] = { 32, 32, 32, 32, 32, 32, 32, 32 };
          while (Serial8.available() < 1) {}

          Serial8.readBytes(presetNameBytes, 8);
          for (int i = 0; i < 8; i++) {
            presetName[i] = presetNameBytes[i];
          }
          while (readByte != finishByte) {
            readByte = Serial8.read();
          }
          break;
        }
    }
  }
#endif
}