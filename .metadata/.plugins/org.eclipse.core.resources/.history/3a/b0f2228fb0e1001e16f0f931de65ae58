/*
 * stm32f4xx_it.c
 *
 *  Created on: Mar 11, 2024
 *      Author: jeffr
 */
#include "stm32f4xx.h"
#include "delay.h"
#include "button.h"

extern Button_t sw1;
extern Button_t sw2;

void SysTick_Handler(void){
	/**
	 *
	 */
	ticksUpdate(1);
	button_update(&sw1);
	button_update(&sw2);
	return;
}

