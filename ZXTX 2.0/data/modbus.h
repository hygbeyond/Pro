
#ifndef __MODBUS_H__
#define __MODBUS_H__

#include "mytype.h"

typedef struct         /*接收数据结构*/
{
    uint8  SlaveAddr;  /*从机地址*/
    uint8  Func;       /*功能*/
    uint8  StartAddrH; /*开始地址*/
    uint8  StartAddrL;
    uint8  NumH;       /*数据数量*/
    uint8  NumL;
    uint16 crc;        /*CRC校验码*/
}__PACKED__ TModbusRx;


typedef struct        /*发送数据结构*/
{
    uint8 SlaveAddr;  /*从机地址*/
    uint8 Func;       /*功能*/
    uint8 Count;      /*数据数量*/
    struct{           /*数据结构*/
        uint8 DataH;  
        uint8 DataL;
    }Data[100];
    uint16 crc;       /*CRC校验码*/
}__PACKED__ TModbusTx;


uint16 modbus_crc16(uint8 *puchMsg, uint16 usDataLen); 
void modbus_init(void );
int modbus_rect(int ch);

#endif //__MODBUS_H__



