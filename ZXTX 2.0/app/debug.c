

#include "mytype.h"
#include "pcommand.h"
#include "printk.h"
#include "MicroOS.h"
#include "bsp.h"
#include "app_cfg.h"
#include "IOProcessing.h"


uint32 debug_en = 3;


int dbg_print( const char *fmt, ... )
{
	va_list ap;
	int i;
	static char buff[64];
	uint8 *str = (uint8*)buff;
	va_start(ap, fmt);
	i = vsnprintf(buff, 64, fmt, ap);
	va_end(ap);

	OS_PutBuff(printk_port, 0, str, i, HZ );
	return 1;
}

static int debug_cmd( int args, char **argv )
{
    if( args > 2 )
    {
        int num = atoi( argv[2] );
        if(!strcmp(argv[1], "en"))
        {
            if( num > 31 )
                num = 31;
            debug_en |= (1<<num);
        }else if(!strcmp(argv[1], "dis"))
        {
            if( num > 31 )
                num = 31;
            debug_en &= ~(1<<num);
        }else if(!strcmp(argv[1], "set"))
        {
            debug_en = num;
        }
    }else
    {
    	dbg_print("debug [en|dis|set] num 0x%08x\n", debug_en);
    }
    return 0;
}
PSHELL_CMD( debug, debug_cmd, "debug [en|dis|set] numb");

void OS_cmd( void );
void OS_cmd( void )
 {
	int i, j;
	/* ��ӡMicroOS�İ汾�� */
	dbg_print("  MicroOS  : V%d.%02d\n", OS_VERSION, OS_PATCHLEVEL);

	/* ��ӡ�δ����������ʣ���ÿ����ٴ����� */
	dbg_print("  TickRate  : %d\n", OS_TICKS_PER_SEC);

#if OS_STAT_EN > 0
	/* ��ӡCPUռ���� */
	dbg_print("  CPU Usage : %02d%%\n", OSCPUUsage);
#endif

	/* ��ӡCPU�ٶ� */
	dbg_print("  CPU Speed : %d MHz\n", (int)(FCCLK / 1000000L));

	/* ��ӡCPU������ʱ�䣨��λ���δ�) */
	dbg_print("  #Ticks    : %d\n", OSTimeCnt);

	/* ��ӡ�������л����� (context switches) */
	dbg_print("  #CtxSw    : %d\n", OSCtxSwCtr);

	dbg_print("����\tID��\t��ջ����\t��ջʹ��\t���д���\n");
	for (i = 0; i <= OS_TASKS; i++) {
		OS_STK *stk = OS_TCBTbl[i].OSTaskStackEnd;
		int size = OS_TCBTbl[i].StkSize;
		if (size) {
			dbg_print("%-5s\t%-4d\t", OS_TCBTbl[i].name, OS_TCBTbl[i].ID);
			for (j = 0; j < size; j++) {
				if (*stk++ != 0)
					break;
			}
			dbg_print("%-5d\t%5d%%\t%-5d\n", size, (size - j) * 100 / size,
					OS_TCBTbl[i].TaskSchedCnt);
		}
	}
}
PSHELL_CMD( os, OS_cmd, "os");

void OSTaskStatHook(void)
{
//	static int i=0;
//	const char *str = "-\\|/";
	DEBUG9("CPU Usage : %02d%%\n", OSCPUUsage);
//	if( i>3 ) i=0;
}


#if SHELL_CMD_IO > 0
static void out_cmd( int args, char **argv )
{
    volatile uint32 *pd = (uint32*)atoi( argv[1] );
    printk("out 0x%08x\t0x%08x\n", (uint32)pd, *pd );
}
PSHELL_CMD( out, out_cmd,  "out regs" );

static void in_cmd( int args, char **argv )
{
    volatile uint32 *pd = (uint32*)atoi( argv[1] );
    uint32  cnt= atoi( argv[2] );
    if( args >= 3 )
    {
        *pd = cnt;
        printk("out 0x%08x\n", *pd );
    }
}
PSHELL_CMD( in, in_cmd,  "in regs" );
#endif

static int version_cmd( int argv, char **args )
{
    printk( __stringify(HNAME) " " __stringify(VERSION) "." __stringify( PATCHLEVEL ) "." __stringify( MAX_POINT_COUNT )  "\n" );
    return 0;
}
PSHELL_CMD( version, version_cmd, "version");

