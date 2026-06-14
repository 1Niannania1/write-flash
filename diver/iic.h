#ifndef __iic_h_
#define __iic_h_

#include "stm32f10x.h"

#define ACK 0
#define NACK 1

//假设用A5作为SCL,A6作为SDA
#define SCL_LOW  (GPIOA->ODR &= ~GPIO_ODR_ODR5)
#define SCL_HIGH (GPIOA->ODR |= GPIO_ODR_ODR5)
//写1不是真的发出了1，而是内部mos管关断，被外部上拉到1

#define SDA_HIGH (GPIOA->ODR |= GPIO_ODR_ODR6)

#define SDA_LOW  (GPIOA->ODR &= ~GPIO_ODR_ODR6)

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_sendbyte(uint8_t byte);
uint8_t i2c_recievebyte(void);
void i2c_ack(void);
void i2c_nack(void);
uint8_t i2c_waitack(void);



#endif
