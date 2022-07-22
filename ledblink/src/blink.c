/*
Des	: Basic blink function of LED with GPIO
Author	: Shawn Meas
*/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

//Set pin number for LED
#define ledPin 0

//Clean exit on SIGINT
void sigint_handler(int sig_num)
{
	printf("\nSIGINT received, exiting...\n");

	//Set all wiringPi pins to low
	for(int i=0;i<=16;i++)
	{
		digitalWrite(i, LOW);
	}

	exit(0);
}

int main()
{
	//Run clean exit when SIGINT received
	signal(SIGINT, sigint_handler);

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

