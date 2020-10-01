# Makefile projet avionique-testbench
# Version 0 : 12/09/2020
# Nathan Roussel
# nathan.roussel.1@ens.etsmtl.ca

######################################
# target
######################################
TARGET = avionique-testbench


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = Debug
ASM_DIR = src

######################################
# source
######################################
# C sources using tree -f
C_SOURCES =  \
Libraries/STM32F4xx_StdPeriph_Driver/src/misc.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c \
Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c \
Utilities/STM32F4-Discovery/stm32f4_discovery.c \
Utilities/STM32F4-Discovery/stm32f4_discovery_audio_codec.c \
Utilities/STM32F4-Discovery/stm32f4_discovery_lis302dl.c \
src/main.c \
src/stm32f4xx_it.c \
src/syscalls.c \
src/system_stm32f4xx.c \
Drivers/UART/uart1.c \
Drivers/UART/uart2.c \
src/tiny_printf.c
#Drivers/LCD/LCD_Driver.c
#Drivers/Pression/ADC_Driver.c

#Drivers/SD/fatfs_sd.c
#Drivers/loadcell/HX711.c

# ASM sources
ASM_SOURCES =  \
src/startup_stm32f40xx.s

#######################################
# binaries
#######################################
PREFIX = arm-atollic-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \


# AS includes
AS_INCLUDES =  \
-I\Inc

# C includes
C_INCLUDES =  \
-ILibraries/STM32F4xx_StdPeriph_Driver/inc \
-ILibraries/CMSIS/Include \
-ILibraries/Device/STM32F4xx/Include \
-IUtilities/STM32F4-Discovery \
-IDrivers/UART \
-Isrc


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = stm32f4_flash.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		
	@echo "\033[0;35mOh shit, here we go again\033[0m"

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
	@echo "\033[0;32mClean as fuck\033[0m"
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)