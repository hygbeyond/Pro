


#ifndef __BSP_H__
#define __BSP_H__

#include "mytype.h"


#if defined( LPC1778 ) || defined( LPC1788 )
//#warning "cpu  LPC177x_8x"
#include "LPC177x_8x_mac.h"
#include "system_LPC177x_8x.h"

#elif defined( LPC1754 ) || defined( LPC1756 ) || defined( LPC1765 ) || defined( LPC1768 )
//#warning "cpu  LPC17xx"
#include "lpc17xx_mac.h"
#include "system_LPC17xx.h"
#else
#include "lpc17xx_mac.h"
#include "system_LPC17xx.h"
#endif


#ifdef BSP_GLOBAL
#define EXT
#else
#define EXT extern
#endif

/*********************************************************************************************************
  ϵͳʱ������
*********************************************************************************************************/

#define FCCLK                      SystemCoreClock                      /*  ��ʱ��Ƶ��<=100Mhz          */
#define FPCLK                      PeripheralClock                      /*  ����ʱ��Ƶ��,FCCLK��1/2��1/4*/
extern uint16 MemStart;

EXT void BSP_Init      (void);
EXT void BSP_Reset     (void);

#undef EXT
#endif //__BSP_H__



