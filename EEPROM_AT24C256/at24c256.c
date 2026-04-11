//#include "at24c256.h"
//#include <string.h>


//static uint8_t AT24C256_Write_InPage(I2C_Handle_t *hi2c, uint16_t mem_addr, uint8_t *pData, uint16_t len)
//{
//    uint8_t tx_buf[AT24C256_PAGE_SIZE + 2]; 

//    if (len > AT24C256_PAGE_SIZE) return EEPROM_ERROR;

//    
//    tx_buf[0] = (uint8_t)((mem_addr >> 8) & 0xFF);
//    tx_buf[1] = (uint8_t)(mem_addr & 0xFF);

//    
//    memcpy(&tx_buf[2], pData, len);

//    
//    if (I2C_Master_Transmit(hi2c, AT24C256_I2C_ADDR, tx_buf, len + 2) != I2C_OK) {
//        return EEPROM_ERROR;
//    }
//    return EEPROM_OK;
//}



//uint8_t AT24C256_Write_Byte(I2C_Handle_t *hi2c, uint16_t mem_addr, uint8_t data)
//{
//    return AT24C256_Write_InPage(hi2c, mem_addr, &data, 1);
//}

//uint8_t AT24C256_Read_Byte(I2C_Handle_t *hi2c, uint16_t mem_addr, uint8_t *pData)
//{
//    return AT24C256_Read_Buffer(hi2c, mem_addr, pData, 1);
//}

//uint8_t AT24C256_Read_Buffer(I2C_Handle_t *hi2c, uint16_t mem_addr, uint8_t *pData, uint16_t len)
//{
//    uint8_t addr_buf[2];
//    addr_buf[0] = (uint8_t)((mem_addr >> 8) & 0xFF);
//    addr_buf[1] = (uint8_t)(mem_addr & 0xFF);

//    if (I2C_Master_Transmit(hi2c, AT24C256_I2C_ADDR, addr_buf, 2) != I2C_OK) {
//        return EEPROM_ERROR;
//    }

//    if (I2C_Master_Receive(hi2c, AT24C256_I2C_ADDR, pData, len) != I2C_OK) {
//        return EEPROM_ERROR;
//    }

//    return EEPROM_OK;
//}

//uint8_t AT24C256_Write_Buffer(I2C_Handle_t *hi2c, uint16_t mem_addr, uint8_t *pData, uint16_t len)
//{
//    uint16_t bytes_to_write;
//    uint16_t offset = 0;

//    while (len > 0) {
//      
//        bytes_to_write = AT24C256_PAGE_SIZE - (mem_addr % AT24C256_PAGE_SIZE);

//        
//        if (len < bytes_to_write) {
//            bytes_to_write = len;
//        }

//        if (AT24C256_Write_InPage(hi2c, mem_addr, &pData[offset], bytes_to_write) != EEPROM_OK) {
//            return EEPROM_ERROR;
//        }

//        mem_addr += bytes_to_write;
//        offset   += bytes_to_write;
//        len      -= bytes_to_write;
//    }

//    return EEPROM_OK;
//}