
#include <stdio.h>
#include "los_typedef.h"
#include "los_task.h"

void TaskDelay(int time)
{
    LOS_TaskDelay(time);
    return;
}

UINT32 creat_maintask(const char *taskname,TSK_ENTRY_FUNC fnTask,UINT32 stackisize,UINT32 uwArg,UINT16 prior)
{
    UINT32 uwRet = LOS_OK;
	UINT32  handle;
    TSK_INIT_PARAM_S task_init_param;
	
    task_init_param.uwArg = uwArg;
    task_init_param.usTaskPrio = prior;
    task_init_param.pcName =(char *) taskname;
    task_init_param.pfnTaskEntry = fnTask;
    task_init_param.uwStackSize = stackisize;
    uwRet = LOS_TaskCreate(&handle, &task_init_param);
    if(LOS_OK != uwRet)
    {
        return uwRet;
    }
    return uwRet;
}



UINT32 sys_jiffies()
{
    UINT32 ret;
    extern UINT64      g_ullTickCount;
    
    ret = (UINT32)g_ullTickCount;
    return ret;
}
/*
#include "los_memory.h"   //here we make the memory for the lwip
#include "target_config.h"

#define POOL_ADDR   OS_SYS_MEM_ADDR

void *malloc(int size)
{
    void *ret = NULL;
    ret = LOS_MemAlloc(POOL_ADDR,size);
    return ret;
}

void free(void *addr)
{
    LOS_MemFree(POOL_ADDR,addr);
    return;
}
void *calloc(int count, int size)
{
  void *p;

  p = malloc(count * size);
  if (p) {
    memset(p, 0, (size_t)count * (size_t)size);
  }
  return p;
}
*/


int fputc(int ch, FILE *f)
{
    int ret = 0;
    ret =uart_write(&ch,1);
    return ret;
}

int fgetc(FILE *f)
{
    int ret;
    char ch;
    ret = uart_read(&ch,1,0xFFFFFF);
    return ch;
}
 int gRamSize = 0x8000;

VOID osTaskMemUsedInc(UINT32 uwUsedSize)
{
    gRamSize += uwUsedSize;
}
VOID osTaskMemUsedDec(UINT32 uwUsedSize)
{
    gRamSize -= uwUsedSize;
}

