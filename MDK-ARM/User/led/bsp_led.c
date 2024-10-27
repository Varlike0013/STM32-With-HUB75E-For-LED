#include "bsp_led.h"

int LED_NUM = 0;

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef  GPIO_InitStruct;

	/*����LED��ص�GPIO����ʱ��*/
	LED_R_GPIO_CLK_ENABLE();
	LED_G_GPIO_CLK_ENABLE();
	LED_B_GPIO_CLK_ENABLE();

	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStruct.Pin = LED_R_PIN;	

	/*�������ŵ��������Ϊ�������*/
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;  

	/*��������Ϊ����ģʽ*/
	GPIO_InitStruct.Pull  = GPIO_PULLUP;

	/*������������Ϊ���� */   
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; 

	/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
	HAL_GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStruct);	

	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStruct.Pin = LED_G_PIN;	
	HAL_GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStruct);	

	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStruct.Pin = LED_B_PIN;	
	HAL_GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStruct);	
	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStruct.Pin = GPIO_PIN_2;	
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);	


	/*�ر�RGB��*/
	LED_RGBOFF;	
}
void LED_ALL_LOOP(uint32_t time_us)
{
		/*������ʾ ������������� ��ɫ*/
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
// LED ����ѭ��
void LED_KEY_LOOP(void)
{
    /* ��� KEY1 �Ƿ������� */
    if (Key_Scan(KEY1_GPIO_PORT, KEY1_PIN) == KEY_ON)
    {
        if (LED_NUM < MAX_LED_NUM)  // ȷ�����������ֵ
        {
            LED_NUM += 1;           // ���� LED ����
        }
				else
				{
						LED_NUM = 0;
				}
    }
    
    /* ��� KEY2 �Ƿ������� */
    if (Key_Scan(KEY2_GPIO_PORT, KEY2_PIN) == KEY_ON)
    {
        if (LED_NUM > 0)           // ȷ����С�� 0
        {
            LED_NUM -= 1;          // ���� LED ����
        }
				else
				{
						LED_NUM = MAX_LED_NUM;
				}
    }

    // ���� LED ״̬
    Control_LED_NUM(LED_NUM);          // ����ʵ�� LED ״̬
}
/*********************************************END OF FILE**********************/
