/*
 * dht.c
 *
 *  Created on: Mar 25, 2024
 *      Author: jeffr
 */


#include "dht.h"
#include <string.h>
/*Private function -----------------------------------*/

static bool DHT_decode(DHT_t *dht, uint8_t *byte){
	int8_t bit;
	uint8_t type  = dht->type;
	switch(type){
	case DHT_Type_DHT21:
	case DHT_Type_AM2301:
	case DHT_Type_AM2305:
		if((dht->data[0]<60) || (dht->data[0]> 100) || (dht->data[1] <60) || (dht->data[1]>100)){
			return false;
		}
		bit = 7;
		for(uint8_t i = 0; i < 80; i += 2){
			if((dht->data[i + 2]>= 35) && (dht->data[i + 2]<= 70)){
				if((dht->data[i + 3]>= 10) && (dht->data[i+ 3]<= 45)){
					*byte &=~ (1<<bit);
				}else if((dht->data[i +3]>= 55) && (dht->data[i +3]<= 95)){
					*byte |= 1<<bit;
				}else{
					return false;
				}
				bit -= 1;
				if(bit == -1){
					bit = 7;
					byte++;
				}
			}else{
				return false;
			}
		}
		break;
	default:
		return false;
	}
	return true;
}
static void dht_output(DHT_t *dht){
	/**
	 * configurar el pin como salida
	 */
	dht->GPIO->MODER &=~ (0x3<< (dht->pin * 2));
	dht->GPIO->MODER |= 0x1<<(2 * dht->pin);
	dht->GPIO->OSPEEDR |= 0x3<<(2 * dht->pin);
	dht->GPIO->BSRR |= 1<<dht->pin;
	return;
}

static void dht_input(DHT_t *dht){
	/**
	 * pin como entrada
	 */
	dht->GPIO->MODER &=~ (0x3<<(2 * dht->pin));
	return;
}

static void dht_delay_us(DHT_t *dht, uint16_t delayus){
	dht->TIM->CNT = 0;
	while(dht->TIM->CNT < delayus);
	return;
}
/*Function definition --------------------------------*/

bool DHT_pinChangeCallback(DHT_t *dht){

	dht->time = getTicks();
	if(dht->cnt < sizeof(dht->data) - 1){
		dht->data[dht->cnt] = dht->TIM->CNT - dht->lastCNT;
		dht->lastCNT = dht->TIM->CNT;
		dht->cnt += 1;
	}else{
		return false;
	}
	return true;
}

void DHT_Init(DHT_t *dht, GPIO_TypeDef *P, uint16_t pin, TIM_TypeDef *tim, DHT_Type_t type){
	memset(dht, 0, sizeof(DHT_t));
	dht->GPIO = P;
	dht->pin = pin;
	dht->TIM = tim;
	dht->type = type;
	//pin inicia en modo salida
	dht_output(dht);
	delay_ms(200);
	return;
}

bool DHT_readData(DHT_t *dht, float *temp, float *hum){
	uint32_t startTime;
	uint8_t type  = dht->type;
	switch(type){
	case DHT_Type_DHT21:
	case DHT_Type_AM2301:
	case DHT_Type_AM2305:
		/**
		 * pin como salida y estado alto
		 */
		dht_output(dht);
		// se pone a bajo el pin
		dht->GPIO->BSRR |= 1<<(dht->pin + 16);
		delay_ms(5);
		//se pone a alto
		dht->GPIO->BSRR |= 1<<dht->pin;

		dht_delay_us(dht, 20);

		dht->GPIO->BSRR |= 1<<(dht->pin + 16);

		dht_delay_us(dht, 5);

		dht->cnt = 0;
		dht->lastCNT = 0;
		dht->TIM->CNT = 0;

		startTime = getTicks();

		/**
		 * configurar el pin como entrada
		 */
		dht_input(dht);

		while(1){
			if((getTicks() - startTime)> 8){ //8ms
				break;
			}
			if((getTicks() - dht->time)>1){
				uint8_t data[5];
				if(DHT_decode(dht, data) == false){
					break;
				}
				if(((data[0] + data[1] + data[2] + data[3]) & 0xFF) != data[4]){
					break;
				}
				dht->temperature = (float)(data[2] * 256 + data[3])/10.0;
				dht->humidity = (float)(data[0] * 256 + data[1])/10.0;

				*temp = dht->temperature;
				*hum = dht->humidity;
				dht->dataValid = true;
				/**
				 * pin como salida
				 */
				dht_output(dht);
				return true;
			}
		}
		break;
	}
	dht->dataValid = false;
	dht_output(dht);
	return false;
}
