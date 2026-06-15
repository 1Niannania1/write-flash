#ifndef __SPI_h
#define __SPI_H

#include "stm32f10x.h"
#include "delay.h"

void SPI_init(void);
void SPI_start(void);
void SPI_stop(void);
uint8_t SPI_weapbyte(uint8_t senddata);

//硬件spi通信

//PA5-SCLK

//PA1-NSS
//PA6—MISO
//PA7—MOSI


#define NSS_LOW  (GPIOA->ODR &=~GPIO_ODR_ODR1)
#define NSS_HIGH  (GPIOA->ODR |=GPIO_ODR_ODR1)

#define delay      (delay_us(10))

#endif
