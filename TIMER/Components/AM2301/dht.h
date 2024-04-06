/*
 * dht.h
 *
 *  Created on: Mar 25, 2024
 *      Author: jeffr
 */

#ifndef AM2301_DHT_H_
#define AM2301_DHT_H_

#ifdef __plusplus
extern "C"{
#endif

/*Inludes -------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stm32f4xx.h>
#include <delay.h>
/*Defines ------------------------------------------*/

/*Typedefs -----------------------------------------*/
typedef enum
{
  DHT_Type_DHT11 = 0,
  DHT_Type_DHT12,
  DHT_Type_DHT21,
  DHT_Type_DHT22,
  DHT_Type_AM2301,
  DHT_Type_AM2305

}DHT_Type_t;




typedef struct{
	GPIO_TypeDef *GPIO;
	uint16_t pin;
	TIM_TypeDef *TIM;
	DHT_Type_t type;
	uint8_t data[84];
	uint16_t cnt;
	uint32_t time;
	uint32_t lastCNT;
	float temperature;
	float humidity;
	bool dataValid;
}DHT_t;

/*Function prototype -------------------------------*/
bool DHT_pinChangeCallback(DHT_t *dht);

void DHT_Init(DHT_t *dht, GPIO_TypeDef *P, uint16_t pin, TIM_TypeDef *tim, DHT_Type_t type);

bool DHT_readData(DHT_t *dht, float *temp, float *hum);

#ifdef __plusplus
}
#endif

#endif /* AM2301_DHT_H_ */
