/*
 * interrupt.c
 *
 *  Created on: Apr 14, 2025
 *      Author: capta
 */

#include <stdint.h>
#include "interrupt.h"
#include "gpio.h"
#include "timer.h"

void (*userInterruptFunc[16])(void) = {0};

unsigned long tiStart[16] = {0}; //Timer Interrupt start for every EXTI

EXTI_TYPE *EXTI = (EXTI_TYPE *) (EXTI_BASE);
SYSCFG_TYPE *SYSCFG = (SYSCFG_TYPE *) (SYSCFG_BASE);

void NVIC_EnableIRQ(uint8_t IRQn)
{
    volatile uint32_t *ISER = (volatile uint32_t *)(NVIC_ISER_BASE + (IRQn / 32) * 4);
    *ISER = (1 << (IRQn % 32)); // Activates the Interrupt
}

void attachInterrupt(uint16_t pin, void (*func)(), EDGE edge)
{


	int line = PINNO(pin);

	EXTI->IMR |= 1 << line; //unmask EXTI Line

	userInterruptFunc[line] = func;

	switch(edge)
	{
		case RISING:
			EXTI->RTSR |= 1 << line; //Activating rising Edge for the pins with the number {line}.
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

void HandleExti(uint16_t exti)
{
	if((unsigned long)(millis - tiStart[exti]) > 50) //Debounce
	{
		if(EXTI->PR & (1 << exti))
		{
			userInterruptFunc[exti]();
			EXTI->PR = (1 << exti); //Reset Interrupt
		}
		tiStart[exti] = millis;
	}
}


void EXTI0_IRQHandler()
{
	HandleExti(0);
}
void EXTI1_IRQHandler()
{
	HandleExti(1);
}
void EXTI2_IRQHandler()
{
	HandleExti(2);
}
void EXTI3_IRQHandler()
{
	HandleExti(3);
}
void EXTI4_IRQHandler()
{
	HandleExti(4);
}
void EXTI9_5_IRQHandler() //EXTI5-9
{
	for(int i = 5; i < 10; i++)
	{
		HandleExti(i);
	}
}

void EXTI15_10_IRQHandler() //EXTI10-15
{
	for(int i = 10; i < 16; i++)
	{
		HandleExti(i);
	}
}

