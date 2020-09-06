# avionique-testbench
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
    3 - FREERTOS
   
Fichier :

    drivers
        |Pression
        |LCD
        |uart2
        |spi1
        |SD
        |Loadcell
    app
    
    src
    
    middleware
        |freeRTOS
        |fatFS
        
    Utilities
        |STM32F4-Discovery
    
    Libraries
        |CMSIS
            |Include
        |Device
            |STM32F4xx
                |Include
        |STM32F4xx_StdPeriph_Driver
            |inc
            |src
    
 VERSION :
    
    debug 0 : 2020-09-06
