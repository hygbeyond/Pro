/****************************************Copyright (c)****************************************************
 **                            Guangzhou ZHIYUAN electronics Co.,LTD.
 **
 **                                 http://www.embedtools.com
 **
 **--------------File Info---------------------------------------------------------------------------------
 ** File name:           IAP.c
 ** Last modified Date:  2010-02-04
 ** Last Version:        V1.0
 ** Descriptions:        IAP����-IAP����
 **
 **--------------------------------------------------------------------------------------------------------
 ** Created by:          Lanwuqiang
 ** Created date:        2010-02-05
 ** Version:             V1.0
 ** Descriptions:        ����û�Ӧ�ó���
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
 *  ����IAP������
 */                                     
#define     IAP_Prepare                                50               /* ѡ������                     */
                                                                        /* ����ʼ�����š����������š�   */
#define     IAP_RAMTOFLASH                             51               /* �������� FLASHĿ���ַ       */
                                                                        /* RAMԴ��ַ    ����д���ֽ���  */
                                                                        /* ϵͳʱ��Ƶ�ʡ�               */
#define     IAP_ERASESECTOR                            52               /* ��������    ����ʼ������     */
                                                                        /* ���������š�ϵͳʱ��Ƶ�ʡ�   */
#define     IAP_BLANKCHK                               53               /* �������    ����ʼ�����š�   */
                                                                        /* ���������š�                 */
#define     IAP_READPARTID                             54               /* ������ID    ���ޡ�           */
#define     IAP_BOOTCODEID                             55               /* ��Boot�汾�š��ޡ�           */
#define     IAP_COMPARE                                56               /* �Ƚ�����    ��Flash��ʼ��ַ  */
                                                                        /* RAM��ʼ��ַ����Ҫ�Ƚϵ�      */
                                                                        /* �ֽ�����                     */
#define     IAP_ReinvokeISP                            57               /* �ֶ�����ISP */

/* 
 *  ����CCLKֵ��С����λΪKHz 
 */
#define  IAP_FCCLK            (FCCLK/1000)
#define  IAP_ENTER_ADR        0x1FFF1FF1                                /* IAP��ڵ�ַ����              */

typedef void (*IAP)(uint32 [],uint32 []);


/*
 *  ���庯��ָ��  
 */
#define IAP_Entry(a, b)  ((IAP) IAP_ENTER_ADR)(a, b)

static uint32 command[5];
static uint32 result[4];
static uint32 iap_flag;


/*********************************************************************************************************
 ** Function name:       sectorPrepare
 ** Descriptions:        IAP��������ѡ���������50
 ** input parameters:    sec1:           ��ʼ����
 **                      sec2:           ��ֹ����
 ** output parameters:   result[0]:    IAP����״̬��,IAP����ֵ
 ** Returned value:      result[0]:    IAP����״̬��,IAP����ֵ
 *********************************************************************************************************/
uint32  sectorPrepare (uint8 sec1, uint8 sec2)
{  
    OS_SREG_VAR;
    OS_ENTER_CRITICAL();
    command[0] = IAP_Prepare;                                /* ����������                   */
    command[1] = sec1;                                       /* ���ò���                     */
    command[2] = sec2;                           
    IAP_Entry(command, result);                              /* ����IAP�������              */
    OS_EXIT_CRITICAL();

    return (result[0]);                                      /* ����״̬��                   */
}

/*********************************************************************************************************
 ** Function name:       ramCopy
 ** Descriptions:        ����RAM�����ݵ�FLASH���������51
 ** input parameters:    dst:            Ŀ���ַ����FLASH��ʼ��ַ����512�ֽ�Ϊ�ֽ�
 **                      src:            Դ��ַ����RAM��ַ����ַ�����ֶ���
 **                      no:             �����ֽڸ�����Ϊ512/1024/4096/8192
 ** output parameters:   result[0]:    IAP����״̬��,IAP����ֵ
 ** Returned value:      result[0]:    IAP����״̬��,IAP����ֵ
 *********************************************************************************************************/
uint32  ramToFlash (uint32 dst, uint32 src, uint32 no)
{  
    OS_SREG_VAR;
    OS_ENTER_CRITICAL();
    command[0] = IAP_RAMTOFLASH;                             /* ����������                   */
    command[1] = dst;                                        /* ���ò���                     */
    command[2] = src;
    command[3] = no;
    command[4] = IAP_FCCLK;
    IAP_Entry(command, result);                              /* ����IAP�������              */
    OS_EXIT_CRITICAL();

    return (result[0]);                                      /* ����״̬��                   */
}

/*********************************************************************************************************
 ** Function name:       sectorErase
 ** Descriptions:        �����������������52
 ** input parameters:    sec1            ��ʼ����
 **                      sec2            ��ֹ����92
 ** output parameters:   result[0]:    IAP����״̬��,IAP����ֵ
 ** Returned value:      result[0]:    IAP����״̬��,IAP����ֵ
 *********************************************************************************************************/
uint32  sectorErase (uint8 sec1, uint8 sec2)
{  
    OS_SREG_VAR;
    OS_ENTER_CRITICAL();
    command[0] = IAP_ERASESECTOR;                            /* ����������                   */
    command[1] = sec1;                                       /* ���ò���                     */
    command[2] = sec2;
    command[3] = IAP_FCCLK;
    IAP_Entry(command, result);                              /* ����IAP�������              */
    OS_EXIT_CRITICAL();

    return (result[0]);                                      /* ����״̬��                   */
}

/*********************************************************************************************************
 ** Function name:       blankChk
 ** Descriptions:        ������գ��������53
 ** input parameters:    sec1:           ��ʼ����
 **                      sec2:           ��ֹ����92
 ** output parameters:   result[0]:    IAP����״̬��,IAP����ֵ
 ** Returned value:      result[0]:    IAP����״̬��,IAP����ֵ
 *********************************************************************************************************/
uint32  blankChk (uint8 sec1, uint8 sec2)
{  
    OS_SREG_VAR;
    OS_ENTER_CRITICAL();
    command[0] = IAP_BLANKCHK;                               /* ����������                   */
    command[1] = sec1;                                       /* ���ò���                     */
    command[2] = sec2;
    IAP_Entry(command, result);                              /* ����IAP�������              */
    OS_EXIT_CRITICAL();

    return (result[0]);                                      /* ����״̬��                   */
}

/*********************************************************************************************************
 ** Function name:       dataCompare
 ** Descriptions:        У�����ݣ��������56
 ** input parameters:    dst:            Ŀ���ַ����RAM/FLASH��ʼ��ַ����ַ�����ֶ���
 **                      src:            Դ��ַ����FLASH/RAM��ַ����ַ�����ֶ���
 **                      no:             �����ֽڸ����������ܱ�4����
 ** output parameters:   result[0]:    IAP����״̬��,IAP����ֵ
 ** Returned value:      result[0]:    IAP����״̬��,IAP����ֵ
 *********************************************************************************************************/
uint32  dataCompare (uint32 dst, uint32 src, uint32 no)
{  
    OS_SREG_VAR;
    OS_ENTER_CRITICAL();
    command[0] = IAP_COMPARE;                                /* ����������                   */
    command[1] = dst;                                        /* ���ò���                     */
    command[2] = src;
    command[3] = no;
    IAP_Entry(command, result);                              /* ����IAP�������              */
    OS_EXIT_CRITICAL();

    return (result[0]);                                      /* ����״̬��                   */
}


/*
 * CPU ID
 */
uint32  parIdRead (void)
{  
    OS_SREG_VAR;
    OS_ENTER_CRITICAL();
    command[0] = IAP_READPARTID;                             /* ����������                   */
    IAP_Entry(command, result);                              /* ����IAP�������              */
    OS_EXIT_CRITICAL();

    return (result[1]);                                      /* ����״̬��                   */
}

/*
 * bootload �汾
 */
uint32  codeIdBoot (void)
{  
    OS_SREG_VAR;
    OS_ENTER_CRITICAL();
    command[0] = IAP_BOOTCODEID;                             /* ����������                   */
    IAP_Entry (command, result);                             /* ����IAP�������              */
    OS_EXIT_CRITICAL();

    return (result[1]);                                      /* ����״̬��                   */
}


static uint32 GetSecNum (uint32 adr)
{
    return adr > 0x10000? (14 + adr/32768): adr/4096;     // Sector Number
}


int flash_eras( void *adr, size_t sz )
{
    int page1 = GetSecNum((uint32)adr);
    int page2 = GetSecNum((uint32)adr + sz - 1);             /*  ѡ������                    */
    int ret;
    DEBUG5("iap eras:%d ~ %d\n", page1, page2);
    
    sectorPrepare       (page1, page2);     /*  ׼������1                   */
    sectorErase         (page1, page2);     /*  ��������1                   */
    ret = blankChk      (page1, page2);     /*  �������1                   */
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

    sectorPrepare     ( GetSecNum( padr ), GetSecNum( padr ));          /*  ѡ������                    */
    if( ramToFlash    ( padr, (uint32)flash_buff, FLASH_PAGE_SIZE))    /*  д���ݵ�����                */
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
    command[0] = IAP_ReinvokeISP;                                  /* ����������                   */
    IAP_Entry (command, result);                                   /* ����IAP�������              */
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
 *  ����IAP����״̬��
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

