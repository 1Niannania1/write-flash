#include   "delay.h" 
#include   "uart_it.h"
#include "W25Q32.h"
#include "DEBUG.h"


uint8_t buffer[256];
uint16_t index=0;

int  main()
 {
uint32_t address=0;
W25_init();
USART_Init();


// W25_eraser(0,0);
while (1)
{
   uint8_t read_cheak_buffer[258]= {0};
//   for (uint8_t i = 0; i < 128; i++)
//   {
//  for (uint8_t j = 0; j < 16; j++)
//  {
  
// W25_eraser(i,j);
//  }

//   }

W25_eraser(0,0);
while(done==0) {


if (out_cycle_buffer(&buffer[index])==1)
{
  index++;
}

if (index==256)
{
 
   W25_write_32addrress(address,buffer,256);
   index=0;
   address+=256;
   if (address==0x400000)
   {
  printf("no flash space\n");
   }
   printf("write one page\n");
   

}

    


}
if (index!=0)
{

W25_write_32addrress(address,buffer,index);

}


W25_read(0x00,0x00,0x00,0x00,read_cheak_buffer,256);

    debug_printf("Read");

 printf("check_buffer=%s",read_cheak_buffer);

done=0;  
tail=0;
head=0;
index=0;
address=0;


}


 }



