


#ifndef __THREAD_H__
#define __THREAD_H__


int _pthread( const char *name, void *(*Task)(void*), void *p_arg, int stk_t, int id );
int  pthread( const char *name, void *(*Task)(void*), void *p_arg, int stk_t );



#endif



