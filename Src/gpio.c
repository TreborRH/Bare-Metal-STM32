#include "gpio.h"
#include <stdint.h>
#include <stdbool.h>

struct GPIO *gpio[] =
{
		(struct GPIO*) GPIOA,
		(struct GPIO*) GPIOB,
		(struct GPIO*) GPIOC,
		(struct GPIO*) GPIOD,
		(struct GPIO*) GPIOE,
		(struct GPIO*) GPIOF,
		(struct GPIO*) GPIOG
};

void gpio_write(uint16_t pin , bool val)
{

	if(val)
	{
		gpio[PINPORT(pin)]->BSRR = 1 << PINNO(pin);
	}
	else
	{
		gpio[PINPORT(pin)]->BSRR = 1 << (PINNO(pin) + 16);
	}
}
void gpio_init(uint16_t pin, MODE mode)
{
	RCC_AHBENR |= 1 << PINPORT(pin); //setting clock port

	gpio[PINPORT(pin)]->MODER &= ~(3 << PINNO(pin) * 2); //clearing MODER
	gpio[PINPORT(pin)]->MODER |= mode << (PINNO(pin) * 2); //setting MODER to mode
}

