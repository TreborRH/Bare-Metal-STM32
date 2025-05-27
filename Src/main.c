#include <thertos.h>
#include <stdint.h>
#include <stdbool.h>
volatile bool isLED = true;
uint16_t pin = PIN('C', 9);
uint16_t pinExt = PIN('A', 0);

void ISR()
{
	gpio_write(pin, isLED);
	isLED = !isLED;
}

int main(void)
{
	gpio_init(pin, OUTPUT);
	gpio_init(pinExt, INPUT);
	init_Timer();
	attachInterrupt(pinExt, ISR, RISING);
	for(;;)
	{
	}
}



