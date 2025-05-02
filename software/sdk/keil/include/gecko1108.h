
#include "platform_config.h"

#define	 	 GECKO_ROM_BASE		    							0x00000000
#define	 	 GECKO_SRAM_BASE		    						0x20000000




/*--------------------- Clock Configuration ----------------------------------*/
/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/

#define IRC_OSC     (8000000UL)        /* Internal RC oscillator frequency   */


/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
//#define IRC_OSC     (16000000UL)        /* Internal RC oscillator frequency   */


#define OSC_CLK       (  IRC_OSC)        /* Main oscillator frequency          */



#define HCI_clock_frequency                                  (10000000)






#define     __I     volatile                  /*!< defines 'read only' permissions      */
#define     __O     volatile                  /*!< defines 'write only' permissions     */
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */





#define BIT(n)            ((unsigned int) 1 << (n))
//#define BIT(x)          (1<<(x))





#if 0

#define BIT0  0x0001
#define BIT1  0x0002
#define BIT2  0x0004
#define BIT3  0x0008
#define BIT4  0x0010
#define BIT5  0x0020
#define BIT6  0x0040
#define BIT7  0x0080
#define BIT8  0x0100
#define BIT9  0x0200
#define BIT10 0x0400
#define BIT11 0x0800
#define BIT12 0x1000
#define BIT13 0x2000
#define BIT14 0x4000
#define BIT15 0x8000

#define BIT16 0x00010000
#define BIT17 0x00020000
#define BIT18 0x00040000
#define BIT19 0x00080000
#define BIT20 0x00100000
#define BIT21 0x00200000
#define BIT22 0x00400000
#define BIT23 0x00800000L
#define BIT24 0x01000000L
#define BIT25 0x02000000L
#define BIT26 0x04000000L
#define BIT27 0x08000000L
#define BIT28 0x10000000L
#define BIT29 0x20000000L
#define BIT30 0x40000000L
#define BIT31 0x80000000UL

#endif







/* -------------------------  Interrupt Number Definition  ------------------------ */
/* -------------------------  Interrupt Number Definition  ------------------------ */
/* -------------------------  Interrupt Number Definition  ------------------------ */
typedef enum IRQn
{
	
/* -------------------  Cortex-M4 Processor Exceptions Numbers  ------------------- */
  NonMaskableInt_IRQn           = -14,      /*!<  2 Non Maskable Interrupt          */
  HardFault_IRQn                = -13,      /*!<  3 HardFault Interrupt             */
  MemoryManagement_IRQn         = -12,      /*!<  4 Memory Management Interrupt     */
  BusFault_IRQn                 = -11,      /*!<  5 Bus Fault Interrupt             */
  UsageFault_IRQn               = -10,      /*!<  6 Usage Fault Interrupt           */
  SVCall_IRQn                   =  -5,      /*!< 11 SV Call Interrupt               */
  DebugMonitor_IRQn             =  -4,      /*!< 12 Debug Monitor Interrupt         */
  PendSV_IRQn                   =  -2,      /*!< 14 Pend SV Interrupt               */
  SysTick_IRQn                  =  -1,      /*!< 15 System Tick Interrupt           */


/* ----------------------  GECKO1108 Specific Interrupt Numbers  --------------------- */
  I2C0_IRQn                     =   0,      /*!< I2C Interrupt                     */
  I2C1_IRQn                     =   1,      /*!< I2C Interrupt                     */

  UART0_IRQn                    =   2,      /*!< UART0 Interrupt                    */
  UART1_IRQn                    =   3,      /*!< UART1 Interrupt                    */
  DMA_IRQn                    =   4,      /*!< UART2 Interrupt                    */
	
  TIMER0_IRQn                   =   5,      /*!< TIMER0 Interrupt                   */
  TIMER1_IRQn                   =   6,      /*!< TIMER1 Interrupt                   */
  ADC_IRQn                      =   7,      /*!< ADC Interrupt                      */
	
  GPIO_0_INTR_IRQn              =   8,      /*!< GPIO Group 0 INTR Interrupt        */
  GPIO_1_INTR_IRQn              =   9,      /*!< GPIO Group 1 INTR Interrupt        */
	
  WDT_IRQn                      =   10,     /*!< WatchDog Interrupt                 */
  Lightning_IRQn             		=   11,     /*!< Lightning Interrupt                */

  GPIO_A0_IRQn             			=   12,     /*!< DMA Interrupt                			*/
	
  APB_SPI0_IRQn                  =  13,     /*!< SPI Master Interrupt               */
  APB_SPI1_IRQn                  =  14,     /*!< SPI Master Interrupt               */

  QI_IRQn             					=   15,     /*!< QI Interrupt                			*/
  QSPI_IRQn                     =   16,     /*!< QSPI controller interrupt          */

//	GPIOA_0_3_MISC_IRQn           =   17,      /*!< GPIO[3:0] MISC   										*/
  RTC_IRQ												=   17,
	
  GPIO_A4_IRQn             			=   18,      /*!< GPIOA[4] interrupt   								*/	
  GPIO_A5_IRQn             			=   19,      /*!< GPIOA[5] interrupt   								*/	
  GPIO_A6_IRQn             			=   20,      /*!< GPIOA[6] interrupt   								*/	
  GPIO_A7_IRQn             			=   21,      /*!< GPIOA[7] interrupt   								*/	

  GPIO_B0_IRQn             			=   22,      /*!< GPIOB[0] interrupt   								*/	
  GPIO_B1_IRQn             			=   23,      /*!< GPIOB[1] interrupt   								*/	
  GPIO_B2_IRQn             			=   24,      /*!< GPIOB[2] interrupt   								*/	
  GPIO_B3_IRQn             			=   25,      /*!< GPIOB[3] interrupt   								*/	
  GPIO_B4_IRQn             			=   26,      /*!< GPIOB[4] interrupt   								*/	
  GPIO_B5_IRQn             			=   27,      /*!< GPIOB[5] interrupt   								*/	
  GPIO_B6_IRQn             			=   28,      /*!< GPIOB[6] interrupt   								*/	
  GPIO_B7_IRQn             			=   29,      /*!< GPIOB[7] interrupt   								*/
  AON_IRQn                      =  30,      /*!< Always-on module interrupt         */
  CMU2AHB_IRQ                   =  31,      /*!< Reserved Interrupt                 */
  INVALID_IRQn
} IRQn_Type;

#if 0
assign irq_raw = {
        2'h0,
        cmu2ahb_wr_ack,     //29
        irq_apb_spi,        //28
        irq_aon_sub,        //27
        irq_qspi_ctrl,      //26
        gpio1mis[7:0],      //25:18
        gpio1intr,          //17
        gpiomis[7:0],       //16:9
        ligt_rx_done_int,   //8
        int_wdt,    //7
        gpiointr,   //6
        intr_gpadc, //5
        int_timer1, //4
        int_timer0, //3
        int_uart1,  //2
        int_uart,   //1
        int_i2c     //0
        }; 
#endif

/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* --------  Configuration of the Cortex-M0 Processor and Core Peripherals  ------- */

#ifndef __CM0_REV
	#define __CM0_REV               0x0000
	//#warning "__CM0_REV not defined in device header file; using default!"
#endif

#ifndef __NVIC_PRIO_BITS
//	#define __NVIC_PRIO_BITS          2
	#define __NVIC_PRIO_BITS          4	
	//#warning "__NVIC_PRIO_BITS not defined in device header file; using default!"
#endif

#ifndef __Vendor_SysTickConfig
	#define __Vendor_SysTickConfig    0
	//#warning "__Vendor_SysTickConfig not defined in device header file; using default!"
#endif







#define GECKO_READ_REGISTER(_register_)                      		(*(volatile uint32*)(_register_))
#define HWreg_Get_Register(_register_)                      		(*(volatile uint32*)(_register_))
	
#define GECKO_WRITE_REGISTER(_register_,_value_)                (*(volatile uint32*)(_register_)) = (uint32)(_value_)
#define HWreg_Assign_Register(_register_,_value_)               (*(volatile uint32*)(_register_)) = (uint32)(_value_)







/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/


/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_SysTick     System Tick Timer (SysTick)
  \brief    Type definitions for the System Timer Registers.
  @{
 */

/**
  \brief  Structure type to access the System Timer (SysTick).
 */
typedef struct
{
  __IO uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __IO uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  __IO uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  __I  uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_Type;





/**
  \ingroup    CMSIS_core_register
  \defgroup   CMSIS_NVIC  Nested Vectored Interrupt Controller (NVIC)
  \brief      Type definitions for the NVIC Registers
  @{
 */

/**
  \brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
typedef struct
{
  __IO uint32_t ISER[1U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
        uint32_t RESERVED0[31U];
  __IO uint32_t ICER[1U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
        uint32_t RSERVED1[31U];
  __IO uint32_t ISPR[1U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
        uint32_t RESERVED2[31U];
  __IO uint32_t ICPR[1U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
        uint32_t RESERVED3[31U];
        uint32_t RESERVED4[64U];
  __IO uint32_t IP[8U];                 /*!< Offset: 0x300 (R/W)  Interrupt Priority Register */
}  NVIC_Type;




/*@} end of group CMSIS_NVIC */


/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_SCB     System Control Block (SCB)
  \brief    Type definitions for the System Control Block Registers
  @{
 */

/**
  \brief  Structure type to access the System Control Block (SCB).
 */
typedef struct
{
  __I  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  __IO uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
        uint32_t RESERVED0;
  __IO uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  __IO uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  __IO uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
        uint32_t RESERVED1;
  __IO uint32_t SHP[2U];                /*!< Offset: 0x01C (R/W)  System Handlers Priority Registers. [0] is RESERVED */
  __IO uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
} SCB_Type;




/* SCB CPUID Register Definitions */
#define SCB_CPUID_IMPLEMENTER_Pos          24U                                            /*!< SCB CPUID: IMPLEMENTER Position */
#define SCB_CPUID_IMPLEMENTER_Msk          (0xFFUL << SCB_CPUID_IMPLEMENTER_Pos)          /*!< SCB CPUID: IMPLEMENTER Mask */

#define SCB_CPUID_VARIANT_Pos              20U                                            /*!< SCB CPUID: VARIANT Position */
#define SCB_CPUID_VARIANT_Msk              (0xFUL << SCB_CPUID_VARIANT_Pos)               /*!< SCB CPUID: VARIANT Mask */

#define SCB_CPUID_ARCHITECTURE_Pos         16U                                            /*!< SCB CPUID: ARCHITECTURE Position */
#define SCB_CPUID_ARCHITECTURE_Msk         (0xFUL << SCB_CPUID_ARCHITECTURE_Pos)          /*!< SCB CPUID: ARCHITECTURE Mask */

#define SCB_CPUID_PARTNO_Pos                4U                                            /*!< SCB CPUID: PARTNO Position */
#define SCB_CPUID_PARTNO_Msk               (0xFFFUL << SCB_CPUID_PARTNO_Pos)              /*!< SCB CPUID: PARTNO Mask */

#define SCB_CPUID_REVISION_Pos              0U                                            /*!< SCB CPUID: REVISION Position */
#define SCB_CPUID_REVISION_Msk             (0xFUL /*<< SCB_CPUID_REVISION_Pos*/)          /*!< SCB CPUID: REVISION Mask */

/* SCB Interrupt Control State Register Definitions */
#define SCB_ICSR_NMIPENDSET_Pos            31U                                            /*!< SCB ICSR: NMIPENDSET Position */
#define SCB_ICSR_NMIPENDSET_Msk            (1UL << SCB_ICSR_NMIPENDSET_Pos)               /*!< SCB ICSR: NMIPENDSET Mask */

#define SCB_ICSR_PENDSVSET_Pos             28U                                            /*!< SCB ICSR: PENDSVSET Position */
#define SCB_ICSR_PENDSVSET_Msk             (1UL << SCB_ICSR_PENDSVSET_Pos)                /*!< SCB ICSR: PENDSVSET Mask */

#define SCB_ICSR_PENDSVCLR_Pos             27U                                            /*!< SCB ICSR: PENDSVCLR Position */
#define SCB_ICSR_PENDSVCLR_Msk             (1UL << SCB_ICSR_PENDSVCLR_Pos)                /*!< SCB ICSR: PENDSVCLR Mask */

#define SCB_ICSR_PENDSTSET_Pos             26U                                            /*!< SCB ICSR: PENDSTSET Position */
#define SCB_ICSR_PENDSTSET_Msk             (1UL << SCB_ICSR_PENDSTSET_Pos)                /*!< SCB ICSR: PENDSTSET Mask */

#define SCB_ICSR_PENDSTCLR_Pos             25U                                            /*!< SCB ICSR: PENDSTCLR Position */
#define SCB_ICSR_PENDSTCLR_Msk             (1UL << SCB_ICSR_PENDSTCLR_Pos)                /*!< SCB ICSR: PENDSTCLR Mask */

#define SCB_ICSR_ISRPREEMPT_Pos            23U                                            /*!< SCB ICSR: ISRPREEMPT Position */
#define SCB_ICSR_ISRPREEMPT_Msk            (1UL << SCB_ICSR_ISRPREEMPT_Pos)               /*!< SCB ICSR: ISRPREEMPT Mask */

#define SCB_ICSR_ISRPENDING_Pos            22U                                            /*!< SCB ICSR: ISRPENDING Position */
#define SCB_ICSR_ISRPENDING_Msk            (1UL << SCB_ICSR_ISRPENDING_Pos)               /*!< SCB ICSR: ISRPENDING Mask */

#define SCB_ICSR_VECTPENDING_Pos           12U                                            /*!< SCB ICSR: VECTPENDING Position */
#define SCB_ICSR_VECTPENDING_Msk           (0x1FFUL << SCB_ICSR_VECTPENDING_Pos)          /*!< SCB ICSR: VECTPENDING Mask */

#define SCB_ICSR_VECTACTIVE_Pos             0U                                            /*!< SCB ICSR: VECTACTIVE Position */
#define SCB_ICSR_VECTACTIVE_Msk            (0x1FFUL /*<< SCB_ICSR_VECTACTIVE_Pos*/)       /*!< SCB ICSR: VECTACTIVE Mask */

/* SCB Application Interrupt and Reset Control Register Definitions */
#define SCB_AIRCR_VECTKEY_Pos              16U                                            /*!< SCB AIRCR: VECTKEY Position */
#define SCB_AIRCR_VECTKEY_Msk              (0xFFFFUL << SCB_AIRCR_VECTKEY_Pos)            /*!< SCB AIRCR: VECTKEY Mask */

#define SCB_AIRCR_VECTKEYSTAT_Pos          16U                                            /*!< SCB AIRCR: VECTKEYSTAT Position */
#define SCB_AIRCR_VECTKEYSTAT_Msk          (0xFFFFUL << SCB_AIRCR_VECTKEYSTAT_Pos)        /*!< SCB AIRCR: VECTKEYSTAT Mask */

#define SCB_AIRCR_ENDIANESS_Pos            15U                                            /*!< SCB AIRCR: ENDIANESS Position */
#define SCB_AIRCR_ENDIANESS_Msk            (1UL << SCB_AIRCR_ENDIANESS_Pos)               /*!< SCB AIRCR: ENDIANESS Mask */

#define SCB_AIRCR_SYSRESETREQ_Pos           2U                                            /*!< SCB AIRCR: SYSRESETREQ Position */
#define SCB_AIRCR_SYSRESETREQ_Msk          (1UL << SCB_AIRCR_SYSRESETREQ_Pos)             /*!< SCB AIRCR: SYSRESETREQ Mask */

#define SCB_AIRCR_VECTCLRACTIVE_Pos         1U                                            /*!< SCB AIRCR: VECTCLRACTIVE Position */
#define SCB_AIRCR_VECTCLRACTIVE_Msk        (1UL << SCB_AIRCR_VECTCLRACTIVE_Pos)           /*!< SCB AIRCR: VECTCLRACTIVE Mask */

/* SCB System Control Register Definitions */
#define SCB_SCR_SEVONPEND_Pos               4U                                            /*!< SCB SCR: SEVONPEND Position */
#define SCB_SCR_SEVONPEND_Msk              (1UL << SCB_SCR_SEVONPEND_Pos)                 /*!< SCB SCR: SEVONPEND Mask */

#define SCB_SCR_SLEEPDEEP_Pos               2U                                            /*!< SCB SCR: SLEEPDEEP Position */
#define SCB_SCR_SLEEPDEEP_Msk              (1UL << SCB_SCR_SLEEPDEEP_Pos)                 /*!< SCB SCR: SLEEPDEEP Mask */

#define SCB_SCR_SLEEPONEXIT_Pos             1U                                            /*!< SCB SCR: SLEEPONEXIT Position */
#define SCB_SCR_SLEEPONEXIT_Msk            (1UL << SCB_SCR_SLEEPONEXIT_Pos)               /*!< SCB SCR: SLEEPONEXIT Mask */

/* SCB Configuration Control Register Definitions */
#define SCB_CCR_STKALIGN_Pos                9U                                            /*!< SCB CCR: STKALIGN Position */
#define SCB_CCR_STKALIGN_Msk               (1UL << SCB_CCR_STKALIGN_Pos)                  /*!< SCB CCR: STKALIGN Mask */

#define SCB_CCR_UNALIGN_TRP_Pos             3U                                            /*!< SCB CCR: UNALIGN_TRP Position */
#define SCB_CCR_UNALIGN_TRP_Msk            (1UL << SCB_CCR_UNALIGN_TRP_Pos)               /*!< SCB CCR: UNALIGN_TRP Mask */

/* SCB System Handler Control and State Register Definitions */
#define SCB_SHCSR_SVCALLPENDED_Pos         15U                                            /*!< SCB SHCSR: SVCALLPENDED Position */
#define SCB_SHCSR_SVCALLPENDED_Msk         (1UL << SCB_SHCSR_SVCALLPENDED_Pos)            /*!< SCB SHCSR: SVCALLPENDED Mask */



/**
  * @brief Cortex-M0 processor and core peripherals configuration
  */




/** \ingroup  CMSIS_core_register
    \defgroup CMSIS_SysTick     System Tick Timer (SysTick)
    \brief      Type definitions for the System Timer Registers.
  @{
 */


/* SysTick Control / Status Register Definitions */
#define SysTick_CTRL_COUNTFLAG_Pos         16                                             /*!< SysTick CTRL: COUNTFLAG Position */
#define SysTick_CTRL_COUNTFLAG_Msk         (1UL << SysTick_CTRL_COUNTFLAG_Pos)            /*!< SysTick CTRL: COUNTFLAG Mask */

#define SysTick_CTRL_CLKSOURCE_Pos          2                                             /*!< SysTick CTRL: CLKSOURCE Position */
#define SysTick_CTRL_CLKSOURCE_Msk         (1UL << SysTick_CTRL_CLKSOURCE_Pos)            /*!< SysTick CTRL: CLKSOURCE Mask */

#define SysTick_CTRL_TICKINT_Pos            1                                             /*!< SysTick CTRL: TICKINT Position */
#define SysTick_CTRL_TICKINT_Msk           (1UL << SysTick_CTRL_TICKINT_Pos)              /*!< SysTick CTRL: TICKINT Mask */

#define SysTick_CTRL_ENABLE_Pos             0                                             /*!< SysTick CTRL: ENABLE Position */
#define SysTick_CTRL_ENABLE_Msk            (1UL /*<< SysTick_CTRL_ENABLE_Pos*/)           /*!< SysTick CTRL: ENABLE Mask */

/* SysTick Reload Register Definitions */
#define SysTick_LOAD_RELOAD_Pos             0                                             /*!< SysTick LOAD: RELOAD Position */
#define SysTick_LOAD_RELOAD_Msk            (0xFFFFFFUL /*<< SysTick_LOAD_RELOAD_Pos*/)    /*!< SysTick LOAD: RELOAD Mask */

/* SysTick Current Register Definitions */
#define SysTick_VAL_CURRENT_Pos             0                                             /*!< SysTick VAL: CURRENT Position */
#define SysTick_VAL_CURRENT_Msk            (0xFFFFFFUL /*<< SysTick_VAL_CURRENT_Pos*/)    /*!< SysTick VAL: CURRENT Mask */

/* SysTick Calibration Register Definitions */
#define SysTick_CALIB_NOREF_Pos            31                                             /*!< SysTick CALIB: NOREF Position */
#define SysTick_CALIB_NOREF_Msk            (1UL << SysTick_CALIB_NOREF_Pos)               /*!< SysTick CALIB: NOREF Mask */

#define SysTick_CALIB_SKEW_Pos             30                                             /*!< SysTick CALIB: SKEW Position */
#define SysTick_CALIB_SKEW_Msk             (1UL << SysTick_CALIB_SKEW_Pos)                /*!< SysTick CALIB: SKEW Mask */

#define SysTick_CALIB_TENMS_Pos             0                                             /*!< SysTick CALIB: TENMS Position */
#define SysTick_CALIB_TENMS_Msk            (0xFFFFFFUL /*<< SysTick_CALIB_TENMS_Pos*/)    /*!< SysTick CALIB: TENMS Mask */

/*@} end of group CMSIS_SysTick */




/* Memory mapping of Core Hardware */
#define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */
#define SysTick_BASE        (SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address */
#define NVIC_BASE           (SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address */
#define SCB_BASE            (SCS_BASE +  0x0D00UL)                    /*!< System Control Block Base Address */

#define SCB                 ((SCB_Type       *)     SCB_BASE      )   /*!< SCB configuration struct */
#define SysTick             ((SysTick_Type   *)     SysTick_BASE  )   /*!< SysTick configuration struct */
#define NVIC                ((NVIC_Type      *)     NVIC_BASE     )   /*!< NVIC configuration struct */






extern void hal_nvic_set_priority(IRQn_Type irq_number, uint32 priority);
extern void hal_nvic_enable_irq(IRQn_Type irq_number);
extern void hal_nvic_disable_irq(IRQn_Type irq_number);

extern uint32_t hal_nvic_get_pending_irq(IRQn_Type irq_number);
extern void hal_nvic_set_pending_irq(IRQn_Type irq_number);
extern void hal_nvic_clear_pending_irq(IRQn_Type irq_number);


