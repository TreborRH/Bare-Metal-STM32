/*
 * timer.c
 *
 *  Created on: Apr 13, 2025
 *      Author: capta
 */

#include "timer.h"

volatile unsigned long millis = 0;

#define NVIC_ISER_BASE 0xE000E100 // Basisadresse des ISER

void NVIC_EnableIRQ(uint8_t IRQn)
{
    volatile uint32_t *ISER = (volatile uint32_t *)(NVIC_ISER_BASE + (IRQn / 32) * 4);
    *ISER = (1 << (IRQn % 32)); // Aktiviert den Interrupt
}



void init_Timer()
{
	RCC_APB1ENR |= 1; //sets TIM2 active

	TIM2_PSC = 1048; //prescaler / MSI clock 1048MHz
	TIM2_ARR = 1; //auto reload register

	TIM2_DIER = 1; //activate update interrupt

	TIM2_CR1 |= 1; // Start timer


	NVIC_EnableIRQ(28); // TIM2 hat IRQ-Nummer 28
}

void TIM2_IRQHandler(void)
{
	if(TIM2_SR & 1) //Check SR UIF
	{
		TIM2_SR &= ~(1); //Clear SR UIF
		millis++;
	}
}
