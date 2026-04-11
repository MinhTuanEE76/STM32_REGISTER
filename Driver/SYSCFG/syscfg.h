#ifndef __SYSCFG_H_
#define __SYSCFG_H_

#include <stdint.h>
#include "gpio.h"
#include "rcc.h"


typedef struct{
				union{
					uint32_t REG;
					struct {
						uint32_t 	MEM_MODE : 2;
						uint32_t  Reserved : 30;
					}BITS;
				}MEMRMAP;//0x00
				
				union{
					uint32_t REG;
					struct {
						uint32_t  Reserved1 			:23;
						uint32_t  MII_RMII_SEL  	:1;
						uint32_t  Reserved2				:8; 
					}BITS;
				}PMC;//0x04
				
				union{
					uint32_t REG;
					struct {
						uint32_t 	EXTI0 	  :4;
						uint32_t 	EXTI1 		:4;
						uint32_t 	EXTI2 		:4;
						uint32_t 	EXTI3 		:4;
						uint32_t  Reserved  :16;
					}BITS;
				}EXTICR1;//0x08
				
				union{
					uint32_t REG;
					struct {
						uint32_t 	EXTI4 : 4;
						uint32_t 	EXTI5 : 4;
						uint32_t 	EXTI6 : 4;
						uint32_t 	EXTI7 : 4;
						uint32_t  Reserved :16;
					}BITS;
				}EXTICR2;//0x0C
				
				union{
					uint32_t REG;
					struct {
						uint32_t 	EXTI8  : 4;
						uint32_t 	EXTI9  : 4;
						uint32_t 	EXTI10 : 4;
						uint32_t 	EXTI711: 4;
						uint32_t  Reserved :16;
					}BITS;
				}EXTICR3;//0x10
				
				union{
					uint32_t REG;
					struct {
						uint32_t 	EXTI12  : 4;
						uint32_t 	EXTI13  : 4;
						uint32_t 	EXTI14  : 4;
						uint32_t 	EXTI715 : 4;
						uint32_t  Reserved :16;
					}BITS;
				}EXTICR4;//0x14
				
				union{
					uint32_t REG;
					struct{
						uint32_t CMP_PD		:1;
						uint32_t Reserved1 :6;
						uint32_t READY    :1;
						uint32_t Reserved2  : 24;
					}BITS;
				}CMPCR; //0x20
}SYSCFG_TypeDef;

#define SYSCFG ((volatile SYSCFG_TypeDef*)0x40013800UL)

typedef struct
{
    volatile uint32_t CR;    // Control register
    volatile uint32_t CSR;   // Control/status register
} PWR_TypeDef;



#define PWR_BASE   0x40007000UL
#define PWR        ((PWR_TypeDef *) PWR_BASE)

typedef struct
{
    volatile uint32_t ACR;       // 0x00 Access control
    volatile uint32_t KEYR;      // 0x04 Key register
    volatile uint32_t OPTKEYR;   // 0x08 Option key
    volatile uint32_t SR;        // 0x0C Status
    volatile uint32_t CR;        // 0x10 Control
    volatile uint32_t OPTCR;     // 0x14 Option control
} FLASH_TypeDef;

#define FLASH_BASE   0x40023C00UL
#define FLASH        ((FLASH_TypeDef *) FLASH_BASE)






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






//==========================Function Prototype======================
void RCC_Enable_SYSCFG(void);

#endif