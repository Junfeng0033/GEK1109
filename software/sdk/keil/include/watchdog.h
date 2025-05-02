
#include "platform_config.h"



#define    GECKO_APB_WATCHDOG_BASE                0x40014000
//define APB watchdog base address
#define	 	 GECKO_APB_WATCHDOG_BASE_ADDR		    		0x40014000


#define    GECKO_iWATCHDOG_BASE                   0x40022000





//output WDOGINT 			FRC(free running control) interrupt
//output WDOGRES			FRC	reset
//output [31:0]				Read data output



/*------------------- Watchdog ----------------------------------------------*/
typedef struct
{

  __IO    uint32_t  WdogLoad;               /* Offset: 0x000 (R/W) Watchdog Load Register */
  __I     uint32_t  WdogValue;//CountRead   /* Offset: 0x004 (R/ ) Watchdog Value Register */
  __IO    uint32_t  CTRL;                   /* Offset: 0x008 (R/W) Watchdog Control Register */
  __O     uint32_t  INTCLR;                 /* Offset: 0x00C ( /W) Watchdog Clear Interrupt Register */
  __I     uint32_t  RAWINTSTAT;             /* Offset: 0x010 (R/ ) Watchdog Raw Interrupt Status Register */
  __I     uint32_t  MASKINTSTAT;            /* Offset: 0x014 (R/ ) Watchdog Interrupt Status Register */
					uint32_t  RESERVED0[762];
  __IO    uint32_t  LOCK;                   /* Offset: 0xC00 (R/W) Watchdog Lock Register */
					uint32_t  RESERVED1[191];
  __IO    uint32_t  ITCR;                   /* Offset: 0xF00 (R/W) Watchdog Integration Test Control Register */
  __O     uint32_t  ITOP;                   /* Offset: 0xF04 ( /W) Watchdog Integration Test Output Set Register */
}GECKO_WATCHDOG_TypeDef;


#define GECKO1108_WATCHDOG          ((GECKO_WATCHDOG_TypeDef  *) GECKO_APB_WATCHDOG_BASE   )



#define Gecko_Watchdog_LOAD_Pos               0                                              /* Watchdog LOAD: LOAD Position */
#define Gecko_Watchdog_LOAD_Msk              (0xFFFFFFFFul << Gecko_Watchdog_LOAD_Pos)       /* Watchdog LOAD: LOAD Mask */

#define Gecko_Watchdog_VALUE_Pos              0                                              /* Watchdog VALUE: VALUE Position */
#define Gecko_Watchdog_VALUE_Msk             (0xFFFFFFFFul << Gecko_Watchdog_VALUE_Pos)      /* Watchdog VALUE: VALUE Mask */



//correct

#define Gecko_Watchdog_CTRL_RESEN_Pos         1                                              /* Watchdog CTRL_RESEN: Enable Reset Output Position */
#define Gecko_Watchdog_CTRL_RESEN_Msk        (0x1ul << Gecko_Watchdog_CTRL_RESEN_Pos)        /* Watchdog CTRL_RESEN: Enable Reset Output Mask */

#define Gecko_Watchdog_CTRL_INTEN_Pos         0                                              /* Watchdog CTRL_INTEN: Int Enable Position */
#define Gecko_Watchdog_CTRL_INTEN_Msk        (0x1ul << Gecko_Watchdog_CTRL_INTEN_Pos)        /* Watchdog CTRL_INTEN: Int Enable Mask */



#define Gecko_Watchdog_INTCLR_Pos             0                                              /* Watchdog INTCLR: Int Clear Position */
#define Gecko_Watchdog_INTCLR_Msk            (0x1ul << Gecko_Watchdog_INTCLR_Pos)            /* Watchdog INTCLR: Int Clear Mask */

#define Gecko_Watchdog_RAWINTSTAT_Pos         0                                              /* Watchdog RAWINTSTAT: Raw Int Status Position */
#define Gecko_Watchdog_RAWINTSTAT_Msk        (0x1ul << Gecko_Watchdog_RAWINTSTAT_Pos)        /* MPS2_Watchdog RAWINTSTAT: Raw Int Status Mask */

#define Gecko_Watchdog_MASKINTSTAT_Pos        0                                              /* Watchdog MASKINTSTAT: Mask Int Status Position */
#define Gecko_Watchdog_MASKINTSTAT_Msk       (0x1ul << Gecko_Watchdog_MASKINTSTAT_Pos)       /* Watchdog MASKINTSTAT: Mask Int Status Mask */

#define Gecko_Watchdog_LOCK_Pos               0                                              /* Watchdog LOCK: LOCK Position */
#define Gecko_Watchdog_LOCK_Msk              (0x1ul << Gecko_Watchdog_LOCK_Pos)              /* Watchdog LOCK: LOCK Mask */

#define Gecko_Watchdog_INTEGTESTEN_Pos        0                                              /* Watchdog INTEGTESTEN: Integration Test Enable Position */
#define Gecko_Watchdog_INTEGTESTEN_Msk       (0x1ul << Gecko_Watchdog_INTEGTESTEN_Pos)       /* Watchdog INTEGTESTEN: Integration Test Enable Mask */

#define Gecko_Watchdog_INTEGTESTOUTSET_Pos    1                                              /* Watchdog INTEGTESTOUTSET: Integration Test Output Set Position */
#define Gecko_Watchdog_INTEGTESTOUTSET_Msk   (0x1ul << Gecko_Watchdog_INTEGTESTOUTSET_Pos)   /* Watchdog INTEGTESTOUTSET: Integration Test Output Set Mask */






//#define    GECKO_iWATCHDOG_BASE                   0x40022000
#define    GECKO_iWATCHDOG_BASE                   0x40022000
typedef struct
{
  __IO    uint32_t  IDREV;               /* Offset: 0x000 (RO) ID and Revision Register */
	        uint32_t  RESERVED04;
	        uint32_t  RESERVED08;
		      uint32_t  RESERVED0C;	
  __I     uint32_t  CTRL;                /* Offset: 0x010 (R/W) Control Register */
  __IO    uint32_t  RESTART;             /* Offset: 0x014 (R/W) Restart Register */
  __O     uint32_t  WREN;                /* Offset: 0x018 ( /W) Write Enable Register */
  __I     uint32_t  ST;                  /* Offset: 0x01C (R/ ) iWatchdog Status Register */

}iWatchDog_T;


#define iWATCHDOG          ((iWatchDog_T  *) GECKO_iWATCHDOG_BASE )

//0x18 register
#define WDT200_WP_NUM 							0x5aa5
//0x14 register
#define WDT200_RESTART_NUM 					0xcafe




//0x10 control register
#define IWDT_EN        			(1<<0)
#define IWDT_CLK_SEL        (1<<1)
#define IWDT_INT_EN        	(1<<2)
#define IWDT_RST_EN         (1<<3)
#define IWDT_INT_TIME(n)    (((n)&0xF)<<4)//IntTime[7:4]////The timer interval of the interrupt stage
#define IWDT_RST_TIME(n)    (((n)&0x7)<<8)//RstTime[10:8]



//#define WDT200_32BIT_TIMER









		




void watchdog_init(unsigned int cycle, int type);
                                       /* Program watchdog: */
                                       /* type = 0 : No action */
                                       /* type = 1 : Interrupt */
                                       /* type = 2 : Reset */
void watchdog_set(unsigned int cycle); /* update watchdog counter */
void watchdog_unlock(void);            /* unlock watchdog */
void watchdog_lock(void);              /* lock watchdog */
void watchdog_irq_clear(void);         /* clear watchdog interrupt */



void feed_dog(unsigned int cycle);


/****************************************************************************/
/* Program watchdog: */
/* type = 0 : No action */
/* type = 1 : Interrupt */
/* type = 2 : Reset */
/****************************************************************************/
//void watchdog_init(unsigned int cycle, int type);


/****************************************************************************/
/* update watchdog counter */
/****************************************************************************/
//void watchdog_set(unsigned int cycle);


/****************************************************************************/
/* unlock watchdog */
/****************************************************************************/
//void watchdog_unlock(void);

/****************************************************************************/
/* lock watchdog */
/****************************************************************************/
//void watchdog_lock(void);

/****************************************************************************/
/* clear watchdog interrupt */
/****************************************************************************/
//void watchdog_irq_clear(void);         




void iWDT_REG_RW(void);
void iWDT_Timer_Init(void);
void iWDT_Timer_Disable(void);
void iWDT_Timer_Restart(void);

