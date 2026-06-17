#include   "delay.h" 
#include   "uart_it.h"
#include "W25Q32.h"
#include "DEBUG.h"

//没有加校验重发导致仍然有一点乱码


//4MB 容量共有 16,384 页。
//8MB 容量共有 16,384*2 页。
//计算page count 用sscom预览字节/256
int  main()
 {
uint8_t buffer[256];
uint16_t index=0;

uint16_t page[5]={0};
uint32_t address=0;
uint8_t read_cheak_buffer[257]= {0};  //多一个数据位0，确保不会越界读取
W25_init();
USART_Init();


W25_eraser_all();//全片擦除
printf("ready\r\n");  //必须等待擦除完成，不要打断

//必须是五位数，高位可用0填充
printf("page write count (must be 5bit):");

//得到主机发送的count
for (int i = 0; i < 5; i++)
{
    while (out_cycle_buffer((uint8_t *)&page[i]) != 1)
    {
        // 等数据
    }
}

//重新置位
done=0;


//串口发送的是字符而非数字，计算出页数
uint16_t page_count=0;
for (uint8_t i = 0; i < 5; i++)
{
    if (page[i] >= '0' && page[i] <= '9')
    {
        page_count = page_count * 10 + (page[i] - '0');
    }
}

printf("page write count=%d\n",page_count);
printf("plese transmit\n");

//所有页写入大循环，一共写入page_Count次
while (page_count)
{
   
   

//页写循环
while((done==0)||(tail!=head)) 
{
if (out_cycle_buffer(&buffer[index])==1)
{
  index++;

  if (index==256)
{
 
   W25_write_32addrress(address,buffer,256);
   page_count--;
   index=0;
   address+=256;
   if (address==0x400000)
   {
  printf("no flash space\n");
   }
   printf("write one page\n");

}

}

}
//当前done=1,且当前缓冲区数据全部读出


//最后一页不满一页的字节写入
if (index!=0)
{

W25_write_32addrress(address,buffer,index);
page_count--;
break;

}

//  多次写入
done=0;  
}


//check
debug_printf(" page write all over\n");
W25_read(0x00,0x02,0x07,0x00,read_cheak_buffer,256);
 printf("check_buffer=%s",read_cheak_buffer);


 }



