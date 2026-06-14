#include "iic.h"
#include "delay.h"

//除了start和stop连着写了两个SCL_HIGH,其他函数我都在最后拉低了SCL
//也就是说，其他函数前面都自带一个没写出来的SCL_LOW,然后我改变SDA,然后拉高SDA检测，拉低SDA采样结束；

//pa9 sda
void i2c_init(void)
{
    RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
    //使能GPIOA
 
 
    GPIOA->CRL |=GPIO_CRL_CNF5_0;
    GPIOA->CRL &=~GPIO_CRL_CNF5_1;
    GPIOA->CRL |=GPIO_CRL_MODE5;

    GPIOA->CRL |=GPIO_CRL_CNF6_0;
    GPIOA->CRL &=~GPIO_CRL_CNF6_1;
    GPIOA->CRL |=GPIO_CRL_MODE6;
    
    //通用开漏输出

    //此时stm32作为主机发送信号

    SCL_HIGH;
    SDA_HIGH;
    //初始状态，SCL和SDA都处于空闲状态



}
void i2c_start(void)
{
//初始状态
    SDA_HIGH;
    SCL_HIGH;
delay_us(10);

//准备信号发出
SDA_LOW;

delay_us(10);

//采样结束

SCL_LOW;
delay_us(10);

}

void i2c_stop(void)
{
 
   //SDA先拉到低
    SDA_LOW;
    SCL_HIGH;
     
    delay_us(10);

   //结束信号发出  SDA在拉到高，整个过程都是SCL_HIGH
   SDA_HIGH;
   
    delay_us(10);

    //采样结束
    SCL_LOW;
    delay_us(10);




}

void i2c_sendbyte(uint8_t byte)
{
//iic协议先发高位

   

    for (uint8_t i = 0; i < 8; i++)
    {
        if((byte & 0x80)==0)
        {
            //我每一步最后都拉低SCL，相当于这里有一步SCL_LOW;
            SDA_LOW;
            

            SCL_HIGH;
            delay_us(10);

           SCL_LOW;
            delay_us(10);
        }
        else{
            SDA_HIGH;
            SCL_HIGH;
            delay_us(10);

            SCL_LOW;
            delay_us(10);
        }
        byte<<=1;
    }
    SDA_HIGH;
    //释放SDA
    SCL_LOW;
    delay_us(10);

 

       

}
uint8_t i2c_recievebyte(void)
{
// 调用这个函数之前，sda应当处于高电平空闲状态，也就是说主机必须释放SDA，允许从机给它发数据
uint8_t data=0;


    //初始状态，允许电平突变
    SCL_LOW;
    delay_us(10);
    
    
    for (uint8_t i = 0; i < 8; i++)
    {
        SCL_HIGH;
    delay_us(10);

    if((GPIOA->IDR & GPIO_IDR_IDR6)==0)
    {
        data &=~0x01;
    }
    else{
        data|=0x01;
    }
    
    if(i==7)
    {}
    else{
    data<<=1;
    }
    SCL_LOW;
    
    delay_us(10);
}

return data;

}

void i2c_ack(void)
{
//我每一步最后都拉低SCL，相当于这里有一步SCL_LOW;
SDA_LOW;//AcK回应
//在低电平改变SDA

SCL_HIGH;
delay_us(10);
//拉高开始采样

SCL_LOW;
//采样结束


SDA_HIGH;
delay_us(10);
//释放SDA

}
//主机主动发送ack


void i2c_nack(void)
{

    SDA_HIGH;
    SCL_HIGH;
    delay_us(10);
    SCL_LOW;
    delay_us(10);
}
//主机不发送ack




//等待从机发送
uint8_t i2c_waitack(void)
{
    uint8_t ack=0;
SDA_HIGH;
//确保总线释放
SCL_HIGH;
delay_us(10);
//从机被允许在SCL线为高的时候改变电平
if ((GPIOA->IDR & GPIO_IDR_IDR6)==0)
{
    ack=ACK;
}
else{
    ack=NACK;
}
SCL_LOW;

return ack;

}
