/*
 * hvac_ll_driver.h
 *
 *  Created on: Mar 8, 2024
 *      Author: jeffr
 */

#ifndef INC_HVAC_LL_DRIVER_H_
#define INC_HVAC_LL_DRIVER_H_
#ifdef __cplusplus
extern "C"{
#endif
/*Includes -----------------------------------------------------*/
#include "stm32f4xx.h"
#include "hvac_config.h"
#include "hvac_typedefs.h"
#include "hvac_utils.h"

/*Defines -------------------------------------------------------*/

/*Extern definition ---------------------------------------------*/

/*Function prototype --------------------------------------------*/
void hvac_io_init(void);

void hvac_lcd_write_nb(uint8_t data, uint8_t control);


void hvac_uart_init(USART_TypeDef *U);
#ifdef __cplusplus
}
#endif
#endif /* INC_HVAC_LL_DRIVER_H_ */
