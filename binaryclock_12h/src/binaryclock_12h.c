/*
Desc	: Basic 10 LED binary clock
Author	: Shawn Meas
*/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>


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

/* TODO
	Look into combining hr_to_binary and min_to_binary, as logic is the same.
	Only difference is array size.
*/

//Function to convert hour integer value to binary value
int * hr_to_binary(int input)
{
	static int binary[4];
	int remainder;
	for(int i=3;i>=0;i--)
	{
		if(input == 0)
		{	
			binary[i] = 0;
		}
		else
		{
			remainder = input % 2;
			if(remainder == 0)
			{
				binary[i] = 0;
			}
			else
			{
				binary[i] = 1;
			}
			input = input / 2;
		}
	}
	return binary;
}

//Function to convert minute integer value to binary value
int * min_to_binary(int input)
{
	static int binary[6];
	int remainder;
	for(int i=5;i>=0;i--)
	{
		if(input == 0)
		{	
			binary[i] = 0;
		}
		else
		{
			remainder = input % 2;
			if(remainder == 0)
			{
				binary[i] = 0;
			}
			else
			{
				binary[i] = 1;
			}
			input = input / 2;
		}
	}
	return binary;
}

int main()
{
	//Run clean exit when SIGINT received
	signal(SIGINT, sigint_handler);

	//Initializing time variables
	time_t rawtime;
	struct tm *currenttime;
	int hr, min, sec;
	int old_hr, old_min, old_sec;
	bool is_pm;

	//Defining arrays for GPIO pin numbers (using WiringPi numbers)
	//In reverse order to correctly show binary numbers
	int hr_pin[4] = {3, 2, 1, 0};
	int min_pin[6] = {27, 26, 7, 6, 5, 4};
	int ampm_pin = 25;

	//Declaring arrays for hour and minute binary values
	int *hr_binary;
	int *min_binary;

	//Set all pins to OUTPUT mode
	wiringPiSetup();
	for(int i=0;i<6;i++)
	{
		if(i < 4)
		{
			pinMode(hr_pin[i], OUTPUT);
		}
		pinMode(min_pin[i], OUTPUT);
	}
	pinMode(ampm_pin, OUTPUT);

	printf("Running 'binaryclock' program...\n\n");

	//Get current time in hours, minutes, seconds as integers, and print time
	time(&rawtime);
	currenttime = localtime(&rawtime);
	hr = currenttime->tm_hour;
	min = currenttime->tm_min;
	sec = currenttime->tm_sec;

	//Logic to convert 24 hour value to 12 hour value and set is_pm if > 12
	if(hr < 12)
	{
		is_pm = false;
		if(hr == 0)
		{
			hr = 12;
		}
	}
	else if(hr >= 12)
	{
		is_pm = true;
		if(hr != 12)
		{
			hr = hr - 12;
		}
	}

	printf("Current time: %02d:%02d:%02d ", hr, min, sec);
	if(is_pm == false)
	{
		printf("AM\n");
	}
	else if (is_pm == true)
	{
		printf("PM\n");
	}
	
	//Set old values for time to current time values
	//Used to check if time has changed
	old_hr = hr;
	old_min = min;
	old_sec = sec;
	
	//Convert hr and min ints to binary
	hr_binary = hr_to_binary(hr);
	min_binary = min_to_binary(min);

	//Set hour LEDs
	for(int i=0;i<4;i++)
	{
		if(hr_binary[i] == 1)
		{
			digitalWrite(hr_pin[i], HIGH);
		}
		else if(hr_binary[i] == 0)
		{
			digitalWrite(hr_pin[i], LOW);
		}
	}

	//Set minute LEDs
	for(int i=0;i<6;i++)
	{
		if(min_binary[i] == 1)
		{
			digitalWrite(min_pin[i], HIGH);
		}
		else if(min_binary[i] == 0)
		{
			digitalWrite(min_pin[i], LOW);
		}
	}

	while(1)
	{
		//Get current time at start of loop
		time(&rawtime);
		currenttime = localtime(&rawtime);
		hr = currenttime->tm_hour;
		min = currenttime->tm_min;
		sec = currenttime->tm_sec;

		if(hr < 12)
		{
			is_pm = false;
			if(hr == 0)
			{
				hr = 12;
			}
		}
		else if(hr >= 12)
		{
			is_pm = true;
			if(hr != 12)
			{
				hr = hr - 12;
			}
		}

		//Set pin to indicate PM
		if(is_pm == false)
		{
			digitalWrite(ampm_pin, LOW);
		}
		else if(is_pm == true)
		{
			digitalWrite(ampm_pin, HIGH);
		}
		
		//Check if any time values have changed.
		//If second value has changed, print new time
		//Works for changing minutes and hours as well, as a second change is the smallest increment
		if(sec != old_sec)
		{
			if(min != old_min)
			{
				if(hr != old_hr)
				{
					//If hour has changed, get new binary value for hour, and set LEDs
					hr_binary = hr_to_binary(hr);

					for(int i=0;i<4;i++)
					{
						if(hr_binary[i] == 1)
						{
							digitalWrite(hr_pin[i], HIGH);
						}
						else if(hr_binary[i] == 0)
						{
							digitalWrite(hr_pin[i], LOW);
						}
					}
					old_hr = hr;
				}

				//If minute has changed, get new binary value for minute, and set LEDs
				min_binary = min_to_binary(min);
				for(int i=0;i<6;i++)
				{
					if(min_binary[i] == 1)
					{
						digitalWrite(min_pin[i], HIGH);
					}
					else if(min_binary[i] == 0)
					{
						digitalWrite(min_pin[i], LOW);
					}
				}
				old_min = min;
			}
			old_sec = sec;
			printf("Current time: %02d:%02d:%02d ", hr, min, sec);
			if(is_pm == false)
			{
				printf("AM\n");
			}
			else if (is_pm == true)
			{
				printf("PM\n");
			}
		}
		

	}

	return 0;
}

