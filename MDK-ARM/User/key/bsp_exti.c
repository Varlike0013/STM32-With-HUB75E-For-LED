 #include "bsp_exti.h"
 #include "bsp_led.h"


 /**
  * @brief  配置 PA0 为线中断口，并设置中断优先级
  * @param  无
  * @retval 无
  */
void EXTI_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 

	/*开启按键GPIO口的时钟*/
	KEY1_INT_GPIO_CLK_ENABLE();
	KEY2_INT_GPIO_CLK_ENABLE();

	/* 选择按键1的引脚 */ 
	GPIO_InitStructure.Pin = KEY1_INT_GPIO_PIN;
	/* 设置引脚为输入模式 */ 
	GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;	    		
	/* 设置引脚不上拉也不下拉 */
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	/* 使用上面的结构体初始化按键 */
	HAL_GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure); 
	/* H750XBH6的PA0和PA0_C共用EXTI0外部中断源，且是两个独立的焊盘，
	   通过一个模拟开关连接到片上外设，为了避免干扰，使用时需要切换 */
  /* PA0 ------> EXTI0  */
	HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PA0, SYSCFG_SWITCH_PA0_CLOSE);
	/* 配置 EXTI 中断源 到key1 引脚、配置中断优先级*/
	HAL_NVIC_SetPriority(KEY1_INT_EXTI_IRQ, 0, 0);
	/* 使能中断 */
	HAL_NVIC_EnableIRQ(KEY1_INT_EXTI_IRQ);

	/* 选择按键2的引脚 */ 
	GPIO_InitStructure.Pin = KEY2_INT_GPIO_PIN;  
	/* 其他配置与上面相同 */
	HAL_GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);      
	/* 配置 EXTI 中断源 到key1 引脚、配置中断优先级*/
	HAL_NVIC_SetPriority(KEY2_INT_EXTI_IRQ, 0, 0);
	/* 使能中断 */
	HAL_NVIC_EnableIRQ(KEY2_INT_EXTI_IRQ);
}
//key1中断发生服务函数
void KEY1_IRQHandler(void)
{
	//检测key1是否发生exti line中断
	if(__HAL_GPIO_EXTI_GET_IT(KEY1_INT_GPIO_PIN) != RESET)
	{
			LED_R_TOGGLE;//反转LED_RED
			__HAL_GPIO_EXTI_CLEAR_IT(KEY1_INT_GPIO_PIN);//清除中断标志位
	}
}
//key2中断发生服务函数
void KEY2_IRQHandler(void)
{
	//检测key1是否发生exti line中断
	if(__HAL_GPIO_EXTI_GET_IT(KEY2_INT_GPIO_PIN) != RESET)
	{
			LED_G_TOGGLE;//反转LED_GREEN
			__HAL_GPIO_EXTI_CLEAR_IT(KEY2_INT_GPIO_PIN);//清除中断标志位
	}
}
/*********************************************END OF FILE**********************/
