# ledblink
Simple implementation of a single LED blinking for the Raspberry Pi, using the C programming language and the [WiringPi](http://wiringpi.com) library.

To set up circuit, connect a 220 ohm resistor to Raspberry Pi GPIO pin 17, positive leg of LED to other end of resistor, and negative end of LED to ground.

Program sets WiringPi pin 0 (which corresponds to Raspberry Pi GPIO 17) to HIGH for one second, turning LED on, then setting to low for one second, turning LED off.
