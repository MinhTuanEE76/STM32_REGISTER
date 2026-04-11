#include "gpio.h"


void GPIO_Config(volatile GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                 uint8_t Mode, uint8_t Type, uint8_t Pull, uint8_t Speed)
{
    uint32_t pos = 0;
    uint32_t mask_2bit;

    for (pos = 0; pos < 16u; pos++)
    {
        if (GPIO_Pin & (1UL << pos))
        {
            mask_2bit = 0x03UL << (pos * 2);

            GPIOx->MODER   = (GPIOx->MODER   & ~mask_2bit) | ((uint32_t)Mode   << (pos * 2));
            GPIOx->OTYPER  = (GPIOx->OTYPER  & ~(1UL << pos)) | ((uint32_t)Type << pos);
            GPIOx->OSPEEDR = (GPIOx->OSPEEDR & ~mask_2bit) | ((uint32_t)Speed  << (pos * 2));
            GPIOx->PUPDR   = (GPIOx->PUPDR   & ~mask_2bit) | ((uint32_t)Pull   << (pos * 2));
        }
    }
}

void GPIO_WritePin(volatile GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t State){
    if(State == GPIO_PIN_SET){
        GPIOx->BSRR = GPIO_Pin;          // SET
    }else{
        GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U;   // RESET
    }
}

uint8_t GPIO_ReadPin(volatile GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	if(GPIOx->IDR & GPIO_Pin){
		return GPIO_PIN_SET;
	}
	else 
		return GPIO_PIN_RESET;
}

void GPIO_TogglePin(volatile GPIO_TypeDef* GPIOx, uint8_t GPIO_Pin){
	GPIOx->ODR ^= GPIO_Pin;
}

void GPIO_AF_Init(const GPIO_AF_TypeDef *Af, uint8_t Type, uint8_t Pull, uint8_t Speed){
		if(Af == NULL) return;
		
		volatile GPIO_TypeDef *GPIOx = Af->Port;
		
		//Check PORT , enbale clock
		if(GPIOx == GPIOA){
			RCC->AHB1ENR.REG |= RCC_AHB1ENR_GPIOAEN;
		}
		else if(GPIOx == GPIOB){
			RCC->AHB1ENR.REG |= RCC_AHB1ENR_GPIOBEN;
		}
		else if(GPIOx == GPIOC){
			RCC->AHB1ENR.REG |= RCC_AHB1ENR_GPIOCEN;
		}
		else if(GPIOx == GPIOD){
			RCC->AHB1ENR.REG |= RCC_AHB1ENR_GPIODEN;
		}
		else if(GPIOx == GPIOE){
			RCC->AHB1ENR.REG |= RCC_AHB1ENR_GPIOEEN;
		}
		//add others if use
		
		uint8_t position;
		for(position = 0 ; position < 16; position++){
  			if(Af->Pin & (1 << position)){
				break;
			}
		}
		//configuration
		GPIOx->MODER    = (GPIOx->MODER   & ~(2U << (position*2))  | (2U << (position*2))) ; //0b10 :ALTF
		GPIOx->OTYPER   = (GPIOx->OTYPER  & ~(1U << position)      | (Type <<  position));
		GPIOx->OSPEEDR  = (GPIOx->OSPEEDR & ~(3U << (position*2))  | (Speed<< (position*2))) ; 
		GPIOx->PUPDR    = (GPIOx->PUPDR   & ~(3U << (position*2))  | (Pull << (position*2))) ; 
		
		//AFR configure
		
		if(position < 8U){
			//AFRL
			GPIOx->AFRL = (GPIOx->AFRL & ~(15 << (position*4) ) | (Af->AF << (position*4)) );
		}
		else{
			//AFRH
			uint8_t shift = position -8;
			GPIOx->AFRH = (GPIOx->AFRH & ~(15 << (shift*4) ) | (Af->AF << (shift*4)) );
		}
}

