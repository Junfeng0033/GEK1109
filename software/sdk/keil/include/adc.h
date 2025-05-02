
#include "platform_config.h"

//define APB ADC base address
#define	 	 GECKO_APB_ADC_BASE		    							0x40016000
#define 	 REG_GPADC_BASE              						0x40016000

typedef struct
{
  __IO uint32 gain0db;//x1
  __IO uint32 gain6db;//x2
       uint32 gain12db;//x4
  __IO uint32 gain16p8db;//x7
  __IO uint32 gain21p4db;//x12
  __I  uint32 gain26p2db;//x21
	__IO uint32 gain31p2db;//x36
  __IO uint32 gain36db;//x64
} ADCBuf_GainSel;



typedef enum
{
	GECKO_GPADC_CHAN_0=0,
	GECKO_GPADC_CHAN_1=1,
	GECKO_GPADC_CHAN_2=2,
	GECKO_GPADC_CHAN_3=3,
	GECKO_GPADC_CHAN_4=4,
	GECKO_GPADC_CHAN_5=5,	
	GECKO_GPADC_CHAN_6=6,
	GECKO_GPADC_CHAN_7=7,	
	GECKO_GPADC_CHAN_8=8,
	GECKO_GPADC_CHAN_9=9,	
  GECKO_GPADC_CHAN_QTY
} GECKO_GPADC_CHAN_T;


typedef volatile struct
{
    REG32                          ctrl;                         //0x00000000
    REG32                          status;                       //0x00000004
    REG32                          data;                         //0x00000008
    REG32                          data_ch0;                     //0x0000000C
    REG32                          data_ch1;                     //0x00000010
    REG32                          data_ch2;                     //0x00000014
    REG32                          data_ch3;                     //0x00000018	
    REG32                          data_ch4;                     //0x0000001C
    REG32                          data_ch5;                     //0x00000020
    REG32                          data_ch6;                     //0x00000024
    REG32                          data_ch7;                     //0x00000028
	
    REG32                          irq_mask;                     //0x0000002C	
    REG32                          irq_cause;                    //0x00000030	
    REG32                          irq_clr;                      //0x00000034
	
    REG32                          thrshd0;                      //0x00000038
    REG32                          thrshd1;                      //0x0000003C
    REG32                          thrshd2;                      //0x00000040
    REG32                          thrshd3;                      //0x00000044
    REG32                          thrshd4;                      //0x00000048
    REG32                          thrshd5;                      //0x0000004C
    REG32                          thrshd6;                      //0x00000050
    REG32                          thrshd7;                      //0x00000054
//2022-09-04
//ADC Data， Confirm data_ch8 and ch9 DATA register
    REG32                          data_ch8;                     //0x00000058
    REG32                          data_ch9;                     //0x0000005C

} HWP_GPADC_T;

#define hw_gpadc                   ((HWP_GPADC_T*) GECKO_APB_ADC_BASE)


#define 		HWgpadc_reg_read(reg,val)  											  hal_analogif_reg_read(reg,val)
#define 		HWgpadc_reg_write(reg,val) 											  hal_analogif_reg_write(reg,val)



//ctrl
//0x00 register
#define GPADC_CH0_EN                (1<<0)
#define GPADC_CH1_EN                (1<<1)
#define GPADC_CH2_EN                (1<<2)
#define GPADC_CH3_EN                (1<<3)
#define GPADC_CH4_EN                (1<<4)
#define GPADC_CH5_EN                (1<<5)
#define GPADC_CH6_EN                (1<<6)
#define GPADC_CH7_EN                (1<<7)
//add ZJF 2022-09-01
#define GPADC_CH8_EN                (1<<8)
#define GPADC_CH9_EN                (1<<9)


//add Junfeng 20210125
//#define GPADC_START                 (1<<8)//20210210	
//#define ADC_EN                 			((uint32)1<<31)//20220124	Modify for ECO verify

//#define GPADC_CK_DIV<0>						(1<<12)
//#define ADC_EN                 			((uint32)1<<12)//20220201	Modify for ECO
//#define GPADC_START                 (1<<12)//20220214	
//#define ADC_EN                 			((uint32)1<<12)



#define GPADC_CH_INGN(n)            (((n)&0x3)<<10) //00=bypass;01=1/2 input;10=1/4 input
#define GPADC_REF_SEL               (1<<12)
#define GPADC_CK_DIV(n)             (((n)&0x7)<<13)

//#define ADC_EN                 			((uint32)1<<15) //New: 1109 change it to bit15
#define ADC_EN                 			((uint32)1<<16) //New: 1109 change it to bit16 --->2022-09-01
//#define GPADC_DONE



//status
#define GPADC_THRSHD0_IRQ           (1<<0)
#define GPADC_THRSHD1_IRQ           (1<<4)


//#define GPADC_EOC                   (1<<16)//20210210 JunfengZhou
//#define GPADC_BUSY                  (1<<17)

#define GPADC_EOC                   (1<<20)//New:1109 change it to bit20 --->2022-09-01
#define GPADC_BUSY                  (1<<21)//New:1109 change it to bit21 --->2022-09-01



//data
#define GPADC_DATA(n)               (((n)&0xFFF)<<0)


//irq_mask
//#define GPADC_THRSHD0_IRQ         (1<<0)
//#define GPADC_THRSHD1_IRQ         (1<<4)
//#define GPADC_EOC                 (1<<8)

//irq_cause
//#define GPADC_THRSHD0_IRQ         (1<<0)
//#define GPADC_THRSHD1_IRQ         (1<<4)
//#define GPADC_EOC                 (1<<8)

//irq_clr
//#define GPADC_THRSHD0_IRQ         (1<<0)
//#define GPADC_THRSHD1_IRQ         (1<<4)
//#define GPADC_EOC                 (1<<8)

//thrshd
#define GPADC_THRSHD0(n)            (((n)&0xFFF)<<0)
#define GPADC_THRSHD1(n)            (((n)&0xFFF)<<16)



// =============================================================================
// GPADC_BAD_VALUE
// -----------------------------------------------------------------------------
/// Value returned when the gpadc has not finished its convertion.
// =============================================================================
#define GPADC_BAD_VALUE  0xFFFF



// =============================================================================
// GPADC_CHAN_T
// -----------------------------------------------------------------------------
/// Channel selection.
// =============================================================================
typedef enum
{
    GPADC_CHAN_0,//AC_IN
    GPADC_CHAN_1,//VBAT
    GPADC_CHAN_2,//REAR_DET
    GPADC_CHAN_3,//LEAR_DET
    GPADC_CHAN_4,//QI_DET
    GPADC_CHAN_5,//VDD5V
    GPADC_CHAN_6,//TEMP_SEN
    GPADC_CHAN_7,//ISEN_BATT	
    GPADC_CHAN_8,
    GPADC_CHAN_9,		
    GPADC_CHAN_QTY,	
	
} GPADC_CHAN_T;









typedef enum
{
	GECKO_ADC_CHAN_BATTERY=0x01,
	GECKO_ADC_CHAN_CHAN_0,
	GECKO_ADC_CHAN_CHAN_1,
	GECKO_ADC_CHAN_CHAN_2,
	GECKO_ADC_CHAN_CHAN_3,
	GECKO_ADC_CHAN_CHAN_4,	
	GECKO_ADC_CHAN_CHAN_5,	
	GECKO_ADC_CHAN_CHAN_6,
	GECKO_ADC_CHAN_CHAN_7,
	GECKO_ADC_CHAN_CHAN_8,
	GECKO_ADC_CHAN_CHAN_9,	
	GECKO_ADC_BAD_VALUE,
	GECKO_ADC_CHAN_QTY,
} HW_GPADC_CHAN_T;







typedef struct{
	uint8_t ad_channel_select; //ADC通道索引    
	uint16_t advalue_buf[8];   //存放各通道ADC转换后的值	
}AdcTypedef;









void ADC_Init(void);
void Get_Advalue_Func(void);
uint16 GeckoGpadcGetRawData(GPADC_CHAN_T channel);
uint16 Get_Vbat_Voltage(void);






