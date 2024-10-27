#include "gpio.h"
/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
//声明GPIO端口和启用对应时钟
void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BROAD_OE_GPIO_Port, BROAD_OE_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, BROAD_G1_Pin|BROAD_R1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOJ, BROAD_LAT_Pin|BROAD_C_Pin|BROAD_B_Pin|BROAD_A_Pin
                          |BROAD_G2_Pin|BROAD_E_Pin|BROAD_B2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BROAD_CLK_GPIO_Port, BROAD_CLK_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BROAD_D_GPIO_Port, BROAD_D_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BROAD_R2_GPIO_Port, BROAD_R2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BROAD_B1_GPIO_Port, BROAD_B1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : OE_Pin */
  GPIO_InitStruct.Pin = BROAD_OE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(BROAD_OE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BROAD_G1_Pin BROAD_R1_Pin */
  GPIO_InitStruct.Pin = BROAD_G1_Pin|BROAD_R1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : LAT_Pin CLK_Pin C_Pin B_Pin
                           A_Pin BROAD_G2_Pin E_Pin BROAD_B2_Pin */
  GPIO_InitStruct.Pin = BROAD_LAT_Pin|BROAD_CLK_Pin|BROAD_C_Pin|BROAD_B_Pin
                          |BROAD_A_Pin|BROAD_G2_Pin|BROAD_E_Pin|BROAD_B2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

  /*Configure GPIO pin : D_Pin */
  GPIO_InitStruct.Pin = BROAD_D_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(BROAD_D_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BROAD_R2_Pin */
  GPIO_InitStruct.Pin = BROAD_R2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(BROAD_R2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BROAD_B1_Pin */
  GPIO_InitStruct.Pin = BROAD_B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(BROAD_B1_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}