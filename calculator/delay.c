#include "delay.h"


void Delay_in_ms (unsigned short delay){

    NVIC_ST_RELOAD_R = delay * MS_CONST;
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 0b1;
    while(!(NVIC_ST_CTRL_R & (1<<16)));
    NVIC_ST_CURRENT_R = 0; /* Clears count flag in control register */
    NVIC_ST_CTRL_R &= 0; /* Stop timer */

}

void Delay_in_us (unsigned long delay){
    NVIC_ST_RELOAD_R = delay * US_CONST;
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 0b1;
    while(!(NVIC_ST_CTRL_R & (1<<16)));
    NVIC_ST_CURRENT_R = 0; /* Clears count flag in control register */
    NVIC_ST_CTRL_R &= 0; /* Stop timer */
}
