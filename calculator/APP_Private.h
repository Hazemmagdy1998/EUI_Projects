#ifndef APP_PRIVATE_H_
#define APP_PRIVATE_H_

#include "keypad.h"
#include "lcd.h"

void initializations(void);

int calculator_sort(void);
fint64_t calculator(void);
void keypad_input();
void error_handle(void);
void resett(void);
char is_operator(char input_operator);
char is_number(char input_number);


#endif /* APP_PRIVATE_H_ */
