#include "dma.h"
//////////////////////////////////////////////////////////////////////////////////	 
    //DMA各通道：
	//USART1-TX   : CH4
	//USART1-RX   : CH5
	//USART2-TX   : CH7
	//USART2-RX   : CH6
	//USART3-TX   : CH2
	//USART3-RX   : CH3
//////////////////////////////////////////////////////////////////////////////////

DMA_InitTypeDef DMA_InitStructure;

u16 DMA1_MEM_LEN;//保存DMA每次数据传送的长度 	    
//DMA1的各通道配置
//这里的传输形式是固定的,这点要根据不同的情况来修改
//从存储器->外设模式/8位数据宽度/存储器增量模式
//DMA_CHx:DMA通道CHx
//cpar:外设地址
//cmar:存储器地址
//cndtr:数据传输量 
void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输时钟
	
    DMA_DeInit(DMA_CHx);   //将DMA的通道1寄存器重设为缺省值

	DMA1_MEM_LEN=cndtr;
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  //DMA外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //数据传输方向，从外设读取发送到内存
	DMA_InitStructure.DMA_BufferSize = cndtr;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //数据宽度为8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //数据宽度为8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //工作在正常模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道 x拥有中优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA_CHx, &DMA_InitStructure);  //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE); //使能串口的DMA接收 
	DMA_ClearFlag(DMA1_FLAG_TC6); //清除DMA接收完成标志
	DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);//DMA传输完成中断
	DMA_NVIC_Config();
	DMA_Cmd(DMA_CHx, ENABLE);  //使能USART2 TX DMA1 所指示的通道 
} 
/**********************************************************************************************
	*函数名：void DMA_NVIC_Config(void)
	* 参 数
	* 返回值：
	* 功能：配置串口DMA的中断优先级
	**********************************************************************************************/
void DMA_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//开启一次DMA传输
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{   
    DMA_ClearFlag(DMA1_FLAG_TC6); //清除DMA接收完成标志	
 	DMA_SetCurrDataCounter(DMA_CHx,DMA1_MEM_LEN);//DMA通道的DMA缓存的大小
 	DMA_Cmd(DMA_CHx, ENABLE);  //使能USART2 TX DMA1 所指示的通道 
}	  
//关闭一次DMA传输
void MYDMA_Disable(DMA_Channel_TypeDef*DMA_CHx)
{
	DMA_Cmd(DMA_CHx, DISABLE); 
}

/*void DMA1_Channel6_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC6)) //通道5传输完成中断TC 还有传输 过半中断HT 错误中断TE 全局中断GL
     {
       MYDMA_Disable(DMA1_Channel6);
	   //DataCounter = DMA_GetCurrDataCounter(DMA1_Channel5);//获取剩余长度,一般都为0,调试用
       DMA_ClearITPendingBit(DMA1_IT_GL6);    //清除全部中断标志
	   MYDMA_Enable(DMA1_Channel6);    
     }
}*/

 

























