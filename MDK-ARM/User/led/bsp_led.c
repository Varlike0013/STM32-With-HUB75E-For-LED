#include "bsp_led.h"

int LED_NUM = 0;

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_GPIO_Config(void)
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef  GPIO_InitStruct;

	/*开启LED相关的GPIO外设时钟*/
	LED_R_GPIO_CLK_ENABLE();
	LED_G_GPIO_CLK_ENABLE();
	LED_B_GPIO_CLK_ENABLE();

	/*选择要控制的GPIO引脚*/															   
	GPIO_InitStruct.Pin = LED_R_PIN;	

	/*设置引脚的输出类型为推挽输出*/
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;  

	/*设置引脚为上拉模式*/
	GPIO_InitStruct.Pull  = GPIO_PULLUP;

	/*设置引脚速率为高速 */   
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; 

	/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
	HAL_GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStruct);	

	/*选择要控制的GPIO引脚*/															   
	GPIO_InitStruct.Pin = LED_G_PIN;	
	HAL_GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStruct);	

	/*选择要控制的GPIO引脚*/															   
	GPIO_InitStruct.Pin = LED_B_PIN;	
	HAL_GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStruct);	
	/*选择要控制的GPIO引脚*/															   
	GPIO_InitStruct.Pin = GPIO_PIN_2;	
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);	


	/*关闭RGB灯*/
	LED_RGBOFF;	
}
void LED_ALL_LOOP(uint32_t time_us)
{
		/*轮流显示 红绿蓝黄紫青白 颜色*/
		LED_RED;
		HAL_Delay(time_us);
		
		LED_GREEN;
		HAL_Delay(time_us);
		
		LED_BLUE;
		HAL_Delay(time_us);
		
		LED_YELLOW;
		HAL_Delay(time_us);
		
		LED_PURPLE;
		HAL_Delay(time_us);
						
		LED_CYAN;
		HAL_Delay(time_us);
		
		LED_WHITE;
		HAL_Delay(time_us);
		
		LED_RGBOFF;
		HAL_Delay(time_us);
}
void Control_LED_NUM(int led_num)
{
		switch(led_num)
		{
			case 0:LED_RED;break;
			case 1:LED_GREEN;break;
			case 2:LED_BLUE;break;
			case 3:LED_YELLOW;break;
			case 4:LED_PURPLE;break;
			case 5:LED_CYAN;break;
			case 6:LED_WHITE;break;
			case 7:LED_RGBOFF;break;
			default:break;
		}
}
// LED 控制循环
void LED_KEY_LOOP(void)
{
    /* 检测 KEY1 是否有输入 */
    if (Key_Scan(KEY1_GPIO_PORT, KEY1_PIN) == KEY_ON)
    {
        if (LED_NUM < MAX_LED_NUM)  // 确保不超过最大值
        {
            LED_NUM += 1;           // 增加 LED 数量
        }
				else
				{
						LED_NUM = 0;
				}
    }
    
    /* 检测 KEY2 是否有输入 */
    if (Key_Scan(KEY2_GPIO_PORT, KEY2_PIN) == KEY_ON)
    {
        if (LED_NUM > 0)           // 确保不小于 0
        {
            LED_NUM -= 1;          // 减少 LED 数量
        }
				else
				{
						LED_NUM = MAX_LED_NUM;
				}
    }

    // 更新 LED 状态
    Control_LED_NUM(LED_NUM);          // 控制实际 LED 状态
}
/*********************************************END OF FILE**********************/
