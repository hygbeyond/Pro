
#include "bsp.h"
#include "can.h"
#include "os_drive.h"
#include "osstring.h"
#include "app_cfg.h"

#define BUFF_SIZE       64

typedef struct
{
    uint32  baudrate;
    int     Rxin, Rxout, Rxcnt;
    CAN_msg Rxbuff[ BUFF_SIZE ];
}TCANbuff;

static TCANbuff CANbuff[2];

#define  PCLK            FPCLK         /* Peripheral clock, depends on VPBDIV */
/* Values of bit time register for different baudrates
   NT = Nominal bit time = TSEG1 + TSEG2 + 3
   SP = Sample point     = ((TSEG2 +1) / (TSEG1 + TSEG2 + 3)) * 100%
                                            SAM,  SJW, TSEG1, TSEG2, NT,  SP */
static const uint32_t CAN_BIT_TIME[] = {          0, /*             not used             */
                                           0, /*             not used             */
                                           0, /*             not used             */
                                           0, /*             not used             */
                                  0x0001C000, /* 0+1,  3+1,   1+1,   0+1,  4, 75% */
                                           0, /*             not used             */
                                  0x0012C000, /* 0+1,  3+1,   2+1,   1+1,  6, 67% */
                                           0, /*             not used             */
                                  0x0023C000, /* 0+1,  3+1,   3+1,   2+1,  8, 63% */
                                           0, /*             not used             */
                                  0x0025C000, /* 0+1,  3+1,   5+1,   2+1, 10, 70% */
                                           0, /*             not used             */
                                  0x0036C000, /* 0+1,  3+1,   6+1,   3+1, 12, 67% */
                                           0, /*             not used             */
                                           0, /*             not used             */
                                  0x0048C000, /* 0+1,  3+1,   8+1,   4+1, 15, 67% */
                                  0x0049C000, /* 0+1,  3+1,   9+1,   4+1, 16, 69% */
                                };

/*----------------------------------------------------------------------------
  configure the requested baudrate.  CAN controller (1..2)
 *----------------------------------------------------------------------------*/
static void CAN_cfgBaudrate (uint32_t ctrl, uint32_t baudrate)
{
    LPC_CAN_TypeDef *pCAN = (ctrl == 1) ? LPC_CAN1 : LPC_CAN2;
    uint32_t result = 0;
    uint32_t nominal_time;

    /* Determine which nominal time to use for PCLK */
    if (((PCLK / 1000000) % 6) == 0) {
        nominal_time = 12;                   /* PCLK based on  72MHz CCLK */
    } else {
        nominal_time = 10;                   /* PCLK based on 100MHz CCLK */
    }

    /* Prepare value appropriate for bit time register */
    result  = (PCLK / nominal_time) / baudrate - 1;

    result &= 0x000003FF;
    result |= CAN_BIT_TIME[nominal_time];

    pCAN->BTR  = result;                           /* Set bit timing */
}

static void can_open( TOSDrive *dev, uint32 flag )
{
    uint32 baudrate = flag? flag: dev->baudrate;
    LPC_CAN_TypeDef *pCAN;
    TCANbuff *pBuf = (TCANbuff *)dev->pdata;

    if( pBuf )
    {
        pBuf->Rxin  = 0;
        pBuf->Rxout = 0;
        pBuf->Rxcnt = 0;
        if( baudrate )
            pBuf->baudrate = baudrate;
    }

    if (dev->num == 1) {
        LPC_SC->PCONP       |=  (1 << 13);           /* Enable power to CAN1 block */
        pCAN = LPC_CAN1;
        
    } else {
        LPC_SC->PCONP       |=  (1 << 14);           /* Enable power to CAN2 block */
        pCAN = LPC_CAN2;
    }
    NVIC_EnableIRQ(CAN_IRQn);                    /* Enable CAN interrupt */

    LPC_CANAF->AFMR = 2;                         /* By default filter is not used */
    pCAN->MOD   = 1;                             /* Enter reset mode */
    pCAN->IER   = 0;                             /* Disable all interrupts */
    pCAN->GSR   = 0;                             /* Clear status register */
    CAN_cfgBaudrate( dev->num, baudrate);             /* Set bit timing */
    pCAN->IER   = 0x01;                          /* Enable Tx and Rx interrupt */
    pCAN->MOD   = 0;

    pr_debug("CAN%d open %d\n", dev->num, baudrate);
}

static int32 can_write( TOSDrive *dev, uint32 pos, const uint8 *buff, uint32 size )
{
    LPC_CAN_TypeDef *pCAN = (dev->num == 1) ? LPC_CAN1 : LPC_CAN2;
    CAN_msg d;
    memcpy( &d, buff, sizeof(CAN_msg));
    CAN_msg *msg = &d;

    if(buff == NULL)
        return 0;
    //CAN_msg *msg = (CAN_msg*) buff;
    volatile uint32 i;
    if(pCAN->GSR & (1<<7))
    { //如果总线因错误挂起，处理
        LPC_CANAF->AFMR = 2;
        pCAN->MOD = 1;
        for(i=0; i<128; i++)
        {
            pCAN->GSR = 0;
            __NOP();
        }
        for(i=0; i<5000; i++);
        pCAN->MOD = 0;
        for(i=0; i<5000; i++);
        pCAN->CMR = 1;
        DEBUG0("CAN%d error\n", dev->num);
        return CAN_ERROR;
    }

    if (pCAN->SR & 0x00000004)  {                    /* Transmit buffer 1 free */
        DEBUG3( "CAN dataA:%08x\n", msg->DataA);
        pCAN->TFI1 = msg->Frame;                     /* Write frame informations */
        pCAN->TID1 = msg->id;                        /* Write CAN message identifier */
        pCAN->TDA1 = msg->DataA;                     /* Write first 4 data bytes */
        pCAN->TDB1 = msg->DataB;                     /* Write second 4 data bytes */
        //pCAN->CMR  = 0x31;                         /* Select Tx1 for Self Tx/Rx */
        pCAN->CMR  = 0x21;                           /* Start transmission without loop-back */
        return msg->len;
    }
    return CAN_BUSY;
}

static int32 can_read( TOSDrive *dev, uint32 pos, uint8 *buff, uint32 size )
{
    TCANbuff *pCAN = (TCANbuff*)dev->pdata;
    if(buff == NULL)
        return 0;

    if( pCAN )
    {
        if( pCAN->Rxcnt )
        {
            pCAN->Rxcnt--;
#if 1
            memcpy( buff, (uint8*)&pCAN->Rxbuff[ pCAN->Rxout], sizeof( CAN_msg ));
#else
            CAN_msg *msg = (CAN_msg *) buff;
            *msg = pCAN->Rxbuff[ pCAN->Rxout];
#endif
            pCAN->Rxout++;
            if( pCAN->Rxout >= BUFF_SIZE )
                pCAN->Rxout = 0;
            return 1;
        }
    }
    return 0;
}


static int32 can_contrl( TOSDrive *dev, uint32 cmd, void *argv)
{
    switch( cmd )
    {
        case DRIVE_CTRL_WRITE:
            return can_write( dev, 0, argv, 1 );
        case DRIVE_CTRL_READ:
            return can_read( dev, 0, argv, 1 );
    }
    return -1;
}


/*----------------------------------------------------------------------------
  read a message from CAN peripheral and release it.  CAN controller (1..2)
 *----------------------------------------------------------------------------*/
static void CAN_rdMsg (uint32 ctrl)  
{
    LPC_CAN_TypeDef *pCAN ;
    TCANbuff *pBuf;
    if(ctrl == 1)
    {
        pCAN = LPC_CAN1;
        pBuf = &CANbuff[0];
    }else
    {
        pCAN = LPC_CAN2;
        pBuf = &CANbuff[1];
    }

    if( pBuf->Rxcnt < BUFF_SIZE )
    {
         /* Read frame informations */
        pBuf->Rxbuff[ pBuf->Rxin].Frame = pCAN->RFS;
        pBuf->Rxbuff[ pBuf->Rxin].id    = pCAN->RID;
        pBuf->Rxbuff[ pBuf->Rxin].DataA = pCAN->RDA;
        pBuf->Rxbuff[ pBuf->Rxin].DataB = pCAN->RDB;

        pBuf->Rxin++;
        if( pBuf->Rxin >= BUFF_SIZE )
            pBuf->Rxin = 0;
        pBuf->Rxcnt++;
    }
}


/*----------------------------------------------------------------------------
  CAN interrupt handler
 *----------------------------------------------------------------------------*/

__AFTER__ void CAN_IRQHandler (void) ;
void CAN_IRQHandler (void) 
{
    uint32 icr;
    /* check CAN controller 1 */
    icr = LPC_CAN1->ICR;                           /* clear interrupts */
    if (icr & (1 << 0)) {                          /* CAN Controller #1 meassage is received */
        CAN_rdMsg( 1 );
        LPC_CAN1->CMR = (1 << 2);                  /* Release receive buffer */
    }

    if (icr & (1 << 1)) {                          /* CAN Controller #1 meassage is transmitted */
    }

    /* check CAN controller 2 */
    icr = LPC_CAN2->ICR;                           /* clear interrupts */
    if (icr & (1 << 0)) {                          /* CAN Controller #2 meassage is received */
        CAN_rdMsg( 2 );
        LPC_CAN2->CMR = (1 << 2);
    }

    if (icr & (1 << 1)) {                          /* CAN Controller #2 meassage is transmitted */
    }
}

__DriveBegin( CAN1 )
    .num = 1,
    .baudrate = 20000,
    .open  = can_open,
    .write = can_write, 
    .read  = can_read,
    .contrl = can_contrl,
    .pdata = &CANbuff[0],
__DriveEnd();


__DriveBegin( CAN2 )
    .num = 2,
    .baudrate = 20000,
    .open  = can_open,
    .write = can_write, 
    .read  = can_read,
    .contrl = can_contrl,
    .pdata = &CANbuff[1],
__DriveEnd();


