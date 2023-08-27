
#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "CPU_Configuration.h"
#define N_ROW 4
#define N_COL 4

#define DIR GPIO_PORTB_DIR_R
#define OUT GPIO_PORTB_DATA_R


#define Column_DIR     GPIO_PORTF_DIR_R
#define ROW_DIR        GPIO_PORTE_DIR_R
#define Column_DATA    GPIO_PORTF_DATA_R
#define ROW_DATA       GPIO_PORTE_DATA_R
unsigned char KeyPad_getPressedKey(void);
void keypad_init(void);



#endif /* KEYPAD_H_ */
