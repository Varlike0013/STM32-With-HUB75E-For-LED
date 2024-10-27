#include "RGBMatrix_device.h"
#include "bsp_debug_usart.h"
#include <stdio.h>

HUB75_port RGB_Matrix;
/**
 * Initialization routine.
 * You might need to enable access to DWT registers on Cortex-M7
 *   DWT->LAR = 0xC5ACCE55
 */
void DWT_Init(void)
{
    if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)) {
        CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
        DWT->CYCCNT = 0;
        DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    }
}

/**
 * Delay routine itself.
 * Time is in microseconds (1/1000000th of a second), not to be
 * confused with millisecond (1/1000th).
 *
 * No need to check an overflow. Let it just tick :)
 *
 * @param uint32_t us  Number of microseconds to delay for
 */
void DWT_Delay(uint32_t us) // microseconds
{
    uint32_t startTick = DWT->CYCCNT,
             delayTicks = us * (SystemCoreClock/1000000);

    while (DWT->CYCCNT - startTick < delayTicks);
}


void HUB75E_DelayUs(int us) {
	HAL_Delay(us);
}



/**
 * HUB75 Initialization.
 * Give the buffer address to the GUI
 *  
 */
uint32_t _PM_timerSave;
uint32_t freq = 0;
void HUB75_show()
{
	HAL_TIM_Base_Start_IT(&htim1);
	_PM_timerSave = __HAL_TIM_GET_COUNTER(&htim1); 
}

void HUB75_Init(uint8_t width,uint8_t address_size,uint8_t bitDepth)
{
	RGB_Matrix.tile = 1;
	
	RGB_Matrix.address_size = address_size;
	RGB_Matrix.column_select =  1 << (RGB_Matrix.address_size);
	
	RGB_Matrix.width = width;
	
	RGB_Matrix.height = (2 << RGB_Matrix.address_size) * abs(RGB_Matrix.tile);

	RGB_Matrix.min_Period = HUB75_MIN_PERIOD;
	RGB_Matrix.timer_Period = RGB_Matrix.min_Period;
	
	RGB_Matrix.bitDepth=bitDepth;
	
	RGB_Matrix.plane = RGB_Matrix.bitDepth; // Take a four-bit color. Due to processor speed issues, if it is too high, flickering will occur.
}




uint16_t initialRedBit = 0x0800 << 1, initialGreenBit = 0x0040 << 1, initialBlueBit = 0x0001 << 1;
//Take the four higher color RGB 11110 111100 11110
void RGBMatrixWrite_565Data(uint8_t row , uint8_t plane){
	
	if(plane == 0){
		initialRedBit   = 0x0800 << 1 ;
		initialGreenBit = 0x0040 << 1 ;
		initialBlueBit	= 0x0001 << 1 ;
	}
			
			uint16_t *upperSrc, *lowerSrc; // Canvas scanline pointers
			int16_t srcIdx;
			int8_t srcInc;
	
			for (int8_t tile = abs(RGB_Matrix.tile) - 1; tile >= 0; tile--) {
				if(RGB_Matrix.tile < 0)
				{
					lowerSrc = RGB_Matrix.BlackImage + (tile * RGB_Matrix.width * (RGB_Matrix.height / 2)) + RGB_Matrix.width * ((RGB_Matrix.height / 2) - 1 - row);
					upperSrc = lowerSrc + RGB_Matrix.width * (RGB_Matrix.height / 2); 
					srcIdx = RGB_Matrix.width - 1;                                      
					srcInc = -1;
				}
				else
				{
					upperSrc = RGB_Matrix.BlackImage + (tile * RGB_Matrix.width * (RGB_Matrix.height)) + (RGB_Matrix.width * row);
					lowerSrc = upperSrc + RGB_Matrix.width * (RGB_Matrix.height / 2); 
					srcIdx = 0;                                     
					srcInc = 1;
				}
//			ptrdiff_t addressDifference = (uintptr_t)upperSrc - (uintptr_t)RGB_Matrix.BlackImage;
//			printf("Address of upperSrc: %d bytes\n", addressDifference);
//			addressDifference = (uintptr_t)lowerSrc - (uintptr_t)RGB_Matrix.BlackImage;
//			printf("Address of lowerSrc: %d bytes\n", addressDifference);
			
			for(uint16_t x = 0; x < RGB_Matrix.width; x++, srcIdx += srcInc)
			{
				if(upperSrc[srcIdx] & initialRedBit)
					BROAD_R1_GPIO_Port->BSRR = BROAD_R1_Pin;
				else
					BROAD_R1_GPIO_Port->BSRR = (uint32_t)BROAD_R1_Pin << 16u;
				
				if(upperSrc[srcIdx] & initialGreenBit)
					BROAD_G1_GPIO_Port->BSRR = BROAD_G1_Pin;
				else
					BROAD_G1_GPIO_Port->BSRR = (uint32_t)BROAD_G1_Pin << 16u;
				
				if(upperSrc[srcIdx] & initialBlueBit)
					BROAD_B1_GPIO_Port->BSRR = BROAD_B1_Pin;
				else
					BROAD_B1_GPIO_Port->BSRR = (uint32_t)BROAD_B1_Pin << 16u;
				
				if(lowerSrc[srcIdx] & initialRedBit)
					BROAD_R2_GPIO_Port->BSRR = BROAD_R2_Pin;
				else
					BROAD_R2_GPIO_Port->BSRR = (uint32_t)BROAD_R2_Pin << 16u;
				
				if(lowerSrc[srcIdx] & initialGreenBit)
					BROAD_G2_GPIO_Port->BSRR = BROAD_G2_Pin;
				else
					BROAD_G2_GPIO_Port->BSRR = (uint32_t)BROAD_G2_Pin << 16u;
				
				if(lowerSrc[srcIdx] & initialBlueBit)
					BROAD_B2_GPIO_Port->BSRR = BROAD_B2_Pin;
				else
					BROAD_B2_GPIO_Port->BSRR = (uint32_t)BROAD_B2_Pin << 16u;

				
				 BROAD_CLK_GPIO_Port->BSRR = (uint32_t)BROAD_CLK_Pin << 16u ;

				 BROAD_CLK_GPIO_Port->BSRR = BROAD_CLK_Pin;
			} //end x
		}// end tile
				initialRedBit <<= 1;
				initialGreenBit <<= 1;
				initialBlueBit <<= 1;
		
}
//用于生成 RGB 颜色轮,接收一个参数 WheelPos（颜色轮位置），返回一个 16 位的 RGB 颜色值
uint16_t Wheel(uint8_t WheelPos) {
  if(WheelPos < 16) {
   return ((32 - WheelPos) << 11) |(WheelPos << 5) | 0;
  } else if(WheelPos < 32) {
   WheelPos -= 16;
   return 0 | ((32 - WheelPos) << 5) | WheelPos;
		
  } else {
   WheelPos -= 32;
   return (WheelPos <<11 )| 0 | (32 - WheelPos);
  }
}