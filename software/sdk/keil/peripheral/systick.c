/* ##################################    SysTick function  ############################################ */
/** \ingroup  CMSIS_Core_FunctionInterface
    \defgroup CMSIS_Core_SysTickFunctions SysTick Functions
    \brief    Functions that configure the System.
  @{
**/

/** \brief  System Tick Configuration

    The function initializes the System Timer and its interrupt, and starts the System Tick Timer.
    Counter is in free running mode to generate periodic interrupts.

    \param [in]  ticks  Number of ticks between two interrupts.

    \return          0  Function succeeded.
    \return          1  Function failed.

    \note     

		When the variable <b>__Vendor_SysTickConfig</b> is set to 1, then the
    function <b>SysTick_Config</b> is not included. In this case, the file <b><i>device</i>.h</b>
    must contain a vendor-specific implementation of this function.

**/
 


#include "gecko1108.h"

extern void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority);


void Set_SysTick_CTRL(uint32_t ctrl)
{
	SysTick->CTRL = ctrl;
}

void Set_SysTick_LOAD(uint32_t load)
{
	SysTick->LOAD = load;
}

uint32_t Read_SysTick_VALUE(void)
{
	//return(SysTick->VALUE);
	return(SysTick->VAL);
}

void Set_SysTick_CALIB(uint32_t calib)
{
	SysTick->CALIB = calib;
}

void Set_SysTick_VALUE(uint32_t value)
{
	//SysTick->VALUE = value;
		SysTick->VAL = value;
}




uint32_t SysTick_Timer_Init(void)
{
	SysTick->CTRL = 0;
	SysTick->LOAD = 0xffffff;
	SysTick->VAL = 0;
	SysTick->CTRL = 0x5;
	while(SysTick->VAL == 0);
	return(SysTick->VAL);
}







/*************************************
//GEK1108 8MHZ
//1/fosc =1/8000000 =125ns
//1ms = 8000 * 125ns
//10ms =80000 * 125ns
**************************************/


/*************************************
//GEK1109 20MHZ
//1/fosc =1/20_000_000 =50ns
//5us  =100 *50ns
//100us=2000*50ns
//1ms  = 20_000 * 50ns
//10ms =200_000 * 50ns
**************************************/

uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk) { return (1UL); }    /* Reload value impossible */

  SysTick->LOAD  = (uint32_t)(ticks - 1UL);                         /* set reload register */
  //NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */
	NVIC_SetPriority (SysTick_IRQn, 0);
  SysTick->VAL   = 0UL;                                             /* Load the SysTick Counter Value */
  
	#if 1
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
  return (0UL);                                                     /* Function successful */
	#else
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   //SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
  return (0UL);                                                     /* Function successful */
	#endif
}





