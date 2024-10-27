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
// ��� PAINT �ṹ����Ϣ�ĺ���
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
    
// ��� HUB75_port �ṹ����Ϣ�ĺ���
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
    // ��������Ƿ��� 2 ����
    if (Pin == 0) {
        return -1; // ������ 0 ����
    }

    int power = 0;

    // ѭ������ Pin �� 2 �Ķ��ٴη�
    while (Pin > 1) {
        Pin >>= 1; // �� Pin ����һλ���൱�ڳ��� 2
        power++;   // ÿ����������һ��ָ��
    }

    return power; // ���ض�Ӧ��ָ��
}

void CheckAndPrintPinState(GPIO_TypeDef *Port, uint16_t Pin)
{
    // ��ȡ����״̬
    GPIO_PinState State = HAL_GPIO_ReadPin(Port, Pin);
    
    // �����������Ƶ��ַ���
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
        default: portName = "Unknown"; break; // ����δ֪�˿�
    }

    // ʹ�� printf ���״̬
    if (State == GPIO_PIN_SET)
    {
        printf("%s Pin %d is SET (High)\n", portName, GetPowerOfTwo(Pin));
    }
    else
    {
        printf("%s Pin %d is RESET (Low)\n", portName, GetPowerOfTwo(Pin));
    }
}