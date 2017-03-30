/*----------------------------------------------------------------------------
 *      Name:    vcomdemo.h
 *      Purpose: USB virtual COM port Demo Definitions
 *      Version: V1.02
 *----------------------------------------------------------------------------
 *      This software is supplied "AS IS" without any warranties, express,
 *      implied or statutory, including but not limited to the implied
 *      warranties of fitness for purpose, satisfactory quality and
 *      noninfringement. Keil extends you a royalty-free right to reproduce
 *      and distribute executable files created using this software for use
 *      on NXP Semiconductors LPC microcontroller devices only. Nothing else 
 *      gives you the right to use this software.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef __VCOMDEMO_H__
#define __VCOMDEMO_H__



void VCOM_Init(void);
int  VCOM_Write(const uint8 *buff, int len);
int  VCOM_Read(uint8 *buff);
void VCOM_CheckSerialState (void);


#endif //__VCOMDEMO_H__


