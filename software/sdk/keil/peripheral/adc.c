#include "platform_config.h"
#include "gecko1108.h"
#include "adc.h"
#include "uart.h"
/****************************************************************************
//
//PIN MAP
//
//ch_0				adc channel_0						AC_IN
//ch_1				adc channel_1						VBAT
//ch_2				adc channel_2						REAR_DET
//ch_3				adc channel_3						LEAE_DET
//ch_4				adc channel_4						QI_DET(QI_5VOUT)
//ch_5				adc channel_5						VDD5V(boost_5v_output)
//ch_6				adc channel_6						TEMP_SEN
//ch_7				adc channel_7						ISEN_BATT
//ch_8
//ch_9
****************************************************************************/
/*
*
*
*ADC_CLKIN
*
*
****************************************************************************/

//#define ADC_12BIT_RANGE             0xFFF

AdcTypedef adcstruct;

//voltage = data * 3.3f / 4096.0f;

//ADC Calibration

//__IO uint16_t VREF_BG_CAL=0;
//VREF_BG_CAL=*(__IO uint16_t *)(0x1FF80078);//1.2V adc value


//store 3 groups calibration value:
//0v---------0xXXXX XXXX address
//1.2v-------0x1FF80078  address
//3.0v-------0xXXXX XXXX address






void adc_delay_us(float dly1us)
{
	volatile uint32 jj=0;
	//for(ii=0;ii<units_of_u_secs;ii++)
	while(dly1us--)
	{
		jj++;
	}
	
	jj=0;
	
}






void ADC_Init(void)
{

	hw_gpadc->ctrl = GPADC_CH0_EN;//enable channel 0, the first channel
	adcstruct.ad_channel_select = 0;
	hw_gpadc->ctrl |= ADC_EN; //bit12 ADC_EN=1
	//hw_gpadc->ctrl = 0;//add 2022-2-16
	
	hw_gpadc->ctrl &= ~GPADC_REF_SEL;//0:1.2V reference;1:3.3V reference
}




void Get_Advalue_Func(void)
{
#if 1//def DEBUG_EN	
	//char *string;	
#endif	
	if((hw_gpadc->status & GPADC_EOC))   //转换完成标记
	{
		switch(adcstruct.ad_channel_select)
		{
			case 0:
					adcstruct.advalue_buf[0] = hw_gpadc->data_ch0;
			    hw_gpadc->ctrl = GPADC_CH1_EN;
					adcstruct.ad_channel_select = 1;
				break;
			
			case 1:
					adcstruct.advalue_buf[1] = hw_gpadc->data_ch1;
					hw_gpadc->ctrl = GPADC_CH2_EN;
					adcstruct.ad_channel_select = 2;
				break;
			
			case 2:
					adcstruct.advalue_buf[2] = hw_gpadc->data_ch2;
					hw_gpadc->ctrl = GPADC_CH3_EN;
					adcstruct.ad_channel_select = 3;

				break;
			
			case 3:
					adcstruct.advalue_buf[3] = hw_gpadc->data_ch3;
					hw_gpadc->ctrl = GPADC_CH4_EN;
					adcstruct.ad_channel_select = 4;

				break;
			
			case 4:
					adcstruct.advalue_buf[4] = hw_gpadc->data_ch4;
					hw_gpadc->ctrl = GPADC_CH5_EN;
			    //channel 5 ---> VDD5V detect
					hw_gpadc->ctrl |= GPADC_REF_SEL;//0:1.2V reference;1:3.3V reference
					adcstruct.ad_channel_select = 5;
				break;
			
			case 5:
					adcstruct.advalue_buf[5] = hw_gpadc->data_ch5;
			
					#if 0//DEBUG_UATR0_PRINT_LOG						
					UATR0_PRINT_LOG((unsigned char *)("ADC GPADC_CHAN_2 --- data_ch2 data:"));
					string=my_itoa(hw_gpadc->data_ch5);
					UATR0_PRINT_LOG((unsigned char *)(string));
					UATR0_PRINT_LOG((unsigned char *)("\r\n"));	
					#endif					
			
					hw_gpadc->ctrl = GPADC_CH6_EN;
					adcstruct.ad_channel_select = 6;
			
			    hw_gpadc->ctrl &= ~GPADC_REF_SEL;//0:1.2V reference;1:3.3V reference
			
				break;
			
			case 6:
					adcstruct.advalue_buf[6] = hw_gpadc->data_ch6;
					hw_gpadc->ctrl = GPADC_CH7_EN;
					adcstruct.ad_channel_select = 7;
				break;
			
			case 7:
					adcstruct.advalue_buf[7] = hw_gpadc->data_ch7;
					hw_gpadc->ctrl = GPADC_CH0_EN;
					adcstruct.ad_channel_select = 0;
				break;
			
			default:
				break;
		}
		hw_gpadc->ctrl |= ADC_EN;
//		hw_gpadc->ctrl |= GPADC_START;    //start convert
	}
}








uint16 GeckoGpadcGetRawData(GPADC_CHAN_T channel)
{
	
		volatile UINT32 enabledMask = 0;
    //volatile unsigned int* dataAddress = NULL;
		volatile unsigned int tmp=0,datavalue = 0;
	  //uint8 channel;
		//char *string;	

	  //hw_gpadc->ctrl |= ADC_EN; //ADC_EN=1
	
	  //hw_gpadc->ctrl &= ~ADC_EN; //ADC_EN=0
		
	
		hw_gpadc->ctrl =(1<<channel) | ADC_EN;	
	  hw_gpadc->ctrl =(1<<channel);	
	  hw_gpadc->ctrl =(1<<channel) | ADC_EN;	
	
    if(channel==8)
		{
		hw_gpadc->ctrl = GPADC_CH8_EN | ADC_EN;
		}
		else if(channel==9)
		{
		hw_gpadc->ctrl = GPADC_CH9_EN | ADC_EN;
		}

		adc_delay_us(10);
		datavalue=hw_gpadc->status;
//		UATR0_PRINT_LOG((unsigned char *)("\r\n"));						
//		UATR0_PRINT_LOG((unsigned char *)("hw_gpadc->status GPADC_EOC--- bit16:"));
//		string=my_itoa(datavalue);
//		UATR0_PRINT_LOG((unsigned char *)(string));
//		UATR0_PRINT_LOG((unsigned char *)("\r\n"));		
			
		while(!(hw_gpadc->status & GPADC_EOC))
		{
			//if (hw_gpadc->status & GPADC_EOC) = 0 , empty loop here ,wait here, wait,wait
			
			if(tmp++>3000)
			{
			//hw_gpadc->ctrl =0;//disable all channels
			datavalue=hw_gpadc->ctrl;
//			UATR0_PRINT_LOG((unsigned char *)("\r\n"));						
//			UATR0_PRINT_LOG((unsigned char *)("hw_gpadc->ctrl ADC_EN--- bit12:"));
//			string=my_itoa(datavalue);
//			UATR0_PRINT_LOG((unsigned char *)(string));
//			UATR0_PRINT_LOG((unsigned char *)("\r\n"));	
				
			datavalue=hw_gpadc->status;
//			UATR0_PRINT_LOG((unsigned char *)("\r\n"));						
//			UATR0_PRINT_LOG((unsigned char *)("hw_gpadc->status GPADC_EOC--- bit16:"));
//			string=my_itoa(datavalue);
//			UATR0_PRINT_LOG((unsigned char *)(string));
//			UATR0_PRINT_LOG((unsigned char *)("\r\n"));					
			return 0xff;//timeout exit loop
				//break;
			}
		}
		
	  tmp=0;

        // Conversion is done, read the GPADC
        switch (channel)
        {
            case GPADC_CHAN_0:
                enabledMask = GPADC_CH0_EN;
								datavalue = hw_gpadc->data_ch0;					
                break;
            case GPADC_CHAN_1:
                enabledMask = GPADC_CH1_EN;
								datavalue = hw_gpadc->data_ch1;
                break;
            case GPADC_CHAN_2:
                enabledMask = GPADC_CH2_EN;
								datavalue = hw_gpadc->data_ch2;
                break;
            case GPADC_CHAN_3:
                enabledMask = GPADC_CH3_EN;
								datavalue = hw_gpadc->data_ch3;
                break;
						
            case GPADC_CHAN_4:
                enabledMask = GPADC_CH4_EN;
								datavalue = hw_gpadc->data_ch4;
                break;
            case GPADC_CHAN_5:
                enabledMask = GPADC_CH5_EN;
						    hw_gpadc->ctrl |= GPADC_REF_SEL;//0:1.2V reference;1:3.3V reference
						    adc_delay_us(20);
								datavalue = hw_gpadc->data_ch5;
                break;
            case GPADC_CHAN_6:
                enabledMask = GPADC_CH6_EN;
								datavalue = hw_gpadc->data_ch6;
                break;
            case GPADC_CHAN_7:
                enabledMask = GPADC_CH7_EN;
								datavalue = hw_gpadc->data_ch7;
                break;
						
//2022-09-04
            case GPADC_CHAN_8:
                enabledMask = GPADC_CH8_EN;
								hw_gpadc->ctrl |= GPADC_REF_SEL;//0:1.2V reference;1:3.3V reference
								datavalue = hw_gpadc->data_ch8;
                break;	
//2022-09-04
            case GPADC_CHAN_9:
                enabledMask = GPADC_CH8_EN;
								hw_gpadc->ctrl |= GPADC_REF_SEL;//0:1.2V reference;1:3.3V reference
								datavalue = hw_gpadc->data_ch9;
                break;	
            default:
								break;
        }
				
				hw_gpadc->ctrl =0;//disable all channels

		return datavalue;
}









uint16 Get_Vbat_Voltage(void)
{
	  uint16 datavalue;
	  int adc_convert;
	
	  volatile unsigned int tmp=0;
	
		hw_gpadc->ctrl = GPADC_CH5_EN | ADC_EN;	
	
		hw_gpadc->ctrl |= GPADC_REF_SEL;//0:1.2V reference;1:3.3V reference	
	
		while(!(hw_gpadc->status & GPADC_EOC))
		{
			if(tmp++>3000)
			{
			return 0x0;//timeout exit loop
			}
		}
		
    tmp=0;
		
		adc_delay_us(20);

		datavalue = hw_gpadc->data_ch5;
		
		hw_gpadc->ctrl =0;//disable all channels	


		adc_convert=(datavalue*1000)/4095;//Expand 1000 times
		//printf("\r\nnGet_Vbat_Voltage adc_convert___1 = %d",adc_convert);
		
		adc_convert=adc_convert*(3.3*2);//3.3V x 2 = 6.6V
		//printf("\r\nnGet_Vbat_Voltage adc_convert___2 = %d",adc_convert);			
		
		return adc_convert;
}








