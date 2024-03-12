/*
 * delay.h
 *
 *  Created on: Mar 11, 2024
 *      Author: jeffr
 */

#ifndef DELAY_DELAY_H_
#define DELAY_DELAY_H_

#include <stdlib.h>
#include <stdint.h>
/**
 * @brief
 */
void delay_ms(uint32_t delay);
/**
 * @brief
 */
uint32_t getTicks(void);

/**
 * @brief
 */
void ticksUpdate(uint32_t ms);

#endif /* DELAY_DELAY_H_ */