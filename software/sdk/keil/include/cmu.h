
/****************************************************************************
 *   $Id:: cmu.c 2020-09-25 
 *   Project: Gecko Clock & Reset Management Unit
 *
 *   Description:System Clock Unit
 * 
****************************************************************************/

#include "platform_config.h"


#define    GECKO_APB_CMU_BASE                0X40010000
#define    GECKO_APB_SCU_BASE                0X40010000

      

typedef volatile struct
{

    REG32                          CLK_DIV;                      //0x00000000
    REG32                          SYS_CLK_EN;                   //0x00000004
		REG32                          Sys_Soft_Rst_N;               //0x00000008
    REG32                          CLK_DIV_2;                    //0x0000000C	
    REG32                          CLK_DIV_3;                    //0x00000010		

	  REG32                          REG32_0x14;                    //0x00000014		
	  REG32                          REG32_0x18;                    //0x00000018
//	  REG32                          REG32_0x1C;                    //0x0000001C
    REG32                          cali32m;                    	 //0x0000001C		
	  REG32                          REG32_0x20;                    //0x00000020
	  REG32                          REG32_0x24;                    //0x00000024	
	  REG32                          REG32_0x28;                    //0x00000028	
	  REG32                          REG32_0x2C;                    //0x0000002C	

	
} HW_SCU_CTRL_T;


#define HW_SysClkUnit                 ((HW_SCU_CTRL_T*) GECKO_APB_CMU_BASE)
//#define cmu               					  ((HW_SCU_CTRL_T*) GECKO_APB_CMU_BASE)



//static struct CMU_T * const cmu = (struct CMU_T *)0x40000000;
//static struct HW_SCU_CTRL_T * const cmu = (struct HW_SCU_CTRL_T *)0x40000000;



/*
* reg32_00 Register bits
*
assign hclk_free_div                    = reg32_00[7:0];
assign uart_clk_div                     = reg32_00[15:8];
assign pwm_clk_div                      = reg32_00[23:16];
assign spinor_clk_div                   = reg32_00[31:24];
*
*/

#define HCLK_FREE_DIV(n)					(((n)&0xFF)<<0)
#define UART_CLK_DIV(n)           (((n)&0xFF)<<8)
#define PWM_CLK_DIV(n)					  (((n)&0xFF)<<16)
#define SPINOR_CLK_DIV(n)         (((n)&0xFF)<<24)

/*
* reg32_0C Register bits
*
assign adc_clk_div                      = reg32_0c[7:0];
assign i2c_clk_div                      = reg32_0c[15:8];
assign timer_clk_div                    = reg32_0c[23:16];
assign lightning_clk_div                = reg32_0c[31:24];
*
*/

#define ADC_CLK_DIV(n)						(((n)&0xFF)<<0)
#define I2C_CLK_DIV(n)          	(((n)&0xFF)<<8)
#define TIMER_CLK_DIV(n)					(((n)&0xFF)<<16)
#define LIGHTNING_CLK_DIV(n)      (((n)&0xFF)<<24)


/*
* reg32_10 Register bits
*
assign efuse_clk_div                    = reg32_10[7:0];
assign wdt_clk_div                      = reg32_10[15:8];
assign gpio_clk_div                     = reg32_10[23:16];
assign uart2_clk_div                    = reg32_10[31:24];
*
*/


#define EFUSE_CLK_DIV(n)						(((n)&0xFF)<<0)
#define WDT_CLK_DIV(n)          	  (((n)&0xFF)<<8)
#define GPIO_CLK_DIV(n)					    (((n)&0xFF)<<16)
#define UART2_CLK_DIV(n)					  (((n)&0xFF)<<24)



/*
 * reg32_04 Register bits
 */

#define HCLK_FREE_BYPASS_EN           0
#define UART_CLK_BYPASS_EN            1
#define PWM_CLK_BYPASS_EN             2
#define SPINOR_CLK_BYPASS_EN          3
#define EN_HCLK_ROM                 	4
#define EN_HCLK_RAM                   5
#define EN_HCLK_UART                  6

#define EN_HCLK_I2C                   7 //Disable I2C Module for Reduce running power consumption
#define EN_HCLK_GPIO                  8
#define EN_HCLK_PCLK                  9
#define EN_HCLK_FLASH                 10
#define EN_PCLK_TIMER0                11
#define EN_PCLK_TIMER1                12
#define EN_PCLK_GPIO   								13
#define EN_PCLK_WDT                 	14 //Disable WDT Module for Reduce running power consumption
#define EN_PCLK_PWM                   15
#define EN_PCLK_EFUSE                 16 //Disable EFUSE Module for Reduce running power consumption
#define EN_PCLK_ADC                   17
#define EN_PCLK_LIGHTNING             18 //Disable LIGHTNING Module for Reduce running power consumption

#define RESERVED1                     19
#define EN_UART_CLK                   20
#define EN_PWM_CLK                 		21
#define EN_SPINOR_CLK                 22
#define EN_WDT_CLK                    23
#define EN_TIMER0_CLK                 24
#define EN_TIMER1_CLK                 25
#define RESERVED2                     26
#define EN_LIGHTNING_CLK              27
#define EN_EFUSE_CLK              		28
#define EN_I2C_CLK              		 	29
#define EN_PCLK_GPIO1             		30
#define RESERVED3                     31


/*
 * reg32_08 Register bits
 */

#define SOFT_RESETN_HCLK                0
#define SOFT_RESETN_UART                1
#define SOFT_RESETN_PWM                 2
#define SOFT_RESETN_WDT                 3 
 
#define SOFT_RESETN_SPINOR              4
#define SOFT_RESETN_TIMER0              5
#define SOFT_RESETN_TIMER1              6
#define SOFT_RESETN_ADC                 7
#define SOFT_RESETN_LIGHTNING           8
#define SOFT_RESETN_I2C                 9
#define RESERVER00                      10
#define SOFT_RESETN_EFUSE           		11
#define RESERVER01                      12
#define SOFT_RESETN_GPIO           		  13
#define SOFT_RESETN_UART2           		14

#define uart2_clk_bypass_en             15
#define en_hclk_uart2                   16
#define en_uart2_clk                    17




/*
 * reg32_30 Register bits
 */
#define DAC_CLK_DIV(n)					  (((n)&0xFF)<<16)



// TIMER_CLK
#define CMU_TIMER1_DIV(n)           (((n) & 0xFFFF) << 0)
#define CMU_TIMER1_DIV_MASK         (0xFFFF << 0)
#define CMU_TIMER1_DIV_SHIFT        (0)
#define CMU_TIMER2_DIV(n)           (((n) & 0xFFFF) << 16)
#define CMU_TIMER2_DIV_MASK         ((uint32)0xFFFF << 16)
#define CMU_TIMER2_DIV_SHIFT        (16)





void gecko_cmu_init(void);
void gecko_cmu_reg_rw(void);



