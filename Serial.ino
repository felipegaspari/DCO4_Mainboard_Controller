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
  if (calibrationMode) {
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

void serial_send_param_change(byte param, uint16_t paramValue) {

  byte bytesArray[5] = { (uint8_t)'p', param, highByte(paramValue), lowByte(paramValue), finishByte };
#ifdef ENABLE_SERIAL1
  while (Serial1.availableForWrite() < 5) {}
  Serial1.write(bytesArray, 5);
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
      case 'a':
        {
          byte byteArray[8];
          Serial1.readBytes(byteArray, 8);

          ADSR1_attack = word(byteArray[0], byteArray[1]);
          ADSR1_decay = word(byteArray[2], byteArray[3]);
          ADSR1_sustain = word(byteArray[4], byteArray[5]);
          ADSR1_release = word(byteArray[6], byteArray[7]);
          break;
        }
      case 'b':
        {
          byte byteArray[8];
          Serial1.readBytes(byteArray, 8);

          ADSR2_attack = word(byteArray[0], byteArray[1]);
          ADSR2_decay = word(byteArray[2], byteArray[3]);
          ADSR2_sustain = word(byteArray[4], byteArray[5]);
          ADSR2_release = word(byteArray[6], byteArray[7]);
          break;
        }
      case 'c':
        {
          byte byteArray[8];
          Serial1.readBytes(byteArray, 8);

          ADSR3_attack = word(byteArray[0], byteArray[1]);
          ADSR3_decay = word(byteArray[2], byteArray[3]);
          ADSR3_sustain = word(byteArray[4], byteArray[5]);
          ADSR3_release = word(byteArray[6], byteArray[7]);
          break;
        }
      case 'd':
        {
          byte byteArray[8];
          Serial1.readBytes(byteArray, 8);

          CUTOFF = word(byteArray[0], byteArray[1]);
          RESONANCE = word(byteArray[2], byteArray[3]);
          ADSR2toVCF = word(byteArray[4], byteArray[5]);
          LFO1toVCF = word(byteArray[6], byteArray[7]);
          formula_update(3);
          formula_update(2);
          break;
        }
      case 'e':
        {
          byte byteArray[2];
          Serial1.readBytes(byteArray, 2);

          ADSR1toVCA = word(byteArray[0], byteArray[1]);
          break;
        }
      case 'f':
        {
          byte byteArray[2];
          Serial1.readBytes(byteArray, 2);

          PW = word(byteArray[0], byteArray[1]);
          break;
        }
      case 'n':
        {
          byte byteArray[3];
          while (Serial1.available() < 3) {}
          Serial1.readBytes(byteArray, 3);

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
          while (Serial1.available() < 1) {}
          voice_n = Serial1.read();
          noteEnd[voice_n] = 1;
          noteStart[voice_n] = 0;
          break;
        }
      case 'p':
        {
          byte paramBytes[3];
          byte finishByte = 1;
          byte readByte = 0;

          while (Serial1.available() < 1) {}

          Serial1.readBytes(paramBytes, 3);

          while (readByte != finishByte) {
            readByte = Serial1.read();
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

          while (Serial1.available() < 1) {}

          Serial1.readBytes(paramBytes, 2);

          while (readByte != finishByte) {
            readByte = Serial1.read();
          }

          uint8_t paramNumber = paramBytes[0];
          int16_t paramValue = paramBytes[1];

          update_parameters(paramNumber, (uint16_t)paramValue);
          break;
        }
      case 'z':
        {
          // if (commandCharacter == 'v') //based on the command character, we decide what to do
          byte dataArray[2];

          byte ndata = 0;
          while (ndata < 2) {
            //for (byte ndata = 0; ndata < 122; ndata++)
            if (Serial1.available() > 0) {
              dataArray[ndata] = Serial1.read();
              ndata++;
            }
          }
          uint16_t a;
          ((uint8_t *)&a)[0] = dataArray[0];
          ((uint8_t *)&a)[1] = dataArray[1];
          //Serial.println(" raw ");
          //Serial.println(a);

          break;
        }
      case 'g':
        {
          byte dataArray[4];

          byte ndata = 0;
          while (ndata < 4) {
            //for (byte ndata = 0; ndata < 122; ndata++)
            //if (Serial1.available() > 0) {
            while (Serial1.available() < 1) {}
            dataArray[ndata] = Serial1.read();
            ndata++;
            //}
          }
          float a;
          ((uint8_t *)&a)[0] = dataArray[0];
          ((uint8_t *)&a)[1] = dataArray[1];
          ((uint8_t *)&a)[2] = dataArray[2];
          ((uint8_t *)&a)[3] = dataArray[3];

          freq = a;
          break;
        }
    }
  }
#endif
}
void read_serial_2() {
#ifdef ENABLE_SERIAL2
  while (Serial2.available() > 0) {
    char commandCharacter = Serial2.read();  //we use characters (letters) for controlling the switch-case
    switch (commandCharacter) {
      case 'a':
        {
          byte byteArray[8];
          Serial2.readBytes(byteArray, 8);

          ADSR1_attack = word(byteArray[0], byteArray[1]);
          ADSR1_decay = word(byteArray[2], byteArray[3]);
          ADSR1_sustain = word(byteArray[4], byteArray[5]);
          ADSR1_release = word(byteArray[6], byteArray[7]);
          break;
        }
      case 'b':
        {
          byte byteArray[8];
          Serial2.readBytes(byteArray, 8);

          ADSR2_attack = word(byteArray[0], byteArray[1]);
          ADSR2_decay = word(byteArray[2], byteArray[3]);
          ADSR2_sustain = word(byteArray[4], byteArray[5]);
          ADSR2_release = word(byteArray[6], byteArray[7]);
          break;
        }
      case 'c':
        {
          byte byteArray[8];
          Serial2.readBytes(byteArray, 8);

          ADSR3_attack = word(byteArray[0], byteArray[1]);
          ADSR3_decay = word(byteArray[2], byteArray[3]);
          ADSR3_sustain = word(byteArray[4], byteArray[5]);
          ADSR3_release = word(byteArray[6], byteArray[7]);
          break;
        }
      case 'd':
        {
          byte byteArray[8];
          Serial2.readBytes(byteArray, 8);

          CUTOFF = word(byteArray[0], byteArray[1]);
          RESONANCE = word(byteArray[2], byteArray[3]);
          ADSR2toVCF = word(byteArray[4], byteArray[5]);
          LFO1toVCF = word(byteArray[6], byteArray[7]);

          formula_update(2);
          formula_update(3);

          break;
        }
      case 'e':
        {
          byte byteArray[2];
          Serial2.readBytes(byteArray, 2);

          ADSR1toVCA = word(byteArray[0], byteArray[1]);
          break;
        }
      case 'f':
        {
          byte byteArray[2];
          Serial2.readBytes(byteArray, 2);

          PW = word(byteArray[0], byteArray[1]);
          break;
        }
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
      case 'z':
        {
          // if (commandCharacter == 'v') //based on the command character, we decide what to do
          byte dataArray[2];

          byte ndata = 0;
          while (ndata < 2) {
            //for (byte ndata = 0; ndata < 122; ndata++)
            if (Serial2.available() > 0) {
              dataArray[ndata] = Serial2.read();
              ndata++;
            }
          }
          uint16_t a;
          ((uint8_t *)&a)[0] = dataArray[0];
          ((uint8_t *)&a)[1] = dataArray[1];
          //Serial.println(" raw ");
          //Serial.println(a);

          break;
        }
      case 'g':
        {
          byte dataArray[4];

          byte ndata = 0;
          while (ndata < 4) {
            //for (byte ndata = 0; ndata < 122; ndata++)
            //if (Serial2.available() > 0) {
            while (Serial2.available() < 1) {}
            dataArray[ndata] = Serial2.read();
            ndata++;
            //}
          }
          float a;
          ((uint8_t *)&a)[0] = dataArray[0];
          ((uint8_t *)&a)[1] = dataArray[1];
          ((uint8_t *)&a)[2] = dataArray[2];
          ((uint8_t *)&a)[3] = dataArray[3];

          freq = a;
          break;
        }
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

          ADSR1_attack = word(byteArray[0], byteArray[1]);
          ADSR1_decay = word(byteArray[2], byteArray[3]);
          ADSR1_sustain = word(byteArray[4], byteArray[5]);
          ADSR1_release = word(byteArray[6], byteArray[7]);
          break;
        }
      case 'b':
        {
          byte byteArray[8];
          Serial8.readBytes(byteArray, 8);

          ADSR2_attack = word(byteArray[0], byteArray[1]);
          ADSR2_decay = word(byteArray[2], byteArray[3]);
          ADSR2_sustain = word(byteArray[4], byteArray[5]);
          ADSR2_release = word(byteArray[6], byteArray[7]);
          break;
        }
      case 'c':
        {
          byte byteArray[8];
          Serial8.readBytes(byteArray, 8);

          ADSR3_attack = word(byteArray[0], byteArray[1]);
          ADSR3_decay = word(byteArray[2], byteArray[3]);
          ADSR3_sustain = word(byteArray[4], byteArray[5]);
          ADSR3_release = word(byteArray[6], byteArray[7]);
          break;
        }
      case 'd':
        {
          byte byteArray[8];
          Serial8.readBytes(byteArray, 8);

          CUTOFF = word(byteArray[0], byteArray[1]);
          RESONANCE = word(byteArray[2], byteArray[3]);
          ADSR2toVCF = word(byteArray[4], byteArray[5]);
          LFO1toVCF = word(byteArray[6], byteArray[7]);
          formula_update(3);
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
      case 'n':
        {
          byte byteArray[3];
          while (Serial8.available() < 3) {}
          Serial8.readBytes(byteArray, 3);

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
          while (Serial8.available() < 1) {}
          voice_n = Serial8.read();
          noteEnd[voice_n] = 1;
          noteStart[voice_n] = 0;
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
      case 'z':
        {
          // if (commandCharacter == 'v') //based on the command character, we decide what to do
          byte dataArray[2];

          byte ndata = 0;
          while (ndata < 2) {
            //for (byte ndata = 0; ndata < 122; ndata++)
            if (Serial8.available() > 0) {
              dataArray[ndata] = Serial8.read();
              ndata++;
            }
          }
          uint16_t a;
          ((uint8_t *)&a)[0] = dataArray[0];
          ((uint8_t *)&a)[1] = dataArray[1];
          //Serial.println(" raw ");
          //Serial.println(a);

          break;
        }
      case 'g':
        {
          byte dataArray[4];

          byte ndata = 0;
          while (ndata < 4) {
            //for (byte ndata = 0; ndata < 122; ndata++)
            //if (Serial8.available() > 0) {
            while (Serial8.available() < 1) {}
            dataArray[ndata] = Serial8.read();
            ndata++;
            //}
          }
          float a;
          ((uint8_t *)&a)[0] = dataArray[0];
          ((uint8_t *)&a)[1] = dataArray[1];
          ((uint8_t *)&a)[2] = dataArray[2];
          ((uint8_t *)&a)[3] = dataArray[3];

          freq = a;
          break;
        }
    }
  }
#endif
}