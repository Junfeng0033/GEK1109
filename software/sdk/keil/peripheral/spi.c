/****************************************************************************
 *   $Id:: spi.c 2021-06-03 22:40:16
 *   Project: Gecko SPI driver
 *
 *   Description:
 *     This file contains SPI code example
 *   Author:
 *   	 YJ
****************************************************************************/
//#include "platform_config.h"

#include "spi.h"
#include "uart.h"
#include "dma2d.h"
#include "gpio.h"
#include "lcd_driver.h"



volatile uint8 *hw_spi_rx_buffer;
uint16 hw_spi_rx_length;

//static void (*hw_spi_tx_fptr)(void);

uint16  HW_SPI_Read_Data(uint16 address)
{
	uint16 temp_data;
	while(SPI_READ_CTLREG(GECKO_APB_SPI_STATUS_REG) & GECKO_BIT(GECKO_APB_SPI_BUSBUSY_BIT));
	temp_data = SPI_READ_DATAREG(GECKO_APB_SPI_DATAACCESS_REG + address);
	while(SPI_READ_CTLREG(GECKO_APB_SPI_STATUS_REG) & GECKO_BIT(GECKO_APB_SPI_BUSBUSY_BIT));
	while(SPI_READ_CTLREG(GECKO_APB_SPI_STATUS_REG) & GECKO_BIT(GECKO_APB_SPI_BUSBUSY_BIT));
	temp_data = SPI_READ_DATAREG(GECKO_APB_SPI_DATAACCESS_REG);
	
	return temp_data;
}

//uint16  HW_SPI_Write_Data(uint16 address, uint16 data)
void HW_SPI_Write_Data(uint16 address, uint16 data)
{
	while(SPI_READ_CTLREG(GECKO_APB_SPI_STATUS_REG) & GECKO_BIT(GECKO_APB_SPI_TXFIFOFULL_BIT));
	SPI_WRITE_DATAREG(address, data);
	//return 0;
}






/*

在reg32_04[0:11]这12个bit中, size有两个bit，input [1:0] size; 分别是bit4和bit5.
//bit5:bit4
//2'b00:8bits; 
//2'b01:16bits(bit5=0,bit4=1); 
//2'b10:32bits(bit5=1,bit4=0);
//2'b11:24bits

*/


void SPI_32bit_Transfer(void)
{
	 hwp_spi0->CTROL=0x10fab;
}



void SPI_16bit_Transfer(void)
{
	 hwp_spi0->CTROL=0x10f9b;
}


void SPI_8bit_Transfer(void)
{
		hwp_spi0->CTROL = 0x10f8b;	//8bit spi data
}


void HW_SPI_Initialise(HAL_SPI_ID_T id)
{
	volatile unsigned int rd_data;
	//char *string;

	if(id==HAL_SPI_0)
	{
#if 1
		//register write test
		//HW_SPI_SET_REG(0x00,0x1234);
		//hwp_spi0->FIFODATA=0x1234;			
		HW_SPI_SET_REG(0x04,0x5678);
		hwp_spi0->CTROL=0x5678;			
		HW_SPI_SET_REG(0x08,0x5757);
		hwp_spi0->STATS=0x5678;
		HW_SPI_SET_REG(0x0C,0x3579);
		hwp_spi0->RCVINT=0x3579;

		rd_data=HW_SPI_GET_REG(0x08);
		rd_data=hwp_spi0->STATS;
		rd_data=HW_SPI_GET_REG(0x0C);
		rd_data=hwp_spi0->RCVINT;
#endif
		
		HW_SPI_SET_REG(XR7_SPI_TRANS_INT_EN,XR7_SPI_TRANS_TRIG_0);			
		hwp_spi0->TRANSINT=XR7_SPI_TRANS_TRIG_0;
		/* reset initial trans trigger value */
		HW_SPI_SET_REG(XR7_SPI_RCV_INT_EN,XR7_SPI_RECV_TRIG_1);
		hwp_spi0->RCVINT=XR7_SPI_RECV_TRIG_1;				
		/* set initial recv trigger value */

		HW_SPI_SET_REG(XR7_SPI_CTL, (XR7_SPI_CTL_LSB_ENABLE |XR7_SPI_CTL_MISO_ENABLE | XR7_SPI_CTL_SPI_ENABLE | XR7_SPI_CTL_FLUSH));
		hwp_spi0->CTROL=(XR7_SPI_CTL_LSB_ENABLE |XR7_SPI_CTL_MISO_ENABLE | XR7_SPI_CTL_SPI_ENABLE | XR7_SPI_CTL_FLUSH);
		//0x04=0x1_0fbb;
		HW_SPI_SET_REG(XR7_SPI_CTL,0x10fab);				
		SPI_WRITE_CTLREG(GECKO_APB_SPI_CONTROL_REG,0x10fbb);
		HW_SPI_SET_REG(XR7_SPI_CTL,0x10fab);

		hwp_spi0->CTROL = 0x10f8b;	//8bit spi data
		hwp_spi0->RCVINT = 0x0;		//mask all interrupt
		
	}		
	
	else if(id==HAL_SPI_1)
	{
#if 1
		//register write test
		//        hwp_spi1->FIFODATA=0x1234;
		hwp_spi1->CTROL=0x5678;	
		hwp_spi1->STATS=0x5678;
		hwp_spi1->RCVINT=0x3579;			
		rd_data=hwp_spi1->STATS;
		rd_data=hwp_spi1->RCVINT;			
#endif

		hwp_spi1->TRANSINT=XR7_SPI_TRANS_TRIG_0;
		/* reset initial trans trigger value */
		hwp_spi1->RCVINT=XR7_SPI_RECV_TRIG_1;				
		/* set initial recv trigger value */

		hwp_spi1->CTROL=(XR7_SPI_CTL_LSB_ENABLE |XR7_SPI_CTL_MISO_ENABLE | XR7_SPI_CTL_SPI_ENABLE | XR7_SPI_CTL_FLUSH);
		//0x04=0x1_0fbb;
		hwp_spi1->CTROL=0x10fbb;
	}
}




void HW_SPI_Tx_Char_Polled(volatile uint8 **buf, volatile uint32 *length, uint8 flag)
{
    uint32 count = *length;
    volatile uint8 *temp_buf;
	
	temp_buf = *buf;

	while(!(HW_SPI_GET_REG(XR7_SPI_STATUS) & XR7_LSR_THRE));    /* Wait until the UART transmitter is empty */

	/*
	 * Once the transmitter is empty, fill the FIFO with characters
	 */

	if(count >= HW_SPI_TX_FIFO_LENGTH)
		count = HW_SPI_TX_FIFO_LENGTH;

	(*length)-= count;

	while(count > 0)
	{
		HW_SPI_SET_REG(XR7_SPI_FIFO,*(temp_buf++));
		count--;
	}

	*buf = temp_buf;
}

/*****************************************************************************
 * dest     address of destination  (byte aligned)
 * src      address of source       (byte aligned)
 * size     in bytes 
//void Gecko_DMA_Transport(volatile void *dest,volatile const void *src, uint16 size,uint8 type, uint8 direct)
 *****************************************************************************/
void HW_SPI_Tx_Block(HAL_SPI_ID_T id,uint16 *pData, uint16 DataLen)
{
	int tmp=0;
	uint16 count = DataLen;	
	uint16 rd_data;
	volatile uint16 *temp_buf;	
	temp_buf = pData;

	if(count >= HW_SPI_TX_FIFO_LENGTH)
		count = HW_SPI_TX_FIFO_LENGTH;

	if(id == HAL_SPI_0)
	{

		//20240125@JF			
		//Before initiating the second DMA-SPI transfer, 
		//it is necessary to check whether SPI has completed the previous data transfer at this time
		//so we need to check spi_busy flag here.
		//The speed of DMA is much faster than that of SPI.	

		//reg_0x08(status register) check busy bit first	

		while((HW_SPI_GET_REG(XR7_SPI_STATUS)) & busy_spi_sync)
		{
			if(tmp++>500)
			{
				return;
			}
		}

#if GEK_DMA_ENABLE
		
		if(count > GECKO_DMA_MIN_SIZE)
		{
			Gecko_DMA_Transport((volatile uint32 *)(XR7_SPI_BASE + XR7_SPI_FIFO), pData, count, 
								AHB_DMA_CONTROL_HWORD_TR, AHB_DMA_CONTROL_SRC_INC_DES_NOINC);
		}
		else
#endif
		{
			while(count > 0)
			{
				//HW_SPI_SET_REG(XR7_SPI_FIFO,*(temp_buf));
				hwp_spi0->FIFODATA = *(temp_buf);
				temp_buf ++ ;
				count--;
			}
		}

		//HW_SPI_Empty_FIFO();
		//while((HW_SPI_GET_REG(XR7_SPI_STATUS)) & XR7_SPI_STATUS_RX_FIFO_INT_FLAG) /* Read all characters out of the fifo */
		//{
		//		;
		//}	
		//HW_SPI_GET_REG(XR7_SPI_STATUS)
		
		rd_data = hwp_spi0->STATS;
		rd_data = rd_data &	XR7_SPI_STATUS_RX_FIFO_INT_FLAG;
		
		while(rd_data) /* Read all characters out of the fifo */
		{
			;
		}
	}
	else if(id==HAL_SPI_1)
	{
			
		//20240125@JF			
		//Before initiating the second DMA-SPI transfer, 
		//it is necessary to check whether SPI has completed the previous data transfer at this time
		//so we need to check spi_busy flag here.
		//The speed of DMA is much faster than that of SPI.	

		//reg_0x08(status register) check busy bit first	
		while((HW_SPI_GET_REG(XR7_SPI_STATUS)) & busy_spi_sync)
		{
			if(tmp++>500)
			{
				return;
			}
		}			

#if GEK_DMA_ENABLE
		
		if(count > GECKO_DMA_MIN_SIZE)
		{
			Gecko_DMA_Transport((volatile uint32 *)(XR7_SPI_BASE + XR7_SPI_FIFO), 
			pData, count, AHB_DMA_CONTROL_BYTE_TR, AHB_DMA_CONTROL_SRC_INC_DES_NOINC);
		}
		else
#endif
		{
			while(count > 0)
			{
				//HW_SPI_SET_REG(XR7_SPI_FIFO,*(temp_buf));
				hwp_spi1->FIFODATA = *(temp_buf);
				temp_buf ++ ;
				count--;
			}
		}
		
		//HW_SPI_Empty_FIFO();
		//while((HW_SPI_GET_REG(XR7_SPI_STATUS)) & XR7_SPI_STATUS_RX_FIFO_INT_FLAG) /* Read all characters out of the fifo */
		//{
		//		;
		//}	
		//HW_SPI_GET_REG(XR7_SPI_STATUS)
		
		rd_data = hwp_spi1->STATS;
		rd_data = rd_data &	XR7_SPI_STATUS_RX_FIFO_INT_FLAG;
		
		while(rd_data) /* Read all characters out of the fifo */
		{
			;
		}
	}			
}



void HW_SPI_Interrupt_Handler(void)
{
	uint16 length = 0;
	while(((HW_SPI_GET_REG(XR7_SPI_STATUS)) & XR7_SPI_STATUS_RX_FIFO_INT_FLAG) && length < hw_spi_rx_length)
	{
		*hw_spi_rx_buffer=HW_SPI_GET_REG(XR7_SPI_FIFO) & 0xff;
		hw_spi_rx_buffer++;
		length ++;
	}

}

void HW_SPI_Setup(volatile uint8 *rx_buffer, uint16 rx_length, uint8 flag)
{
    if(rx_buffer!=NULL)
        hw_spi_rx_buffer = rx_buffer;
    hw_spi_rx_length = rx_length;
    HW_SPI_SET_REG(XR7_SPI_RCV_INT_EN,rx_length);
}

void HW_SPI_Empty_FIFO(void)
{
    while((HW_SPI_GET_REG(XR7_SPI_STATUS)) & XR7_SPI_STATUS_RX_FIFO_INT_FLAG) /* Read all characters out of the fifo */
    {
        ;
    }
}





//void HW_SPI_Tx_DMA(HAL_SPI_ID_T id,uint16 *pData, uint16 DataLen);

__RAM_CODE__ void HW_SPI_Tx_DMA(HAL_SPI_ID_T id,uint16 *pData, uint16 DataLen)
{

	LCD_RS_SET;


//	Gecko_DMA_Transport((volatile uint32 *)(XR7_SPI_BASE + XR7_SPI_FIFO), pData, DataLen, 
//						AHB_DMA_CONTROL_BYTE_TR, AHB_DMA_CONTROL_SRC_INC_DES_NOINC);


//
//	Gecko_DMA_Transport((volatile uint32 *)(XR7_SPI_BASE + XR7_SPI_FIFO), pData, DataLen, 
//						AHB_DMA_CONTROL_HWORD_TR, AHB_DMA_CONTROL_SRC_INC_DES_NOINC);

//

Gecko_DMA_Transport((volatile uint32 *)(XR7_SPI_BASE + XR7_SPI_FIFO), pData, DataLen, 
					AHB_DMA_CONTROL_WORD_TR, AHB_DMA_CONTROL_SRC_INC_DES_NOINC);	


}






//向lcd写入数据通过dma的方式
void Lcd_Write_data_dma(uint8_t *p_data, uint16_t len)
{
	LCD_RS_SET;

	
//	SPI_32bit_Transfer();	
//	Gecko_DMA_Transport((volatile uint32 *)(XR7_SPI_BASE + XR7_SPI_FIFO), p_data, len, 
//						AHB_DMA_CONTROL_WORD_TR, AHB_DMA_CONTROL_SRC_INC_DES_NOINC);	



	
	SPI_8bit_Transfer();
	Gecko_DMA_Transport((volatile uint32 *)(XR7_SPI_BASE + XR7_SPI_FIFO), p_data, len, 
						AHB_DMA_CONTROL_BYTE_TR, AHB_DMA_CONTROL_SRC_INC_DES_NOINC);
}





