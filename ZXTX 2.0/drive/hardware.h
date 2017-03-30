


#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include "bsp.h"
#include "../bsp/mytype.h"

#define LED_NOT           NBI_P( 2, 10)
#define LED_ON            CBI_P( 2, 10)
#define LED_OFF           SBI_P( 2, 10)


void  IO_init(void);

#undef EXT
#endif /* __HARDWARE_H__ */



