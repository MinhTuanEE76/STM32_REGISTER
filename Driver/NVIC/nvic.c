#include "nvic.h"

/*========================= NVIC Functions Implementation =========================*/

void NVIC_EnableIRQ(IRQn_Type IRQn)
{
    if (IRQn >= 0)
    {
        uint32_t reg_offset = (uint32_t)IRQn >> 5U;
        uint32_t bit_pos    = (uint32_t)IRQn & 0x1FU;

        NVIC->ISER[reg_offset] = (1U << bit_pos);
    }
}

void NVIC_DisableIRQ(IRQn_Type IRQn)
{
    if (IRQn >= 0)
    {
        uint32_t reg_offset = (uint32_t)IRQn >> 5U;
        uint32_t bit_pos    = (uint32_t)IRQn & 0x1FU;

        if (reg_offset == 0) NVIC->ISER[0] = (1U << bit_pos);   
        if (reg_offset == 0) NVIC->ICER[0] = (1U << bit_pos);   
        
    }
}