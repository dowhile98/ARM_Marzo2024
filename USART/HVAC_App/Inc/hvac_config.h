/*
 * hvac_config.h
 *
 *  Created on: Mar 8, 2024
 *      Author: jeffr
 */

#ifndef INC_HVAC_CONFIG_H_
#define INC_HVAC_CONFIG_H_


#ifdef __cplusplus
extern "C"{
#endif
/**
 * Pines donde van conectado los botones
 */
#define SW1			A, 0
#define SW2			A, 1
/**
 * Pines donde van conectado la lectura de los contactos
 */
#define CONTACT1	B, 6
#define CONTACT2	B, 7
/**
 * Pines donde van conectados los relays
 */
#define RELAY1		D, 12
#define RELAY2		D, 13
/**
 * Pines donde van conectado la LCD
 */
#define LCD_RS		C, 11
#define LCD_EN		C, 12
#define LCD_D4		D, 0
#define LCD_D5		D, 1
#define LCD_D6		D, 2
#define LCD_D7		D, 3
/**
 * Alarma de contacto
 */
#define A_CONTACT	B, 7
/**
 * Led de estado
 */
#define STATUS		D, 14

/**
 * CONTACT IT PRIORITY
 */
#define CONTACT1_PRI	2
#define CONTACT2_PRI	3

/**
 * UART
 */
#define USART2_TX		A, 2
#define USART2_RX 		A, 3


#ifdef __cplusplus
}
#endif
#endif /* INC_HVAC_CONFIG_H_ */