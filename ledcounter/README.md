# ledcounter
Base 10 LED counter for the Raspberry Pi, using the C programming language and the [WiringPi](https://github.com/WiringPi/WiringPi) library.

Circuit consists of 10 LEDs and 220 ohm resistors, connected to WiringPi pins 0, 1, 2, 3, 4, 5, 6, 7, 26, and 27 (as 8 and 9 aren't properly suitable for GPIO purposes).

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
| WiringPi 8   | GPIO 12  |
| WiringPi 9   | GPIO 16  |
