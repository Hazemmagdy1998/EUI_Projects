 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: GPIO.h
 *
 * Description: Header file for the GPIO driver
 *
 * Author: Hazem Magdy
 *
 *******************************************************************************/
#ifndef GPIO_H_
#define GPIO_H_

#include "common_macros.h"
#include "std_types.h"
#include "hw_gpio.h"



// GPIO port names
typedef enum {
    PORTA,PORTB,PORTC,PORTD,PORTE,PORTF
}PORT_NAME;

// Pin direction (input or output)
typedef enum {
    input,output
}PIN_DIRECTION;

// Pin value (set or clear)

typedef enum {
    set,clear
}PIN_VALUE;

// Operation mode (GPIO or alternative function)
typedef enum {
    GPIO,ALTERNATIVE_FN
}OPERATION_MODE;

// Current strength (2mA, 4mA, 8mA)

typedef enum {
    ma_2,ma_4,ma_8
}CUREENT;

// Pin type (pull-up, pull-down, open-drain)

typedef enum {
   pull_up,pull_down,open_drain
}PIN_TYPE;



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

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
