


#define BSP_GLOBAL
#include "mytype.h"
#include "bsp.h"
#include "printk.h"

#include "OSstdio.h"

uint16 __NOINIT__ MemStart;


static void U0_open( uint32 baudrate );
static int printk_put( int ch, FILE * p_file);
static int printk_get( FILE *p_file );

void BSP_Init(void)
{
    SystemInit();
    U0_open( 115200 );
    printk_set( printk_put, printk_get );
}



static void U0_open( uint32 baudrate )
{
    LPC_UART_TypeDef *pUart = (LPC_UART_TypeDef *)LPC_UART0;

    LPC_SC->PCONP |= PCONP_UART0;

#if CPU == LPC1778 || CPU == LPC1788
    LPC_IOCON->P0_2 = D_SETIO( 1, 2);   // TXD0
    LPC_IOCON->P0_3 = D_SETIO( 1, 2);   // RXD0
#else
    LPC_PINCON->PINSEL0 |=  (1 << 4);        /* Pin P0.2 used as TXD0           */
    LPC_PINCON->PINSEL0 |=  (1 << 6);        /* Pin P0.3 used as RXD0           */
#endif


    pUart->LCR = 0x83;		/* 8 bits, no Parity, 1 Stop bit */
    uint32 Fdiv = (( 2 * FPCLK / 16 ) / baudrate + 1) / 2 ;	/*baud rate */
    pUart->DLM = Fdiv / 256;							
    pUart->DLL = Fdiv % 256;
    pUart->LCR = 0x03;		/* DLAB = 0 */
    pUart->FCR = 0x07;		/* Enable and reset TX and RX FIFO. */

    pUart->IER = 0x00;
}


static int printk_put( int ch, FILE * p_file)
{
    LPC_UART_TypeDef *pUart = (LPC_UART_TypeDef *)LPC_UART0;
    pUart = (LPC_UART_TypeDef *)LPC_UART0;
    while (!(pUart->LSR & 0x20));
    return (pUart->THR = ch);
}

static int printk_get( FILE *p_file )
{
    LPC_UART_TypeDef *pUart = (LPC_UART_TypeDef *)LPC_UART0;
    if(pUart->LSR & 0x01)
    {
        return pUart->RBR;
    }
    return -1;
}




/*
 * BSP_Reset   通过软件复位单片机
 */
void BSP_Reset (void)
{   /*  此系统上电复位等同硬件复位  */
    NVIC_SystemReset();
}



/*
 * end bsp.c
 */


