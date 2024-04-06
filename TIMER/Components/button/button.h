/*
 * button.h
 *
 *  Created on: Mar 11, 2024
 *      Author: jeffr
 */

#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_

#ifdef __cplusplus
extern "C"{
#endif
/*Includes -----------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
/*Defines ------------------------------------------------------*/
#define KEEP_ALIVE_PERIOD		100
/*Typedefs -----------------------------------------------------*/
typedef uint8_t(*read_fc)(uint8_t pin);
typedef uint32_t (*ticks_fc)(void);

typedef enum{
	ONPRESS_SENT = 1,
	ONRELEASE_SENT = 1<<1,
	ONPRESS_EVT	= 1<<3,
	BUTTON_TIME_ONCE  = 1<<4
}Button_flags_t;


typedef struct{
	uint16_t pin;
	read_fc read;
	ticks_fc ticks;
	uint32_t pressTime;
	uint8_t old_state;
	uint32_t time_state_change;
	uint8_t flags;
	uint32_t debounceMs;
	struct{
		uint32_t last_time;
		uint16_t cnt;
	}keepalive;
}Button_t;
/*Function prototype -------------------------------------------*/
/**
 *
 */
void button_init(Button_t *b, read_fc r, ticks_fc t, uint32_t db, uint16_t pin);
/**
 *
 */
void button_update(Button_t *b);
/**
 *
 */
bool button_on_press(Button_t *b);

/**
 *
 */
bool button_on_release(Button_t *b);
/**
 *
 */
bool button_press_time_is_greater(Button_t *b, uint32_t ms, bool once);

#ifdef __cplusplus
}
#endif

#endif /* BUTTON_BUTTON_H_ */
