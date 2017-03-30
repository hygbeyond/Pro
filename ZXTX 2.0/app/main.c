/*
********************************************************************************
**				                   MicroOS(ARM)
**                      The Real-Time Kernel(For ARM cortex-m0)
**
**                     (c) Copyright 2006-2007, hygbeyond
**                             All Rights Reserved
**
**                                    V0.9
**                       基于周立功TinyM0  LPC1114/301
********************************************************************************
**创 建 人：胡勇刚
**文 件 名：main.c
**创建日期：2010-11-23
**描    述：移植到LPC1114，实现了任务切换，shell接口。
**  main源代码，实现了基于MicroOS（ARM）的任务函数。
********************************************************************************
*/

#include "microOS.h"
#include "bsp.h"
#include "app_cfg.h"
#include "thread.h"
#include "kmalloc.h"
#include "pcommand.h"
#include "hardware.h"
#include "os_drive.h"
#include "can_data.h"

#include "proCan.h"
#include "protocol.h"

/*********************************************************************************************************
  宏定义
*********************************************************************************************************/

#define ACPWR_P     0
#define BTPWR_P     1
#define ERROR_P     2
#define ZDGD_P      3


#define DAY_DLY            (24 * 60 * 60)

BJState __NOINIT__  bjstate  ;
int32  __NOINIT__  main_Timeout;
int runDly;     //疏散启动延时, -1为正常状态,


int __NOINIT__ SetAddress;
int __NOINIT__ MKState;
int __NOINIT__ MKStateTrans;
uint8 __NOINIT__ MKIO;
int LED_on;

int can1_port, can2_port, print_port, printk_port;
int r485_port;
int vcom_port;
int fire_port;

int com1_port, com2_port;
int soundEn;
OS_EVENT *BJ_Mbox;
int proCOM_port;

OSTASK_STK( Shell, 192 );     /* shell接口          */


void *vcom_Task(void *pd);
void *trans_Task( void *pd );
void *Tx_Task( void *pd);
void *Rx_Task( void *pd);


int fire_cmd( int argv, char **args );
int reset_cmd( int argv, char **args );
void   GotoISP(void);
//******************************************************************************
void Init_Devices(void);

extern void shell(int ch);

int main (void)
{
    GotoISP();
	OSInit();
    OSTASK_CREATE( Shell, 5 );
    OSStart();
	return 0;
}

/*
 * 功能: shell接口
 */
void Shell_Task(void)
{
    int ret;
    uint8 cmd=0;
    int dly=HZ;
    uint8 buff[8];

    MKState      = 0;
    MKStateTrans = 0;

    Init_Devices();
    OSMalloc_init();

    CanData_Init();
    ProCAN_Init();

    bjstate.trans_state = 0;
    bjstate.cmd = 0;
    if( MemStart != 0x55AA)
    {
        SetAddress = 0;
        MemStart = 0x55AA;
    }

    BJ_Mbox      = OSMboxCreate(&cmd);
    ASSERT(BJ_Mbox);
    DEBUG0("RSID %08x\n", (int)LPC_SC->RSID);
    LPC_SC->RSID = 0x0F;
    //创建线程

    _pthread( "Tx", Tx_Task, NULL, 128, 1 );
    _pthread( "Rx", Rx_Task, NULL, 128, 0 );
    _pthread( "trans", trans_Task, NULL, 128, 2 );
    _pthread( "Vcom", vcom_Task, NULL, 128, 3 );

    printk( VERSION_STR " modbus" \
            "\ncmd>"
          );

    while( 1 ){

        ret = DRead( printk_port, 0, buff, sizeof(buff));
        for(int i=0; i<ret; i++ )
        {
            shell( buff[i] );
        }

        OSTimeDly( 1 );

        if(LED_on)
        {
        	LED_on--;
        	LED_ON;
        }else
        	LED_OFF;
        if( --dly == 0 )
        {
        	dly = HZ;
//        	LED_NOT;
        }
    }
}


void *vcom_Task(void *pd)
{
    int time = 0;
    int port;
    uint8 buff[8];
    OSTimeDly(HZ);
    vcom_port = DOpen( "VCOM", 9600);
    pr_debug("vcom 线程\n");
    while(1)
    {
        port = vcom_port;
        int ret = DRead( port, 0, buff, sizeof(buff));
        for(int i=0; i<ret; i++ )
        {
            if( ProCAN_Rect( buff[i] ) )
                proCOM_port = 2;
        }
        if( proCOM_port == 2 )
        {
            if( ProCAN_Trans( port ) )
            {
                time = HZ*30;
            }

            if (time)
			{
				time--;
				if (time == 0)
				{
					reset_cmd(0, 0);
				}
			}
        }
        OSTimeDly(1);
    }
}

void *trans_Task( void *pd )
{
    int time = 0;
    int port;
    uint8 buff[8];
    OSTimeDly(HZ);
    pr_debug("发送数据线程\n");
    //IO_PutBuff( r485_port, (uint8*) "你好\r\n", 6, 1000 );
    while(1)
    {
        port = r485_port;
        int ret = DRead( port, 0, buff, sizeof(buff));
        for(int i=0; i<ret; i++ )
        {
            if( ProCAN_Rect( buff[i] ) )
                proCOM_port = 1;
        }
        if( proCOM_port == 1 )
        {
            if( ProCAN_Trans( port ) )
            {
                time = HZ*30;
            }
            if (time)
			{
				time--;
				if (time == 0)
				{
					reset_cmd(0, 0);
				}
			}
        }
        OSTimeDly(1);

    }
}


void *Tx_Task( void *pd)
{
    static CAN_msg TxMsg2, TxMsg;
    int time = HZ;
    OSTimeDly(HZ);
    TxMsg2.Frame = 0;
    TxMsg.Frame = 0;
    while( 1 )
    {
        if( TxMsg2.Frame == 0 ) {
            CanData_Get( 1, &TxMsg2 );
        }else {
            if( DWrite( can2_port, 0, (uint8*) &TxMsg2, 1 ) > 0 )
            {
                TxMsg2.Frame = 0;
            }
        }

        if( TxMsg.Frame == 0 ){
            CanData_Get( 0, &TxMsg );
        }else{
            if( DWrite( can1_port, 0, (uint8*) &TxMsg, 1 ) > 0)
            {
                TxMsg.Frame = 0;
            }
        }
        OSTimeDly( 1 );

        time--;
        if( time == 0)
        {
            time = 5*HZ;
        }
    }
}

#define PRINTK_PORT           0
void *Rx_Task( void *pd )
{
    static CAN_msg msg;

    while( 1 )
    {
        if( DRead( can1_port, 0,(uint8*) &msg, 1 ) > 0)
        {
//            LEDCOM_NOT;
            DEBUG2("can1 %x, %08x\t%08x\n", msg.id, msg.DataA, msg.DataB );
            ProCAN_Add(0, &msg );
        }

        if( DRead( can2_port, 0, (uint8*) &msg, 1 ) > 0 )
        {
//            LEDCOM_NOT;
            DEBUG2("can2 %x, %08x\t%08x\n", msg.id, msg.DataA, msg.DataB );
            ProCAN_Add(1, &msg );
        }

        OSTimeDly(1);
    }
}


static int printk_put( int ch, FILE * p_file)
{
    return DContrl( printk_port, DRIVE_CTRL_TCHAR, &ch );
}

static int printk_get( FILE *p_file )
{
    return DContrl( printk_port, DRIVE_CTRL_RECT, NULL );
}

/*
 * 初始化硬件
 */
void Init_Devices(void)
{
    OS_SREG_VAR;
    OS_ENTER_CRITICAL();
    BSP_Init();
    OS_CPU_SysTickInit( FCCLK/HZ );
    OS_EXIT_CRITICAL();

#if OS_STAT_EN > 0
    OSStatInit();
#endif

    IO_init();

//    printk_port = DOpen( "uart0", 115200 );
//    r485_port   = DOpen( "uart2", 38400);

    printk_port = DOpen( "uart2", 115200 );
    r485_port   = DOpen( "uart0", 38400);
    printk_set( printk_put, printk_get );
    ASSERT( r485_port >= 0 );

    can1_port  = DOpen( "CAN1", 10000);
    ASSERT( can1_port >= 0 );
    can2_port  = DOpen( "CAN2", 10000);
    ASSERT( can2_port >= 0 );


    com1_port = -1;
    com2_port = -1;
    pr_debug("init device\n");

}

int reset_cmd( int argv, char **args )
{
	MemStart = 0;
    BSP_Reset();
    return 0;
}
PSHELL_CMD( reset, reset_cmd, "reset");

/*
 * 最低任务钩子函数，主要是低功耗控制
 */
#if OS_TASK_HOOK_EN > 0
void OS_TaskIdle_Hook(void)
{
#if OS_STAT_EN > 0
#else
    __WFI();
#endif
}
#endif 

/*********************************************************************************************************
  End File
*********************************************************************************************************/

