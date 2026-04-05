#include "uart.h"
#include <stdio.h>
/*------------------------static function------------------------------------------*/
static uint32_t UART_CalculateBRR(uint32_t Clock, uint32_t Baudrate){
		if(Baudrate == 0) return 0;
		
		uint32_t usartdiv = (Clock + Baudrate/2U)/Baudrate;//clk/baudrate + 0.5
		uint32_t mantissa = usartdiv/16;
		uint32_t fraction = usartdiv%16;
		return (mantissa << 4U ) | fraction;
}

//RING_BUFFER
static void RingBuffer_Init(Ring_buffer_t *buffer){
		buffer->head = 0;
		buffer->tail = 0;
		buffer->count = 0;
}

static void RingBuffer_Write(Ring_buffer_t *rb, uint8_t data){
		if(rb->count < RING_BUFFER_SIZE){
				rb->buffer[rb->head] = data;
				rb->head = (rb->head + 1) % RING_BUFFER_SIZE;
				rb->count++;
		}
}

static uint8_t RingBuffer_Read(Ring_buffer_t *rb){
		if(rb->count == 0) return 0;
		uint8_t data = rb->buffer[rb->tail];
		rb->tail = (rb->tail + 1) % RING_BUFFER_SIZE;
		rb->count--;
		return data;
}
/*--------------------------------------------------------------------------------------------*/
void UART_Init(USART_Handle_TypeDef	*huart){
		if(huart->Instance == NULL || huart == NULL) return;
		
		volatile USART_TypeDef *USARTx = huart->Instance;
		//Enable clock
		if(USARTx == USART1){
			//usart1
			RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		}
		else if(USARTx == USART2){
			//usart2
			RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		}
		else if(USARTx == USART3){
			//usart3
			RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
		}
		else if(USARTx == UART4){
			//uart4
			RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
		}
		else if(USARTx == UART5){
			//uart5
			RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
		}
		else{
			//not uart
			return;
		}
		
		//disable uart to configure
		USARTx->CR1 &= ~USART_CR1_UE;
		//stop bit
		USARTx->CR2  &= ~(USART_CR2_STOP_MASK);
		if(huart->StopBits == UART_STOPBITS_2){
			USARTx->CR2 |= USART_CR2_STOP_1;//0b10 = 2 stopbits
		}
		else{
			USARTx->CR2 &= ~(USART_CR2_STOP_1);//0b00 = 1 stopbit
		}
		
		uint32_t cr1_temp = 0;
		//wordlength
		if(huart->WordLength == UART_WORDLENGTH_9B){
			cr1_temp |= USART_CR1_M;
		}//else 8 bit
		
		//parity
		if(!(huart->Parity == UART_PARITY_NONE)){
			if(huart->Parity == UART_PARITY_ODD){
				cr1_temp |= USART_CR1_PS;//ps = 1
			}
			//else ps = 0 (reset)
		}
		//Mode
		if(huart->Mode == UART_MODE_TX_RX){
			//RXTX
			cr1_temp |= (USART_CR1_RE | USART_CR1_TE);
		}
		else if(huart->Mode == UART_MODE_RX){
			//RX    
			cr1_temp |= USART_CR1_RE;
		}
		else{
			//TX
			cr1_temp |= USART_CR1_TE;
		}
		
		USARTx->CR1 = cr1_temp;
		
		//BRR
		if(USARTx == USART1){
			USARTx->BRR = UART_CalculateBRR(SYSCLK/2, huart->BaudRate);
		}
		else{
			USARTx->BRR = UART_CalculateBRR(SYSCLK/4, huart->BaudRate);
		}
		//Interrupt
		if(huart->rx_it){//Receive Interrupt
				USARTx->CR1 |= USART_CR1_RXNEIE;//enable rx_it
				NVIC_EnableIRQ(USART1_IRQn);
				//init ring_buffer
				RingBuffer_Init(&(huart->RxBuffer));
		} 
		//rx_tx
		if(huart->tx_it){
				//no need set TXEIE immediately
				NVIC_EnableIRQ(USART1_IRQn);
		}
		//enable
		USARTx->CR1 |= USART_CR1_UE;
}


/*------------------------------------Transmition Function---------------------------------------*/

//Send 1 byte
void UART_SendByte(USART_Handle_TypeDef *huart, uint8_t ch){
		if(huart ==	 NULL || huart->Instance == NULL) return;
	
		while(!(huart->Instance->SR & USART_SR_TXE));//waiting TXE = 1
		huart->Instance->DR = ch;
		while(!(huart->Instance->SR & USART_SR_TC));//wait transnmit complete
}
//Send data
void UART_SendData(USART_Handle_TypeDef *huart, uint8_t *data, uint16_t len){
		if (huart == NULL || huart->Instance == NULL || data == NULL || len <= 0) return;
		
		for( uint16_t i = 0 ; i < len ; i++){
			UART_SendByte(huart,data[i]);
		}
		while(!(huart->Instance->SR & USART_SR_TC));//wait transnmit complete
}
//TRANSMIT INTERRUPT
void UART_Transmit_IT(USART_Handle_TypeDef *huart, uint8_t *data,uint16_t len){
		huart->pTxBuffer = data;
		huart->TxCount 	 = len;
		//start trigger
		huart->Instance->DR = *(huart->pTxBuffer++);
		huart->TxCount--;
		
		//Enable TXEIE
		huart->Instance->CR1 |= USART_CR1_TXEIE;
}
/*------------------------------------Receive Function---------------------------------------*/

uint8_t UART_ReceiveByte(USART_Handle_TypeDef *huart){
		//check RXNE in SR
		while(!(huart->Instance->SR & USART_SR_RXNE));//wait RXNE = 1;
		return (uint8_t)huart->Instance->DR;
}

void UART_ReceiveData(USART_Handle_TypeDef *huart , uint8_t *buffer){
		uint16_t index = 0;
		while(1){
			//check RXNE
			while(!(huart->Instance->SR & USART_SR_RXNE));//wait RXNE = 1
			buffer[index] = (uint8_t)huart->Instance->DR;
			if(buffer[index] == '\n'){
				buffer[++index] = '\0';
				break;
			}
			index ++;
		}
}


//==========================================
void UART_IRQ_HandlerCommon(USART_Handle_TypeDef *huart){
		//RX
		if(huart->Instance->SR & USART_SR_RXNE && huart->Instance->CR1 & USART_CR1_RXNEIE){
				uint8_t data = huart->Instance->DR;//read DR->automatically clear RXNE	
				//push data
				RingBuffer_Write(&(huart->RxBuffer),data);
		}
		//TX
		if(huart->Instance->SR & USART_SR_TXE && huart->Instance->CR1 & USART_CR1_TXEIE){
				if(huart->TxCount > 0){
					huart->Instance->DR = *(huart->pTxBuffer++);
					huart->TxCount--;
				}
				else{
						//ENABLE
					huart->Instance->CR1 &= ~USART_CR1_TXEIE;
					huart->Instance->CR1 |= USART_CR1_TCIE;
				}
		}
		//Transmit Complete
		if(huart->Instance->SR & USART_SR_TC && huart->Instance->CR1 & USART_CR1_TCIE){
				huart->Instance->CR1 &= ~USART_CR1_TCIE;//clear TCIE
				if(huart->TxCallback){
					huart->TxCallback();
				}
		}
}
//Note: call void USART1_IRQHandler if use interrupt and inside call UART_IRQHandlerCommon 
