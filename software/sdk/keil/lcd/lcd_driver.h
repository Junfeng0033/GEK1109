
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��������   : 2018-1111
//  ����޸�   : 
//  ��������   : 0.96��ISP LCD 4�ӿ���ʾ����(STM32ϵ��)
/******************************************************************************
//������������STM32F103C8
//              GND   ��Դ��
//              VCC   ��5V��3.3v��Դ
//              SCL   ��PA5��SCL��
//              SDA   ��PA7��SDA��
//              RES   ��PB0
//              DC    ��PB1
//              CS    ��PA4//����ֱ�ӽӵ�
//              BLK    ��P10 BLK�������ղ��ӣ�����Ҫ�رձ����ʱ��BLK�õ͵�ƽ
*******************************************************************************/
// �޸���ʷ   :
// ��    ��   : 
// �޸�����   : 
//******************************************************************************/

#include "stdint.h"

#define X_MAX_PIXEL		120
#define Y_MAX_PIXEL		240


#define USE_HORIZONTAL 1  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
//#define LCD_W 80
//#define LCD_H 160
#else
#define LCD_W 160
#define LCD_H 80
#endif






#define RED  				0xf800
#define GREEN				0x07e0
#define BLUE 				0x001f
#define WHITE				0xffff
#define BLACK				0x0000
#define YELLOW  		0xFFE0
#define GRAY0   		0xEF7D   		//��ɫ0  3165 00110 001011 00101
#define GRAY1   		0x8410      //��ɫ1  00000 000000 00000
#define GRAY2   		0x4208      //��ɫ2  1111111111011111


// backlight control
#define LCD_BL_PORT  		GPIOB			//MCU_PB2--->>TFT --LCD_LEDK
#define LCD_BL_PIN       	2  			//MCU_PB2--->>TFT --BL

#define LCD_RS_PORT			GPIOB
#define LCD_RS_PIN         	1			//PB1--->>TFT --RS/DC

#define LCD_RST_PORT		GPIOB
#define LCD_RST_PIN     	0				//PB0--->>TFT --RST






//Һ�����ƿ���1�������궨��

#define	LCD_RS_SET  	gpio_set_value(LCD_RS_PORT, 1, LCD_RS_PIN)
#define	LCD_BL_SET  	gpio_set_value(LCD_BL_PORT, 1, LCD_BL_PIN)
#define	LCD_RST_SET  	gpio_set_value(LCD_RST_PORT, 1, LCD_RST_PIN)


//Һ�����ƿ���0�������궨��

#define	LCD_RS_CLR  	gpio_set_value(LCD_RS_PORT, 0, LCD_RS_PIN)
#define	LCD_BL_CLR  	gpio_set_value(LCD_BL_PORT, 0, LCD_BL_PIN)
#define	LCD_RST_CLR  	gpio_set_value(LCD_RST_PORT, 0, LCD_RST_PIN)




#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
}




void LCD_GPIO_Init(void);
void Lcd_WriteIndex(uint8_t Index);
void Lcd_WriteData(uint8_t Data);
void Lcd_WriteReg(uint8_t Index,uint8_t Data);
uint16_t Lcd_ReadReg(uint8_t LCD_Reg);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(uint16_t Color);
void Lcd_SetXY(uint16_t x,uint16_t y);
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data);
unsigned int Lcd_ReadPoint(uint16_t x,uint16_t y);
void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end);
void LCD_WriteData_16Bit(uint16_t Data);






