
/*********************************************************************************************
 *   $Id:: watchdog.c 2020-07-15 
 *   Project: Gecko watchdog driver
 *	 Author: Moana
 *   Description: 
 *	 1,AWT --- Auto Wakeup Timer
 *   2,IWDG --- independent watchdog, VDD comes from VBAT, CLOCK comes from always-on clock
 *   3,WWDG --- window watchdog
*********************************************************************************************/
#include "gecko1108.h"
#include "watchdog.h"
#include "uart.h"




/* ----------------------------------------------------------------- */
/* Unlock watchdog access */
void watchdog_unlock(void)
{
  GECKO1108_WATCHDOG->LOCK = 0x1ACCE551;
}
/* ----------------------------------------------------------------- */
/* Lock watchdog access */
void watchdog_lock(void)
{
  GECKO1108_WATCHDOG->LOCK = 0;
}


/* ----------------------------------------------------------------- */
/* Watchdog initialization */
/* type = 0 : No action */
/* type = 1 : Interrupt */
/* type = 2 : Reset */
/* ----------------------------------------------------------------- */
void watchdog_init(unsigned int cycle, int type)
{
	volatile int TmpData;
  watchdog_unlock();
  GECKO1108_WATCHDOG->WdogLoad = cycle;
	TmpData=GECKO1108_WATCHDOG->WdogLoad;
  if (type==0) 
	{
		//printf("Set to no action");
    GECKO1108_WATCHDOG->CTRL = 0;
  } 
	else if (type==1) 
	{
		//printf("Set to NMI generation");
    GECKO1108_WATCHDOG->CTRL = Gecko_Watchdog_CTRL_INTEN_Msk;

		hal_nvic_clear_pending_irq(WDT_IRQn);
		hal_nvic_set_priority(WDT_IRQn, 0);
		hal_nvic_enable_irq(WDT_IRQn);			
		
  } 
	else 
	{
		//printf("Set to reset generation");
    GECKO1108_WATCHDOG->CTRL = Gecko_Watchdog_CTRL_RESEN_Msk|Gecko_Watchdog_CTRL_INTEN_Msk;
  }
  watchdog_lock();
}






//void iWDT_Timer_Init(unsigned int cycle, int type)
void iWDT_Timer_Init(void)
{
	volatile int ID,Val;
  ID=iWATCHDOG->IDREV;
	
	iWATCHDOG->WREN=WDT200_WP_NUM;//Write the magic number,0x5aa5

	Val|=IWDT_INT_TIME(0);//The timer interval of the interrupt stage
	Val|=IWDT_RST_TIME(2);//The time interval of the reset stage
	
	Val|=IWDT_CLK_SEL;//Clock source of timer:[0:EXTCLK;1:PCLK]
	Val|=IWDT_INT_EN;
	Val|=IWDT_RST_EN;
	Val|=IWDT_EN;	

	iWATCHDOG->CTRL=Val;	
	
}


void iWDT_Timer_Restart(void)
{
		iWATCHDOG->WREN=WDT200_WP_NUM;//Write the magic number,0x5aa5
		iWATCHDOG->RESTART=WDT200_RESTART_NUM;//Write the magic number,0xcafe	
}


void iWDT_Timer_Disable(void)
{
	iWATCHDOG->WREN=WDT200_WP_NUM;//Write the magic number,0x5aa5	
	iWATCHDOG->CTRL=(~IWDT_EN);//En=0	
}



/* ----------------------------------------------------------------- */
/* Update watchdog counter */
void watchdog_set(unsigned int cycle)
{
  watchdog_unlock();
#ifdef _FPGA_

#else
  GECKO1108_WATCHDOG->WdogLoad = cycle;
#endif
  watchdog_lock();
}






//feed watchdog
void feed_dog(unsigned int cycle)
{
	unsigned int read_data;
	
#if 0	
  uint8 i = 0;
  while (i<10) {
    read_data = GECKO1108_WATCHDOG->WdogValue;//CountRead, current value
    if (read_data < 1600) //the threshold must be large enough so that the NMI interrupt
                           //won't be triggered before the watchdog value is set again
    {
      watchdog_set(2000);
      i++;
      //printf("  Watchdog value set again");
    }
  }
	
#endif

	read_data = GECKO1108_WATCHDOG->WdogValue;//CountRead, current value	
	if (read_data<100)
  watchdog_set(cycle);

}






/* ----------------------------------------------------------------- */
/* Clear watchdog interrupt request */
void watchdog_irq_clear(void)
{
  //watchdog_unlock();
	GECKO1108_WATCHDOG->LOCK = 0x1ACCE551;
	
	
	printf("\r\nwatchdog_irq_clear\r\n");

	
  GECKO1108_WATCHDOG->INTCLR = Gecko_Watchdog_INTCLR_Msk;
  //watchdog_lock();
	GECKO1108_WATCHDOG->LOCK = 0;
}











