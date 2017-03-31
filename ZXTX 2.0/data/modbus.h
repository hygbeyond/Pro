
#ifndef __MODBUS_H__
#define __MODBUS_H__

#include "mytype.h"

typedef struct         /*�������ݽṹ*/
{
    uint8  SlaveAddr;  /*�ӻ���ַ*/
    uint8  Func;       /*����*/
    uint8  StartAddrH; /*��ʼ��ַ*/
    uint8  StartAddrL;
    uint8  NumH;       /*��������*/
    uint8  NumL;
    uint16 crc;        /*CRCУ����*/
}__PACKED__ TModbusRx;


typedef struct        /*�������ݽṹ*/
{
    uint8 SlaveAddr;  /*�ӻ���ַ*/
    uint8 Func;       /*����*/
    uint8 Count;      /*��������*/
    struct{           /*���ݽṹ*/
        uint8 DataH;  
        uint8 DataL;
    }Data[100];
    uint16 crc;       /*CRCУ����*/
}__PACKED__ TModbusTx;


uint16 modbus_crc16(uint8 *puchMsg, uint16 usDataLen); 
void modbus_init(void );
int modbus_rect(int ch);

#endif //__MODBUS_H__



