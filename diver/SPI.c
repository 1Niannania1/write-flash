#include "SPI.h"

//硬件spi通信

//PA5-SCLK  -复用输出

//PA1-NSS -通用推挽
//PA6—MISO  -浮空输入
//PA7—MOSI  -复用输出


void SPI_init()
{
    RCC->APB2ENR |=RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |=RCC_APB2ENR_SPI1EN;

    //1.PA2 配置通用推挽输出 CNF--00，MODE=11（最大输出模式）
 
    GPIOA->CRL &=~GPIO_CRL_CNF1;
    GPIOA->CRL |=GPIO_CRL_MODE1;

    //2.PA5 ， PA7 配置复用推挽输出 CNF--10，MODE=11（最大输出模式）
    GPIOA->CRL &=~GPIO_CRL_CNF7_0;
    GPIOA->CRL |=GPIO_CRL_CNF7_1;
    GPIOA->CRL |=GPIO_CRL_MODE7;

   GPIOA->CRL &=~GPIO_CRL_CNF5_0;
    GPIOA->CRL |=GPIO_CRL_CNF5_1;
    GPIOA->CRL |=GPIO_CRL_MODE5;


    

    //2.PA6浮空输入模式  CNF--01（浮空），mode--00（输入）
    GPIOA->CRL |=GPIO_CRL_CNF6_0;
    GPIOA->CRL &=~GPIO_CRL_MODE6;


    //初始电平给1，等待后续拉低
    NSS_HIGH;

    //3.SPI初始化

    //软件从设备管理并且设置为高电平
    SPI1->CR1 |=SPI_CR1_SSM;
    SPI1->CR1 |=SPI_CR1_SSI;
    
    //4分频
     SPI1->CR1 &=~SPI_CR1_BR;
     SPI1->CR1 |=SPI_CR1_BR_0;

    //主模式选择   
    SPI1->CR1 |=SPI_CR1_MSTR;

   //极性和相位默认0

   SPI1->CR1 |=SPI_CR1_SPE;



    }


void SPI_start(void)
{

    NSS_LOW;
   delay;
}
void SPI_stop(void)
{
 NSS_HIGH;      
 delay;

}


uint8_t SPI_weapbyte(uint8_t senddata)
{   

   uint8_t byte_true=0;
while((SPI1->SR & SPI_SR_TXE)==0)
{

}
    SPI1->DR =senddata;

// while((SPI1->SR & SPI_SR_RXNE)==0)
// {

// }
//      SPI1->DR; 

while((SPI1->SR & SPI_SR_RXNE)==0)
{

}
    byte_true= SPI1->DR; 

    return byte_true;

}
