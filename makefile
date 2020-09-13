# Makefile projet testbench
# Version 0 : 12/09/2020
# Nathan Roussel
# nathan.roussel@ens.etsmtl.ca

#-{ Project Relative Paths }----------------------------------------------------
BIN=./Binary
SRC=./src
UTI=./Utilities
LIB=./Libraries
DRV=./Drivers

#-{ Compiler Definitions }------------------------------------------------------

# Compiler
CC=arm-none-eabi-gcc

# Device specific flags [1]
DFLAGS=-mcpu=cortex-m4 #-mthumb -msoft-float # A verifier

# Compiler flags
CFLAGS=$(DFLAGS) -g -c -Wall -Wextra

# Linker
LD=arm-none-eabi-gcc

# Path to linker script
LSCRIPT=stm32f4_flash.ld

# Linker flags
LFLAGS=-T $(LSCRIPT) --specs=nosys.specs

# Object copy (for converting formats)
OBJCOPY=arm-none-eabi-objcopy
OFLAGS=-O ihex


