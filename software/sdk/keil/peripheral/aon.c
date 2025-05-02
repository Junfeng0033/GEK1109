#include "platform_config.h"
#include "gecko1108.h"

#include "aon.h"
#include "../norflash/xtxflash/dpi_common.h"

#include "uart.h"
extern void h2l_wr_busy(void);


extern void manba_task_cpu_goto_sleep(void);

extern void tc_gecko_aon_sanity_cm0(void);//deep sleep
extern void tc_gecko_cm0_aon_sleep(void);

//switch to quad spi nor flash mode
extern void gecko_task_cm0_sw_flash_quad(void);

//SPI-to-AHB config to Dual-wire access NOR Flash
extern void gecko_task_cm0_sw_flash_dual(void);
extern void delay_1us(unsigned int delay_val);


#define ANA_READ_CTLREG(REG)      				(*(volatile unsigned int*)(REG))
#define ANA_WRITE_CTLREG(REG,VAL)    			(*(volatile unsigned int*)(REG)) = (unsigned int)(VAL) 


//uint32 AON_CFG_ANA_CTRL_1_0x20_Default=0x808E7885;
//uint32 AON_CFG_ANA_CTRL_2_0x24_Default=0;
//uint32 AON_CFG_GPIO_WAKEUP_CTRL_0x10_Default=0;





void aon_wakeup_irq_cfg(void)
{
	hal_nvic_clear_pending_irq(AON_IRQn);
	hal_nvic_set_priority(AON_IRQn, 0);
	hal_nvic_enable_irq(AON_IRQn);	
}






void Analog_Ctrl_1_Init(void)
{
	unsigned int wr_data;
	//char *string;	

	//wr_data = reg_read(ADDR_AON_CFG_ANA_CTRL_1);
	wr_data = ANA_READ_CTLREG(ADDR_AON_CFG_ANA_CTRL_1);//0x4001A000+0x20
	wr_data =(*(volatile unsigned int*)(0x4001A020));

	
	//enable ldo
	//wr_data |= (LDO18_EN |EN_OSC32M |LDO1_VSET(3)| LDO1_EN | BG_EN);
	//wr_data |= LDO_FLASH_VSET(3);//VSET<1:0> 00-->3.3V;01-->3.2V;10-->3.4V;11-->3.5V
	//#define LDO_FLASH_VSET(n)        (((n)&0x3)<<3)  //2 bits,(bit3 and bit4)
	wr_data  = wr_data | 0x00000018;//(bit3 and bit4)
  reg_write(ADDR_AON_CFG_ANA_CTRL_1, wr_data);	
  //reg_write(ADDR_AON_CFG_ANA_CTRL_1, (LDO18_EN |EN_OSC32M |LDO1_VSET(3)| LDO1_EN | BG_EN));
	
}




void Analog_Ctrl_2_Init(void)
{
	volatile unsigned int wr_data;
	//char *string;	

  //wr_data=reg_read(ADDR_AON_CFG_ANA_CTRL_2);	
	wr_data = ANA_READ_CTLREG(ADDR_AON_CFG_ANA_CTRL_2);
	wr_data =(*(volatile unsigned int*)(0x4001A024));
	
//	wr_data |= (SW_FORCE_BG_EN |SW_FORCE_LDO18_EN | SW_FORCE_LDO1_EN | SW_FORCE_OSC32M_EN);
//  reg_write(ADDR_AON_CFG_ANA_CTRL_2, wr_data);

	
}



void LDO18_Ctrl(void)
{
	unsigned int wr_data;
	//char *string;	
	
	wr_data=reg_read(ADDR_AON_CFG_ANA_CTRL_2);
	
	//Force bit[1]
	wr_data |= SW_FORCE_LDO18_EN;
	
  reg_write(ADDR_AON_CFG_ANA_CTRL_2, wr_data);	
	
	
	//wr_data = reg_read(ADDR_AON_CFG_ANA_CTRL_1);
	wr_data = ANA_READ_CTLREG(ADDR_AON_CFG_ANA_CTRL_1);//0x4001A000+0x20
	wr_data =(*(volatile unsigned int*)(0x4001A020));

	
	//enable ldo
	//wr_data |= (LDO18_EN |EN_OSC32M |LDO1_VSET(3)| LDO1_EN | BG_EN);
	//wr_data |= LDO_FLASH_VSET(3);//VSET<1:0> 00-->3.3V;01-->3.2V;10-->3.4V;11-->3.5V
	//#define LDO_FLASH_VSET(n)        (((n)&0x3)<<3)  //2 bits,(bit3 and bit4)
	//wr_data  = wr_data | 0x00000018;//(bit3 and bit4)
	wr_data  = wr_data & 0xFFFFFFFE;//(bit0=0,LDO18_EN=0)
  reg_write(ADDR_AON_CFG_ANA_CTRL_1, wr_data);	
  //reg_write(ADDR_AON_CFG_ANA_CTRL_1, (LDO18_EN |EN_OSC32M |LDO1_VSET(3)| LDO1_EN | BG_EN));
	
}



//LDO1
void LDO33_OUT_Ctrl(void)
{
	unsigned int wr_data;
	//char *string;	
	
	wr_data=reg_read(ADDR_AON_CFG_ANA_CTRL_2);
	
	//Force bit[1]
	wr_data |= SW_FORCE_LDO18_EN;
	
  reg_write(ADDR_AON_CFG_ANA_CTRL_2, wr_data);	

	
	//wr_data = reg_read(ADDR_AON_CFG_ANA_CTRL_1);
	wr_data = ANA_READ_CTLREG(ADDR_AON_CFG_ANA_CTRL_1);//0x4001A000+0x20
	wr_data =(*(volatile unsigned int*)(0x4001A020));

	
	//enable ldo
	//wr_data |= (LDO18_EN |EN_OSC32M |LDO1_VSET(3)| LDO1_EN | BG_EN);
	//wr_data |= LDO_FLASH_VSET(3);//VSET<1:0> 00-->3.3V;01-->3.2V;10-->3.4V;11-->3.5V
	//#define LDO_FLASH_VSET(n)        (((n)&0x3)<<3)  //2 bits,(bit3 and bit4)
	//wr_data  = wr_data | 0x00000018;//(bit3 and bit4)
	wr_data  = wr_data & 0xFFFFFFFE;//(bit0=0,LDO18_EN=0)
  reg_write(ADDR_AON_CFG_ANA_CTRL_1, wr_data);	
  //reg_write(ADDR_AON_CFG_ANA_CTRL_1, (LDO18_EN |EN_OSC32M |LDO1_VSET(3)| LDO1_EN | BG_EN));
}



//wr_data = 0x848E7885;//0x808E7885
void PWR_MOS_Gate_CTRL(uint8 gate)
{
	unsigned int wr_data;
	wr_data=reg_read(ADDR_AON_CFG_ANA_CTRL_1);
	
	//bit13,bit14
	wr_data |= PWRMOS_G(gate);
	//3:GATE0 and GATE1 equal to "1" at the same time
	//2:GATE0 equal to "1" and GATE1 equal to "0"
	//1:GATE0 equal to "0" and GATE1 equal to "1"
	//0:GATE0 and GATE1 equal to "0" at the same time
	if(gate==3)//MOS-S0 connected to MOS -D0
	{
		wr_data |= 0x00006000;//bit13,bit14 =1
		//UATR0_PRINT_LOG((unsigned char *)("(gate==3)-PWR_MOS_Gate_CTRL"));
	}
	else if(gate==0)//MOS-S0 disconnected to MOS -D0
	{
		wr_data &= 0xffff9fff;//bit13,bit14 =0
    //UATR0_PRINT_LOG((unsigned char *)("(gate==0)-PWR_MOS_Gate_CTRL"));		
	}
	
  reg_write(ADDR_AON_CFG_ANA_CTRL_1, wr_data);	
	
}







/*
aon_regfile.v
ADDR_REG_0X028 : rdata_comb={17'h0,reg_aon_pwrmos_g,2h'0,reg_aon_ldo_aux_vset,1'h0,reg_aon_ldo_aux_en,reg_aon_op2_en,reg_aon_op1_en,reg_aon_opa_pga2,reg_aon_opa_pga1}
*/
#define GEK1109_OPA1_PGA(n)      (((n)&0x3)<<0)  //2 bits
#define GEK1109_OPA2_PGA(n)      (((n)&0x3)<<2)  //2 bits
#define GEK1109_OPA1_EN          (1<<4)
#define GEK1109_OPA2_EN          (1<<5)
#define GEK1109_LDO_AUX_EN       (1<<6)
//bit7 reserved
#define GEK1109_LDO_AUX_VSET(n)  (((n)&0x3)<<8)  //2 bits
//bit10 reserved 
//bit11 reserved 
#define GEK1109_MOS_GATE(n)      (((n)&0x7)<<12)  //GEK1109 3-bit MOS Gate [14:12]



/*
aon_regfile.v
ADDR_REG_0X090 : rdata_comb=reg_0x090
*/

#define GEK1109_OPA2_CMP_SEL          (1<<0)
#define GEK1109_OPA1_CMP_SEL          (1<<1)
#define GEK1109_LDO2_EN          			(1<<2)
#define GEK1109_LDO2_VSET(n)      		(((n)&0x3)<<3)  //2 bits
#define GEK1109_LDO_FLS_EN            (1<<5)
#define GEK1109_LDO_FLS_BYPASS        (1<<6)




volatile uint8 ctrl_flag=0;

void GEK1109_MOS_Gate_CTRL(void)
{
	  unsigned int wr_data,wr_data_0x090,wr_data_0x080,wr_data_0x08c,wr_data_0x088;
		wr_data=reg_read(GECKO_AON_BASE_ADDR+0x028);
	
	  wr_data_0x080=reg_read(GECKO_AON_BASE_ADDR+0x080);//ana_sel
	  wr_data_0x088=reg_read(GECKO_AON_BASE_ADDR+0x088);//pull up
	  wr_data_0x08c=reg_read(GECKO_AON_BASE_ADDR+0x08C);//pull down
	
		wr_data_0x090=reg_read(GECKO_AON_BASE_ADDR+0x090);
	
		if(ctrl_flag)
		{	
			ctrl_flag=0;
			wr_data=GEK1109_MOS_GATE(0);
			
			wr_data &=(~GEK1109_OPA1_EN);
			wr_data &=(~GEK1109_OPA2_EN);
			wr_data &=(~GEK1109_LDO_AUX_EN);
			
			wr_data_0x080 &=0x000000;//ana_sel
			
			wr_data_0x088 &=0x000000;
			wr_data_0x08c &=0x000000;
			
			wr_data_0x090 &=(~GEK1109_OPA2_CMP_SEL);
			wr_data_0x090 &=(~GEK1109_OPA1_CMP_SEL);
			wr_data_0x090 &=(~GEK1109_LDO2_EN);			
			wr_data_0x090 &=(~GEK1109_LDO_FLS_EN);		
		}
		else
		{
			ctrl_flag=1;
			wr_data=GEK1109_MOS_GATE(7);

			wr_data |=(GEK1109_OPA1_EN);
			wr_data |=(GEK1109_OPA2_EN);
			wr_data |=(GEK1109_LDO_AUX_EN);
			
			wr_data_0x080 |=0xFFFFFF;//ana_sel
			wr_data_0x088 |=0xFFFFFF;
			wr_data_0x08c |=0xFFFFFF;	

			wr_data_0x090 |=(GEK1109_OPA2_CMP_SEL);
			wr_data_0x090 |=(GEK1109_OPA1_CMP_SEL);
			wr_data_0x090 |=(GEK1109_LDO2_EN);			
			wr_data_0x090 |=(GEK1109_LDO_FLS_EN);			
			
		}
	  reg_write(GECKO_AON_BASE_ADDR+0x028, wr_data);
		
		reg_write(GECKO_AON_BASE_ADDR+0x080, wr_data_0x080);//ana_sel
	  reg_write(GECKO_AON_BASE_ADDR+0x088, wr_data_0x088);
	  reg_write(GECKO_AON_BASE_ADDR+0x08C, wr_data_0x08c);
	  reg_write(GECKO_AON_BASE_ADDR+0x090, wr_data_0x090);			
}




/*
//GPIO_WAKEUP
//register 0x10
#define GPIO_WAKEUP_EN_00                 (1<<0)						//PAD08
#define GPIO_WAKEUP_EN_01                 (1<<1)						//PAD09
#define GPIO_WAKEUP_EN_02                 (1<<2)						//PAD10
#define GPIO_WAKEUP_EN_03                 (1<<3)						//PAD11
#define GPIO_WAKEUP_EN_04                 (1<<4)						//PAD12
#define GPIO_WAKEUP_EN_05                 (1<<5)						//PAD13
#define GPIO_WAKEUP_EN_06                 (1<<6)						//PAD14
#define GPIO_WAKEUP_EN_07                 (1<<7)						//PAD15
#define GPIO_WAKEUP_EN_08                 (1<<8)						//PAD16
#define GPIO_WAKEUP_EN_09                 (1<<9)						//PAD17
#define GPIO_WAKEUP_EN_10                 (1<<10)						//PAD18
#define GPIO_WAKEUP_EN_11                 (1<<11)						//PAD19
*/


/*
`ifdef GECKO_MACRO_TC_PIN_WAKEUP_DS
initial begin
    wait (`AON_TOP.u_aon_ctrl.ena_deepsleep_lpclk==1'b1);
    force `AON_TOP.u_aon_status_sync.reg_aon_gpio_wakeup_ena_03 = 1'b1;
    wait (`AON_TOP.u_aon_ctrl.sys_is_in_sleep==1'b1);
    $display("[TC Message] [GECKO_MACRO_TC_PIN_WAKEUP_DS] Use PAD_11 (GPIO, default SPI CSN input) to wake-up DeepSleep.");
    #200us;
    force tbench.PAD_11 = 1'b0;
    #1us;
    force tbench.PAD_11 = 1'b1;
    #1us;
    release tbench.PAD_11;
    wait (`DIG_CORE.sys_hwrite_cortexm0==1'b1);
    #10us;
    $display("[TC Message] [GECKO_MACRO_TC_PIN_WAKEUP_DS] GPIO wake-up DeepSleep is test done.");
    $finish;
end
`endif
*/


void GPIO_WakeUp_Setting(void)
{
	unsigned int wr_data;
  wr_data=reg_read(ADDR_AON_CFG_GPIO_WAKEUP_CTRL);
	
//	wr_data |= (GPIO_WAKEUP_EN_00 |GPIO_WAKEUP_EN_01 |GPIO_WAKEUP_EN_02| GPIO_WAKEUP_EN_03);
	wr_data |= (GPIO_WAKEUP_EN_01);
  reg_write(ADDR_AON_CFG_GPIO_WAKEUP_CTRL, wr_data);

}



//kevin@20230725
void GEK1109_GPIO_WakeUp_From_DeepSleep(void)
{
	unsigned int wr_data;
	
	wr_data=reg_read(GECKO_AON_BASE_ADDR+0x00C);//test reg_0x00C read and write
	wr_data = 0xC08;
	h2l_wr_busy();
  reg_write(GECKO_AON_BASE_ADDR+0x00C, wr_data);//

  wr_data=reg_read(GECKO_AON_BASE_ADDR+0x004);
	wr_data |= 0x1;//aon_ena_wakeup_int
	h2l_wr_busy();
	reg_write(GECKO_AON_BASE_ADDR+0x004, wr_data);

  wr_data=reg_read(GECKO_AON_BASE_ADDR+0x010);
	
	wr_data |= GPIOA4_WAKEUP_EN_00;
	wr_data |= GPIOA5_WAKEUP_EN_01;
	wr_data |= GPIOA6_WAKEUP_EN_02;
	wr_data |= GPIOA7_WAKEUP_EN_03;

	wr_data |= GPIOB0_WAKEUP_EN_04;
	wr_data |= GPIOB1_WAKEUP_EN_05;
	wr_data |= GPIOB2_WAKEUP_EN_06;
	wr_data |= GPIOB3_WAKEUP_EN_07;

	wr_data |= GPIOB4_WAKEUP_EN_08;
	wr_data |= GPIOB5_WAKEUP_EN_09;
	wr_data |= GPIOB6_WAKEUP_EN_10;
	wr_data |= GPIOB7_WAKEUP_EN_11;		
	
	h2l_wr_busy();
	reg_write(GECKO_AON_BASE_ADDR+0x010, wr_data);	


  wr_data=reg_read(GECKO_AON_BASE_ADDR+0x018);
	wr_data |= 0xFFF;
	h2l_wr_busy();
	reg_write(GECKO_AON_BASE_ADDR+0x018, wr_data);	
	
}




/*
GEK1109 register 

assign reg_aon_pad_pullup		=reg_0x88[23:0]
assign reg_aon_pad_pulldn		=reg_0x8C[23:0]

*/

void GEK1109_PAD_pullup_pulldown_Config(void)
{
	  unsigned int wr_data;
		wr_data=reg_read(GECKO_AON_BASE_ADDR+0x088);//pull up
	  wr_data |=0xFFFFFF;
	  reg_write(GECKO_AON_BASE_ADDR+0x088, wr_data);
	
		wr_data=reg_read(GECKO_AON_BASE_ADDR+0x088);
	  wr_data &=0x000000;
	  reg_write(GECKO_AON_BASE_ADDR+0x088, wr_data);
	
///////////////////////////////////////////////////////////////////
	
		wr_data=reg_read(GECKO_AON_BASE_ADDR+0x08C);//pull down
	  wr_data &=0x000000;
	  reg_write(GECKO_AON_BASE_ADDR+0x08C, wr_data);
	

		wr_data=reg_read(GECKO_AON_BASE_ADDR+0x08C);
	  wr_data |=0xFFFFFF;
	  reg_write(GECKO_AON_BASE_ADDR+0x08C, wr_data);
	
}





/*
uint32 AON_CFG_ANA_CTRL_1_0x20_Default=0x808E7885;//
//ANA_CTRL_1
//register 0x20

#define LDO18_EN                 (1<<0)
#define LDO18_VSET(n)            (((n)&0x3)<<1)  //2 bits
#define LDO_FLASH_VSET(n)        (((n)&0x3)<<3)  //2 bits
#define LPBG_VTRIM(n)            (((n)&0x7)<<5)  //3 bits
#define RCO32K_FC(n)						 (((n)&0xF)<<8)  //4 bits

#define EN_OSC32M                (1<<12)

#define PWRMOS_G(n)              (((n)&0x3)<<13)  //2 bits Power PMOS Gate
#define LDO1_VSET(n)             (((n)&0x3)<<15)  //2 bits
#define LDO1_EN                  (1<<17)
#define BG_EN                    (1<<18)
#define RCO32M_EN_16M            (1<<19)
#define RCO32M_TC(n)						 (((n)&0xF)<<20)  //4 bits
#define RCO32M_FREQ(n)					 (((n)&0xFF)<<24) //8 bits
*/

//uint32 AON_CFG_ANA_CTRL_1_0x20_Default=0x808E7885;//
//0xA0,4.065MHz
//0x90,3.7736MHz(uart ok)


/*
void Osc32M_Freq_Trimming_1(void)
{
	unsigned int wr_data;
	//char *string;	

	wr_data=reg_read(ADDR_AON_CFG_ANA_CTRL_2);
	
	//Force bit[4] to use SW config OSC frequency
	wr_data |= SW_FORCE_CALI32M_TUNE;
	
  reg_write(ADDR_AON_CFG_ANA_CTRL_2, wr_data);	


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
	
	wr_data=reg_read(ADDR_AON_CFG_ANA_CTRL_1);

	//wr_data |= RCO32M_FREQ(0xff);//max
//1@1 board
  wr_data = 0x8A8E7885;//0x808E7885

//  wr_data = 0x908E7885;//0x808E7885
//0xA0,4.065MHz
//0x90,3.7736MHz(uart ok)	
  reg_write(ADDR_AON_CFG_ANA_CTRL_1, wr_data);
	
	
}
*/




void Osc32M_Freq_Trimming(void)
{
	unsigned int wr_data;
	volatile unsigned long adr;
	//char *string;	
//	wr_data=reg_read(OFFSET_REG_AON_AON_FSM_CTRL);
//	wr_data=reg_read(OFFSET_REG_AON_AON_STATUS);	
//	wr_data=reg_read(OFFSET_REG_AON_AON_SLEEP_CNT);

//	wr_data=reg_read(OFFSET_REG_AON_AON_SLEEP_CNT_RBK);
//	wr_data=reg_read(OFFSET_REG_AON_GPIO_WAKEUP);	
//	
//	wr_data=reg_read(OFFSET_REG_AON_ANA_CTRL_1);
//	wr_data=reg_read(OFFSET_REG_AON_ANA_CTRL_2);	
//	
//	wr_data=reg_read(OFFSET_REG_AON_RSV_ANA_CTRL);	
//	wr_data=reg_read(OFFSET_REG_AON_RSV_DIG_CTRL_1);
//	wr_data=reg_read(OFFSET_REG_AON_RSV_DIG_CTRL_2);		
	
//	adr=0x3F000;
//	status=pEnterCriticalSection(); 
//	hj_ahb_rd_data=QSPI_NorFlash_ReadWord(adr);
//	pExitCriticalSection(status);	
	
	wr_data=reg_read(ADDR_AON_CFG_ANA_CTRL_2);

	
	//Force bit[4] to use SW config OSC frequency
//	wr_data |= SW_FORCE_CALI32M_TUNE | SW_FORCE_LDO1_EN;//change LDO33_OUT and LDO33_FLASH_OUT to 3.5V//2022-08-19 ZJF
	wr_data |= SW_FORCE_CALI32M_TUNE;	
	
  reg_write(ADDR_AON_CFG_ANA_CTRL_2, wr_data);	

	
	wr_data=reg_read(ADDR_AON_CFG_ANA_CTRL_1);

	
	//wr_data |= RCO32M_FREQ(0xff);//max
//1@1 board
  wr_data = 0x8A8E7885;//0x808E7885
  wr_data = 0x938E7885;//0x808E7885 chip-1
  wr_data = 0x8B8E7885;//0x808E7885 chip-2	

//#define LDO1_VSET(n)             (((n)&0x3)<<15)  //2 bits,2b'00,3.3V;2b'01,3.2V;2b'10,3.4V;2b'11,3.5V;
//#define LDO_FLASH_VSET(n)        (((n)&0x3)<<3)  //2 bits,//VSET<1:0> 00-->3.3V;01-->3.2V;10-->3.4V;11-->3.5V

//  wr_data = 0x8B8FF89D;////change LDO33_OUT and LDO33_FLASH_OUT to 3.5V	
//  wr_data = 0x8B8FF885;////change LDO33_OUT(LDO1) to 3.5V
  wr_data = 0x8B8E789D;////change LDO33_FLASH_OUT to 3.5V

/*
volatile unsigned int ahb_rd_data;// global variable
volatile unsigned long adr;
adr=0x3F000;
ahb_rd_data=QSPI_NorFlash_ReadWord(adr);


//写入高8位calibration值
wr_data= wr_data&0x00FFFFFF;
ahb_rd_data= ahb_rd_data&0xFF000000;
wr_data= wr_data| ahb_rd_data;

*/


//0xA0,4.065MHz
//0x90,3.7736MHz(uart ok)	
//	wr_data = 0xcc86789D;	//2024-09-14 @shanghai change bit19=0 24.2MH2@3.3V

  wr_data = 0xD886789D;//PCLK_OUT=2.4MHZ
	
  //wr_data = 0x9D86789D;//20MHZ
  //wr_data = 0x6F86789D;//16MHZ

  //wr_data = 0x7B8E789D;//2024-09-14 @Shanghai  8.5MHZ
	
	//wr_data = 0x708E789D;//2024-09-14 @Shanghai  8MHZ
	reg_write(ADDR_AON_CFG_ANA_CTRL_1, wr_data);
	
}








void GEK_Retention_Reg_Access(void)
{
	volatile unsigned int aon_data;
	reg_write(ADDR_AON_RETENTION_REG_0, 0x12345678);
	reg_write(ADDR_AON_RETENTION_REG_1, 0xA55ACAFE);
	reg_write(ADDR_AON_RETENTION_REG_2, 0xABCD5678);
	reg_write(ADDR_AON_RETENTION_REG_3, 0xA55AABCD);

//	reg_write(ADDR_AON_RETENTION_REG_4, 0x12345678);
//	reg_write(ADDR_AON_RETENTION_REG_5, 0xA55ACAFE);
//	reg_write(ADDR_AON_RETENTION_REG_6, 0xABCD5678);
//	reg_write(ADDR_AON_RETENTION_REG_7, 0xA55AABCD);	
	
	aon_data=reg_read(ADDR_AON_RETENTION_REG_0);
	aon_data=reg_read(ADDR_AON_RETENTION_REG_1);
	aon_data=reg_read(ADDR_AON_RETENTION_REG_2);
	aon_data=reg_read(ADDR_AON_RETENTION_REG_3);	
	
//	aon_data=reg_read(ADDR_AON_RETENTION_REG_4);
//	aon_data=reg_read(ADDR_AON_RETENTION_REG_5);
//	aon_data=reg_read(ADDR_AON_RETENTION_REG_6);
//	aon_data=reg_read(ADDR_AON_RETENTION_REG_7);		

}





/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


/*
"GEK1109 added a AON clock divded-by-2 MUX
0: 32kHz clock (default)
1: 16kHz clock"

*/
void gecko_rootnode_clk32k_cfg(void)
{
	//AON Register,Offset Addr 0x0
	unsigned int wr_data;
	//sel_aon_clk16k
	wr_data=reg_read(ADDR_AON_CFG_AON_FSM_CTRL);
	wr_data |= SEL_AON_CLK16K;
	reg_write(ADDR_AON_CFG_AON_FSM_CTRL, wr_data);	
	wr_data=reg_read(ADDR_AON_CFG_AON_FSM_CTRL);
	delay_1us(15);
	wr_data &= (~SEL_AON_CLK16K);	
	reg_write(ADDR_AON_CFG_AON_FSM_CTRL, wr_data);
}


/*
digital root node clock(Oscillator CLK input)

"GEK1109 added a AON register
Default 2'b01: 1/2 of OSC - 16MHz"

*/

void gecko_rootnode_osc32mclk_cfg(void)
{
	//AON Register,Offset Addr 0x70
	unsigned int wr_data;
	//aon2cmu_clk_div
	wr_data=reg_read(ADDR_AON_CFG_CTRL_EXT0);//aon2cmu_clk_div
	wr_data=aon2cmu_clk_div(1);
	reg_write(ADDR_AON_CFG_CTRL_EXT0, wr_data);	
	wr_data=reg_read(ADDR_AON_CFG_CTRL_EXT0);
	delay_1us(2);
	wr_data=aon2cmu_clk_div(2);
	reg_write(ADDR_AON_CFG_CTRL_EXT0, wr_data);	
	wr_data=reg_read(ADDR_AON_CFG_CTRL_EXT0);
	delay_1us(2);
	wr_data=aon2cmu_clk_div(3);
	reg_write(ADDR_AON_CFG_CTRL_EXT0, wr_data);	
	wr_data=reg_read(ADDR_AON_CFG_CTRL_EXT0);//aon2cmu_clk_div
	delay_1us(2);
	
	wr_data=aon2cmu_clk_div(1);
	reg_write(ADDR_AON_CFG_CTRL_EXT0, wr_data);		
}








void gek1109_adc_0_1_analog_port(void)
{
	
		unsigned int wr_data;
		reg_write(GECKO_AON_BASE_ADDR+0x080, 0x0);//reg_aon_ana0_sel
		//reg_write(GECKO_AON_BASE_ADDR+0x084, 0x0);//reg_aon_ana0_sel

	  //set PAD as analog function
	  //CK32K_OUT  <------> reg_aon_ana0_sel[11]
	  wr_data=reg_read(GECKO_AON_BASE_ADDR+0x080);
	  wr_data |= 0x300;//bit8 and bit9 (PAD8 and PAD9 as ADC function)
	  reg_write(GECKO_AON_BASE_ADDR+0x080, wr_data);		
}



void gek1109_adc_8_9_analog_port(void)
{
	
		unsigned int wr_data;
		reg_write(GECKO_AON_BASE_ADDR+0x080, 0x0);//reg_aon_ana0_sel
		//reg_write(GECKO_AON_BASE_ADDR+0x084, 0x0);//reg_aon_ana0_sel

	  //set PAD as analog function
	  //CK32K_OUT  <------> reg_aon_ana0_sel[11]
	  wr_data=reg_read(GECKO_AON_BASE_ADDR+0x080);
	  wr_data |= 0x300000;//bit20 and bit21 (PAD20 and PAD21 as ADC function)
	  reg_write(GECKO_AON_BASE_ADDR+0x080, wr_data);		
}


