/*
 * interrupt.h
 *
 *  Created on: Apr 14, 2025
 *      Author: capta
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#define NVIC_ISER_BASE 0xE000E100 // Basisadresse des ISER
#define EXTI_BASE 0x40010400
#define SYSCFG_BASE 0x40010000

typedef struct
{
	uint32_t MEMRMP, PMC;
	uint32_t EXTICR[4];
}SYSCFG_TYPE;
typedef struct
{
	uint32_t IMR, EMR, RTSR, FTSR, SWIER, PR;
}EXTI_TYPE;

typedef enum EDGE
{
	RISING,
	FALLING
}EDGE;

void attachInterrupt(uint16_t, void (*)(void), EDGE);

void detachInterrupt(uint16_t);
#endif /* INTERRUPT_H_ */
