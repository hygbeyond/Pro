
#ifndef __CAN_DATA_H__
#define __CAN_DATA_H__

#include "can.h"
#include "protocol_def.h"
#include "data_def.h"

extern int CanTransEn;

void CanData_Init( void );
int CanData_Get( uint8 channenl, CAN_msg *msg );
int CanData_Put( uint8 channel, CAN_msg *msg );

uint8 GZ_Trans( uint8 cmd, uint8 state );
uint8 TK_Trans( uint8 cmd );
int CanCmdMsg( CAN_msg *pMsg );

#endif // __CAN_DATA_H__


