#include "keypad.h"



#if(N_COL == 3)
static unsigned char KeyPad_4x3_adjustKeyNumber(unsigned char button_number);
#elif(N_COL == 4)
static unsigned char KeyPad_4x4_adjustKeyNumber(unsigned char button_number);
#endif

unsigned char KeyPad_getPressedKey(void){
    unsigned char row , col, res = 'n' ;


    for (col = 0 ; col < N_COL ; col++){
        Column_DATA = ~(0b00000001 << col);
//        ROW_DATA = (1<<col); // row is output
        for(row = 0 ; row < N_ROW ; row++){
            while(BIT_IS_CLEAR(ROW_DATA,row)){
#if(N_COL == 3)
               res =  KeyPad_4x3_adjustKeyNumber((row*N_COL)+col+1);
#elif(N_COL == 4)
               res =  KeyPad_4x4_adjustKeyNumber((row*N_COL)+col+1);
#endif


            }
        }

    }
    return res;
}

#if (N_COL == 3)

static unsigned char KeyPad_4x3_adjustKeyNumber(unsigned char button_number)
{
    switch(button_number)
    {
        case 10: return '*'; // ASCII Code of *
                 break;
        case 11: return 0;
                 break;
        case 12: return '#'; // ASCII Code of #
                 break;
        default: return button_number;
    }
}

#elif (N_COL == 4)

static unsigned char KeyPad_4x4_adjustKeyNumber(unsigned char button_number)
{
    unsigned char val = 'n';
    switch(button_number)
        {
            case 1: val = '1';
                    break;
            case 2: val = '2';
                    break;
            case 3: val =  '3';
                    break;
            case 4: val = '+'; // ASCII Code of %
                    break;
            case 5: val =  '4';
                    break;
            case 6: val =  '5';
                    break;
            case 7: val =  '6';
                    break;
            case 8: val = '-'; /* ASCII Code of '*' */
                    break;
            case 9: val =  '7';
                    break;
            case 10: val =  '8';
                    break;
            case 11: val =  '9';
                    break;
            case 12: val = '/'; /* ASCII Code of '-' */
                    break;
            case 13: val =  '*';  /* ASCII of Enter */
                    break;
            case 14: val = '0';
                    break;
            case 15: val = 'r'; /* ASCII Code of '=' */
                    break;
            case 16: val = '='; /* ASCII Code of '+' */
                    break;
            default: return val;
        }
    return val;
}
#endif

void keypad_init()
{
    Column_DIR = 0xFF; //COL 1 IS OUTPUT
    ROW_DIR = 0; // PORTD IN INPUT
    GPIO_PORTE_PUR_R = 0xFF; // PULL UP FOR ROWS SWITCHES
}



