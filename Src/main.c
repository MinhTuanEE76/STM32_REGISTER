#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "rcc.h"
#include "gpio.h"
#include "syscfg.h"
#include "exti.h"
#include "timer.h"
#include "uart.h"
#include "i2c.h"
#include "at24c256.h"

uint8_t i2c_data[64];
uint32_t callback_flag = 0;
uint32_t test = 1111111;
volatile uint32_t led_flag = 0 ;
char rx_buffer[1024];
char msg[] = "Hello from STM32F407VET6TR - Build by bare-metal\r\n";

void TX_Callback_Complete(void);

I2C_Handle_t hi2c1 = {
	.Instance = I2C1,
	.AddressingMode = I2C_ADDRESS_7BIT,
	.Timing = I2C_FAST_MODE
};
USART_Handle_TypeDef huart = {
		.Instance = USART1		,
		.BaudRate = 115200		,
		.Mode			= UART_MODE_TX_RX,
		.Parity  	= UART_PARITY_NONE,
		.StopBits = UART_STOPBITS_1,
		.WordLength = UART_WORDLENGTH_8B,
		.tx_it = true,
		.rx_it = true,
		.TxCallback = TX_Callback_Complete
};
void TX_Callback_Complete(void){
		callback_flag = 1;
		char msg[] = "UART Transmition Complete!!!!\r\n";
		UART_SendData(&huart,(uint8_t*)msg,strlen(msg));
}

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
		I2C_Init(&hi2c1);

	
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
		TIM2_Init(&TIM_cfg);
    while(1){
				AT24C256_Write_Buffer(&hi2c1,0,(uint8_t*)msg,strlen(msg));
				Delay_ms(10);
				AT24C256_Read_Buffer(&hi2c1,0,i2c_data,6);
				UART_SendData(&huart,(uint8_t*)msg,6);
 				Delay_ms(2000);
    }
}


/*=============================IRQ Handler=================================*/

void USART1_IRQHandler(void){
	UART_IRQ_HandlerCommon(&huart);
}

