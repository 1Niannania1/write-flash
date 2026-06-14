#ifndef __uart_it_h
#define __uart_it_h

#include "stm32f10x.h"
#include "stdio.h"
  extern  uint8_t buffer[100];
 extern uint8_t size;
 extern uint8_t flag;
// 初始化
void USART_Init(void);

// 发送一个字符
void USART_SendChar(uint8_t ch);

// // 接收一个字符
// uint8_t USART_ReceiveChar(void);

// 发送字符串
void USART_SendString(uint8_t *str, uint8_t size);

// // 接收字符串
// void USART_ReceiveString(uint8_t buffer[], uint8_t *size);



#endif
