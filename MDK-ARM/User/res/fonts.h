/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FONTS_H
#define __FONTS_H

/*�������΢���ź�24 (32x41) */
#define MAX_HEIGHT_FONT         41
#define MAX_WIDTH_FONT          32
#define OFFSET_BITMAP           

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

//ASCII
typedef struct _tFont
{    
  const uint8_t *table;
  uint16_t Width;
  uint16_t Height;
  
} sFONT;

//GB2312
typedef struct                                          // ������ģ���ݽṹ
{
  unsigned char index[2];                               // ������������
  const char matrix[MAX_HEIGHT_FONT*MAX_WIDTH_FONT/8];  // ����������
}CH_CN;


typedef struct
{    
  const CH_CN *table;
  uint16_t size;
  uint16_t ASCII_Width;
  uint16_t Width;
  uint16_t Height;
  
}cFONT;

extern sFONT Font24;
extern sFONT Font20;
extern sFONT Font16;
extern sFONT Font12;
extern sFONT Font8;

extern cFONT Font12CN;
extern cFONT Font24CN;

/** @defgroup FONTS_Exported_Constants
  * @{
  */ 
#define LINE(x) ((x) * (((sFONT *)LCD_GetFont())->Height))

/*******************中文********** 在显示屏上显示的字符大小 ***************************/
#define      WIDTH_CH_CHAR		              24	    //中文字符宽度 
#define      HEIGHT_CH_CHAR		              24		//中文字符高度 

//0表示使用SD卡字模，非零表示FLASH字模,由于SD卡字模有文件系统，速度慢很多。

#define GBKCODE_FLASH 						1

#if GBKCODE_FLASH
/*使用FLASH字模*/
/*=========================================================================================*/
/*中文字库存储在FLASH的起始地址*/
/*FLASH*/
/* 资源烧录到的FLASH基地址（目录地址） */
#define RESOURCE_BASE_ADDR	(16*1024*1024)
/* 存储在FLASH中的资源目录大小 */
#define CATALOG_SIZE				(8*1024)

/* 字库目录信息类型 */
typedef struct 
{
	char 	      name[40];  /* 资源的名字 */
	uint32_t  	size;      /* 资源的大小 */ 
	uint32_t 	  offset;    /* 资源相对于基地址的偏移 */
}CatalogTypeDef;
/*=========================================================================================*/

/*获取字库的函数*/
//定义获取中文字符字模数组的函数名，ucBuffer为存放字模数组名，usChar为中文字符（国标码）
#define      GetGBKCode( ucBuffer, usChar )  GetGBKCode_from_EXFlash( ucBuffer, usChar )  
int GetGBKCode_from_EXFlash( uint8_t * pBuffer, uint16_t c);
int GetResOffset(const char *res_name);

#else
/*使用SD字模*/


/*SD卡字模路径*/
#define GBKCODE_FILE_NAME			"0:/Font/GB2312_H2424.FON"


/*获取字库的函数*/
//定义获取中文字符字模数组的函数名，ucBuffer为存放字模数组名，usChar为中文字符（国标码）

#define GetGBKCode( ucBuffer, usChar )  GetGBKCode_from_sd( ucBuffer, usChar )
int GetGBKCode_from_sd ( uint8_t * pBuffer, uint16_t c);
#endif

#ifdef __cplusplus
}
#endif
  
#endif /* __FONTS_H */
