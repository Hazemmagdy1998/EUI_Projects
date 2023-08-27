#ifndef LCD_H_
#define LCD_H_

#include "CPU_Configuration.h"
#define DATA_BITS_MODE 8
#define DECIMAL_POINT_ACCURACY  8

#if(DATA_BITS_MODE == 4)
#define UPPER_BITS
#endif
#define PA5 (1<<5)
#define PA6 (1<<6)
#define PA7 (1<<7)

#define RS 5
#define RW 6
#define E  7


#define LCD_CTRL_PORT         GPIO_PORTA_DATA_R
#define LCD_CTRL_PORT_DIR     GPIO_PORTA_DIR_R

#define LCD_DATA_PORT         GPIO_PORTB_DATA_R
#define LCD_DATA_PORT_DIR     GPIO_PORTB_DIR_R

/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_init(void);
void LCD_sendCommand(uint8_t command);
void LCD_displayCharacter(uint8_t data);
void LCD_displayString(const uint8_t *str);
void LCD_clearScreen(void);
void LCD_goToRowColumn(uint8_t row,uint8_t col);
void LCD_displayStringRowColumn(uint8_t row,uint8_t col,const uint8_t *Str);
void LCD_void_SendNumber(SINT32_t number);
void LCD_void_Send_FLoatNumber(fint64_t Fnumber);

#endif /* LCD_H_ */
