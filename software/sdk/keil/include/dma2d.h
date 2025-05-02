#include "platform_config.h"


#define AHB_DMA_BASE                     				0x40006000
//| Slv 7 | UART3         										| 0x4000_6000 - 0x4000_6fff

//#define GEK_DMA_ENABLE             0
#define GEK_DMA_ENABLE             1


#define AHB_DMA_CONTROL_REG                     (AHB_DMA_BASE + 0x00)
#define AHB_DMA_SRCADDR_REG                     (AHB_DMA_BASE + 0x04)
#define AHB_DMA_DESTADDR_REG                    (AHB_DMA_BASE + 0x08)
#define AHB_DMA_DATALENGTH_REG                  (AHB_DMA_BASE + 0x0C)
//#######################################################################
//New Register for GEK1109
#define AHB_DMA_DONE_STS_REG                  	(AHB_DMA_BASE + 0x10) //dma done status register
#define AHB_DMA_STEP_CTRL_REG                  	(AHB_DMA_BASE + 0x14) //dma carry data step control register


//register 0x14
#define dma_for_dac_en				  (1<<18)
#define dma_int_mask				    (1<<17)//set this bit "1" to enable DMA Interrupt.
#define dma_int_clear				    (1<<16)
//#######################################################################




#define AHB_DMA_CONTROL_SRC_INC_DES_INC         0
#define AHB_DMA_CONTROL_SRC_NOINC_DES_INC       1
#define AHB_DMA_CONTROL_SRC_INC_DES_NOINC       2
#define AHB_DMA_CONTROL_SRC_NOINC_DES_NOINC     3

#define AHB_DMA_CONTROL_WORD_TR                 0x08
#define AHB_DMA_CONTROL_HWORD_TR                0x04
#define AHB_DMA_CONTROL_BYTE_TR                 0x00

#define GECKO_DMA_MIN_SIZE                   	  (16)


#define DMA_READ_REG(REG)      									(*(volatile uint32*)(REG))
#define DMA_WRITE_REG(REG,VAL)    							(*(volatile uint32*)(REG)) = (uint32)(VAL) 





#define DMA2D_INPUT_ARGB8888        0x00000000U  /*!< ARGB8888 color mode */
#define DMA2D_INPUT_RGB888          0x00000001U  /*!< RGB888 color mode   */
#define DMA2D_INPUT_RGB565          0x00000002U  /*!< RGB565 color mode   */
#define DMA2D_INPUT_ARGB1555        0x00000003U  /*!< ARGB1555 color mode */
#define DMA2D_INPUT_ARGB4444        0x00000004U  /*!< ARGB4444 color mode */
#define DMA2D_INPUT_L8              0x00000005U  /*!< L8 color mode       */
#define DMA2D_INPUT_AL44            0x00000006U  /*!< AL44 color mode     */
#define DMA2D_INPUT_AL88            0x00000007U  /*!< AL88 color mode     */
#define DMA2D_INPUT_L4              0x00000008U  /*!< L4 color mode       */
#define DMA2D_INPUT_A8              0x00000009U  /*!< A8 color mode       */
#define DMA2D_INPUT_A4              0x0000000AU  /*!< A4 color mode       */
#define DMA2D_INPUT_YCBCR           0x0000000BU  /*!< YCbCr color mode */



typedef volatile struct
{
    REG32                          CR;                  //0x00000000
    REG32                          FGMAR;               //0x00000004
    REG32                          OMAR;                //0x00000008
    REG32                          FGOR;                //0x0000000C
    REG32                          OOR;                 //0x00000010
    REG32                          FGPFCCR;             //0x00000014
    REG32                          NLR;             		//0x00000018
} HW_DMA2D;


#define DMA2D                   ((HW_DMA2D*) AHB_DMA_BASE)



void Gecko_DMA_Transport(volatile void *dest,volatile const void *src, uint16 size,uint8 type, uint8 direct);
void DMA_Configuration(void);
void Clear_DMA_Interrupt(void);
void DMA_ISR_Routine(void);

//void dma2d_memcopy(uint32_t pixelformat, void * psrc, void * pdst, int width, int height, int offLinesrc, int offLinedst);

