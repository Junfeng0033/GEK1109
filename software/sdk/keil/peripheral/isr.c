
/****************************************************************************
 *   $Id:: isr.c 2020-10-19 
 *   Project: Interrupt Service Routines
 *	 Author: Moana
 *   Description: Interrupt Service Routines
****************************************************************************/
#include "platform_config.h"
#include "gecko1108.h"
#include "uart.h"

#include "gpio.h"
#include "watchdog.h"
#include "pwm.h"
#include "spi.h"
#include "lcd_driver.h"





/* Cortex-M0 Processor Exception Handlers -----------------------------------*/
/**
  * @brief  Handle NMI
  * @param  None
  * @retval None
  */
void nmi_handler(void)
{
}

/**
  * @brief  Handle hard fault
  * @param  None
  * @retval None
  */
void hardfault_handler(void)
{
    while (1)
    {
    }
}

/**
  * @brief  Handle SVC
  * @param  None
  * @retval None
  */
void svc_handler(void)
{
}

/**
  * @brief  Handle PendSV
  * @param  None
  * @retval None
  */
void pendsv_handler(void)
{
}






volatile uint32_t TimeTick = 0;

void SysTick_Handler(void)  //interrupt routine
{

	TimeTick++;//TimeTick will increase by "1"  every 100us
#if 0			
	if(TimeTick%2)
	  //LCD_BL_CLR;
	  //(*(volatile uint32*)(0x40019000 + (1 << (2 + 2)) ) ) = (uint32)(0 << 2);
	else
	  //LCD_BL_SET;
	  //(*(volatile uint32*)(0x40019000 + (1 << (2 + 2)) ) ) = (uint32)(1 << 2);
#endif	
}




uint32_t Get_SysTick(void)
{
	return TimeTick;
}

	



/******************************************************************************/
/*                 Gecko1108 Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PERIPHERAL), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_cm0.s).                                               */
/******************************************************************************/
/**
  * @brief  This function handles external lines 4 to 15 interrupt request.
  * @param  None
  * @retval None
  */
void external_irq_handler(void)
{

}




void GPIO_B6_IRQHandler(void)
{

}




void GPIO_A5_IRQHandler(void)
{
  #if 0//DEBUG_UATR0_PRINT_LOG
	UATR0_PRINT_LOG((unsigned char *)("\r\n"));						
	UATR0_PRINT_LOG((unsigned char *)("GPIO_A5_IRQHandler"));
	UATR0_PRINT_LOG((unsigned char *)("\r\n"));
  #endif		
}


#if 1
extern void Timer0_Interrupt_Handler(void);

void TIMER0_IRQHandler(void)
{
	Timer0_Interrupt_Handler();
	
}

#endif






extern void UART0_Interrupt_Handler(void);

void UART0_IRQHandler(void)
{
	//the first UART interrupt service routine
	UART0_Interrupt_Handler();
	
}


extern void UART1_Interrupt_Handler(void);

void UART1_IRQHandler(void)
{
	//the second UART interrupt service routine
	UART1_Interrupt_Handler();
}






void GPADC_IRQHandler(void)
{
	
}





extern void Clear_DMA_Interrupt(void);
extern void DMA_ISR_Routine(void);


volatile unsigned char dma_int_flag=0;

void DMA_IRQHandler(void)
{
	
	dma_int_flag =1;
	Clear_DMA_Interrupt();
	//DMA_ISR_Routine();
	
}


__RAM_CODE__ void dma_sram_delay(unsigned long delay)
{
    unsigned int i;
    unsigned long count;
    count = (delay<<4);
    for (i=0; i<count; i++)
    {
			  if(dma_int_flag==1)
				{
						dma_int_flag=0;
					  return;					
				}
        __nop();
			  __nop();
			  __nop();
    }
}










extern void watchdog_irq_clear(void);

volatile uint8_t flag_250us=0;
//__RAM_CODE__ void WDT_IRQHandler(void)
void WDT_IRQHandler(void)
{
#if 0	
	if(flag_250us)
	{
		flag_250us=0;
		set_gpiob4_l();
	}
	else
	{
		flag_250us=1;
		set_gpiob4_h();
	}	
#endif

//**********************************************************	
  //watchdog_irq_clear();
	
  //watchdog_unlock();
	GECKO1108_WATCHDOG->LOCK = 0x1ACCE551;
	
  GECKO1108_WATCHDOG->INTCLR = Gecko_Watchdog_INTCLR_Msk;
  //watchdog_lock();
	GECKO1108_WATCHDOG->LOCK = 0;	
//*************************************************************	
}






//****************************************************************************
//  IRQ handler of : 1. QSPI controller; 2. AON Wakeup
//  Gofee added @ 2021.02.11
//****************************************************************************
extern void gecko_ahb2qspi_ctrl_irq_handler(void);

void QSPI_CTRL_IRQHandler(void)
{
  
  gecko_ahb2qspi_ctrl_irq_handler();
  
}





extern void gecko_aon_wakeup_irq_handler(void);

void AON_WKUP_IRQHandler(void)
{
  
  gecko_aon_wakeup_irq_handler();
  
}





void APB_SPI0_IRQnHandler(void)
{
	
}




void CMU2AHB_IRQHandler(void)
{
    // TBD
}




//****************************************************************************

