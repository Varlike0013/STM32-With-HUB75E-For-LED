#include "tim.h"
#include "stm32h7xx_hal_tim.h"
#include "RGBMatrix_device.h"
#include "bsp_led.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TIM_HandleTypeDef htim1;

/* TIM1 init function */
void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 71;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspInit 0 */

  /* USER CODE END TIM1_MspInit 0 */
    /* TIM1 clock enable */
    __HAL_RCC_TIM1_CLK_ENABLE();

    /* TIM1 interrupt Init */
    HAL_NVIC_SetPriority(TIM1_UP_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
  /* USER CODE BEGIN TIM1_MspInit 1 */

  /* USER CODE END TIM1_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspDeInit 0 */

  /* USER CODE END TIM1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM1_CLK_DISABLE();

    /* TIM1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM1_UP_IRQn);
  /* USER CODE BEGIN TIM1_MspDeInit 1 */

  /* USER CODE END TIM1_MspDeInit 1 */
  }
}
//定时器中断回调函数 HAL_TIM_PeriodElapsedCallback 的实现,用于驱动 RGB 矩阵显示
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == htim1.Instance)
    {
			BROAD_OE_GPIO_Port->BSRR = BROAD_OE_Pin;

			BROAD_LAT_GPIO_Port->BSRR = (uint32_t)BROAD_LAT_Pin << 16u;
			BROAD_LAT_GPIO_Port->BSRR = BROAD_LAT_Pin;
			
			//HAL_TIM_Base_Stop_IT(&htim1);
			//uint8_t prevPlane = RGB_Matrix.plane;
			//printf("prevPlane:%d\n",prevPlane);
			BROAD_LAT_GPIO_Port->BSRR = (uint32_t)BROAD_LAT_Pin << 16u;
			
			if(RGB_Matrix.plane == 0)
			{
				if(RGB_Matrix.column_select & 0x1)
					BROAD_A_GPIO_Port->BSRR = BROAD_A_Pin;
				else
					BROAD_A_GPIO_Port->BSRR = (uint32_t)BROAD_A_Pin << 16u;
//				GPIO_PinState State = HAL_GPIO_ReadPin(BROAD_A_GPIO_Port, BROAD_A_Pin);
//				printf("%d    ",State);
				if(RGB_Matrix.column_select & 0x2)
					BROAD_B_GPIO_Port->BSRR = BROAD_B_Pin;
				else
					BROAD_B_GPIO_Port->BSRR = (uint32_t)BROAD_B_Pin << 16u;
//				State = HAL_GPIO_ReadPin(BROAD_B_GPIO_Port, BROAD_B_Pin);
//				printf("%d    ",State);
				if(RGB_Matrix.column_select & 0x4)
					BROAD_C_GPIO_Port->BSRR = BROAD_C_Pin;
				else
					BROAD_C_GPIO_Port->BSRR = (uint32_t)BROAD_C_Pin << 16u;
//				State = HAL_GPIO_ReadPin(BROAD_C_GPIO_Port, BROAD_C_Pin);
//				printf("%d    ",State);
				if(RGB_Matrix.column_select & 0x8)
					BROAD_D_GPIO_Port->BSRR = BROAD_D_Pin;
				else
					BROAD_D_GPIO_Port->BSRR = (uint32_t)BROAD_D_Pin << 16u;
//				State = HAL_GPIO_ReadPin(BROAD_D_GPIO_Port, BROAD_D_Pin);
//				printf("%d    ",State);
				if(RGB_Matrix.column_select & 0x10)
					BROAD_E_GPIO_Port->BSRR = BROAD_E_Pin;
				else
					BROAD_E_GPIO_Port->BSRR = (uint32_t)BROAD_E_Pin << 16u;
//				State = HAL_GPIO_ReadPin(BROAD_E_GPIO_Port, BROAD_E_Pin);
//				printf("%d\n",State);
			}
			if(++RGB_Matrix.plane >= RGB_Matrix.bitDepth)
			{
				RGB_Matrix.plane = 0;
				
				if(++RGB_Matrix.column_select >= (1 << RGB_Matrix.address_size))
				{
					RGB_Matrix.column_select = 0;				
				}		
			}  
//			GPIO_PinState State = HAL_GPIO_ReadPin(BROAD_G2_GPIO_Port, BROAD_G2_Pin);
//			printf("GPIO_G2_Pin_State: %d    ",State);
			//printf("column_select: %d \n", RGB_Matrix.column_select);
			__HAL_TIM_SET_COUNTER(&htim1,0);
			htim1.Instance->ARR = RGB_Matrix.timer_Period << RGB_Matrix.plane;
			
			HAL_TIM_Base_Start_IT(&htim1);
			
			BROAD_OE_GPIO_Port->BSRR = (uint32_t)BROAD_OE_Pin << 16u;;
			
			RGBMatrixWrite_565Data(RGB_Matrix.column_select,RGB_Matrix.plane);
			
			
			if(RGB_Matrix.plane == 0)
			{
				uint32_t elapsed = __HAL_TIM_GET_COUNTER(&htim1) - _PM_timerSave;
				RGB_Matrix.timer_Period = ((RGB_Matrix.timer_Period * 7) + elapsed) / 8;			
				if (RGB_Matrix.timer_Period < RGB_Matrix.min_Period) RGB_Matrix.timer_Period = RGB_Matrix.min_Period;
			}
    }
		
}