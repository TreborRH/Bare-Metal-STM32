#include "gpio.h"
#include "timer.h"
#include <stdint.h>
#include <stdbool.h>


int main(void)
{
	unsigned long startTime = 0;
	uint16_t pin = PIN('C', 9);

	gpio_init(pin, OUTPUT);
	bool isLed = false;


	isLed = !isLed;
	gpio_write(pin, isLed);

	init_Timer();

	for(;;)
	{
		if(millis - startTime > 1000)
		{
			startTime = millis;
			isLed = !isLed;
			gpio_write(pin, isLed);
		}
	}
}
