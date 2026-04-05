#ifndef __EXTI_H
#define __EXTI_H

#include "type.h"
#include "syscfg.h"
#include "gpio.h"
#include "nvic.h"

/*--------------Exti typedef---------------------*/
typedef struct{
	__32BIT IMR;    //0x00
	__32BIT EMR;    //0x04
	__32BIT RTSR;		//0x08
	__32BIT FTSR;		//0x0C
	__32BIT SWIER;	//0x10
	__32BIT PR;			//0x14
}EXTI_TypeDef;

#define EXTI ((volatile EXTI_TypeDef*)0x40013C00UL)
	
//=====================Define Port Pin for EXTI=========================
typedef enum{
				RISING_TRIGGER = 0U,
				FALLING_TRIGGER		 ,
				BOTH_TRIGGER
} EXTI_Trigger_t;

typedef struct{
				GPIO_Port_t    Port_Pin;
				uint16_t       GPIO_Pin;
				EXTI_Trigger_t Trigger ;
				void (*callback)(void);
}EXTI_Config_t;



/*===============Function Prototype=========================*/

// EXTI0_Init(GPIO_Port_t Port_Pin, EXTI_Trigger_t Trigger);
//void EXTI1_Init(PORT_Pin_t Port_Pin, EXTI_Trigger_t Trigger);
//void EXTI2_Init(PORT_Pin_t Port_Pin, EXTI_Trigger_t Trigger);
//void EXTI3_Init(PORT_Pin_t Port_Pin, EXTI_Trigger_t Trigger);
//void EXTI4_Init(PORT_Pin_t Port_Pin, EXTI_Trigger_t Trigger);
//void EXTI5_Init(PORT_Pin_t Port_Pin, EXTI_Trigger_t Trigger);
//void EXTI6_Init(PORT_Pin_t Port_Pin, EXTI_Trigger_t Trigger);
//void EXTI7_Init(PORT_Pin_t Port_Pin, EXTI_Trigger_t Trigger);
//void EXTI8_Init(PORT_Pin_t Port_Pin, EXTI_Trigger_t Trigger);
//void EXTI9_Init(PORT_Pin_t Port_Pin, EXTI_Trigger_t Trigger);
//void EXTI10_Init(PORT_Pin_t Port_Pin, EXTI_Trigger_t Trigger);
//void EXTI11_Init(PORT_Pin_t Port_Pin, EXTI_Trigger_t Trigger);
//void EXTI12_Init(PORT_Pin_t Port_Pin, EXTI_Trigger_t Trigger);
//void EXTI13_Init(PORT_Pin_t Port_Pin, EXTI_Trigger_t Trigger);
//void EXTI14_Init(PORT_Pin_t Port_Pin, EXTI_Trigger_t Trigger);
//void EXTI15_Init(PORT_Pin_t Port_Pin, EXTI_Trigger_t Trigger);

void EXTI_Init(EXTI_Config_t *cfg);


#endif
