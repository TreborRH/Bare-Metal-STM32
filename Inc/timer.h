/*
 * timer.h
 *
 *  Created on: Apr 13, 2025
 *      Author: capta
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

extern volatile unsigned long millis;

#define RCC_APB1ENR (*(volatile uint32_t*) 0x40023824)
#define TIM2_PSC 	(*(volatile uint32_t*) 0x40000028)
#define TIM2_ARR 	(*(volatile uint32_t*) 0x4000002C)
#define TIM2_DIER 	(*(volatile uint32_t*) 0x4000000C)
#define TIM2_CR1	(*(volatile uint32_t*) 0x40000000)
#define TIM2_SR		(*(volatile uint32_t*) 0x40000010)

#endif /* TIMER_H_ */
