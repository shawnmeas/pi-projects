/*
Des	: Basic blink function of LED with GPIO
Author	: Shawn Meas
*/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


//Clean exit on SIGINT
void sigint_handler(int sig_num)
{
	printf("\nSIGINT received, exiting...\n");

	//Set all wiringPi pins to low
	for(int i=0;i<=16;i++)
	{
		digitalWrite(i, LOW);
	}
	for(int i=21;i<=31;i++)
	{
		digitalWrite(i, LOW);
	}

	exit(0);
}

int main()
{
	//Defining array with LED pin numbers
	//Done to account for WiringPi pins being out of order
	int pin[10] = {0, 1, 2, 3, 4, 5, 6, 7, 26, 27};

	int counter = 0;
	int interval;
	char input[10];
	char *ptr;

	//Run clean exit when SIGINT received
	signal(SIGINT, sigint_handler);

	//Set all pins to OUTPUT mode
	wiringPiSetup();
	for(int i=0;i<10;i++)
	{
		pinMode(pin[i], OUTPUT);
	}

	printf("Running 'counter' program...\n");

	//Get user input for counter interval with fgets, then convert to int
	//Also do error checking, and if error, set to default
	printf("Counter interval in milliseconds (minimum: 50) [Default: 1000]: ");
	fgets(input, 10, stdin);
	interval = strtol(input, &ptr, 10);

	if(interval == 0)
	{
		printf("\nInterval set to default\n");
		interval = 1000;
	}
	else if(interval < 50)
	{
		printf("\nInterval out of range, setting to default\n");
		interval = 1000;
	}
	else
	{
		printf("\nInterval set to %d milliseconds.\n", interval);
	}

	printf("%d\n", counter);
	delay(interval);
	while(1)
	{
		//Iterate through pins, turning on next every 1000ms
		for(int i=0;i<10;i++)
		{
			digitalWrite(pin[i], HIGH);
			counter++;
			printf("%d\n", counter);
			delay(interval);
		}

		//Turn off all pins but 0 (for counter to be read properly)
		for(int i=1;i<10;i++)
		{
			digitalWrite(pin[i], LOW);
		}
	}
	return 0;
}

