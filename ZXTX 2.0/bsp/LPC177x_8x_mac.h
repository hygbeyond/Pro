

#ifndef __LPC11XX_MAC_H__
#define __LPC11XX_MAC_H__

#include "LPC177x_8x.h"
#include "mytype.h"


#define  PCONP_LCD			BIT(0 )				//LCD����������/ʱ�ӿ���λ��	0	
#define  PCONP_TIM0			BIT(1 )				//��ʱ��/������0����/ʱ�ӿ���λ	1
#define  PCONP_TIM1			BIT(2 )				//��ʱ��/������1����/ʱ�ӿ���λ��	1
#define  PCONP_UART0		BIT(3 )				//UART0����/ʱ�ӿ���λ��	1
#define  PCONP_UART1		BIT(4 )				//UART1����/ʱ�ӿ���λ��	1
#define  PCONP_PWM0			BIT(5 )				//PWM0����/ʱ�ӿ���λ��	0
#define  PCONP_PWM1			BIT(6 )				//PWM1����/ʱ�ӿ���λ��	0
#define  PCONP_I2C0			BIT(7 )				//I2C0�ӿڹ���/ʱ�ӿ���λ��	1
#define  PCONP_UART4		BIT(8 )				//UART4����/ʱ�ӿ���λ��	0
#define  PCONP_RTC			BIT(9 )				//RTC���¼�������/��¼������/ʱ�ӿ���λ��	1
#define  PCONP_SSP1			BIT(10)				//SSP1�ӿڹ���/ʱ�ӿ���λ��	0
#define  PCONP_EMC			BIT(11)				//�ⲿ�洢������������/ʱ�ӿ���λ��	0
#define  PCONP_ADC			BIT(12)				//A/Dת������ADC������/ʱ�ӿ���λ��	0
#define  PCONP_CAN1			BIT(13)				//CAN������1����/ʱ�ӿ���λ��	0
#define  PCONP_CAN2			BIT(14)				//CAN������2����/ʱ�ӿ���λ��	0
#define  PCONP_GPIO			BIT(15)				//IOCON��GPIO��GPIO�жϹ���/ʱ�ӿ���λ��	1
#define  PCONP_NC			BIT(16)				//��������ȡֵδ���壬ֻд��0��	��
#define  PCONP_MCPWM		BIT(17)				//�������PWM����/ʱ�ӿ���λ��	0
#define  PCONP_QEI			BIT(18)				//�����������ӿڹ���/ʱ�ӿ���λ��	0
#define  PCONP_I2C1			BIT(19)				//I2C1�ӿڹ���/ʱ�ӿ���λ��	1
#define  PCONP_SSP2			BIT(20)				//SSP2�ӿڹ���/ʱ�ӿ���λ��	0
#define  PCONP_SSP0			BIT(21)				//SSP0�ӿڹ���/ʱ�ӿ���λ��	0
#define  PCONP_TIM2			BIT(22)				//��ʱ��2����/ʱ�ӿ���λ��	0
#define  PCONP_TIM3			BIT(23)				//��ʱ��3����/ʱ�ӿ���λ��	0
#define  PCONP_UART2		BIT(24)				//UART2����/ʱ�ӿ���λ��	0
#define  PCONP_UART3		BIT(25)				//UART3����/ʱ�ӿ���λ��	0
#define  PCONP_I2C2			BIT(26)				//I2C�ӿ�2����/ʱ�ӿ���λ��	1
#define  PCONP_I2S			BIT(27)				//I2S�ӿڹ���/ʱ�ӿ���λ��	0
#define  PCONP_SDC			BIT(28)				//SD���ӿڹ���/ʱ�ӿ���λ��	0
#define  PCONP_GPDMA		BIT(29)				//GP	DMA���ܹ���/ʱ�ӿ���λ��	0
#define  PCONP_ENET			BIT(30)				//��̫��ģ�鹦��/ʱ�ӿ���λ��	0
#define  PCONP_USB			BIT(31)				//USB�ӿڹ���/ʱ�ӿ���λ��	0


#ifndef BIT
#define BIT(a)             (1<<(a))
#endif

/*
 * λ�����궨����
 */
#ifndef SBI
#define SBI(a, b)          (a) |=  (1<<(b))
#define CBI(a, b)          (a) &= ~(1<<(b))
#define NBI(a, b)          (a) ^=  (1<<(b))
#define PBI(a, b)          ((a) &  (1<<(b))
#endif


#define  D_SETIO( func, mod )         (func&0x7)|(mod<<3) | 0xA0

/*
 * GPIO λ�����궨����,����λ��������Χ�ڣ�ͨ��C����λ������ʽ����
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
 * GPIO λ�����궨�����
 */

#if 1 
/* M3 ֧��λ������
 * λ�������궨����
 * ֧��λ���ڴ淶Χ 0x2000_0000 ~ 0x200F_FFFF �� 0x4000_0000 ~ 0x400F_FFFF
 */
#define AliasAddr(a)               (( volatile uint32_t * )(((a   ) & 0xF0000000) + 0x02000000 + (((a   )&0xFFFFF)<<5) ))
#define BITBAND( addr, bitnum)                             (((addr) & 0xF0000000) + 0x02000000 + (((addr)&0xFFFFF)<<5) + (bitnum<<2))
#define MEM_ADDR( addr )           *(( volatile uint32_t * ) (addr))

/*
 * ����Ϊָ���ַ
 * ���磺MEM_BITBAND(&LPC_UART->LCR, 1) = 1;
 */
#define MEM_BITBAND( addr, bitnum)   AliasAddr( (uint32_t)(addr))[bitnum] 
//#define MEM_BITBAND( addr, bitnum)   MEM_ADDR( BITBAND( (uint32_t)(addr), bitnum))

/*
 * ����Ϊ�Ĵ�����ַָ��
 * ���磺BITBAND_P(LPC_UART->LCR, 1) = 1;
 */
#define BITBAND_P( addr, bitnum)     MEM_ADDR( BITBAND( (uint32_t)&(addr), bitnum) ) /*ͨ��ָ��ķ�ʽʵ��*/
#define BITBAND_V( addr, bitnum)     AliasAddr( (uint32_t)&(addr))[bitnum]           /*ͨ������ķ�ʽʵ��*/
#endif

/*
 * ����ϵͳʱ��ʹ�ܹ��ܣ�ͨ��λ����ʽ�������磺UART
 * SYSAHBCLKCTRL( 12, 1);
 * SYSAHBCLKCTRL_SET( AHBCLK_GPIO );
 * SYSAHBCLKCTRL_CLR( AHBCLK_USB_RGG);
 */
#define SYSAHBCLKCTRL( bit, value )  BITBAND_P( LPC_SYSCON->SYSAHBCLKCTRL, bit ) = value
#define SYSAHBCLKCTRL_SET( bit )     SYSAHBCLKCTRL(  bit, 1 )
#define SYSAHBCLKCTRL_CLR( bit )     SYSAHBCLKCTRL(  bit, 0 )


/*********************************************************************************************************
**  NVIC Interrupt Priority   NVIC�ж����ȼ�
*********************************************************************************************************/
#ifndef PRIO_ZERO
#define PRIO_ZERO            (0x00)                                     /* ���ȼ�Ϊ0                    */
#define PRIO_ONE             (0x01 << 5)                                /* ���ȼ�Ϊ1                    */
#define PRIO_TWO             (0x02 << 5)                                /* ���ȼ�Ϊ2                    */
#define PRIO_THREE           (0x03 << 5)                                /* ���ȼ�Ϊ3                    */
#define PRIO_FOUR            (0x04 << 5)                                /* ���ȼ�Ϊ4                    */
#define PRIO_FIVE            (0x05 << 5)                                /* ���ȼ�Ϊ5                    */
#define PRIO_SIX             (0x06 << 5)                                /* ���ȼ�Ϊ6                    */
#define PRIO_SEVEN           (0x07 << 5)                                /* ���ȼ�Ϊ7                    */
#endif
               


#endif



