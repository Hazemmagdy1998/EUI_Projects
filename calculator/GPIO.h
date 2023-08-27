#ifndef GPIO_H_
#define GPIO_H_
#include "CPU_Configuration.h"
typedef unsigned char uint8_t;
typedef unsigned long uint32_t;

///*************************PORT A PINS***********************/
//#define PA0 (1U<<0)
//#define PA1 (1U<<1)
//#define PA2 (1U<<2)
//#define PA3 (1U<<3)
//#define PA4 (1U<<4)
//#define PA5 (1U<<5)
//#define PA6 (1U<<6)
//#define PA7 (1U<<7)
//
///*************************PORT B PINS***********************/
//#define PB0 (1U<<0)
//#define PB1 (1U<<1)
//#define PB2 (1U<<2)
//#define PB3 (1U<<3)
//#define PB4 (1U<<4)
//#define PB5 (1U<<5)
//#define PB6 (1U<<6)
//#define PB7 (1U<<7)
///*************************PORT C PINS***********************/
//#define PC0 (1U<<0)
//#define PC1 (1U<<1)
//#define PC2 (1U<<2)
//#define PC3 (1U<<3)
//#define PC4 (1U<<4)
//#define PC5 (1U<<5)
//#define PC6 (1U<<6)
//#define PC7 (1U<<7)
///*************************PORT D PINS***********************/
//#define PD0 (1U<<0)
//#define PD1 (1U<<1)
//#define PD2 (1U<<2)
//#define PD3 (1U<<3)
//#define PD4 (1U<<4)
//#define PD5 (1U<<5)
//#define PD6 (1U<<6)
//#define PD7 (1U<<7)
//
///*************************PORT E PINS***********************/
//#define PE0 (1U<<0)
//#define PE1 (1U<<1)
//#define PE2 (1U<<2)
//#define PE3 (1U<<3)
//#define PE4 (1U<<4)
//#define PE5 (1U<<5)
//#define PE6 (1U<<6)
//#define PE7 (1U<<7)
//
///*************************PORT F PINS***********************/
//#define PF0 (1U<<0)
//#define PF1 (1U<<1)
//#define PF2 (1U<<2)
//#define PF3 (1U<<3)
//#define PF4 (1U<<4)
//#define PF5 (1U<<5)
//#define PF6 (1U<<6)
//#define PF7 (1U<<7)





typedef enum {
    PORTA,PORTB,PORTC,PORTD,PORTE,PORTF
}PORT_NAME;

typedef enum {
    input,output
}PIN_DIRECTION;


typedef enum {
    set,clear
}PIN_VALUE;

typedef enum {
    GPIO,ALTERNATIVE_FN
}OPERATION_MODE;

typedef enum {
    ma_2,ma_4,ma_8
}CUREENT;


typedef enum {
   pull_up,pull_down,open_drain
}PIN_TYPE;





 void GPIO_Init (uint8_t PORT_NUM);
 void Set_PortPin_Direction (PORT_NAME port_name ,  PIN_DIRECTION pin_type , uint8_t pin_num );
 void Set_Port_Direction (PORT_NAME port_name, uint8_t pin_num);
 void GPIO_WritePin (PORT_NAME port_name , uint8_t pin_num , PIN_VALUE pin_state);
 void GPIO_WritePort (PORT_NAME port_name , uint8_t data);
 uint8_t GPIO_GetBit (PORT_NAME port_name , uint8_t pin_num);
 void GPIO_WriteBit_Banding(PORT_NAME port_name ,uint8_t index , PIN_VALUE pin_value);
 void GPIO_Interrupt_Enable (PORT_NAME port_name , uint8_t pin_num);
 void GPIO_NVIC_EN0_Enable (PORT_NAME port_name);
 void GPIO_MODE_OF_OPERATION ( PORT_NAME port_name , OPERATION_MODE mode , uint8_t pin_num);
 void GPIO_CURRENT_OF_PIN ( PORT_NAME port_name , CUREENT mode , uint8_t pin_num);
 void GPIO_PULL_UP_DOWN_OPENDRAIN ( PORT_NAME port_name , PIN_TYPE mode , uint8_t pin_num);







#endif /* GPIO_H_ */
