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
	
//LED-64*64板变量
	uint16_t width = 64; //length of a single screen
	uint8_t address_size = 5; //The number of digits in the address, for example: 1/32 scan is a 5-digit address
	uint8_t bitDepth=4; //Bit depth setting, up to 4 bits 
	uint8_t model = 1;
	//蓝牙数据数组
	char* redata;
	uint16_t len = 0;
	static uint8_t hc05_role=0;
	unsigned long count;
	
	char hc05_mode[10]="SLAVE";
	char hc05_name[30]="HC05_SLAVE";
	char hc05_nameCMD[40];
	char disp_buff[200];

	
	HAL_Init();
	
  SystemClock_Config();/* 系统时钟初始化成480MHz */
	MX_GPIO_Init();//其他io口初始化
	MX_USART2_UART_Init();//串口USART2初始化
  MX_TIM1_Init();//
	DWT_Init();//
	LED_GPIO_Config();//led_io口定义（R:PB0-G:PB1-B:PA3）
	Key_GPIO_Config();//key_io口定义（KEY1:PA0-KEY2:PC13）
	SysTick_Init();//初始化自定义系统定时器，在"stm32h7xx_it.h"文件中切换为自定义系统定时器SysTick_Handler()后可用
	DEBUG_USART_Config();/* 串口初始化 */
	//EXTI_Key_Config();//启动key中断检测,启动后当key1发送中断时反转LED_RED。
	//HAL_RCC_MCOConfig(RCC_MCO2, RCC_MCO2SOURCE_SYSCLK, RCC_MCODIV_4);//MCO2输出SYSCLK
	
	LED_GREEN;
	HUB75_Init(width,address_size,bitDepth);//HUB75 initialization
	Clock_init(2024,10,21,16,06,30);//初始化时钟时间YEAR--MONTH--DAY--HOUR--MIN--SEC
			
	if((RGB_Matrix.BlackImage = (UWORD *)malloc(RGB_Matrix.width * RGB_Matrix.height * 2)) == NULL) 
	{
		printf("Failed to apply for black memory...\r\n");
		while(1);
	}
		
	Paint_NewImage(RGB_Matrix.BlackImage,RGB_Matrix.width, RGB_Matrix.height, 0, BLACK);//初始化绘制图层
		 
	HUB75_show();//启动TIM计算器，开启HUB75接口和显示图像
	
	Paint_Clear(BLACK);
	Paint_System_Start();//显示系统启动界面
	HAL_Delay(1000);
		
//	Paint_Clear(BLACK);
//	Paint_DrawImage(gImage_varlike,0,0,64,64);
//	HAL_Delay(5000);
	
	//蓝牙测试
	HC05_INFO("**********HC05模块实验************");
	delay_ms(200);
	if(HC05_Init() == 0)
	{
		HC05_INFO("HC05模块检测正常。");

	}
	else
	{
		HC05_ERROR("HC05模块检测不正常，请检查模块与开发板的连接，然后复位开发板重新测试。");
		while(1);
	}
	/*复位、恢复默认状态*/
	delay_ms(200);
	HC05_Send_CMD("AT+RESET\r\n",1);	
	delay_ms(800);
	HC05_Send_CMD("AT+ORGL\r\n",1);
	delay_ms(200);
//	/*各种命令测试演示，默认不显示。
//	 *在bsp_hc05.h文件把HC05_DEBUG_ON 宏设置为1，
//	 *即可通过串口调试助手接收调试信息*/	
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
	
	/*初始化SPP规范*/
	delay_ms(800);
	HC05_Send_CMD("AT+INIT\r\n",1);
	delay_ms(200);
	HC05_Send_CMD("AT+CLASS=0\r\n",1);
	delay_ms(200);
	HC05_Send_CMD("AT+INQM=1,9,48\r\n",1);
	
	/*设置模块名字*/
	
	sprintf(hc05_nameCMD,"AT+NAME=%s\r\n",hc05_name);
	delay_ms(200);
	HC05_Send_CMD(hc05_nameCMD,1);
	HC05_INFO("本模块名字为:%s ,模块已准备就绪。",hc05_name);
	sprintf(disp_buff,"Device name:%s",hc05_name);
	model = 2;
	delay_ms(400);
  while (1)
  {
		if(model == 1){Paint_Clear(BLACK);Paint_Clock();HAL_Delay(1000);}
		if(model == 2)
		{
		//搜索蓝牙模块，并进行连接
		if(Task_Delay[2]==0 && !IS_HC05_CONNECTED() ) 
		{
			if(hc05_role == 1)	//主模式
			{
				static uint8_t color=0;
				
				HC05_INFO("正在扫描蓝牙设备...");		
				
				if(color==0)	
				{
					color=1;
				}
				else
				{

					color=0;
				}				

				/*搜索蓝牙模块，并进行连接*/
				linkHC05();
				Task_Delay[2]=3000; //此值每1ms会减1，减到0才可以重新进来这里，所以执行的周期是3s

			}
			else	//从模式
			{
					
					delay_ms(400);
					HC05_Send_CMD("AT+INQ\r\n",1);//模块在查询状态，才能容易被其它设备搜索到
					delay_ms(800);
					HC05_Send_CMD("AT+INQC\r\n",1);//中断查询，防止查询的结果干扰串口透传的接收	
					Task_Delay[2]=2000; //此值每1ms会减1，减到0才可以重新进来这里，所以执行的周期是2s
			}
			
		}				
		
		//连接后每隔一段时间检查接收缓冲区
		if(Task_Delay[0]==0 && IS_HC05_CONNECTED())  
		{
				uint16_t linelen;


				/*获取数据*/
				redata = get_rebuff(&len); 
				linelen = get_line(linebuff,redata,len);
			
				/*检查数据是否有更新*/
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
						/*这里只演示显示单行的数据，如果想显示完整的数据，可直接使用redata数组*/
						HC05_INFO("receive:\r\n%s",linebuff);
						

					}
					
					/*处理数据后，清空接收蓝牙模块数据的缓冲区*/
					clean_rebuff();
					
				}
			Task_Delay[0]=700;//此值每1ms会减1，减到0才可以重新进来这里，所以执行的周期是500ms
		}
		
		//连接后每隔一段时间通过蓝牙模块发送字符串
		if(Task_Delay[1]==0 && IS_HC05_CONNECTED())
		{
			static uint8_t testdata=0;
		
			sprintf(sendData,"<%s> send data test,testdata=%d\r\n",hc05_name,testdata++);
			HC05_SendString(sendData);			

			Task_Delay[1]=50000;//此值每1ms会减1，减到0才可以重新进来这里，所以执行的周期是5000ms

		}		
		
			//如果KEY1被单击，切换master-slave模式
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
								HC05_INFO("设备名字被更改为：%s",hc05_name);
								
								sprintf(disp_buff,"Device name: %s",hc05_name);

							}
							else
							{							
								HC05_ERROR("更改名字失败");
								
							}
							
							HC05_Send_CMD("AT+INIT\r\n",1);
							HC05_Send_CMD("AT+CLASS=0\r\n",1);
							HC05_Send_CMD("AT+INQM=1,9,48\r\n",1);
							
							//清空蓝牙设备列表
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
							HC05_INFO("设备名字被更改为：%s",hc05_name);
							sprintf(disp_buff,"Device name: %s",hc05_name);
							

						}
						else
						{
							HC05_ERROR("更改名字失败");
							
						}
							
						HC05_Send_CMD("AT+INIT\r\n",1);
						HC05_Send_CMD("AT+CLASS=0\r\n",1);
						HC05_Send_CMD("AT+INQM=1,9,48\r\n",1);	
						
						//清空蓝牙设备列表
						bltDevList.num = 0;

					}					

				}

			}
		
			//如果KEY2被单击，随机生成一个名字
			if( Key_Scan(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON  )
			{
					/*生成随机数，给名字随机编号*/
					get_tick_count(&count);
					srand(count);
				
					sprintf(hc05_name,"HC05_%s_%d",hc05_mode,(uint8_t)rand());
					sprintf(hc05_nameCMD,"AT+NAME=%s\r\n",hc05_name);
					
					if(HC05_Send_CMD(hc05_nameCMD,1) == 0)
					{
						HC05_INFO("设备名字被更改为：%s",hc05_name);
						sprintf(disp_buff,"Device name: %s",hc05_name);
						

					}
					else
					{
						HC05_ERROR("更改名字失败");
						
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

