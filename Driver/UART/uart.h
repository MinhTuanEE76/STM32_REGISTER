#ifndef __UART_H
#define __UART_H

#include <stdint.h>
#include <stdbool.h>
#include "syscfg.h"
#include "gpio.h"
#include "nvic.h"

// ================================================================
// Bit Mask
// ================================================================

// ------------------- USART_CR1 -------------------
#define USART_CR1_UE                (1U << 13)    // USART Enable
#define USART_CR1_M                 (1U << 12)    // Word length: 0=8bit, 1=9bit
#define USART_CR1_WAKE              (1U << 11)
#define USART_CR1_PCE               (1U << 10)    // Parity Control Enable
#define USART_CR1_PS                (1U << 9)     // Parity Selection (0=Even, 1=Odd)
#define USART_CR1_PEIE              (1U << 8)
#define USART_CR1_TXEIE             (1U << 7)
#define USART_CR1_TCIE              (1U << 6)
#define USART_CR1_RXNEIE            (1U << 5)
#define USART_CR1_IDLEIE            (1U << 4)
#define USART_CR1_TE                (1U << 3)     // Transmitter Enable
#define USART_CR1_RE                (1U << 2)     // Receiver Enable
#define USART_CR1_RWU               (1U << 1)
#define USART_CR1_SBK               (1U << 0)

// ------------------- USART_CR2 -------------------
#define USART_CR2_LINEN             (1U << 14)
#define USART_CR2_STOP_1            (1U << 13)    // Stop bits [13:12]
#define USART_CR2_STOP_0            (1U << 12)
#define USART_CR2_STOP_MASK         (3U << 12)
#define USART_CR2_CLKEN             (1U << 11)
#define USART_CR2_CPOL              (1U << 10)
#define USART_CR2_CPHA              (1U << 9)
#define USART_CR2_LBCL              (1U << 8)
#define USART_CR2_LBDIE             (1U << 4)

// ------------------- USART_CR3 -------------------
#define USART_CR3_CTSIE             (1U << 11)
#define USART_CR3_CTSE              (1U << 10)    // CTS Enable
#define USART_CR3_RTSE              (1U << 9)     // RTS Enable
#define USART_CR3_DMAT              (1U << 8)     // DMA Enable Transmitter
#define USART_CR3_DMAR              (1U << 7)     // DMA Enable Receiver
#define USART_CR3_SCEN              (1U << 6)
#define USART_CR3_NACK              (1U << 5)
#define USART_CR3_HDSEL             (1U << 4)     // Half-Duplex Selection
#define USART_CR3_IREN              (1U << 3)
#define USART_CR3_IRLP              (1U << 2)
#define USART_CR3_EIE               (1U << 1)     // Error Interrupt Enable

// ------------------- USART_SR -------------------
#define USART_SR_CTS                (1U << 9)
#define USART_SR_LBD                (1U << 8)
#define USART_SR_TXE                (1U << 7)     // Transmit Data Register Empty
#define USART_SR_TC                 (1U << 6)     // Transmission Complete
#define USART_SR_RXNE               (1U << 5)     // Read Data Register Not Empty
#define USART_SR_IDLE               (1U << 4)
#define USART_SR_ORE                (1U << 3)     // Overrun Error
#define USART_SR_NE                 (1U << 2)     // Noise Error (NF)
#define USART_SR_FE                 (1U << 1)     // Framing Error
#define USART_SR_PE                 (1U << 0)     // Parity Error

#define BASE_ADDRESS_USART1				0x40011000UL
#define BASE_ADDRESS_USART6				0x40011400UL
#define BASE_ADDRESS_USART2				0x40004400UL
#define BASE_ADDRESS_USART3				0x40004800UL

#define BASE_ADDRESS_UART4				0x40004C00UL
#define BASE_ADDRESS_UART5				0x40005000UL

typedef struct{
		volatile uint32_t SR;//0x00
		volatile uint32_t DR;//0x04
		volatile uint32_t BRR;//0x08
		volatile uint32_t CR1;//0x0C
		volatile uint32_t CR2;//0x10
		volatile uint32_t CR3;//0x14
		volatile uint32_t GTPR;//0x18
}USART_TypeDef;

//mapping
#define USART1			((volatile USART_TypeDef*)(BASE_ADDRESS_USART1))
#define USART2			((volatile USART_TypeDef*)(BASE_ADDRESS_USART2))
#define USART3			((volatile USART_TypeDef*)(BASE_ADDRESS_USART3))
#define UART4				((volatile USART_TypeDef*)(BASE_ADDRESS_UART4))
#define UART5				((volatile USART_TypeDef*)(BASE_ADDRESS_UART5))

/*=============================RING_BUFFER======================*/
#define RING_BUFFER_SIZE		256U

typedef struct{
		uint8_t buffer[RING_BUFFER_SIZE] ; // data
		uint16_t head;										//index push data
		uint16_t tail;										//index pop data
		uint16_t count;										//amount of byte in buffer
}Ring_buffer_t;

//==============Handle USART==========================

typedef struct{
		volatile USART_TypeDef *Instance;
		//flag
		bool rx_it;
		bool tx_it;
		
		uint32_t BaudRate;
		uint8_t WordLength;
		uint8_t StopBits;
		uint8_t Parity;
		uint8_t Mode;
		//buffer
		uint8_t *pTxBuffer;
		uint16_t TxCount;
		Ring_buffer_t RxBuffer;
	
		//callback
		void (*TxCallback)(void);
		void (*RxCallback)(void);
}USART_Handle_TypeDef;

// ================================================================
// Define mode and configuration
// ================================================================
#define UART_MODE_TX                ((uint8_t)0x01U)
#define UART_MODE_RX                ((uint8_t)0x02U)
#define UART_MODE_TX_RX             ((uint8_t)0x03U)

#define UART_WORDLENGTH_8B          ((uint8_t)0x00U)
#define UART_WORDLENGTH_9B          ((uint8_t)0x01U)

#define UART_STOPBITS_1             ((uint8_t)0x00U)
#define UART_STOPBITS_2             ((uint8_t)0x02U)

#define UART_PARITY_NONE            ((uint8_t)0x00U)
#define UART_PARITY_EVEN            ((uint8_t)0x01U)
#define UART_PARITY_ODD             ((uint8_t)0x02U)


/*=============================FUNCTION PROTOTYPE======================*/
void UART_Init(USART_Handle_TypeDef	*huart);

//Sending
void UART_SendByte(USART_Handle_TypeDef *huart, uint8_t ch);
void UART_SendData(USART_Handle_TypeDef *huart,uint8_t *data, uint16_t len);
void UART_Transmit_IT(USART_Handle_TypeDef *huart, uint8_t *data,uint16_t len);

//Receive
uint8_t UART_ReceiveByte(USART_Handle_TypeDef *huart);
void UART_ReceiveData(USART_Handle_TypeDef *huart , uint8_t *buffer);



void UART_ClearError(USART_Handle_TypeDef *huart);
bool UART_HasError(USART_Handle_TypeDef *huart);

/*  Irq handler */
void UART_IRQ_HandlerCommon(USART_Handle_TypeDef *huart);


#endif
