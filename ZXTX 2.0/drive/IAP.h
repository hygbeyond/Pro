/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.embedtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           IAP.h
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
#ifndef __IAP_H
#define __IAP_H

#include "mytype.h"


#define     IAP_FLAG_WRITE                             0x01
#define     IAP_FLAG_READ                              0x02
#define     IAP_FLAG_ERAS                              0x04
#define     IAP_FLAG_WRITEERAS                         0x08

#define     IAP_CTRL_ERAS                              0xA

#define     IAP_CTRL_ERAS_GETSIZE( a )                 (0x0FFFFFFF & (a))
#define     IAP_CTRL_ERAS_CMD( a )                     (((a) >> 28) & 0xF)
#define     IAP_CTRL_ERASSIZE( a )                     ( (IAP_CTRL_ERAS <<28) | ( a ) )

/*
 *  ����IAP����״̬��
 */
#define     CMD_SUCCESS                                0
#define     INVALID_COMMAND                            1
#define     SRC_ADDR_ERROR                             2
#define     DST_ADDR_ERROR                             3
#define     SRC_ADDR_NOT_MAPPED                        4
#define     DST_ADDR_NOT_MAPPED                        5
#define     COUNT_ERROR                                6
#define     INVALID_SECTOR                             7
#define     SECTOR_NOT_BLANK                           8
#define     SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION    9
#define     COMPARE_ERROR                              10
#define     BUSY                                       11


/*********************************************************************************************************
** Function name:       sectorPrepare
** Descriptions:        IAP��������ѡ���������50
** input parameters:    sec1:           ��ʼ����
**                      sec2:           ��ֹ����
** output parameters:   paramout[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      paramout[0]:    IAP����״̬��,IAP����ֵ
*********************************************************************************************************/
extern uint32  sectorPrepare (uint8 sec1, uint8 sec2);

/*********************************************************************************************************
** Function name:       ramCopy
** Descriptions:        ����RAM�����ݵ�FLASH���������51
** input parameters:    dst:            Ŀ���ַ����FLASH��ʼ��ַ����512�ֽ�Ϊ�ֽ�
**                      src:            Դ��ַ����RAM��ַ����ַ�����ֶ���
**                      no:             �����ֽڸ�����Ϊ512/1024/4096/8192
** output parameters:   paramout[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      paramout[0]:    IAP����״̬��,IAP����ֵ
*********************************************************************************************************/
extern uint32  ramToFlash (uint32 dst, uint32 src, uint32 no);

/*********************************************************************************************************
** Function name:       sectorErase
** Descriptions:        �����������������52
** input parameters:    sec1            ��ʼ����
**                      sec2            ��ֹ����92
** output parameters:   paramout[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      paramout[0]:    IAP����״̬��,IAP����ֵ
*********************************************************************************************************/
extern uint32  sectorErase (uint8 sec1, uint8 sec2);

/*********************************************************************************************************
** Function name:       blankChk
** Descriptions:        ������գ��������53
** input parameters:    sec1:           ��ʼ����
**                      sec2:           ��ֹ����92
** output parameters:   paramout[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      paramout[0]:    IAP����״̬��,IAP����ֵ
*********************************************************************************************************/
extern uint32  blankChk (uint8 sec1, uint8 sec2);

/*********************************************************************************************************
** Function name:       parIdRead
** Descriptions:        ������գ��������54
** input parameters:    ��
** output parameters:   paramout[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      paramout[0]:    IAP����״̬��,IAP����ֵ
*********************************************************************************************************/
extern  uint32  parIdRead (void);

/*********************************************************************************************************
** Function name:       codeIdBoot
** Descriptions:        ������գ��������55
** input parameters:    ��
** output parameters:   paramout[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      paramout[0]:    IAP����״̬��,IAP����ֵ
*********************************************************************************************************/
extern uint32  codeIdBoot (void);

/*********************************************************************************************************
** Function name:       dataCompare
** Descriptions:        У�����ݣ��������56
** input parameters:    dst:            Ŀ���ַ����RAM/FLASH��ʼ��ַ����ַ�����ֶ���
**                      src:            Դ��ַ����FLASH/RAM��ַ����ַ�����ֶ���
**                      no:             �����ֽڸ����������ܱ�4����
** output parameters:   paramout[0]:    IAP����״̬��,IAP����ֵ
** Returned value:      paramout[0]:    IAP����״̬��,IAP����ֵ
*********************************************************************************************************/
extern uint32  dataCompare (uint32 dst, uint32 src, uint32 no);

uint32 flash_write( void *flash_addr, void *buff, size_t len);
int    flash_eras( void *adr, size_t sz );

void   GotoISP(void);

#endif                                                                  /*  _IAP_H_                     */

/*********************************************************************************************************
  End Of File
*********************************************************************************************************/

