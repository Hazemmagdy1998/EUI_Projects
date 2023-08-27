 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Hazem Magdy
 *
 *******************************************************************************/

#include "lcd.h"
#include "GPIO.h"




/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*******************************************************************************
 *FUNCTION NAME : DELAY
 *
 *INPUTS : UNSIGNED LONG NUMBER
 *
 *DESCRIPTION : FUNCTION TO MAKE A SOFTWARE DELAY IN MS
 *******************************************************************************/

void delay(uint32_t num){
    int i ;
    for(i = 0 ; i < 762 * num ; i++);
}


/*******************************************************************************
 *FUNCTION NAME : INIT
 *
 *DESCRIPTION : FUNCTION TO INITIALIZE THE LCD_MODULE
 *******************************************************************************/


void LCD_init(void){
    LCD_CTRL_PORT_DIR |= PA5 | PA6 | PA7 ; // CONFIGURE THE E , RS AND RW AS OUTPUT PINS

#if(DATA_BITS_MODE == 4)
#ifdef UPPER_BITS
    LCD_DATA_PORT_DIR |=  0xF0; // Configure upper bits for 4-bit mode
#else
    LCD_DATA_PORT_DIR |=  0x0F; // Configure lower bits for 4-bit mode
#endif
    LCD_sendCommand(FOUR_BITS_DATA_MODE); // Set 4-bit data mode
    LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE); // Set 2-line display mode
#elif (DATA_BITS_MODE == 8)
    LCD_DATA_PORT_DIR =  0xFF; // Configure all 8 bits for 8-bit mode
//    LCD_sendCommand(0xC0);
    LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); // Set 2-line display mode
#endif
    LCD_sendCommand(CURSOR_OFF); // Turn off cursor
    LCD_sendCommand(CLEAR_COMMAND); // Clear the LCD screen

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
    CLR_BIT(LCD_CTRL_PORT,RS); // Set RS (Register Select) pin to LOW for command mode
    CLR_BIT(LCD_CTRL_PORT,RW); // Set RW (Read/Write) pin to LOW for write mode
    delay(1);
    SET_BIT(LCD_CTRL_PORT,E); // Set E (Enable) pin to HIGH
    delay(1);
#if(DATA_BITS_MODE == 4)
#ifdef UPPER_BITS // SENDING UPPER BITS
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0xF0)); // Send upper bits of the command
#else
    LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command & 0xF0) >> 4); // Send lower bits of the command
#endif
    delay(1);
    CLR_BIT(LCD_CTRL_PORT,E); // Clear the enable bit PA7
    delay(1);
    SET_BIT(LCD_CTRL_PORT,E); // set the enable bit PA7
    delay(1);
#ifdef UPPER_BITS
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4); // Send lower bits of the command
#else
    LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (command & 0x0F); Send lower bits of the command
#endif
    delay(1);
    CLR_BIT(LCD_CTRL_PORT,7); // Clear the enable bit PA7
    delay(1);
#elif (DATA_BITS_MODE == 8)
    LCD_DATA_PORT = command; // Send the command
    delay(1);
    CLR_BIT(LCD_CTRL_PORT,E); // Clear the enable bit PA7
    delay(1);
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
    SET_BIT(LCD_CTRL_PORT,RS); // Set RS (Register Select) pin to HIGH for data mode
    CLR_BIT(LCD_CTRL_PORT,RW); // Set RW (Read/Write) pin to LOW for write mode
    delay(1);
    SET_BIT(LCD_CTRL_PORT,E);  // Set E (Enable) pin to HIGH
    delay(1);
#if(DATA_BITS_MODE == 4)
#ifdef UPPER_BITS
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0xF0));// Send upper bits of the character
#else
    LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((data & 0xF0) >> 4);// Send lower bits of the character
#endif
    delay(1);
    CLR_BIT(LCD_CTRL_PORT,E); // Clear the enable bit PA7
    delay(1);
    SET_BIT(LCD_CTRL_PORT,E); // SET the enable bit PA7
#ifdef UPPER_BITS // SENDING LOWER BITS
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0x0F) << 4); // Send lower bits of the character
#else
    LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (data & 0x0F); // Send lower bits of the character
#endif
    delay(1);
     CLR_BIT(LCD_CTRL_PORT,E);// Clear the enable bit PA7
     delay(1);
#elif (DATA_BITS_MODE == 8)
    LCD_DATA_PORT = data; // Send the character
    delay(1);
    CLR_BIT(LCD_CTRL_PORT,E); // Clear the enable bit PA7
    delay(1);
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
    // Calculate the address based on row and column
    switch (row){
    case 0 :
        address = col ;
        break;
    case 1 :
        address = col + 0x40;
        break;
    case 2 :
        address = col + 0x10;
        break ;
    case 3 :
        address = col + 0x50;
        break;
    }
    LCD_sendCommand(address | SET_CURSOR_LOCATION); // Set the cursor address


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

void LCD_void_SendNumber(sint32_t Copy_s32Number)
{
    uint8_t Local_u8String[20];
    char Local_u8NumLength=0,Local_u8Rem,Local_u8Counter;
    long Local_u32Num=Copy_s32Number;
    if(Copy_s32Number==0)
    {
        Local_u8String[0]='0';
        Local_u8String[1]='\0';
    }
    else
    {
        if(Copy_s32Number<0)
        {
            LCD_displayCharacter('-');
            Copy_s32Number*=-1;
        }
        // Calculate the number of digits in the number
        while(Local_u32Num!=0)
        {
            Local_u8NumLength++;
            Local_u32Num/=10;
        }
        // Convert each digit to a character and display it on the LCD
        for(Local_u8Counter=0;Local_u8Counter<Local_u8NumLength;Local_u8Counter++)
        {
            Local_u8Rem=Copy_s32Number%10;
            Copy_s32Number/=10;
            Local_u8String[Local_u8NumLength-(Local_u8Counter+1)]=Local_u8Rem+'0';
        }
        Local_u8String[Local_u8NumLength]='\0';
    }

    LCD_displayString(Local_u8String);
}



