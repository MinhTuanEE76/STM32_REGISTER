#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "rcc.h"
#include "gpio.h"
#include "syscfg.h"
#include "exti.h"
#include "timer.h"
#include "uart.h"

uint32_t test = 1111111;
volatile uint32_t led_flag = 0 ;
char rx_buffer[1024];
char msg[] = "Hello from STM32F407VET6TR - Build by bare-metal\r\n";
USART_Handle_TypeDef huart = {
		.Instance = USART1		,
		.BaudRate = 115200		,
		.Mode			= UART_MODE_TX_RX,
		.Parity  	= UART_PARITY_NONE,
		.StopBits = UART_STOPBITS_1,
		.WordLength = UART_WORDLENGTH_8B,
};



void SetFlag(void){
	led_flag = 1;
}

void TimerFlag(void){
	GPIO_TogglePin(GPIOA,GPIO_PIN_7);
}

EXTI_Config_t cfg = {
		.Port_Pin = PE_PIN,
		.GPIO_Pin = GPIO_PIN_3,
		.Trigger  = FALLING_TRIGGER,
		.callback = SetFlag
};

TIM_Config_t TIM_cfg = {
		.PSC = 47999	,
		.ARR = 999		,
		.Callback = TimerFlag
};


int main(){
		RCC_Config_168Mhz();	
    // 1. Enable clock GPIOA
    RCC_Enable_PortA();
		RCC_Enable_PortE();
		GPIO_AF_Init(&USART1_TX_PA9,GPIO_PUSH_PULL,GPIO_NO_PULL,GPIO_SPEED_MEDIUM);
		GPIO_AF_Init(&USART1_RX_PA10,GPIO_PUSH_PULL,GPIO_NO_PULL,GPIO_SPEED_MEDIUM);
		UART_Init(&huart);
	
		volatile uint32_t rcc_ahb1 = RCC->AHB1ENR.REG;
	
		GPIO_Config(GPIOA,GPIO_PIN_6,
								GPIO_MODE_OUTPUT,
								GPIO_PUSH_PULL,
								GPIO_PULL_UP,
								GPIO_SPEED_LOW);
	
		GPIO_Config(GPIOA,GPIO_PIN_7,
								GPIO_MODE_OUTPUT,
								GPIO_PUSH_PULL,
								GPIO_PULL_UP,
								GPIO_SPEED_LOW);
	
		GPIO_Config(GPIOE,GPIO_PIN_3,
								GPIO_MODE_INPUT,
								GPIO_PUSH_PULL,
								GPIO_PULL_UP,
								GPIO_SPEED_LOW);
		GPIO_TogglePin(GPIOA,GPIO_PIN_6);
		EXTI_Init(&cfg);
//		TIM2_Init(&TIM_cfg);
    while(1){
				if(led_flag) {
					led_flag = 0;
					char msg[] = "Button is pressed\r\n";
					UART_SendData(&huart,(uint8_t*)msg,strlen(msg));
				}
				UART_ReceiveData(&huart,(uint8_t*)rx_buffer);
				UART_SendData(&huart,(uint8_t*)rx_buffer,strlen(rx_buffer));
				UART_SendData(&huart,(uint8_t*)msg,strlen(msg));
				GPIO_TogglePin(GPIOA,GPIO_PIN_7);
				Delay_ms(1000);
    }
}
