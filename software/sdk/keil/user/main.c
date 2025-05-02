//#include "platform_config.h"
#include "key_handle.h"

#include "gecko1108.h"

#include "gpio.h"
#include "watchdog.h"

#include "adc.h"
#include "cmu.h"
#include "iomux.h"

#include "dma2d.h"


#include "uart.h"
#include "hci.h"

#include "norflash.h"
#include "aon.h"
#include "spi.h"
#include "pwm.h"

#include "timer.h"

#include "lcd_driver.h"


extern KeyHandle keyHandle;

extern void delay_1us(unsigned int delay_val);
extern void sram_run_delay(unsigned long delay);
extern void gecko_task_cm0_sw_flash_dual(void);
extern void gecko_task_cm0_sw_flash_quad(void);

extern void Key_Process(void);
extern void dma_sram_delay(unsigned long delay);

extern uint32_t SysTick_Config(uint32_t ticks);

extern void SPI_32bit_Transfer(void);

extern const unsigned int gImage_120x240_32bit[14400];
extern const unsigned int gImage_120x240_1_32bit[14400];


volatile uint16 ram_color=0x1234;
//uint16 ram_color=0;
uint8 flag=0;

extern uint32_t TimeTick;

//#define __RAM_CODE__ 		__attribute__((section("ram_code")))


//int Trim[] __attribute__ ((section(".ARM.__at_0x0001F000"))) = {0x12345678,0x22334455};
//volatile int *myVariable = (volatile int *)0x0001F000;

const uint8 gSysDate[12] = __DATE__;
const uint8 gSysTime[16] = __TIME__;

#define VERSION "(\"BraveStarr 1900+ GPU\" - GPU MCU Firware  - "__DATE__" - "__TIME__")"


void SystemInit(void)
{

	//gek1108_sram_test();
	

	Osc32M_Freq_Trimming();//trimming 32MHz	
	
//	gecko_rootnode_osc32mclk_cfg();
//	gecko_rootnode_clk32k_cfg();

	//cmu clock manager unit
	//gecko_cmu_reg_rw();
	
	//2024-11-16
	gecko_cmu_init();	

	
#if 1
	hal_nvic_clear_pending_irq(CMU2AHB_IRQ);
	hal_nvic_set_priority(CMU2AHB_IRQ, 0);
	hal_nvic_enable_irq(CMU2AHB_IRQ);	
	gecko_task_cm0_sw_flash_dual(); // changed @ 2021.03.31 added SPI-to-AHB ctrl the QSPI controller
	// SPI command 0x3B is fast quad read for XTX NOR Flash 
	// SPI command 0x3B is given by MemRdCmd=0x2 for QSPI control,
	// Address 3 bytes in Regular mode + Dummy 1 byte in Regular mode + Dual-wire mode
	// reg_write((0x50000000+0x50), 0x2);
	//----------------------------------
#else
    //manba_task_sys_debug (0xCAFE00A1, 0x0, 0x0);
    hal_nvic_clear_pending_irq(CMU2AHB_IRQ);
    hal_nvic_set_priority(CMU2AHB_IRQ, 0);
    hal_nvic_enable_irq(CMU2AHB_IRQ);   
    //  gecko_task_cm0_sw_flash_dual(); //
		gecko_task_cm0_sw_flash_quad();
    //----------------------------------
#endif


}












int main (void) 
{
	int wr_data;
	
	//uint8 loop_cnt;
  //uint16 adc_datavalue;
	//char *string;	
	//uint8 gpio_status,key_status;	
	
	//int val = *myVariable;
	
	SystemInit();	
	
	gecko_pinmux_default_config();


	gecko_pinmux_config(PAD0,UART0_OUT);
	gecko_pinmux_config(PAD1,UART0_IN);

	gecko_pinmux_config(PAD13,UART1_OUT);
	gecko_pinmux_config(PAD14,UART1_IN);
	
	Uart_16550_Initialise(HAL_UART_0,115200,0x3);	
	Uart_16550_Initialise(HAL_UART_1,115200,0x3);	

	
	
	gecko_pinmux_config(PAD15,SPI_CSN);
	gecko_pinmux_config(PAD16,SPI_MOSI);
	gecko_pinmux_config(PAD17,SPI_CLK);
	gecko_pinmux_config(PAD18,SPI_MISO);

	HW_SPI_Initialise(HAL_SPI_0);	

///////////////////////////////////////////////////////
//LDO33_AUX enable, power supply for LCD module
	wr_data = reg_read(0x40020000+0x28);
	wr_data |= 0x340;
	reg_write(0x40020000+0x28,wr_data);
///////////////////////////////////////////////////////

  //delay_1us(8000);
  //delay_1us(8000);	
	
	Lcd_Init();
	//gek1109_pullup_pulldown_config(PAD_14,PAD_PULLUP);//BL control	
	//LCD_BL_SET;//turn on backlight
	LCD_BL_CLR;
	
	gek1109_pullup_pulldown_config(PAD_14,PAD_PULLDOWN);//BL control	
	
	Lcd_Clear(RED); 	//clear screen
	
	Lcd_SetRegion(0, 0, X_MAX_PIXEL-1, Y_MAX_PIXEL-1);

  DMA_Configuration();

	SPI_32bit_Transfer();
	
	HW_SPI_Tx_DMA(HAL_SPI_0, (uint16*)gImage_120x240_32bit, 14400);	


#if  0//CHG_INSET_DET_EN //charger insert detect

//config PAD19(GPIOB7) as GPIO input
	  gecko_pinmux_config(PAD19,GPIO_B_7);
    extern void Set_GPIO_B7_Input(void);
		Set_GPIO_B7_Input();

    aon_wakeup_irq_cfg();

#endif

	
/**********************************************************************************	
	//Gecko_Timer_Init();
	//Gecko_Timer_Setting(TIMER_INDEX0);	
*************************************************************************************/

	
	gecko_pinmux_config(PAD12,PCLK_OUT);


//----SysTick Init-----
	//SysTick_Config(20000);//SysTick Test === 1ms tick for KEY detect	
	SysTick_Config(200000);//SysTick Test === 10ms tick for KEY detect

//aon irq
  aon_wakeup_irq_cfg();	

  printf("date:%s \r\n",gSysDate);
  printf("time:%s \r\n",gSysTime);
	printf("\r\n");
	printf(VERSION);
  
  //__wfi();//wait for interrupt
	//__wfe();//wait for event
	//__sev();//send event
	
	
	while(1)
	{
	
		
#if 1	
		//PAD18(GPIOB6) KEY2
		//gpio_status=GpiopinRead(PB6);
		
		Key_Process(); 
	
		printf("\r\n Key Process  keyHandle.valid_press = %d",keyHandle.key_released_flag);
		
		printf("\r\n Key Process  keyHandle.valid_press = %d",keyHandle.valid_press);
		
		printf("\r\n Key Process  keyHandle.valid_long_press = %d",keyHandle.valid_long_press);

	  if(keyHandle.key_released_flag)
		{
			keyHandle.key_released_flag = false;
			
			if(flag==0)
			{
				printf("KEY Press Down");
        HW_SPI_Tx_DMA(HAL_SPI_0, (uint16*)gImage_120x240_32bit, 14400);					
				//sram_run_delay(10);
				dma_sram_delay(30);
				flag=1;
			}
			else
			{

				HW_SPI_Tx_DMA(HAL_SPI_0, (uint16*)gImage_120x240_1_32bit, 14400);
				//sram_run_delay(10);
				dma_sram_delay(30);
				flag=0;								
			}
		}

		
	  if(keyHandle.valid_press)
		{
			keyHandle.valid_press = false;
		}
	
		
		if(keyHandle.valid_long_press) 
		{
			keyHandle.valid_long_press = false;
			// Execute long press business logic
		}	
		
		
#endif



//sleep-wakeup setting		
#if 0		
		//1000*10ms=10000ms=10s
		if(TimeTick>1000)
		{
				GEK1109_GPIO_WakeUp_From_DeepSleep();//	
				wr_data = 0x608e7885;
				reg_write(0x40020000+0x020, wr_data);
			
				//reg_aon_sel_aon_clk16k(bit10)
				wr_data=reg_read(0x40020000+0x000);
				wr_data |= 0x200;//(set bit10=1)
				reg_write(0x40020000+0x000, wr_data);

			  LCD_BL_CLR;
				gek1109_pullup_pulldown_config(PAD_14,PAD_PULLDOWN);	
			
			
			  //LDO33_AUX disable, power down LCD module
				wr_data = reg_read(0x40020000+0x28);
				//wr_data &= (~0x340);
			  wr_data=0x0;
				reg_write(0x40020000+0x28,wr_data);
			
				tc_gecko_cm0_aon_sleep();//deep sleep test for low power design
		}			
#endif
	}
	
	
}








