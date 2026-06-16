#ifndef __w25q32_h
#define __w25q32_h

#include "stm32f10x.h"
#include "SPI.h"


void W25_init(void);
void W25_writeable(void);

void W25_wait4nobusy(void);


void W25_eraser(uint8_t block,uint8_t duan);
void W25_write(uint8_t block,uint8_t duan,uint8_t page,uint8_t inderdress,uint8_t *senddata,uint8_t size);
void W25_read(uint8_t block,uint8_t duan,uint8_t page,uint8_t inderdress,uint8_t *receivedata,uint32_t size);

void W25_write_32addrress(uint32_t data,uint8_t *senddata,uint16_t size);
void W25_eraser_all(void);


#endif
