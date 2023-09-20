/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   LTDC-LCD��������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� STM32  F429������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./led/bsp_led.h"
#include "./usart/bsp_debug_usart.h"
#include "./sdram/bsp_sdram.h"
#include "./lcd/bsp_lcd.h"
#include "./touch/gt9xx.h"
#include "./touch/palette.h"
#include "./systick/bsp_SysTick.h"

void Delay(__IO u32 nCount); 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	
	
  Debug_USART_Config();    
  printf("\r\nҰ��STM3F429 ���������������\r\n");

//	LED_BLUE;
	/* ��ʼ�������� */
  GTP_Init_Panel();
    
  printf("\r\n��ʾ��\r\n"
         "�����4.3��/5���RGB��Ļ��ʹ�õĴ���оƬ������GT1151QM��\r\n"
         "�����������ʾ�쳣����ȷ��ʹ�õ���Ļ����оƬ�ͺţ�"
         "�ڡ�bsp_i2c_touch.h���ļ��޸ĺ궨�� LCD_TOUCH_IC_GT1151QM��\r\n\r\n");
  
		SysTick_Init();
	/*��ʼ��Һ����*/
  LCD_Init();
	

  LCD_LayerInit();
  LTDC_Cmd(ENABLE);
	
	/*�ѱ�����ˢ��ɫ*/
  LCD_SetLayer(LCD_BACKGROUND_LAYER);  
	LCD_Clear(LCD_COLOR_BLACK);
	
  /*��ʼ����Ĭ��ʹ��ǰ����*/
	LCD_SetLayer(LCD_FOREGROUND_LAYER); 
	/*Ĭ�����ò�͸��	���ú�������Ϊ��͸���ȣ���Χ 0-0xff ��0Ϊȫ͸����0xffΪ��͸��*/
  LCD_SetTransparency(0xFF);
	LCD_Clear(LCD_COLOR_BLACK);
	
	/*���û��庯��*/
	Palette_Init();


  Delay(0xfff);
   

  while(1);
   

}



void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/

