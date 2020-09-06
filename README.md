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

    DRIVER
        |CMSIS
        |
    app
    
    src
    
    middleware
        |freeRTOS
        |fatFS
    
