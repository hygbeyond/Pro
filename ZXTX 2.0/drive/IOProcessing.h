

#ifndef  __IOPROCESSING_H__
#define  __IOPROCESSING_H__

#include "os_drive.h"

int flashWrite( int port, uint32 pos, const void *pd, int len, int timeout );

int OS_PutBuff(int port, uint32 pos, const void *pd, int len, int timeout );
int OS_GetBuff(int port, uint32 pos, void *pd, int len, int timeout );

#define IO_PutBuff(a,b,c,d )    OS_PutBuff( a, 0, b, c, d)
#define IO_GetBuff(a,b,c,d )    OS_GetBuff( a, 0, b, c, d)



#endif //__IOPROCESSING_H__


