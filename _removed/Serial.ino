// Removed unused code from Serial.ino

// --- from Serial.ino: commented dead preset 'r'/'s' cases in read_serial_1 ---
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
        //       case 0: break;
        //       case 1: break;
        //       case 2: break;
        //       case 3: break;
        //       case 4: // should get the number to save
        //       break;
        //       case 5:
        //       writePreset(0);
        //       break;
        //     }
        //     break;
        //   }
