#ifndef __led_H
#define __led_H




#include <stm32f10x.h>

//宏定义
#define led1 GPIO_ODR_ODR0
#define led2 GPIO_ODR_ODR1
#define led3 GPIO_ODR_ODR8

extern uint16_t  led[];

void led_Init(void);


void led_on(uint16_t led);
void led_off(uint16_t led);

//翻转led
void led_TOGGLE(uint16_t led);

void led_allon(uint16_t led[],uint8_t size);
void led_alloff(uint16_t led[],uint8_t size);


#endif
