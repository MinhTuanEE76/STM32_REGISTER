#ifndef AT24C256_H
#define AT24C256_H

#include "i2c.h" 


#define AT24C256_I2C_ADDR    0x50       
#define AT24C256_PAGE_SIZE   64         
#define AT24C256_TOTAL_SIZE  32768      
#define AT24C256_WRITE_TIME  5          

#define EEPROM_OK            0
#define EEPROM_ERROR         1
#define EEPROM_BUSY          2




uint8_t AT24C256_Write_Byte(I2C_Handle_t *hi2c, uint16_t mem_addr, uint8_t data);
uint8_t AT24C256_Read_Byte(I2C_Handle_t *hi2c, uint16_t mem_addr, uint8_t *pData);
uint8_t AT24C256_Write_Buffer(I2C_Handle_t *hi2c, uint16_t mem_addr, uint8_t *pData, uint16_t len);
uint8_t AT24C256_Read_Buffer(I2C_Handle_t *hi2c, uint16_t mem_addr, uint8_t *pData, uint16_t len);

#endif 