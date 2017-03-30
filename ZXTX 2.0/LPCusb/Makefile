# Hey Emacs, this is a -*- makefile -*-
#
# WinARM template makefile
# by Martin Thomas, Kaiserslautern, Germany
# <eversmith@heizung-thomas.de>
#
# based on the WinAVR makefile written by Eric B. Weddington, Jörg Wunsch, et al.
# Released to the Public Domain
# Please read the make user manual!
#
#
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make program = Download the hex file to the device, using lpc21isp
#
# (TODO: make filename.s = Just compile filename.c into the assembler code only)
#
# To rebuild project do "make clean" then "make all".
#
# Changelog:
# - 17. Feb. 2005  - added thumb-interwork support (mth)
# - 28. Apr. 2005  - added C++ support (mth)
# - 29. Arp. 2005  - changed handling for lst-Filename (mth)
#

#FLASH_TOOL = ULINK

CROSS_COMPILE ?= arm-none-eabi-
#CROSS_COMPILE = arm-eabi-
#CROSS_COMPILE = arm-elf-

# MCU name and submodel
MCU      ?= cortex-m3
THUMB    ?= -mthumb
F_CPU    ?= 12

# Object files directory
OBJDIR = obj

# HEX files directory
HEXDIR = testhex
OSLIBC = libLPCusb.a

# List C source files here. (C dependencies are automatically generated.)
# use file-extension c for "c-only"-files
SRC = 

# List C source files here which must be compiled in ARM-Mode.
# use file-extension c for "c-only"-files

OSSRC = 

#myLib
MYLIBSRC = 

#myGUI
GUISRC  = 

#SRCARM += $(GUISRCARM)


# List C++ source files here.
# use file-extension cpp for C++-files
CPPSRC =


# List Assembler source files here.
# Make them always end in a capital .S.  Files ending in a lowercase .s
# will not be considered source files but generated files (assembler
# output from the compiler), and will be deleted upon "make clean"!
# Even though the DOS/Win* filesystem matches both .s and .S the same,
# it will preserve the spelling of the filenames, and gcc itself does
# care about how the name is spelled on its command-line.
ASRC = 

include src/Makefile


SRC += $(LSRC)

# Optimization level, can be [0, 1, 2, 3, s].
# 0 = turn off optimization. s = optimize for size.
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = s

# Debugging format.
# Native formats for AVR-GCC's -g are stabs [default], or dwarf-2.
# AVR (extended) COFF requires stabs, plus an avr-objcopy run.
#DEBUG = stabs
DEBUG = dwarf-2

# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
#EXTRAINCDIRS = ./include
#EXTRAINCDIRS = ./inc ./conf

EXTRAINCDIRS = 	src inc \
				../LPC_CMSIS/inc

VPATH = $(EXTRAINCDIRS)

# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD = -std=gnu99

# Place -D or -U options for C here
CDEFS += -DF_CPU=$(F_CPU)000000UL

# Place -I options here
CINCS =

# Place -D or -U options for ASM here
ADEFS =  -D$(RUN_MODE)


# Compiler flags.
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
#
# Flags for C and C++ (arm-elf-gcc/arm-elf-g++)
CFLAGS = -g3
CFLAGS += $(CDEFS) $(CINCS)
CFLAGS += -O$(OPT)
CFLAGS += -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections

CFLAGS += -Wa,-adhlns=$(@:%.o=%.lst)
CFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))

# flags only for C
CONLYFLAGS  = -Wstrict-prototypes -Wmissing-declarations
CONLYFLAGS += -Wmissing-prototypes -Wnested-externs
CONLYFLAGS += $(CSTANDARD)

# flags only for C++ (arm-elf-g++)
# CPPFLAGS = -fno-rtti -fno-exceptions
CPPFLAGS =

# Assembler flags.
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -ahlms:    create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see avr-libc docs [FIXME: not yet described there]
##ASFLAGS = -Wa,-adhlns=$(@:%.o=%.lst),-gstabs
ASFLAGS = $(ADEFS) -Wa,-adhlns=$(@:%.o=%.lst),-g$(DEBUG)

# ---------------------------------------------------------------------------

# Define directories, if needed.
## DIRARM = c:/WinARM/
## DIRARMBIN = $(DIRAVR)/bin/
## DIRAVRUTILS = $(DIRAVR)/utils/bin/

# Define programs and commands.
SHELL = sh
CC      = $(CROSS_COMPILE)gcc
CPP     = $(CROSS_COMPILE)g++
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
SIZE    = $(CROSS_COMPILE)size
NM      = $(CROSS_COMPILE)nm
AR      = $(CROSS_COMPILE)ar
REMOVE  = rm -rf
COPY    = cp


# Define Messages
# English
MSG_ERRORS_NONE = Errors: none
MSG_BEGIN       = -------- begin -------- 
MSG_END         = --------  end  --------
MSG_SIZE_BEFORE = Size before:
MSG_SIZE_AFTER  = Size after:
MSG_FLASH       = Creating load file for Flash:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE     = Creating Symbol Table:
MSG_LINKING          = Linking:
MSG_COMPILING        = Compiling C:
MSG_COMPILING_ARM    = "Compiling C (ARM-only):"
MSG_COMPILINGCPP     = Compiling C++:
MSG_COMPILINGCPP_ARM = "Compiling C++ (ARM-only):"
MSG_ASSEMBLING       = Assembling:
MSG_ASSEMBLING_ARM   = "Assembling (ARM-only):"
MSG_CLEANING         = Cleaning project:
MSG_LPC21_RESETREMINDER = You may have to bring the target in bootloader-mode now.


# Define all object files.
COBJ      = $(SRC:%.c=$(OBJDIR)/%.o)
AOBJ      = $(ASRC:%.s=$(OBJDIR)/%.o)

# Define all listing files.
LST = $(ASRC:.s=.lst)  $(SRC:.c=.lst) 

# Compiler flags to generate dependency files.
### GENDEPFLAGS = -Wp,-M,-MP,-MT,$(*F).o,-MF,.dep/$(@F).d
GENDEPFLAGS = -MD -MP -MF .dep/$(@F).d
#GENDEPFLAGS = -MD

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = -mcpu=$(MCU) $(THUMB_IW) -I. $(CFLAGS) $(GENDEPFLAGS)
ALL_ASFLAGS = -mcpu=$(MCU) $(THUMB_IW) -I. -x assembler-with-cpp $(ASFLAGS)


# Default target.
all: lib 

build: clean_file lib

lib: $(OSLIBC)


# Eye candy.
begin:
	@echo
	@echo $(MSG_BEGIN)

finished:
	@echo $(MSG_ERRORS_NONE)

end:
	@echo $(MSG_END)
	@echo

# Display compiler version information.
gccversion :
	@$(CC) --version


# Create extended listing file from ELF output file.
# testing: option -C
%.lss: %.elf
	@echo
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -S -C $< > $@


# Create a symbol table from ELF output file.
%.sym: %.elf
	@echo
	@echo $(MSG_SYMBOL_TABLE) $@
	$(NM) -n $< > $@


.PRECIOUS :  $(AOBJ) $(COBJ)
%.a:  $(AOBJ) $(COBJ)
	@echo
	@echo $(MSG_LINKING) $@
	$(AR) -cr  $@  $^


# Link: create ELF output file from object files.
.SECONDARY : $(TARGET).elf
.PRECIOUS :  $(AOBJ) $(COBJ)
%.elf:  $(AOBJARM) $(AOBJ) $(COBJARM) $(COBJ) $(CPPOBJ) $(CPPOBJARM)
	@echo
	@echo $(MSG_LINKING) $@
	$(CC) $(THUMB) $(ALL_CFLAGS) $(AOBJ) $(COBJ) --output $@ $(LDFLAGS)

# Compile: create object files from C source files. ARM/Thumb
$(OBJDIR)/%.o : %.c
	@echo
	@echo $(MSG_COMPILING) $<
	$(CC) -c $(THUMB) $(ALL_CFLAGS) $(CONLYFLAGS) $< -o $@

%.i : %.c
	@echo
	@echo $(MSG_COMPILING_ARM) $<
	$(CC) -E $(THUMB) $(ALL_CFLAGS) $(CONLYFLAGS) $< -o $(OBJDIR)/$@


# Compile: create assembler files from C source files. ARM/Thumb
## does not work - TODO - hints welcome
##$(COBJ) : %.s : %.c
##	$(CC) $(THUMB) -S $(ALL_CFLAGS) $< -o $@


# Assemble: create object files from assembler source files. ARM/Thumb
$(OBJDIR)/%.o : %.s
	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(CC) -c $(THUMB) $(ALL_ASFLAGS) $< -o $@

# Target: clean project.
clean: begin clean_list finished end


clean_list :
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) $(OBJDIR)
	$(REMOVE) .dep
	$(REMOVE) $(OSLIBC)

clean_obj:
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) $(OBJDIR)
	$(REMOVE) .dep

clean_file:
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) $(OBJDIR)/*
	$(REMOVE) .dep/*
	$(REMOVE) $(OSLIBC)

#$(shell mkdir $(MYDIR)  2>/dev/null)
$(shell mkdir $(OBJDIR) 2>/dev/null)

# Include the dependency files.
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)


# Listing of phony targets.
.PHONY : all buildall begin finish end sizebefore sizeafter gccversion \
	build elf hex lss sym clean clean_list clean_file program isp copy

