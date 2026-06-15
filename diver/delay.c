#include "delay.h"

void delay_us(uint16_t us)
{
SysTick->LOAD=72*us;
SysTick->CTRL =0x05;

while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG)==0)
{}
SysTick->CTRL &=~SysTick_CTRL_ENABLE;

}

void delay_ms(uint16_t ms)
{
for(uint16_t i=0;i<ms;i++)
{
delay_us(1000);

}

}
void delay_s(uint16_t s)
{
for(uint16_t i=0;i<s;i++)
{
delay_ms(1000);

}

}
