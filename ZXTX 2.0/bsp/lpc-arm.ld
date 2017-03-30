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


__ram_size__       = LENGTH(RAM);
__ram_top_stack__  = ORIGIN(RAM) + __ram_size__ ;
__stack_end__      = __ram_top_stack__ ;

__flash_32k        = ORIGIN(ROM) + 32K;
__flash_60k        = ORIGIN(ROM) + 60K;
__flash_64k        = ORIGIN(ROM) + 64K;
__flash_128k       = ORIGIN(ROM) + 128K;
__flash_256k       = ORIGIN(ROM) + 256K;
__flash_end        = ORIGIN(ROM) + LENGTH(ROM);

/* Section Definitions */
SECTIONS
{
   .text : ALIGN(4)
  {
    FILL( 0xFF)
	KEEP(*(.isr_vector .isr_vector.*))
    *(.after_vectors .after_vectors.*)

    . = __CRP_ADDR;
	KEEP(*(.crp .crp.*))    /*¼ÓÃÜÎ»*/

	*(.text .text.*)
	*(.glue_7)
	*(.glue_7t)
	*(.gcc_except_table)
    . = ALIGN(4);
	*(.gnu.linkonce.r.*)
  } > ROM
 
  .rodata : ALIGN(4)
  {
    *(.rodata .rodata.* .gnu.linkonce.r.*)
  } > ROM

  .shell : ALIGN(4)
  {
      KEEP( *(.shell .shell.*));
      PROVIDE (shell_end = .);
  } > ROM

  PROVIDE (shell_start = LOADADDR(.shell) );
  PROVIDE (shell_size  = SIZEOF(.shell) );

  .drive : ALIGN(4)
  {
      KEEP( *(.drive .drive.*));
      PROVIDE (drive_end = .);
  } > ROM
  PROVIDE (drive_start = LOADADDR(.drive) );
  PROVIDE (drive_size  = SIZEOF(.drive)); 

	__exidx_end = .;
	_etext = .;

  .data : AT (_etext)  ALIGN(4)
  {
	_data = .;
	*(.data .data.*)
	_edata = . ;
  } > RAM
 
  /* .bss section which is used for uninitialized data */
  .bss (NOLOAD)  : ALIGN(4)
  {
    _bss = . ;
    *(.bss .bss.*)
    *(.gnu.linkonce.b*)
    *(COMMON)
	_ebss = . ;
  } > RAM

  .udata  (NOLOAD) : ALIGN(4)
  {
      *(.udata*);
  } > USRAM

  __udata_end = .;
  PROVIDE(_udata_end = .);

  .ndata  (NOLOAD) : ALIGN(4)
  {
      *(.ndata*);
  } > NSRAM
  __ndata_end = .;
  PROVIDE(_ndata_end = .);
  
 
  .sdram  (NOLOAD) : ALIGN(4)
  {
      KEEP(*(.sdram*));
  } > SDRAM
  __sdram_end = .;
  PROVIDE(_sdram_end = .);
  
  .ddram  (NOLOAD) : ALIGN(4)
  {
      KEEP(*(.ddram*));
  } > DDRAM
  __ddram_end = .;
  PROVIDE(_ddram_end = .);
   
  .noinit (NOLOAD): ALIGN(4)
  {
      PROVIDE (__noinit_start = .);
      *(.noinit);
  } > RAM

  .stack (NOLOAD)  :  ALIGN(32)
  {
      PROVIDE (stack_start = .);
      *(.stack*)
      PROVIDE (_stack = .);
  } > RAM

  . = ALIGN(4);
  _end = . ;
  PROVIDE (__end = .);
  PROVIDE (_stack_end = __stack_end__ );
  PROVIDE (_ram_top = __ram_top_stack__ );
    
  /* Stabs debugging sections.  */
  .stab          0 : { *(.stab) }
  .stabstr       0 : { *(.stabstr) }
  .stab.excl     0 : { *(.stab.excl) }
  .stab.exclstr  0 : { *(.stab.exclstr) }
  .stab.index    0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
}

