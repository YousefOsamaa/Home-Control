

#include "SREG_Private.h"

void SREG_vid_EnableBitI(void)
{
    SREG |= (1 << SREG_BIT_I);
}

void SREG_vid_ClearBitI(void)
{
    
    SREG &= ~(1 << SREG_BIT_I);

}
