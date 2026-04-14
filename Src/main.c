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

char data[] = "Hello from STM32F407\r\n";
char mem_add[2] = {0x00,0x00};
char tx_buffer[64];

USART_Handle_TypeDef huart = {
		.Instance = USART1		,
		.BaudRate = 115200		,
		.Mode			= UART_MODE_TX_RX,
		.Parity  	= UART_PARITY_NONE,
		.StopBits = UART_STOPBITS_1,
		.WordLength = UART_WORDLENGTH_8B
};


char rx[1024]; 
volatile I2C_Handle_TypeDef hi2c = {
	.Instance = I2C1,
	.AddressingMode = I2C_ADDRESS_7BIT,
	.Timing = I2C_STANDARD_MODE
};

void Time2_Expire(void){
	GPIO_TogglePin(GPIOA,GPIO_PIN_6);
}

TIM_Config_t tim2 = {
	.PSC = 41999,
	.ARR = 999,
	.it_flag = true,
	.Callback = Time2_Expire
};

	
int main(){
		RCC_Config_168Mhz();
		RCC_Enable_PortA();
		TIM2_Init(&tim2);
    I2C_Init(&hi2c);
		GPIO_AF_Init(&USART1_TX_PA9,GPIO_PUSH_PULL,GPIO_NO_PULL,GPIO_SPEED_MEDIUM);
		GPIO_AF_Init(&USART1_RX_PA10,GPIO_PUSH_PULL,GPIO_NO_PULL,GPIO_SPEED_MEDIUM);
		UART_Init(&huart);
		tx_buffer[0] = 0x05;
		tx_buffer[1] = 0x00;
		memcpy(tx_buffer+2,data,strlen(data)+1);
		GPIO_Config(GPIOA,GPIO_PIN_6,GPIO_MODE_OUTPUT,GPIO_PUSH_PULL,GPIO_PULL_UP,GPIO_SPEED_LOW);
    while(1){
			I2C_START(&hi2c);
			volatile uint8_t status = I2C_Master_Transmit(&hi2c,0x50,(uint8_t*)tx_buffer,2+ strlen(data));
			I2C_STOP(&hi2c);
			Delay_ms(10);
 			
//			I2C_START(&hi2c); 
//			I2C_Master_Transmit(&hi2c,0x50,(uint8_t*)mem_add,2);
//			Delay_ms(10);
//			I2C_START(&hi2c);
//			I2C_Master_Receive(&hi2c,0x50,(uint8_t*)rx,64);
//			I2C_STOP(&hi2c);
//			UART_SendData(&huart,(uint8_t*)rx,64);
			
			//
			mem_add[0] = 0x05;
			mem_add[1] = 0x00;
			I2C_START(&hi2c); 
			I2C_Master_Transmit(&hi2c,0x50,(uint8_t*)mem_add,2);
			Delay_ms(1);
			I2C_START(&hi2c);
			I2C_Master_Receive(&hi2c,0x50,(uint8_t*)rx,strlen(data));
			I2C_STOP(&hi2c);
			UART_SendData(&huart,(uint8_t*)rx,strlen(rx));
		
			GPIO_TogglePin(GPIOA,GPIO_PIN_6);
			Delay_ms(2000);
    }
}


/*=============================IRQ Handler=================================*/

//void USART1_IRQHandler(void){
//	UART_IRQ_HandlerCommon(&huart);
//}

