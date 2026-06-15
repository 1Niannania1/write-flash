#include   "delay.h" 
#include   "uart_it.h"
#include "W25Q32.h"
#include "DEBUG.h"


uint8_t buffer[256];
uint16_t index=0;
uint8_t read_cheak_buffer[256];
int  main()
 {
uint32_t address=0;
W25_init();
USART_Init();





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
   debug_printf("no flash space\n");
   }
   debug_printf("write one page\n");
   

}

    


}
if (index!=0)
{

W25_write_32addrress(address,buffer,index);

}


W25_read(0x00,0x00,0x00,0x00,read_cheak_buffer,100);
if (read_cheak_buffer[0])
{
  printf("over");
 printf("%s",read_cheak_buffer);
}





 }



