#include "i2c.h"
#include <stdio.h>

#define PCLK1			42000000UL

/*--------------------Static Function---------------------------------*/

//start condition
static void I2C_Generate_Start_Condition(I2C_Handle_t *hi2c){
	hi2c->Instance->CR1 |= I2C_CR1_START;
}
//stop condition
static void I2C_Generate_Stop_Condition(I2C_Handle_t *hi2c){
	hi2c->Instance->CR1 |= I2C_CR1_STOP;
}

//wait flag
static uint8_t I2C_WaitFlag(I2C_Handle_t *hi2c,uint32_t flag,uint32_t timeout){
	//wait flags in SR1 : SB(check start conditon),TxE,RxNE
	while(!(hi2c->Instance->SR1 & flag)){
		if(--timeout == 0){
			return I2C_TIMEOUT;
		}
	}
	return I2C_OK;
}

//clear ADDR
static void I2C_ClearADDR(I2C_Handle_t *hi2c){
	//read sr1 and then read sr2
	uint32_t dummy = hi2c->Instance->SR1;
	dummy = hi2c->Instance->SR2;
	(void)dummy;
}
//check bus
static uint8_t I2C_CheckStatus(I2C_Handle_t *hi2c){
	if(hi2c->Instance->SR2 & I2C_SR2_BUSY){
		//busy
		return I2C_BUSY;
	}
	else return I2C_NOT_BUSY;
}

//=====================================================================

//Init I2C
void I2C_Init(I2C_Handle_t *hi2c){
	if(hi2c == NULL || hi2c->Instance == NULL) return;//check 
	
	I2C_TypeDef *hi2cX = hi2c->Instance;
	//enale clock
	if(hi2cX == I2C1){
		//i2c1
		RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	}
	else if(hi2cX == I2C2){
		//i2c2
		RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
	}
	else if(hi2cX == I2C3){
		//i2c3
		RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
	}
	else return;//not i2c
	
	//gpio_af
	if(hi2cX == I2C1){
		//i2c1
		GPIO_AF_Init(&I2C1_SCL_PB6,GPIO_OPEN_DRAIN,GPIO_NO_PULL,GPIO_SPEED_MEDIUM);
		GPIO_AF_Init(&I2C1_SDA_PB7,GPIO_OPEN_DRAIN,GPIO_NO_PULL,GPIO_SPEED_MEDIUM);
	}
	else if(hi2cX == I2C2){
		//i2c2
		GPIO_AF_Init(&I2C2_SCL_PB10,GPIO_OPEN_DRAIN,GPIO_NO_PULL,GPIO_SPEED_MEDIUM);
		GPIO_AF_Init(&I2C2_SDA_PB11,GPIO_OPEN_DRAIN,GPIO_NO_PULL,GPIO_SPEED_MEDIUM);
	}
	else if(hi2cX == I2C3){
		//i2c3
		GPIO_AF_Init(&I2C3_SCL_PA8,GPIO_OPEN_DRAIN,GPIO_NO_PULL,GPIO_SPEED_MEDIUM);
		GPIO_AF_Init(&I2C3_SDA_PC9,GPIO_OPEN_DRAIN,GPIO_NO_PULL,GPIO_SPEED_MEDIUM);
	}
	else return;//not i2c
	
	//Reset i2c
	hi2cX->CR1 |= I2C_CR1_SWRST;
	hi2cX->CR1 &= ~I2C_CR1_SWRST;
	
	//configure pclk
	hi2cX->CR2 &= ~I2C_CR2_FREQ;
	hi2cX->CR2 |= 42UL;//APB1 = 42Mhz
	//rate of clk
	hi2cX->CCR &= ~I2C_CCR_DUTY;
	//select mode and calculate t_rise
	if(hi2c->Timing <= I2C_MODE_STANDARD){
		//standard mode
	hi2cX->CCR &= ~I2C_CCR_FS;//0 : standard mode
	
	uint32_t ccr = PCLK1 / (2*hi2c->Timing);
	if(ccr < 4) ccr = 4;
		
	hi2cX->CCR &= ~I2C_CCR_CCR;
	hi2cX->CCR |= (ccr & 0xFFFUL);
		//t_rise: TRISE = t_rise_max/T_APB1 + 1
	
	hi2cX->TRISE = 43;
	}
	else{
		//fast mode
	hi2cX->CCR |= I2C_CCR_FS;//1 : fast mode
	hi2cX->CCR &= ~I2C_CCR_DUTY;                  // DUTY = 0 (2:1)
	
	uint32_t ccr = PCLK1 / (3 * hi2c->Timing);
	if (ccr < 1) ccr = 1;
		
	hi2cX->CCR &= ~I2C_CCR_CCR;
	hi2cX->CCR |= (ccr & 0xFFFUL);
		
	hi2cX->TRISE = 14;
	}
	//enable 
	hi2cX->CR1 |= (I2C_CR1_PE | I2C_CR1_ACK);
}

/*---------------------Transmition--------------------------------------*/
uint8_t I2C_Master_Transmit(I2C_Handle_t *hi2c, uint8_t slave_addr, uint8_t *pData, uint16_t Size){
	if(hi2c == NULL || hi2c->Instance == NULL) return I2C_ERROR;
	//Check bus
	if(I2C_CheckStatus(hi2c) == I2C_BUSY) return I2C_BUSY;
	//start + check start-condition
	I2C_Generate_Start_Condition(hi2c);
	if(I2C_WaitFlag(hi2c,I2C_SR1_SB,I2C_MAX_TIMEOUT) != I2C_OK ){
		I2C_Generate_Stop_Condition(hi2c);
		return I2C_ERROR;
	} 
	//send address + wait ACK (ADDR matched?)
	uint8_t address_byte = (slave_addr << 1) | I2C_WRITE;
	hi2c->Instance->DR = address_byte;
	if(I2C_WaitFlag(hi2c,I2C_SR1_ADDR,I2C_MAX_TIMEOUT) != I2C_OK ){
		I2C_Generate_Stop_Condition(hi2c);
		return I2C_ERROR;
	} 
	//clear ADDR
	I2C_ClearADDR(hi2c);
	//send data
	for (uint16_t i = 0; i < Size; i++){
        if (I2C_WaitFlag(hi2c, I2C_SR1_TXE, I2C_MAX_TIMEOUT) != I2C_OK)
        {
            I2C_Generate_Stop_Condition(hi2c);
            return I2C_ERROR;
        }
        hi2c->Instance->DR = pData[i];
   }
	//wait transmit finish
	if (I2C_WaitFlag(hi2c, I2C_SR1_BTF, I2C_MAX_TIMEOUT) != I2C_OK){
    
    I2C_Generate_Stop_Condition(hi2c);//error stop transmit
    return I2C_ERROR;   
	}
	//stop condition
	I2C_Generate_Stop_Condition(hi2c);
	return I2C_OK;
}

/*--------------------- Master Receive----------------------*/
uint8_t I2C_Master_Receive(I2C_Handle_t *hi2c, uint8_t slave_addr, uint8_t *pData, uint16_t len)
{
    if (hi2c == NULL || hi2c->Instance == NULL || pData == NULL || len == 0)
        return I2C_ERROR;

    I2C_TypeDef *I2Cx = hi2c->Instance;

    //check bus
    if (I2C_CheckStatus(hi2c) == I2C_BUSY)
        return I2C_BUSY;

    //Generate START
    I2C_Generate_Start_Condition(hi2c);
    if (I2C_WaitFlag(hi2c, I2C_SR1_SB, I2C_MAX_TIMEOUT) != I2C_OK){
        I2C_Generate_Stop_Condition(hi2c);
        return I2C_ERROR;
    }

    //Slave Address + Read (1)
    I2Cx->DR = (slave_addr << 1) | I2C_READ;

    if (I2C_WaitFlag(hi2c, I2C_SR1_ADDR, I2C_MAX_TIMEOUT) != I2C_OK){
        I2C_Generate_Stop_Condition(hi2c);
        return I2C_ERROR;       
    }

		//Receive data
    if (len == 1)
    {
        //1 byte
				
        I2Cx->CR1 &= ~I2C_CR1_ACK;           // NACK before read byte
				I2C_ClearADDR(hi2c);

        if (I2C_WaitFlag(hi2c, I2C_SR1_RXNE, I2C_MAX_TIMEOUT) != I2C_OK)
        {
            I2C_Generate_Stop_Condition(hi2c);
            return I2C_ERROR;
        }

        pData[0] = I2Cx->DR;

        I2C_Generate_Stop_Condition(hi2c);   // Stop
    }
    else
    {
				I2C_ClearADDR(hi2c);//clear before reading
        //n byte
        for (uint16_t i = 0; i < len -3; i++){//remain 3 bytes
					if(I2C_WaitFlag(hi2c,I2C_SR1_RXNE,I2C_MAX_TIMEOUT) != I2C_OK){
						return I2C_ERROR;
					}
					pData[i] = I2Cx->DR;
				}//end step1
				if(I2C_WaitFlag(hi2c,I2C_SR1_BTF,I2C_MAX_TIMEOUT) != I2C_OK){
					return I2C_ERROR;
				}//wait byte tranferred
				//[len-3]->DR 
				//NACK
				I2Cx->CR1 &= ~I2C_CR1_ACK;
				//read N-2(len -3)
				pData[len-3] = I2Cx->DR;//N-1 or len-2 in DR
				if(I2C_WaitFlag(hi2c,I2C_SR1_BTF,I2C_MAX_TIMEOUT ) != I2C_OK){
					return I2C_ERROR;
				}//wait byte tranferred
				//stop
				I2C_Generate_Stop_Condition(hi2c);
				pData[len-2] = I2Cx->DR;//N-1
				if(I2C_WaitFlag(hi2c, I2C_SR1_RXNE, I2C_MAX_TIMEOUT) != I2C_OK) return I2C_ERROR;
				pData[len-1] = I2Cx->DR;//N
    }
		
		I2Cx->CR1 |= I2C_CR1_ACK; 
    return I2C_OK;
    return I2C_OK;
}

