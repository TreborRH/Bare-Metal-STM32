#include "gpio.h"
#include "timer.h"
#include <stdint.h>
#include <stdbool.h>
#include "interrupt.h"
volatile bool isLED = true;
uint16_t pin = PIN('C', 9);
uint16_t pinExt = PIN('D', 2);
volatile void ISR()
{
	gpio_write(pin, isLED);
	isLED = !isLED;
}

int main(void)
{


	gpio_init(pin, OUTPUT);
	init_Timer();


	gpio_init(pinExt, INPUT);
	attachInterrupt(pinExt, ISR, RISING);

	for(;;)
	{

	}


}

