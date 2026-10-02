# CAN-Linked Rover

Two microcontrollers talking over a CAN bus. An ESP32 sends drive commands, and an Arduino Uno receives them and drives DC motors through an L298N H-bridge.

<img width="500" alt="CAN Rover" src="PASTE YOUR EXISTING IMAGE LINK HERE" />

## How it works

- The ESP32 acts as the primary brain and sends a drive command over CAN.
- The Arduino Uno receives it through an MCP2515 CAN module and sets the motor direction and speed.
- Direction is set with the L298N input pins, and speed is set with PWM on the enable pin.
- The ESP32 resends the command every 100 ms. If the Uno stops hearing commands for 300 ms, it stops the motor on its own.

## Hardware

- ESP32
- Arduino Uno
- 2x MCP2515 CAN modules
- L298N motor driver
- DC motor

## CAN message

- Bus speed: 500 kbps
- Message ID: `0x100`
- Data (2 bytes): direction (0 stop, 1 forward, 2 reverse) and speed (0-255)

## Wiring

| Board | Connection | Pin |
|---|---|---|
| ESP32 | CAN chip select | GPIO 5 |
| ESP32 | SPI (SCK, MISO, MOSI) | GPIO 18, 19, 23 |
| Uno | CAN chip select | D10 |
| Uno | SPI (SCK, MISO, MOSI) | D13, D12, D11 |
| Uno | L298N enable (PWM) | D5 |
| Uno | L298N IN1, IN2 | D6, D7 |
