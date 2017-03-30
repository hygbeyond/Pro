
#ifndef __HARDWARE_PRO_H__
#define __HARDWARE_PRO_H__


#include "hardware.h"
#include "MicroOS.h"
#include "user.h"

#define GZ_CALL        0
#define BJ_CALL        1

static inline 
void hard_SY(void)
{
    LED_Set(0xFF);
    CALL_ON;
    OSTimeDly(HZ/2);
    CALL_OFF;
    OSTimeDly(HZ*2);
    LED_Clr(0xFF);
}

static inline
void hard_LEDDis(void)
{
    static int i = 0;
    static int btDly = 0;
    static int gzDly = 0;
    i++;
    if(BD_IN)
    {
        btDly++;
        if( btDly == 20 )
        {
            GZ_Add(0, 0, DATA_GZ_MAINP );
        }
    }else
    {
        btDly = 0;
        GZ_Del(0, 0, DATA_GZ_MAINP );           
    }

    if(GZ_IN)
    {
        gzDly++;
        if( gzDly >= 20 )
        {
            LEDSYSGZ_ON;
            GZ_Add(0, 0, DATA_GZ_BEIP );
        }
    }else
    {
        gzDly = 0;
        LEDSYSGZ_OFF;
        GZ_Del(0, 0, DATA_GZ_BEIP );
    }

    /*指示灯显示控制*/
    Power_Dis();

    if(gzlist.cnt)
    {
        bjstate.state |= 2;
        LEDGZ_ON;
    }else
    {
        if(bjstate.call_en && bjstate.call_state == GZ_CALL)
        {
            bjstate.call_en = 0;
        }
        bjstate.state &= ~2;
        LEDGZ_OFF;
    }

    if( bjlist.cnt )
    {
        LEDBJ_NOT;
    }else
    {
        LEDBJ_OFF;
    }

    if(!bjstate.relay_En)
    {
        OUT_OFF;
    }else
    {
        OUT_ON;
    }

    if(bjstate.call_en && PCALL_EN)
    {
        switch(bjstate.call_state)
        {
            case BJ_CALL:
                CALL_NOT;
                break;
            case GZ_CALL:
                if((i & 0x3) == 0x02)
                {
                    CALL_NOT;
                }
                break;
        }
    }else
    {
        CALL_OFF;
    }
}





#endif



