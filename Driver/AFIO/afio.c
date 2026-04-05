#include "afio.h"

/*--------------------internal function-------------------------*/
static void AFIO_Set(volatile GPIO_TypeDef *GPIOx,uint16_t Pin,uint8_t AF){
			uint32_t positon;
			for(positon = 0 ; positon < 16 ; positon++){
				if(Pin & (1 << positon)){
					if(positon <= 7){
						//AFRL
						GPIOx->AFRL = ( GPIOx->AFRL & ~(0xFU << positon*4) | (uint32_t)(AF << (positon*4))  );
					}
					else{//postion >  7
						uint32_t temp = positon - 8U ;
						GPIOx->AFRH =(GPIOx->AFRH & ~(0xFU << positon*4) | (uint32_t)(AF << (temp*4))  );
					}
				}
			}
}

/*--------------------internal function-------------------------*/

void GPIO_AF_Init(const GPIO_AF_TypeDef *af, uint8_t Type, uint8_t Pull, uint8_t Speed){
		
}