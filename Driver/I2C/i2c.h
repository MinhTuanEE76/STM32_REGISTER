#ifndef __I2C_H
#define __I2C_H

#include <stdint.h>
#include <gpio.h>

/*------------------------------mapping address-------------------*/
typedef struct{
	volatile uint32_t CR1; //0x00
	volatile uint32_t CR2;	//0x04
	volatile uint32_t OAR1;//0x08
	volatile uint32_t OAR2;//0x0C
	volatile uint32_t DR;  //0x10
	volatile uint32_t SR1; //0x14
	volatile uint32_t SR2;	//0x18
	volatile uint32_t CCR; //0x1C
	volatile uint32_t TRISE;//0x20
	volatile uint32_t FLTR;//0x24
}I2C_TypeDef;

#define I2C1_BASE_ADDRESS 			0x40005400UL
#define I2C2_BASE_ADDRESS 			0x40005800UL
#define I2C3_BASE_ADDRESS 			0x40005C00UL

#define I2C1				((volatile I2C_TypeDef*)I2C1_BASE_ADDRESS)
#define I2C2				((volatile I2C_TypeDef*)I2C2_BASE_ADDRESS)
#define I2C3				((volatile I2C_TypeDef*)I2C3_BASE_ADDRESS)

/* ========================== I2C Bit Definitions ========================== */

/* --------------------- I2C_CR1 --------------------- */
#define I2C_CR1_PE          (1U << 0)     // Peripheral Enable
#define I2C_CR1_SMBUS       (1U << 1)     // SMBus mode
#define I2C_CR1_SMBTYPE     (1U << 3)     // SMBus type (Host/Device)
#define I2C_CR1_ENARP       (1U << 4)     // ARP enable
#define I2C_CR1_ENPEC       (1U << 5)     // PEC enable
#define I2C_CR1_ENGC        (1U << 6)     // General Call enable
#define I2C_CR1_NOSTRETCH   (1U << 7)     // Clock stretching disable
#define I2C_CR1_START       (1U << 8)     // Start generation
#define I2C_CR1_STOP        (1U << 9)     // Stop generation
#define I2C_CR1_ACK         (1U << 10)    // Acknowledge enable
#define I2C_CR1_POS         (1U << 11)    // Acknowledge/PEC position
#define I2C_CR1_PEC         (1U << 12)    // Packet Error Checking
#define I2C_CR1_ALERT       (1U << 13)    // SMBus alert
#define I2C_CR1_SWRST       (1U << 15)    // Software reset

/* --------------------- I2C_CR2 --------------------- */
#define I2C_CR2_FREQ_0      (1U << 0)     // FREQ[5:0] bits
#define I2C_CR2_FREQ        (0x3FU << 0)  // Frequency mask (6 bits)
#define I2C_CR2_ITERREN     (1U << 8)     // Error interrupt enable
#define I2C_CR2_ITEVTEN     (1U << 9)     // Event interrupt enable
#define I2C_CR2_ITBUFEN     (1U << 10)    // Buffer interrupt enable
#define I2C_CR2_DMAEN       (1U << 11)    // DMA enable
#define I2C_CR2_LAST        (1U << 12)    // DMA last transfer

/* --------------------- I2C_OAR1 --------------------- */
#define I2C_OAR1_ADD0       (1U << 0)     // Address bit 0 (10-bit)
#define I2C_OAR1_ADD7_1     (0x7FU << 1)  // 7-bit address
#define I2C_OAR1_ADD         (0x3FFU << 0)// Full 10-bit address mask
#define I2C_OAR1_ADDMODE    (1U << 15)    // Addressing mode (0=7-bit, 1=10-bit)

/* --------------------- I2C_SR1 --------------------- */
#define I2C_SR1_SB          (1U << 0)     // Start bit
#define I2C_SR1_ADDR        (1U << 1)     // Address sent/matched
#define I2C_SR1_BTF         (1U << 2)     // Byte transfer finished
#define I2C_SR1_ADD10       (1U << 3)     // 10-bit header sent
#define I2C_SR1_STOPF       (1U << 4)     // Stop detection
#define I2C_SR1_RXNE        (1U << 6)     // Data register not empty
#define I2C_SR1_TXE         (1U << 7)     // Data register empty
#define I2C_SR1_BERR        (1U << 8)     // Bus error
#define I2C_SR1_ARLO        (1U << 9)     // Arbitration lost
#define I2C_SR1_AF          (1U << 10)    // Acknowledge failure
#define I2C_SR1_OVR         (1U << 11)    // Overrun/Underrun
#define I2C_SR1_PECERR      (1U << 12)    // PEC error
#define I2C_SR1_TIMEOUT     (1U << 14)    // Timeout
#define I2C_SR1_SMBALERT    (1U << 15)    // SMBus alert

/* --------------------- I2C_SR2 --------------------- */
#define I2C_SR2_MSL         (1U << 0)     // Master/Slave
#define I2C_SR2_BUSY        (1U << 1)     // Bus busy
#define I2C_SR2_TRA         (1U << 2)     // Transmitter/Receiver
#define I2C_SR2_GENCALL     (1U << 4)     // General call address
#define I2C_SR2_SMBDEFAULT  (1U << 5)     // SMBus device default address
#define I2C_SR2_SMBHOST     (1U << 6)     // SMBus host header
#define I2C_SR2_DUALF       (1U << 7)     // Dual flag
#define I2C_SR2_PEC         (0xFFU << 8)  // Packet Error Checking value

/* --------------------- I2C_CCR --------------------- */
#define I2C_CCR_CCR         (0xFFFU << 0) // Clock control register (12 bits)
#define I2C_CCR_DUTY        (1U << 14)    // Fast mode duty cycle (0=2:1, 1=16:9)
#define I2C_CCR_FS          (1U << 15)    // I2C master mode selection (0=Standard, 1=Fast)

/* --------------------- I2C_TRISE --------------------- */
#define I2C_TRISE_TRISE     (0x3FU << 0)  // Maximum rise time (6 bits)

/* --------------------- I2C_FLTR (Filter Register) --------------------- */
#define I2C_FLTR_DNF        (0x0FU << 0)  // Digital noise filter
#define I2C_FLTR_ANOFF      (1U << 4)     // Analog noise filter OFF

#define I2C_ADDRESS_7BIT       0 // 7bit
#define I2C_ADDRESS_10BIT      1 //10 bit
#define I2C_MODE_STANDARD      100000UL
#define I2C_MODE_FAST			     400000UL
#define I2C_RISING_TIME_STD    1000UL
#define I2C_RISING_TIME_FAST   300UL
//Handle i2c
typedef struct{
	volatile I2C_TypeDef *Instance;//pointer to reg
	
	uint8_t AddressingMode;//7bit or 10 bit
	uint32_t Timing ; //standard mode(<100khz) or fast mode (<400khz)
	uint16_t Address;
}I2C_Handle_TypeDef;

#define I2C_OK          0
#define I2C_ERROR       1U
#define I2C_BUSY 	  		2U
#define I2C_NOT_BUSY 	  3U
#define I2C_TIMEOUT     4U
#define I2C_MAX_TIMEOUT 0xFFUL

#define I2C_WRITE				0
#define I2C_READ				1

#define I2C_FAST_MODE 				400000UL
#define I2C_STANDARD_MODE 		100000UL

/* ====================== Function Prototypes ====================== */
void I2C_Init(volatile I2C_Handle_TypeDef *hi2c);
void I2C_START(volatile I2C_Handle_TypeDef *hi2c);
void I2C_STOP(volatile I2C_Handle_TypeDef *hi2c);
//Transmit
uint8_t I2C_Master_Transmit(volatile I2C_Handle_TypeDef *hi2c, uint8_t slave_addr, uint8_t *pData, uint16_t len);

//Receive
uint8_t I2C_Master_Receive(volatile I2C_Handle_TypeDef *hi2c, uint8_t slave_addr, uint8_t *pData, uint16_t len);

/*  */

#endif