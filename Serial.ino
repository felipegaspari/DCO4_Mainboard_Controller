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

inline void serial_send_signal(byte signal) {
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

inline void read_serial_1() {
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


// -------------------------------
// Serial2 parser (non-blocking, shared core)
// -------------------------------
//
// This section wires the generic serial_parser.h core to the mainboard's
// Serial2 link. The mainboard receives from the DCO:
//
//   'n' : NOTE ON
//   'o' : NOTE OFF
//   'p' : PARAM 16-bit (ParamId + int16)
//   'w' : PARAM 8-bit  (ParamId + int8)
//   'x' : PARAM 32-bit (ParamId + uint32)
//
// The parser core is shared; only the handlers below are mainboard-specific.

// NOTE ON ('n') handler
static void main_handle_note_on(char, const uint8_t* payload, uint8_t len) {
  if (len != SERIAL_PAYLOAD_LEN_NOTE_ON) {
    return;
  }
  uint8_t voice_n = payload[0];
  uint8_t velo    = payload[1];
  uint8_t noteVal = payload[2];

  velocity[voice_n]  = velo;
  note[voice_n]      = noteVal;
  noteStart[voice_n] = 1;
  noteEnd[voice_n]   = 0;
}

// NOTE OFF ('o') handler
static void main_handle_note_off(char, const uint8_t* payload, uint8_t len) {
  if (len != SERIAL_PAYLOAD_LEN_NOTE_OFF) {
    return;
  }
  uint8_t voice_n = payload[0];
  noteEnd[voice_n]   = 1;
  noteStart[voice_n] = 0;
}

// Shared parameter handlers: decode then call update_parameters(int32_t)
static void main_handle_param16(char, const uint8_t* payload, uint8_t len) {
  if (len != SERIAL_PAYLOAD_LEN_PARAM_16) {
    return;
  }
  ParamFrame frame;
  decode_param_p(payload, frame);
  update_parameters(frame.id, frame.value);
}

static void main_handle_param8(char, const uint8_t* payload, uint8_t len) {
  if (len != SERIAL_PAYLOAD_LEN_PARAM_8) {
    return;
  }
  ParamFrame frame;
  decode_param_w(payload, frame);
  update_parameters(frame.id, frame.value);
}

static void main_handle_param32(char, const uint8_t* payload, uint8_t len) {
  if (len != SERIAL_PAYLOAD_LEN_PARAM_32) {
    return;
  }
  ParamFrame frame;
  decode_param_x(payload, frame);
  update_parameters(frame.id, frame.value);
}

// Command table for the mainboard's Serial2 link.
static const SerialCommandDef mainSerial2Commands[] = {
  { SERIAL_CMD_NOTE_ON,   SERIAL_PAYLOAD_LEN_NOTE_ON,   main_handle_note_on   },
  { SERIAL_CMD_NOTE_OFF,  SERIAL_PAYLOAD_LEN_NOTE_OFF,  main_handle_note_off  },
  { SERIAL_CMD_PARAM_16,  SERIAL_PAYLOAD_LEN_PARAM_16,  main_handle_param16   },
  { SERIAL_CMD_PARAM_8,   SERIAL_PAYLOAD_LEN_PARAM_8,   main_handle_param8    },
  { SERIAL_CMD_PARAM_32,  SERIAL_PAYLOAD_LEN_PARAM_32,  main_handle_param32   },
};

// Parser context for the mainboard's Serial2 link.
static SerialParserContext mainSerial2Parser = {
  SERIAL_WAIT_FOR_CMD,
  0,
  nullptr,
  {0},
  0,
  0,
  0
};

// Mainboard's Serial2 read loop (replace older parser's read function).
inline void read_serial_2() {
#ifdef ENABLE_SERIAL2
  // First, expire any stale partial frame (only if we're in a frame).
  if (mainSerial2Parser.state == SERIAL_READ_PAYLOAD) {
    uint32_t now = micros();
    serial_parser_check_timeout(mainSerial2Parser, now);
  }

  // Then, consume all available bytes without blocking.
  if (Serial2.available() > 0) {
    uint32_t now = micros();  // one timestamp per batch is enough
    while (Serial2.available() > 0) {
      uint8_t b = Serial2.read();
      serial_parser_process_byte(
        mainSerial2Parser,
        mainSerial2Commands,
        sizeof(mainSerial2Commands) / sizeof(mainSerial2Commands[0]),
        b,
        now
      );
    }
  }
#endif
}

// -------------------------------
// Serial8 parser (non-blocking, shared core)
// -------------------------------
//
// This section wires the generic serial_parser.h core to the mainboard's
// Serial8 link. The input board sends:
//
//   'a' : ADSR1 block (8 bytes)
//   'b' : ADSR2 block (8 bytes)
//   'c' : ADSR3 block (8 bytes)
//   'd' : filter block (8 bytes)
//   'e' : ADSR1->VCA amount (2 bytes)
//   'f' : PWM value (2 bytes)
//   'p' : PARAM 16-bit (ParamId + int16 + finish)
//   'w' : PARAM 8-bit  (ParamId + int8  + finish)
//   'q' : preset name (8 chars + finish byte)
//
// The parser core is shared; only the handlers below are mainboard-specific.

// ADSR1 block ('a'): 8 bytes
static void input_handle_adsr1(char, const uint8_t* payload, uint8_t len) {
  if (len != INPUT_SERIAL_LEN_ADSR_BLOCK) {
    return;
  }
  // MAP/CONSTRAIN is done on input board; here we just apply the values.
  ADSR1_attack  = word(payload[0], payload[1]);
  ADSR1_decay   = word(payload[2], payload[3]);
  ADSR1_sustain = word(payload[4], payload[5]);
  ADSR1_release = word(payload[6], payload[7]);
}

// ADSR2 block ('b'): 8 bytes
static void input_handle_adsr2(char, const uint8_t* payload, uint8_t len) {
  if (len != INPUT_SERIAL_LEN_ADSR_BLOCK) {
    return;
  }
  ADSR2_attack  = word(payload[0], payload[1]);
  ADSR2_decay   = word(payload[2], payload[3]);
  ADSR2_sustain = word(payload[4], payload[5]);
  ADSR2_release = word(payload[6], payload[7]);
}

// ADSR3 block ('c'): 8 bytes
static void input_handle_adsr3(char, const uint8_t* payload, uint8_t len) {
  if (len != INPUT_SERIAL_LEN_ADSR_BLOCK) {
    return;
  }
  ADSR3_attack  = word(payload[0], payload[1]);
  ADSR3_decay   = word(payload[2], payload[3]);
  ADSR3_sustain = word(payload[4], payload[5]);
  ADSR3_release = word(payload[6], payload[7]);

  serialSendADSR3ControlValuesFlag = true;
}

// Filter block ('d'): 8 bytes
static void input_handle_filter_block(char, const uint8_t* payload, uint8_t len) {
  if (len != INPUT_SERIAL_LEN_FILTER_BLOCK) {
    return;
  }
  CUTOFF     = word(payload[0], payload[1]);
  RESONANCE  = word(payload[2], payload[3]);
  ADSR2toVCF = word(payload[4], payload[5]);
  LFO2toVCF  = word(payload[6], payload[7]);
  formula_update(4);
  formula_update(2);
}

// ADSR1->VCA amount ('e'): 2 bytes
static void input_handle_adsr1_to_vca(char, const uint8_t* payload, uint8_t len) {
  if (len != INPUT_SERIAL_LEN_ADSR1_TO_VCA) {
    return;
  }
  ADSR1toVCA = word(payload[0], payload[1]);
}

// PWM value ('f'): 2 bytes
static void input_handle_pw(char, const uint8_t* payload, uint8_t len) {
  if (len != INPUT_SERIAL_LEN_PW_VALUE) {
    return;
  }
  PW = word(payload[0], payload[1]);
}

// PARAM 16-bit from input board ('p'):
// payload: [paramNumber, hi, lo, finish] (finish is ignored here).
static void input_handle_param16(char, const uint8_t* payload, uint8_t len) {
  if (len != INPUT_SERIAL_LEN_PARAM_16) {
    return;
  }
  ParamFrame frame;
  decode_param_p(payload, frame);
  update_parameters(frame.id, frame.value);
}

// PARAM 8-bit from input board ('w'):
// payload: [paramNumber, int8 value, finish] (finish is ignored).
static void input_handle_param8(char, const uint8_t* payload, uint8_t len) {
  if (len != INPUT_SERIAL_LEN_PARAM_8) {
    return;
  }
  ParamFrame frame;
  decode_param_w(payload, frame);
  update_parameters(frame.id, frame.value);
}

// Preset name ('q'):
// payload: [8 chars, finishByte]
static void input_handle_preset_name(char, const uint8_t* payload, uint8_t len) {
  if (len != INPUT_SERIAL_LEN_PRESET_NAME) {
    return;
  }
  for (int i = 0; i < 8; ++i) {
    presetName[i] = payload[i];
  }
  // payload[8] is the finish byte; we don't need its value here.
}

// Command table for the mainboard's Serial8 link (input board).
static const SerialCommandDef inputSerial8Commands[] = {
  { INPUT_CMD_ADSR1_BLOCK,   INPUT_SERIAL_LEN_ADSR_BLOCK,   input_handle_adsr1          },
  { INPUT_CMD_ADSR2_BLOCK,   INPUT_SERIAL_LEN_ADSR_BLOCK,   input_handle_adsr2          },
  { INPUT_CMD_ADSR3_BLOCK,   INPUT_SERIAL_LEN_ADSR_BLOCK,   input_handle_adsr3          },
  { INPUT_CMD_FILTER_BLOCK,  INPUT_SERIAL_LEN_FILTER_BLOCK, input_handle_filter_block   },
  { INPUT_CMD_ADSR1_TO_VCA,  INPUT_SERIAL_LEN_ADSR1_TO_VCA, input_handle_adsr1_to_vca   },
  { INPUT_CMD_PW_VALUE,      INPUT_SERIAL_LEN_PW_VALUE,     input_handle_pw             },
  { INPUT_CMD_PARAM_16,      INPUT_SERIAL_LEN_PARAM_16,     input_handle_param16        },
  { INPUT_CMD_PARAM_8,       INPUT_SERIAL_LEN_PARAM_8,      input_handle_param8         },
  { INPUT_CMD_PRESET_NAME,   INPUT_SERIAL_LEN_PRESET_NAME,  input_handle_preset_name    },
};

static SerialParserContext inputSerial8Parser = {
  SERIAL_WAIT_FOR_CMD,
  0,
  nullptr,
  {0},
  0,
  0,
  0
};

inline void read_serial_8() {
#ifdef ENABLE_SERIAL8
  // First, expire any stale partial frame (only if we're in a frame).
  if (inputSerial8Parser.state == SERIAL_READ_PAYLOAD) {
    uint32_t now = micros();
    serial_parser_check_timeout(inputSerial8Parser, now);
  }

  // Then, consume all available bytes without blocking.
  if (Serial8.available() > 0) {
    uint32_t now = micros();  // one timestamp per batch is enough
    while (Serial8.available() > 0) {
      uint8_t b = Serial8.read();
      serial_parser_process_byte(
        inputSerial8Parser,
        inputSerial8Commands,
        sizeof(inputSerial8Commands) / sizeof(inputSerial8Commands[0]),
        b,
        now
      );
    }
  }
#endif
}