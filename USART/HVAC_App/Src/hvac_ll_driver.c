/*
 * hvac_ll_driver.c
 *
 *  Created on: Mar 8, 2024
 *      Author: jeffr
 */

#include "hvac_ll_driver.h"

/*Defines-----------------------------------------------*/
#define CONCAT_EXTICR(a,b, c)	a ## b ## c

#if (PINX(CONTACT1)==0)
#define CONTACT1_IRQn		EXTI0_IRQn
#define SYSCFG_EXTICRx		0
#elif (PINX(CONTACT1)==1)
#define CONTACT1_IRQn		EXTI1_IRQn
#elif (PINX(CONTACT1)==2)
#define CONTACT1_IRQn		EXTI2_IRQn
#elif (PINX(CONTACT1)==3)
#define CONTACT1_IRQn		EXTI3_IRQn
#elif (PINX(CONTACT1)==4)
#define CONTACT1_IRQn		EXTI4_IRQn
#elif((PINX(CONTACT1)<10) && (PINX(CONTACT1)>4))
#define CONTACT1_IRQn		EXTI9_5_IRQn
#else
#define CONTACT1_IRQn		EXTI15_10_IRQn
#endif


#if (PINX(CONTACT2)==0)
#define CONTACT2_IRQn		EXTI0_IRQn
#elif (PINX(CONTACT2)==1)
#define CONTACT2_IRQn		EXTI1_IRQn
#elif (PINX(CONTACT2)==2)
#define CONTACT2_IRQn		EXTI2_IRQn
#elif (PINX(CONTACT2)==3)
#define CONTACT2_IRQn		EXTI3_IRQn
#elif (PINX(CONTACT2)==4)
#define CONTACT2_IRQn		EXTI4_IRQn
#elif((PINX(CONTACT2)<10) && (PINX(CONTACT2)>4))
#define CONTACT2_IRQn		EXTI9_5_IRQn
#else
#define CONTACT2_IRQn		EXTI15_10_IRQn
#endif




#if(PINX(CONTACT1) <4)
#define CONTACT1_EXTICR		0
#elif(PINX(CONTACT1)<8)
#define CONTACT1_EXTICR		1
#define EXTI_NUMBER			PINX(CONTACT1)
#elif (PINX(CONTACT1) < 12)
#define CONTACT1_EXTICR		2
#else
#define CONTACT1_EXTICR		3
#endif

#if(PINX(CONTACT2) <4)
#define CONTACT2_EXTICR		0
#elif(PINX(CONTACT2)<8)
#define CONTACT2_EXTICR		1
#elif (PINX(CONTACT2) < 12)
#define CONTACT2_EXTICR		2
#else
#define CONTACT2_EXTICR		3
#endif


#if(GPIOX_PORTNUM(CONTACT1) == GPIOX_PORTNUM_A )
#define CONTACT1_PIN_SOURCE	0
#elif (GPIOX_PORTNUM(CONTACT1) == GPIOX_PORTNUM_B )
#define CONTACT1_PIN_SOURCE	0x1
#elif (GPIOX_PORTNUM(CONTACT1) == GPIOX_PORTNUM_C )
#define CONTACT1_PIN_SOURCE	0x2
#elif (GPIOX_PORTNUM(CONTACT1) == GPIOX_PORTNUM_D )
#define CONTACT1_PIN_SOURCE	0x3
#elif (GPIOX_PORTNUM(CONTACT1) == GPIOX_PORTNUM_E )
#define CONTACT1_PIN_SOURCE	0x4
#elif (GPIOX_PORTNUM(CONTACT1) == GPIOX_PORTNUM_F )
#define CONTACT1_PIN_SOURCE	0x5
#endif

#if(GPIOX_PORTNUM(CONTACT2) == GPIOX_PORTNUM_A )
#define CONTACT2_PIN_SOURCE	0
#elif (GPIOX_PORTNUM(CONTACT2) == GPIOX_PORTNUM_B )
#define CONTACT2_PIN_SOURCE	0x1
#elif (GPIOX_PORTNUM(CONTACT2) == GPIOX_PORTNUM_C )
#define CONTACT2_PIN_SOURCE	0x2
#elif (GPIOX_PORTNUM(CONTACT2) == GPIOX_PORTNUM_D )
#define CONTACT2_PIN_SOURCE	0x3
#elif (GPIOX_PORTNUM(CONTACT2) == GPIOX_PORTNUM_E )
#define CONTACT2_PIN_SOURCE	0x4
#elif (GPIOX_PORTNUM(CONTACT2) == GPIOX_PORTNUM_F )
#define CONTACT2_PIN_SOURCE	0x5
#endif
/*Function definition ----------------------------------*/
void hvac_io_init(void){

	uint32_t exti_cr_msk;
	uint32_t factor;
	/**
	 * SW1
	 */
	GPIOX_CLK_EN(SW1); GPIOX_CLK_EN(SW2);
	GPIOX_MODER(SW1, 0);
	GPIOX_MODER(SW2, 0);
	//GPIOX_PUPDR(SW1, 1);
	GPIOX_PUPDR(SW2, 1);
	/**
	 * Contactos
	 */
	GPIOX_CLK_EN(CONTACT1); GPIOX_CLK_EN(CONTACT2);
	GPIOX_MODER(CONTACT1, 0);
	GPIOX_MODER(CONTACT2, 0);
	GPIOX_PUPDR(CONTACT1, 2);
	GPIOX_PUPDR(CONTACT2, 2);
	/**
	 * Relay
	 */
	GPIOX_CLK_EN(RELAY1);GPIOX_CLK_EN(RELAY2);
	GPIOX_MODER(RELAY1, 0x1);
	GPIOX_MODER(RELAY2, 0x1);

	/**
	 * STATUS
	 */
	GPIOX_CLK_EN(STATUS);
	GPIOX_MODER(STATUS, 1);
	/**
	 * Alarma de contacto
	 */
	GPIOX_CLK_EN(A_CONTACT);
	GPIOX_MODER(A_CONTACT, 1);
	/**
	 * interrupcion
	 */
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	EXTI->IMR |= (1<<PINX(CONTACT1) | 1<<PINX(CONTACT2));
	EXTI->RTSR |= (1<<PINX(CONTACT1) | 1<<PINX(CONTACT2));
	EXTI->PR |= (1<<PINX(CONTACT1) | 1<<PINX(CONTACT2));

	/**
	 * ASIGNAR EL PIN EN EL REGISTRO DE CONFIGURACION
	 */
	factor = CONTACT1_EXTICR;
	if(factor == 0){
		exti_cr_msk = PINX(CONTACT1) * 4;
	}else{
		/**
		 * 14 % (4 * 3) = 2 * 4 -> 8
		 */
		exti_cr_msk = (PINX(CONTACT1) % (factor * 4 ))  * 4;
	}
	SYSCFG->EXTICR[CONTACT1_EXTICR] &=~ 0xF<<exti_cr_msk;
	SYSCFG->EXTICR[CONTACT1_EXTICR] |= CONTACT1_PIN_SOURCE<<exti_cr_msk;
	factor = CONTACT2_EXTICR;
	if(factor == 0){
		exti_cr_msk = PINX(CONTACT2) * 4;
	}else{
		/**
		 * 14 % (4 * 3) = 2 * 4 -> 8
		 */
		exti_cr_msk = (PINX(CONTACT2) % (factor * 4 ))  * 4;
	}

	SYSCFG->EXTICR[CONTACT2_EXTICR] &=~ 0xF<<exti_cr_msk;
	SYSCFG->EXTICR[CONTACT2_EXTICR] |= CONTACT2_PIN_SOURCE<<exti_cr_msk;

	/**
	 * CONFIGURAR NVIC
	 */
	NVIC_EnableIRQ(CONTACT1_IRQn);
	NVIC_EnableIRQ(CONTACT2_IRQn);
	NVIC_SetPriority(CONTACT1_IRQn, CONTACT1_PRI);
	NVIC_SetPriority(CONTACT2_IRQn, CONTACT2_PRI);

	/**
	 * LCD
	 */
	GPIOX_CLK_EN(LCD_RS); GPIOX_CLK_EN(LCD_EN);
	GPIOX_CLK_EN(LCD_D4); GPIOX_CLK_EN(LCD_D5);
	GPIOX_CLK_EN(LCD_D6); GPIOX_CLK_EN(LCD_D7);

	GPIOX_MODER(LCD_RS, 0x1); GPIOX_MODER(LCD_EN, 1);
	GPIOX_MODER(LCD_D4, 0x1); GPIOX_MODER(LCD_D5, 1);
	GPIOX_MODER(LCD_D6, 0x1); GPIOX_MODER(LCD_D7, 1);

	/**
	 * UART
	 */
	GPIOX_CLK_EN(USART2_TX);
	GPIOX_MODER(USART2_TX, 0x2);
	GPIOX_MODER(USART2_RX, 0x2);

	PORTX(USART2_TX)->AFR[0] &=~ GPIO_AFRL_AFSEL2;
	PORTX(USART2_RX)->AFR[0] &=~ GPIO_AFRL_AFSEL3;
	PORTX(USART2_TX)->AFR[0] |= 0x7<<GPIO_AFRL_AFSEL2_Pos;
	PORTX(USART2_RX)->AFR[0] |= 0x7<<GPIO_AFRL_AFSEL3_Pos;

	GPIOX_OSPEEDR(USART2_TX, 0x3);
	GPIOX_OSPEEDR(USART2_RX, 0x3);
	return;
}

/**
 * UART
 */
void hvac_uart_init(USART_TypeDef *U){
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	/**
	 *
	 */
	U->CR1 = 0;
	/**
	 * BAUDIOS
	 * USARTDIV = 16E+6 / (16 * 115200)
	 * USARTDIV = 8.68
	 * -> 8 -> 0x8
	 *
	 * ->0.68 * 16 -> 10.8888 -> 11 -> 0xB
	 * BRR = 0x8B
	 */
	U->BRR = 0x8B;
	/**
	 * re y te
	 */
	U->CR1 |= USART_CR1_TE | USART_CR1_RE;
	/**
	 * IT
	 */
	U->CR1 |= USART_CR1_RXNEIE;

	NVIC_EnableIRQ(USART2_IRQn);

	/**
	 * habilitamos
	 */
	U->CR1 |= USART_CR1_UE;
}
/**
 * LCD
 */
void hvac_lcd_write_nb(uint8_t data, uint8_t control){
	uint32_t delay = 1;
	//GPIOX_ODR(LCD_D7, (data>>3) & 0x1);
	GPIOX_ODR(LCD_D7) = (data>>3) & 0x1;
	GPIOX_ODR(LCD_D6) = (data>>2) & 0x1;
	GPIOX_ODR(LCD_D5) = (data>>1) & 0x1;
	GPIOX_ODR(LCD_D4) = (data) & 0x1;

	GPIOX_ODR(LCD_EN) = 0;
	if(control){
		GPIOX_ODR(LCD_RS) = 1;
	}else{
		GPIOX_ODR(LCD_RS) = 0;
	}
	GPIOX_ODR(LCD_EN) = 1;
	while(delay-->0);
	GPIOX_ODR(LCD_EN) = 0;
	return;
}