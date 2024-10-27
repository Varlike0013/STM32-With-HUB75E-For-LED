 #include "bsp_exti.h"
 #include "bsp_led.h"


 /**
  * @brief  ���� PA0 Ϊ���жϿڣ��������ж����ȼ�
  * @param  ��
  * @retval ��
  */
void EXTI_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 

	/*��������GPIO�ڵ�ʱ��*/
	KEY1_INT_GPIO_CLK_ENABLE();
	KEY2_INT_GPIO_CLK_ENABLE();

	/* ѡ�񰴼�1������ */ 
	GPIO_InitStructure.Pin = KEY1_INT_GPIO_PIN;
	/* ��������Ϊ����ģʽ */ 
	GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;	    		
	/* �������Ų�����Ҳ������ */
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	/* ʹ������Ľṹ���ʼ������ */
	HAL_GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure); 
	/* H750XBH6��PA0��PA0_C����EXTI0�ⲿ�ж�Դ���������������ĺ��̣�
	   ͨ��һ��ģ�⿪�����ӵ�Ƭ�����裬Ϊ�˱�����ţ�ʹ��ʱ��Ҫ�л� */
  /* PA0 ------> EXTI0  */
	HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PA0, SYSCFG_SWITCH_PA0_CLOSE);
	/* ���� EXTI �ж�Դ ��key1 ���š������ж����ȼ�*/
	HAL_NVIC_SetPriority(KEY1_INT_EXTI_IRQ, 0, 0);
	/* ʹ���ж� */
	HAL_NVIC_EnableIRQ(KEY1_INT_EXTI_IRQ);

	/* ѡ�񰴼�2������ */ 
	GPIO_InitStructure.Pin = KEY2_INT_GPIO_PIN;  
	/* ����������������ͬ */
	HAL_GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);      
	/* ���� EXTI �ж�Դ ��key1 ���š������ж����ȼ�*/
	HAL_NVIC_SetPriority(KEY2_INT_EXTI_IRQ, 0, 0);
	/* ʹ���ж� */
	HAL_NVIC_EnableIRQ(KEY2_INT_EXTI_IRQ);
}
//key1�жϷ���������
void KEY1_IRQHandler(void)
{
	//���key1�Ƿ���exti line�ж�
	if(__HAL_GPIO_EXTI_GET_IT(KEY1_INT_GPIO_PIN) != RESET)
	{
			LED_R_TOGGLE;//��תLED_RED
			__HAL_GPIO_EXTI_CLEAR_IT(KEY1_INT_GPIO_PIN);//����жϱ�־λ
	}
}
//key2�жϷ���������
void KEY2_IRQHandler(void)
{
	//���key1�Ƿ���exti line�ж�
	if(__HAL_GPIO_EXTI_GET_IT(KEY2_INT_GPIO_PIN) != RESET)
	{
			LED_G_TOGGLE;//��תLED_GREEN
			__HAL_GPIO_EXTI_CLEAR_IT(KEY2_INT_GPIO_PIN);//����жϱ�־λ
	}
}
/*********************************************END OF FILE**********************/
