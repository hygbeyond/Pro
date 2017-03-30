




#include "MicroOS.h"
#include "thread.h"
#include "kmalloc.h"
#include "app_cfg.h"
#include "OSstring.h"

#define THREAD_DBG

int _pthread( const char *name, void *(*Task)(void*), void *p_arg, int stk_t, int id )
{
    int ret;
    int TaskID = id;
    int size;
    OS_STK *pStk;
	OS_SREG_VAR;

	if( TaskID < 0 ) TaskID = OSTaskFindIdleID();
	if( stk_t <= 0 ) stk_t = 256;    
    size = sizeof(OS_STK) * stk_t;

    if( TaskID < 0 || OS_TCBTbl[TaskID].TCBCreate )
        return OS_TASK_RESUME_PRIO;

    pStk = (OS_STK*) OSMalloc( size );	
    if( pStk == NULL) return OS_MEM_FULL;
	
    OSDataClean( pStk, size );
    
	OS_ENTER_CRITICAL();  //保护堆栈转换
    //OSDataClean( &OS_TCBTbl[TaskID], sizeof( OS_TCBTbl[TaskID] ) );	
	OS_TCBTbl[TaskID].OSTaskStackTop = OSTaskStkInit( (TaskFuc)Task, p_arg, &pStk[stk_t-1] );    //将人工堆栈的栈顶，保存到堆栈的数组中
	OS_TCBTbl[TaskID].OSTaskStackEnd = pStk;
	OS_TCBTbl[TaskID].StkSize        = stk_t;
	OS_TCBTbl[TaskID].ID             = TaskID;
    strncpy( OS_TCBTbl[TaskID].name, name, OS_TASKNAME_SIZE-1);
    OS_TCBTbl[TaskID].name[OS_TASKNAME_SIZE-1]=0;
    OS_TCBTbl[TaskID].state = 0x09;
    //OS_TCBTbl[TaskID].TCBCreate = 1;
    //OS_TCBTbl[TaskID].TCBalloc = 1;
    OSRdyTblRdy( TaskID );
	OS_EXIT_CRITICAL();

    ret = OS_NO_ERR;
	if ( OSRunning )
	{
		OSSched();
    }
	return(ret);
}


int pthread( const char *name, void* (*Task)(void*), void *p_arg, int stk_t )
{
	return _pthread( name, Task, p_arg, stk_t, -1 );
}


void OS_TaskClose( uint8 id, uint32 ret )
{
    OS_SREG_VAR;
    if( id >= OS_TASKS ) return;
	OS_TCB *ptcb      = &OS_TCBTbl[id];
    pr_debug("Task ID %d\tname %s close\n", id, ptcb->name );
    OS_ENTER_CRITICAL();
    OSRdyTblWait( id );
    ptcb->TCBReturn  = 1;
    ptcb->OSWaitTick = 0;
    ptcb->TaskRet = ret;
    OS_EXIT_CRITICAL();
    OSSched();
}

void OS_TaskReturn(uint32 ret)
{
	OS_TaskClose( OS_TCBCur->ID, ret);
}

void OS_cmd(void);
void OSTaskDelHook(void)
{
#ifdef THREAD_DBG
	int dbg = 0;
#endif
	int id;
	OS_SREG_VAR;
    OS_TCB       *ptcb;

	for(id=0; id<OS_TASKS; id++)
	{
		if (OS_TCBTbl[id].TCBReturn )
		{
		    ptcb      = &OS_TCBTbl[id];
		    pr_debug("delete Task ID %d\tname %s\n", id, ptcb->name );
			OS_ENTER_CRITICAL();
		    if( OS_TCBTbl[id].TCBalloc )
		    	OSFree( ptcb->OSTaskStackEnd );

            int size = ptcb->TaskSchedCnt;
#ifdef THREAD_DBG
			dbg++;
            OSDataClean( ptcb, sizeof( *ptcb ) );
#else
			ptcb->OSTaskStackEnd = NULL;
			ptcb->OSTaskStackTop = NULL;
			ptcb->StkSize    = 0;
			ptcb->OSWaitTick = 0;
			ptcb->ID         = OS_TASKS;
            ptcb->state      = 0;
			ptcb->name       = NULL;
#endif
            ptcb->TCBDel = 1;
            ptcb->TaskSchedCnt = size;
		    OS_EXIT_CRITICAL();

		}
	}
#ifdef THREAD_DBG
	if(dbg )
	{
		OS_cmd();
	}
#endif
}













