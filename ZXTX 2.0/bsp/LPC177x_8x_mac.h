

#ifndef __LPC11XX_MAC_H__
#define __LPC11XX_MAC_H__

#include "LPC177x_8x.h"
#include "mytype.h"


#define  PCONP_LCD			BIT(0 )				//LCD控制器功率/时钟控制位。	0	
#define  PCONP_TIM0			BIT(1 )				//定时器/计数器0功率/时钟控制位	1
#define  PCONP_TIM1			BIT(2 )				//定时器/计数器1功率/时钟控制位。	1
#define  PCONP_UART0		BIT(3 )				//UART0功率/时钟控制位。	1
#define  PCONP_UART1		BIT(4 )				//UART1功率/时钟控制位。	1
#define  PCONP_PWM0			BIT(5 )				//PWM0功率/时钟控制位。	0
#define  PCONP_PWM1			BIT(6 )				//PWM1功率/时钟控制位。	0
#define  PCONP_I2C0			BIT(7 )				//I2C0接口功率/时钟控制位。	1
#define  PCONP_UART4		BIT(8 )				//UART4功率/时钟控制位。	0
#define  PCONP_RTC			BIT(9 )				//RTC和事件监视器/记录器功率/时钟控制位。	1
#define  PCONP_SSP1			BIT(10)				//SSP1接口功率/时钟控制位。	0
#define  PCONP_EMC			BIT(11)				//外部存储器控制器功率/时钟控制位。	0
#define  PCONP_ADC			BIT(12)				//A/D转换器（ADC）功率/时钟控制位。	0
#define  PCONP_CAN1			BIT(13)				//CAN控制器1功率/时钟控制位。	0
#define  PCONP_CAN2			BIT(14)				//CAN控制器2功率/时钟控制位。	0
#define  PCONP_GPIO			BIT(15)				//IOCON、GPIO和GPIO中断功率/时钟控制位。	1
#define  PCONP_NC			BIT(16)				//保留。读取值未定义，只写入0。	无
#define  PCONP_MCPWM		BIT(17)				//电机控制PWM功率/时钟控制位。	0
#define  PCONP_QEI			BIT(18)				//正交编码器接口功率/时钟控制位。	0
#define  PCONP_I2C1			BIT(19)				//I2C1接口功率/时钟控制位。	1
#define  PCONP_SSP2			BIT(20)				//SSP2接口功率/时钟控制位。	0
#define  PCONP_SSP0			BIT(21)				//SSP0接口功率/时钟控制位。	0
#define  PCONP_TIM2			BIT(22)				//定时器2功率/时钟控制位。	0
#define  PCONP_TIM3			BIT(23)				//定时器3功率/时钟控制位。	0
#define  PCONP_UART2		BIT(24)				//UART2功率/时钟控制位。	0
#define  PCONP_UART3		BIT(25)				//UART3功率/时钟控制位。	0
#define  PCONP_I2C2			BIT(26)				//I2C接口2功率/时钟控制位。	1
#define  PCONP_I2S			BIT(27)				//I2S接口功率/时钟控制位。	0
#define  PCONP_SDC			BIT(28)				//SD卡接口功率/时钟控制位。	0
#define  PCONP_GPDMA		BIT(29)				//GP	DMA功能功率/时钟控制位。	0
#define  PCONP_ENET			BIT(30)				//以太网模块功率/时钟控制位。	0
#define  PCONP_USB			BIT(31)				//USB接口功率/时钟控制位。	0


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


#define  D_SETIO( func, mod )         (func&0x7)|(mod<<3) | 0xA0

/*
 * GPIO 位操作宏定义区,不在位带操作范围内，通过C语言位操作方式操作
 */
#ifndef MYLIB_CONCAT           
#define MYLIB_CONCAT(a, b)            a ## b
#define MYLIB_CONCAT_EXPANDED(a, b)   MYLIB_CONCAT(a, b)
#endif

#ifndef SBI_P
#define PORT(name)                    MYLIB_CONCAT(LPC_GPIO, name)->PIN
#define SET_PORT(name)                MYLIB_CONCAT(LPC_GPIO, name)->SET
#define CLR_PORT(name)                MYLIB_CONCAT(LPC_GPIO, name)->CLR
#define DDRP(name)                    MYLIB_CONCAT(LPC_GPIO, name)->DIR
#define DDRPORT( name )               DDRP( name )
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
#define MEM_BITBAND( addr, bitnum)   AliasAddr( (uint32_t)(addr))[bitnum] 
//#define MEM_BITBAND( addr, bitnum)   MEM_ADDR( BITBAND( (uint32_t)(addr), bitnum))

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
#define SYSAHBCLKCTRL( bit, value )  BITBAND_P( LPC_SYSCON->SYSAHBCLKCTRL, bit ) = value
#define SYSAHBCLKCTRL_SET( bit )     SYSAHBCLKCTRL(  bit, 1 )
#define SYSAHBCLKCTRL_CLR( bit )     SYSAHBCLKCTRL(  bit, 0 )


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



