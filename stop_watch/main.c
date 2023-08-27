#include "GPIO.h"
#include "systick.h"
#include "lcd.h"



extern unsigned char sec;
extern unsigned char min;

extern unsigned char digit1;
extern unsigned char digit2;
extern unsigned char digit3;
extern unsigned char digit4;



state number_of_state = start;


int main(void)
{

    GPIO_Init(PORTA);//initialize PORTA (LCD CONTROL PINS)
    GPIO_Init(PORTB);//initialize PORTB (LCD DATA PINS)
    GPIO_Init(PORTF);// initialize PORTF (ENABLE SWITCH 0 AND 4)
    Set_PortPin_Direction(PORTF,input,0); //PUT PIN0 IN PORTF AS INPUT
    Set_PortPin_Direction(PORTF,input,4);//PUT PIN4 IN PORTF AS INPUT
    GPIO_PULL_UP_DOWN_OPENDRAIN(PORTF,pull_up,0);//SET THE INTERNAL PULL UP RESISTANCE FOR PIN0
    GPIO_PULL_UP_DOWN_OPENDRAIN(PORTF,pull_up,4);//SET THE INTERNAL PULL UP RESISTANCE FOR PIN4
    LCD_init();//INITIALIZE THE LCD
    LCD_goToRowColumn(0,3);
    LCD_displayString("stop watch");
    delay(2000);
    LCD_goToRowColumn(1,2);
    LCD_displayString("Hazem & Omar");
    delay(3000);
    LCD_clearScreen();//CLEAR THE SCREEN AT FIRST OF PROGRAM
    Systick_Count_Sec_Init();//INTITIALZE THE SYSTICK TIMER



/*ACCORDING TO THE STATE WE WILL CHOOSE THE MODE OF STATE (START,STOP,lap,RESET)*/
    while(1){
        switch(number_of_state){
        case start :
          // if(BIT_IS_CLEAR(GPIO_PORTF_DATA_R,0)){
                NVIC_ST_CTRL_R = 0x00000003;//ENABLING THE SYSTICK TIMER
                if(BIT_IS_CLEAR(GPIO_PORTF_DATA_R,0)){//IF SWITCH 0 IS PRESSED THE STATE WILL BE CHANGED TO STOP INSTEAD OF START STATE
                    delay(170);
                    number_of_state = stop;//STATE NOW IS STOP STATE
                }
                else if (BIT_IS_CLEAR(GPIO_PORTF_DATA_R,4)){//IF SWITCH 4 IS PRESSED THE STATE WILL BE CHANGED TO LAP INSTEAD OF START STATE
                    delay(100);
                    number_of_state = lap;//STATE NOW IS LAP STATE
                }
         // }
            break;
        case stop :
            NVIC_ST_CTRL_R = 0x00000000;//STOP THE SYSTICK TIMER
            if(BIT_IS_CLEAR(GPIO_PORTF_DATA_R,0)){ //IF SWITCH 0 IS PRESSED IT WILL RESUME THE PROGRAM AGAIN BY CHANGING THE STATE FROM STOP TO START
                delay(100);
                number_of_state = start;//STATE NOW IS START STATE
            }
            else if (BIT_IS_CLEAR(GPIO_PORTF_DATA_R,4)){//IF SWITCH 4 IS PRESSED IT WILL RESET THE PROGRAM AGAIN BY CHANGING THE STATE FROM STOP TO RESET
                 delay(100);
                number_of_state = reset;
            }
            break;
        case lap :
            LCD_goToRowColumn(1,9);
            LCD_void_SendNumber(digit1);//SHOW THE DIGIT ONE OF SECONDS
            LCD_goToRowColumn(1,8);
            LCD_void_SendNumber(digit2);//SHOW THE DIGIT TWO OF SECONDS
            LCD_goToRowColumn(1,6);
            LCD_void_SendNumber(digit3);//SHOW THE DIGIT ONE OF MINUTES
            LCD_goToRowColumn(1,5);
            LCD_void_SendNumber(digit4);//SHOW THE DIGIT TWO OF SECONDS
            number_of_state = start; // RESUME THE PROGRAM AGAIN
         while(BIT_IS_CLEAR(GPIO_PORTF_DATA_R,0)){//IF THE SWITCH 0 IS PRESSED IT WILL STOP THE PROGRAM
             delay(100);
             number_of_state = stop;

         }
            break;
        case reset :
            sec = 0 ;
            min = 0;
            digit1 = 0;
            digit2 = 0;
            digit3 = 0;
            digit4 = 0;
            LCD_goToRowColumn(0,9);
            LCD_void_SendNumber(digit1);
            LCD_goToRowColumn(0,8);
            LCD_void_SendNumber(digit2);
            LCD_goToRowColumn(0,6);
            LCD_void_SendNumber(digit3);
            LCD_goToRowColumn(0,5);
            LCD_void_SendNumber(digit4);
            NVIC_ST_CTRL_R = 0x00000000; // STOP THE SYSTICK TIMER TO RESET IT
            while(BIT_IS_CLEAR(GPIO_PORTF_DATA_R,0)){// IF SWITCH 0 IS PRESSED IT WILL START THE PROGRAM AGAIN AFTER THE RESET
                delay(100);
                number_of_state = start;//STATE NOW IS START
            }
            break;
        default :
            number_of_state = start;
            break;
        }


    }
	return 0;
}


