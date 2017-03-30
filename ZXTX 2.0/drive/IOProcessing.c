

#include "MicroOS.h"
#include "os_drive.h"
#include "IOProcessing.h"
#include "app_cfg.h"

extern TOSDrive drive_start[];
extern TOSDrive drive_end[];
extern char     drive_size[];

//#define OSDRIVE_MAX             (((uint32)drive_end - (uint32)drive_start)/ sizeof( TOSDrive))
#define OSDRIVE_MAX               ((uint32)drive_size/ sizeof( TOSDrive ))

int flashWrite( int port, uint32 pos, const void *pd, int len, int timeout )
{
    int ret;
    int cnt = 0;
    const uint8 *buff = pd;
    uint32 time = ( timeout * HZ )/ 10000;

    while( len > 0 )
    {
        ret = DWrite( port, pos, buff, len );
        if( ret > 0 )
        {
            cnt  += ret;
            len  -= ret;
            buff += ret;
            pos  += ret;
        }
        if( time == 0 )
            break;
#if ( HZ/50) > 0
        OSTimeDly(HZ/50);  //ÑÓÊ±20mS
#else
        OSTimeDly( 1 );
#endif
        time--;
    }
    return cnt;
}

int OS_PutBuff(int port, uint32 pos, const void  *pd, int len, int timeout )
{
    int ret;
    int cnt = 0;
    const uint8 *buff = pd;
    uint32 time = ( timeout * HZ )/ 1000;
    while( len > 0 )
    {
        ret = DWrite( port, pos, buff, len );
        if( ret > 0 )
        {
            cnt  += ret;
            len  -= ret;
            if( len <= 0 )
                return cnt;
            buff += ret;
            pos  += ret;
        }
        if( time == 0 )
            break;
        OSTimeDly(1);
        time--;
    }
    return cnt;
}

int OS_GetBuff(int port, uint32 pos, void *pd, int len , int timeout )
{
    int ret = 0;
    int cnt;
    uint8 *buff = (uint8 *)pd;
    uint32 time = ( timeout * HZ )/ 1000;
    while( len > 0)
    {
        cnt = DRead( port, pos, buff, len );
        if( cnt > 0)
        {
            len  -= cnt;
            ret  += cnt;
            if( len <= 0 )
                return ret;
            buff += cnt;
            pos  += cnt;
        }
        if( time == 0 )
            break;
        OSTimeDly(1);
        time--;
    }
    return ret;
}

#if  SHELL_CMD_DRIVEDEBUG > 0
#include "pcommand.h"
#include "OSstring.h"
static int drive_cmd( int args, char **argv )
{
    static int drive = -1;
    static uint8 buff[32];
    int i;
    int addr = 0;
    int num  = 0;
    if( args >= 3 )
    {
        addr = atoi( argv[2] );
        if(args >= 4 )
        {
            num = atoi( argv[3] );
        }
        if( !strcmp( argv[1], "o" ) )
        {
            drive = DOpen( argv[2], num ) ;
        }else if( !strcmp( argv[1], "r" ) )
        {
            if( (num=OS_GetBuff( drive, addr, buff, sizeof( buff ), HZ )) > 0)
            {
                printk("read %d:", addr );
                for(i=0; i<num; i++) 
                    printk("%02x ", buff[i] );
                printk("\n");
            }else
            {
                printk("read error\n");
            }
        }else if( !strcmp( argv[1], "w" ) )
        {
            for(i=0; i<sizeof( buff); i++)
            {
                buff[i] = num+i;
            }

            if( (num = OS_PutBuff( drive, addr, buff, sizeof( buff), HZ )) > 0 )
            {
                printk("write ok size %d\n" , num);
            }else
                printk("write error\n");
        }else if( !strcmp( argv[1], "c" ) )
        {
            DClose( drive );
            drive = -1;
        }
    }else
    {
        int drive_cnt = OSDRIVE_MAX;
        printk("drive cnt %d\n", drive_cnt);
        for(i=0; i<drive_cnt; i++)
        {
            printk("\t%d:%s\n",i, drive_start[i].name);
        }
    }
    return 0;
}
PSHELL_CMD( dv, drive_cmd, "dv [o|r|w|c] [name|addr] num");
#endif

