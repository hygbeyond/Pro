/******************************************************************************
 *
 * standalone.ld - Linker script for applications using startup.c and
 *                 DriverLib.
 *
 * Copyright (c) 2005-2007 Luminary Micro, Inc.  All rights reserved.
 *
 * Software License Agreement
 *
 * Luminary Micro, Inc. (LMI) is supplying this software for use solely and
 * exclusively on LMI's microcontroller products.
 *
 * The software is owned by LMI and/or its suppliers, and is protected under
 * applicable copyright laws.  All rights are reserved.  Any use in violation
 * of the foregoing restrictions may subject the user to criminal sanctions
 * under applicable laws, as well as to civil liability for the breach of the
 * terms and conditions of this license.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * LMI SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * This is part of revision 1049 of the Stellaris Driver Library.
 *
 *****************************************************************************/


MEMORY
{
    FLASH (rx)    : ORIGIN = 0x00000000, LENGTH = 512K
    SRAM (rwx)    : ORIGIN = 0x10000000, LENGTH = 64K
    AHBSRAM0(rwx) : ORIGIN = 0x20000000, LENGTH = 32k
    AHBSRAM1(rwx) : ORIGIN = 0x20004000, LENGTH = 16k
    EXRAM(rwx)    : ORIGIN = 0x80000000, LENGTH = 64K
}

REGION_ALIAS("ROM",   SRAM );
REGION_ALIAS("RAM",   SRAM  );
REGION_ALIAS("USRAM", AHBSRAM0 );
REGION_ALIAS("NSRAM", AHBSRAM0 );

REGION_ALIAS("SDRAM", EXRAM );
REGION_ALIAS("DDRAM", EXRAM );

__ExRAM          = ORIGIN( EXRAM );
__ExRAM_end      = ORIGIN(EXRAM) + LENGTH(EXRAM);


__CRP_ADDR = 0x2FC;

INCLUDE "./bsp/lpc-arm.ld"

