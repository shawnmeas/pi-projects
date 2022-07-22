/*
Des	: Basic blink function of LED with GPIO
Author	: Shawn Meas
*/

#include <wiringPi.h>
#include <stdio.h>

//Set pin number for LED
#define ledPin 0

int main()
{
	printf("Running 'blink' program...\n");

	wiringPiSetup();

	pinMode(ledPin, OUTPUT);
	printf("Running on pin %d\n", ledPin);

	while(1)
	{
		//Turn on LED for 1000ms
		digitalWrite(ledPin, HIGH);
		delay(1000);

		//Turn off LED for 1000ms
		digitalWrite(ledPin, LOW);
		delay(1000);
	}
}

