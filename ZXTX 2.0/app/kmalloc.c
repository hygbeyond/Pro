

#include "MicroOS.h"
#include "OSmalloc.h"
#include "app_cfg.h"
#include "kmalloc.h"

OS_EVENT *OSSemMalloc;

extern uint8 _end[];
extern uint8 _ram_top[];

#define EMC_Data            ((volatile uint8 *) 0x80000000 )
extern uint8 __ExRAM[];
extern uint8 __ExRAM_end[];

void OSMalloc_init( void )
{
    OSSemMalloc= OSSemCreate( 1 );
    ASSERT( OSSemMalloc );
    
//#if defined( LPC1778 ) || defined( LPC1788 )
//    heap_init( __ExRAM, __ExRAM_end );
//    #warning "malloc  LPC177x_8x  __ExRAM"
//#else
    OS_heap_init( _end, _ram_top );
//#endif
}

void *OSMalloc(size_t size )
{
	void *ret = NULL;
	if (OSSemPend(OSSemMalloc, 0) == OS_NO_ERR) {
		ret = OS_malloc(size);
		OSSemPost(OSSemMalloc);
	}
	return ret;
}

void *OSRalloc(void *rmem, size_t size) {
	void *ret = NULL;
	if (OSSemPend(OSSemMalloc, 0) == OS_NO_ERR) {
		ret = OS_realloc(rmem, size);
		OSSemPost(OSSemMalloc);
	}
	return ret;
}

int OSMallocSize(void *mem) {
	return OS_malloc_size(mem);
}


void OSFree( void *mem )
{
    OSSemPend( OSSemMalloc, 0 );
    OS_free( mem );
    OSSemPost( OSSemMalloc );
}




