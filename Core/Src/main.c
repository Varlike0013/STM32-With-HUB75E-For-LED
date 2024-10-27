/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "usart.h"
#include "image.h"

#include "stm32h7xx_hal_uart.h"
#include "stm32h7xx_hal_tim.h"

#include "bsp_led.h"
#include "core_delay.h"
#include "bsp_clkconfig.h"
#include "bsp_exti.h"
#include "bsp_SysTick.h"
#include "bsp_mpu.h"
#include "bsp_debug_usart.h"
#include "bsp_blt_usart.h"
#include "bsp_hc05.h"
#include "bsp_key.h"

#include "infomation.h"
#include "RGBMatrix_device.h"
#include "GUI_Paint.h"

#include <stdlib.h>
#include <string.h>


unsigned int Task_Delay[NumOfTask]; 
BLTDev bltDevList;
char sendData[1024];
char linebuff[1024];
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	
//LED-64*64�����
	uint16_t width = 64; //length of a single screen
	uint8_t address_size = 5; //The number of digits in the address, for example: 1/32 scan is a 5-digit address
	uint8_t bitDepth=4; //Bit depth setting, up to 4 bits 
	uint8_t model = 1;
	//������������
	char* redata;
	uint16_t len = 0;
	static uint8_t hc05_role=0;
	unsigned long count;
	
	char hc05_mode[10]="SLAVE";
	char hc05_name[30]="HC05_SLAVE";
	char hc05_nameCMD[40];
	char disp_buff[200];

	
	HAL_Init();
	
  SystemClock_Config();/* ϵͳʱ�ӳ�ʼ����480MHz */
	MX_GPIO_Init();//����io�ڳ�ʼ��
	MX_USART2_UART_Init();//����USART2��ʼ��
  MX_TIM1_Init();//
	DWT_Init();//
	LED_GPIO_Config();//led_io�ڶ��壨R:PB0-G:PB1-B:PA3��
	Key_GPIO_Config();//key_io�ڶ��壨KEY1:PA0-KEY2:PC13��
	SysTick_Init();//��ʼ���Զ���ϵͳ��ʱ������"stm32h7xx_it.h"�ļ����л�Ϊ�Զ���ϵͳ��ʱ��SysTick_Handler()�����
	DEBUG_USART_Config();/* ���ڳ�ʼ�� */
	//EXTI_Key_Config();//����key�жϼ��,������key1�����ж�ʱ��תLED_RED��
	//HAL_RCC_MCOConfig(RCC_MCO2, RCC_MCO2SOURCE_SYSCLK, RCC_MCODIV_4);//MCO2���SYSCLK
	
	LED_GREEN;
	HUB75_Init(width,address_size,bitDepth);//HUB75 initialization
	Clock_init(2024,10,21,16,06,30);//��ʼ��ʱ��ʱ��YEAR--MONTH--DAY--HOUR--MIN--SEC
			
	if((RGB_Matrix.BlackImage = (UWORD *)malloc(RGB_Matrix.width * RGB_Matrix.height * 2)) == NULL) 
	{
		printf("Failed to apply for black memory...\r\n");
		while(1);
	}
		
	Paint_NewImage(RGB_Matrix.BlackImage,RGB_Matrix.width, RGB_Matrix.height, 0, BLACK);//��ʼ������ͼ��
		 
	HUB75_show();//����TIM������������HUB75�ӿں���ʾͼ��
	
	Paint_Clear(BLACK);
	Paint_System_Start();//��ʾϵͳ��������
	HAL_Delay(1000);
		
//	Paint_Clear(BLACK);
//	Paint_DrawImage(gImage_varlike,0,0,64,64);
//	HAL_Delay(5000);
	
	//��������
	HC05_INFO("**********HC05ģ��ʵ��************");
	delay_ms(200);
	if(HC05_Init() == 0)
	{
		HC05_INFO("HC05ģ����������");

	}
	else
	{
		HC05_ERROR("HC05ģ���ⲻ����������ģ���뿪��������ӣ�Ȼ��λ���������²��ԡ�");
		while(1);
	}
	/*��λ���ָ�Ĭ��״̬*/
	delay_ms(200);
	HC05_Send_CMD("AT+RESET\r\n",1);	
	delay_ms(800);
	HC05_Send_CMD("AT+ORGL\r\n",1);
	delay_ms(200);
//	/*�������������ʾ��Ĭ�ϲ���ʾ��
//	 *��bsp_hc05.h�ļ���HC05_DEBUG_ON ������Ϊ1��
//	 *����ͨ�����ڵ������ֽ��յ�����Ϣ*/	
	delay_ms(200);
	HC05_Send_CMD("AT+VERSION?\r\n",1);
	delay_ms(400);
	HC05_Send_CMD("AT+ADDR?\r\n",1);
	
	HC05_Send_CMD("AT+UART?\r\n",1);
	
	HC05_Send_CMD("AT+CMODE?\r\n",1);
	delay_ms(200);
	HC05_Send_CMD("AT+STATE?\r\n",1);	
	delay_ms(400);
	HC05_Send_CMD("AT+ROLE=0\r\n",1);
	
	/*��ʼ��SPP�淶*/
	delay_ms(800);
	HC05_Send_CMD("AT+INIT\r\n",1);
	delay_ms(200);
	HC05_Send_CMD("AT+CLASS=0\r\n",1);
	delay_ms(200);
	HC05_Send_CMD("AT+INQM=1,9,48\r\n",1);
	
	/*����ģ������*/
	
	sprintf(hc05_nameCMD,"AT+NAME=%s\r\n",hc05_name);
	delay_ms(200);
	HC05_Send_CMD(hc05_nameCMD,1);
	HC05_INFO("��ģ������Ϊ:%s ,ģ����׼��������",hc05_name);
	sprintf(disp_buff,"Device name:%s",hc05_name);
	model = 2;
	delay_ms(400);
  while (1)
  {
		if(model == 1){Paint_Clear(BLACK);Paint_Clock();HAL_Delay(1000);}
		if(model == 2)
		{
		//��������ģ�飬����������
		if(Task_Delay[2]==0 && !IS_HC05_CONNECTED() ) 
		{
			if(hc05_role == 1)	//��ģʽ
			{
				static uint8_t color=0;
				
				HC05_INFO("����ɨ�������豸...");		
				
				if(color==0)	
				{
					color=1;
				}
				else
				{

					color=0;
				}				

				/*��������ģ�飬����������*/
				linkHC05();
				Task_Delay[2]=3000; //��ֵÿ1ms���1������0�ſ������½����������ִ�е�������3s

			}
			else	//��ģʽ
			{
					
					delay_ms(400);
					HC05_Send_CMD("AT+INQ\r\n",1);//ģ���ڲ�ѯ״̬���������ױ������豸������
					delay_ms(800);
					HC05_Send_CMD("AT+INQC\r\n",1);//�жϲ�ѯ����ֹ��ѯ�Ľ�����Ŵ���͸���Ľ���	
					Task_Delay[2]=2000; //��ֵÿ1ms���1������0�ſ������½����������ִ�е�������2s
			}
			
		}				
		
		//���Ӻ�ÿ��һ��ʱ������ջ�����
		if(Task_Delay[0]==0 && IS_HC05_CONNECTED())  
		{
				uint16_t linelen;


				/*��ȡ����*/
				redata = get_rebuff(&len); 
				linelen = get_line(linebuff,redata,len);
			
				/*��������Ƿ��и���*/
				if(linelen<200 && linelen != 0)
				{
					
					if(strcmp(redata,"AT+LED1=ON")==0)
					{
						LED_R_ON;						
						HC05_SendString("+LED1:ON\r\nOK\r\n");	
									
					}
					else if(strcmp(redata,"AT+LED1=OFF")==0)
					{
						LED_R_OFF;
						HC05_SendString("+LED1:OFF\r\nOK\r\n");
						
					}
					else
					{
						/*����ֻ��ʾ��ʾ���е����ݣ��������ʾ���������ݣ���ֱ��ʹ��redata����*/
						HC05_INFO("receive:\r\n%s",linebuff);
						

					}
					
					/*�������ݺ���ս�������ģ�����ݵĻ�����*/
					clean_rebuff();
					
				}
			Task_Delay[0]=700;//��ֵÿ1ms���1������0�ſ������½����������ִ�е�������500ms
		}
		
		//���Ӻ�ÿ��һ��ʱ��ͨ������ģ�鷢���ַ���
		if(Task_Delay[1]==0 && IS_HC05_CONNECTED())
		{
			static uint8_t testdata=0;
		
			sprintf(sendData,"<%s> send data test,testdata=%d\r\n",hc05_name,testdata++);
			HC05_SendString(sendData);			

			Task_Delay[1]=50000;//��ֵÿ1ms���1������0�ſ������½����������ִ�е�������5000ms

		}		
		
			//���KEY1���������л�master-slaveģʽ
			if( Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON  )
			{
				hc05_role=!hc05_role;
				if(hc05_role == 0)
				{						
						HC05_Send_CMD("AT+RESET\r\n",1);
						delay_ms(800);

						if(HC05_Send_CMD("AT+ROLE=0\r\n",1) == 0)	
						{				
							delay_ms(100);
							
							sprintf(hc05_mode,"SLAVE");
							HC05_INFO("hc05_mode  = %s",hc05_mode);	

							sprintf(hc05_name,"HC05_%s_%d",hc05_mode,(uint8_t)rand());
							sprintf(hc05_nameCMD,"AT+NAME=%s\r\n",hc05_name);
							
							if(HC05_Send_CMD(hc05_nameCMD,1) == 0)
							{
								HC05_INFO("�豸���ֱ�����Ϊ��%s",hc05_name);
								
								sprintf(disp_buff,"Device name: %s",hc05_name);

							}
							else
							{							
								HC05_ERROR("��������ʧ��");
								
							}
							
							HC05_Send_CMD("AT+INIT\r\n",1);
							HC05_Send_CMD("AT+CLASS=0\r\n",1);
							HC05_Send_CMD("AT+INQM=1,9,48\r\n",1);
							
							//��������豸�б�
							bltDevList.num = 0;
						}
						


				}
				else
				{
					HC05_Send_CMD("AT+RESET\r\n",1);
					delay_ms(800);
					
					if(HC05_Send_CMD("AT+ROLE=1\r\n",1) == 0)	
					{
						delay_ms(100);
						
						sprintf(hc05_mode,"MASTER");
						HC05_INFO("HC05 mode  = %s",hc05_mode);
							
						sprintf(hc05_name,"HC05_%s_%d",hc05_mode,(uint8_t)rand());
						sprintf(hc05_nameCMD,"AT+NAME=%s\r\n",hc05_name);	
						
						if(HC05_Send_CMD(hc05_nameCMD,1) == 0)
						{
							HC05_INFO("�豸���ֱ�����Ϊ��%s",hc05_name);
							sprintf(disp_buff,"Device name: %s",hc05_name);
							

						}
						else
						{
							HC05_ERROR("��������ʧ��");
							
						}
							
						HC05_Send_CMD("AT+INIT\r\n",1);
						HC05_Send_CMD("AT+CLASS=0\r\n",1);
						HC05_Send_CMD("AT+INQM=1,9,48\r\n",1);	
						
						//��������豸�б�
						bltDevList.num = 0;

					}					

				}

			}
		
			//���KEY2���������������һ������
			if( Key_Scan(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON  )
			{
					/*�����������������������*/
					get_tick_count(&count);
					srand(count);
				
					sprintf(hc05_name,"HC05_%s_%d",hc05_mode,(uint8_t)rand());
					sprintf(hc05_nameCMD,"AT+NAME=%s\r\n",hc05_name);
					
					if(HC05_Send_CMD(hc05_nameCMD,1) == 0)
					{
						HC05_INFO("�豸���ֱ�����Ϊ��%s",hc05_name);
						sprintf(disp_buff,"Device name: %s",hc05_name);
						

					}
					else
					{
						HC05_ERROR("��������ʧ��");
						
					}
			}
		}		
  }
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

