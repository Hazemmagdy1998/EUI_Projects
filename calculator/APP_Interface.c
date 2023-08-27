#include "APP_Private.h"

UINT8_t input_arr[15];
UINT32_t input_counter=0;
fint64_t numbers_arr_arr[15];
UINT8_t operations_arr[15];
UINT32_t numbers_arr_counter = 0;
UINT32_t operations_arr_counter = 0;
fint64_t number = 0;

UINT8_t error_flag =0;

/*============================================================================================================================================
Function name: calculator

Description: This function performs the operation of a regular calculator with priority handling.
============================================================================================================================================*/
fint64_t calculator(){
    fint64_t total=0;
    error_flag =0;
    int j;
    // Iterate through the operations array and perform calculations
    for( j =0 ; j< operations_arr_counter;j++){
        if((operations_arr[j]=='*')){
            numbers_arr_arr[j+1]*=numbers_arr_arr[j];
            numbers_arr_arr[j]=0;
        }else{
            if((operations_arr[j]=='/')){
                if(numbers_arr_arr[j+1]==0)
                {
                    error_handle();
                    error_flag = 1;
                    break;
                }
                numbers_arr_arr[j+1]=numbers_arr_arr[j]/numbers_arr_arr[j+1];
                numbers_arr_arr[j]=0;
            }
        }
        total+=numbers_arr_arr[j];
    }
    // Add the remaining operand to the total
    total+=numbers_arr_arr[numbers_arr_counter-1];
    return total;
}
/*============================================================================================================================================
Function name: calculator_sort

Description: This function collects the array input from the user and splits it into two arrays one for operators and one for the operands.
============================================================================================================================================*/
int calculator_sort(){
    int arr_size= sizeof(input_arr)/sizeof(input_arr[0]);
    int i,neg_flag=0,neg_counter=0,counterr=1,error_falg=0;
    for(i = 0 ; i < arr_size ; i++){
        if((is_operator(input_arr[arr_size-1])) || (input_arr[0]=='*') || (input_arr[0]=='/')){
            error_handle();
            error_falg =1;
            break;
        }
        if(input_arr[i]=='\0'){
            break;
        }
        counterr=1;
        if(is_operator(input_arr[i])){
            neg_flag=0;
            if((input_arr[i] =='-') || (input_arr[i] == '+')){
                if((input_arr[i] =='-')){
                    neg_counter++;
                }
                while((input_arr[i+counterr] == '-') || (input_arr[i+counterr] == '+')){
                    if((input_arr[i+counterr] == '-')){
                        neg_counter++;
                    }
                    counterr++;
                }
                if(is_number(input_arr[i+counterr])){
                    if(neg_counter%2 != 0){
                        neg_flag=1;
                        neg_counter=0;
                    }else{
                        neg_flag=0;
                    }
                    if(i!=0){
                        if((input_arr[i-1] != '*') && (input_arr[i-1] != '/') && (is_number(input_arr[i-1]))){
                            operations_arr[operations_arr_counter]='+';
                            operations_arr_counter++;
                        }
                    }
                    i+=(counterr-1);
                    counterr=1;
                }else{
                    error_handle();
                    error_falg =1;
                    break;
                }
            }
            if((input_arr[i]=='*') || (input_arr[i] == '/')){
                operations_arr[operations_arr_counter]=input_arr[i];
                operations_arr_counter++;
            }
        }else{
            counterr =0;
            do{
                number *= 10;
                number += input_arr[i+counterr]-48;
                counterr++;
            }while(is_number(input_arr[i+counterr]));
            if(neg_flag){
                number*=(-1);
            }
            numbers_arr_arr[numbers_arr_counter]=number;
            numbers_arr_counter++;
            number =0;
            i+=(counterr-1);

        }
    }
    // Check if the number of operators is greater than or equal to the number of operands
    if(operations_arr_counter>=numbers_arr_counter){
        error_handle();
        error_falg =1;
    }
    return !error_falg;
}
/*============================================================================================================================================
Function name: keypad_input

Description: This function returns the value entered on the keypad.
============================================================================================================================================*/
void keypad_input(){
    UINT8_t key = KeyPad_getPressedKey();
    while(key != '='&& key != 'r'){
        key = KeyPad_getPressedKey();
        if(input_counter < 15){
            if(key != 'n' && key!='r'){
                if(key != '='){
                    LCD_displayCharacter(key);
                    input_arr[input_counter]=key;
                    input_counter++;
                }
            }
        }else{

            break;
        }
    }
    if(key!='r'){
        if(calculator_sort()){
            fint64_t num = calculator();
            if(error_flag ==0)
            {
                LCD_goToRowColumn(1,0);
                LCD_displayString("ANS = ");
               LCD_void_Send_FLoatNumber(num);
            }
            else{ // Handle error}

        }
    }
    while(key != 'r'){
        key=KeyPad_getPressedKey();
    }
    resett(); // Reset variables
}
}
/*============================================================================================================================================
Function name: error_handle

Description: This function displays an error message.
============================================================================================================================================*/
void error_handle(){
    LCD_clearScreen();
    LCD_displayString("ERROR!");
    operations_arr_counter=0;
    numbers_arr_counter=0;
}
/*=====================================================================================================
Function name: is_operator

Description: This function checks if a character is an operator (+, -, *, /).
=====================================================================================================*/
char is_operator(char input_operator){
    char operator[]={'+','-','*','/'};
    int counter;
    char found = 0;
    for(counter = 0 ; counter < 4 ; ++counter){
        if(operator[counter] == input_operator){
            found = 1;
            break;
        }
    }
    return found;
}
/*=====================================================================================================
Function name: is_number

Description: This function checks if a character is a digit (0-9).
=====================================================================================================*/
char is_number(char input_number){
    char found = 0;
    int counter;
    char numbers[]={'1','2','3','4','5','6','7','8','9','0'};
    for(counter = 0 ; counter < 10 ; ++counter){
        if(numbers[counter] == input_number){
            found = 1;
            break;
        }
    }
    return found;
}
void initializations(){
    GPIO_Init(PORTA);
    GPIO_Init(PORTB);
    GPIO_Init(PORTF);
    GPIO_Init(PORTE);
    keypad_init();
    LCD_init();
    LCD_displayString("Omar Ayman");
    LCD_goToRowColumn(1,0);
    LCD_displayString("1045");
    Delay_in_ms(3500);
    LCD_clearScreen();
    LCD_displayString("Hazem Magdy");
    LCD_goToRowColumn(1,0);
    LCD_displayString("1004");
    Delay_in_ms(3500);
    LCD_clearScreen();

}
void resett(){
LCD_clearScreen();
int i;
for(i =0 ;i<15;i++){
input_arr[i]=0;
numbers_arr_arr[i]=0;
operations_arr[i]=0;
}
 input_counter=0;
 numbers_arr_counter = 0;
 operations_arr_counter = 0;
 number = 0;
}

