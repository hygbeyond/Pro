
#ifndef __APP_CFG_H__
#define __APP_CFG_H__

#include "mytype.h"
#include "printk.h"
#include "OSstdio.h"
#include "OSstdlib.h"
#include "OSstring.h"
#include "MicroOS.h"
#include "thread.h"

#ifndef MAX_POIN
#define MAX_POIN   110
#endif

#ifndef DEBUG
#define DEBUG  1
#endif

#ifndef EN_CRP
#define EN_CRP 1
#endif


#define   MAX_LOOP                      20
#define   LOOP_DOOR_SIZE                200


#define   DATA_GZ_DX_CNT                3     /*报掉线需要连续接收不到数据的数量*/

#define   MAX_POINT_COUNT               MAX_POINT
#define   CMD_BUFF_SIZE                 512 
#define   CANCMD_BUFF_SIZE              256

#define   APP_NAME                      __stringify(HNAME)

#define   TRACE                         pr_debug



#ifndef VERSION_STR
#define VERSION_STR    __stringify(HNAME) " " __stringify(VERSION) "." __stringify( PATCHLEVEL )
#endif

#define   UART_BPS                      115200
#define   CAN_MAX_PORTS                 1

#define   SHELL_CMD_RESET               1
#define   SHELL_CMD_USER                1
#define   SHELL_CMD_TIME                1
#define   SHELL_CMD_IAP                 0
#define   SHELL_CMD_DATA                1
#define   SHELL_CMD_DRIVEDEBUG          1
#define   SHELL_CMD_IO                  0

#define GZ_CALL        4
#define BJ_CALL        5

typedef struct {
    union{
        uint16 enable;
        struct{
        	uint16 relay_En :1;      //手动状态
        	uint16 call_en  :1;      //报警声音状态
        	uint16 saveDis  :1;      //停止报警保存
        	uint16 Fire     :1;      //火警
        	uint16 YJ_en    :1;      //应急信号已经发送
        	uint16 BDGZEn   :1;      //电池故障发送
        	uint16 ZDGZEn   :1;      //主电故障发送

        };
    };
    union{
    	uint16 trans_state;
    	struct
		{
    		uint16 :1;
    		uint16 GZ:1;//故障
    		uint16 BJ:1;//报警
    		uint16 ZDGZ     :1;      //主电故障
    		uint16 BDGZ     :1;      //电池故障
    		uint16 ZXDL     :1;      //总线短路
    		uint16 RESET    :1;      //复位
    		uint16 KJ       :1;      //开机
    		uint16 QDLED:1;
    		uint16 ONLED:1;
    		uint16 OFFLED:1;
		};
    };
    uint8 call_state;    //报警声音类型
    uint8 state;         //报警状态
    uint8 TransTimeout;
    uint8 LocalAuto;
    uint8 cmd;
    uint8  TTaddr;
    uint16 addr;
}BJState,*PBJState;

extern BJState  bjstate  ;

extern int can1_port, can2_port, print_port, printk_port;
extern int r485_port;
extern int fire_port;
extern int com1_port, com2_port;
extern int runDly;

extern uint32 AutoProc_time;
extern uint32 UserSave_time;
#define  AUTOPROC()                    //AutoProc_time = 2*20
#define  USERSAVE()                    //UserSave_time = 2 * 5;

extern OS_EVENT *Key_Mbox;        //键盘输入邮箱
extern OS_EVENT *Process_Mbox;    //处理通信邮箱
extern OS_EVENT *File_Mbox;       //报警数据存储读取邮箱
extern OS_EVENT *BJ_Mbox;         //报警处理邮箱


                                /* -------------------- BIT DEFINES ------------------- */
#define  DEF_BIT_NONE                                   0x00

#define  DEF_BIT_00                                     0x01
#define  DEF_BIT_01                                     0x02
#define  DEF_BIT_02                                     0x04
#define  DEF_BIT_03                                     0x08
#define  DEF_BIT_04                                     0x10
#define  DEF_BIT_05                                     0x20
#define  DEF_BIT_06                                     0x40
#define  DEF_BIT_07                                     0x80

#define  DEF_BIT_08                                   0x0100
#define  DEF_BIT_09                                   0x0200
#define  DEF_BIT_10                                   0x0400
#define  DEF_BIT_11                                   0x0800
#define  DEF_BIT_12                                   0x1000
#define  DEF_BIT_13                                   0x2000
#define  DEF_BIT_14                                   0x4000
#define  DEF_BIT_15                                   0x8000

#define  DEF_BIT_16                               0x00010000
#define  DEF_BIT_17                               0x00020000
#define  DEF_BIT_18                               0x00040000
#define  DEF_BIT_19                               0x00080000
#define  DEF_BIT_20                               0x00100000
#define  DEF_BIT_21                               0x00200000
#define  DEF_BIT_22                               0x00400000
#define  DEF_BIT_23                               0x00800000

#define  DEF_BIT_24                               0x01000000
#define  DEF_BIT_25                               0x02000000
#define  DEF_BIT_26                               0x04000000
#define  DEF_BIT_27                               0x08000000
#define  DEF_BIT_28                               0x10000000
#define  DEF_BIT_29                               0x20000000
#define  DEF_BIT_30                               0x40000000
#define  DEF_BIT_31                               0x80000000


extern uint32 debug_en;
int dbg_print( const char *fmt, ... );
#define DEBUG_PRINT                      dbg_print

#if DEBUG
#define DEBUG0(...)       do{if( debug_en & DEF_BIT_00 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG1(...)       do{if( debug_en & DEF_BIT_01 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG2(...)       do{if( debug_en & DEF_BIT_02 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG3(...)       do{if( debug_en & DEF_BIT_03 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG4(...)       do{if( debug_en & DEF_BIT_04 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG5(...)       do{if( debug_en & DEF_BIT_05 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG6(...)       do{if( debug_en & DEF_BIT_06 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG7(...)       do{if( debug_en & DEF_BIT_07 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG8(...)       do{if( debug_en & DEF_BIT_08 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG9(...)       do{if( debug_en & DEF_BIT_09 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG10(...)      do{if( debug_en & DEF_BIT_10 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG11(...)      do{if( debug_en & DEF_BIT_11 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG12(...)      do{if( debug_en & DEF_BIT_12 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG13(...)      do{if( debug_en & DEF_BIT_13 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG14(...)      do{if( debug_en & DEF_BIT_14 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG15(...)      do{if( debug_en & DEF_BIT_15 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG16(...)      do{if( debug_en & DEF_BIT_16 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG17(...)      do{if( debug_en & DEF_BIT_17 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG18(...)      do{if( debug_en & DEF_BIT_18 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG19(...)      do{if( debug_en & DEF_BIT_19 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG20(...)      do{if( debug_en & DEF_BIT_20 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG21(...)      do{if( debug_en & DEF_BIT_21 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG22(...)      do{if( debug_en & DEF_BIT_22 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG23(...)      do{if( debug_en & DEF_BIT_23 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG24(...)      do{if( debug_en & DEF_BIT_24 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG25(...)      do{if( debug_en & DEF_BIT_25 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG26(...)      do{if( debug_en & DEF_BIT_26 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG27(...)      do{if( debug_en & DEF_BIT_27 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG28(...)      do{if( debug_en & DEF_BIT_28 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG29(...)      do{if( debug_en & DEF_BIT_29 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG30(...)      do{if( debug_en & DEF_BIT_30 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG31(...)      do{if( debug_en & DEF_BIT_31 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#else
#define DEBUG0(...)       do{if( debug_en & DEF_BIT_00 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG1(...)       do{if( debug_en & DEF_BIT_01 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG2(...)       do{if( debug_en & DEF_BIT_02 ) DEBUG_PRINT(__VA_ARGS__);}while(0)
#define DEBUG3(...)        
#define DEBUG4(...)        
#define DEBUG5(...)       
#define DEBUG6(...)       
#define DEBUG7(...)       
#define DEBUG8(...)       
#define DEBUG9(...)       
#define DEBUG10(...)      
#define DEBUG11(...)      
#define DEBUG12(...)      
#define DEBUG13(...)      
#define DEBUG14(...)      
#define DEBUG15(...)      
#define DEBUG16(...)      
#define DEBUG17(...)      
#define DEBUG18(...)      
#define DEBUG19(...)      
#define DEBUG20(...)      
#define DEBUG21(...)      
#define DEBUG22(...)      
#define DEBUG23(...)      
#define DEBUG24(...)      
#define DEBUG25(...)      
#define DEBUG26(...)      
#define DEBUG27(...)      
#define DEBUG28(...)      
#define DEBUG29(...)      
#define DEBUG30(...)      
#define DEBUG31(...)      
#endif


#define   UART_BPS                   115200
#define   MAX_SVC_SIZE               128

#define   MAX_CAN_RX_SIZE            32



#endif
 
 
 
 
 
 
 
 
 
 
