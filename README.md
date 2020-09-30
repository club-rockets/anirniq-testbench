# avionique-testbench

/!\ MERCI DE MODIFIER UNIQUEMENT LE FICHIER SRC/MAIN.C DANS CE REPOSITORY /!\

Projet avionique testbench

Spec :

    Architecture : ARM
    Processeur : RISC CORTEX M
    Jeu d'instructions : ARMv7-M (Cortex M4)
    Manufacturier : ST
    Carte de developpement : STM32F4DISCOVERY

Couche d'abstraction :

    1 - CMSIS
    2 - FATFS
    3 - FREERTOS (OUTDATED)
   
Fichier :

    .
    ├── Drivers
    │   ├── LCD
    │   │   ├── LCD_Driver.c
    │   │   └── LCD_Driver.h
    │   ├── Pression
    │   │   ├── ADC_Driver.c
    │   │   └── ADC_Driver.h
    │   ├── RFD900
    │   │   ├── uart2.c
    │   │   └── uart2.h
    │   ├── SD
    │   │   ├── fatfs_sd.c
    │   │   └── fatfs_sd.h
    │   └── loadcell
    │       ├── HX711.c
    │       └── HX711.h
    ├── Libraries
    │   ├── CMSIS
    │   │   ├── CMSIS END USER LICENCE AGREEMENT.pdf
    │   │   └── Include
    │   │       ├── arm_common_tables.h
    │   │       ├── arm_math.h
    │   │       ├── core_cm4.h
    │   │       ├── core_cm4_simd.h
    │   │       ├── core_cmFunc.h
    │   │       └── core_cmInstr.h
    │   ├── Device
    │   │   └── STM32F4xx
    │   │       ├── Include
    │   │       │   ├── stm32f4xx.h
    │   │       │   └── system_stm32f4xx.h
    │   │       └── Release_Notes.html
    │   └── STM32F4xx_StdPeriph_Driver
    │       ├── Release_Notes.html
    │       ├── inc
    │       │   ├── misc.h
    │       │   ├── stm32f4xx_adc.h
    │       │   ├── stm32f4xx_can.h
    │       │   ├── stm32f4xx_crc.h
    │       │   ├── stm32f4xx_cryp.h
    │       │   ├── stm32f4xx_dac.h
    │       │   ├── stm32f4xx_dbgmcu.h
    │       │   ├── stm32f4xx_dcmi.h
    │       │   ├── stm32f4xx_dma.h
    │       │   ├── stm32f4xx_exti.h
    │       │   ├── stm32f4xx_flash.h
    │       │   ├── stm32f4xx_fsmc.h
    │       │   ├── stm32f4xx_gpio.h
    │       │   ├── stm32f4xx_hash.h
    │       │   ├── stm32f4xx_i2c.h
    │       │   ├── stm32f4xx_iwdg.h
    │       │   ├── stm32f4xx_pwr.h
    │       │   ├── stm32f4xx_rcc.h
    │       │   ├── stm32f4xx_rng.h
    │       │   ├── stm32f4xx_rtc.h
    │       │   ├── stm32f4xx_sdio.h
    │       │   ├── stm32f4xx_spi.h
    │       │   ├── stm32f4xx_syscfg.h
    │       │   ├── stm32f4xx_tim.h
    │       │   ├── stm32f4xx_usart.h
    │       │   └── stm32f4xx_wwdg.h
    │       └── src
    │           ├── misc.c
    │           ├── stm32f4xx_adc.c
    │           ├── stm32f4xx_can.c
    │           ├── stm32f4xx_crc.c
    │           ├── stm32f4xx_cryp.c
    │           ├── stm32f4xx_cryp_aes.c
    │           ├── stm32f4xx_cryp_des.c
    │           ├── stm32f4xx_cryp_tdes.c
    │           ├── stm32f4xx_dac.c
    │           ├── stm32f4xx_dbgmcu.c
    │           ├── stm32f4xx_dcmi.c
    │           ├── stm32f4xx_dma.c
    │           ├── stm32f4xx_exti.c
    │           ├── stm32f4xx_flash.c
    │           ├── stm32f4xx_fsmc.c
    │           ├── stm32f4xx_gpio.c
    │           ├── stm32f4xx_hash.c
    │           ├── stm32f4xx_hash_md5.c
    │           ├── stm32f4xx_hash_sha1.c
    │           ├── stm32f4xx_i2c.c
    │           ├── stm32f4xx_iwdg.c
    │           ├── stm32f4xx_pwr.c
    │           ├── stm32f4xx_rcc.c
    │           ├── stm32f4xx_rng.c
    │           ├── stm32f4xx_rtc.c
    │           ├── stm32f4xx_sdio.c
    │           ├── stm32f4xx_spi.c
    │           ├── stm32f4xx_syscfg.c
    │           ├── stm32f4xx_tim.c
    │           ├── stm32f4xx_usart.c
    │           └── stm32f4xx_wwdg.c
    ├── Makefile
    ├── README.md
    ├── Utilities
    │   └── STM32F4-Discovery
    │       ├── MCD-ST Liberty SW License Agreement V2.pdf
    │       ├── Release_Notes.html
    │       ├── libPDMFilter_GCC.a
    │       ├── pdm_filter.h
    │       ├── stm32f4_discovery.c
    │       ├── stm32f4_discovery.h
    │       ├── stm32f4_discovery_audio_codec.c
    │       ├── stm32f4_discovery_audio_codec.h
    │       ├── stm32f4_discovery_lis302dl.c
    │       └── stm32f4_discovery_lis302dl.h
    ├── src
    │   ├── main.c
    │   ├── startup_stm32f40xx.s
    │   ├── stm32f4xx_conf.h
    │   ├── stm32f4xx_it.c
    │   ├── stm32f4xx_it.h
    │   ├── syscalls.c
    │   ├── system_stm32f4xx.c
    │   └── tiny_printf.c
    └── stm32f4_flash.ld
    
 Version :
    
    debug 0 : 2020-09-06 (master)
