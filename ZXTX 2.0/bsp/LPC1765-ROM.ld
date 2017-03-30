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
    FLASH (rx)    : ORIGIN = 0x00000000, LENGTH = 256K 
    SRAM (rwx)    : ORIGIN = 0x10000000, LENGTH = 32K
    AHBSRAM0(rwx) : ORIGIN = 0x2007C000, LENGTH = 16k
    AHBSRAM1(rwx) : ORIGIN = 0x20080000, LENGTH = 16k
}




REGION_ALIAS("ROM",   FLASH );
REGION_ALIAS("RAM",   SRAM  );

REGION_ALIAS("SDRAM", SRAM );
REGION_ALIAS("DDRAM", SRAM );

REGION_ALIAS("USRAM", AHBSRAM0 );
REGION_ALIAS("NSRAM", AHBSRAM1 );


__CRP_ADDR = 0x2FC;

INCLUDE "./bsp/lpc-arm.ld"


