#include "DMA.h"

void DMA_init(void)
{
RCC->AHBENR |=RCC_AHBENR_DMA1EN;

//men2men
DMA1_Channel1->CCR |=DMA_CCR1_MEM2MEM;

//方向：0-从外设读，1-从存储器读
DMA1_Channel1->CCR &=~DMA_CCR1_DIR;
//把rom当成外设，从rom读到ram里

//地址自增
DMA1_Channel1->CCR |=DMA_CCR1_MINC;
DMA1_Channel1->CCR |=DMA_CCR1_PINC;

//传输八位数据--默认

//允许传输完成中断
DMA1_Channel1->CCR |=DMA_CCR1_TCIE;

//中断设置
NVIC_SetPriorityGrouping(4);
NVIC_SetPriority(DMA1_Channel1_IRQn,1);
// NVIC_EnableIRQ(DMA1_Channel1_IRQn);




}





void DMA_transmit(uint32_t srcdress,uint32_t destdress,uint16_t lenth)
{
DMA1_Channel1->CMAR =destdress;
DMA1_Channel1->CPAR =srcdress;
DMA1_Channel1->CNDTR =lenth;
DMA1_Channel1->CCR |=DMA_CCR1_EN;


}



