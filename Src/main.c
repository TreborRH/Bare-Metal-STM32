#include "gpio.h"
#include <stdint.h>
#include <stdbool.h>

int main(void)
{
	uint16_t pin = PIN('C', 9);

	gpio_init(pin, OUTPUT);
	gpio_write(pin, true);



    /* Loop forever */
	for(;;);
}
