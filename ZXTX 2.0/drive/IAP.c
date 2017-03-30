/****************************************Copyright (c)****************************************************
 **                            Guangzhou ZHIYUAN electronics Co.,LTD.
 **
 **                                 http://www.embedtools.com
 **
 **--------------File Info---------------------------------------------------------------------------------
 ** File name:           IAP.c
 ** Last modified Date:  2010-02-04
 ** Last Version:        V1.0
 ** Descriptions:        IAP升级-IAP函数
 **
 **--------------------------------------------------------------------------------------------------------
 ** Created by:          Lanwuqiang
 ** Created date:        2010-02-05
 ** Version:             V1.0
 ** Descriptions:        添加用户应用程序
 **
 **--------------------------------------------------------------------------------------------------------
 ** Modified by:         
 ** Modified date:       
 ** Version:             
 ** Descriptions:        
 ** Rechecked by:        
 *********************************************************************************************************/
#include "bsp.h"
#include "IAP.h"
#include "app_cfg.h" 
#include "pcommand.h"
#include "microOS.h"
#include "os_drive.h"


/* 
 *  定义IAP命令字
 */                                     
#define     IAP_Prepare                                50               /* 选择扇区                     */
                                                                        /* 【起始扇区号、结束扇区号】   */
#define     IAP_RAMTOFLASH                             51               /* 拷贝数据 FLASH目标地址       */
                                                                        /* RAM源地址    【、写入字节数  */
                                                                        /* 系统时钟频率】               */
#define     IAP_ERASESECTOR                            52               /* 擦除扇区    【起始扇区号     */
                                                                        /* 结束扇区号、系统时钟频率】   */
#define     IAP_BLANKCHK                               53               /* 查空扇区    【起始扇区号、   */
                                                                        /* 结束扇区号】                 */
#define     IAP_READPARTID                             54               /* 读器件ID    【无】           */
#define     IAP_BOOTCODEID                             55               /* 读Boot版本号【无】           */
#define     IAP_COMPARE                                56               /* 比较命令    【Flash起始地址  */
                                                                        /* RAM起始地址、需要比较的      */
                                                                        /* 字节数】                     */
#define     IAP_ReinvokeISP                            57               /* 手动进入ISP */

/* 
 *  定义CCLK值大小，单位为KHz 
 */
#define  IAP_FCCLK            (FCCLK/1000)
#define  IAP_ENTER_ADR        0x1FFF1FF1                                /* IAP入口地址定义              */

typedef void (*IAP)(uint32 [],uint32 []);


/*
 *  定义函数指针  
 */
#define IAP_Entry(a, b)  ((IAP) IAP_ENTER_ADR)(a, b)

static uint32 command[5];
static uint32 result[4];
static uint32 iap_flag;


/*********************************************************************************************************
 ** Function name:       sectorPrepare
 ** Descriptions:        IAP操作扇区选择，命令代码50
 ** input parameters:    sec1:           起始扇区
 **                      sec2:           终止扇区
 ** output parameters:   result[0]:    IAP操作状态码,IAP返回值
 ** Returned value:      result[0]:    IAP操作状态码,IAP返回值
 *********************************************************************************************************/
uint32  sectorPrepare (uint8 sec1, uint8 sec2)
{  
    OS_SREG_VAR;
    OS_ENTER_CRITICAL();
    command[0] = IAP_Prepare;                                /* 设置命令字                   */
    command[1] = sec1;                                       /* 设置参数                     */
    command[2] = sec2;                           
    IAP_Entry(command, result);                              /* 调用IAP服务程序              */
    OS_EXIT_CRITICAL();

    return (result[0]);                                      /* 返回状态码                   */
}

/*********************************************************************************************************
 ** Function name:       ramCopy
 ** Descriptions:        复制RAM的数据到FLASH，命令代码51
 ** input parameters:    dst:            目标地址，即FLASH起始地址。以512字节为分界
 **                      src:            源地址，即RAM地址。地址必须字对齐
 **                      no:             复制字节个数，为512/1024/4096/8192
 ** output parameters:   result[0]:    IAP操作状态码,IAP返回值
 ** Returned value:      result[0]:    IAP操作状态码,IAP返回值
 *********************************************************************************************************/
uint32  ramToFlash (uint32 dst, uint32 src, uint32 no)
{  
    OS_SREG_VAR;
    OS_ENTER_CRITICAL();
    command[0] = IAP_RAMTOFLASH;                             /* 设置命令字                   */
    command[1] = dst;                                        /* 设置参数                     */
    command[2] = src;
    command[3] = no;
    command[4] = IAP_FCCLK;
    IAP_Entry(command, result);                              /* 调用IAP服务程序              */
    OS_EXIT_CRITICAL();

    return (result[0]);                                      /* 返回状态码                   */
}

/*********************************************************************************************************
 ** Function name:       sectorErase
 ** Descriptions:        扇区擦除，命令代码52
 ** input parameters:    sec1            起始扇区
 **                      sec2            终止扇区92
 ** output parameters:   result[0]:    IAP操作状态码,IAP返回值
 ** Returned value:      result[0]:    IAP操作状态码,IAP返回值
 *********************************************************************************************************/
uint32  sectorErase (uint8 sec1, uint8 sec2)
{  
    OS_SREG_VAR;
    OS_ENTER_CRITICAL();
    command[0] = IAP_ERASESECTOR;                            /* 设置命令字                   */
    command[1] = sec1;                                       /* 设置参数                     */
    command[2] = sec2;
    command[3] = IAP_FCCLK;
    IAP_Entry(command, result);                              /* 调用IAP服务程序              */
    OS_EXIT_CRITICAL();

    return (result[0]);                                      /* 返回状态码                   */
}

/*********************************************************************************************************
 ** Function name:       blankChk
 ** Descriptions:        扇区查空，命令代码53
 ** input parameters:    sec1:           起始扇区
 **                      sec2:           终止扇区92
 ** output parameters:   result[0]:    IAP操作状态码,IAP返回值
 ** Returned value:      result[0]:    IAP操作状态码,IAP返回值
 *********************************************************************************************************/
uint32  blankChk (uint8 sec1, uint8 sec2)
{  
    OS_SREG_VAR;
    OS_ENTER_CRITICAL();
    command[0] = IAP_BLANKCHK;                               /* 设置命令字                   */
    command[1] = sec1;                                       /* 设置参数                     */
    command[2] = sec2;
    IAP_Entry(command, result);                              /* 调用IAP服务程序              */
    OS_EXIT_CRITICAL();

    return (result[0]);                                      /* 返回状态码                   */
}

/*********************************************************************************************************
 ** Function name:       dataCompare
 ** Descriptions:        校验数据，命令代码56
 ** input parameters:    dst:            目标地址，即RAM/FLASH起始地址。地址必须字对齐
 **                      src:            源地址，即FLASH/RAM地址。地址必须字对齐
 **                      no:             复制字节个数，必须能被4整除
 ** output parameters:   result[0]:    IAP操作状态码,IAP返回值
 ** Returned value:      result[0]:    IAP操作状态码,IAP返回值
 *********************************************************************************************************/
uint32  dataCompare (uint32 dst, uint32 src, uint32 no)
{  
    OS_SREG_VAR;
    OS_ENTER_CRITICAL();
    command[0] = IAP_COMPARE;                                /* 设置命令字                   */
    command[1] = dst;                                        /* 设置参数                     */
    command[2] = src;
    command[3] = no;
    IAP_Entry(command, result);                              /* 调用IAP服务程序              */
    OS_EXIT_CRITICAL();

    return (result[0]);                                      /* 返回状态码                   */
}


/*
 * CPU ID
 */
uint32  parIdRead (void)
{  
    OS_SREG_VAR;
    OS_ENTER_CRITICAL();
    command[0] = IAP_READPARTID;                             /* 设置命令字                   */
    IAP_Entry(command, result);                              /* 调用IAP服务程序              */
    OS_EXIT_CRITICAL();

    return (result[1]);                                      /* 返回状态码                   */
}

/*
 * bootload 版本
 */
uint32  codeIdBoot (void)
{  
    OS_SREG_VAR;
    OS_ENTER_CRITICAL();
    command[0] = IAP_BOOTCODEID;                             /* 设置命令字                   */
    IAP_Entry (command, result);                             /* 调用IAP服务程序              */
    OS_EXIT_CRITICAL();

    return (result[1]);                                      /* 返回状态码                   */
}


static uint32 GetSecNum (uint32 adr)
{
    return adr > 0x10000? (14 + adr/32768): adr/4096;     // Sector Number
}


int flash_eras( void *adr, size_t sz )
{
    int page1 = GetSecNum((uint32)adr);
    int page2 = GetSecNum((uint32)adr + sz - 1);             /*  选择扇区                    */
    int ret;
    DEBUG5("iap eras:%d ~ %d\n", page1, page2);
    
    sectorPrepare       (page1, page2);     /*  准备扇区1                   */
    sectorErase         (page1, page2);     /*  擦除扇区1                   */
    ret = blankChk      (page1, page2);     /*  查空扇区1                   */
    return ret;
}


#define  FLASH_PAGE_SIZE           512
static uint32 flash_buff[FLASH_PAGE_SIZE/4];
static int flash_writeF(uint32 faddr, uint8 *buffer , size_t len)
{    
    uint32 padr, ofs, cnt;
    int i;
    DEBUG5("iap write %08x %08x %d\n", faddr, (uint32)buffer, len);
    padr = faddr & ~(FLASH_PAGE_SIZE - 1);     // Page Address
    ofs  = faddr - padr;                       // Data Offset
    cnt  = FLASH_PAGE_SIZE - ofs;              // Data Count

    if( cnt > len )
        cnt = len;

    for(i=0; i<FLASH_PAGE_SIZE/4; i++)
    {
        flash_buff[i] = *((uint32 *)padr + i);
    }

    for (i = 0; i < cnt; i++) {                              // Go through Page Data
        *((uint8 *)flash_buff + ofs++) = *buffer++;          // Copy & Align to Page Buffer
    }
    DEBUG5("iap write:%d %08x %d\n", GetSecNum( padr ), padr, cnt);

    sectorPrepare     ( GetSecNum( padr ), GetSecNum( padr ));          /*  选择扇区                    */
    if( ramToFlash    ( padr, (uint32)flash_buff, FLASH_PAGE_SIZE))    /*  写数据到扇区                */
        return -1;
    return cnt;
}

uint32 flash_write(void *flash_addr, void *data, size_t len)
{
    uint32 faddr = (uint32) flash_addr;
    uint32 baddr = (uint32) data;
    int time =10;
    do{
        int ret = flash_writeF( faddr, (uint8*)baddr, len);
        if( ret > 0 )
        {
            time = 10;
            faddr += ret;
            baddr += ret;
            len   -= ret;
            if( len <= 0 )
                return TRUE;
        }
        OSTimeDly(HZ/100);
    }while( --time );
    return FALSE;
}


static void  iap_open( TOSDrive *dev, uint32 flag )
{
#if 0
    ASSERT( dev );
    uint32 *pd = dev->pdata;
    if( pd )
    {
        *pd = flag;
    }
#else
    iap_flag = flag;
#endif
}

static int32 iap_write( TOSDrive *dev, uint32 pos, const uint8 *buff, uint32 len )
{
    uint32 faddr = (uint32) pos;
    uint32 baddr = (uint32) buff;
    int time =10;

    if( iap_flag & IAP_FLAG_WRITEERAS )
    {
        flash_eras( (void*)pos, len);
    }

    if( (iap_flag & IAP_FLAG_WRITE) == 0 )
        return FALSE;

    do{
        int ret = flash_writeF( faddr, (uint8*)baddr, len);
        if( ret > 0 )
        {
            time = 10;
            faddr += ret;
            baddr += ret;
            len   -= ret;
            if( len <= 0 )
                return TRUE;
        }
        OSTimeDly(HZ/100);
    }while( --time );
    return FALSE;
}

static int32 iap_read( TOSDrive *dev, uint32 pos, uint8 *buff, uint32 len )
{
    uint8 *pd = (uint8*)pos;
    int i;
    for(i=0; i<len; i++)
    {
        *buff++ = *pd++;
    }
    return i;
}


static int32 iap_contrl( TOSDrive *dev, uint32 cmd, void *argv )
{
    if( IAP_CTRL_ERAS_CMD( cmd ) == IAP_CTRL_ERAS )
    {
        uint32 size = IAP_CTRL_ERAS_GETSIZE( cmd );
        flash_eras( argv, size );
    }
    return 0;
}

uint32 __NOINIT__ isp_en;

void   GotoISP(void)
{
    if( isp_en != 0x55AA55AAUL)
        return;
    isp_en = 0;
    command[0] = IAP_ReinvokeISP;                                  /* 设置命令字                   */
    IAP_Entry (command, result);                                   /* 调用IAP服务程序              */
    while(1);
}

#include "bsp.h"

static int isp_cmd( int args, char **argv )
{
    printk("goto isp \n");
    isp_en = 0x55AA55AAUL;
    MemStart = 0;
    BSP_Reset();
    return 0;
}
PSHELL_CMD( isp, isp_cmd, "isp");



__DriveBegin( iap )
    .open  = iap_open,
    .write = iap_write, 
    .read  = iap_read,
    .contrl = iap_contrl,
    .pdata  = &iap_flag,
__DriveEnd();





#define IAP_USER_ADDR              0x00038000

#if SHELL_CMD_IAP > 0
/*
 *  定义IAP返回状态字
 */
#if 0
static void printIAP(int a)
{
    switch(a)
    {
        case CMD_SUCCESS                               :
            break;
        case INVALID_COMMAND                           :
            pr_debug("INVALID_COMMAND\n");
            break;
        case SRC_ADDR_ERROR                            :
            pr_debug("SRC_ADDR_ERROR\n");
            break;
        case DST_ADDR_ERROR                            :
            pr_debug("DST_ADDR_ERROR\n");
            break;
        case SRC_ADDR_NOT_MAPPED                       :
            pr_debug("SRC_ADDR_NOT_MAPPED\n");
            break;
        case DST_ADDR_NOT_MAPPED                       :
            pr_debug("DST_ADDR_NOT_MAPPED\n");
            break;
        case COUNT_ERROR                               :
            pr_debug("COUNT_ERROR\n");
            break;
        case INVALID_SECTOR                            :
            pr_debug("INVALID_SECTOR\n");
            break;
        case SECTOR_NOT_BLANK                          :
            pr_debug("SECTOR_NOT_BLANK\n");
            break;
        case SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION   :
            pr_debug("SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION\n");
            break;
        case COMPARE_ERROR                             :
            pr_debug("COMPARE_ERROR\n");
            break;
        case BUSY                                      :
            pr_debug("BUSY\n");
            break;
    }
}
#endif

#include "kmalloc.h"
//uint8 tbuff[128];
static int iap_cmd(int args, char **argv)
{
    const uint8 *pd;
    int i;
    int data;
    int addr;
    uint8 *tbuff;
    OS_SREG_VAR;

    tbuff = (uint8*)OSMalloc( 128 );
    if( tbuff == NULL ) return 0;
    addr  = atoi( argv[2] );
    data  = atoi( argv[3] );
    pd = (void*)addr;
    if( args > 1 )
    {
        if(!strcmp( argv[1], "id"))
        {
            goto iap_cmd_id;
        }else if(!strcmp( argv[1], "write"))
        {
            for(i=0; i<sizeof(tbuff); i++)
                tbuff[i] = data;
            flash_write((void*) addr, tbuff, sizeof(tbuff));
        }else if(!strcmp( argv[1], "erase"))
        {
            flash_eras((void*) addr, data);
        }else if(!strcmp( argv[1], "read"))
        {
            printk("\nflash read:0x%x\n",(int)pd);
            for(i=0; i<512; i++)
                printk("%x ",*pd++);
            printk("\n");
        }
    }else
    {
        printk("iap [id|read|write|erase] data \n");
iap_cmd_id:
        OS_ENTER_CRITICAL();
        printk("id  :%08x\n", parIdRead());
        printk("boot:%08x\n", codeIdBoot());
        OS_EXIT_CRITICAL();
    }
    OSFree( tbuff );
    return 0;
}
PSHELL_CMD(iap, iap_cmd, "iap [id|read|write|erase] addr data");
#endif 

/*********************************************************************************************************
  End Of File
 *********************************************************************************************************/

