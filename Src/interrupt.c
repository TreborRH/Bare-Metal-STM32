/*
 * interrupt.c
 *
 *  Created on: Apr 14, 2025
 *      Author: capta
 */

#include <stdint.h>
#include "interrupt.h"
#include "gpio.h"

void (*userInterruptFunc[16])(void) = {0};

EXTI_TYPE *EXTI = (EXTI_TYPE *) (EXTI_BASE);
SYSCFG_TYPE *SYSCFG = (SYSCFG_TYPE *) (SYSCFG_BASE);

void NVIC_EnableIRQ(uint8_t IRQn)
{
    volatile uint32_t *ISER = (volatile uint32_t *)(NVIC_ISER_BASE + (IRQn / 32) * 4);
    *ISER = (1 << (IRQn % 32)); // Aktivates the Interrupt
}

void attachInterrupt(uint16_t pin, void (*func)(), EDGE edge)
{


	int line = PINNO(pin);

	EXTI->IMR |= 1 << line; //unmask EXTI Line

	userInterruptFunc[line] = func;

	switch(edge)
	{
		case RISING:
			EXTI->RTSR |= 1 << line; //Activating rising Edge for the pins with number line.
			break;
		case FALLING:
			EXTI->FTSR |= 1 << line;
			break;
	}

	//ACTIVATING THE CORRECT PIN IN SYSCFG
	SYSCFG->EXTICR[line/4] |= PINPORT(pin) << ((line%4) * 4);

	switch(line)
	{
		case 0:
			NVIC_EnableIRQ(6);
			break;
		case 1:
			NVIC_EnableIRQ(7);
			break;
		case 2:
			NVIC_EnableIRQ(8);
			break;
		case 3:
			NVIC_EnableIRQ(9);
			break;
		case 4:
			NVIC_EnableIRQ(10);
			break;
		default:
			if(line > 4 && line < 10)
			{
				NVIC_EnableIRQ(23);
			}
			else if(line > 9 && line < 16)
			{
				NVIC_EnableIRQ(40);
			}
	}
}
void detachInterrupt(uint16_t pin)
{
	int line = PINNO(pin);
	EXTI->RTSR &= ~(1 << line);
	EXTI->FTSR &= ~(1 << line);
	EXTI->IMR &= ~(1 << line);
	SYSCFG->EXTICR[line/4] &= ~(15 << ((line%4) * 4));
}
void EXTI0_IRQHandler()
{
	userInterruptFunc[0]();
	EXTI->PR &= ~(1);
}
void EXTI1_IRQHandler()
{
	userInterruptFunc[1]();
	EXTI->PR &= ~(1 << 1);
}
void EXTI2_IRQHandler()
{
	userInterruptFunc[2]();
	EXTI->PR &= ~(1 << 2);
}
void EXTI3_IRQHandler()
{
	userInterruptFunc[3]();
	EXTI->PR &= ~(1 << 3);
}
void EXTI4_IRQHandler()
{
	userInterruptFunc[4]();
	EXTI->PR &= ~(1 << 4);
}
void EXTI9_5_IRQHandler() //EXTI5-9
{
	//Check which EXTI triggered
	if(EXTI->PR & (1 << 5))
	{
		userInterruptFunc[5]();
		EXTI->PR &= ~(1 << 5);
	}
	if(EXTI->PR & (1<<6))
	{
		userInterruptFunc[6]();
		EXTI->PR &= ~(1 << 6);
	}
	if(EXTI->PR & (1<<7))
	{
		userInterruptFunc[7]();
		EXTI->PR &= ~(1 << 7);
	}
	if(EXTI->PR & (1<<8))
	{
		userInterruptFunc[8]();
		EXTI->PR &= ~(1 << 8);
	}
	if(EXTI->PR & (1<<9))
	{
		userInterruptFunc[9]();
		EXTI->PR &= ~(1 << 9);
	}
}

void EXTI15_10_IRQHandler() //EXTI10-15
{
	if(EXTI->PR & (1 << 10))
	{
		userInterruptFunc[10]();
		EXTI->PR &= ~(1 << 10);
	}
	if(EXTI->PR & (1<<11))
	{
		userInterruptFunc[11]();
		EXTI->PR &= ~(1 << 11);
	}
	if(EXTI->PR & (1<<12))
	{
		userInterruptFunc[12]();
		EXTI->PR &= ~(1 << 12);
	}
	if(EXTI->PR & (1<<13))
	{
		userInterruptFunc[13]();
		EXTI->PR &= ~(1 << 13);
	}
	if(EXTI->PR & (1<<14))
	{
		userInterruptFunc[14]();
		EXTI->PR &= ~(1 << 14);
	}
	if(EXTI->PR & (1<<15))
	{
		userInterruptFunc[15]();
		EXTI->PR &= ~(1 << 15);
	}
}

