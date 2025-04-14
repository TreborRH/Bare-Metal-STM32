/*
 * timer.c
 *
 *  Created on: Apr 13, 2025
 *      Author: capta
 */

#include "timer.h"

#include "interrupt.h"

volatile unsigned long millis = 0;

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
