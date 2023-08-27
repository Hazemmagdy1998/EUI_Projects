#ifndef SYSTICK_H_
#define SYSTICK_H_


#include "common_macros.h"
#include "hw_gpio.h"
#include "std_types.h"

#define SEC_COUNT_VAR 4000000 // value to make Systick timer calculate 1 second


// enum to determine the state of the program (start,stop,lab,reset) and this determined by switches
typedef enum {
    start,stop,lap,reset
}state;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Systick_Handler (void);
void Systick_Count_Sec_Init(void);

#endif /* SYSTICK_H_ */
