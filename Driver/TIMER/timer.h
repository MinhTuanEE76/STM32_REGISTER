#ifndef __TIM_H
#define __TIM_H

#include <stdint.h>
#include <stdbool.h>
#include "rcc.h"
#include "exti.h"

/*==================== TIM CR1 ====================*/
#define TIM_CR1_CEN        (1U << 0)
#define TIM_CR1_UDIS       (1U << 1)
#define TIM_CR1_URS        (1U << 2)
#define TIM_CR1_OPM        (1U << 3)
#define TIM_CR1_DIR        (1U << 4)
#define TIM_CR1_ARPE       (1U << 7)

/*==================== TIM DIER ====================*/
#define TIM_DIER_UIE       (1U << 0)

/*==================== TIM SR ====================*/
#define TIM_SR_UIF         (1U << 0)

/*==================== TIM EGR ====================*/
#define TIM_EGR_UG         (1U << 0)

#define ADD_BASE_TIM2 			0x40000000UL
#define ADD_BASE_TIM3 			0x40000400UL
#define ADD_BASE_TIM4 			0x40000800UL
#define ADD_BASE_TIM5 			0x40000C00UL

typedef struct{
    volatile uint32_t CR1;      // 0x00
    volatile uint32_t CR2;      // 0x04
    volatile uint32_t SMCR;     // 0x08
    volatile uint32_t DIER;     // 0x0C
    volatile uint32_t SR;       // 0x10
    volatile uint32_t EGR;      // 0x14
    volatile uint32_t CCMR1;    // 0x18
    volatile uint32_t CCMR2;    // 0x1C
    volatile uint32_t CCER;     // 0x20
    volatile uint32_t CNT;      // 0x24
    volatile uint32_t PSC;      // 0x28
    volatile uint32_t ARR;      // 0x2C
    volatile uint32_t RCR;      // 0x30 (TIM2 not use -> align)
    volatile uint32_t CCR1;     // 0x34
    volatile uint32_t CCR2;     // 0x38
    volatile uint32_t CCR3;     // 0x3C
    volatile uint32_t CCR4;     // 0x40
    volatile uint32_t BDTR;     // 0x44 (align)
    volatile uint32_t DCR;      // 0x48
    volatile uint32_t DMAR;     // 0x4C
} TIM2_TypeDef;

#define TIM2 						((volatile TIM2_TypeDef*)ADD_BASE_TIM2)

typedef struct{
		uint32_t PSC;
		uint32_t ARR;
		bool it_flag;
		void (*Callback)(void);
} TIM_Config_t;

static void(*TIM2_Callbacks)(void);

/*------------------------Function Prototype---------------------------*/
void TIM2_Init(TIM_Config_t *cfg);
void Delay_ms(uint32_t time);


#endif 