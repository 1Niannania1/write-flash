#include   "delay.h" 
#include   "uart_it.h"
#include "W25Q32.h"
#include "DEBUG.h"


// uint8_t buffer[256];
// uint16_t index=0;
// uint8_t page_Size;
// uint8_t page[5];

//4MB 容量共有 16,384 页。
int  main()
 {
uint8_t buffer[256];
uint16_t index=0;

uint16_t page[5]={0};
uint32_t address=0;
uint8_t read_cheak_buffer[257]= {0};  
W25_init();
USART_Init();


// W25_eraser_all();//全片擦除
// printf("ready\r\n");  

// printf("page write count (must be 5bit):");

// //得到主机发送的count
// for (int i = 0; i < 5; i++)
// {
//     while (out_cycle_buffer((uint8_t *)&page[i]) != 1)
//     {
//         // 等数据
//     }
// }
// done=0;



// uint16_t page_count=0;

// for (uint8_t i = 0; i < 5; i++)
// {
//     if (page[i] >= '0' && page[i] <= '9')
//     {
//         page_count = page_count * 10 + (page[i] - '0');
//     }
// }

// printf("page write=%d\n",page_count);
// printf("plese transmit\n");

// while (page_count)
// {
//    page_count--;
   


// while((done==0)||(tail!=head)) {


// if (out_cycle_buffer(&buffer[index])==1)
// {
//   index++;
// }

// if (index==256)
// {
 
//    W25_write_32addrress(address,buffer,256);
//    index=0;
//    address+=256;
//    if (address==0x400000)
//    {
//   printf("no flash space\n");
//    }
//    printf("write one page\n");
   

// }

    


// }
// if (index!=0)
// {

// W25_write_32addrress(address,buffer,index);
// break;

// }

// //  多次写入
// done=0;  
// // tail=0;
// // head=0;
// index=0;
// // address=0;

// }

debug_printf(" page write over\n");
W25_read(0x00,0x00,0x20,0x00,read_cheak_buffer,256);
 printf("check_buffer=%s",read_cheak_buffer);


 }



