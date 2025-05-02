/****************************************************************************
 *   $Id:: uart.c 2020-06-03 19:47:02
 *   Project: Gecko uart driver
 *
 *   Description:
 *     This file contains uart code example,
****************************************************************************/
//#include "gecko1108.h"			/* Gecko Peripheral Registers */
//it's different to ordinary uart interface. pay attention to 5V IO for data exchange@ACTION.
//LEFT			UART0
//MIDDLE		UART1
//RIGHT 		UART2
//port 1,uart1;2,uart2
//16B FIFO
//single line,first transmit mode and then switch to receive mode
//baud rate:9600bps or lower than 9600bps
//set it as 5V GPIO port
/**************************************************************************************/
//5V GPIO
//VOUT(5V)/UART_TX_RX/GPIO
//uart default receive mode, because most of time,it is standby for receiving,
//user should switch to transmit mode when need to send command.
//
/**************************************************************************************/

#include "platform_config.h"
#include "hci.h"
#include <stdarg.h>
#include <stdio.h>
#include "string.h"
#include "gecko1108.h"
#include "uart.h"

#include "dma2d.h"
#include "stdio.h"


extern void NVIC_EnableIRQ(IRQn_Type IRQn);
extern void NVIC_DisableIRQ(IRQn_Type IRQn);



/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
volatile uint8 comRXbuf[RXBUFSIZE]={0xFF};
bt_uart_ptr  *bt_tws_uart;






void uart_delay_us(uint32 units_of_u_secs)
{
	//volatile uint32 ii=0;
	//for(ii=0;ii<units_of_u_secs;ii++)
	while(units_of_u_secs--)
	{
		//ii++;
	}
	
}





void gecko_uart0_init(uint16 uart_setting)
{
		Gecko_Uart_Shutdown();
		Gecko_Uart_Restart();
		HWreg_UART_0_SET_REG(GECKO_UART_LCR, uart_setting|GECKO_LCR_8DIV);				
		//uint32 trx_fifo_trigger_length;
		HWreg_UART_0_SET_REG(GECKO_UART_FRR,UART_TX_FIFO_TRIGGER(1)|UART_RX_FIFO_TRIGGER(1));	
	
		//HWreg_UART_0_SET_REG(GECKO_UART_MCR, 0x00);    /* close auto baudrate detect module*/
	
	  //Gecko_Set_BaudRate(1,115200);
	  //HAL_UART_0
	  Gecko_Set_BaudRate(HAL_UART_0,115200);
	
	
}


void gecko_uart1_init(uint16 uart_setting)
{
		//Gecko_Uart_Shutdown();
	   HWreg_UART_1_SET_REG(GECKO_UART_IER,0); 
	
		//Gecko_Uart_Restart();
	  HWreg_UART_1_SET_REG(GECKO_UART_IER,1);
	
		HWreg_UART_1_SET_REG(GECKO_UART_LCR, uart_setting|GECKO_LCR_8DIV);				
		//uint32 trx_fifo_trigger_length;
		HWreg_UART_1_SET_REG(GECKO_UART_FRR,UART_TX_FIFO_TRIGGER(1)|UART_RX_FIFO_TRIGGER(1));	
	
		//HWreg_UART_1_SET_REG(GECKO_UART_MCR, 0x00);    /* close auto baudrate detect module*/
	
	  //Gecko_Set_BaudRate(HAL_UART_1,115200);
	  //HAL_UART_1
	  Gecko_Set_BaudRate(HAL_UART_1,115200);
}






void Uart_16550_Initialise(HAL_UART_ID_T id,uint32 baud_rate, uint16 uart_setting)
{
	
		//uint16 baud_divisor;
	  //uint8 _fifo_ctrl;
	
	
    /*
     * Clear the fptr in case an MSR interrupt happens before the upper layer
     * has initialised the pointer via a call to Tx_Block. We can validly
     * check against NULL.
     */
    uint8 mcr_value;
	
	
	 	if(id==HAL_UART_0)
		{
				Gecko_Uart_Shutdown();
				Gecko_Uart_Restart();
				//hcit_chimera_16550_tx_fptr = 0x0;

#if 0
				/* Initial UART Buffer Manager */
				bt_tws_uart->st = (uint8_t *) comRXbuf;
				bt_tws_uart->in = bt_tws_uart->st;
				bt_tws_uart->out = bt_tws_uart->st;
				bt_tws_uart->end = bt_tws_uart->st + RXBUFSIZE - 1;
#endif
				HWreg_UART_0_SET_REG(GECKO_UART_IER,0);             /* Disable 16550 Interrupts */

				/*
				 * An awkward implementation of UARTs on the Chimera board
				 * means that the NCO (Numerically Controlled Oscillator) used
				 * to generate the baud rate, is shared between both UARTs.
				 * To properly program the chosen UART, the DLAB for UART1 (the
				 * first UART, often incorrectly referred to as UART0) must first
				 * be set to access the DLM. To access the DLL, the DLAB for the _chosen_
				 * UART must also be set.
				 */

				//sys_hcit_uart_info.uart_setting = (XR7_LCR_8BITS | XR7_LCR_1STOP);
				HWreg_UART_0_SET_REG(GECKO_UART_LCR, uart_setting|GECKO_LCR_8DIV);
				
				
				//uint32 trx_fifo_trigger_length;
				HWreg_UART_0_SET_REG(GECKO_UART_FRR,UART_TX_FIFO_TRIGGER(1)|UART_RX_FIFO_TRIGGER(1));
				
				
				mcr_value = HWreg_UART_0_GET_REG(GECKO_UART_MCR);
				HWreg_UART_0_SET_REG(GECKO_UART_MCR, 0x00);    /* close auto baudrate detect module*/
				//#define XR7_MCR_PLSEL               0x100    /* 1:48M   0:24M */		
				HWreg_UART_0_SET_REG(GECKO_UART_MCR, XR7_MCR_PLSEL);  /*set UART clk  48MHz*/
				HWreg_UART_0_SET_REG(GECKO_UART_MCR, XR7_MCR_PLSEL|XR7_MCR_RTS); /* set RTS to 1*/
				if(mcr_value & 0x20)
						HWreg_UART_0_SET_REG(GECKO_UART_MCR, XR7_MCR_PLSEL|XR7_MCR_RTS|XR7_MCR_AFCE); /* set RTS to 1*/

				//HCIT_Chimera_16550_Set_BaudRate(baud_rate);
				Gecko_Set_BaudRate(id,baud_rate);
				/* Set UARTs int mask */
				HWreg_UART_0_SET_REG(GECKO_UART_IER, GECKO_IER_ERBFI );
				/*
				 * Interrupts enabled above:
				 * Received Data available
				 * Receiver line status interrupt
				 * Modem Status interrupt
				 */
				

#if 0				
				/******* configure the UART NVIC ********************************/
				hal_nvic_clear_pending_irq(UART0_IRQn);
				hal_nvic_set_priority(UART0_IRQn, 0);
				hal_nvic_enable_irq(UART0_IRQn);						
#endif	
				return;
	  }
		else if(id==HAL_UART_1) //AHB_UART1 ---> New UART --->2022-09-04
		{
				HWreg_UART_1_SET_REG(GECKO_UART_IER,0);   /* Disable 16550 Interrupts */
			
				HWreg_UART_1_SET_REG(GECKO_UART_IER,1);	  /* Enable 16550 Interrupts */
			
			  HWreg_UART_1_SET_REG(GECKO_UART_IER,0);     /* Disable 16550 Interrupts */
			
				//sys_hcit_uart_info.uart_setting = (XR7_LCR_8BITS | XR7_LCR_1STOP);
				HWreg_UART_1_SET_REG(GECKO_UART_LCR, uart_setting|GECKO_LCR_8DIV);

			
				//uint32 trx_fifo_trigger_length;
				HWreg_UART_1_SET_REG(GECKO_UART_FRR,UART_TX_FIFO_TRIGGER(1)|UART_RX_FIFO_TRIGGER(1));			
			
			

				mcr_value = HWreg_UART_1_GET_REG(GECKO_UART_MCR);
				HWreg_UART_1_SET_REG(GECKO_UART_MCR, 0x00);    /* close auto baudrate detect module*/
				//#define XR7_MCR_PLSEL               0x100    /* 1:48M   0:24M */		
				HWreg_UART_1_SET_REG(GECKO_UART_MCR, XR7_MCR_PLSEL);  /*set UART clk  48MHz*/
				HWreg_UART_1_SET_REG(GECKO_UART_MCR, XR7_MCR_PLSEL|XR7_MCR_RTS); /* set RTS to 1*/
				if(mcr_value & 0x20)
						HWreg_UART_1_SET_REG(GECKO_UART_MCR, XR7_MCR_PLSEL|XR7_MCR_RTS|XR7_MCR_AFCE); /* set RTS to 1*/

				
				
				//HCIT_Chimera_16550_Set_BaudRate(baud_rate);
				Gecko_Set_BaudRate(id,baud_rate);
				
		
				/* Set UARTs int mask */
				HWreg_UART_1_SET_REG(GECKO_UART_IER, GECKO_IER_ERBFI );

#if 0				
				
				/******* configure the UART NVIC ********************************/
				hal_nvic_clear_pending_irq(UART1_IRQn);
				hal_nvic_set_priority(UART1_IRQn, 0);
				hal_nvic_enable_irq(UART1_IRQn);						
#endif			
		}		

}





void Gecko_Uart_Set_AutoBaudRate_Enable(BOOL enable)
{
    if(enable)
    {
        HWreg_UART_0_SET_REG(GECKO_UART_MCR, HWreg_UART_0_GET_REG(GECKO_UART_MCR) | XR7_MCR_AUTODETECTBAUDRATE);
    }
    else
    {
        HWreg_UART_0_SET_REG(GECKO_UART_MCR, HWreg_UART_0_GET_REG(GECKO_UART_MCR) & ~XR7_MCR_AUTODETECTBAUDRATE);
    }
}





void Gecko_Set_BaudRate(HAL_UART_ID_T id,uint32 baud_rate)
{
    uint32 baud_divisor;
    uint32 baud_mod;
    uint32 dec_cnt;
    baud_divisor = (HCI_clock_frequency / baud_rate) / 8;
    baud_mod = (HCI_clock_frequency / baud_rate) % 8;
    dec_cnt = (HCI_clock_frequency*10/baud_rate) % 10;

	 	if(id==HAL_UART_0)
		{	
	
			HWreg_UART_0_SET_REG(GECKO_UART_IER,0);			   /* Disable Uart Interrupts */
		
			HWreg_UART_0_SET_REG(GECKO_UART_LCR, HWreg_UART_0_GET_REG(GECKO_UART_LCR) | GECKO_LCR_DLAB);		
			HWreg_UART_0_SET_REG(XR7_HCIT_DLL, baud_divisor & 0xFF);
			HWreg_UART_0_SET_REG(XR7_HCIT_DLH, (baud_divisor & 0xFF00)>>8);		
			
			//HWreg_UART_0_SET_REG(XR7_HCIT_DL2, ((baud_mod >> 0x1)+((baud_mod+(baud_mod&1)) << 0x3)));
				HWreg_UART_0_SET_REG(XR7_HCIT_DL2, ((baud_mod >> 0x1)+((baud_mod+(baud_mod&1)) << 0x3) + 0x11 )); 	
			//HWreg_UART_0_SET_REG(XR7_HCIT_DL2, 0x43);//8bit register		

			
		  HWreg_UART_0_SET_REG(XR7_DEC_CNT, (HWreg_UART_0_GET_REG(XR7_DEC_CNT)&(~0xf))|dec_cnt);		
			HWreg_UART_0_SET_REG(GECKO_UART_LCR, HWreg_UART_0_GET_REG(GECKO_UART_LCR) & ~ GECKO_LCR_DLAB);
			
			
			//HWreg_UART_0_SET_REG(GECKO_UART_FCR, GECKO_FCR_ENABLE | GECKO_FCR_RX_FIFO_RESET | GECKO_FCR_TX_FIFO_RESET);
			#if 1
					/* Interrupt & FIFO section */
					
					/* Enable fifo */
			
					uint8 _fifo_ctrl;
			
					_fifo_ctrl = GECKO_FCR_ENABLE;
					
					
					/* Clear transmit and receive fifos */
					
					_fifo_ctrl |= GECKO_FCR_TX_FIFO_RESET;
					_fifo_ctrl |= GECKO_FCR_RX_FIFO_RESET;

					/*
					 * The following figures relate to the UART with the 16 byte
					 * FIFO (UART1). In the case of UART2 or UART3, these numbers
					 * are wired to the FIFO locations of 1 2 3 and 4.
					 */

			#if GECKO_16550_RECV_FIFO_TRIGGER ==   14

					_fifo_ctrl |= GECKO_FCR_RECV_TRIGL_14;
					_fifo_ctrl |= GECKO_FCR_RECV_TRIGM_14;

			#elif GECKO_16550_RECV_FIFO_TRIGGER == 8

					_fifo_ctrl |= GECKO_FCR_RECV_TRIGL_8;
					_fifo_ctrl |= GECKO_FCR_RECV_TRIGM_8;

			#elif GECKO_16550_RECV_FIFO_TRIGGER == 4

					_fifo_ctrl |= GECKO_FCR_RECV_TRIGL_4;
					_fifo_ctrl |= GECKO_FCR_RECV_TRIGM_4;

			#elif GECKO_16550_RECV_FIFO_TRIGGER == 1

					_fifo_ctrl |= GECKO_FCR_RECV_TRIGL_1;
					_fifo_ctrl |= GECKO_FCR_RECV_TRIGM_1;

			#else
					#error Please define GECKO_RECV_FIFO_LENGTH
			#endif

					HWreg_UART_0_SET_REG(GECKO_UART_FCR,_fifo_ctrl);
			#endif
			
			HWreg_UART_0_SET_REG(GECKO_UART_IER,1);
			
		}
		else if(id==HAL_UART_1)
		{
			HWreg_UART_1_SET_REG(GECKO_UART_IER,0);			   /* Disable Uart Interrupts */
		
			HWreg_UART_1_SET_REG(GECKO_UART_LCR, HWreg_UART_1_GET_REG(GECKO_UART_LCR) | GECKO_LCR_DLAB);		
			HWreg_UART_1_SET_REG(XR7_HCIT_DLL, baud_divisor & 0xFF);
			HWreg_UART_1_SET_REG(XR7_HCIT_DLH, (baud_divisor & 0xFF00)>>8);
			
			//HWreg_UART_1_SET_REG(XR7_HCIT_DL2, ((baud_mod >> 0x1)+((baud_mod+(baud_mod&1)) << 0x3)));
			HWreg_UART_1_SET_REG(XR7_HCIT_DL2, ((baud_mod >> 0x1)+((baud_mod+(baud_mod&1)) << 0x3) + 0x11 )); 	
			
			HWreg_UART_1_SET_REG(XR7_DEC_CNT, (HWreg_UART_1_GET_REG(XR7_DEC_CNT)&(~0xf))|dec_cnt);		
			HWreg_UART_1_SET_REG(GECKO_UART_LCR, HWreg_UART_1_GET_REG(GECKO_UART_LCR) & ~ GECKO_LCR_DLAB);
			
			//HWreg_UART_1_SET_REG(GECKO_UART_FCR, GECKO_FCR_ENABLE | GECKO_FCR_RX_FIFO_RESET | GECKO_FCR_TX_FIFO_RESET);
			
			#if 1
					/* Interrupt & FIFO section */
					
					/* Enable fifo */
			
					uint8 _fifo_ctrl;
			
					_fifo_ctrl = GECKO_FCR_ENABLE;
					
					
					/* Clear transmit and receive fifos */
					
					_fifo_ctrl |= GECKO_FCR_TX_FIFO_RESET;
					_fifo_ctrl |= GECKO_FCR_RX_FIFO_RESET;

					/*
					 * The following figures relate to the UART with the 16 byte
					 * FIFO (UART1). In the case of UART2 or UART3, these numbers
					 * are wired to the FIFO locations of 1 2 3 and 4.
					 */

			#if GECKO_16550_RECV_FIFO_TRIGGER ==   14

					_fifo_ctrl |= GECKO_FCR_RECV_TRIGL_14;
					_fifo_ctrl |= GECKO_FCR_RECV_TRIGM_14;

			#elif GECKO_16550_RECV_FIFO_TRIGGER == 8

					_fifo_ctrl |= GECKO_FCR_RECV_TRIGL_8;
					_fifo_ctrl |= GECKO_FCR_RECV_TRIGM_8;

			#elif GECKO_16550_RECV_FIFO_TRIGGER == 4

					_fifo_ctrl |= GECKO_FCR_RECV_TRIGL_4;
					_fifo_ctrl |= GECKO_FCR_RECV_TRIGM_4;

			#elif GECKO_16550_RECV_FIFO_TRIGGER == 1

					_fifo_ctrl |= GECKO_FCR_RECV_TRIGL_1;
					_fifo_ctrl |= GECKO_FCR_RECV_TRIGM_1;

			#else
					#error Please define GECKO_RECV_FIFO_LENGTH
			#endif

					HWreg_UART_1_SET_REG(GECKO_UART_FCR,_fifo_ctrl);
			#endif
			
			HWreg_UART_1_SET_REG(GECKO_UART_IER,1);
		}		
}





void Gecko_Uart_Shutdown(void)
{
    HWreg_UART_0_SET_REG(GECKO_UART_IER,0);   /* Disable 16550 Interrupts */
}


void Gecko_Uart_Restart(void)
{
    HWreg_UART_0_SET_REG(GECKO_UART_IER,1);
}




void Gecko_Uart0_Send_Char(char s)
{

	HWreg_UART_0_SET_REG(GECKO_UART_RBRTHR,s);
  while(!((HWreg_UART_0_GET_REG(GECKO_UART_LSR)) & GECKO_LSR_TEMT));    /* Wait until the UART transmitter is finished */
	//////uart_delay_us(20);//comment this line //2022-02-24
	
}


void Gecko_Uart1_Send_Char(char s)
{
	
	HWreg_UART_1_SET_REG(GECKO_UART_RBRTHR,s);
  while(!((HWreg_UART_1_GET_REG(GECKO_UART_LSR)) & GECKO_LSR_TEMT));    /* Wait until the UART transmitter is finished */
	//uart_delay_us(20);
	
}





//uart fifo depth is 4,  check tx_count before writing fifo 
void Gecko_Uart_Tx_Data(HAL_UART_ID_T id,uint8 *pData, uint16 DataLen)
{

    uint16 count = DataLen;	
    volatile uint8 *temp_buf;
    volatile uint8 status;	
    temp_buf = pData;
	  //int timeout=0;

	 	if(id==HAL_UART_0)
		{		
				/*
				 * Once the transmitter is empty, fill the FIFO with characters
				 */
				if(count>=4)
					count=4;//GECKO1108_TX_FIFO_LENGTH=4
			
				while(count > 0)
				{
						{
							HWreg_UART_0_SET_REG(GECKO_UART_RBRTHR,*(temp_buf));
						} 
						temp_buf ++ ;
						count--;
						//uart_delay_us(1);
				}

				//uart_delay_us(10);
				while(!((HWreg_UART_0_GET_REG(GECKO_UART_LSR)) & GECKO_LSR_TEMT));    /* Wait until the UART transmitter is finished */
		
		}	
		else if(id==HAL_UART_1)
		{

				if(count>=4)
					count=4;//GECKO1108_TX_FIFO_LENGTH=4
				
				while(count > 0)
				{
						{
							HWreg_UART_1_SET_REG(GECKO_UART_RBRTHR,*(temp_buf));
						} 
						temp_buf ++ ;
						count--;
				}			 
        
				//uart_delay_us(10);
				while(!((HWreg_UART_1_GET_REG(GECKO_UART_LSR)) & GECKO_LSR_TEMT)); 
				
		}			
}





void Gecko_Uart0_Empty_TXFinish(void)
{
    while(!(HWreg_UART_0_GET_REG(GECKO_UART_LSR) & GECKO_LSR_TEMT));    /* Wait until the UART transmitter is finished */
}

void Gecko_Uart1_Empty_TXFinish(void)
{
    while(!(HWreg_UART_1_GET_REG(GECKO_UART_LSR) & GECKO_LSR_TEMT));    /* Wait until the UART transmitter is finished */
}





/*
 * UART0_Interrupt_Handler
 *
 * paramters: void
 * returns: void
 *
 * Handle interrupts from the 16550 UART
 */

void UART0_Interrupt_Handler(void)
{
    uint8 status;
    uint8 ch;
    //uint16 length = 0;
		volatile uint8  res;
	
    /*
     * Level triggered interrupt, no need to clear any ICR condition
     */
    status = HWreg_UART_0_GET_REG(GECKO_UART_IIR) & GECKO_IIR_ID_MASK;   /* Not interested in upper 5 bits */

    if(!((status) & (GECKO_IIR_INT_NOT_PENDING)))                     /* While there are interrupts pending */
    {
        switch(status)
        {
            case GECKO_IIR_RLS:                                 /* This only fires with break or an error */
                ch = HWreg_UART_0_GET_REG(GECKO_UART_LSR);         /* Clear interrupt by reading LSR */

                if(ch & GECKO_LSR_FE)
								    //#error UART_FRAMING_ERROR
									#if pDEBUG
									printf("UART_FRAMING_ERROR");
								  #endif
                if(ch & GECKO_LSR_OE)
                    //#error UART_OVERRUN_ERROR
									#if pDEBUG
									printf("UART_OVERRUN_ERROR");
								  #endif								
                break;
            case GECKO_IIR_RECVBUF:
							
								//uboot receive command and DATA from uart0					

								res=HWreg_UART_0_GETBYTE_REG(GECKO_UART_RBRTHR)&0xff;

						    //uboot_receive_command(res);
			
	
								break;

            case GECKO_IIR_THRE:                                         /* Turn off tx interrupts again */

                break;
        }
				status = HWreg_UART_0_GET_REG(GECKO_UART_IIR) & 0x7;            /* Re-read status */
    }
}






void UART1_Interrupt_Handler(void)
{
    uint8 status;
    uint8 ch;
    //uint16 length = 0;
		volatile uint8  res;
	
	

	
    /*
     * Level triggered interrupt, no need to clear any ICR condition
     */
    status = HWreg_UART_1_GET_REG(GECKO_UART_IIR) & GECKO_IIR_ID_MASK;   /* Not interested in upper 5 bits */

    if(!((status) & (GECKO_IIR_INT_NOT_PENDING)))                     /* While there are interrupts pending */
    {
        switch(status)
        {
            case GECKO_IIR_RLS:                                 /* This only fires with break or an error */
                ch = HWreg_UART_1_GET_REG(GECKO_UART_LSR);         /* Clear interrupt by reading LSR */

                if(ch & GECKO_LSR_FE)
								    //#error UART_FRAMING_ERROR
									#if pDEBUG
									printf("UART_FRAMING_ERROR");
								  #endif
                if(ch & GECKO_LSR_OE)
                    //#error UART_OVERRUN_ERROR
									#if pDEBUG
									printf("UART_OVERRUN_ERROR");
								  #endif								
                break;
            case GECKO_IIR_RECVBUF:
							
								//uboot receive command and DATA from uart1

								res=HWreg_UART_1_GETBYTE_REG(GECKO_UART_RBRTHR)&0xff;

						    //uboot_receive_command(res);

								break;

            case GECKO_IIR_THRE:                                         /* Turn off tx interrupts again */

                break;
        }
				status = HWreg_UART_1_GET_REG(GECKO_UART_IIR) & 0x7;            /* Re-read status */
    }
}







/*******************************************************************************
*	bit5 and bit4
*
*	sout_cfg[1:0]
*	sout_cfg[1]---dr
*	sout_cfg[0]---reg
*
*	sout_cfg[1]=0,hardware auto;other wise software controll sout,sout_cfg[1]=1,
**********************************************************************************/

uint8 Switch_UartTxRx_Mode(HAL_UART_ID_T id,uint8 mode)
{
		uint8 val;	
	
		
		if(id==HAL_UART_1)
		{
				val = HWreg_UART_1_GET_REG(GECKO_UART_SOUT_CFG);
			
				val = val| GECKO_UART_SOUT_CFG_1; //set sout_cfg[1]=1
			
				HWreg_UART_1_SET_REG(GECKO_UART_SOUT_CFG,val);
			
				switch(mode)
				{
					case UART_TX_MODE:
						
						val = HWreg_UART_1_GET_REG(GECKO_UART_SOUT_CFG);//
					
						val = val & (~GECKO_UART_SOUT_CFG_0); //set sout_cfg[0]=0	
					
						HWreg_UART_1_SET_REG(GECKO_UART_SOUT_CFG,val);
					
					  HWreg_UART_1_SET_REG(GECKO_UART_FRR,UART_TX_FIFO_TRIGGER(0x1FF)|UART_RX_FIFO_TRIGGER(0x1FF));
					  HWreg_UART_1_SET_REG(GECKO_UART_FCR, GECKO_FCR_ENABLE | GECKO_FCR_RX_FIFO_RESET | GECKO_FCR_TX_FIFO_RESET);

					  hal_nvic_clear_pending_irq(UART1_IRQn);					    					
					  NVIC_DisableIRQ(UART1_IRQn);
					
						break;
					case UART_RX_MODE:
						
						val = HWreg_UART_1_GET_REG(GECKO_UART_SOUT_CFG);
					
						val = val | GECKO_UART_SOUT_CFG_0; //set sout_cfg[0]=1	
					
						HWreg_UART_1_SET_REG(GECKO_UART_SOUT_CFG,val);			


					  HWreg_UART_1_SET_REG(GECKO_UART_FRR,UART_TX_FIFO_TRIGGER(0x1FF)|UART_RX_FIFO_TRIGGER(1));	
					  HWreg_UART_1_SET_REG(GECKO_UART_FCR, GECKO_FCR_ENABLE | GECKO_FCR_RX_FIFO_RESET | GECKO_FCR_TX_FIFO_RESET);
						
				    hal_nvic_clear_pending_irq(UART1_IRQn);	
						hal_nvic_set_priority(UART1_IRQn, 0);						
					  NVIC_EnableIRQ(UART1_IRQn);							
						break;
					default:
						break;			
				}				
		}		
		else if(id==HAL_UART_0)
		{
				val = HWreg_UART_0_GET_REG(GECKO_UART_SOUT_CFG);
			
				val = val| GECKO_UART_SOUT_CFG_1; //set sout_cfg[1]=1
			
				HWreg_UART_0_SET_REG(GECKO_UART_SOUT_CFG,val);
			
				switch(mode)
				{
					case UART_TX_MODE:
						
						val = HWreg_UART_0_GET_REG(GECKO_UART_SOUT_CFG);
					
						val = val & (~GECKO_UART_SOUT_CFG_0); //set sout_cfg[0]=0	
					
						HWreg_UART_0_SET_REG(GECKO_UART_SOUT_CFG,val);
					
					  HWreg_UART_0_SET_REG(GECKO_UART_FRR,UART_TX_FIFO_TRIGGER(0x1FF)|UART_RX_FIFO_TRIGGER(0x1FF));
					  HWreg_UART_0_SET_REG(GECKO_UART_FCR, GECKO_FCR_ENABLE | GECKO_FCR_RX_FIFO_RESET | GECKO_FCR_TX_FIFO_RESET);

					  hal_nvic_clear_pending_irq(UART0_IRQn);					    					
					  NVIC_DisableIRQ(UART0_IRQn);
					
						break;
					case UART_RX_MODE:
						
						val = HWreg_UART_0_GET_REG(GECKO_UART_SOUT_CFG);
					
						val = val | GECKO_UART_SOUT_CFG_0; //set sout_cfg[0]=1	
					
						HWreg_UART_0_SET_REG(GECKO_UART_SOUT_CFG,val);			


					  HWreg_UART_0_SET_REG(GECKO_UART_FRR,UART_TX_FIFO_TRIGGER(0x1FF)|UART_RX_FIFO_TRIGGER(1));	
					  HWreg_UART_0_SET_REG(GECKO_UART_FCR, GECKO_FCR_ENABLE | GECKO_FCR_RX_FIFO_RESET | GECKO_FCR_TX_FIFO_RESET);
						
				    hal_nvic_clear_pending_irq(UART0_IRQn);	
						hal_nvic_set_priority(UART0_IRQn, 0);						
					  NVIC_EnableIRQ(UART0_IRQn);							
						break;
					default:
						break;			
				}			
			
			
		}
		return NOERROR;
}









void UATR0_PRINT_LOG(unsigned char *s) {
    //int i;
    while(*s != 0)
		    Gecko_Uart_Tx_Data(HAL_UART_0,(s++),1);
}


void UATR1_PRINT_LOG(unsigned char *s) {
    //int i;
    while(*s != 0)
		    Gecko_Uart_Tx_Data(HAL_UART_1,(s++),1);
}








void Uart0_SendString(char string)
{
		//uart1 for debug on fpga
		volatile uint16 count=1;	
		volatile char *temp_buf;	
		*temp_buf = string;	
	

		while(!(HWreg_UART_0_GET_REG(GECKO_UART_LSR) & GECKO_LSR_THRE));    /* Wait until the UART transmitter is empty */
		/*
		 * Once the transmitter is empty, fill the FIFO with characters
		 */
		if(count>=4)
			count=4;//GECKO1108_TX_FIFO_LENGTH=4
	
		while(count > 0)
		{
				{
					HWreg_UART_0_SET_REG(GECKO_UART_RBRTHR,*(temp_buf));
				} 
				temp_buf ++ ;
				count--;

		}	


		/*
		 * Turn on transmitter interrupts
		 */
		//HWreg_UART_0_SET_REG(GECKO_UART_IER, HWreg_UART_0_GET_REG(GECKO_UART_IER) | GECKO_IER_ETBEI);				
		while(!(HWreg_UART_0_GET_REG(GECKO_UART_LSR) & GECKO_LSR_TEMT));    /* Wait until the UART transmitter is finished */
		
}






#if 1//


char *reverse(char *s)
{
	char temp;
	char *p = s;
	char *q = s;
	while(*q)
		++q;
	q--;
 

	while(q > p)
	{
		temp = *p;
		*p++ = *q;
		*q-- = temp;
	}
	return s;
}




char *my_itoa(int n)
{
	int i = 0,isNegative = 0;
	static char s[64];
	char table[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" ;	
	int radix=16;//HEX Mode
	if((isNegative = n) < 0)
	{
		n = -n;
	}
	
	
	do
	{
		//s[i++] = n%radix + '0';
		s[i++]=table[n%radix];
		n = n/radix;
	}while(n > 0);


	
	if(isNegative < 0)
	{
		s[i++] = '-';
	}
	s[i] = '\0';
	return reverse(s);	
}


#endif





void gecko1108_product_information(void)
{
	  //UART_PRINT_LOG("***GEK1108***");
	  //const char thing[] = "string";
	  //char *str="abcd"; 
	  //signed char *s_str = str;
	  //UATR0_PRINT_LOG(s_str);
	  //unsigned char u_str[]="abcdefg";
		//char str[64];
    //strcpy(str,(char *)u_str);
    //UATR0_PRINT_LOG(u_str);
		//char str_u[];
		//unsigned char str2[64]="hijklmn";
    //memcpy(str_u,str2,strlen(str2)+1);	
	
    //unsigned char u_str[]="********************************GEK1108**************************************";
		//UATR0_PRINT_LOG("********************************GEK1108**************************************");
	  //UATR0_PRINT_LOG(u_str);

    UATR0_PRINT_LOG((unsigned char *)("\r\n"));	
	  UATR1_PRINT_LOG((unsigned char *)("\r\n"));
	  //UATR2_PRINT_LOG((unsigned char *)("\r\n"));
	
		UATR0_PRINT_LOG((unsigned char *)("********************************###GEK1109###**************************************"));
		UATR1_PRINT_LOG((unsigned char *)("********************************###GEK1109###**************************************"));	
		//UATR2_PRINT_LOG((unsigned char *)("********************************###GEK1109###**************************************"));	
	
    UATR0_PRINT_LOG((unsigned char *)("\r\n"));	
	  UATR1_PRINT_LOG((unsigned char *)("\r\n"));
	  //UATR2_PRINT_LOG((unsigned char *)("\r\n"));
	
	  UATR0_PRINT_LOG((unsigned char *)("Gecko1108 TWS Charger Solution Software, Copyright (c) 2020-2022 Gecko Inc."));
	  UATR1_PRINT_LOG((unsigned char *)("Gecko1108 TWS Charger Solution Software, Copyright (c) 2020-2022 Gecko Inc."));	
	  //UATR2_PRINT_LOG((unsigned char *)("Gecko1108 TWS Charger Solution Software, Copyright (c) 2020-2022 Gecko Inc."));	
		
		
    UATR0_PRINT_LOG((unsigned char *)("\r\n"));	
	  UATR1_PRINT_LOG((unsigned char *)("\r\n"));		
    UATR0_PRINT_LOG((unsigned char *)("\r\n"));	
	  UATR1_PRINT_LOG((unsigned char *)("\r\n"));
    UATR0_PRINT_LOG((unsigned char *)("\r\n"));	
	  UATR1_PRINT_LOG((unsigned char *)("\r\n"));



    UATR0_PRINT_LOG((unsigned char *)("\r\n"));
    UATR1_PRINT_LOG((unsigned char *)("\r\n"));		
    UATR0_PRINT_LOG((unsigned char *)("Platform:"));
    UATR1_PRINT_LOG((unsigned char *)("Platform:"));		
	  UATR0_PRINT_LOG((unsigned char *)(PLATFORMSTRING));
	  UATR1_PRINT_LOG((unsigned char *)(PLATFORMSTRING));		
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));
		UATR1_PRINT_LOG((unsigned char *)("\r\n"));		
    //pDebugPrintfEX("Manufacturer Name: %#04x\n\n", MANUFACTURER_NAME);

    UATR0_PRINT_LOG((unsigned char *)("Manufacturer Name:"));		
    UATR1_PRINT_LOG((unsigned char *)("Manufacturer Name:"));		
	  UATR0_PRINT_LOG((unsigned char *)(MANUFACTURER_NAME));
	  UATR1_PRINT_LOG((unsigned char *)(MANUFACTURER_NAME));		
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));
		UATR1_PRINT_LOG((unsigned char *)("\r\n"));

	  UATR0_PRINT_LOG((unsigned char *)("Chip Local Name:"));
	  UATR1_PRINT_LOG((unsigned char *)("Chip Local Name:"));		
		UATR0_PRINT_LOG((unsigned char *)(CHIP_LOCAL_NAME));
		UATR1_PRINT_LOG((unsigned char *)(CHIP_LOCAL_NAME));		
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));
		UATR1_PRINT_LOG((unsigned char *)("\r\n"));		

    UATR0_PRINT_LOG((unsigned char *)("Time:"));
    UATR1_PRINT_LOG((unsigned char *)("Time:"));			
	  UATR0_PRINT_LOG((unsigned char *)("2024-6-21"));
	  UATR1_PRINT_LOG((unsigned char *)("2024-6-21"));		
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));
		UATR1_PRINT_LOG((unsigned char *)("\r\n"));		


	  #if 0
    UATR0_PRINT_LOG((unsigned char *)("\r\n"));	
		UATR0_PRINT_LOG((unsigned char *)("********************************GEK1109**************************************"));	
	  UATR0_PRINT_LOG((unsigned char *)("\r\n"));
	  UATR0_PRINT_LOG((unsigned char *)("Gecko1109 wireless microphone Charger Solution Software, Copyright (c) 2020-2022 Gecko Inc."));
    UATR0_PRINT_LOG((unsigned char *)("\r\n"));
		
    UATR0_PRINT_LOG((unsigned char *)("Platform:"));		
	  UATR0_PRINT_LOG((unsigned char *)(PLATFORMSTRING));
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));
    //pDebugPrintfEX("Manufacturer Name: %#04x\n\n", MANUFACTURER_NAME);

    UATR0_PRINT_LOG((unsigned char *)("Manufacturer Name:"));		
	  UATR0_PRINT_LOG((unsigned char *)(MANUFACTURER_NAME));
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));
	
	  UATR0_PRINT_LOG((unsigned char *)("Chip Local Name:"));
		UATR0_PRINT_LOG((unsigned char *)(CHIP_LOCAL_NAME));
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));

    UATR0_PRINT_LOG((unsigned char *)("Time:"));		
	  UATR0_PRINT_LOG((unsigned char *)("2021-4-15"));
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));	
	
		UATR0_PRINT_LOG((unsigned char *)("flash base addr: 0x"));
		char *string;
    int addr_base=0x10000000;		
		string=my_itoa(addr_base);
		UATR0_PRINT_LOG((unsigned char *)(string));
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));	
		
		UATR0_PRINT_LOG((unsigned char *)("rom base addr: 0x"));
		//char *string;
    addr_base=0x00000000;		
		string=my_itoa(addr_base);
		UATR0_PRINT_LOG((unsigned char *)(string));
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));
		
		UATR0_PRINT_LOG((unsigned char *)("lightning base addr: 0x"));		
    addr_base=0x40017000;		
		string=my_itoa(addr_base);
		UATR0_PRINT_LOG((unsigned char *)(string));
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));
		
		UATR0_PRINT_LOG((unsigned char *)("pwm base addr: 0x"));		
    addr_base=0x40013000;		
		string=my_itoa(addr_base);
		UATR0_PRINT_LOG((unsigned char *)(string));
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));
		
		UATR0_PRINT_LOG((unsigned char *)("gpio group 0 base addr: 0x"));		
    addr_base=0x40018000;		
		string=my_itoa(addr_base);
		UATR0_PRINT_LOG((unsigned char *)(string));
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));
		
		UATR0_PRINT_LOG((unsigned char *)("gpio group 1 base addr: 0x"));		
    addr_base=0x40019000;		
		string=my_itoa(addr_base);
		UATR0_PRINT_LOG((unsigned char *)(string));
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));


		UATR0_PRINT_LOG((unsigned char *)("uart0 base addr: 0x"));		
    addr_base=0x40001000;		
		string=my_itoa(addr_base);
		UATR0_PRINT_LOG((unsigned char *)(string));
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));
		
		UATR0_PRINT_LOG((unsigned char *)("uart1 base addr: 0x"));		
    addr_base=0x40003000;		
		string=my_itoa(addr_base);
		UATR0_PRINT_LOG((unsigned char *)(string));
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));

		UATR0_PRINT_LOG((unsigned char *)("adc base addr: 0x"));		
    addr_base=0x40016000;		
		string=my_itoa(addr_base);
		UATR0_PRINT_LOG((unsigned char *)(string));
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));
		
		UATR0_PRINT_LOG((unsigned char *)("efuse base addr: 0x"));		
    addr_base=0x40015000;		
		string=my_itoa(addr_base);
		UATR0_PRINT_LOG((unsigned char *)(string));
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));		
		
		UATR0_PRINT_LOG((unsigned char *)("********************************GEK1108**************************************"));
		UATR0_PRINT_LOG((unsigned char *)("\r\n"));
		#endif
}






void pDebugPrintfEX(char *format, ...)
{
	 va_list args;
	 unsigned char string[256];
   va_start(args, format);
	
	 char* dst = (char*)string;
	 vsprintf(dst,format,args);
	
	 UATR0_PRINT_LOG(string);
	
   vprintf(format, args);
   va_end(args);
}






/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
	Gecko_Uart0_Send_Char(ch);
	return ch;
}




