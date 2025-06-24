# STM32F4 LED Blinky (Bare Metal)

This is a simple bare-metal project for STM32F407 (or similar), demonstrating:

- Manual register manipulation
- GPIO setup
- LED toggling (PD15)
- Minimal delay loop

## Requirements

- STM32F407 board (e.g., STM32F4 Discovery)
- STM32CubeIDE or any ARM GCC toolchain
- ST-Link (or debugger) to flash

## Pinout

- **PD15**: Onboard LED (Blue on STM32F4 Disco)

## How it works

1. Enables the peripheral clock for GPIOD.
2. Configures pin 15 of port D as output.
3. Toggles PD15 in an infinite loop with delay.

## License

MIT or your preferred license.
