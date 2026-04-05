#include "exti.h"


void (*EXTI_Callbacks[16])(void) = {};


static void EXTI_EnableNVIC(uint8_t pin)
{
    if (pin <= 4)
    {
        NVIC->ISER[0] |= (1UL << (6 + pin) );
    }
    else if (pin <= 9)
    {
        NVIC->ISER[0] |= (1UL << 23);        // EXTI9_5_IRQn = 23
    }
    else  // pin 10 ~ 15
    {
        NVIC->ISER[1] |= (1UL << 8);         // EXTI15_10_IRQn = 40 
    }
}


void EXTI_Init(EXTI_Config_t *cfg){
		//Enable clock for SYSCFG
		RCC->APB2ENR |= (1 << 14);
		
		//find pin index
		uint8_t pin;
		for(pin = 0 ; pin < 16 ; pin++){
			if(cfg->GPIO_Pin & (1 << pin) )
				break;
		}
		
		//mapping
		// each reg 4 EXTI	: EXTICR1->EXTICR4	= 16 Line
		uint8_t reg_index = pin/4;
		uint8_t shift= (pin%4)*4;
		switch(reg_index){
			case 0 :
				SYSCFG->EXTICR1.REG = SYSCFG->EXTICR1.REG & ~(0xFU) | (cfg->Port_Pin << shift);
				break;
			case 1 :
				SYSCFG->EXTICR2.REG = SYSCFG->EXTICR2.REG & ~(0xFU << 4) | (cfg->Port_Pin << shift);
				break;
			case 2 :
				SYSCFG->EXTICR3.REG = SYSCFG->EXTICR3.REG & ~(0xFU << 8) | (cfg->Port_Pin << shift);
				break;
			case 3 : 
				SYSCFG->EXTICR4.REG = SYSCFG->EXTICR4.REG & ~(0xFU << 12) | (cfg->Port_Pin << shift);
				break;
		}
		
		//Trigger
		if(cfg->Trigger == BOTH_TRIGGER){
				EXTI->FTSR.REG |= (1 << pin);
				EXTI->RTSR.REG |= (1 << pin);
		}
		else if(cfg->Trigger == RISING_TRIGGER){
				EXTI->RTSR.REG |= (1 << pin);
		}
		else{
				EXTI->FTSR.REG |= (1 << pin);
		}
		
		//Enable Interrupt
		EXTI->IMR.REG |= (1 << pin);
		//save callback
		EXTI_Callbacks[pin] = cfg->callback;
		
		//EnableNVIC
		EXTI_EnableNVIC(pin);
}

void EXTI_IRQ_Handler_Common(uint16_t GPIO_Pin){
	uint32_t pending = EXTI->PR.REG & GPIO_Pin;
	for(uint8_t position = 0 ; position < 16 ; position++ ){
		if(pending & (1 << position) ){
			//clear pending
			EXTI->PR.REG |= (1 << position);
			//callback
			if(EXTI_Callbacks[position]){
				EXTI_Callbacks[position]();
			}
		}
	}
}

/*===========================EXTI_IRQ===============================*/
void EXTI0_IRQHandler(void){
		EXTI_IRQ_Handler_Common(GPIO_PIN_0);
}

void EXTI1_IRQHandler(void){
		EXTI_IRQ_Handler_Common(GPIO_PIN_1);
}

void EXTI2_IRQHandler(void){
		EXTI_IRQ_Handler_Common(GPIO_PIN_2);
}

void EXTI3_IRQHandler(void){
		EXTI_IRQ_Handler_Common(GPIO_PIN_3);
}

void EXTI4_IRQHandler(void){
		EXTI_IRQ_Handler_Common(GPIO_PIN_4);
}

void EXTI9_5_IRQHandler(void){
	EXTI_IRQ_Handler_Common(GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);
}

void EXTI15_10_IRQHandler(void){
	EXTI_IRQ_Handler_Common(GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
}
