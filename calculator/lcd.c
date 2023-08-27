#include "lcd.h"

/*******************************************************************************
                       Functions Definitions
 *******************************************************************************
********************************************************************************


*******************************************************************************
 *FUNCTION NAME : INIT
 *
 *DESCRIPTION : FUNCTION TO INITIALIZE THE LCD_MODULE
 *******************************************************************************/


void LCD_init(void){
    LCD_CTRL_PORT_DIR |= PA5 | PA6 | PA7 ; // CONFIGURE THE E , RS AND RW AS OUTPUT PINS

#if(DATA_BITS_MODE == 4)
#ifdef UPPER_BITS
    LCD_DATA_PORT_DIR |=  0xF0;
#else
    LCD_DATA_PORT_DIR |=  0x0F;
#endif
    LCD_sendCommand(FOUR_BITS_DATA_MODE);
    LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
#elif (DATA_BITS_MODE == 8)
    LCD_DATA_PORT_DIR =  0xFF;
//    LCD_sendCommand(0xC0);
    LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);
#endif
    LCD_sendCommand(CURSOR_OFF);
    LCD_sendCommand(CLEAR_COMMAND);

}
/*******************************************************************************
 * FUNCTION NAME: LCD_sendCommand
 *
 * DESCRIPTION: Function to send a command to the LCD module
 *
 * INPUTS: uint8_t command: The command to be sent
 *
 *******************************************************************************/
void LCD_sendCommand(uint8_t command){
    CLR_BIT(LCD_CTRL_PORT,RS);
    CLR_BIT(LCD_CTRL_PORT,RW);
    Delay_in_ms(1);
    SET_BIT(LCD_CTRL_PORT,E);
    Delay_in_ms(1);
#if(DATA_BITS_MODE == 4)
#ifdef UPPER_BITS // SENDING UPPER BITS
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0xF0));
#else
    LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command & 0xF0) >> 4);
#endif
    Delay_in_ms(1);
    CLR_BIT(LCD_CTRL_PORT,7);
    Delay_in_ms(1);
    SET_BIT(LCD_CTRL_PORT,7);
    Delay_in_ms(1);
#ifdef UPPER_BITS // SENDING LOWER BITS
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4);
#else
    LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (command & 0x0F);
#endif
    Delay_in_ms(1);
    CLR_BIT(LCD_CTRL_PORT,7);
    Delay_in_ms(1);
#elif (DATA_BITS_MODE == 8)
    LCD_DATA_PORT = command;
    Delay_in_ms(1);
    CLR_BIT(LCD_CTRL_PORT,E);
    Delay_in_ms(1);
#endif
}
/*******************************************************************************
 * FUNCTION NAME: LCD_displayCharacter
 *
 * DESCRIPTION: Function to display a character on the LCD module
 *
 * INPUTS: uint8_t data: The character to be displayed
 *
 *******************************************************************************/
void LCD_displayCharacter(uint8_t data){
    SET_BIT(LCD_CTRL_PORT,5);
    CLR_BIT(LCD_CTRL_PORT,6);
    Delay_in_ms(1);
    SET_BIT(LCD_CTRL_PORT,7);
    Delay_in_ms(1);
#if(DATA_BITS_MODE == 4)
#ifdef UPPER_BITS // SENDING UPPER BITS
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0xF0));
#else
    LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((data & 0xF0) >> 4);
#endif
    Delay_in_ms(1);
    CLR_BIT(LCD_CTRL_PORT,7);
    Delay_in_ms(1);
    SET_BIT(LCD_CTRL_PORT,7);
#ifdef UPPER_BITS // SENDING LOWER BITS
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0x0F) << 4);
#else
    LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (data & 0x0F);
#endif
    Delay_in_ms(1);
     CLR_BIT(LCD_CTRL_PORT,7);
     Delay_in_ms(1);
#elif (DATA_BITS_MODE == 8)
    LCD_DATA_PORT = data;
    Delay_in_ms(1);
    CLR_BIT(LCD_CTRL_PORT,E);
    Delay_in_ms(1);
#endif
}
/*******************************************************************************
 * FUNCTION NAME: LCD_displayString
 *
 * DESCRIPTION: Function to display a string on the LCD module
 *
 * INPUTS: const uint8_t *str: Pointer to char to the string to be displayed
 *
 *******************************************************************************/
void LCD_displayString(const uint8_t *str){
    uint32_t i = 0;
    while(str[i] != '\0'){
        LCD_displayCharacter(str[i]);
        i++;
    }

}
/*******************************************************************************
 * FUNCTION NAME: LCD_clearScreen
 *
 * DESCRIPTION: clearing the screen of LCD
 *
 *******************************************************************************/
void LCD_clearScreen(void){
    LCD_sendCommand(CLEAR_COMMAND);
}
/*******************************************************************************
 * FUNCTION NAME: LCD_goToRowColumn
 *
 * DESCRIPTION: Function to move the cursor to a specific row and column on the LCD module
 *
 * INPUTS: - uint8_t row: The row number (0 or 1)
 *         - uint8_t col: The column number (0 to 15)
 *
 *******************************************************************************/
void LCD_goToRowColumn(uint8_t row,uint8_t col){
    uint8_t address ;
    switch (row){
    case 0 :
        address = col ;
        break;
    case 1 :
        address = col + 0xC0;
        break;
    case 2 :
        address = col + 0x10;
        break ;
    case 3 :
        address = col + 0x50;
        break;
    }
    LCD_sendCommand(address | SET_CURSOR_LOCATION); // set cursor location to set the cursor and loop it by our index

}
/*******************************************************************************
 * FUNCTION NAME: LCD_displayStringRowColumn
 *
 * DESCRIPTION: Function to display a string on a specific row and specific column
 *
 * INPUTS: uint8_t row , uint8_t col : row and col numbers to go to them
 *         const uint8_t *str : pointer to char to the string that will
 *         be displayed at required row and column
 *
 *******************************************************************************/

void LCD_displayStringRowColumn(uint8_t row,uint8_t col,const uint8_t *Str){
    LCD_goToRowColumn(row, col);
    LCD_displayString(Str);
}


/*******************************************************************************
 * FUNCTION NAME: LCD_void_SendNumber
 *
 * DESCRIPTION: Function to display a number on the LCD module
 *
 * INPUTS: uint32_t Copy_u32_Number: The number to be displayed
 *
 *******************************************************************************/
void LCD_void_SendNumber(SINT32_t number)
{
    if(number < 0){
        LCD_displayCharacter('-');
         number*=(-1);
     }
     SINT32_t num = number;
     UINT16_t digit = 0;
     while(num != 0){
         digit++;
         num/=10;
     }
     if(number == 0){
         LCD_displayCharacter('0');
         }else{
         UINT8_t arr_num[15];

         int i;
         for(i = digit-1 ; i >= 0 ;i--){
             arr_num[i]=number %10 + '0';
             number/=10;
         }

         int j;
         for(j =0 ; j<digit;j++){
             LCD_displayCharacter(arr_num[j]);
         }
     }
}
/*******************************************************************************
 * FUNCTION NAME: LCD_void_Send_FloatNumber
 *
 * DESCRIPTION: Function to display a float number on the LCD module
 *
 * INPUTS: fint64_t Fnumber: The number to be displayed
 *
 *******************************************************************************/
void LCD_void_Send_FLoatNumber(fint64_t Fnumber)
{
    // Check if the number is negative
    if(Fnumber<0){
        LCD_displayCharacter('-'); // Display the negative sign
            Fnumber*=(-1); // Make the number positive
        }
    // Convert the floating-point number to an integer
        SINT32_t intfnumber = (SINT32_t)Fnumber;
        LCD_void_SendNumber(intfnumber); // Send the integer part to the LCD

        // Extract the decimal part of the floating-point number
        SINT32_t decimalp = ((Fnumber - (fint64_t)intfnumber) *100000000);
        // Initialize variables for formatting
        SINT32_t num = decimalp;
        UINT16_t digit = 0,ref_numb =DECIMAL_POINT_ACCURACY , ref_flag=0;
        // Determine the number of digits after the decimal point
        while(num != 0){
            if(num%10 == 0 && !ref_flag){
                ref_numb--;
                decimalp/=10;
            }else{
                ref_flag =1;
                digit++;
            }

            num/=10;
        }
        // Display the decimal point and leading zeros (if any)
        if(decimalp != 0){
            LCD_displayCharacter('.'); // Display the decimal point
            while(digit<ref_numb){
                LCD_displayCharacter('0'); // Display leading zeros
                digit++;
            }
            LCD_void_SendNumber(decimalp); // Display the decimal part
        }
}



