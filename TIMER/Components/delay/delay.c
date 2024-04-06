/*
 * delay.c
 *
 *  Created on: Mar 11, 2024
 *      Author: jeffr
 */

#include "delay.h"


volatile uint32_t uwTicks = 0;
/**
 * @brief
 */
void delay_ms(uint32_t delay){
	uint32_t tickStart = getTicks();
	while((getTicks() - tickStart)< delay){

	}
	return;
}
/**
 * @brief
 */
uint32_t getTicks(void){
	return uwTicks;
}

/**
 * @brief
 */
void ticksUpdate(uint32_t ms){
	uwTicks += ms;
	return;
}