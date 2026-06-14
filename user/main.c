#include   "delay.h" 
#include   "uart_it.h"
#include "W25Q32.h"



// i'm back
// 我回来了.


int  main()
 {
uint8_t arr[100]={1};
W25_init();
USART_Init();
printf("%d\n",arr[0]);


printf("init over\n");
W25_eraser(0,0);
printf("eraser over\n");  
W25_write(0,0,0,0,"hello cworld",12);
printf("write over\n");
// W25_wait4nobusy();
W25_read(0,0,0,0,arr,12);
printf("ready read\n");

printf("%d\n",arr[0]);
printf("%s\n",arr);


// uint8_t id[3];
// SPI_start();
// SPI_weapbyte(0x9F);
// id[0] = SPI_weapbyte(0xFF);
// id[1] = SPI_weapbyte(0xFF);
// id[2] = SPI_weapbyte(0xFF);
// SPI_stop();
// printf("ID: %d %d %d\n", id[0], id[1], id[2]);


//硬件不稳定 导致信号波动



while(1) {

}


 }



