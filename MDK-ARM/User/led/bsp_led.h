#ifndef __LED_H
#define	__LED_H

#include "stm32h7xx.h"
#include "bsp_key.h"
#include "core_delay.h"

//引脚定义
/*******************************************************/
//R 红色灯
#define LED_R_PIN                  GPIO_PIN_0                 
#define LED_R_GPIO_PORT            GPIOB                      
#define LED_R_GPIO_CLK_ENABLE()    __GPIOB_CLK_ENABLE()

//G 绿色灯
#define LED_G_PIN                  GPIO_PIN_1                 
#define LED_G_GPIO_PORT            GPIOB                      
#define LED_G_GPIO_CLK_ENABLE()    __GPIOB_CLK_ENABLE()

//B 蓝色灯
#define LED_B_PIN                  GPIO_PIN_3                 
#define LED_B_GPIO_PORT            GPIOA                       
#define LED_B_GPIO_CLK_ENABLE()    __GPIOA_CLK_ENABLE()

/************************************************************/


/** 控制LED灯亮灭的宏，
	* LED低电平亮，设置ON=0，OFF=1
	* 若LED高电平亮，把宏设置成ON=1 ，OFF=0 即可
	*/
#define ON  GPIO_PIN_RESET
#define OFF GPIO_PIN_SET
#define MAX_LED_NUM 7

/* 带参宏，可以像内联函数一样使用 */
#define LED_R(a)	HAL_GPIO_WritePin(LED_R_GPIO_PORT,LED_R_PIN,a)


#define LED_G(a)	HAL_GPIO_WritePin(LED_G_GPIO_PORT,LED_G_PIN,a)


#define LED_B(a)	HAL_GPIO_WritePin(LED_B_GPIO_PORT,LED_B_PIN,a)


/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)				{p->BSRR=i;}			  //设置为高电平		
#define digitalLo(p,i)				{p->BSRR=i<<16;}				//输出低电平
#define digitalToggle(p,i)		{p->ODR ^=i;}			//输出反转状态


/* 定义控制IO的宏 */
#define LED_R_TOGGLE		digitalToggle(LED_R_GPIO_PORT,LED_R_PIN)
#define LED_R_OFF			digitalHi(LED_R_GPIO_PORT,LED_R_PIN)
#define LED_R_ON				digitalLo(LED_R_GPIO_PORT,LED_R_PIN)

#define LED_G_TOGGLE		digitalToggle(LED_G_GPIO_PORT,LED_G_PIN)
#define LED_G_OFF			digitalHi(LED_G_GPIO_PORT,LED_G_PIN)
#define LED_G_ON				digitalLo(LED_G_GPIO_PORT,LED_G_PIN)

#define LED_B_TOGGLE		digitalToggle(LED_B_GPIO_PORT,LED_B_PIN)
#define LED_B_OFF			digitalHi(LED_B_GPIO_PORT,LED_B_PIN)
#define LED_B_ON				digitalLo(LED_B_GPIO_PORT,LED_B_PIN)


/* 基本混色，后面高级用法使用PWM可混出全彩颜色,且效果更好 */

//红
#define LED_RED  \
					LED_R_ON;\
					LED_G_OFF\
					LED_B_OFF
//绿
#define LED_GREEN		\
					LED_R_OFF;\
					LED_G_ON\
					LED_B_OFF
//蓝
#define LED_BLUE	\
					LED_R_OFF;\
					LED_G_OFF\
					LED_B_ON
//黄(红+绿)					
#define LED_YELLOW	\
					LED_R_ON;\
					LED_G_ON\
					LED_B_OFF
//紫(红+蓝)
#define LED_PURPLE	\
					LED_R_ON;\
					LED_G_OFF\
					LED_B_ON
//白(红+绿+蓝)
#define LED_WHITE	\
					LED_R_ON;\
					LED_G_ON\
					LED_B_ON
//青(绿+蓝)
#define LED_CYAN \
					LED_R_OFF;\
					LED_G_ON\
					LED_B_ON								
//黑(全部关闭)
#define LED_RGBOFF	\
					LED_R_OFF;\
					LED_G_OFF\
					LED_B_OFF
					




void LED_GPIO_Config(void);
void LED_ALL_LOOP(uint32_t time_us);
void LED_KEY_LOOP(void);
void Control_LED_NUM(int led_num);

#endif /* __LED_H */
