/*
 * delay.h
 *
 *  Created on: Mar 11, 2024
 *      Author: jeffr
 */

#ifndef DELAY_DELAY_H_
#define DELAY_DELAY_H_

#ifdef __cplusplus
extern "C"{
#endif

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


#ifdef __cplusplus
}
#endif
#endif /* DELAY_DELAY_H_ */
