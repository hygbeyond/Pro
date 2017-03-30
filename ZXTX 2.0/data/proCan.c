

#include "app_cfg.h"
#include "protocol.h"
#include "proCan.h"
#include "myfifo.h"
#include "OSstring.h"
#include "can_data.h"
#include "hardware.h"

extern int  LED_on;

TFIFO_TYPE( TProCan, 64 );
typedef FIFO_TYPE( TProCan ) TFifo_ProCan;

static TFifo_ProCan proBuff;
static TProtocol localPro;

extern uint8 MKIO;
extern uint8 MKState;

void ProCAN_Init(void)
{
    localPro.state = 0;
    FIFO_CLEAN( proBuff );
    pr_debug("TProCan %d\n", sizeof( TProCan ) );
}

int  ProCAN_Trans ( int port )
{
    TProCan pro;
    if( FIFO_GET( proBuff, pro ) )
    {
    	LED_on = HZ/10;
        return ProTransData( port, (uint8*)&pro, sizeof( pro));
    }
    return 0;
}

int ProCAN_Add(int port, CAN_msg *pMsg )
{
    TProCan pro;
    memset( &pro, 0, sizeof( pro ));
    pro.cmd = 0xA0;
    pro.msg.IO  = 0;
    pro.msg.num = port;
    pro.msg.IDCOUNT = pMsg->id;
    pro.msg.DataA   = pMsg->DataA;
    pro.msg.DataB   = pMsg->DataB;
    pro.msg.cnt     = pMsg->len;
    return FIFO_PUT( proBuff, pro);
}

#include "os_drive.h"

int ProCAN_Rect( uint8 dat )
{
    TProCan *pPro;
    CAN_msg msg;
    if( Pro_Add( &localPro, dat ))
    {
    	LED_on = HZ/10;
//    	LED_NOT;
        pPro = (TProCan*)localPro.buff;
        pr_debug("proCAN ÃüÁî:%x\n", pPro->cmd);
        switch( pPro->cmd )
        {
            case 0xA0:
                msg.id = pPro->msg.id;
                if( pPro->msg.IDEXT)
                {
                    msg.Frame =0x80000000 | (pPro->msg.cnt<<16); 
                }else
                    msg.Frame = pPro->msg.cnt << 16;
                msg.DataA = pPro->msg.DataA;
                msg.DataB = pPro->msg.DataB;
                MKIO = pPro->msg.IO;

				switch (pPro->msg.num)
				{
				default:
				case 0:
					CanData_Put(1, &msg);
				case 1:
					CanData_Put(0, &msg);
					break;
				case 2:
					CanData_Put(1, &msg);
					break;
				}
                return 1;
                break;

            case 0xA1:
                {
                    int m_baudrate = pPro->buff[0] + pPro->buff[1] * 256;
                    can1_port  = DOpen( "CAN1", m_baudrate);
                    can2_port  = DOpen( "CAN2", m_baudrate);
                    return FIFO_PUT( proBuff, *pPro );
                }
                break;
            case 0xA2:
                MKIO = pPro->buff[0];
                pPro->buff[0] = MKState;
                return FIFO_PUT( proBuff, *pPro );
                //TRACE("GetIO %02x\r\n", buff[1]);
                break;
            case 0xA3:
                {
                    pr_debug("°æ±¾\n");
                    pPro->buff[0] = VERSION;
                    pPro->buff[1] = PATCHLEVEL;
                    return FIFO_PUT( proBuff, *pPro );
                }
                break;

        }
        return TRUE;
    }
    return FALSE;
}


