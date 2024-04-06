/*
 * stm32f4xx_it.c
 *
 *  Created on: Mar 11, 2024
 *      Author: jeffr
 */
#include "stm32f4xx.h"
#include "delay.h"
#include "button.h"
#include "hvac_ll_driver.h"
#include <string.h>
#include <stdlib.h>
#include "hvac_typedefs.h"
#include "dht.h"

extern usart_rx_data_t rxData;
extern Button_t sw1;
extern Button_t sw2;
extern uint8_t *pointer;
extern DHT_t am2301;

void EXTI4_IRQHandler(void){
	if(EXTI->PR & 1<<4){
		EXTI->PR |= 1<<4;
		//SENSOR UPDATE
		DHT_pinChangeCallback(&am2301);
	}
}
void SysTick_Handler(void){
	/**
	 *
	 */
	ticksUpdate(1);
	button_update(&sw1);
	button_update(&sw2);
	return;
}

void EXTI9_5_IRQHandler(void){
	if(EXTI->PR & 1<<PINX(CONTACT1)){
		EXTI->PR |= 1<<PINX(CONTACT1);
		//Todo

	}
	if(EXTI->PR & 1<<PINX(CONTACT2)){
		EXTI->PR |= 1<<PINX(CONTACT2);
		//Todo

	}
}

void HardFault_Handler(void){
	while(1){

	}
}

void USART2_IRQHandler(void){
	static uint8_t i = 0;
	if(USART2->SR & USART_SR_RXNE){//Byte disponible
		pointer[i] = USART2->DR;
		if(pointer[i] == 0xFF){
			//Consumir el dato
			memcpy((void *)&rxData, pointer, i + 1);
			i = 0;
			hvac_flags |= HVAC_RX_UART_DATA;
		}else{
			i += 1;
		}

	}
//	if(USART2->SR & USART_SR_IDLE){
//		USART2->SR &=~ USART_SR_IDLE;
//		// Ejecutar
//		if(pointer[i] == 0xFF){
//			//Consumir el dato
//			memcpy((void *)&rxData, pointer, i + 1);
//			i = 0;
//			hvac_flags |= HVAC_RX_UART_DATA;
//		}
//	}
}
