#include "infomation.h"
void Show_Message_LED_CMD(void)
{
  printf("\r\n   Controlling RGB LED lights with commands. \n");
  printf("Using USART1 with parameters: %d 8-N-1 \n", DEBUG_USART_BAUDRATE);
  printf("   Command  ------  LED Color \n");
  printf("     1      ------    Red \n");
  printf("     2      ------    Green \n");
  printf("     3      ------    Blue \n");
  printf("     4      ------    Yellow \n");
  printf("     5      ------    Purple \n");
  printf("     6      ------    Cyan \n");
  printf("     7      ------    White \n");
  printf("     8      ------    Off \n");  
}
// 输出 PAINT 结构体信息的函数
void printPaintInfo(PAINT *paint) {
    if (paint == NULL) {
        printf(" PAINT  == NULL \n");
        return;
    }

    printf("PAINT INFO:\n");
    printf("  Image: %p\n", (void *)paint->Image);
    printf("  Width: %u\n", paint->Width);
    printf("  Height: %u\n", paint->Height);
    printf("  WidthMemory: %u\n", paint->WidthMemory);
    printf("  HeightMemory: %u\n", paint->HeightMemory);
    printf("  Color: 0x%04X\n", paint->Color);
    printf("  Rotate: %u\n", paint->Rotate);
    printf("  Mirror: %u\n", paint->Mirror);
    printf("  WidthByte: %u\n", paint->WidthByte);
    printf("  HeightByte: %u\n", paint->HeightByte);
    printf("  Scale: %u\n", paint->Scale);
}
    
// 输出 HUB75_port 结构体信息的函数
void printRGB_MatrixInfo(HUB75_port *RGB_Matrix) {
    if (RGB_Matrix == NULL) {
        printf("RGB_Matrix == NULL\n");
        return;
    }

    printf("RGB_Matrix:\n");
    printf("  BlackImage: %p\n", (void *)RGB_Matrix->BlackImage);
    printf("  Timer Period: %d ms\n", RGB_Matrix->timer_Period);
    printf("  Min Period: %d ms\n", RGB_Matrix->min_Period);
    printf("  Width: %d bits\n", RGB_Matrix->width);
    printf("  Height: %d bits\n", RGB_Matrix->height);
    printf("  All Width: %d bits\n", RGB_Matrix->all_width);
    printf("  Address Size: %d\n", RGB_Matrix->address_size);
    printf("  Column Select: %d\n", RGB_Matrix->column_select);
    printf("  Tile: %d\n", RGB_Matrix->tile);
    printf("  Plane: %d\n", RGB_Matrix->plane);
    printf("  Row: %d\n", RGB_Matrix->row);
    printf("  Bit Depth: %d\n", RGB_Matrix->bitDepth);
}
int GetPowerOfTwo(uint16_t Pin) {
    // 检查输入是否是 2 的幂
    if (Pin == 0) {
        return -1; // 不允许 0 输入
    }

    int power = 0;

    // 循环查找 Pin 是 2 的多少次方
    while (Pin > 1) {
        Pin >>= 1; // 将 Pin 右移一位，相当于除以 2
        power++;   // 每次右移增加一次指数
    }

    return power; // 返回对应的指数
}

void CheckAndPrintPinState(GPIO_TypeDef *Port, uint16_t Pin)
{
    // 读取引脚状态
    GPIO_PinState State = HAL_GPIO_ReadPin(Port, Pin);
    
    // 生成引脚名称的字符串
    const char *portName;
    switch ((uintptr_t)Port) {
        case (uintptr_t)GPIOA: portName = "GPIOA"; break;
        case (uintptr_t)GPIOB: portName = "GPIOB"; break;
        case (uintptr_t)GPIOC: portName = "GPIOC"; break;
        case (uintptr_t)GPIOD: portName = "GPIOD"; break;
        case (uintptr_t)GPIOE: portName = "GPIOE"; break;
        case (uintptr_t)GPIOF: portName = "GPIOF"; break;
        case (uintptr_t)GPIOG: portName = "GPIOG"; break;
        case (uintptr_t)GPIOH: portName = "GPIOH"; break;
				case (uintptr_t)GPIOI: portName = "GPIOI"; break;
        case (uintptr_t)GPIOJ: portName = "GPIOJ"; break;
				case (uintptr_t)GPIOK: portName = "GPIOK"; break;
        default: portName = "Unknown"; break; // 处理未知端口
    }

    // 使用 printf 输出状态
    if (State == GPIO_PIN_SET)
    {
        printf("%s Pin %d is SET (High)\n", portName, GetPowerOfTwo(Pin));
    }
    else
    {
        printf("%s Pin %d is RESET (Low)\n", portName, GetPowerOfTwo(Pin));
    }
}