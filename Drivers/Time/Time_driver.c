/*The RCC feeds the external clock of the Cortex System Timer (SysTick) with the AHB clock
(HCLK) divided by 8. The SysTick can work either with this clock or with the Cortex clock
(HCLK), configurable in the SysTick control and status register.





*/
#include "Time_driver.h"
#include "stm32f4xx_it.h"

volatile uint32_t TIMEms = 0;

void systick_initial(uint16_t freq){

	SysTick_Config(1000); //interrupt every 1ms

}

void wait(uint32_t delay){

	uint32_t TIMEmspic = TIMEms;

	while((TIMEms - TIMEmspic) < 100);

}

uint32_t get_time_ms(void){

	return TIMEmspic;
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TIMEms ++; //49 days
}

