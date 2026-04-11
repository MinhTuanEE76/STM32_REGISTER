#ifndef __RCC_H
#define __RCC_H

#include <stdint.h>
#include <stdio.h>
#include "syscfg.h"

#define SYSCLK			168000000UL

// =============================================================================
// RCC - AHB1ENR  (AHB1 Peripheral Clock Enable Register)
// =============================================================================
#define RCC_AHB1ENR_GPIOAEN         (1U << 0)
#define RCC_AHB1ENR_GPIOBEN         (1U << 1)
#define RCC_AHB1ENR_GPIOCEN         (1U << 2)
#define RCC_AHB1ENR_GPIODEN         (1U << 3)
#define RCC_AHB1ENR_GPIOEEN         (1U << 4)
#define RCC_AHB1ENR_GPIOFEN         (1U << 5)
#define RCC_AHB1ENR_GPIOGEN         (1U << 6)
#define RCC_AHB1ENR_GPIOHEN         (1U << 7)
#define RCC_AHB1ENR_GPIOIEN         (1U << 8)

#define RCC_AHB1ENR_CRCEN           (1U << 12)
#define RCC_AHB1ENR_DMA1EN          (1U << 21)
#define RCC_AHB1ENR_DMA2EN          (1U << 22)

// =============================================================================
// RCC - AHB2ENR  (AHB2 Peripheral Clock Enable Register)
// =============================================================================
#define RCC_AHB2ENR_OTGFSEN         (1U << 7)     // USB OTG FS

// =============================================================================
// RCC - APB1ENR  (APB1 Peripheral Clock Enable Register)
// =============================================================================
#define RCC_APB1ENR_TIM2EN          (1U << 0)
#define RCC_APB1ENR_TIM3EN          (1U << 1)
#define RCC_APB1ENR_TIM4EN          (1U << 2)
#define RCC_APB1ENR_TIM5EN          (1U << 3)
#define RCC_APB1ENR_TIM6EN          (1U << 4)
#define RCC_APB1ENR_TIM7EN          (1U << 5)
#define RCC_APB1ENR_TIM12EN         (1U << 6)
#define RCC_APB1ENR_TIM13EN         (1U << 7)
#define RCC_APB1ENR_TIM14EN         (1U << 8)

#define RCC_APB1ENR_WWDGEN          (1U << 11)
#define RCC_APB1ENR_SPI2EN          (1U << 14)
#define RCC_APB1ENR_SPI3EN          (1U << 15)
#define RCC_APB1ENR_USART2EN        (1U << 17)
#define RCC_APB1ENR_USART3EN        (1U << 18)
#define RCC_APB1ENR_UART4EN         (1U << 19)
#define RCC_APB1ENR_UART5EN         (1U << 20)

#define RCC_APB1ENR_I2C1EN          (1U << 21)
#define RCC_APB1ENR_I2C2EN          (1U << 22)
#define RCC_APB1ENR_I2C3EN          (1U << 23)

#define RCC_APB1ENR_CAN1EN          (1U << 25)
#define RCC_APB1ENR_CAN2EN          (1U << 26)
#define RCC_APB1ENR_PWREN           (1U << 28)

// =============================================================================
// RCC - APB2ENR  (APB2 Peripheral Clock Enable Register)
// =============================================================================
#define RCC_APB2ENR_TIM1EN          (1U << 0)
#define RCC_APB2ENR_TIM8EN          (1U << 1)
#define RCC_APB2ENR_USART1EN        (1U << 4)
#define RCC_APB2ENR_USART6EN        (1U << 5)

#define RCC_APB2ENR_ADC1EN          (1U << 8)
#define RCC_APB2ENR_ADC2EN          (1U << 9)
#define RCC_APB2ENR_ADC3EN          (1U << 10)

#define RCC_APB2ENR_SDIOEN          (1U << 11)
#define RCC_APB2ENR_SPI1EN          (1U << 12)
#define RCC_APB2ENR_SPI4EN          (1U << 13)
#define RCC_APB2ENR_SYSCFGEN        (1U << 14)

#define RCC_APB2ENR_TIM9EN          (1U << 16)
#define RCC_APB2ENR_TIM10EN         (1U << 17)
#define RCC_APB2ENR_TIM11EN         (1U << 18)



typedef struct{

    //================ 0x00: CR =================
    union{
        uint32_t REG;
        struct{
            uint32_t HSION     :1;
            uint32_t HSIRDY    :1;
            uint32_t           :1;
            uint32_t HSITRIM   :5;
            uint32_t HSICAL    :8;
            uint32_t HSEON     :1;
            uint32_t HSERDY    :1;
            uint32_t HSEBYP    :1;
            uint32_t CSSON     :1;
            uint32_t           :4;
            uint32_t PLLON     :1;
            uint32_t PLLRDY    :1;
            uint32_t PLLI2SON  :1;
            uint32_t PLLI2SRDY :1;
            uint32_t           :4;
        }BITS;
    } CR;

    //================ 0x04: PLLCFGR =================
    union{
        uint32_t REG;
        struct{
            uint32_t PLLM   :6;
            uint32_t PLLN   :9;
            uint32_t        :1;
            uint32_t PLLP   :2;
            uint32_t        :4;
            uint32_t PLLSRC :1;
            uint32_t        :1;
            uint32_t PLLQ   :4;
            uint32_t        :4;
        }BITS;
    } PLLCFGR;

    //================ 0x08: CFGR =================
    union{
        uint32_t REG;
        struct{
            uint32_t SW      :2;
            uint32_t SWS     :2;
            uint32_t HPRE    :4;
					  uint32_t RESERE  :2;
            uint32_t PPRE1   :3;
            uint32_t PPRE2   :3;
            uint32_t RTCPRE  :5;
            uint32_t MCO1    :2;
            uint32_t I2SSRC  :1;
            uint32_t MCO1PRE :3;
            uint32_t MCO2PRE :3;
            uint32_t MCO2    :2;
        }BITS;
    } CFGR;

    //================ 0x0C =================
    uint32_t CIR;

    //================ RESET =================
    uint32_t AHB1RSTR;   //0x10
    uint32_t AHB2RSTR;   //0x14
    uint32_t AHB3RSTR;   //0x18
    uint32_t RESERVED0;  //0x1C

    uint32_t APB1RSTR;   //0x20
    uint32_t APB2RSTR;   //0x24

    uint32_t RESERVED1[2];

    //================ ENABLE =================
    union{
        uint32_t REG;
        struct{
            uint32_t GPIOAEN :1;
            uint32_t GPIOBEN :1;
            uint32_t GPIOCEN :1;
            uint32_t GPIODEN :1;
            uint32_t GPIOEEN :1;
            uint32_t GPIOFEN :1;
            uint32_t GPIOGEN :1;
            uint32_t GPIOHEN :1;
            uint32_t GPIOIEN :1;
            uint32_t         :3;
            uint32_t CRCEN   :1;
            uint32_t         :19;
        }BITS;
    } AHB1ENR;           //0x30

    uint32_t AHB2ENR;   //0x34
    uint32_t AHB3ENR;   //0x38
    uint32_t RESERVED2; //0x3C

    uint32_t APB1ENR;   //0x40
    uint32_t APB2ENR;   //0x44

    uint32_t RESERVED3[2];

    //================ LOW POWER =================
    union{
        uint32_t REG;
        struct{
            uint32_t GPIOALPEN :1;
            uint32_t GPIOBLPEN :1;
            uint32_t GPIOCLPEN :1;
            uint32_t GPIODLPEN :1;
            uint32_t GPIOELPEN :1;
            uint32_t GPIOFLPEN :1;
            uint32_t GPIOGLPEN :1;
            uint32_t GPIOHLPEN :1;
            uint32_t GPIOILPEN :1;
            uint32_t           :3;
            uint32_t CRCLPEN   :1;
            uint32_t           :19;
        }BITS;
    } AHB1LPENR;        //0x50

    uint32_t AHB2LPENR; //0x54
    uint32_t AHB3LPENR; //0x58
    uint32_t RESERVED4; //0x5C

    uint32_t APB1LPENR; //0x60
    uint32_t APB2LPENR; //0x64

    uint32_t RESERVED5[2];

    //================ BDCR =================
    union{
        uint32_t REG;
        struct{
            uint32_t LSEON  :1;
            uint32_t LSERDY :1;
            uint32_t LSEBYP :1;
            uint32_t        :5;
            uint32_t RTCSEL :2;
            uint32_t        :5;
            uint32_t RTCEN  :1;
            uint32_t BDRST  :1;
            uint32_t        :15;
        }BITS;
    } BDCR;             //0x70

    //================ CSR =================
    union{
        uint32_t REG;
        struct{
            uint32_t LSION    :1;
            uint32_t LSIRDY   :1;
            uint32_t          :22;
            uint32_t RMVF     :1;
            uint32_t BORRSTF  :1;
            uint32_t PINRSTF  :1;
            uint32_t PORRSTF  :1;
            uint32_t SFTRSTF  :1;
            uint32_t IWDGRSTF :1;
            uint32_t WWDGRSTF :1;
            uint32_t LPWRRSTF :1;
        }BITS;
    } CSR;              //0x74

    uint32_t RESERVED6[2];

    //================ SSCGR =================
    union{
        uint32_t REG;
        struct{
            uint32_t MODPER    :13;
            uint32_t INCSTEP   :15;
            uint32_t           :2;
            uint32_t SPREADSEL :1;
            uint32_t SSCGEN    :1;
        }BITS;
    } SSCGR;            //0x80

    //================ PLLI2SCFGR =================
    union{
        uint32_t REG;
        struct{
            uint32_t PLLI2SN :9;
            uint32_t         :15;
            uint32_t PLLI2SR :3;
            uint32_t         :5;
        }BITS;
    } PLLI2SCFGR;       //0x84

    uint32_t RESERVED7;

    //================ DCKCFGR =================
    union{
        uint32_t REG;
        struct{
            uint32_t TIMPRE :1;
            uint32_t        :31;
        }BITS;
    } DCKCFGR;          //0x8C

} RCC_TypeDef;
//define rcc register
#define RCC_ADD_BASE 0x40023800UL
#define RCC ((volatile RCC_TypeDef*)RCC_ADD_BASE)
	
//define flash interface register 
#define FLASH_ADD_BASE 0x40023C00UL
#define FLASH_ACR *((volatile uint32_t*)FLASH_ADD_BASE)
	
			

/*----------------funtion prototype---------------------*/
void RCC_Config_168Mhz(void);
//enable GPIO
void RCC_Enable_PortA(void);
void RCC_Enable_PortB(void);
void RCC_Enable_PortC(void);
void RCC_Enable_PortD(void);
void RCC_Enable_PortE(void);
void RCC_Enable_PortF(void);
void RCC_Enable_PortG(void);
void RCC_Enable_PortH(void);
void RCC_Enable_PortI(void);

//enable TIMx
void RCC_Enable_TIM1(void);
void RCC_Enable_TIM2(void);
void RCC_Enable_TIM3(void);
void RCC_Enable_TIM4(void);
void RCC_Enable_TIM5(void);
void RCC_Enable_TIM6(void);
void RCC_Enable_TIM7(void);
void RCC_Enable_TIM8(void);
void RCC_Enable_TIM9(void);
void RCC_Enable_TIM10(void);
void RCC_Enable_TIM11(void);
void RCC_Enable_TIM12(void);
void RCC_Enable_TIM13(void);
void RCC_Enable_TIM14(void);

//Enable syscfg
void Enable_Syscfg(void);

#endif
