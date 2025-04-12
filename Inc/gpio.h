#ifndef GPIO_H
#define GPIO_H

#include<stdint.h>
#include <stdbool.h>


#define GPIOA (0x40020000)
#define GPIOB (0x40020400)
#define GPIOC (0x40020800)
#define GPIOD (0x40020C00)
#define GPIOE (0x40021000)
#define GPIOF (0x40021400)
#define GPIOG (0x40021800)

typedef struct GPIO
{
	uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR, AFRL, AFRH, BRR;
} GPIO;

typedef enum MODE
{
	INPUT,
	OUTPUT,
	ALT,
	ANALOG
} MODE;

#define PIN(port, num) (((int)port - 65) << 8) | (num) //creates a 16bit sized container saving the port in the first 8 bits and the pin number in the last 8
#define PINNO(pin) ((pin) & 255)	//Extracts the Pin number out of the pin
#define PINPORT(pin) ((pin) >> 8)	//Extracts the Pin port out of the pin

#define RCC_AHBENR (*(volatile uint32_t*) 0x4002381C)

void gpio_write(uint16_t, bool);

void gpio_init(uint16_t, MODE);

extern struct GPIO *gpio[];

#endif
