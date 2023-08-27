 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: GPIO.c
 *
 * Description: Source file for the GPIO driver
 *
 * Author: Hazem Magdy
 *
 *******************************************************************************/
#include "GPIO.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*******************************************************************************
 *FUNCTION NAME : GPIO_Init
 *
 *INPUTS : ENUM OF PORT NAME
 *
 *DESCRIPTION : INITIALIZE GPIO MODULE
 *******************************************************************************/

void GPIO_Init (PORT_NAME PORT_NUM){

    switch(PORT_NUM){
    case PORTA :
        SYSCTL_RCGCGPIO_R |= 0x00000001; // ENABLE SYSTEM CLOCK FOR PORTA
        while(SYSCTL_RCGCGPIO_R & 0x00000001 == 0 ){}
        GPIO_PORTA_LOCK_R = 0x4C4F434B;
        GPIO_PORTA_CR_R = 0xFF;
        GPIO_PORTA_DEN_R = 0xFF;// ENABLE DIGITAL ENABLE FOR PORTA


        break ;
    case PORTB :
        SYSCTL_RCGCGPIO_R |= 0x00000002;// ENABLE SYSTEM CLOCK FOR PORTB
        while(SYSCTL_RCGCGPIO_R & 0x00000002 == 0 ){}
        GPIO_PORTB_LOCK_R = 0x4C4F434B;
        GPIO_PORTB_CR_R = 0xFF;
        GPIO_PORTB_DEN_R = 0xFF;// ENABLE DIGITAL ENABLE FOR PORTB
        break ;
    case PORTC :
        SYSCTL_RCGCGPIO_R |= 0x00000004;// ENABLE SYSTEM CLOCK FOR PORTC
        while(SYSCTL_RCGCGPIO_R & 0x00000004 == 0 ){}
        GPIO_PORTC_LOCK_R = 0x4C4F434B;
        GPIO_PORTC_CR_R = 0xFF;
        GPIO_PORTC_DEN_R = 0xFF;// ENABLE DIGITAL ENABLE FOR PORTC
        break ;
    case PORTD :
        SYSCTL_RCGCGPIO_R |= 0x00000008;// ENABLE SYSTEM CLOCK FOR PORTD
        while(SYSCTL_RCGCGPIO_R & 0x00000008 == 0 ){}
        GPIO_PORTD_LOCK_R = 0x4C4F434B;
        GPIO_PORTD_CR_R = 0xFF;
        GPIO_PORTD_DEN_R = 0xFF;// ENABLE DIGITAL ENABLE FOR PORTD
        break;
    case PORTE :
        SYSCTL_RCGCGPIO_R |= 0x00000010;// ENABLE SYSTEM CLOCK FOR PORTE
        while(SYSCTL_RCGCGPIO_R & 0x00000010 == 0 ){}
        GPIO_PORTE_LOCK_R = 0x4C4F434B;
        GPIO_PORTE_CR_R = 0x3F;
        GPIO_PORTE_DEN_R = 0x3F;// ENABLE DIGITAL ENABLE FOR PORTE
        break ;
    case PORTF :

        SYSCTL_RCGCGPIO_R |= 0x00000020;// ENABLE SYSTEM CLOCK FOR PORTF
        while(SYSCTL_RCGCGPIO_R & 0x00000020 == 0 ){}
        GPIO_PORTF_LOCK_R = 0x4C4F434B;
        GPIO_PORTF_CR_R = 0x1F;
        GPIO_PORTF_DEN_R = 0x1F;// ENABLE DIGITAL ENABLE FOR PORTF
        break ;

    }


}
/*******************************************************************************
 *FUNCTION NAME : Set_PortPin_Direction
 *
 *INPUTS : ENUM OF PORT NAME , ENUM TO DETECT PIN IS OUTPUT OR INPUT AND THE PIN NUMBER
 *
 *DESCRIPTION : SETTING THE DIRECTION (OUTPUT OR INPUT) FOR PINS IN REQUIRED PORT
 *******************************************************************************/


void Set_PortPin_Direction (PORT_NAME port_name ,  PIN_DIRECTION pin_type , uint8_t pin_num ){
    switch(port_name){
    case PORTA :
        if(pin_type == input){
            CLR_BIT(GPIO_PORTA_DIR_R,pin_num); // PIN IS INPUT
        }
        else if (pin_type == output){
            SET_BIT(GPIO_PORTA_DIR_R,pin_num); // PIN IS OUTPUT
        }
        break;
    case PORTB :
        if(pin_type == input){
            CLR_BIT(GPIO_PORTB_DIR_R,pin_num);// PIN IS INPUT
        }
        else if (pin_type == output){
            SET_BIT(GPIO_PORTB_DIR_R,pin_num);// PIN IS OUTPUT
        }
        break ;
    case PORTC :
        if(pin_type == input){
            CLR_BIT(GPIO_PORTC_DIR_R,pin_num);// PIN IS INPUT
        }
        else if (pin_type == output){
            SET_BIT(GPIO_PORTC_DIR_R,pin_num);// PIN IS OUTPUT
        }
        break;
    case PORTD :
        if(pin_type == input){
            CLR_BIT(GPIO_PORTD_DIR_R,pin_num);// PIN IS INPUT
        }
        else if (pin_type == output){
            SET_BIT(GPIO_PORTD_DIR_R,pin_num);// PIN IS OUTPUT
        }
        break;
    case PORTE :
        if(pin_type == input){
            CLR_BIT(GPIO_PORTE_DIR_R,pin_num);// PIN IS INPUT
        }
        else if (pin_type == output){
            SET_BIT(GPIO_PORTE_DIR_R,pin_num);// PIN IS OUTPUT
        }
        break ;
    case PORTF :
        if(pin_type == input){
            CLR_BIT(GPIO_PORTF_DIR_R,pin_num);// PIN IS INPUT
        }
        else if (pin_type == output){
            SET_BIT(GPIO_PORTF_DIR_R,pin_num);// PIN IS OUTPUT
        }
        break ;
    }
}

/*******************************************************************************
 *FUNCTION NAME : Set_Port_Direction
 *
 *INPUTS : ENUM OF PORT NAME AND THE PORT VALUE
 *
 *DESCRIPTION : SETTING THE DIRECTION (OUTPUT OR INPUT) FOR THE WHOLE REQUIRED PORT
 *******************************************************************************/
void Set_Port_Direction (PORT_NAME port_name, uint8_t port_value){
    switch (port_name){
    case PORTA :
        GPIO_PORTA_DIR_R = port_value;
        break;
    case PORTB :
        GPIO_PORTB_DIR_R = port_value;
        break;
    case PORTC :
        GPIO_PORTC_DIR_R = port_value;
        break;
    case PORTD :
        GPIO_PORTD_DIR_R = port_value;
        break ;
    case PORTE :
        GPIO_PORTE_DIR_R = port_value;
        break;
    case PORTF :
        GPIO_PORTF_DIR_R = port_value;
        break;
    }
}


/*******************************************************************************
 *FUNCTION NAME : GPIO_WritePin
 *
 *INPUTS : ENUM OF PORT NAME ,PIN NUM AND THE PIN STATE (SET OR CLEAR)
 *
 *DESCRIPTION : SETTING OR CLEARING PIN IN A PORT
 *******************************************************************************/


void GPIO_WritePin (PORT_NAME port_name , uint8_t pin_num , PIN_VALUE pin_state){

    switch (port_name){
    case PORTA :
        if(pin_state == set){//PIN IS SET
            SET_BIT(GPIO_PORTA_DATA_R,pin_num);
        }
        else if(pin_state == clear){//PIN IS CLEARED
            CLR_BIT(GPIO_PORTA_DATA_R,pin_num);
        }
        break;
    case PORTB :
        if(pin_state == set){
            SET_BIT(GPIO_PORTB_DATA_R,pin_num);//PIN IS SET
        }
        else if(pin_state == clear){
            CLR_BIT(GPIO_PORTB_DATA_R,pin_num);//PIN IS CLEARED
        }
        break;
    case PORTC :
        if(pin_state == set){
            SET_BIT(GPIO_PORTC_DATA_R,pin_num);//PIN IS SET
        }
        else if(pin_state == clear){
            CLR_BIT(GPIO_PORTC_DATA_R,pin_num);//PIN IS CLEARED
        }
        break;
    case PORTD :
        if(pin_state == set){
            SET_BIT(GPIO_PORTD_DATA_R,pin_num);//PIN IS SET
        }
        else if(pin_state == clear){
            CLR_BIT(GPIO_PORTD_DATA_R,pin_num);//PIN IS CLEARED
        }
        break ;
    case PORTE :
        if(pin_state == set){
            SET_BIT(GPIO_PORTE_DATA_R,pin_num);//PIN IS SET
        }
        else if(pin_state == clear){
            CLR_BIT(GPIO_PORTE_DATA_R,pin_num);//PIN IS CLEARED
        }
        break ;
    case PORTF :
        if(pin_state == set){
            SET_BIT(GPIO_PORTF_DATA_R,pin_num);//PIN IS SET
        }
        else if(pin_state == clear){
            CLR_BIT(GPIO_PORTF_DATA_R,pin_num);//PIN IS CLEARED
        }
        break ;
    }
}

/*******************************************************************************
 *FUNCTION NAME : GPIO_WritePort
 *
 *INPUTS : ENUM OF PORT NAME , AND THE DATA WRITTEN IN THE PORT
 *
 *DESCRIPTION : WRITTING DATA IN REQUIRED PORT
 *******************************************************************************/

void GPIO_WritePort (PORT_NAME port_name , uint8_t data){
    switch (port_name){
    case PORTA :
        GPIO_PORTA_DATA_R = data;
        break;
    case PORTB :
        GPIO_PORTB_DATA_R = data;
        break;
    case PORTC :
        GPIO_PORTC_DATA_R = data;
        break;
    case PORTD :
        GPIO_PORTD_DATA_R = data;
        break ;
    case PORTE :
        GPIO_PORTE_DATA_R = data;
        break ;
    case PORTF :
        GPIO_PORTF_DATA_R = data;
        break;
    }

}


/*******************************************************************************
 *FUNCTION NAME : GPIO_GetBit
 *
 *INPUTS : ENUM OF PORT NAME , AND PIN NUM
 *
 *OUTPUT : UINT8_T
 *
 *DESCRIPTION : READ A PIN FROM PORT
 *******************************************************************************/

uint8_t GPIO_GetBit (PORT_NAME port_name , uint8_t pin_num){
    uint8_t returned_bit ;
    switch (port_name){
    case PORTA :
        returned_bit = GET_BIT(GPIO_PORTA_DATA_R,pin_num);
        break ;
    case PORTB :
        returned_bit = GET_BIT(GPIO_PORTB_DATA_R,pin_num);
        break ;
    case PORTC :
        returned_bit = GET_BIT(GPIO_PORTC_DATA_R,pin_num);
        break ;
    case PORTD :
        returned_bit = GET_BIT(GPIO_PORTD_DATA_R,pin_num);
        break ;
    case PORTE :
        returned_bit = GET_BIT(GPIO_PORTE_DATA_R,pin_num);
        break ;
    case PORTF :
        returned_bit = GET_BIT(GPIO_PORTF_DATA_R,pin_num);
        break ;
    }
    return returned_bit;

}

/*******************************************************************************
 *FUNCTION NAME : GPIO_WriteBit_Banding
 *
 *INPUTS : ENUM OF PORT NAME , UINT8_T FOR INDEX AND THE PIN VALUE
 *
 *DESCRIPTION : WRITING A VALUE IN SPECIFIC PIN WITH BIT BANDING METHOD
 *******************************************************************************/

void GPIO_WriteBit_Banding(PORT_NAME port_name , uint8_t index , PIN_VALUE pin_value){
    switch(port_name){
    case PORTA :
        if (pin_value == set){
        GPIO_PORTA_DATA_BITS_R [index] = 0xFF  ;  //it will just access the required location not all pins
        }
        else if (pin_value == clear){
            GPIO_PORTA_DATA_BITS_R [index] = 0  ;
        }
        break;
    case PORTB :
        if (pin_value == set){
            GPIO_PORTB_DATA_BITS_R [index] = 0xFF ;
        }
        else if (pin_value == clear){
            GPIO_PORTB_DATA_BITS_R [index] = 0 ;
        }
        break ;
    case PORTC :
        if (pin_value == set){
            GPIO_PORTC_DATA_BITS_R [index] = 0xFF ;
        }
        else if (pin_value == clear){
            GPIO_PORTC_DATA_BITS_R [index] = 0 ;
        }
        break ;
    case PORTD :
        if (pin_value == set){
            GPIO_PORTD_DATA_BITS_R [index] = 0xFF ;
        }
        else if (pin_value == clear){
            GPIO_PORTD_DATA_BITS_R [index] = 0 ;
        }
        break ;
    case PORTE :
        if (pin_value == set){
            GPIO_PORTE_DATA_BITS_R [index] = 0xFF ;
        }
        else if (pin_value == clear){
            GPIO_PORTE_DATA_BITS_R [index] = 0 ;
        }

        break ;
    case PORTF :
        if (pin_value == set){
            GPIO_PORTF_DATA_BITS_R [index] = 0xFF ;
        }
        else if (pin_value == clear){
            GPIO_PORTF_DATA_BITS_R [index] = 0 ;
        }
        break;

    }
}


/*******************************************************************************
 *FUNCTION NAME : GPIO_Interrupt_Enable
 *
 *INPUTS : ENUM OF PORT NAME AND PIN_NUM
 *
 *DESCRIPTION : ENABLING INTERRUPT ON CERTAIN PIN
 *******************************************************************************/


void GPIO_Interrupt_Enable (PORT_NAME port_name , uint8_t pin_num){
//    GPIO_PORTF_IM_R = 0;
    switch (port_name){
    case PORTA :
//        GPIO_PORTA_IM_R = 0; // clearing IME in the beginning
        GPIO_PORTA_IS_R = 0; // edge senstive
        GPIO_PORTA_IBE_R = 0 ;
        GPIO_PORTA_IEV_R = 0; // falling edge to generate interrupt
        GPIO_PORTA_RIS_R = 0; // clearing GPIORIS
        GPIO_PORTA_IM_R |=  (1 << pin_num);
        break;
    case PORTB :
//        GPIO_PORTB_IM_R = 0; // clearing IME in the beginning
        GPIO_PORTB_IS_R = 0; // edge senstive
        GPIO_PORTB_IBE_R = 0 ;
        GPIO_PORTB_IEV_R = 0; // falling edge to generate interrupt
        GPIO_PORTB_RIS_R = 0; // clearing GPIORIS
        GPIO_PORTB_IM_R |= (1 << pin_num);
        break;
    case PORTC :
//        GPIO_PORTC_IM_R = 0; // clearing IME in the beginning
        GPIO_PORTC_IS_R = 0; // edge senstive
        GPIO_PORTC_IBE_R = 0 ;
        GPIO_PORTC_IEV_R = 0; // falling edge to generate interrupt
        GPIO_PORTC_RIS_R = 0; // clearing GPIORIS
        GPIO_PORTC_IM_R |= (1 << pin_num);
        break;
    case PORTD :
//        GPIO_PORTD_IM_R = 0; // clearing IME in the beginning
        GPIO_PORTD_IS_R = 0; // edge senstive
        GPIO_PORTD_IBE_R = 0 ;
        GPIO_PORTD_IEV_R = 0; // falling edge to generate interrupt
        GPIO_PORTD_RIS_R = 0; // clearing GPIORIS
        GPIO_PORTD_IM_R |= (1 << pin_num);
        break;
    case PORTE :
//        GPIO_PORTE_IM_R = 0; // clearing IME in the beginning
        GPIO_PORTE_IS_R = 0; // edge senstive
        GPIO_PORTE_IBE_R = 0 ;
        GPIO_PORTE_IEV_R = 0; // falling edge to generate interrupt
        GPIO_PORTE_RIS_R = 0; // clearing GPIORIS
        GPIO_PORTE_IM_R |= (1 << pin_num);
        break;
    case PORTF :

// GPIO_PORTF_IM_R = 0; // clearing IME in the beginning
        GPIO_PORTF_IS_R = 0; // edge senstive
        GPIO_PORTF_IBE_R = 0 ;
        GPIO_PORTF_IEV_R = 0; // falling edge to generate interrupt
        GPIO_PORTF_RIS_R = 0; // clearing GPIORIS
        GPIO_PORTF_IM_R |= (1 << pin_num);
        break;
    }
}

/*******************************************************************************
 *FUNCTION NAME : GPIO_NVIC_EN0_Enable
 *
 *INPUTS : ENUM OF PORT NAME
 *
 *DESCRIPTION : ENABLING NVIC FOR ALL PORTS TO ENABLE THE INTERRUPTS
 *******************************************************************************/

void GPIO_NVIC_EN0_Enable (PORT_NAME port_name){
    switch (port_name){
    case PORTA :
        SET_BIT(NVIC_EN0_R,0);//ENABLE NVIC FOR PORTA
        break;
    case PORTB :
        SET_BIT(NVIC_EN0_R,1);//ENABLE NVIC FOR PORTB
        break;
    case PORTC :
        SET_BIT(NVIC_EN0_R,2);//ENABLE NVIC FOR PORTC
        break;
    case PORTD :
        SET_BIT(NVIC_EN0_R,3);//ENABLE NVIC FOR PORTD
        break;
    case PORTE :
        SET_BIT(NVIC_EN0_R,4);//ENABLE NVIC FOR PORTE
        break;
    case PORTF :
        SET_BIT(NVIC_EN0_R,30);//ENABLE NVIC FOR PORTF
        break ;
    }
}
/*******************************************************************************
 *FUNCTION NAME : GPIO_MODE_OF_OPERATION
 *
 *INPUTS : ENUM OF PORT NAME , MODE OF OPERATION AND THE PIN NUMBER
 *
 *DESCRIPTION : CHOOSING THE MODE OF OPERATION NEEDED FOR REQUIRED PIN
 *******************************************************************************/

void GPIO_MODE_OF_OPERATION ( PORT_NAME port_name , OPERATION_MODE mode , uint8_t pin_num){
    switch (port_name){
    case PORTA :
        if (mode == GPIO){
            CLR_BIT(GPIO_PORTA_AFSEL_R,pin_num);
        }
        else if (mode == ALTERNATIVE_FN){
            SET_BIT(GPIO_PORTA_AFSEL_R,pin_num);
        }
        break;
    case PORTB :
        if (mode == GPIO){
            CLR_BIT(GPIO_PORTB_AFSEL_R,pin_num);
        }
        else if (mode == ALTERNATIVE_FN){
            SET_BIT(GPIO_PORTB_AFSEL_R,pin_num);
        }
        break;
    case PORTC :
        if (mode == GPIO){
            CLR_BIT(GPIO_PORTC_AFSEL_R,pin_num);
        }
        else if (mode == ALTERNATIVE_FN){
            SET_BIT(GPIO_PORTC_AFSEL_R,pin_num);
        }
        break ;
    case PORTD :
        if (mode == GPIO){
            CLR_BIT(GPIO_PORTD_AFSEL_R,pin_num);
        }
        else if (mode == ALTERNATIVE_FN){
            SET_BIT(GPIO_PORTD_AFSEL_R,pin_num);
        }
        break ;
    case PORTE :
        if (mode == GPIO){
            CLR_BIT(GPIO_PORTE_AFSEL_R,pin_num);
        }
        else if (mode == ALTERNATIVE_FN){
            SET_BIT(GPIO_PORTE_AFSEL_R,pin_num);
        }
        break ;
    case PORTF :
        if (mode == GPIO){
            CLR_BIT(GPIO_PORTF_AFSEL_R,pin_num);
        }
        else if (mode == ALTERNATIVE_FN){
            SET_BIT(GPIO_PORTF_AFSEL_R,pin_num);
        }
        break;
    }

}
/*******************************************************************************
 *FUNCTION NAME : GPIO_CURRENT_OF_PIN
 *
 *INPUTS : ENUM OF PORT NAME , MODE OF CURRENT USED IN PINS AND THE PIN NUMBER
 *
 *DESCRIPTION : CHOOSING THE CURRENT USED BY PINS (2MA,4MA,8MA)
 *******************************************************************************/

void GPIO_CURRENT_OF_PIN ( PORT_NAME port_name , CUREENT mode , uint8_t pin_num){
    switch (port_name){
    case PORTA :
        if(mode == ma_2){
            SET_BIT(GPIO_PORTA_DR2R_R,pin_num);
        }
        else if(mode == ma_4){
            SET_BIT(GPIO_PORTA_DR4R_R,pin_num);
        }
        else if(mode == ma_8){
            SET_BIT(GPIO_PORTA_DR8R_R,pin_num);
        }
        break;
    case PORTB :
        if(mode == ma_2){
            SET_BIT(GPIO_PORTB_DR2R_R,pin_num);
        }
        else if(mode == ma_4){
            SET_BIT(GPIO_PORTB_DR4R_R,pin_num);
        }
        else if(mode == ma_8){
            SET_BIT(GPIO_PORTB_DR8R_R,pin_num);
        }
        break;
    case PORTC :
        if(mode == ma_2){
            SET_BIT(GPIO_PORTC_DR2R_R,pin_num);
        }
        else if(mode == ma_4){
            SET_BIT(GPIO_PORTC_DR4R_R,pin_num);
        }
        else if(mode == ma_8){
            SET_BIT(GPIO_PORTC_DR8R_R,pin_num);
        }
        break;
    case PORTD :
        if(mode == ma_2){
            SET_BIT(GPIO_PORTD_DR2R_R,pin_num);
        }
        else if(mode == ma_4){
            SET_BIT(GPIO_PORTD_DR4R_R,pin_num);
        }
        else if(mode == ma_8){
            SET_BIT(GPIO_PORTD_DR8R_R,pin_num);
        }
        break ;
    case PORTE :
        if(mode == ma_2){
            SET_BIT(GPIO_PORTE_DR2R_R,pin_num);
        }
        else if(mode == ma_4){
            SET_BIT(GPIO_PORTE_DR4R_R,pin_num);
        }
        else if(mode == ma_8){
            SET_BIT(GPIO_PORTE_DR8R_R,pin_num);
        }
        break;
    case PORTF :
        if(mode == ma_2){
            SET_BIT(GPIO_PORTF_DR2R_R,pin_num);
        }
        else if(mode == ma_4){
            SET_BIT(GPIO_PORTF_DR4R_R,pin_num);
        }
        else if(mode == ma_8){
            SET_BIT(GPIO_PORTF_DR8R_R,pin_num);
        }
        break ;
    }
}

/*******************************************************************************
 *FUNCTION NAME : GPIO_PULL_UP_DOWN_OPENDRAIN
 *
 *INPUTS : ENUM OF PORT NAME , MODE OF USED IN PINS AND THE PIN NUMBER
 *
 *DESCRIPTION : CHOOSING THE MODE OF EACH PIN (PULL UP , PULL DOWN , OPEN DRAIN)
 *******************************************************************************/

void GPIO_PULL_UP_DOWN_OPENDRAIN ( PORT_NAME port_name , PIN_TYPE mode , uint8_t pin_num){
    switch(port_name){
    case PORTA :
        if(mode == pull_up){
            SET_BIT(GPIO_PORTA_PUR_R,pin_num);
        }
        else if(mode == pull_down){
            SET_BIT(GPIO_PORTA_PDR_R,pin_num);
        }
        else if(mode == open_drain){
            SET_BIT(GPIO_PORTA_ODR_R,pin_num);
        }
        break ;
    case PORTB :
        if(mode == pull_up){
            SET_BIT(GPIO_PORTB_PUR_R,pin_num);
        }
        else if(mode == pull_down){
            SET_BIT(GPIO_PORTB_PDR_R,pin_num);
        }
        else if(mode == open_drain){
            SET_BIT(GPIO_PORTB_ODR_R,pin_num);
        }
        break;
    case PORTC :
        if(mode == pull_up){
            SET_BIT(GPIO_PORTC_PUR_R,pin_num);
        }
        else if(mode == pull_down){
            SET_BIT(GPIO_PORTC_PDR_R,pin_num);
        }
        else if(mode == open_drain){
            SET_BIT(GPIO_PORTC_ODR_R,pin_num);
        }
        break ;
    case PORTD :
        if(mode == pull_up){
            SET_BIT(GPIO_PORTD_PUR_R,pin_num);
        }
        else if(mode == pull_down){
            SET_BIT(GPIO_PORTD_PDR_R,pin_num);
        }
        else if(mode == open_drain){
            SET_BIT(GPIO_PORTD_ODR_R,pin_num);
        }
        break;
    case PORTE :
        if(mode == pull_up){
            SET_BIT(GPIO_PORTE_PUR_R,pin_num);
        }
        else if(mode == pull_down){
            SET_BIT(GPIO_PORTE_PDR_R,pin_num);
        }
        else if(mode == open_drain){
            SET_BIT(GPIO_PORTE_ODR_R,pin_num);
        }
        break;
    case PORTF :
        if(mode == pull_up){
            SET_BIT(GPIO_PORTF_PUR_R,pin_num);
        }
        else if(mode == pull_down){
            SET_BIT(GPIO_PORTF_PDR_R,pin_num);
        }
        else if(mode == open_drain){
            SET_BIT(GPIO_PORTF_ODR_R,pin_num);
        }
        break;
    }
}



