#include "systick.h"
#include "lcd.h"


uint8_t sec = 0; // overall seconds
uint8_t min = 0; // overall minutes
uint8_t digit1 = 0; //showing the first digit
uint8_t digit2 = 0;//showing the second digit
uint8_t digit3 = 0;//showing the third digit
uint8_t digit4 = 0;//showing the forth digit


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


/*******************************************************************************
 *FUNCTION NAME : Systick_Count_Sec_Init
 *
 *DESCRIPTION : FUNCTION TO initialize the systick timer to count one second
 *******************************************************************************/


void Systick_Count_Sec_Init (void){
    NVIC_ST_CTRL_R = 0x00000000; // make sure that systick timer disabled at first
    NVIC_ST_RELOAD_R |= SEC_COUNT_VAR - 1; // load the value to count 1 second
    NVIC_ST_CURRENT_R = 0 ;
    NVIC_ST_CTRL_R |= 0x00000001; // disabling interrupt at first until get the switch pressed
}


/*******************************************************************************
 *FUNCTION NAME : Systick_Handler
 *
 *DESCRIPTION : FUNCTION executed when an interrupt occurred by systick timer
 *******************************************************************************/

void Systick_Handler(void){
    LCD_goToRowColumn(0,9);
    LCD_void_SendNumber(digit1); // showing the first digit at first it equals zero
    LCD_goToRowColumn(0,8);
    LCD_void_SendNumber(digit2);// showing the second digit at first it equals zero
    LCD_goToRowColumn(0,6);
    LCD_void_SendNumber(digit3);// showing the third digit at first it equals zero
    LCD_goToRowColumn(0,5);
    LCD_void_SendNumber(digit4);// showing the forth digit at first it equals zero
    sec++; // incrementing the overall seconds to get digits of seconds from it
    LCD_goToRowColumn(0,9);
    digit1 = sec % 10 ; // get the first digit of seconds
    LCD_void_SendNumber(digit1); // showing the first digit of seconds
    LCD_goToRowColumn(0,8);
    digit2 = sec / 10 ; // get the second digit of seconds
    LCD_void_SendNumber(digit2);// showing the first digit of seconds
    if(sec == 60){ // if the overall seconds reaches 60 it will be zero again and increment the overall minutes
        sec = 0 ;
        digit1=0;//make the first digit of seconds with zero to start again
        digit2=0;//make the second digit of seconds with zero to start again
        LCD_goToRowColumn(0,9);
        LCD_void_SendNumber(digit1);
        LCD_goToRowColumn(0,8);
        LCD_void_SendNumber(digit2);
        min++;// incrementing the overall minutes to get digits of minutes from it
        LCD_goToRowColumn(0,6);
        digit3 = min % 10 ; // get the first digit of minutes
        LCD_void_SendNumber(digit3);
        LCD_goToRowColumn(0,5);
        digit4 = min / 10 ;// get the second digit of seconds
        LCD_void_SendNumber(digit4);
    }
    NVIC_ST_CURRENT_R = 0 ; // clearing the interrupt flag
}
