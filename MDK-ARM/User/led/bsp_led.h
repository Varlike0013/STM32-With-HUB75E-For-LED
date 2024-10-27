#ifndef __LED_H
#define	__LED_H

#include "stm32h7xx.h"
#include "bsp_key.h"
#include "core_delay.h"

//���Ŷ���
/*******************************************************/
//R ��ɫ��
#define LED_R_PIN                  GPIO_PIN_0                 
#define LED_R_GPIO_PORT            GPIOB                      
#define LED_R_GPIO_CLK_ENABLE()    __GPIOB_CLK_ENABLE()

//G ��ɫ��
#define LED_G_PIN                  GPIO_PIN_1                 
#define LED_G_GPIO_PORT            GPIOB                      
#define LED_G_GPIO_CLK_ENABLE()    __GPIOB_CLK_ENABLE()

//B ��ɫ��
#define LED_B_PIN                  GPIO_PIN_3                 
#define LED_B_GPIO_PORT            GPIOA                       
#define LED_B_GPIO_CLK_ENABLE()    __GPIOA_CLK_ENABLE()

/************************************************************/


/** ����LED������ĺ꣬
	* LED�͵�ƽ��������ON=0��OFF=1
	* ��LED�ߵ�ƽ�����Ѻ����ó�ON=1 ��OFF=0 ����
	*/
#define ON  GPIO_PIN_RESET
#define OFF GPIO_PIN_SET
#define MAX_LED_NUM 7

/* ���κ꣬��������������һ��ʹ�� */
#define LED_R(a)	HAL_GPIO_WritePin(LED_R_GPIO_PORT,LED_R_PIN,a)


#define LED_G(a)	HAL_GPIO_WritePin(LED_G_GPIO_PORT,LED_G_PIN,a)


#define LED_B(a)	HAL_GPIO_WritePin(LED_B_GPIO_PORT,LED_B_PIN,a)


/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)				{p->BSRR=i;}			  //����Ϊ�ߵ�ƽ		
#define digitalLo(p,i)				{p->BSRR=i<<16;}				//����͵�ƽ
#define digitalToggle(p,i)		{p->ODR ^=i;}			//�����ת״̬


/* �������IO�ĺ� */
#define LED_R_TOGGLE		digitalToggle(LED_R_GPIO_PORT,LED_R_PIN)
#define LED_R_OFF			digitalHi(LED_R_GPIO_PORT,LED_R_PIN)
#define LED_R_ON				digitalLo(LED_R_GPIO_PORT,LED_R_PIN)

#define LED_G_TOGGLE		digitalToggle(LED_G_GPIO_PORT,LED_G_PIN)
#define LED_G_OFF			digitalHi(LED_G_GPIO_PORT,LED_G_PIN)
#define LED_G_ON				digitalLo(LED_G_GPIO_PORT,LED_G_PIN)

#define LED_B_TOGGLE		digitalToggle(LED_B_GPIO_PORT,LED_B_PIN)
#define LED_B_OFF			digitalHi(LED_B_GPIO_PORT,LED_B_PIN)
#define LED_B_ON				digitalLo(LED_B_GPIO_PORT,LED_B_PIN)


/* ������ɫ������߼��÷�ʹ��PWM�ɻ��ȫ����ɫ,��Ч������ */

//��
#define LED_RED  \
					LED_R_ON;\
					LED_G_OFF\
					LED_B_OFF
//��
#define LED_GREEN		\
					LED_R_OFF;\
					LED_G_ON\
					LED_B_OFF
//��
#define LED_BLUE	\
					LED_R_OFF;\
					LED_G_OFF\
					LED_B_ON
//��(��+��)					
#define LED_YELLOW	\
					LED_R_ON;\
					LED_G_ON\
					LED_B_OFF
//��(��+��)
#define LED_PURPLE	\
					LED_R_ON;\
					LED_G_OFF\
					LED_B_ON
//��(��+��+��)
#define LED_WHITE	\
					LED_R_ON;\
					LED_G_ON\
					LED_B_ON
//��(��+��)
#define LED_CYAN \
					LED_R_OFF;\
					LED_G_ON\
					LED_B_ON								
//��(ȫ���ر�)
#define LED_RGBOFF	\
					LED_R_OFF;\
					LED_G_OFF\
					LED_B_OFF
					




void LED_GPIO_Config(void);
void LED_ALL_LOOP(uint32_t time_us);
void LED_KEY_LOOP(void);
void Control_LED_NUM(int led_num);

#endif /* __LED_H */
