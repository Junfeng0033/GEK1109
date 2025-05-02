#include "lcd_driver.h"
#include "stdint.h"
#include "gpio.h"
#include "spi.h"
#include "iomux.h"

#include "dma2d.h"


extern uint16 ram_color;


void GC9A01_HSD105_Init(void);

#define SPI_WriteData(data) hwp_spi0->FIFODATA = data

//液晶IO初始化配置
void LCD_GPIO_Init(void)
{
	//gecko_pinmux_config(PAD18,GPIO_B_6);
	gecko_pinmux_config(PAD14,GPIO_B_2);
	gecko_pinmux_config(PAD13,GPIO_B_1);
	gecko_pinmux_config(PAD12,GPIO_B_0);
	
	//gpio_set_output(LCD_CS_PORT, LCD_CS_PIN);
	gpio_set_output(LCD_BL_PORT, LCD_BL_PIN);
	gpio_set_output(LCD_RS_PORT, LCD_RS_PIN);
	gpio_set_output(LCD_RST_PORT, LCD_RST_PIN);
}


void delay_1ms(void)
{
    unsigned int i;
    unsigned int count = 2;

    for (i=0; i<110; i++)
    {
		while(count--);
		count = 2;
    }
}

void delay_ms(unsigned int delay_val)
{
    unsigned int i;

    for (i=0; i<delay_val; i++)
    {
		delay_1ms();
    }
}



//向液晶屏写一个8位指令
void Lcd_WriteIndex(uint8_t Index)
{
	//SPI 写命令时序开始
	LCD_RS_CLR;
	SPI_WriteData(Index);
}

//向液晶屏写一个8位数据
void Lcd_WriteData(uint8_t Data)
{
   LCD_RS_SET;
   SPI_WriteData(Data); 
}

//向液晶屏写一个16位数据
__RAM_CODE__ void LCD_WriteData_16Bit(uint16_t Data)
{
	LCD_RS_SET;
	SPI_WriteData(Data>>8); 	//写入高8位数据
	SPI_WriteData(Data); 			//写入低8位数据
}

void Lcd_WriteReg(uint8_t Index,uint8_t Data)
{
	Lcd_WriteIndex(Index);
	Lcd_WriteData(Data);
}

void Lcd_Reset(void)
{
	LCD_RST_SET;
	delay_ms(100);
	LCD_RST_CLR;
	delay_ms(500);
	LCD_RST_SET;
	delay_ms(50);
}









#define 	LCD_NV3022_CMD							Lcd_WriteIndex
#define 	LCD_NV3022_Parameter				Lcd_WriteData


#define 	LCD_NV3023_CMD							Lcd_WriteIndex
#define 	LCD_NV3023_Parameter				Lcd_WriteData





//LCD Init For 1.47Inch LCD Panel with NV3022B.
void Lcd_Init(void)
{	
	LCD_GPIO_Init();
	Lcd_Reset(); //Reset before LCD Init.	
	GC9A01_HSD105_Init();
}






//KP85A
#define 	SPI_WriteComm							Lcd_WriteIndex
#define 	SPILCD_WriteData				  Lcd_WriteData

void GC9A01_HSD105_Init(void)
{
	
LCD_RST_SET;
delay_ms(10);
LCD_RST_CLR;
delay_ms(10); 
LCD_RST_SET;
delay_ms(120);

SPI_WriteComm(0xFE);			 
SPI_WriteComm(0xEF); 

SPI_WriteComm(0xEB);	
SPILCD_WriteData(0x14); 

SPI_WriteComm(0x84);			
SPILCD_WriteData(0x60); 

SPI_WriteComm(0x85);
SPILCD_WriteData(0xF7);

SPI_WriteComm(0x86);            
SPILCD_WriteData(0xFC); 

SPI_WriteComm(0x87);            
SPILCD_WriteData(0x28);

SPI_WriteComm(0x8E);        
SPILCD_WriteData(0x0F);

SPI_WriteComm(0x8F);     
SPILCD_WriteData(0xFC); 

SPI_WriteComm(0x88);			
SPILCD_WriteData(0x0A);

SPI_WriteComm(0x89);			
SPILCD_WriteData(0x21); 

SPI_WriteComm(0x8A);			
SPILCD_WriteData(0x00); 

SPI_WriteComm(0x8B);			
SPILCD_WriteData(0x80); 

SPI_WriteComm(0x8C);			
SPILCD_WriteData(0x01); 

SPI_WriteComm(0x8D);			
SPILCD_WriteData(0x03); 

SPI_WriteComm(0xB6);			
SPILCD_WriteData(0x00); 
SPILCD_WriteData(0x20); 

SPI_WriteComm(0x36);			
SPILCD_WriteData(0xC8);//SPILCD_WriteData(0x48);

SPI_WriteComm(0x3A);			
SPILCD_WriteData(0x05); 

SPI_WriteComm(0x90);			
SPILCD_WriteData(0x08);
SPILCD_WriteData(0x08);
SPILCD_WriteData(0x08);
SPILCD_WriteData(0x08); 

SPI_WriteComm(0xBA);			
SPILCD_WriteData(0x01);// TE WIDTH

SPI_WriteComm(0xBD);			
SPILCD_WriteData(0x06);

SPI_WriteComm(0xBC);			
SPILCD_WriteData(0x00);	

SPI_WriteComm(0xFF);			
SPILCD_WriteData(0x60);
SPILCD_WriteData(0x01);
SPILCD_WriteData(0x04);

SPI_WriteComm(0xC3);			
SPILCD_WriteData(0x48);
SPI_WriteComm(0xC4);			
SPILCD_WriteData(0x48);

SPI_WriteComm(0xC9);			
SPILCD_WriteData(0x25);

SPI_WriteComm(0xBE);			
SPILCD_WriteData(0x11);

SPI_WriteComm(0xE1);
SPILCD_WriteData(0x10);
SPILCD_WriteData(0x0E);

SPI_WriteComm(0xDF);			
SPILCD_WriteData(0x21);
SPILCD_WriteData(0x10);
SPILCD_WriteData(0x02);

SPI_WriteComm(0xf0);
SPILCD_WriteData(0x4b);
SPILCD_WriteData(0x0f);
SPILCD_WriteData(0x0A);
SPILCD_WriteData(0x0B);
SPILCD_WriteData(0x15);
SPILCD_WriteData(0x30);

SPI_WriteComm(0xf1);
SPILCD_WriteData(0x43);
SPILCD_WriteData(0x70);
SPILCD_WriteData(0x72);
SPILCD_WriteData(0x36);
SPILCD_WriteData(0x37);
SPILCD_WriteData(0x6f); 

SPI_WriteComm(0xf2);
SPILCD_WriteData(0x4b);
SPILCD_WriteData(0x0f);
SPILCD_WriteData(0x0A);
SPILCD_WriteData(0x0B);
SPILCD_WriteData(0x15);
SPILCD_WriteData(0x30);

SPI_WriteComm(0xf3);
SPILCD_WriteData(0x43);
SPILCD_WriteData(0x70);
SPILCD_WriteData(0x72);
SPILCD_WriteData(0x36);
SPILCD_WriteData(0x37);
SPILCD_WriteData(0x6f);

SPI_WriteComm(0xED);	
SPILCD_WriteData(0x1B); 
SPILCD_WriteData(0x0B); 

SPI_WriteComm(0xAC);			
SPILCD_WriteData(0x47);

SPI_WriteComm(0xAE);			
SPILCD_WriteData(0x77);

SPI_WriteComm(0xCD);			
SPILCD_WriteData(0x63);		

SPI_WriteComm(0x70);			
SPILCD_WriteData(0x07);
SPILCD_WriteData(0x09);
SPILCD_WriteData(0x04);
SPILCD_WriteData(0x0C);
SPILCD_WriteData(0x0D); 
SPILCD_WriteData(0x09);
SPILCD_WriteData(0x07);
SPILCD_WriteData(0x08);
SPILCD_WriteData(0x03);

SPI_WriteComm(0xE8);			
SPILCD_WriteData(0x34);

//////////////////////////////
SPI_WriteComm(0x60);		
SPILCD_WriteData(0x38);
SPILCD_WriteData(0x0B);
SPILCD_WriteData(0x76);
SPILCD_WriteData(0x62);

SPILCD_WriteData(0x39);
SPILCD_WriteData(0xF0);
SPILCD_WriteData(0x76);
SPILCD_WriteData(0x62);

SPI_WriteComm(0x61);
SPILCD_WriteData(0x38);
SPILCD_WriteData(0xF6);
SPILCD_WriteData(0x76);
SPILCD_WriteData(0x62);

SPILCD_WriteData(0x38);
SPILCD_WriteData(0xF7);
SPILCD_WriteData(0x76);
SPILCD_WriteData(0x62);
//////////////////////////////
SPI_WriteComm(0x62);
SPILCD_WriteData(0x38);
SPILCD_WriteData(0x0D);
SPILCD_WriteData(0x71);
SPILCD_WriteData(0xED);
SPILCD_WriteData(0x76);
SPILCD_WriteData(0x62);
SPILCD_WriteData(0x38);
SPILCD_WriteData(0x0F);
SPILCD_WriteData(0x71);
SPILCD_WriteData(0xEF);
SPILCD_WriteData(0x76); 
SPILCD_WriteData(0x62);

SPI_WriteComm(0x63);			
SPILCD_WriteData(0x38);
SPILCD_WriteData(0x11);
SPILCD_WriteData(0x71);
SPILCD_WriteData(0xF1);
SPILCD_WriteData(0x76);
SPILCD_WriteData(0x62);
SPILCD_WriteData(0x38);
SPILCD_WriteData(0x13);
SPILCD_WriteData(0x71);
SPILCD_WriteData(0xF3);
SPILCD_WriteData(0x76); 
SPILCD_WriteData(0x62);

/////////////////////////////
SPI_WriteComm(0x64);			
SPILCD_WriteData(0x3b);
SPILCD_WriteData(0x29);
SPILCD_WriteData(0xF1);
SPILCD_WriteData(0x01);
SPILCD_WriteData(0xF1);
SPILCD_WriteData(0x00);
SPILCD_WriteData(0x0a);

SPI_WriteComm(0x66);			
SPILCD_WriteData(0x3C);
SPILCD_WriteData(0x00);
SPILCD_WriteData(0xCD);
SPILCD_WriteData(0x67);
SPILCD_WriteData(0x45);
SPILCD_WriteData(0x45);
SPILCD_WriteData(0x10);
SPILCD_WriteData(0x00);
SPILCD_WriteData(0x00);
SPILCD_WriteData(0x00);

SPI_WriteComm(0x67);			
SPILCD_WriteData(0x00);
SPILCD_WriteData(0x3C);
SPILCD_WriteData(0x00);
SPILCD_WriteData(0x00);
SPILCD_WriteData(0x00);
SPILCD_WriteData(0x01);
SPILCD_WriteData(0x54);
SPILCD_WriteData(0x10);
SPILCD_WriteData(0x32);
SPILCD_WriteData(0x98);

SPI_WriteComm(0xB5);			
SPILCD_WriteData(0x08);
SPILCD_WriteData(0x09);
SPILCD_WriteData(0x14);
SPILCD_WriteData(0x08);
					
SPI_WriteComm(0x74);			
SPILCD_WriteData(0x10);	
SPILCD_WriteData(0x85);	
SPILCD_WriteData(0x80);
SPILCD_WriteData(0x00); 
SPILCD_WriteData(0x00); 
SPILCD_WriteData(0x4E);
SPILCD_WriteData(0x00);					

SPI_WriteComm(0x98);			
SPILCD_WriteData(0x3e);
SPILCD_WriteData(0x07);

SPI_WriteComm(0x99);			
SPILCD_WriteData(0x3e);
SPILCD_WriteData(0x07);

SPI_WriteComm(0x35);	
SPILCD_WriteData(0x00); 

SPI_WriteComm(0x21);

SPI_WriteComm(0x11);
delay_ms(120);
SPI_WriteComm(0x29);
delay_ms(10);

}




/**********SLEEP IN***************/
void GC9A01_HSD105_EnterSleep(void)
{
	SPI_WriteComm(0x28);
	SPI_WriteComm(0x10);
	delay_ms(120);
}

/**********SLEEP OUT***************/
void GC9A01_HSD105_ExitSleep(void)
{
	SPI_WriteComm(0x11);
	delay_ms(120);
	SPI_WriteComm(0x29);
}












/*************************************************
函数名：LCD_Set_Region
功能：设置lcd显示区域，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end)
{		
	Lcd_WriteIndex(0x2a);
	//Lcd_WriteData(0x00);
	LCD_WriteData_16Bit(x_start+60);//LCD_WriteData_16Bit
	//Lcd_WriteData(0x00);
	LCD_WriteData_16Bit(x_end+60);

	Lcd_WriteIndex(0x2b);
	//Lcd_WriteData(0x00);
	LCD_WriteData_16Bit(y_start);
	//Lcd_WriteData(0x00);
	LCD_WriteData_16Bit(y_end);	
	Lcd_WriteIndex(0x2c);

}

/*************************************************
函数名：LCD_Set_XY
功能：设置lcd显示起始点
入口参数：xy坐标
返回值：无
*************************************************/
void Lcd_SetXY(uint16_t x,uint16_t y)
{
  	Lcd_SetRegion(x,y,x,y);
}

	
/*************************************************
函数名：LCD_DrawPoint
功能：画一个点
入口参数：无
返回值：无
*************************************************/
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data)
{
	Lcd_SetRegion(x,y,x+1,y+1);
	LCD_WriteData_16Bit(Data);

}    

/*****************************************
 函数功能：读TFT某一点的颜色                          
 出口参数：color  点颜色值                                 
******************************************/
unsigned int Lcd_ReadPoint(uint16_t x,uint16_t y)
{
  unsigned int Data;
  Lcd_SetXY(x,y);

  //Lcd_ReadData();//丢掉无用字节
  //Data=Lcd_ReadData();
  Lcd_WriteData(Data);
  return Data;
}



/*************************************************
函数名：Lcd_Clear
功能：全屏清屏函数
入口参数：填充颜色COLOR
返回值：无
*************************************************/

__RAM_CODE__ void Lcd_Clear(uint16_t Color)               
{	
   unsigned int i,m;
	
	 ram_color=Color;
	
   Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   //Lcd_WriteIndex(0x2C);
   for(i=0;i<X_MAX_PIXEL;i++)
    for(m=0;m<Y_MAX_PIXEL;m++)
    {	
	  	//LCD_WriteData_16Bit(Color);
	  	LCD_WriteData_16Bit(ram_color);			
    }   
}




/*************************************************
函数名：Lcd_Fill
功能：指定区域填充颜色
入口参数：填充颜色COLOR
返回值：无
*************************************************/
void Lcd_Fill(uint16_t x,uint16_t y,uint16_t xend,uint16_t yend,uint16_t Color)               
{	
	unsigned int i;
	uint16_t num = (xend-x+1)*(yend-y+1);
	
	Lcd_SetRegion(x,y,xend,yend);
	for(i=0; i<num; i++)
		LCD_WriteData_16Bit(Color);
}





extern const unsigned char gImage_circle_100x100[20000];


void ui_paint_color_circle(void)
{
	Lcd_SetRegion(10, 10, 109, 109);//坐标设置
	Lcd_Write_data_dma((uint8_t*)gImage_circle_100x100, 20000);
}



