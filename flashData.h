#ifndef __FLASH_H__
#define __FLASH_H__

static const uint8_t flashPresetSize = 140;
byte flashData[flashPresetSize];

#ifdef ENABLE_SD

#include <STM32SD.h>
#define SD_DETECT_PIN SD_DETECT_NONE
File fileBank1;
static const uint16_t flashBankSize = flashPresetSize * 512;
byte presetBank1Buffer[flashBankSize];

#else

#include <EEPROM.h>

#endif

#endif
