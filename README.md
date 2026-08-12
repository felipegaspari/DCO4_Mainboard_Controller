# DCO3-MONOSYNTH – Mainboard Controller (STM32) — ARCHIVED

> **Archived (absorption Phase 5).** This STM32 board is **not part of the shipping monosynth topology**. Modulation (ADSRs, LFOs, filter/VCA CVs, wave mux, MCP4728) and serial hub duties live on the **DCO (Pico 2)**.
>
> - Live overview: [`../../DCO/docs/SYSTEM_OVERVIEW.md`](../../DCO/docs/SYSTEM_OVERVIEW.md)
> - How it was absorbed: [`../../DCO/docs/MAINBOARD_ABSORPTION.md`](../../DCO/docs/MAINBOARD_ABSORPTION.md)
> - Parent pointer: [`../README.md`](../README.md)
>
> To bench the old 4-board stack against this firmware, build DCO with `#define ENABLE_LEGACY_MAINBOARD_LINK` (disables Input/Screen hub defaults).

Firmware for the **Mainboard** of DCO3-MONOSYNTH: the STM32 modulation brain that owns **ADSRs**, **LFOs**, **filter/VCA/resonance CVs** (timer PWM), **square/sub levels** (MCP4728), **analog wave select** (74HC595), and **parameter routing** between the DCO voice board, input controller, and screen.

Based on DCO4 Mainboard, retargeted for **1 voice × 3 oscillators** on the DCO (OSC3 is forward-only here — no OSC3 CV/DAC/mux on this board).

Single-threaded `setup()` / `loop()` (not dual-core).

How this board fits the instrument: canonical overview in [`../../DCO/docs/SYSTEM_OVERVIEW.md`](../../DCO/docs/SYSTEM_OVERVIEW.md); local UART stub in [`docs/SYSTEM_OVERVIEW.md`](docs/SYSTEM_OVERVIEW.md).

## Target model

| Item | Value |
|------|--------|
| Voices | `NUM_VOICES = 1` |
| Filters | `NUM_FILTERS = 2` (both outs currently share voice-0 VCF; unused CVs parked in `PWM.ino`) |
| OSC3 | ParamIds **33–35** store + forward to DCO only |
| ADSR3→osc | **0–4** (OSC1 / OSC2 / both / OSC3 / all), forwarded |
| Manual cal | Stage = osc index **0..2**; OSC3 has no mux/SQR path |

Commented DCO4 voice/LFO slots remain in headers for a later paraphonic path.

## Features

- **Modulation:** 3 Bézier ADSRs (VCA, VCF, ADSR3 for DCO); LFO1 / LFO2; per-voice VCF drift LFO
- **CV outs:** Resonance, cutoff, VCA via STM32 timer PWM; SQR1/SQR2/Sub via MCP4728 I2C DACs (comments may still say DCO4 V1–V4; OSC3 has no DAC channel)
- **Wave select:** Dual 74HC595 mux (saw / saw2 / tri / sine); unused voice slots forced off
- **Serial:** 2.5 Mbaud to DCO (Serial2), Input (Serial8), Screen (Serial1); USB Serial @ 2 Mbaud for debug
- **Params:** Table-driven `ParamId` router; apply locally and/or forward to DCO
- **Manual calibration:** Special PWM/mux path when `manualCalibrationFlag` is set

**Not active today:** presets (owned by Input); `flashData` / BU2505 / `SPI_settings` live only under [`_removed/`](_removed/); Screen module and autotune includes off. `_removed/` is not compiled.

## Documentation

| Doc | Status | Contents |
|-----|--------|----------|
| [`docs/SYSTEM_OVERVIEW.md`](docs/SYSTEM_OVERVIEW.md) | Current | Local UART table; points to DCO system overview |
| [`docs/MODULATION_PIPELINE.md`](docs/MODULATION_PIPELINE.md) | Partially stale | Notes / params → ADSR/LFO → PWM/DAC → DCO serial (may still say DCO4 / 4-voice) |
| [`docs/CV_AND_PINS.md`](docs/CV_AND_PINS.md) | Current | Timer PWM, MCP4728, 74HC595, UART pins |
| [`docs/FILE_INDEX.md`](docs/FILE_INDEX.md) | Partially stale | File / function map (may still say DCO4 / 4-voice) |
| [`docs/REFERENCE_AI.md`](docs/REFERENCE_AI.md) | Partially stale | Deep semantic map (prefer this README for monosynth facts) |
| [`docs/README_serial_and_params.md`](docs/README_serial_and_params.md) | Current | Shared serial / ParamId how-to |

**Suggested reading order:** this README → DCO system overview → modulation / CV pins → FILE_INDEX or REFERENCE_AI (with stale-count caveat) → serial how-to.

## High-level architecture

| Subsystem | Files | Role |
|-----------|-------|------|
| Entry / loop | `DCO4_Mainboard_Controller.ino` | Init + soft-timer schedule |
| Serial RX | `Serial.ino`, `serial_*.h` | DCO notes/params; Input blocks/params; Screen RX stub |
| Serial TX | `Serial2.ino` | ADSR3 `'s'` + PW `'f'` flush; immediate `*Function` param forwards; Screen/Input `'x'` helpers |
| Params | `params.ino`, `params_def.h`, `param_router.h` | Apply + forward (incl. OSC3 33–35) |
| ADSR / LFO | `ADSR.*`, `LFO.*` | Envelope and LFO levels |
| Formulas | `formulas.*` | Depth/speed scalars |
| CV write | `PWM.ino`, `Timers.*`, `MCP4728.ino` | Timer PWM + I2C DACs |
| Waves | `waveSelector.*` | 74HC595 |

Hot path every `loop`: Serial2 → LFO1/2 → ADSR_update → setPWMOuts (or manual-cal). Details: [`docs/MODULATION_PIPELINE.md`](docs/MODULATION_PIPELINE.md).

## Hardware / UART summary

| Port | Pins | Baud | Peer |
|------|------|------|------|
| Serial | USB | 2 000 000 | Debug |
| Serial1 | PA10 / PA9 | 2 500 000 | Screen |
| Serial2 | PD6 / PD5 | 2 500 000 | DCO |
| Serial8 | PE0 / PE1 | 2 500 000 | Input |

I2C MCP4728: SDA **PB9**, SCL **PB8**, 1 MHz. Full CV pin table: [`docs/CV_AND_PINS.md`](docs/CV_AND_PINS.md).

## Building

- **Toolchain:** Arduino IDE / CLI with STM32 Arduino core (no FQBN checked in yet — board part TBD).
- **Sketch:** open `DCO4_Mainboard_Controller.ino`.
- **Libraries:** `ADSR_Bezier`, `mo-lfo`, `MCP4728_multiaddress`, `RoxMux`, `Wire`; optional `RunningAverage` if benchmarking.

### Feature flags

| Flag | Default | Effect |
|------|---------|--------|
| `NUM_VOICES` | **1** | Voice array sizes / live ADSR+LFO instances |
| `NUM_FILTERS` | **2** | Active filter CV outs; extras parked |
| `ENABLE_SD` | **on** (main sketch) | SDMMC pin reservation / TIM8 CH4 gating only (no live preset I/O) |
| `ENABLE_SPI` | **off** | SPI / BU2505 path removed to `_removed/` |
| `ENABLE_SERIAL*` | **on** (`Serial.h`) | Per-UART compile-in |
| `ENABLE_SCREEN` | **off** | Would call `initScreen()` |
| `RUNNING_AVERAGE` | **off** | Loop micro-benchmarks |
| `build_opt.h` | always | Larger Serial RX/TX buffers |

## Contributing / hacking

- Prefer this README for monosynth voice/filter counts until deep docs are refreshed.
- Keep `ParamId` numbers stable across boards (`params_def.h`).
- Route new controls through `params.ino` + serial protocol headers rather than ad-hoc UART bytes.
- When changing CV math, keep [`docs/CV_AND_PINS.md`](docs/CV_AND_PINS.md) and [`docs/MODULATION_PIPELINE.md`](docs/MODULATION_PIPELINE.md) in sync.
- Excised unused code lives under [`_removed/`](_removed/) and is not compiled.
