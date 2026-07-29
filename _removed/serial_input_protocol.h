// Removed unused code from serial_input_protocol.h

// --- // Optional helper: return payload lengt ---
// Optional helper: return payload length for an input command.
static inline uint8_t input_serial_payload_len(char cmd) {
  switch (cmd) {
    case INPUT_CMD_ADSR1_BLOCK:   return INPUT_SERIAL_LEN_ADSR_BLOCK;
    case INPUT_CMD_ADSR2_BLOCK:   return INPUT_SERIAL_LEN_ADSR_BLOCK;
    case INPUT_CMD_ADSR3_BLOCK:   return INPUT_SERIAL_LEN_ADSR_BLOCK;
    case INPUT_CMD_FILTER_BLOCK:  return INPUT_SERIAL_LEN_FILTER_BLOCK;
    case INPUT_CMD_ADSR1_TO_VCA:  return INPUT_SERIAL_LEN_ADSR1_TO_VCA;
    case INPUT_CMD_PW_VALUE:      return INPUT_SERIAL_LEN_PW_VALUE;
    case INPUT_CMD_PARAM_16:      return INPUT_SERIAL_LEN_PARAM_16;
    case INPUT_CMD_PARAM_8:       return INPUT_SERIAL_LEN_PARAM_8;
    case INPUT_CMD_PRESET_NAME:   return INPUT_SERIAL_LEN_PRESET_NAME;
    default:                      return 0;
  }
}


