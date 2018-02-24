#include "dma.h"
//////////////////////////////////////////////////////////////////////////////////	 
    //DMA��ͨ����
	//USART1-TX   : CH4
	//USART1-RX   : CH5
	//USART2-TX   : CH7
	//USART2-RX   : CH6
	//USART3-TX   : CH2
	//USART3-RX   : CH3
//////////////////////////////////////////////////////////////////////////////////

DMA_InitTypeDef DMA_InitStructure;

u16 DMA1_MEM_LEN;//����DMAÿ�����ݴ��͵ĳ��� 	    
//DMA1�ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
//�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
//DMA_CHx:DMAͨ��CHx
//cpar:�����ַ
//cmar:�洢����ַ
//cndtr:���ݴ����� 
void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����ʱ��
	
    DMA_DeInit(DMA_CHx);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ

	DMA1_MEM_LEN=cndtr;
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  //DMA�������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //���ݴ��䷽�򣬴������ȡ���͵��ڴ�
	DMA_InitStructure.DMA_BufferSize = cndtr;  //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //����������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA_CHx, &DMA_InitStructure);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE); //ʹ�ܴ��ڵ�DMA���� 
	DMA_ClearFlag(DMA1_FLAG_TC6); //���DMA������ɱ�־
	DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);//DMA��������ж�
	DMA_NVIC_Config();
	DMA_Cmd(DMA_CHx, ENABLE);  //ʹ��USART2 TX DMA1 ��ָʾ��ͨ�� 
} 
/**********************************************************************************************
	*��������void DMA_NVIC_Config(void)
	* �� ���U
	* ����ֵ��
	* ���ܣ����ô���DMA���ж����ȼ�
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

//����һ��DMA����
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{   
    DMA_ClearFlag(DMA1_FLAG_TC6); //���DMA������ɱ�־	
 	DMA_SetCurrDataCounter(DMA_CHx,DMA1_MEM_LEN);//DMAͨ����DMA����Ĵ�С
 	DMA_Cmd(DMA_CHx, ENABLE);  //ʹ��USART2 TX DMA1 ��ָʾ��ͨ�� 
}	  
//�ر�һ��DMA����
void MYDMA_Disable(DMA_Channel_TypeDef*DMA_CHx)
{
	DMA_Cmd(DMA_CHx, DISABLE); 
}

/*void DMA1_Channel6_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC6)) //ͨ��5��������ж�TC ���д��� �����ж�HT �����ж�TE ȫ���ж�GL
     {
       MYDMA_Disable(DMA1_Channel6);
	   //DataCounter = DMA_GetCurrDataCounter(DMA1_Channel5);//��ȡʣ�೤��,һ�㶼Ϊ0,������
       DMA_ClearITPendingBit(DMA1_IT_GL6);    //���ȫ���жϱ�־
	   MYDMA_Enable(DMA1_Channel6);    
     }
}*/

 

























