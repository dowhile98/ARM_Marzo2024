/*
 * hvac_utils.h
 *
 *  Created on: Mar 8, 2024
 *      Author: jeffr
 */

#ifndef INC_HVAC_UTILS_H_
#define INC_HVAC_UTILS_H_

#define CONCACT(a, b)   a ## b
#define PORT(a)			CONCACT(GPIO, a)



#define BITBAND_ACCESS(a, b)  *(volatile uint32_t*)(((uint32_t)&a & 0xF0000000) + 0x2000000 + (((uint32_t)&a & 0x000FFFFF) << 5) + (b << 2))

/**
 * moder
 */
#define GPIOX_MODER_(a, b, n)  {PORT(a)->MODER &=~ (0x3)<<(2 * b); \
								PORT(a)->MODER |= n<<(2 * b);}
#define GPIOX_MODER(a, m) 		GPIOX_MODER_(a, m)
/**
 * otyper
 */
#define GPIOX_OTYPER_(a, b, n)  {GPIO ## a->OTYPER &=~(1<<b); \
								 GPIO ## a->OTYPER |= n<<b;}
#define GPIOX_OTYPER(a, b)		GPIOX_OTYPER_(a, b)
/**
 * ospeedr
 */
#define GPIOX_OSPEEDR_(a, b, n)		{PORT(a)->OSPEEDR &=~ (0x3)<<(2 * b); \
									PORT(a)->OSPEEDR |= n<<(2 * b);}
#define GPIOX_OSPEEDR(a, b)			GPIOX_OSPEEDR_(a, b)
/**
 * pupdr
 */
#define GPIOX_PUPDR_(a, b, n)		{PORT(a)->PUPDR &=~ (0x3)<<(2 * b); \
									PORT(a)->PUPDR |= n<<(2 * b);}
#define GPIOX_PUPDR(a, b)			GPIOX_PUPDR_(a, b)

/**
 * ODR
 */
//#define GPIOX_ODR_(a, b, n)			{PORT(a)->ODR &=~ (1<<b); PORT(a)->ODR |= n<<b;}
//#define GPIOX_ODR(a, b)				GPIOX_ODR_(a, b)
/**
 * toggle
 */
#define GPIOX_TOGGLE_(a,b )			PORT(a)->ODR ^= 1<<b
#define GPIOX_TOGGLE(a)				GPIOX_TOGGLE_(a)

/**
 * read pin
 */
//#define GPIOX_IDR_(a, b)			(GPIO ## a->IDR & 1<<b) ? 1 : 0
//#define GPIOX_IDR(a)				GPIOX_IDR_(a)
/**
 * pin set
 */
#define GPIOX_PIN_SET_(a, b, n)		GPIO ## a ->BSRR |= (n) ? 1<<b : 1<<(b + 16)
#define GPIOX_PIN_SET(a, b)			GPIOX_PIN_SET_(a, b)

/**
 * Clock enable
 */
#define GPIOX_CLK_EN_(a, b)			RCC->AHB1ENR |= RCC_AHB1ENR_GPIO ## a ## EN
#define GPIOX_CLK_EN(a)				GPIOX_CLK_EN_(a)
/**
 * BIND BAND
 */
#define GPIOX_ODR_(a, b)      		BITBAND_ACCESS(GPIO ## a ->ODR, b)
#define GPIOX_ODR(a)          		GPIOX_ODR_(a)

#define GPIOX_IDR_(a, b)      		BITBAND_ACCESS(GPIO ## a ->IDR, b)
#define GPIOX_IDR(a)          		GPIOX_IDR_(a)

#define PINX_(a, b)					b
#define PINX(a)						PINX_(a)
#define PORTX_(a, b)				GPIO ## a
#define PORTX(a)					PORTX_(a)



#define GPIOX_PORTNUM_A       1
#define GPIOX_PORTNUM_B       2
#define GPIOX_PORTNUM_C       3
#define GPIOX_PORTNUM_D       4
#define GPIOX_PORTNUM_E       5
#define GPIOX_PORTNUM_F       6
#define GPIOX_PORTNUM_G       7
#define GPIOX_PORTNUM_H       8
#define GPIOX_PORTNUM_I       9
#define GPIOX_PORTNUM_J       10
#define GPIOX_PORTNUM_K       11
#define GPIOX_PORTNUM_(a, b)  GPIOX_PORTNUM_ ## a
#define GPIOX_PORTNUM(a)      GPIOX_PORTNUM_(a)

#define GPIOX_PORTNAME_(a, b) a
#define GPIOX_PORTNAME(a)     GPIOX_PORTNAME_(a)
#endif /* INC_HVAC_UTILS_H_ */
