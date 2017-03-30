

#define HARDWARE_GLOBAL
#include "mytype.h"
#include "bsp.h"
#include "hardware.h"
#include "printk.h"
#include "main_mac.h"
#include "LPC1700PinCfg.h"
#include "microOS.h"


#define WDI                25
#define WDI_PORT            0

void pinInit (void);

static void   wdt_init(void);
void IO_init(void)
{
    pinInit();
    DDRPORT(0) |= BIT(WDI);
    DDRPORT(1) |= BIT(1);
	DDRPORT(2) |= BIT(10);

    __NOP();

	LED_ON;

    wdt_init();
    pr_debug("io init\n");
}

void wdt_init(void)
{
	PORT_OUT( WDI_PORT, WDI );
}

void wdt_reset(void)
{
	NBI_P( WDI_PORT, WDI );
}

void pinInit (void)
{
    /*
     * 引脚连接配置P0.00 -- P0.15
     */
    LPC_PINCON->PINSEL0  = (P0_15_FNUC << 30)|
               (P0_11_FNUC << 22)|(P0_10_FNUC << 20)|(P0_9_FNUC << 18) |(P0_8_FNUC << 16) |
               (P0_7_FNUC << 14) |(P0_6_FNUC << 12) | (P0_5_FNUC << 10)|(P0_4_FNUC << 8)  |
               (P0_3_FNUC << 6)  |(P0_2_FNUC << 4)  |(P0_1_FNUC << 2)  |(P0_0_FNUC << 0);

    /*
     * 引脚连接配置P0.16 -- P0.30
     */
    LPC_PINCON->PINSEL1  = (P0_30_FNUC << 28)|(P0_29_FNUC << 26)|(P0_28_FNUC << 24)|(P0_27_FNUC << 22)|
               (P0_26_FNUC << 20)|(P0_25_FNUC <<18) |(P0_24_FNUC <<16) |(P0_23_FNUC <<14) |
               (P0_22_FNUC <<12) |(P0_21_FNUC << 10)|(P0_20_FNUC << 8) |(P0_19_FNUC << 6) |
               (P0_18_FNUC << 4) |(P0_17_FNUC << 2) |(P0_16_FNUC << 0);
    
    /*
     * 引脚连接配置P1.0 -- P1.15
     */
    LPC_PINCON->PINSEL2  = (P1_15_FNUC << 30)|(P1_14_FNUC << 28)|(P1_10_FNUC << 20)|(P1_9_FNUC << 18)|
               (P1_8_FNUC  << 16)|(P1_4_FNUC << 8)  |(P1_1_FNUC << 2)  |(P1_0_FNUC << 0);

    /*
     * 引脚连接配置P1.16 -- P1.31
     */
    LPC_PINCON->PINSEL3  = (P1_31_FNUC << 30)|(P1_30_FNUC << 28)|(P1_29_FNUC << 26)|(P1_28_FNUC << 24)| 
               (P1_27_FNUC << 22)|(P1_26_FNUC << 20)|(P1_25_FNUC << 18)|(P1_24_FNUC << 16)|
               (P1_23_FNUC << 14)|(P1_22_FNUC << 12)|(P1_21_FNUC << 10)|(P1_20_FNUC << 8) |
               (P1_19_FNUC << 6) |(P1_18_FNUC << 4) |(P1_17_FNUC << 2) |(P1_16_FNUC << 0);

    /*
     * 引脚连接配置P2.0 -- P2.13
     */       
    LPC_PINCON->PINSEL4  = (P2_13_FNUC << 26)|(P2_12_FNUC << 24)|(P2_11_FNUC << 22)|(P2_10_FNUC << 20)|
               (P2_9_FNUC << 18) |(P2_8_FNUC  << 16)|(P2_7_FNUC << 14) |(P2_6_FNUC << 12) | 
               (P2_5_FNUC << 10) |(P2_4_FNUC << 8)  |(P2_3_FNUC << 6)  |(P2_2_FNUC << 4)  |
               (P2_1_FNUC << 2)  |(P2_0_FNUC << 0);
    
    /*
     * 引脚连接配置P3.25 -- P3.26
     */
    LPC_PINCON->PINSEL7  = (P3_26_FNUC << 20)|(P3_25_FNUC << 18);

    /*
     * 引脚连接配置P4.28 -- P4.29
     */
    LPC_PINCON->PINSEL9  = (P4_29_FNUC <<26) | (P4_28_FNUC <<24);

    LPC_PINCON->PINSEL10 = P10_3_FNUC;                                              /*  禁止ETM接口功能             */

    /*
     * 引脚内部上下拉电阻配置
     */
    LPC_PINCON->PINMODE0 = (P0_15_MODE << 30)|(P0_14_MODE << 28)|(P0_13_MODE << 26)|(P0_12_MODE << 24)|
               (P0_11_MODE << 22)|(P0_10_MODE << 20)|(P0_9_MODE << 18) |(P0_8_MODE << 16) |
               (P0_7_MODE << 14) |(P0_6_MODE << 12) |(P0_5_MODE << 10) |(P0_4_MODE << 8)  |
               (P0_3_MODE << 6)  |(P0_2_MODE << 4)  |(P0_1_MODE << 2)  |(P0_0_MODE << 0);
    
    LPC_PINCON->PINMODE1 = (P0_30_MODE << 28)|(P0_29_MODE << 26)|(P0_28_MODE << 24)|(P0_27_MODE << 22)|
               (P0_26_MODE << 20)|(P0_25_MODE << 18)|(P0_24_MODE << 16)|(P0_23_MODE << 14)|
               (P0_22_MODE << 12)|(P0_21_MODE <<10) |(P0_20_MODE << 8) |(P0_19_MODE << 6) |
               (P0_18_MODE << 4) |(P0_17_MODE << 2) |(P0_16_MODE << 0);
            
    LPC_PINCON->PINMODE2 = (P1_15_MODE << 30)|(P1_14_MODE << 28)|(P1_13_MODE << 26)|(P1_12_MODE << 24)|
               (P1_11_MODE << 22)|(P1_10_MODE << 20)|(P1_9_MODE << 18) |(P1_8_MODE << 16) |
               (P1_7_MODE << 14) |(P1_6_MODE << 12) |(P1_5_MODE << 10) |(P1_4_MODE << 8)  |
               (P1_3_MODE << 6)  |(P1_2_MODE << 4)  |(P1_1_MODE << 2)  |(P1_0_MODE << 0);
     
    LPC_PINCON->PINMODE3 = (P1_31_MODE << 30)|(P1_30_MODE << 28)|(P1_29_MODE << 26)|(P1_28_MODE << 24)|
               (P1_27_MODE << 22)|(P1_26_MODE << 20)|(P1_25_MODE << 18)|(P1_24_MODE << 16)|
               (P1_23_MODE << 14)|(P1_22_MODE << 12)|(P1_21_MODE << 10)|(P1_20_MODE << 8) |
               (P1_19_MODE << 6) |(P1_18_MODE << 4) |(P1_17_MODE << 2)|(P1_16_MODE << 0);

    LPC_PINCON->PINMODE4 = (P2_15_MODE << 30)|(P2_14_MODE << 28)|(P2_13_MODE << 26)|(P2_12_MODE << 24)|
               (P2_11_MODE << 22)|(P2_10_MODE << 20)|(P2_9_MODE << 18) |(P2_8_MODE << 16) | 
               (P2_7_MODE << 14) |(P2_6_MODE << 12) |(P2_5_MODE << 10) |(P2_4_MODE << 8)  |
               (P2_3_MODE << 6)  |(P2_2_MODE << 4)  |(P2_1_MODE << 2)  |(P2_0_MODE << 0);

    LPC_PINCON->PINMODE7 = (P3_26_MODE << 20)|(P3_25_MODE << 18);
    
    LPC_PINCON->PINMODE9 = (P4_29_MODE << 26)|(P4_28_MODE << 24);

    LPC_GPIO0->FIOMASK =0x00;                                                     /*  不屏蔽引脚高速功能         */
    LPC_GPIO1->FIOMASK =0x00;
    LPC_GPIO2->FIOMASK =0x00;
    LPC_GPIO3->FIOMASK =0x00;
    LPC_GPIO4->FIOMASK =0x00;
}


#if 0


/**
 * @brief  Return the Process Stack Pointer
 *
 * @return ProcessStackPointer
 *
 * Return the actual process stack pointer
 */
uint32_t __get_PSP(void)
{
    uint32_t ret;
    asm volatile ("mrs %0, psp\r\n":"=r"(ret) :);
    return ret;
}

/**
 * @brief  Set the Process Stack Pointer
 *
 * @param  topOfProcStack  Process Stack Pointer
 *
 * Assign the value ProcessStackPointer to the MSP 
 * (process stack pointer) Cortex processor register
 */
void __set_PSP(uint32_t topOfProcStack)
{
    asm volatile ("msr psp, %0\r\n"::"r"(topOfProcStack) );
}

/**
 * @brief  Return the Main Stack Pointer
 *
 * @return Main Stack Pointer
 *
 * Return the current value of the MSP (main stack pointer)
 * Cortex processor register
 */
uint32_t __get_MSP(void)
{
    uint32_t ret;
    asm volatile ("mrs %0, msp\r\n":"=r"(ret) :);
    return ret;
}

/**
 * @brief  Set the Main Stack Pointer
 *
 * @param  topOfMainStack  Main Stack Pointer
 *
 * Assign the value mainStackPointer to the MSP 
 * (main stack pointer) Cortex processor register
 */
void __set_MSP(uint32_t topOfMainStack)
{
    asm volatile ("msr msp, %0\r\n"::"r"(topOfMainStack) );
}

#endif


/*  hardware.c end */

