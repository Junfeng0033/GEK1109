
#include "platform_config.h"


//define AHB base address
//AHB Address
#define GECKO_PWM_BASE								0x40005000



//define AHB base address
//AHB Address
#define GECKO_PWM_BASE_NEW								0x40005000



typedef volatile struct
{
    REG32                          pwm_select_en;                   //0x00000000
    REG32                          r_pwm01_initial;                 //0x00000004
    REG32                          r_pwm23_initial;                 //0x00000008
    REG32                          r_pwm01_toggle;                  //0x0000000C
    REG32                          r_pwm23_toggle;                  //0x00000010
    REG32                          r_pwm01_phase;                   //0x00000014	
    REG32                          r_pwm23_phase;                   //0x00000018
	
    REG32                          r_pwm45_initial;                 //0x0000001C
    REG32                          r_pwm45_toggle;                  //0x00000020
    REG32                          r_pwm45_phase;                   //0x00000024
	
    REG32                          r_pwm03_Td_cycle;                //0x00000028
    REG32                          r_pwm47_Td_cycle;                //0x0000002C	
#if 1//def GEK1109		
    REG32                          r_pwm67_initial;                 //0x00000030
    REG32                          r_pwm67_toggle;                  //0x00000034
    REG32                          r_pwm67_phase;                   //0x00000038
	
    REG32                          pwm_reg0x3c;                     //0x0000003C
    REG32                          pwm_reg0x40;                     //0x00000040
    REG32                          pwm_reg0x44;                     //0x00000044
    REG32                          pwm_reg0x48;                     //0x00000048	
    REG32                          pwm_reg0x4c;                     //0x0000004C
    REG32                          pwm_reg0x50;                     //0x00000050		

#endif	
	
} Gecko_PWM_T;



#define Gecko_PWM                   ((Gecko_PWM_T*) GECKO_PWM_BASE_NEW)




typedef enum
{
  	HW_PWM_CHAN_0=0,
    HW_PWM_CHAN_1,
    HW_PWM_CHAN_2,
    HW_PWM_CHAN_3,
    HW_PWM_CHAN_4,
    HW_PWM_CHAN_5,
#if 1//def GEK1109	
    HW_PWM_CHAN_6,
    HW_PWM_CHAN_7,	
#endif
    HW_PWM_CHAN_QTY,
	
} HW_PWM_CHAN_T;




#define PWM_MAX_VALUE                   0xFFFF

//AHB clock is 20MHZ@3.3V (20241212)
#define APB_PWM_CLOCK                  	10000000



struct HAL_PWM_CFG_T {
    uint32_t freq; //expected frequency
    uint8_t ratio; //expected duty
	  uint8   Tdead_cycle_count;
};










#define PWM_LOAD01_0(n)             (((n) & 0xFFFF) << 0)
#define PWM_LOAD01_0_MASK           (0xFFFF << 0)
#define PWM_LOAD01_0_SHIFT          (0)
#define PWM_LOAD01_1(n)             (((n) & 0xFFFF) << 16)
#define PWM_LOAD01_1_MASK           ((uint32) 0xFFFF << 16)
#define PWM_LOAD01_1_SHIFT          (16)

#define PWM_LOAD23_2(n)             (((n) & 0xFFFF) << 0)
#define PWM_LOAD23_2_MASK           (0xFFFF << 0)
#define PWM_LOAD23_2_SHIFT          (0)
#define PWM_LOAD23_3(n)             (((n) & 0xFFFF) << 16)
#define PWM_LOAD23_3_MASK           ((uint32)0xFFFF << 16)
#define PWM_LOAD23_3_SHIFT          (16)

//by JF
#define PWM_LOAD45_4(n)             (((n) & 0xFFFF) << 0)
#define PWM_LOAD45_4_MASK           (0xFFFF << 0)
#define PWM_LOAD45_4_SHIFT          (0)
#define PWM_LOAD45_5(n)             (((n) & 0xFFFF) << 16)
#define PWM_LOAD45_5_MASK           ((uint32)0xFFFF << 16)
#define PWM_LOAD45_5_SHIFT          (16)

//by JF ---2022-09-02
#define PWM_LOAD67_6(n)             (((n) & 0xFFFF) << 0)
#define PWM_LOAD67_6_MASK           (0xFFFF << 0)
#define PWM_LOAD67_6_SHIFT          (0)
#define PWM_LOAD67_7(n)             (((n) & 0xFFFF) << 16)
#define PWM_LOAD67_7_MASK           ((uint32)0xFFFF << 16)
#define PWM_LOAD67_7_SHIFT          (16)


#define PWM_TOGGLE01_0(n)           (((n) & 0xFFFF) << 0)
#define PWM_TOGGLE01_0_MASK         (0xFFFF << 0)
#define PWM_TOGGLE01_0_SHIFT        (0)
#define PWM_TOGGLE01_1(n)           (((n) & 0xFFFF) << 16)
#define PWM_TOGGLE01_1_MASK         ((uint32)0xFFFF << 16)
#define PWM_TOGGLE01_1_SHIFT        (16)

#define PWM_TOGGLE23_2(n)           (((n) & 0xFFFF) << 0)
#define PWM_TOGGLE23_2_MASK         (0xFFFF << 0)
#define PWM_TOGGLE23_2_SHIFT        (0)
#define PWM_TOGGLE23_3(n)           (((n) & 0xFFFF) << 16)
#define PWM_TOGGLE23_3_MASK         ((uint32)0xFFFF << 16)
#define PWM_TOGGLE23_3_SHIFT        (16)

#define PWM_TOGGLE45_4(n)           (((n) & 0xFFFF) << 0)
#define PWM_TOGGLE45_4_MASK         (0xFFFF << 0)
#define PWM_TOGGLE45_4_SHIFT        (0)
#define PWM_TOGGLE45_5(n)           (((n) & 0xFFFF) << 16)
#define PWM_TOGGLE45_5_MASK         ((uint32)0xFFFF << 16)
#define PWM_TOGGLE45_5_SHIFT        (16)

//by JF ---2022-09-02
#define PWM_TOGGLE67_6(n)           (((n) & 0xFFFF) << 0)
#define PWM_TOGGLE67_6_MASK         (0xFFFF << 0)
#define PWM_TOGGLE67_6_SHIFT        (0)
#define PWM_TOGGLE67_7(n)           (((n) & 0xFFFF) << 16)
#define PWM_TOGGLE67_7_MASK         ((uint32)0xFFFF << 16)
#define PWM_TOGGLE67_7_SHIFT        (16)


#define PWM_PHASE01_0(n)            (((n) & 0xFFFF) << 0)
#define PWM_PHASE01_0_MASK          (0xFFFF << 0)
#define PWM_PHASE01_0_SHIFT         (0)
#define PWM_PHASE01_1(n)            (((n) & 0xFFFF) << 16)
#define PWM_PHASE01_1_MASK          (0xFFFF << 16)
#define PWM_PHASE01_1_SHIFT         (16)

#define PWM_PHASE23_2(n)            (((n) & 0xFFFF) << 0)
#define PWM_PHASE23_2_MASK          (0xFFFF << 0)
#define PWM_PHASE23_2_SHIFT         (0)
#define PWM_PHASE23_3(n)            (((n) & 0xFFFF) << 16)
#define PWM_PHASE23_3_MASK          (0xFFFF << 16)
#define PWM_PHASE23_3_SHIFT         (16)


#define PWM_PHASE45_4(n)            (((n) & 0xFFFF) << 0)
#define PWM_PHASE45_4_MASK          (0xFFFF << 0)
#define PWM_PHASE45_4_SHIFT         (0)
#define PWM_PHASE45_5(n)            (((n) & 0xFFFF) << 16)
#define PWM_PHASE45_5_MASK          (0xFFFF << 16)
#define PWM_PHASE45_5_SHIFT         (16)

//by JF ---2022-09-02
#define PWM_PHASE67_6(n)            (((n) & 0xFFFF) << 0)
#define PWM_PHASE67_6_MASK          (0xFFFF << 0)
#define PWM_PHASE67_6_SHIFT         (0)
#define PWM_PHASE67_7(n)            (((n) & 0xFFFF) << 16)
#define PWM_PHASE67_7_MASK          (0xFFFF << 16)
#define PWM_PHASE67_7_SHIFT         (16)


//register 0x28
#define PWM0_Td_Cycle(n)					(((n)&0xFF)<<0)
#define PWM1_Td_Cycle(n)          (((n)&0xFF)<<8)
#define PWM2_Td_Cycle(n)					(((n)&0xFF)<<16)
#define PWM3_Td_Cycle(n)          (((n)&0xFF)<<24)


//register 0x2c
#define PWM4_Td_Cycle(n)					(((n)&0xFF)<<0)
#define PWM5_Td_Cycle(n)          (((n)&0xFF)<<8)
//by JF ---2022-09-02
#define PWM6_Td_Cycle(n)					(((n)&0xFF)<<16)
#define PWM7_Td_Cycle(n)          (((n)&0xFF)<<24)


//register 0x40
#define FREQ_AVE_DONE          		(1<<1)//bit1

//register 0x4C
//#define FREQ_AVE_NUM(n)           (((n)&0xFF)<<16) 
#define FREQ_AVE_EN               ((uint32)1<<24)//bit24



//register 0x50

void hw_pwm_invert(HW_PWM_CHAN_T channel);
uint8 gecko_pwm_init(void);

void Config_PWM(HW_PWM_CHAN_T channel,const struct HAL_PWM_CFG_T *cfg);
void hw_pwm_enable(HW_PWM_CHAN_T channel);

void SixCh_PWM5_Config(void);
uint32 PWM_Capture(void);
