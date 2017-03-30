
#ifndef __KMALLOC_H__
#define __KMALLOC_H__

#undef malloc
#undef realloc
#undef free

#define malloc  OSMalloc
#define realloc OSRealloc
#define free    OSFree

void  OSMalloc_init( void );
void *OSMalloc(size_t size );
void *OSRalloc( void *mem, size_t size );
void  OSFree( void *mem );
int   OSMallocSize( void *mem );


#endif

