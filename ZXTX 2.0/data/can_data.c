


#include "app_cfg.h"
#include "can.h"
#include "can_data.h"
#include "myFifo.h"
#include "protocol_def.h"
#include "data_def.h"


TFIFO_TYPE( CAN_msg, 128 );

FIFO_TYPE( CAN_msg) CANbuff[2];
int CanTransEn;

void CanData_Init( void )
{
    FIFO_CLEAN( CANbuff[0] );
    FIFO_CLEAN( CANbuff[1] );
    CanTransEn = 0;
}

int CanData_Get( uint8 channel, CAN_msg *msg )
{
    if( channel < ARRAY_SIZE( CANbuff ) )
    {
        return FIFO_GET( CANbuff[channel], *msg );
    }
    return 0;
}

int CanData_Put( uint8 channel, CAN_msg *msg )
{
	DEBUG2("can%d %x, %08x\t%08x\n", channel + 1, msg->id, msg->DataA,
			msg->DataB);
	if (channel == 1)
	{
		return FIFO_PUT( CANbuff[channel], *msg );
	}
	else if (channel == 0)
	{
		return FIFO_PUT( CANbuff[channel], *msg );
	}
	return 0;
}
