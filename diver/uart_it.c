#include "uart_it.h"


// clycle receive buffer
#define cycle_max 512
uint8_t rx_buffer[cycle_max]={0};
volatile uint16_t head=0,tail=0;
uint16_t next=0;
volatile uint8_t done=0;

void in_cycle_buffer(uint8_t byte);

void in_cycle_buffer(uint8_t byte)
{
next=(head+1)%cycle_max;
if (next!=tail)
{
 rx_buffer[head]=byte;
head=(head+1)%cycle_max;
}

else
{
   printf("no new cycle space to write\n");
}

}
int out_cycle_buffer(uint8_t *byte)
{
    
 
    if (head!=tail)
  {  *byte=rx_buffer[tail];
  tail=(tail+1)%cycle_max;
return 1;}
  else{
    return -1;
  }
  //head=tail，无数据


    
    

}
// 初始化
void USART_Init(void)
{
RCC->APB2ENR |=RCC_APB2ENR_USART1EN;
RCC->APB2ENR |=RCC_APB2ENR_IOPAEN;

   
    //GPIO工作模式
    // PA9: 复用推挽输出，CNF-10，MODE-11
    // PA10: 浮空输入，CNF-01，MODE-00
GPIOA->CRH |=GPIO_CRH_CNF9_1;
GPIOA->CRH &=~GPIO_CRH_CNF9_0;
GPIOA->CRH |=GPIO_CRH_MODE9;

GPIOA->CRH |=GPIO_CRH_CNF10_0;
GPIOA->CRH &=~GPIO_CRH_CNF10_1;
GPIOA->CRH &=~GPIO_CRH_MODE10;

//串口设置
//1.波特率设置
USART1->BRR=0x271;

//2.收发使能及模块使能.RE—收使能，TE-发使能，UE-USART1模块使能
USART1->CR1 |= (USART_CR1_UE| USART_CR1_TE|USART_CR1_RE);

    // 3.3 其它配置，设置数据帧格式
    USART1->CR1 &= ~USART_CR1_M;
   //因为不加校验位，所以数据是八位
    USART1->CR1 &= ~USART_CR1_PCE;
    //不加校验位
    USART1->CR2 &= ~USART_CR2_STOP;
   //一个停止位

//3.中断使能
  USART1->CR1 |= USART_CR1_IDLEIE;
  USART1->CR1 |=USART_CR1_RXNEIE;

  //3.设置优先级
  NVIC_SetPriorityGrouping(4);
  NVIC_SetPriority(USART1_IRQn,0x01);
  NVIC_EnableIRQ(USART1_IRQn);





}

// 发送一个字符
void USART_SendChar(uint8_t ch)
{
 while ((USART1->SR & USART_SR_TXE)==0)
 {
    
 }

 USART1->DR=ch;
//写dr相当于清除TXE标志位

}

// // 接收一个字符
// uint8_t USART_ReceiveChar(void)
// {
    
// while ((USART1->SR & USART_SR_RXNE)==0)
// {
//      if((USART1->SR & USART_SR_IDLE )!=0)
//      {
//         return 0;
//      }

// }
 
// return  USART1->DR;
// //读dr相当于清除RXNE标志位

// }

// 发送字符串
void USART_SendString(uint8_t *str, uint8_t size)
{

for (uint16_t i = 0; i < size; i++)
{
    USART_SendChar(str[i]);
}


}

// // 接收字符串
// void USART_ReceiveString(uint8_t buffer[], uint8_t *size)
// {
// uint8_t i=0;
// //初始化给0，防止意外
// while((USART1->SR & USART_SR_IDLE)==0)
// {
//    buffer[i]=USART_ReceiveChar();
//    // 因为IDLE是一帧空闲才置位，所以有延迟。如果不在receiverchar里判断IDLE，最后会卡死在receivechar函数，无法跳出；
//    i++;
  
// }
// //清除IDLE
// USART1->SR;
// USART1->DR;

// i--;
// //为什么减1：最后一定是从receivechar里跳出来的，也就是多返回了一个0，被编译成/0；
// *size=i;
// }

uint16_t interrupt_count=0;
void USART1_IRQHandler()
{
if(USART1->SR & USART_SR_RXNE)
{
    interrupt_count++;

in_cycle_buffer(USART1->DR);
}
if(USART1->SR & USART_SR_IDLE)
{

//取消IDLE标志位
USART1->SR;
USART1->DR;
done=1;

}


}


int fputc(int ch,FILE *f)
{
USART_SendChar((uint8_t )ch);
return ch;

}

