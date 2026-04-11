#include "i2c.h"
#include <stdio.h>
#include <string.h>
#define PCLK1 42000000UL

/*--------------------Static Function---------------------------------*/



//=====================================================================
void I2C_START(volatile I2C_Handle_TypeDef *hi2c){
	//Generate START
    hi2c->Instance->CR1 |= I2C_CR1_START;
		//Check START Condition
		while(!(hi2c->Instance->SR1 & I2C_SR1_SB)){
			///
		}
}
void I2C_STOP(volatile I2C_Handle_TypeDef *hi2c){
	hi2c->Instance->CR1 |= I2C_CR1_STOP;
}
// Init I2C
void I2C_Init(volatile I2C_Handle_TypeDef *hi2c)
{
    if (hi2c == NULL || hi2c->Instance == NULL)
    {
        return;  // Invalid handle
    }

    volatile I2C_TypeDef *I2Cx = hi2c->Instance;
   
    //Enable I2C clock
    if (I2Cx == I2C1)
    {
        RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
        volatile uint32_t tmp = RCC->APB1ENR;  // Dummy read to ensure clock is enabled
        (void)tmp;
    }
    else if (I2Cx == I2C2)
    {
        RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
        volatile uint32_t tmp = RCC->APB1ENR;
        (void)tmp;
    }
    else if (I2Cx == I2C3)
    {
        RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
        volatile uint32_t tmp = RCC->APB1ENR;
        (void)tmp;
    }
    else
    {
        return;  // Unsupported I2C instance
    }

    //Configure GPIO for I2C (SCL and SDA pins) */
    if (I2Cx == I2C1)
    {
        // PB6 -> I2C1_SCL, PB7 -> I2C1_SDA
        GPIO_AF_Init(&I2C1_SCL_PB6, GPIO_OPEN_DRAIN, GPIO_PULL_UP, GPIO_SPEED_MEDIUM);
        GPIO_AF_Init(&I2C1_SDA_PB7, GPIO_OPEN_DRAIN, GPIO_PULL_UP, GPIO_SPEED_MEDIUM);
    }
    else if (I2Cx == I2C2)
    {
        // PB10 -> I2C2_SCL, PB11 -> I2C2_SDA
        GPIO_AF_Init(&I2C2_SCL_PB10, GPIO_OPEN_DRAIN, GPIO_PULL_UP, GPIO_SPEED_MEDIUM);
        GPIO_AF_Init(&I2C2_SDA_PB11, GPIO_OPEN_DRAIN, GPIO_PULL_UP, GPIO_SPEED_MEDIUM);
    }
    else if (I2Cx == I2C3)
    {
        // PA8 -> I2C3_SCL, PC9 -> I2C3_SDA
        GPIO_AF_Init(&I2C3_SCL_PA8, GPIO_OPEN_DRAIN, GPIO_PULL_UP, GPIO_SPEED_MEDIUM);
        GPIO_AF_Init(&I2C3_SDA_PC9, GPIO_OPEN_DRAIN, GPIO_PULL_UP, GPIO_SPEED_MEDIUM);
    }

    //Reset the I2C peripheral
    I2Cx->CR1 &= ~I2C_CR1_PE;               // Disable I2C first
    I2Cx->CR1 |= I2C_CR1_SWRST;             // Software reset
    for (volatile uint32_t i = 0; i < 50; i++);  // Small delay
    I2Cx->CR1 &= ~I2C_CR1_SWRST;            // Release reset

    //Configure I2C clock source (PCLK1 frequency)
    I2Cx->CR2 &= ~I2C_CR2_FREQ;
    I2Cx->CR2 |= 42UL;                      // APB1 = 42 MHz

    //Configure I2C speed (CCR and TRISE)
    if (hi2c->Timing <= 100000UL)           // Standard Mode (100 kHz)
    {
        /* Standard mode */
        I2Cx->CCR &= ~I2C_CCR_FS;           // Clear FS bit -> Standard mode

        uint32_t ccr = PCLK1 / (2 * hi2c->Timing);
        if (ccr < 4) ccr = 4;               // Minimum allowed value

				I2Cx->CCR &= ~0xFFFUL;//12bit [11:0]
        I2Cx->CCR |= ccr;

        //Maximum Rise Time 1000ns
        I2Cx->TRISE = (PCLK1 / 1000000UL) + 1;   // ~43 for 42MHz
    }
    else                                    // Fast Mode (typically 400 kHz)
    {
        /* Fast mode */
        I2Cx->CCR |= I2C_CCR_FS;            // Set FS bit -> Fast mode
        I2Cx->CCR &= ~I2C_CCR_DUTY;         // Duty cycle 2:1 (default)

        uint32_t ccr = PCLK1 / (3 * hi2c->Timing);
        if (ccr < 1) ccr = 1;

        I2Cx->CCR &= ~0xFFFUL;
        I2Cx->CCR |= (ccr & 0xFFFUL);

        /* Maximum Rise Time for Fast mode */
        I2Cx->TRISE = 14;                   // Safe value for 400kHz @ 42MHz
    }

    //Enable I2C peripheral and ACK
		I2Cx->CR1 |= I2C_CR1_ACK;      
    I2Cx->CR1 &= ~I2C_CR1_PE;            
    I2Cx->CR1 |= I2C_CR1_PE;
		     
}

/*---------------------Transmition--------------------------------------*/
uint8_t I2C_Master_Transmit(volatile I2C_Handle_TypeDef  *hi2c, uint8_t slave_addr,uint8_t *pData, uint16_t len)
{
    if (hi2c == NULL || hi2c->Instance == NULL || pData == NULL || len == 0)
        return I2C_ERROR;

    volatile I2C_TypeDef *I2Cx = hi2c->Instance;
		//check bus
//		while(I2Cx->SR2 & I2C_SR2_BUSY){
//		//wait not busy
//		}
    
    //Send slave address + Write (0)
    uint8_t address_byte = (slave_addr << 1) | I2C_WRITE;   // I2C_WRITE = 0
    I2Cx->DR = address_byte;

    // Wait for ADDR
		while(!(I2Cx->SR1 & I2C_SR1_ADDR)){
		if(I2Cx->SR1 & I2C_SR1_AF){
			I2Cx->CR1 |= I2C_CR1_STOP;
					I2Cx->SR1 &= ~I2C_SR1_AF;
					return I2C_ERROR;
		}
	}
		//clear ADDR after matching address
		volatile uint32_t dummy = hi2c->Instance->SR1;
		dummy = hi2c->Instance->SR2;
		
    //Send data
		
    for (uint16_t i = 0; i < len; i++){
			while(!(I2Cx->SR1 & I2C_SR1_TXE)){
				if(I2Cx->SR1 & I2C_SR1_AF){
					//ACK fail
					I2Cx->CR1 |= I2C_CR1_STOP;
					I2Cx->SR1 &= ~I2C_SR1_AF;
					return I2C_ERROR;
				}
			}
			//not error and TXE is set
			I2Cx->DR = pData[i];
		}
    
    return I2C_OK;
}

/*--------------------- Master Receive----------------------*/
uint8_t I2C_Master_Receive(volatile I2C_Handle_TypeDef *hi2c, uint8_t slave_addr,uint8_t *pData, uint16_t len)
{
	if (hi2c == NULL || hi2c->Instance == NULL || pData == NULL || len == 0)
		return I2C_ERROR;

	volatile I2C_TypeDef *I2Cx = hi2c->Instance;

	// check bus
//	while(I2Cx->SR2 & I2C_SR2_BUSY){
//		
//	}
	I2Cx->CR1 |= I2C_CR1_ACK;
	// Slave Address + Read (1)
	I2Cx->DR = (slave_addr << 1) | I2C_READ;
	while(!(I2Cx->SR1 & I2C_SR1_ADDR)){
		if(I2Cx->SR1 & I2C_SR1_AF){
			I2Cx->CR1 |= I2C_CR1_STOP;
					I2Cx->SR1 &= ~I2C_SR1_AF;
					return I2C_ERROR;
		}
	}
	//clear ADDR after matching address
	uint32_t dummy = I2Cx->SR1;
	dummy = I2Cx->SR2;
	(void)dummy;

	
	// Receive data
	I2Cx->CR1 |= I2C_CR1_ACK;//certainly ACK is set
	if(len == 1){
		I2Cx->CR1 &= ~I2C_CR1_ACK;
		I2Cx->CR1 |= I2C_CR1_STOP;
		while(!(I2Cx->SR1 & I2C_SR1_RXNE)){
			//wait RXNE  = 1
		}
		pData[0] = I2Cx->DR;
	}
	else{//N > 2 (N is amount of byte receiving)
		for(uint16_t i = 0 ; i < len ; i++){
			if(i == len -2){
				//
				while(!(I2Cx->SR1 & I2C_SR1_RXNE));//wait byte N-1->DR
				I2Cx->CR1 &= ~I2C_CR1_ACK;
				I2Cx->CR1 |= I2C_CR1_STOP;
				pData[i] = I2Cx->DR;
				
				i++;//byte N
				while(!(I2Cx->SR1 & I2C_SR1_RXNE));//wait byte N->DR
				pData[i] = I2Cx->DR;
				break;
			}
			while(!(I2Cx->SR1 & I2C_SR1_RXNE)){
				//
			}
			pData[i] = I2Cx->DR; 
		}
	}
	I2Cx->CR1 |= I2C_CR1_ACK;
	return I2C_OK;
}
