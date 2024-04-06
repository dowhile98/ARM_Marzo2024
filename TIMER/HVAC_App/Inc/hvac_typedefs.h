/*
 * hvac_typedefs.h
 *
 *  Created on: Mar 8, 2024
 *      Author: jeffr
 */

#ifndef INC_HVAC_TYPEDEFS_H_
#define INC_HVAC_TYPEDEFS_H_
#ifdef __cplusplus
extern "C"{
#endif


typedef struct{
	uint8_t header;
	uint8_t len;
	uint8_t cmd;
	uint8_t payload[250];
	uint8_t end;
}usart_rx_data_t;


typedef enum{
	HVAC_RX_UART_DATA = 0x1,
}HVAC_Flags_t;

#ifdef __cplusplus
}
#endif
#endif /* INC_HVAC_TYPEDEFS_H_ */
