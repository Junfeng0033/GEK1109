//=================================================
// GEK1108 PMOS Control
//
//==================================================

#include "platform_config.h"

#include "aon.h"


//There is a bug in AON register reading
//#define PWRMOS_G(n)              (((n)&0x3)<<13)  //2 bits Power PMOS Gate



//MOSFET switch Test
//PWR_MOS_Gate_CTRL(0);
//PWR_MOS_Gate_CTRL(3);



#if 0

void PWR_MOS_Gate_CTRL(uint8 gate)
{
	unsigned int wr_data,wr_data_tmp;
	wr_data=reg_read(ADDR_AON_CFG_ANA_CTRL_1);
  wr_data = AON_CFG_ANA_CTRL_1_0x20_Default;////There is a bug in AON register reading

	#if DEBUG_UATR0_PRINT_LOG	
  char *string;		

	UATR0_PRINT_LOG((unsigned char *)("\r\n"));						
	UATR0_PRINT_LOG((unsigned char *)("111-PWR_MOS_Gate_CTRL"));
	
  wr_data_tmp=wr_data>>16;
	UATR0_PRINT_LOG((unsigned char *)("\r\n"));						
	UATR0_PRINT_LOG((unsigned char *)("AON_CFG_ANA_CTRL_1_0x20_Default High 16bit --- = 0x"));
	string=my_itoa(wr_data_tmp);
	UATR0_PRINT_LOG((unsigned char *)(string));
	UATR0_PRINT_LOG((unsigned char *)("\r\n"));


  wr_data_tmp=wr_data & 0x0000ffff;
	UATR0_PRINT_LOG((unsigned char *)("\r\n"));						
	UATR0_PRINT_LOG((unsigned char *)("AON_CFG_ANA_CTRL_1_0x20_Default Low 16bit --- = 0x"));
	string=my_itoa(wr_data_tmp);
	UATR0_PRINT_LOG((unsigned char *)(string));
	UATR0_PRINT_LOG((unsigned char *)("\r\n"));
	
  #endif
	
	//bit13,bit14
	wr_data |= PWRMOS_G(gate);
	//3:GATE0 and GATE1 equal to "1" at the same time
	//2:GATE0 equal to "1" and GATE1 equal to "0"
	//1:GATE0 equal to "0" and GATE1 equal to "1"
	//0:GATE0 and GATE1 equal to "0" at the same time
	if(gate==3)//MOS-S0 connected to MOS -D0
	{
		wr_data |= 0x00006000;//bit13,bit14 =1
		UATR0_PRINT_LOG((unsigned char *)("(gate==3)-PWR_MOS_Gate_CTRL"));
	}
	else if(gate==0)//MOS-S0 disconnected to MOS -D0
	{
		wr_data &= 0xffff9fff;//bit13,bit14 =0
    UATR0_PRINT_LOG((unsigned char *)("(gate==0)-PWR_MOS_Gate_CTRL"));		
	}
	
  reg_write(ADDR_AON_CFG_ANA_CTRL_1, wr_data);	
	AON_CFG_ANA_CTRL_1_0x20_Default=wr_data;
	
	#if DEBUG_UATR0_PRINT_LOG	
	UATR0_PRINT_LOG((unsigned char *)("\r\n"));						
	UATR0_PRINT_LOG((unsigned char *)("222-PWR_MOS_Gate_CTRL"));
	
  wr_data_tmp=wr_data>>16;
	UATR0_PRINT_LOG((unsigned char *)("\r\n"));						
	UATR0_PRINT_LOG((unsigned char *)("AON_CFG_ANA_CTRL_1_0x20_Default High 16bit --- = 0x"));
	string=my_itoa(wr_data_tmp);
	UATR0_PRINT_LOG((unsigned char *)(string));
	UATR0_PRINT_LOG((unsigned char *)("\r\n"));


  wr_data_tmp=wr_data & 0x0000ffff;
	UATR0_PRINT_LOG((unsigned char *)("\r\n"));						
	UATR0_PRINT_LOG((unsigned char *)("AON_CFG_ANA_CTRL_1_0x20_Default Low 16bit --- = 0x"));
	string=my_itoa(wr_data_tmp);
	UATR0_PRINT_LOG((unsigned char *)(string));
	UATR0_PRINT_LOG((unsigned char *)("\r\n"));		
  #endif
	
}

#endif

