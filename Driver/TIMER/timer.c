#include "timer.h"

void TIM2_Init(TIM_Config_t *cfg){
		//clock
		RCC->APB1ENR |= (1 << 0);
		//reset timer
		RCC->APB1RSTR |= ( 1<< 0);
		RCC->APB1RSTR &= ~( 1<< 0);
		
		//Reset cnt
		TIM2->CNT = 0;
		//configure
		TIM2->PSC = cfg->PSC;
		TIM2->ARR = cfg->ARR;
	
		//clear pending 
		TIM2->SR &= ~(1 << 0);
		//enable interrupt
		TIM2->DIER |= (1 << 0);
	
		//callback
		TIM2_Callbacks = cfg->Callback;
		//Nvic enable
		NVIC->ISER[0] |= (1 <<28);
		//start timer
		TIM2->CR1 |= (1 << 0);//couter enable
} 

void TIM2_IRQHandler(void){
		if(TIM2->SR & (1 << 0)){
			TIM2->SR &= ~(1 << 0);
			if(TIM2_Callbacks){
				TIM2_Callbacks();
			}
		}
}

void Delay_ms(uint32_t time){
    RCC->APB1ENR |= (1 << 0);

    TIM2->CR1 = 0;        // STOP

    TIM2->PSC = 41999;
    TIM2->ARR = time*2 - 1;
    TIM2->CNT = 0;

    TIM2->EGR = 1;        // LOAD

    TIM2->SR = 0;

    TIM2->CR1 = 1;        // START

    while(!(TIM2->SR & 1));

    TIM2->CR1 = 0;        // STOP
    TIM2->SR = 0;
}
	
	

