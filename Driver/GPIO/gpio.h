#ifndef __GPIO_H
#define __GPIO_H

#include <stdint.h>
#include <stdio.h>
#include "rcc.h"


/*===============================GPIO==============================*/

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
} GPIO_TypeDef;


//gpio base address
#define GPIOA (volatile GPIO_TypeDef*)(0x40020000UL)
#define GPIOB (volatile GPIO_TypeDef*)(0x40020400UL)
#define GPIOC (volatile GPIO_TypeDef*)(0x40020800UL)
#define GPIOD (volatile GPIO_TypeDef*)(0x40020C00UL)
#define GPIOE (volatile GPIO_TypeDef*)(0x40021000UL)
#define GPIOF (volatile GPIO_TypeDef*)(0x40021400UL)
#define GPIOG (volatile GPIO_TypeDef*)(0x40021800UL)
#define GPIOH (volatile GPIO_TypeDef*)(0x40021C00UL)
#define GPIOI (volatile GPIO_TypeDef*)(0x40022000UL)
	
	
#define GPIO_PIN_0     ((uint16_t)0x0001)
#define GPIO_PIN_1     ((uint16_t)0x0002)
#define GPIO_PIN_2     ((uint16_t)0x0004)
#define GPIO_PIN_3     ((uint16_t)0x0008)
#define GPIO_PIN_4     ((uint16_t)0x0010)
#define GPIO_PIN_5     ((uint16_t)0x0020)
#define GPIO_PIN_6     ((uint16_t)0x0040)
#define GPIO_PIN_7     ((uint16_t)0x0080)
#define GPIO_PIN_8     ((uint16_t)0x0100)
#define GPIO_PIN_9     ((uint16_t)0x0200)
#define GPIO_PIN_10    ((uint16_t)0x0400)
#define GPIO_PIN_11    ((uint16_t)0x0800)
#define GPIO_PIN_12    ((uint16_t)0x1000)
#define GPIO_PIN_13    ((uint16_t)0x2000)
#define GPIO_PIN_14    ((uint16_t)0x4000)
#define GPIO_PIN_15    ((uint16_t)0x8000)

typedef enum{
				PA_PIN		=	0U,
				PB_PIN		=	1U,
				PC_PIN		=	2U,
				PD_PIN		=	3U,
				PE_PIN		=	4U,
				PF_PIN		=	5U,
				PG_PIN		=	6U,
				PH_PIN		=	7U,
				PI_PIN		=	8U
}GPIO_Port_t;

//Mode
#define GPIO_MODE_INPUT    0
#define GPIO_MODE_OUTPUT   1
#define GPIO_MODE_AF			 2
#define GPIO_MODE_ANALOG   3
//Output type
#define GPIO_PUSH_PULL     0
#define GPIO_OPEN_DRAIN    1
//pull
#define GPIO_NO_PULL       0
#define GPIO_PULL_UP       1
#define GPIO_PULL_DOWN     2
//speed
#define GPIO_SPEED_LOW      0
#define GPIO_SPEED_MEDIUM   1
#define GPIO_SPEED_FAST     2
#define GPIO_SPEED_HIGH     3
// State
#define GPIO_PIN_RESET      0
#define GPIO_PIN_SET        1
#define GPIO_PIN_UNDEFINED  2


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

#define AF_SYSTEM                AF0
#define AF_TIM1_TIM2             AF1
#define AF_TIM3_TIM4_TIM5        AF2
#define AF_TIM8_TIM9_10_11       AF3
#define AF_I2C1_2_3              AF4
#define AF_SPI1_SPI2             AF5
#define AF_SPI3_I2S3             AF6
#define AF_USART1_2_3            AF7
#define AF_UART4_5_USART6        AF8
#define AF_CAN1_CAN2             AF9
#define AF_OTG_FS_HS             AF10
#define AF_ETH                   AF11
#define AF_FSMC_SDIO_OTGFS       AF12
#define AF_DCMI                  AF13
#define AF_EVENTOUT              AF15

//================AF struct==================
typedef struct{
	volatile GPIO_TypeDef *Port;
	uint16_t Pin;
	uint8_t  AF;//AF0->AF15
} GPIO_AF_TypeDef;

/*---------------------Define AF Pin-------------------------*/
//                  USART / UART
// ================================================

// USART1
#define USART1_TX_PA9       (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_9,  AF_USART1_2_3}
#define USART1_RX_PA10      (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_10, AF_USART1_2_3}
#define USART1_TX_PB6       (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_6,  AF_USART1_2_3}
#define USART1_RX_PB7       (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_7,  AF_USART1_2_3}

// USART2
#define USART2_TX_PA2       (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_2,  AF_USART1_2_3}
#define USART2_RX_PA3       (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_3,  AF_USART1_2_3}
#define USART2_TX_PD5       (GPIO_AF_TypeDef){GPIOD, GPIO_PIN_5,  AF_USART1_2_3}
#define USART2_RX_PD6       (GPIO_AF_TypeDef){GPIOD, GPIO_PIN_6,  AF_USART1_2_3}

// USART3
#define USART3_TX_PB10      (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_10, AF_USART1_2_3}
#define USART3_RX_PB11      (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_11, AF_USART1_2_3}
#define USART3_TX_PC10      (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_10, AF_USART1_2_3}
#define USART3_RX_PC11      (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_11, AF_USART1_2_3}

// UART4
#define UART4_TX_PA0        (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_0,  AF_UART4_5_USART6}
#define UART4_RX_PA1        (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_1,  AF_UART4_5_USART6}
#define UART4_TX_PC10       (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_10, AF_UART4_5_USART6}
#define UART4_RX_PC11       (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_11, AF_UART4_5_USART6}

// UART5
#define UART5_TX_PC12       (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_12, AF_UART4_5_USART6}
#define UART5_RX_PD2        (GPIO_AF_TypeDef){GPIOD, GPIO_PIN_2,  AF_UART4_5_USART6}

// USART6
#define USART6_TX_PC6       (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_6,  AF_UART4_5_USART6}
#define USART6_RX_PC7       (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_7,  AF_UART4_5_USART6}
#define USART6_TX_PG14      (GPIO_AF_TypeDef){GPIOG, GPIO_PIN_14, AF_UART4_5_USART6}
#define USART6_RX_PG9       (GPIO_AF_TypeDef){GPIOG, GPIO_PIN_9,  AF_UART4_5_USART6}

// ================================================
//                  SPI
// ================================================

// SPI1
#define SPI1_SCK_PA5        (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_5,  AF_SPI1_SPI2}
#define SPI1_MISO_PA6       (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_6,  AF_SPI1_SPI2}
#define SPI1_MOSI_PA7       (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_7,  AF_SPI1_SPI2}
#define SPI1_NSS_PA4        (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_4,  AF_SPI1_SPI2}

// SPI2
#define SPI2_SCK_PB13       (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_13, AF_SPI1_SPI2}
#define SPI2_MISO_PB14      (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_14, AF_SPI1_SPI2}
#define SPI2_MOSI_PB15      (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_15, AF_SPI1_SPI2}
#define SPI2_NSS_PB12       (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_12, AF_SPI1_SPI2}

// SPI3
#define SPI3_SCK_PB3        (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_3,  AF_SPI3_I2S3}
#define SPI3_MISO_PB4       (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_4,  AF_SPI3_I2S3}
#define SPI3_MOSI_PB5       (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_5,  AF_SPI3_I2S3}
#define SPI3_SCK_PC10       (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_10, AF_SPI3_I2S3}
#define SPI3_MISO_PC11      (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_11, AF_SPI3_I2S3}
#define SPI3_MOSI_PC12      (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_12, AF_SPI3_I2S3}

// ================================================
//                  I2C
// ================================================

// I2C1
#define I2C1_SCL_PB6        (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_6,  AF_I2C1_2_3}
#define I2C1_SDA_PB7        (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_7,  AF_I2C1_2_3}

// I2C2
#define I2C2_SCL_PB10       (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_10, AF_I2C1_2_3}
#define I2C2_SDA_PB11       (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_11, AF_I2C1_2_3}

// I2C3
#define I2C3_SCL_PA8        (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_8,  AF_I2C1_2_3}
#define I2C3_SDA_PC9        (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_9,  AF_I2C1_2_3}

// ================================================
//                  TIM (PWM)
// ================================================

// TIM1
#define TIM1_CH1_PA8        (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_8,  AF_TIM1_TIM2}
#define TIM1_CH2_PA9        (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_9,  AF_TIM1_TIM2}
#define TIM1_CH3_PA10       (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_10, AF_TIM1_TIM2}
#define TIM1_CH4_PA11       (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_11, AF_TIM1_TIM2}

// TIM3
#define TIM3_CH1_PA6        (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_6,  AF_TIM3_TIM4_TIM5}
#define TIM3_CH2_PA7        (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_7,  AF_TIM3_TIM4_TIM5}
#define TIM3_CH3_PB0        (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_0,  AF_TIM3_TIM4_TIM5}
#define TIM3_CH4_PB1        (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_1,  AF_TIM3_TIM4_TIM5}

// TIM4
#define TIM4_CH1_PB6        (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_6,  AF_TIM3_TIM4_TIM5}
#define TIM4_CH2_PB7        (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_7,  AF_TIM3_TIM4_TIM5}
#define TIM4_CH3_PB8        (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_8,  AF_TIM3_TIM4_TIM5}
#define TIM4_CH4_PB9        (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_9,  AF_TIM3_TIM4_TIM5}

// ================================================
//                  OTG_FS
// ================================================

#define OTG_FS_DM_PA11      (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_11, AF_OTG_FS_HS}
#define OTG_FS_DP_PA12      (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_12, AF_OTG_FS_HS}
#define OTG_FS_ID_PA10      (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_10, AF_OTG_FS_HS}

// ================================================
//                  ETH (RMII)
// ================================================

#define ETH_RMII_REF_CLK_PA1 (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_1,  AF_ETH}
#define ETH_RMII_CRS_DV_PA7  (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_7,  AF_ETH}
#define ETH_RMII_RXD0_PC4    (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_4,  AF_ETH}
#define ETH_RMII_RXD1_PC5    (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_5,  AF_ETH}
#define ETH_RMII_TX_EN_PB11  (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_11, AF_ETH}
#define ETH_RMII_TXD0_PB12   (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_12, AF_ETH}
#define ETH_RMII_TXD1_PB13   (GPIO_AF_TypeDef){GPIOB, GPIO_PIN_13, AF_ETH}
#define ETH_MDIO_PA2         (GPIO_AF_TypeDef){GPIOA, GPIO_PIN_2,  AF_ETH}
#define ETH_MDC_PC1          (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_1,  AF_ETH}

// ================================================
//                  SDIO
// ================================================

#define SDIO_D0_PC8         (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_8,  AF_FSMC_SDIO_OTGFS}
#define SDIO_D1_PC9         (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_9,  AF_FSMC_SDIO_OTGFS}
#define SDIO_D2_PC10        (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_10, AF_FSMC_SDIO_OTGFS}
#define SDIO_D3_PC11        (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_11, AF_FSMC_SDIO_OTGFS}
#define SDIO_CK_PC12        (GPIO_AF_TypeDef){GPIOC, GPIO_PIN_12, AF_FSMC_SDIO_OTGFS}
#define SDIO_CMD_PD2        (GPIO_AF_TypeDef){GPIOD, GPIO_PIN_2,  AF_FSMC_SDIO_OTGFS}


/*----------------Function Prototype---------------------------*/

void GPIO_Config(volatile GPIO_TypeDef *GPIOx,uint16_t GPIO_PIN,uint8_t Mode,
													uint8_t Type,uint8_t Pull,uint8_t Speed);

void GPIO_WritePin(volatile GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t State);

uint8_t GPIO_ReadPin(volatile GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

void GPIO_TogglePin(volatile GPIO_TypeDef* GPIOx, uint8_t GPIO_Pin);

//Initialize AF
void GPIO_AF_Init(const GPIO_AF_TypeDef *Af, uint8_t Type, uint8_t Pull, uint8_t Speed);

#endif

