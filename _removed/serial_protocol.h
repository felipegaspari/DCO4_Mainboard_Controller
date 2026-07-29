// Removed unused code from serial_protocol.h

// --- // Helper: return canonical payload leng ---
// Helper: return canonical payload length for a command.
// Every MCU should use this so that the parser treats commands consistently.
static inline uint8_t serial_protocol_payload_len(char cmd) {
  switch (cmd) {
    case SERIAL_CMD_NOTE_ON:    return SERIAL_PAYLOAD_LEN_NOTE_ON;
    case SERIAL_CMD_NOTE_OFF:   return SERIAL_PAYLOAD_LEN_NOTE_OFF;
    case SERIAL_CMD_PW_UPDATE:  return SERIAL_PAYLOAD_LEN_PW_UPDATE;
    case SERIAL_CMD_ADSR_BLOCK: return SERIAL_PAYLOAD_LEN_ADSR_BLOCK;
    case SERIAL_CMD_PARAM_16:   return SERIAL_PAYLOAD_LEN_PARAM_16;
    case SERIAL_CMD_PARAM_8:    return SERIAL_PAYLOAD_LEN_PARAM_8;
    case SERIAL_CMD_PARAM_32:   return SERIAL_PAYLOAD_LEN_PARAM_32;
    default:                    return 0; // unknown or unsupported command
  }
}


