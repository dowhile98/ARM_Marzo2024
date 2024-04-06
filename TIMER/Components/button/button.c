/*
 * button.c
 *
 *  Created on: Mar 11, 2024
 *      Author: jeffr
 */
#include "button.h"
/**
 *
 */
void button_init(Button_t *b, read_fc r, ticks_fc t, uint32_t db, uint16_t pin){
	b->debounceMs = db;
	b->read = r;
	b->ticks = t;
	b->old_state = 0;
	b->pressTime = 0;
	b->flags = 0;
	b->pin = pin;
}
/**
 *
 */
void button_update(Button_t *b){
	read_fc read;
	ticks_fc bt_getTcks;
	if(b->read == NULL || b->ticks == NULL){
		return;
	}
	read = b->read;
	bt_getTcks = b->ticks;

	uint8_t new_state = read(b->pin);
	/*state verify*/
	if(new_state != b->old_state){
		b->time_state_change = bt_getTcks();
	}
	else if(new_state){
		if(!(b->flags & ONPRESS_SENT)){
			//debounce
			if((bt_getTcks() - b->time_state_change)>= b->debounceMs){
				b->flags &=~ ONRELEASE_SENT;
				b->flags |= ONPRESS_SENT | ONPRESS_EVT;
				//
				b->keepalive.cnt = 0;
				b->keepalive.last_time = bt_getTcks();

				b->time_state_change = bt_getTcks();
				b->pressTime = 0;
			}
		}else{
			if((bt_getTcks() - b->keepalive.last_time)>= KEEP_ALIVE_PERIOD){
				b->keepalive.last_time = bt_getTcks();
				b->keepalive.cnt += 1;
				b->pressTime += KEEP_ALIVE_PERIOD;
			}
		}
	}else{
		if(b->flags & ONPRESS_SENT){
			b->pressTime = 0;
			b->flags &=~ (ONPRESS_SENT | ONPRESS_EVT | BUTTON_TIME_ONCE);
			b->flags |= ONRELEASE_SENT;
			b->time_state_change = bt_getTcks();
		}
	}
	b->old_state = new_state;
	return;
}
/**
 *
 */
bool button_on_press(Button_t *b){
	if(b->flags & ONPRESS_EVT){
		b->flags &=~ ONPRESS_EVT;
		return true;
	}
	return false;
}

/**
 *
 */
bool button_on_release(Button_t *b){
	if(b->flags & ONRELEASE_SENT){
		b->flags &=~ ONRELEASE_SENT;
		return true;
	}
	return false;
}
/**
 *
 */
bool button_press_time_is_greater(Button_t *b, uint32_t ms, bool once){
	if(once == true){
		if((b->pressTime >= ms) &&(!(b->flags & BUTTON_TIME_ONCE))){
			b->flags |= BUTTON_TIME_ONCE;
			return true;
		}
	}else{
		if(b->pressTime >= ms){
			return true;
		}
	}
	return false;
}