#ifndef _INFOMATION_H_
#define _INFOMATION_H_

#include <stdio.h>
#include "bsp_debug_usart.h"
#include "GUI_Paint.h"
#include "RGBMatrix_device.h"

void Show_Message_LED_CMD(void);
void printPaintInfo(PAINT *paint);
void printRGB_MatrixInfo(HUB75_port *RGB_Matrix);
int GetPowerOfTwo(uint16_t Pin);
void CheckAndPrintPinState(GPIO_TypeDef *Port, uint16_t Pin);
#endif
