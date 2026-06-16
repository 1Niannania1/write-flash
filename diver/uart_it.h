#ifndef __uart_it_h
#define __uart_it_h

#include "stm32f10x.h"
#include "stdio.h"
#include "DEBUG.h"

extern volatile uint8_t done;
extern volatile uint16_t head,tail;
// 初始化
void USART_Init(void);

// 发送一个字符
void USART_SendChar(uint8_t ch);

// 接收一个字符
// uint8_t USART_ReceiveChar(void);

// 发送字符串
void USART_SendString(uint8_t *str, uint8_t size);

// 接收字符串
// void USART_ReceiveString(uint8_t buffer[], uint8_t *size);

int out_cycle_buffer(uint8_t *byte);

#endif
