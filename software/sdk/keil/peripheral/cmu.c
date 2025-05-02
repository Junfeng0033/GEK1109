
/****************************************************************************
* *   $Id:: cmu.c 2020-09-25 
* *   Project: Gecko Clock & Reset Management Unit
* *
* *   Description:
* *
****************************************************************************/

#include "platform_config.h"
#include "gecko1108.h"
#include "cmu.h"





void gecko_cmu_init(void)
{
	volatile uint32 Val=0;
	
	Val=HW_SysClkUnit->CLK_DIV_3;
	Val |= 0x20;	//bit5=1
	HW_SysClkUnit->CLK_DIV_3=Val; //speed up SPI0 CLK
	
#if 0
//register 0x04
//system clock enable
//corresponding module's enable 
//	HW_SysClkUnit->SYS_CLK_EN=0xffffffff;//set bypass enable
	
		// System clock enable	
		// Gofee change @ 2021.07.27 | 1. set HCLK bypass enable for 8MHz clock; 2. disable WatchDog clock;
		//HW_SysClkUnit->SYS_CLK_EN=0xffffbfff;//SYS_CLK_EN--->0x04
	  HW_SysClkUnit->SYS_CLK_EN=0xffffffff;//SYS_CLK_EN--->0x04
    //disable ROM clock (bit4 #define EN_HCLK_ROM  4)
		HW_SysClkUnit->SYS_CLK_EN=0xffffffef;//SYS_CLK_EN--->0x04
//========================================================================================
//Add Kevin Zhou 2022-03-16
		//Val=HW_SysClkUnit->SYS_CLK_EN;	
		//Val &= (~EN_PCLK_LIGHTNING);//Disable Lightning Module for Reduce running power consumption	
		//HW_SysClkUnit->SYS_CLK_EN=Val;
	
	
	  ////Disable EFUSE Module and WDT Module
		//HW_SysClkUnit->SYS_CLK_EN=0xfffebfff;//SYS_CLK_EN--->0x04
	
	  //HW_SysClkUnit->SYS_CLK_EN=0xfffabf7f;//SYS_CLK_EN--->0x04
		
		////Disable ROM clock when it boots to norflash running
		//HW_SysClkUnit->SYS_CLK_EN=0xfffabf6f;//EN_HCLK_ROM--->0x04
//========================================================================================	

	
//register 0x00
		Val=0;		
		Val |= HCLK_FREE_DIV(0x02);
    Val	|= UART_CLK_DIV(0x01);
	  Val |= PWM_CLK_DIV(0x01);
	  Val |= SPINOR_CLK_DIV(0x01);		
		HW_SysClkUnit->CLK_DIV=Val;

//register 0x0c	
	  Val=0;
		Val |= ADC_CLK_DIV(0x01);
	  Val |= I2C_CLK_DIV(0x01);
	  Val |= TIMER_CLK_DIV(0x01);
	  Val |= LIGHTNING_CLK_DIV(0x01);		
		HW_SysClkUnit->CLK_DIV_2=Val;	

//register 0x10	
	  Val=0;
		Val |= EFUSE_CLK_DIV(0x01);
	  Val |= WDT_CLK_DIV(0x01);
	  Val |= GPIO_CLK_DIV(0x01);		
		HW_SysClkUnit->CLK_DIV_3=Val;	

//register 0x08, "1" not reset module, "0" reset module
		HW_SysClkUnit->Sys_Soft_Rst_N=0xffffffff;
		
		
	
#endif


}









/*
    REG32                          CLK_DIV;                      //0x00000000
    REG32                          SYS_CLK_EN;                   //0x00000004
		REG32                          Sys_Soft_Rst_N;               //0x00000008
    REG32                          CLK_DIV_2;                    //0x0000000C	
    REG32                          CLK_DIV_3;                    //0x00000010		

	  REG32                          REG32_0x14;                    //0x00000014		
	  REG32                          REG32_0x18;                    //0x00000018	

	  REG32                          REG32_0x1C;                    //0x0000001C	
	  REG32                          REG32_0x20;                    //0x00000020

	  REG32                          REG32_0x24;                    //0x00000024	
	  REG32                          REG32_0x28;                    //0x00000028
	
	  REG32                          REG32_0x2C;                    //0x0000002C	
	  REG32                          REG32_0x30;                    //0x00000030	
*/

void gecko_cmu_reg_rw(void)
{
		volatile uint32 VAL=0;
//	  VAL=HW_SysClkUnit->CLK_DIV;//0x00
//	  VAL=HW_SysClkUnit->SYS_CLK_EN;//0x04	
//	  VAL=HW_SysClkUnit->Sys_Soft_Rst_N;//0x08
//	  VAL=HW_SysClkUnit->CLK_DIV_2;//0x0C
//	  VAL=HW_SysClkUnit->CLK_DIV_3;//0x10		
//	
//	  VAL=HW_SysClkUnit->REG32_0x14;//0x14	
//	  VAL=HW_SysClkUnit->REG32_0x18;//0x18	
//	  VAL=HW_SysClkUnit->cali32m;//0x1C	
//	  VAL=HW_SysClkUnit->REG32_0x20;//0x20
//	
//	
//	  VAL=HW_SysClkUnit->REG32_0x24;//0x24	
//	  VAL=HW_SysClkUnit->REG32_0x28;//0x28	
//	  VAL=HW_SysClkUnit->REG32_0x2C;//0x2C	
//	  VAL=HW_SysClkUnit->REG32_0x30;//0x30
	
}




