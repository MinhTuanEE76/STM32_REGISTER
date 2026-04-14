#include <rcc.h>

//void RCC_Config_168Mhz(void){

//    //Enable HSE
//    RCC->CR.REG |= (1 << 16); // HSEON
//    while(!(RCC->CR.REG & (1 << 17))); // HSERDY
//	
//		RCC->APB1ENR |= (1 << 28);
//	
//    //Configure Flash 
//    FLASH_ACR =
//        (5 << 0) |   // LATENCY = 5WS
//        (1 << 8) |   // PRFTEN (prefetch)
//        (1 << 9) |   // ICEN
//        (1 << 10);   // DCEN

//    //Set prescaler
//		RCC->CFGR.REG = 0;
//    RCC->CFGR.REG |= (0 << 4);
//		RCC->CFGR.REG |= (5 << 10);
//		RCC->CFGR.REG |= (4 << 13);

//    //Configure PLL
//    RCC->PLLCFGR.REG = 0;
//		RCC->PLLCFGR.REG =
//    (8 << 0)   |   // PLLM
//    (336 << 6) |   // PLLN
//    (0 << 16)  |   // PLLP = /2
//    (1 << 22);     // HSE

//    //Enable PLL
//    RCC->CR.REG |= (1 << 24);
//    while(!(RCC->CR.REG & (1 << 25))); // PLLRDY

//    //Select PLL as system clock
//    RCC->CFGR.REG |= (2 << 0);

//    //Wait switch done N UNJ J
//    while(((RCC->CFGR.REG >> 2) & 0x3) != 2);
//}

void RCC_Config_168Mhz(void)
{
    //Enable HSE 
    RCC->CR.REG |= (1 << 16);                 // HSEON
    while (!(RCC->CR.REG & (1 << 17)));       // Wait HSERDY

    //Enable PWR clock + Voltage scaling
    RCC->APB1ENR |= (1 << 28);            // PWREN
    PWR->CR |= (1 << 14);                 // VOS = Scale 1 (for 168MHz)

    //Configure Flash
    FLASH->ACR =
        (5 << 0)  |   // LATENCY = 5WS
        (1 << 8)  |   // PRFTEN
        (1 << 9)  |   // ICEN
        (1 << 10);    // DCEN

    //Configure prescalers 
    // AHB = /1
    RCC->CFGR.REG &= ~(0xF << 4);
    RCC->CFGR.REG |=  (0 << 4);

    // APB1 = /4
    RCC->CFGR.REG &= ~(0x7 << 10);
    RCC->CFGR.REG |=  (5 << 10);

    // APB2 = /2
    RCC->CFGR.REG &= ~(0x7 << 13);
    RCC->CFGR.REG |=  (4 << 13);

    //Configure PLL 
    RCC->PLLCFGR.REG =
        (8 << 0)   |   // PLLM = 8
        (336 << 6) |   // PLLN = 336
        (0 << 16)  |   // PLLP = 2
        (1 << 22);     // PLLSRC = HSE

    //Enable PLL 
    RCC->CR.REG |= (1 << 24);                 // PLLON
    while (!(RCC->CR.REG & (1 << 25)));       // Wait PLLRDY

    //Select PLL as SYSCLK 
    RCC->CFGR.REG &= ~(0x3 << 0); 
    RCC->CFGR.REG |=  (2 << 0);               // SW = PLL

    while (((RCC->CFGR.REG >> 2) & 0x3) != 2); // Wait SWS = PLL
}


//Enable RCC port A->I
void RCC_Enable_PortA(void){
	RCC->AHB1ENR.BITS.GPIOAEN = 1;
}
void RCC_Enable_PortB(void){
	RCC->AHB1ENR.BITS.GPIOBEN = 1;
}
void RCC_Enable_PortC(void){
	RCC->AHB1ENR.BITS.GPIOCEN = 1;
}
void RCC_Enable_PortD(void){
	RCC->AHB1ENR.BITS.GPIODEN = 1;
}
void RCC_Enable_PortE(void){
	RCC->AHB1ENR.BITS.GPIOEEN = 1;
}
void RCC_Enable_PortF(void){
	RCC->AHB1ENR.BITS.GPIOFEN = 1;
}
void RCC_Enable_PortG(void){
	RCC->AHB1ENR.BITS.GPIOGEN = 1;
}
void RCC_Enable_PortH(void){
	RCC->AHB1ENR.BITS.GPIOHEN = 1;
}
void RCC_Enable_PortI(void){
	RCC->AHB1ENR.BITS.GPIOIEN = 1;
}
//end enable port

/*==================Enable TIMx================== */

void RCC_Enable_TIM1(void){
	RCC->APB2ENR |= (1 << 0);
}
void RCC_Enable_TIM2(void){
	RCC->APB1ENR |= (1 << 0);
}
void RCC_Enable_TIM3(void){
	RCC->APB1ENR |= (1 << 1);
}
void RCC_Enable_TIM4(void){
	RCC->APB1ENR |= (1 << 2);
}
void RCC_Enable_TIM5(void){
	RCC->APB1ENR |= (1 << 3);
}
void RCC_Enable_TIM6(void){
	RCC->APB1ENR |= (1 << 4);
}
void RCC_Enable_TIM7(void){
	RCC->APB1ENR |= (1 << 5);
}

/*==================Enable SYSCFG================== */
void Enable_Syscfg(void){
	RCC->APB2ENR |= (1 << 14);
}

//SYSCFG
void RCC_Enable_SYSCFG(void){
	RCC->APB2ENR |= (1 << 14);
}

