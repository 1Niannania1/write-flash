#include "led.h"                  // Device header

uint16_t led[]={led1,led2,led3};

void led_Init()
{
 RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

 GPIOA->CRL &=~GPIO_CRL_CNF0;
 GPIOA->CRL |=GPIO_CRL_MODE0;

 GPIOA->CRL &=~GPIO_CRL_CNF1;
 GPIOA->CRL |=GPIO_CRL_MODE1;

 GPIOA->CRH &=~GPIO_CRH_CNF8;
 GPIOA->CRH |=GPIO_CRH_MODE8;

 //通用推挽输出

 led_alloff(led,3);
 

}
void led_on(uint16_t led)
{
GPIOA->ODR &=~led;


}
void led_off(uint16_t led)
{
    GPIOA->ODR |=led;
}
//翻转led
void led_TOGGLE(uint16_t led)
{
if((GPIOA->IDR & led)==0)
{
    GPIOA->ODR |= led;
}
else{

    GPIOA->ODR &= ~led;
}


}
void led_allon(uint16_t led[],uint8_t size)
{
for(uint8_t i=0;i<size;i++)
{
    GPIOA->ODR &=~led[i];
}
}
void led_alloff(uint16_t led[],uint8_t size)
{
for(uint8_t i=0;i<size;i++)
     { GPIOA->ODR |=led[i];}
     
}

