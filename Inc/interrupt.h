/*
 * interrupt.h
 *
 *  Created on: Apr 14, 2025
 *      Author: capta
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#define NVIC_ISER_BASE 0xE000E100 //adress of ISER
#define EXTI_BASE 0x40010400

#define SYSCFG_BASE 0x40010000

#define DEBOUNCETIME 100

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

void NVIC_EnableIRQ(uint8_t);
#endif /* INTERRUPT_H_ */
