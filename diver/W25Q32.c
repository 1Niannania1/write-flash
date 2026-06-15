#include "W25Q32.h"
#include "stdio.h"

void W25_init()
{
    SPI_init();
}

void W25_writeable(void)
{
SPI_start();
SPI_weapbyte(0x06);
SPI_stop();

}

void W25_wait4nobusy(void)
{
 
SPI_start();
 (SPI_weapbyte(0x05)); 
uint16_t count=0;

while ((SPI_weapbyte(0xff))&0x01)
{
 
    count++;
    if (count==50000)
    {
  
     count=0;
     break;
        /* code */
    }
    
}
SPI_stop();

}


void W25_eraser(uint8_t block,uint8_t duan)
{
//清除之前必须开启写使能
W25_writeable();

SPI_start();
SPI_weapbyte(0x20);//发送擦除命令

//计算发送的字节
uint32_t data =(block<<16)+(duan<<12);

//分别发送擦除地址
SPI_weapbyte((data>>16)&0xff);
SPI_weapbyte((data>>8)&0xff);
SPI_weapbyte((data>>0)&0xff);

SPI_stop();

W25_wait4nobusy();


}




void W25_write(uint8_t block,uint8_t duan,uint8_t page,uint8_t inderdress,uint8_t *senddata,uint8_t size)
{
W25_writeable();
SPI_start();
SPI_weapbyte(0x02);//发送写命令

//计算发送的字节
uint32_t data =(block<<16)+(duan<<12)+(page<<8)+(inderdress<<0);

//分别发送写入地址
SPI_weapbyte((data>>16)&0xff);
SPI_weapbyte((data>>8)&0xff);
SPI_weapbyte((data>>0)&0xff);
for (uint8_t i = 0; i < size; i++)
{
  SPI_weapbyte(senddata[i]);

}
SPI_stop();
W25_wait4nobusy();

}


void W25_read(uint8_t block,uint8_t duan,uint8_t page,uint8_t inderdress,uint8_t *receivedata,uint32_t size)
{

SPI_start();
SPI_weapbyte(0x03);//发送读命令

//计算发送的字节
uint32_t data =(block<<16)+(duan<<12)+(page<<8)+(inderdress<<0);

//分别发送读取地址
SPI_weapbyte((data>>16)&0xff);
SPI_weapbyte((data>>8)&0xff);
SPI_weapbyte((data>>0)&0xff);

for (uint32_t i = 0; i < size; i++)
{
  receivedata[i]= SPI_weapbyte(0xff);

}
SPI_stop();


}

void W25_write_32addrress(uint32_t data,uint8_t *senddata,uint16_t size)
{
W25_writeable();
SPI_start();
SPI_weapbyte(0x02);//发送写命令



//分别发送写入地址
SPI_weapbyte((data>>16)&0xff);
SPI_weapbyte((data>>8)&0xff);
SPI_weapbyte((data>>0)&0xff);
for (uint16_t i = 0; i < size; i++)
{
  SPI_weapbyte(senddata[i]);

}
SPI_stop();
W25_wait4nobusy();

}

void W25_eraser_32(uint32_t data)
{
//清除之前必须开启写使能
W25_writeable();

SPI_start();
SPI_weapbyte(0x20);//发送擦除命令


//分别发送擦除地址
SPI_weapbyte((data>>16)&0xff);
SPI_weapbyte((data>>8)&0xff);
SPI_weapbyte((data>>0)&0xff);

SPI_stop();

W25_wait4nobusy();


}