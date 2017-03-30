
#ifndef __OS_DRIVE_H__
#define __OS_DRIVE_H__

#include "mytype.h"


#define DRIVE_CTRL_GET            1
#define DRIVE_CTRL_SET            2
#define DRIVE_CTRL_TCHAR          3         /*写入单条数据*/
#define DRIVE_CTRL_WRITE          4
#define DRIVE_CTRL_READ           5
#define DRIVE_CTRL_RECT           6         /*读取单条数据*/
#define DRIVE_CTRL_ERAS           7
#define DRIVE_CTRL_ERASPAGE       8
#define DRIVE_CTRL_ERASALL        9


#define OS_MAX(a, b)             (a)>(b)? (a) : (b)
#define OS_MIN(a, b)             (a)<(b)? (a) : (b)

#define OSDRIVE_NAMECNT          8
#define __OSDRIVE__              __attribute__((section(".drive")))

typedef struct _TOSDrive TOSDrive;
typedef void    (*OpenFunc) ( TOSDrive *dev, uint32 flag);
typedef int32  (*ReadFunc) ( TOSDrive *dev, uint32 pos, uint8 *buff, uint32 size);
typedef int32  (*WriteFunc)( TOSDrive *dev, uint32 pos, const uint8 *buff, uint32 size);
typedef int32  (*ContrlFunc)( TOSDrive *dev, uint32 cmd, void *argv );
typedef int     (*CloseFunc)( TOSDrive *dev );

struct _TOSDrive{
    char       name[OSDRIVE_NAMECNT];
    uint8      num;
    uint32     baudrate;
    OpenFunc   open;
    CloseFunc  close;
    ReadFunc   read;
    ContrlFunc contrl;
    WriteFunc  write;
    void      *pdata;
    void      *dev_base;
};

#define __Drive( _name, _baud, _open, _read, _write) \
    TOSDrive _name ## _drive; \
    TOSDrive __OSDRIVE__ _name ## _drive = { \
        .name =   __stringify(_name) , \
        .baudrate =  (_baud), \
        .open =  _open, \
        .read =  (ReadFunc)_read, \
        .write = (WriteFunc)_write};

#define __DriveBegin( _name ) \
    TOSDrive _name ## _drive; \
    TOSDrive __OSDRIVE__ _name ## _drive = { .name = __stringify(_name),


#define __DriveEnd()       };


int   DOpen( const char *name, uint32 flag );
int   DClose( int port );
int32 DRead( int port, uint32 pos, uint8 *buff, uint32 len);
int32 DWrite( int port, uint32 pos, const uint8 *buff, uint32 len);
int32 DContrl( int port, uint32 cmd, void *argv);




#endif


