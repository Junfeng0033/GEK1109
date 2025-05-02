/******************************************************************************************************************
Calibration fuses:
BLK3_PART_RESERVE      BLOCK3 partially served for ADC calibration data  = 0 R/W (0x0)
ADC_VREF               Voltage reference calibration                     = 1093 R/W (0x11)

EFUSE block 0:
00000000 c40042xx xxxxxxxx 00000000 00000033 00000000 00000000
EFUSE block 1:
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
EFUSE block 2:
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
EFUSE block 3:
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000

//32*8 bit  8 blocks, 32bit per block

******************************************************************************************************************/

#include "platform_config.h"
#include "gecko1108.h"

#include "iomux.h"





volatile uint32 efuse_data_buf;

#define  			GECKO_APB_EFFUSE_ADDR								0X40015000

typedef struct
{
    uint8 clk32k_calib;
    uint8 osc_calib;                 
    uint8 adc_calib[8];               /* adc calibration data for 8 channel     */
    uint8 product_id;
} st_EFUSE_config;

st_EFUSE_config 		g_efuse_cfg;

//#define GECKO1108_EFUSE          ((st_EFUSE_config  *) GECKO_APB_EFFUSE_ADDR   )


//#define  			GECKO_APB_EFFUSE_ADDR								0x40015000

#define EFUSE_CTRL_BASE              0x40015000

#define EFUSE_APB_RW_CFG          *((volatile uint32_t *)(EFUSE_CTRL_BASE + 0x00))
#define EFUSE_APB_RW_ADDR         *((volatile uint32_t *)(EFUSE_CTRL_BASE + 0x04))
#define EFUSE_APB_BIT_DATA        *((volatile uint32_t *)(EFUSE_CTRL_BASE + 0x08))
	
#define EFUSE_APB_TIMING          *((volatile uint32_t *)(EFUSE_CTRL_BASE + 0x10))


/*
 * reg32_00 Register bits
 */

#define 				EFUSE_APB_RD_TRIGGER               			0
#define 				EFUSE_APB_WR_TRIGGER		                1

/*
* reg32_04 Register ,EFUSE_APB_RW_ADDR[31:0]
*/
//from 0 to 31
#define EFUSE_ADDR(bit)											(1 << bit)

/*
 * reg32_08 Register bits
 */

#define 				EFUSE_APB_RD_DATA               			0
#define 				EFUSE_APB_RD_FINISH		                1
#define 				EFUSE_APB_WR_FINISH		                2








void gecko_efuse_read(void) {
    efuse_data_buf = 0; // Initialize the data buffer	
    //SYS_HW32_REG_WR(0x310,0x0);	
    for (uint32_t bit_pos = 0; bit_pos < 32; bit_pos++) {
        int timeout = 0;		
        // Set the bit address to be read (directly use the address value from 0 - 31)			
        //EFUSE_APB_RW_ADDR = bit_pos;
			  EFUSE_APB_RW_ADDR = (1<<bit_pos);

        // Trigger the read operation
        EFUSE_APB_RW_CFG = (1 << EFUSE_APB_RD_TRIGGER);

        // Wait for the read to complete or timeout
        while (!(EFUSE_APB_BIT_DATA & (1 << EFUSE_APB_RD_FINISH))) {
            if (timeout++ > 450) {
                // Optional: Add timeout error handling
                return;
            }
        }
        // Extract the bit value and splice it into the buffer
        //if (EFUSE_APB_BIT_DATA & (1 << EFUSE_APB_RD_DATA)) 
				if (EFUSE_APB_BIT_DATA & 0x1) 
				{
            efuse_data_buf |= (1u << bit_pos); // Set the bit according to the bit position
        }
    }		
		//SYS_HW32_REG_WR(0x310,efuse_data_buf);//test new register for storing efuse value
}










//for 32M_Freq<7:0>
void gecko_read_efuse_rcosc32m_FREQ(void)
{
		

}



//for 32M_TC<3:0>
void gecko_read_efuse_rcosc32m_TC(void)
{
		//uint8 i;
		volatile uint8 osc_tc_field;
	
		osc_tc_field=(uint8)efuse_data_buf;			
		//set_osc_tc_calibration();//i2c timming
}








#if 0

/*
    read one efuse byte
    param-addr: efuse addr, from 0x000 to 0x1FF
*/
uint8_t duet_efuse_byte_read(uint16_t addr)
{
    EFUSE->B_ADDR = addr;
    EFUSE->CFG_TYPE = 0x0;//read type

    EFUSE->START = 0x1;
    while(EFUSE->START & 0x1);
    return EFUSE->RDBK_DATA;
}

/*
    read one efuse word
    param-addr: efuse addr, from 0x000 to 0x1FC
*/
uint32_t duet_efuse_word_read(uint16_t addr)
{
    uint32_t rd_word_data = 0;
    uint8_t rd_byte_data = 0;
    for(int i = 0; i < 4; i++)
    {
        rd_byte_data = duet_efuse_byte_read(addr+i);
        rd_word_data |= rd_byte_data << (i<<3);
    }
    return rd_word_data;
}

/*
    program one efuse byte
    param-addr: efuse addr, from 0x000 to 0x1FF
    param-data: data to be written
*/
void duet_efuse_byte_write(uint16_t addr, uint8_t data)
{
    EFUSE->PGM_DATA = data;
    EFUSE->B_ADDR = addr;
    EFUSE->CFG_TYPE = 0x1;//program type
    EFUSE->WR_TYPE = 0x0;//write type: byte
    EFUSE->START = 0x1;
    while(EFUSE->START & 0x1);
}

/*
    program one efuse word
    param-addr: efuse addr, from 0x000 to 0x1FC
    param-data: data to be written
*/
void duet_efuse_word_write(uint16_t addr, uint32_t data)
{
    EFUSE->PGM_DATA = data;
    EFUSE->B_ADDR = addr;
    EFUSE->CFG_TYPE = 0x1;//program type
    EFUSE->WR_TYPE = 0x1;//write type: word
    EFUSE->START = 0x1;
    while(EFUSE->START & 0x1);
}

#endif



//void Boot_Efuse_Read(uint8 *efuse_cfg)
void Boot_Efuse_Read(st_EFUSE_config *efuse_cfg)
{
	
// boot_efuse_read((UINT8*)&g_boot_efuse_cfg, BOOT_EFUSE_START_ADDR, sizeof(g_boot_efuse_cfg)) == 0

}





void ROM_SystemInit(void)
{
  	//uint8 g_boot_efuse_cfg;
		Boot_Efuse_Read(&g_efuse_cfg); //read efuse for booting software 

		g_efuse_cfg.clk32k_calib = 0x01;			///dbgCtrl &0xff;
    g_efuse_cfg.osc_calib = 0x02;					////(dbgCtrl>>8)&0xff;
    g_efuse_cfg.product_id = 0x58;			////(dbgCtrl>>16)&0xff;	
  
}











