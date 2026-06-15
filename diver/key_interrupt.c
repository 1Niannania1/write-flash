#include "key_interrupt.h"
#include "led.h"
#include "delay.h"

void key_able(void)
{RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;

RCC->APB2ENR|=RCC_APB2ENR_AFIOEN;
// KEY.AFIO ENABLE

GPIOB->CRL &= ~GPIO_CRL_MODE4;
GPIOB->CRL |= GPIO_CRL_CNF4_1;
GPIOB->CRL &= ~GPIO_CRL_CNF4_0;
//配置成输入模式，（浮空，上下拉，模拟）选择上下拉

GPIOB->ODR |=GPIO_ODR_ODR4;
// 我把按键初始接地，与例程不同。应该用上拉输入，给一个低电平就是下拉输入，后续捕捉下降沿 

AFIO->EXTICR[1]|=AFIO_EXTICR1_EXTI0_PB;

EXTI->FTSR|=EXTI_FTSR_TR4;
//f——下降，给下降沿捕捉寄存器置1

EXTI->IMR|=EXTI_IMR_MR4;
//给中断屏蔽寄存器置1，确保允许中断
NVIC_SetPriorityGrouping(4);
NVIC_SetPriority(EXTI4_IRQn,0X20);
NVIC_EnableIRQ(EXTI4_IRQn);
}

void EXTI4_IRQHandler()
{
EXTI->PR |= EXTI_PR_PR4;

delay_ms(10);
if ((GPIOB->IDR & GPIO_IDR_IDR4)==0)
{
  led_TOGGLE(led1);
}

}

