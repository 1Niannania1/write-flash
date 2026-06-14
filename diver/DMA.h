#ifndef __dma_h
#define __dma_h

#include "stm32f10x.h"


void DMA_init(void);


void DMA_transmit(uint32_t srcdress,uint32_t destdress,uint16_t lenth);

#endif
