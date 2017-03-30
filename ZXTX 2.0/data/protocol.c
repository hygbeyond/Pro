
#define PROTOCOL_GLOBAL
#include "mytype.h"
#include "protocol.h"
#include "crc16.h"
#include "app_cfg.h"
#include "IOProcessing.h"
#include "OSstring.h"
#include "hardware.h"


#if 0
static int Get_Crc( TProtocol *pPro)
{
    int size; 
    uint16 crc, crc1;
    uint8 *pd = &pPro->T1;
    size = pPro->Tcnt+3;
    crc  = GetCheckCRC( 0, pd, size);
    crc1 = pd[size] + (pd[size+1]<<8);
    return crc == crc1;
}
#endif

int Set_Crc( TProtocol *pPro )
{
    if( pPro == NULL )
        return 0;

    int size; 
    uint16 crc;
    uint8 *pd = &pPro->T1;
    pPro->T1 = TPROC_T1;
    pPro->T2 = TPROC_T2;
    size = pPro->Tcnt+3;
    crc  = modbus_crc( 0, pd, size);
    pd[size]   = crc & 0xFF;
    pd[size+1] = crc>>8;
    return size+2;
}

int Pro_Add( TProtocol *pPro, uint8 dat )
{

	switch( pPro->state )
	{
	case 0: // T1
		if( dat == TPROC_T1 )
		{
			pPro->T1 = TPROC_T1;
			pPro->state++;
		}
		break;
	case 1: // T2
		if( dat == TPROC_T2 )
		{
			pPro->T2 = TPROC_T2;
			pPro->state++;
		}
		break;
	case 2:
		if( dat > 128 )
		{
			pPro->state = 0;
			break;
		}
		pPro->Tcnt = dat;
		pPro->state++;
		pPro->size = 0;
		break;
	case 4:
		if( dat == TPROC_T2 )
		{
			pPro->state = 2;
			break;
		}
		pPro->state = 3;
	case 3:
		if( dat == TPROC_T1 )
			pPro->state = 4;
		pPro->buff[pPro->size++]  = dat;
		if( pPro->size == pPro->Tcnt+2 )
		{
			pPro->crc   = pPro->buff[pPro->Tcnt] + (pPro->buff[pPro->Tcnt+1]<<8);
			pPro->state = 0;
			WORD crc   = modbus_crc(0, &pPro->T1, pPro->Tcnt+3);
			return pPro->crc == crc;
		}
		break;
	 default:
		pPro->state = 0;
		break;
	}
	return FALSE;
    
}

int ProAddData( TProtocol *pPro, uint8 *dat, int size )
{
    memcpy( pPro->buff, dat, size );
    pPro->Tcnt = size;
    return Set_Crc( pPro);
}

int ProTransData( int hcom, uint8 *dat, int size )
{
    static TProtocol pro;
    pro.Tcnt = size;
    memcpy( pro.buff, dat, size );
    pro.T1 = TPROC_T1;
    pro.T2 = TPROC_T2;

	uint16 crc   = modbus_crc(0, &pro.T1, pro.Tcnt+3);
	pro.buff[pro.Tcnt]   = crc&0xFF;
	pro.buff[pro.Tcnt+1] = crc>>8;

    return IO_PutBuff( hcom, &pro.T1, pro.Tcnt + 5, 1000 );
}

