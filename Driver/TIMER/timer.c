#include "timer.h"

static void (*TIM2_Callbacks)(void) = 0;

void TIM2_Init(TIM_Config_t *cfg){
    /* Enable clock */
    RCC->APB1ENR |= (1 << 0);

    /* Reset TIM2 */
    RCC->APB1RSTR |=  (1 << 0);
    RCC->APB1RSTR &= ~(1 << 0);

    /* Stop timer */
    TIM2->CR1 &= ~TIM_CR1_CEN;

    /* Configure */
    TIM2->PSC = cfg->PSC;
    TIM2->ARR = cfg->ARR;

    /* Reload registers */
    TIM2->EGR |= TIM_EGR_UG;

    /* Clear flag */
    TIM2->SR &= ~TIM_SR_UIF;

    /* Enable interrupt */
		if(cfg->it_flag){
			TIM2->DIER |= TIM_DIER_UIE;
			NVIC_EnableIRQ(TIM2_IRQn);
		}
    
    /* Save callback */
		if(cfg->Callback){
			TIM2_Callbacks = cfg->Callback;
		}
   
    /* Start timer */
    TIM2->CR1 |= TIM_CR1_CEN;
}

/*==================== IRQ ====================*/
void TIM2_IRQHandler(void){
    if(TIM2->SR & TIM_SR_UIF){
        TIM2->SR &= ~TIM_SR_UIF;

        if(TIM2_Callbacks){
            TIM2_Callbacks();
        }
    }
}

/*==================== DELAY (BLOCKING) ====================*/
void Delay_ms(uint32_t time){
    if(time == 0) return;

    /* Backup */
    uint32_t psc  = TIM2->PSC;
    uint32_t arr  = TIM2->ARR;
    uint32_t cr1  = TIM2->CR1;
    uint32_t dier = TIM2->DIER;

    /* Stop */
    TIM2->CR1 &= ~TIM_CR1_CEN;

    /* Disable interrupt */
    TIM2->DIER &= ~TIM_DIER_UIE;

    /*
        Config:
        84MHz / (41999 + 1) = 2000Hz ? 0.5ms
        => ARR = 2*time - 1 ? time (ms)
    */
    TIM2->PSC = 41999;
    TIM2->ARR = (2 * time) - 1;
    TIM2->CNT = 0;

    /* Update */
    TIM2->EGR |= TIM_EGR_UG;

    /* Clear flag */
    TIM2->SR &= ~TIM_SR_UIF;

    /* Start */
    TIM2->CR1 |= TIM_CR1_CEN;

    /* Wait */
    while(!(TIM2->SR & TIM_SR_UIF));

    /* Stop */
    TIM2->CR1 &= ~TIM_CR1_CEN;

    /* Restore */
    TIM2->PSC  = psc;
    TIM2->ARR  = arr;
    TIM2->DIER = dier;
    TIM2->CR1  = cr1;

    TIM2->EGR |= TIM_EGR_UG;
    TIM2->SR &= ~TIM_SR_UIF;
}