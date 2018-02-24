#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "dma.h"
#include "DJI_RC.h"

/************************************************
 ALIENTEK战舰STM32开发板实验22
 DMA 实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
u16 ch0,ch1,ch2,ch3,s1,s2;
u8 re_flag;

 int main(void)
 {	
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	LED_Init();		  		//初始化与LED连接的硬件接口
	LCD_Init();			   	//初始化LCD 	
	KEY_Init();				//按键初始化
	RC_Init();
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(30,50,200,16,16,"DJI DR16 RC");	
	LCD_ShowString(30,70,200,16,16," STM32F103");	
	LCD_ShowString(30,90,200,16,16,"Huangmaoliang");
	LCD_ShowString(30,110,200,16,16,"2017/3/1");	
 	
	 LCD_ShowString(30,150,200,16,16,"ch0 :    ");
	 LCD_ShowString(30,170,200,16,16,"ch1 :    ");
	 LCD_ShowString(30,190,200,16,16,"ch2 :    ");
	 LCD_ShowString(30,210,200,16,16,"ch3 :    ");
	 LCD_ShowString(30,230,200,16,16,"s1  :    ");
	 LCD_ShowString(30,250,200,16,16,"s2  :    ");
	 LCD_ShowString(30,270,200,16,16,"test:    ");
	 
	 while(1)
	 {
	  if(re_flag==1)
	  {
		  LCD_ShowNum(30+48+8,150,ch0,4,16);
		  LCD_ShowNum(30+48+8,170,ch1,4,16);
		  LCD_ShowNum(30+48+8,190,ch2,4,16);
		  LCD_ShowNum(30+48+8,210,ch3,4,16);
		  LCD_ShowNum(30+48+8,230,s1,3,16);
		  LCD_ShowNum(30+48+8,250,s2,3,16);
	 // LCD_ShowNum(30+48+8,270,p,3,16);
	 // LCD_ShowNum(30+48+8,290,RC_Receive[17],3,16); 
		  re_flag=0;
	  }
	 }
}
