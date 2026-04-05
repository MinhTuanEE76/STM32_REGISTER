#ifndef __AFIO_H_
#define __AFIO_H_

#include <stdint.h>
#include "gpio.h"

//=======ALTERNATE FUNCTION NUMBERS================
#define AF0			0U
#define AF1			1U
#define AF2			2U
#define AF3			3U
#define AF4			4U
#define AF5			5U
#define AF6			6U
#define AF7			7U
#define AF8			8U
#define AF9			9U
#define AF10		10U
#define AF11		11U
#define AF12		12U
#define AF13		13U
#define AF14		14U
#define AF15		15U

#define AF_SYSTEM           AF0
#define AF_TIM1_TIM2        AF1
#define AF_TIM3_5           AF2
#define AF_TIM8_11          AF3
#define AF_I2C              AF4
#define AF_SPI1_SPI2        AF5
#define AF_SPI3_I2S         AF6
#define AF_USART123         AF7
#define AF_UART45_USART6    AF8
#define AF_CAN              AF9
#define AF_OTG              AF10
#define AF_ETH              AF11
#define AF_FSMC_SDIO        AF12
#define AF_DCMI             AF13
#define AF_EVENTOUT         AF15

//================AF struct==================
typedef struct{
	volatile GPIO_TypeDef *Port;
	uint16_t Pin;
	uint8_t  AF;//AF0->AF15
} GPIO_AF_TypeDef;

#define 

/*---------------------Define AF Pin-------------------------*/

//USART

#define USART1_TX_PA9			(GPIO_AF_TypeDef){GPIOA,GPIO_PIN_9,AF_USART123}



//==========================Function Prototype======================

void GPIO_AF_Init(const GPIO_AF_TypeDef *Af, uint8_t Type, uint8_t Pull, uint8_t Speed);

#endif