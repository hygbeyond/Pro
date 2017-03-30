

#ifndef __LPC11XX_MAC_H__
#define __LPC11XX_MAC_H__

#include "mytype.h"
#include "LPC17xx.h"


/*
 * 功率控制
 */
#define PCONP_TIM0          BIT( 1  )
#define PCONP_TIM1          BIT( 2  )
#define PCONP_UART0         BIT( 3  )
#define PCONP_UART1         BIT( 4  )
#define PCONP_PWM1          BIT( 6  )
#define PCONP_I2C0          BIT( 7  )
#define PCONP_SPI           BIT( 8  )
#define PCONP_RTC           BIT( 9  )
#define PCONP_SSP1          BIT( 10 )
#define PCONP_AD            BIT( 12 )
#define PCONP_CAN1          BIT( 13 )
#define PCONP_CAN2          BIT( 14 )
#define PCONP_GPIO          BIT( 15 )
#define PCONP_RIT           BIT( 16 )
#define PCONP_MC            BIT( 17 )
#define PCONP_QEI           BIT( 18 )
#define PCONP_I2C1          BIT( 19 )
#define PCONP_SSP0          BIT( 21 )
#define PCONP_TIM2          BIT( 22 )
#define PCONP_TIM3          BIT( 23 )
#define PCONP_UART2         BIT( 24 )
#define PCONP_UART3         BIT( 25 )
#define PCONP_I2C2          BIT( 26 )
#define PCONP_I2S           BIT( 27 )
#define PCONP_GPDMA         BIT( 29 )
#define PCONP_ENET          BIT( 30 )
#define PCONP_USB           BIT( 31 )


                                                                /* -------------- INTERRUPT SOURCE ------------------ */
#define  BSP_INT_SRC_NBR_WDT                                0   /* Watchdog                                           */
#define  BSP_INT_SRC_NBR_TMR0                               1   /* Timer 0 (Match 0-3 Capture 0-3)                    */
#define  BSP_INT_SRC_NBR_TMR1                               2   /* Timer 1 (Match 0-3 Capture 0-3)                    */
#define  BSP_INT_SRC_NBR_TMR2                               3   /* Timer 2 (Match 0-3 Capture 0-3)                    */
#define  BSP_INT_SRC_NBR_TMR3                               4   /* Timer 2 (Match 0-3 Capture 0-3)                    */
#define  BSP_INT_SRC_NBR_UART0                              5   /* UART 0  (RLS, THRE, RDA, CTI)                      */
#define  BSP_INT_SRC_NBR_UART1                              6   /* UART 1  (RLS, THRE, RDA, CTI, MSI)                 */
#define  BSP_INT_SRC_NBR_UART2                              7   /* UART 1  (RLS, THRE, RDA, CTI, MSI)                 */
#define  BSP_INT_SRC_NBR_UART3                              8   /* UART 1  (RLS, THRE, RDA, CTI, MSI)                 */
#define  BSP_INT_SRC_NBR_PWM1                               9   /* PWM 1   (Match 0-6 Capture 0-3)                    */
#define  BSP_INT_SRC_NBR_I2C0                              10   /* I2C     (SI)                                       */
#define  BSP_INT_SRC_NBR_I2C1                              11   /* I2C     (SI)                                       */
#define  BSP_INT_SRC_NBR_I2C2                              12   /* I2C     (SI)                                       */
#define  BSP_INT_SRC_NBR_SPI0                              13   /* SPI0    (SPIF, MODF)                               */
#define  BSP_INT_SRC_NBR_SSP0                              14   /* SSP0    Tx/Rx FIFO Int. Rx Timeout/Overrun         */
#define  BSP_INT_SRC_NBR_SSP1                              14   /* SSP1    Tx/Rx FIFO Int. Rx Timeout/Overrun         */
#define  BSP_INT_SRC_NBR_PLL0                              16   /* PLL lock (PLOCK)                                   */
#define  BSP_INT_SRC_NBR_RTC                               17   /* RTC     (RTCCIF, RTCALF)                           */
#define  BSP_INT_SRC_NBR_EINT0                             18   /* External interrupt 0 (EINT0)                       */
#define  BSP_INT_SRC_NBR_EINT1                             19   /* External interrupt 1 (EINT1)                       */
#define  BSP_INT_SRC_NBR_EINT2                             20   /* External interrupt 2 (EINT2)                       */
#define  BSP_INT_SRC_NBR_EINT3                             21   /* External interrupt 3 (EINT3)                       */
#define  BSP_INT_SRC_NBR_ADC0                              22   /* A/D Converter 0 end of conversion                  */
#define  BSP_INT_SRC_NBR_BOD                               23   /* Brown out detect                                   */
#define  BSP_INT_SRC_NBR_USB                               24   /* USB Interrupts, DMA Interrupt                      */
#define  BSP_INT_SRC_NBR_CAN                               25   /* CAN Interrupt                                      */
#define  BSP_INT_SRC_NBR_GPDMA                             26   /* IntSattus of DMA channel 0/1                       */
#define  BSP_INT_SRC_NBR_I2S                               27   /* SI (state change)                                  */
#define  BSP_INT_SRC_NBR_EMAC                              28   /* Ethernet Interrupt                                 */
#define  BSP_INT_SRC_NBR_RITINT                            28   /* Repetitive interrupt timer                         */
#define  BSP_INT_SRC_NBR_MOTOR_PWM                         29   /* Motor Control PWM                                  */
#define  BSP_INT_SRC_NBR_QUAD_ENCODER                      30   /* Quadrature Encoder                                 */
#define  BSP_INT_SRC_NBR_PLL1                              31   /* PLL1 lock (PLOCK)                                  */
#define  BSP_INT_SRC_NBR_USB_ACT                           32   /* USB Activity                                       */
#define  BSP_INT_SRC_NBR_CAN_ACT                           33   /* CAN Activity                                       */

#ifndef BIT
#define BIT(a)             (1<<(a))
#endif

/*
 * 位操作宏定义区
 */
#ifndef SBI
#define SBI(a, b)          (a) |=  (1<<(b))
#define CBI(a, b)          (a) &= ~(1<<(b))
#define NBI(a, b)          (a) ^=  (1<<(b))
#define PBI(a, b)          ((a) &  (1<<(b))
#endif


/*
 * GPIO 位操作宏定义区,不在位带操作范围内，通过C语言位操作方式操作
 */
#ifndef MYLIB_CONCAT           
#define MYLIB_CONCAT(a, b)            a ## b
#define MYLIB_CONCAT_EXPANDED(a, b)   MYLIB_CONCAT(a, b)
#endif

#ifndef SBI_P
#define PORT(name)                    MYLIB_CONCAT(LPC_GPIO, name)->FIOPIN
#define SET_PORT(name)                MYLIB_CONCAT(LPC_GPIO, name)->FIOSET
#define CLR_PORT(name)                MYLIB_CONCAT(LPC_GPIO, name)->FIOCLR
#define DDRP(name)                    MYLIB_CONCAT(LPC_GPIO, name)->FIODIR
#define DDRPORT( name )               DDRP( name )
#define DIRPORT( name )               DDRP( name )
#define CLRPORT( name )               CLR_PORT( name )
#define SETPORT( name )               SET_PORT( name )
#define INPORT( name )                PORT( name )

#define PIN(name )                    PORT(name)

#define PORT_IN( pin, bit )           CBI( DDRP( pin ), bit)
#define PORT_OUT( pin, bit)           SBI( DDRP( pin ), bit)
#define PBI_P(pin, bit)               PBI( PORT( pin ), bit)
#define NBI_P(pin, bit)               if(PBI_P(pin,bit)) { CBI_P(pin,bit); } else { SBI_P(pin,bit); }
#define SBI_P(pin, bit)               SET_PORT(pin) = BIT(bit)
#define CBI_P(pin, bit)               CLR_PORT(pin) = BIT(bit)
#endif
/*
 * GPIO 位操作宏定义结束
 */

#if 1 
/* M3 支持位带操作
 * 位带操作宏定义区
 * 支持位带内存范围 0x2000_0000 ~ 0x200F_FFFF 及 0x4000_0000 ~ 0x400F_FFFF
 */
#define AliasAddr(a)               (( volatile uint32_t * )(((a   ) & 0xF0000000) + 0x02000000 + (((a   )&0xFFFFF)<<5) ))
#define BITBAND( addr, bitnum)                             (((addr) & 0xF0000000) + 0x02000000 + (((addr)&0xFFFFF)<<5) + (bitnum<<2))
#define MEM_ADDR( addr )           *(( volatile uint32_t * ) (addr))

/*
 * 输入为指针地址
 * 例如：MEM_BITBAND(&LPC_UART->LCR, 1) = 1;
 */
#define MEM_BITBAND( addr, bitnum)   MEM_ADDR( BITBAND( (uint32_t)(addr), bitnum))

/*
 * 输入为寄存器地址指针
 * 例如：BITBAND_P(LPC_UART->LCR, 1) = 1;
 */
#define BITBAND_P( addr, bitnum)     MEM_ADDR( BITBAND( (uint32_t)&(addr), bitnum) ) /*通过指针的方式实现*/
#define BITBAND_V( addr, bitnum)     AliasAddr( (uint32_t)&(addr))[bitnum]           /*通过数组的方式实现*/
#endif

/*
 * 设置系统时钟使能功能，通过位带方式操作，如：UART
 * SYSAHBCLKCTRL( 12, 1);
 * SYSAHBCLKCTRL_SET( AHBCLK_GPIO );
 * SYSAHBCLKCTRL_CLR( AHBCLK_USB_RGG);
 */
//#define SYSAHBCLKCTRL( bit, value )  BITBAND_P( LPC_SYSCON->SYSAHBCLKCTRL, bit ) = value
#define SYSAHBCLKCTRL_SET( bit )     SBI( LPC_SYSCON->SYSAHBCLKCTRL, bit )
#define SYSAHBCLKCTRL_CLR( bit )     CBI( LPC_SYSCON->SYSAHBCLKCTRL, bit )

#define AHBCLK_SYS                           0 
#define AHBCLK_ROM                           1
#define AHBCLK_RAM                           2 
#define AHBCLK_FLASH1                        3 
#define AHBCLK_FLASH2                        4
#define AHBCLK_I2C                           5 
#define AHBCLK_GPIO                          6
#define AHBCLK_CT16B0                        7
#define AHBCLK_CT16B1                        8
#define AHBCLK_CT32B0                        9
#define AHBCLK_CT32B1                        10
#define AHBCLK_SSP0                          11
#define AHBCLK_UART                          12
#define AHBCLK_ADC                           13
#define AHBCLK_USB_RGG                       14
#define AHBCLK_WDT                           15
#define AHBCLK_IOCON                         16
#define AHBCLK_SSP1                          18


/*********************************************************************************************************
**  NVIC Interrupt Priority   NVIC中断优先级
*********************************************************************************************************/
#ifndef PRIO_ZERO
#define PRIO_ZERO            (0x00)                                     /* 优先级为0                    */
#define PRIO_ONE             (0x01 << 5)                                /* 优先级为1                    */
#define PRIO_TWO             (0x02 << 5)                                /* 优先级为2                    */
#define PRIO_THREE           (0x03 << 5)                                /* 优先级为3                    */
#define PRIO_FOUR            (0x04 << 5)                                /* 优先级为4                    */
#define PRIO_FIVE            (0x05 << 5)                                /* 优先级为5                    */
#define PRIO_SIX             (0x06 << 5)                                /* 优先级为6                    */
#define PRIO_SEVEN           (0x07 << 5)                                /* 优先级为7                    */
#endif
               


#endif




