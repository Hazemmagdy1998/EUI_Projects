 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Hazem Magdy
 *
 *******************************************************************************/
#ifndef LCD_H_
#define LCD_H_


#include "hw_gpio.h"
#include "common_macros.h"
#include "std_types.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define DATA_BITS_MODE 8 //8_BIT MODE

#if(DATA_BITS_MODE == 4) // 4_BIT MODE
#define UPPER_BITS
#endif
/*HW CONTROL PINS */
#define PA5 (1<<5)
#define PA6 (1<<6)
#define PA7 (1<<7)

#define RS 5
#define RW 6
#define E  7

/*PORTA : PA5 , PA6 AND PA7 TO CONTROL PINS FOR LCD */
#define LCD_CTRL_PORT         GPIO_PORTA_DATA_R
#define LCD_CTRL_PORT_DIR     GPIO_PORTA_DIR_R
/*PORTB : ALL PORTB PINS USED FOR DATA PINS OF LCD*/
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
void LCD_sendCommand(uint8_t command);
void LCD_displayCharacter(uint8_t data);
void LCD_displayString(const uint8_t *Str);
void LCD_init(void);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uint8_t row,uint8_t col,const uint8_t *Str);
void LCD_goToRowColumn(uint8_t row,uint8_t col);
void LCD_intgerToString(uint32_t data);
void LCD_void_SendNumber(sint32_t Copy_s32Number);
void delay(uint32_t num);





#endif /* LCD_H_ */
