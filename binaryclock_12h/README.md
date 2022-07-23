# binaryclock\_12h
Binary clock (12 hour AM/PM format) for the Raspberry Pi, using the C programming language and the [WiringPi](https://github.com/WiringPi/WiringPi) library.

Circuit consists of 11 LEDs (1 to indicate AM/PM, 4 for hours, and 6 for minutes) and 220 ohm resistors, connected to WiringPi pins 0, 1, 2, 3, 4, 5, 6, 7, 25, 26, and 27.

WiringPi to GPIO mappings are as follows.

| WiringPi Pin | GPIO Pin |
| ------------ | -------- |
| WiringPi 0   | GPIO 17  |
| WiringPi 1   | GPIO 18  |
| WiringPi 2   | GPIO 27  |
| WiringPi 3   | GPIO 22  |
| WiringPi 4   | GPIO 23  |
| WiringPi 5   | GPIO 24  |
| WiringPi 6   | GPIO 25  |
| WiringPi 7   | GPIO 4   |
| WiringPi 25  | GPIO 26  |
| WiringPi 26  | GPIO 12  |
| WiringPi 27  | GPIO 16  |
