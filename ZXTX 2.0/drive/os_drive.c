
#include "mytype.h"
#include "os_drive.h"
#include "OSstring.h"
#include "app_cfg.h"
#include "MicroOS.h"

extern TOSDrive drive_start[];
extern TOSDrive drive_end[];
extern char     drive_size[];
static uint32   drive_cnt = 0;

//#define OSDRIVE_MAX             (((uint32)drive_end - (uint32)drive_start)/ sizeof( TOSDrive))
#define OSDRIVE_MAX               ((uint32)drive_size/ sizeof( TOSDrive ))

static int find( const char *name )
{
    int i;
    if(drive_cnt == 0)
    {
        drive_cnt = OSDRIVE_MAX;
        //pr_debug("drive cnt:%d\n", drive_cnt);
    }
    for(i=0; i<drive_cnt; i++)
    {
        if( !strncmp( drive_start[i].name, name, 8))
        {
            return i+1;
        }
    }
    return -1;
}

int DOpen(const char *name, uint32 flag )
{
    int ret = find(name);
    OpenFunc open;
    if( ret > 0 )
    {
        ret--;
        open = drive_start[ret].open;
        if(open)
        {
            open( &drive_start[ret], flag );
        }
        return ret+1;
    }
    return -1;
}


int32 DRead( int port, uint32 pos, uint8 *buff, uint32 len)
{
    int ret = port;
    if( ret > 0 && ret <= drive_cnt )
    {
        ret--;
        ReadFunc read =  drive_start[ret].read;
        return read==NULL? 0: read(&drive_start[ret], pos, buff, len );
    }
    return -1;
}

int32 DWrite( int port, uint32 pos,const uint8 *buff, uint32 len)
{
    int ret = port;
    WriteFunc write;
    if( ret > 0 && ret <= drive_cnt )
    {
        ret--;
        write =  drive_start[ret].write;
        return write==NULL? 0: write(&drive_start[ret],pos, buff, len );
    }
    return -1;
}

int32 DContrl( int port, uint32 cmd, void *argv)
{
    int ret = port;
    ContrlFunc contrl;
    if( ret > 0 && ret <= drive_cnt )
    {
        ret--;
        contrl =  drive_start[ret].contrl;
        return contrl==NULL? 0: contrl(&drive_start[ret], cmd, argv );
    }
    return -1;
}

int DClose( int port )
{
    int ret = port;
    CloseFunc close;
    if( ret > 0 && ret <= drive_cnt )
    {
        ret--;
        close = drive_start[ret].close;
        return close==NULL? 0: close( &drive_start[ret]);
    }
    return -1;
}


