# Mainboard CV and pin map

Hardware mapping for **DCO4_Mainboard_Controller** (STM32). Signal routing comes from live `setPWMOuts()` / `mcpUpdate()` / `waveSelector` code and `Timers.h` pin macros.

---

## UART

| Port | Pins (RX / TX) | Baud | Peer |
|------|----------------|------|------|
| `Serial` | USB | 2 000 000 | Debug |
| `Serial1` | PA10 / PA9 | 2 500 000 | Screen |
| `Serial2` | PD6 / PD5 | 2 500 000 | DCO |
| `Serial8` | PE0 / PE1 | 2 500 000 | Input |

Pins and `Uart Serial1/2/8` objects are in `Serial.h` (core 3.x `extern Uart`, not `HardwareSerial`). `setup()` still calls `setRx`/`setTx` then `begin()`.

---

## Timer PWM → resonance / cutoff / VCA

Overflow / resolution uses `ADSR_1_DACSIZE` (see ADSR headers). Active writes are in `PWM.ino` `setPWMOuts()`.

### Resonance (same duty on all voices)

| Voice | Timer / channel | Pin macro | GPIO |
|-------|-----------------|-----------|------|
| 1 | TIM4 CH1 | `TIM4_CH1_PIN` | PD12 |
| 2 | TIM8 CH1 | `TIM8_CH1_PIN` | PC6 |
| 3 | TIM5 CH1 | `TIM5_CH1_PIN` | PA0 |
| 4 | TIM3 CH1 | `TIM3_CH1_PIN` | PB4 |

### Cutoff (`VCF_PWM[i]`)

| Voice | Timer / channel | Pin macro | GPIO |
|-------|-----------------|-----------|------|
| 0 | TIM12 CH1 | `TIM12_CH1_PIN` | PB14 |
| 1 | TIM4 CH3 | `TIM4_CH3_PIN` | PD14 |
| 2 | TIM15 CH2 | `TIM15_CH2_PIN` | PE6 |
| 3 | TIM5 CH3 | `TIM5_CH3_PIN` | PA2 |

### VCA (`VCA_PWM[i]`)

| Voice | Timer / channel | Pin macro | GPIO |
|-------|-----------------|-----------|------|
| 0 | TIM2 CH3 | `TIM2_CH3_PIN` | PB10 |
| 1 | TIM13 CH1 | `TIM13_CH1_PIN` | PA6 |
| 2 | TIM1 CH4 | `TIM1_CH4_PIN` | PE14 |
| 3 | TIM3 CH3 | `TIM3_CH3_PIN` | PB0 |

Other timer channels are configured in `init_timers()` for historical / alternate wiring; only the rows above are written every loop by `setPWMOuts()`.

**`ENABLE_SD`:** defined in the main sketch. TIM8 CH4 / some SDMMC pins (`PD2`, `PC8`–`PC12`) are reserved; see comments in `DCO4_Mainboard_Controller.ino` and gated paths in `Timers.ino`.

**`ENABLE_SPI`:** currently **off**. When off, TIM2 CH1/CH2 and TIM3 CH2 PWM modes are still enabled; SPI DAC path is inactive.

---

## I2C MCP4728 (square / sub levels)

| Item | Value |
|------|--------|
| SDA | PB9 |
| SCL | PB8 |
| Clock | 1 MHz |
| Chips | `mcp` @ `0x63`, `mcp2` @ `0x64`, `mcp3` @ `0x65` |

`mcpUpdate()` channel mapping (comments in `PWM.ino`):

| Chip | A | B | C | D |
|------|---|---|---|---|
| `mcp` | V1 OSC1 SQR | V2 OSC2 SQR | V2 OSC1 SQR | V3 OSC2 SQR |
| `mcp2` | V3 OSC1 SQR | V4 OSC2 SQR | V4 OSC1 SQR | SUB3 |
| `mcp3` | SUB4 | SUB1 | SUB2 | V1 OSC2 SQR |

Levels: globals `SQR1Level`, `SQR2Level`, `SubLevel` (updated from params).

---

## Wave selector (74HC595 × 2)

| Signal | Pin |
|--------|-----|
| DATA | PE4 |
| LATCH | PE2 |
| CLK | PE3 |

Mux bit arrays (crossed cabling — active values in `waveSelector.h`):

| Wave | Bits per voice 0..3 |
|------|---------------------|
| TRI | 14, 10, 6, 2 |
| SINE | 13, 9, 5, 1 |
| SAW2 | 12, 8, 4, 0 |
| SAW | 15, 11, 7, 3 |

`update_waveSelector(wave)` writes pins from `sawStatus` / `saw2Status` / `triStatus` / `sqr2Status` (inverted).

---

## Inactive hardware paths

| Path | Status |
|------|--------|
| Local SD / EEPROM presets (`flashData.ino`) | Fully commented; presets live on Input |
| SPI BU2505FV | `ENABLE_SPI` off; functions commented |
| On-board Screen module | `ENABLE_SCREEN` / `Screen.h` commented out |
| Autotune include | Commented |

See [`MODULATION_PIPELINE.md`](MODULATION_PIPELINE.md) for how CVs are computed before these pins are written.
