
#include "bsp.h"
#include "os_drive.h"
#include "myFifo.h"
#include "printk.h"


#define BUFF_SIZE              32

#define UART_CNT               4
#define SERIAL_IRQEN           1    /* Rx IRQ enable */

typedef uint8 Tser;
TFIFO_TYPE( Tser, BUFF_SIZE );
typedef FIFO_TYPE( Tser ) Tserial;

/*
typedef struct Sserial
{
    int   Rxin, Rxout,Rxcnt;
    uint8 Rxbuff[BUFF_SIZE];
} Tserial;
//*/

static Tserial serialBuff[UART_CNT];

static int uart_irqGet( int uart )
{
    LPC_UART_TypeDef *pUart;
    uint32 iir;
    Tserial *pSer;

    switch( uart )
    {
        case 0:
            pUart = (LPC_UART_TypeDef *)LPC_UART0;
            pSer = &serialBuff[0];
            break;
#if UART_CNT > 1
        case 1:
            pUart = (LPC_UART_TypeDef *)LPC_UART1;
            pSer = &serialBuff[1];
            break;
#if UART_CNT > 2
        case 2:
            pUart = (LPC_UART_TypeDef *)LPC_UART2;
            pSer = &serialBuff[2];
            break;
#if UART_CNT > 3
        case 3:
            pUart = (LPC_UART_TypeDef *)LPC_UART3;
            pSer = &serialBuff[3];
            break;
#endif
#endif
#endif
        default:
            return -1;
    }

    iir = pUart->IIR;

    if ((iir & 0x4) || (iir & 0xC)) {            // RDA or CTI pending
        while (pUart->LSR & 0x01) {                 // Rx FIFO is not empty
            FIFO_PUT( *pSer, pUart->RBR );
        }
    }
    if ((iir & 0x2)) {                           // TXMIS pending
#if 0
        if (SER_BUF_COUNT(ser_out) != 0) {
            pUart->THR = SER_BUF_RD(ser_out);         // Write to the Tx FIFO
            ser_txRestart = 0;
        }
        else {
            ser_txRestart = 1;
        }
#endif
    }
    return 0;
}

__AFTER__  void UART0_IRQHandler(void); 
void UART0_IRQHandler(void) 
{ 
    uart_irqGet(0);
}

__AFTER__  void UART1_IRQHandler(void);
void UART1_IRQHandler(void) 
{ 
    uart_irqGet(1);
}

__AFTER__  void UART2_IRQHandler(void);
void UART2_IRQHandler(void) 
{ 
    uart_irqGet(2);
}


__AFTER__  void UART3_IRQHandler(void);
void UART3_IRQHandler(void) 
{ 
    uart_irqGet(3);
}


static void serial_open( TOSDrive *dev, uint32 flag )
{
    LPC_UART_TypeDef *pUart;
    uint32 baudrate;

    baudrate = flag != 0? flag: dev->baudrate;
    switch( dev->num )
    {
        case 0:
            LPC_SC->PCONP |= PCONP_UART0;
            pUart = (LPC_UART_TypeDef *)LPC_UART0;
            break;
#if UART_CNT > 1
        case 1:
            LPC_SC->PCONP |= PCONP_UART1;
            pUart = (LPC_UART_TypeDef *)LPC_UART1;
            break;
#if UART_CNT > 2
        case 2:
            LPC_SC->PCONP |= PCONP_UART2;
            pUart = (LPC_UART_TypeDef *)LPC_UART2;
            break;
#if UART_CNT > 3
        case 3:
            LPC_SC->PCONP |= PCONP_UART3;
            pUart = (LPC_UART_TypeDef *)LPC_UART3;
            break;
#endif 
#endif
#endif 
        default:
            return;
    }

    pUart->LCR = 0x83;		/* 8 bits, no Parity, 1 Stop bit */
	uint32 Fdiv = (( 2 * FPCLK / 16 ) / baudrate + 1) / 2 ;	/*baud rate */
    pUart->DLM = Fdiv / 256;							
    pUart->DLL = Fdiv % 256;
	pUart->LCR = 0x03;		/* DLAB = 0 */
    pUart->FCR = 0x07;		/* Enable and reset TX and RX FIFO. */

    Tserial *pSerial = (Tserial*)dev->pdata;
    pUart->IER = 0x03;
    FIFO_CLEAN( *pSerial );
    //pSerial->Rxin = pSerial->Rxout = pSerial->Rxcnt = 0;
    switch( dev->num )
    {
        case 0:
            NVIC_EnableIRQ(UART0_IRQn);
            break;
        case 1:
            NVIC_EnableIRQ(UART1_IRQn);
            break;
        case 2:
            NVIC_EnableIRQ(UART2_IRQn);
            break;
        case 3:
            NVIC_EnableIRQ(UART3_IRQn);
            break;
    }
}

static void r485_open( TOSDrive *dev, uint32 flag )
{
    serial_open( dev, flag );
    LPC_UART1->RS485CTRL = 0x30;
    pr_debug("r485 %d\n", flag );
}

static int32 serial_write( TOSDrive *dev, uint32 pos, const uint8 *buff, uint32 size )
{
    int cnt,i;
    LPC_UART_TypeDef *pUart = dev->dev_base;
    if(buff == NULL || pUart == NULL )
        return 0;

    if( ( pUart->LSR & BIT(5) ) == 0)
        return 0;
    cnt = size > 8? 8: size;
    for(i = 0; i<cnt; i++ )
    {
        pUart->THR = *buff++;
    }
    return cnt;
}

static int32 serial_contrl( TOSDrive *dev, uint32 cmd, void *argv )
{
    LPC_UART_TypeDef *pUart = dev->dev_base;
    Tserial *pSerial = (Tserial*)dev->pdata;
    if( pUart == NULL )
        return -1;

    switch( cmd )
    {
        case DRIVE_CTRL_TCHAR:
            {
                uint8 *pd = argv;
                if(pd==NULL)
                    return 0;
                while (!(pUart->LSR & 0x20));
                return (pUart->THR = *pd);
            }
            break;
        case DRIVE_CTRL_RECT:
            {
                uint8 tmp;
                if( FIFO_GET( *pSerial, tmp ) )
                    return tmp;
                return -1;
            }
            break;
    }
    return 0;
}

static int32 serial_read( TOSDrive *dev, uint32 pos, uint8 *buff, uint32 size )
{
    LPC_UART_TypeDef *pUart = dev->dev_base;
    int cnt;
    if(buff == NULL || pUart == NULL)
        return 0;

    cnt = 0;
    Tserial *pSerial = (Tserial*)dev->pdata;
    if(pSerial )
    {
        while( size-- )
        {
            if( !FIFO_Get( *pSerial, buff[cnt++] ))
                break;
        }
    }else
    {
        while(pUart->LSR & 0x01)
        {
            buff[cnt++] = pUart->RBR;
        }
    }
    return cnt;
}

__DriveBegin( uart0 )
    .num = 0,
    .baudrate = 9600,
    .open = serial_open,
    .write = serial_write,
    .read  = serial_read,
    .contrl = serial_contrl,
    .pdata = &serialBuff[0],
    .dev_base = LPC_UART0,
__DriveEnd();

#if UART_CNT > 1
__DriveBegin( r485 )
    .num = 1,
    .baudrate = 9600,
    .open  = r485_open,
    .write = serial_write,
    .read  = serial_read,
    .contrl = serial_contrl,
    .pdata = &serialBuff[1],
    .dev_base = LPC_UART1,
__DriveEnd();

__DriveBegin( uart1 )
    .num = 1,
    .baudrate = 9600,
    .open = serial_open,
    .write = serial_write,
    .read  = serial_read,
    .contrl = serial_contrl,
    .pdata = &serialBuff[1],
    .dev_base = LPC_UART1,
__DriveEnd();


#if UART_CNT > 2
__DriveBegin( uart2 )
    .num = 2,
    .baudrate = 9600,
    .open = serial_open,
    .write = serial_write,
    .read  = serial_read,
    .contrl = serial_contrl,
    .pdata = &serialBuff[2],
    .dev_base = LPC_UART2,
__DriveEnd();

#if UART_CNT > 3
__DriveBegin( uart3 )
    .num = 3,
    .baudrate = 9600,
    .open = serial_open,
    .write = serial_write,
    .read  = serial_read,
    .contrl = serial_contrl,
    .pdata = &serialBuff[3],
    .dev_base = LPC_UART3,
__DriveEnd();
#endif 
#endif 
#endif 


