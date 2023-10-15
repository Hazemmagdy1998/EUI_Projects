#include "tm4c123gh6pm.h"
#include "dio.h"



void PORT_init(PORT_NAME port){

    switch (port) {
    case PORTA :
        SYSCTL_RCGCGPIO_R |= (1<<PORTA);
        GPIO_PORTA_LOCK_R = 0X4C4F434B;
        GPIO_PORTA_CR_R = 0X11;
        GPIO_PORTA_DEN_R = 0XFF;
        break;
    case PORTB :
        SYSCTL_RCGCGPIO_R |= (1<<PORTB);
        GPIO_PORTB_LOCK_R = 0X4C4F434B;
        GPIO_PORTB_CR_R = 0X11;
        GPIO_PORTB_DEN_R = 0XFF;
        break;
    case PORTC :
        SYSCTL_RCGCGPIO_R |= (1<<PORTC);
        GPIO_PORTC_LOCK_R = 0X4C4F434B;
        GPIO_PORTC_CR_R = 0X11;
        GPIO_PORTC_DEN_R = 0XFF;
        break;
    case PORTD :
        SYSCTL_RCGCGPIO_R |= (1<<PORTD);
        GPIO_PORTD_LOCK_R = 0X4C4F434B;
        GPIO_PORTD_CR_R = 0X11;
        GPIO_PORTD_DEN_R = 0XFF;
        break;
    case PORTE :
        SYSCTL_RCGCGPIO_R |= (1<<PORTE);
        GPIO_PORTE_LOCK_R = 0X4C4F434B;
        GPIO_PORTE_CR_R = 0X11;
        GPIO_PORTE_DEN_R = 0XFF;
        break;
    case PORTF :
        SYSCTL_RCGCGPIO_R |= (1<<PORTF);
        GPIO_PORTF_LOCK_R = 0X4C4F434B;
        GPIO_PORTF_CR_R = 0X11;
        GPIO_PORTF_DEN_R = 0XFF;
        break;
    default:
        break;
    }

}


void PortPin_Direction (PORT_NAME port_name ,PIN_DIRECTION pin_type ,uint8 pin_num){
    switch(port_name){
    case PORTA :
        if(pin_type == input){
            GPIO_PORTA_DIR_R &= ~(1<<pin_num);
        }
        else if (pin_type == output){
            GPIO_PORTA_DIR_R |= (1<<pin_num);
        }
        else{
            /*FOR MISRA RULES*/
        }
        break;
    case PORTB :
        if(pin_type == input){
            GPIO_PORTB_DIR_R &= ~(1<<pin_num);
        }
        else if (pin_type == output){
            GPIO_PORTB_DIR_R |= (1<<pin_num);
        }
        else{
            /*FOR MISRA RULES*/
        }
        break ;
    case PORTC :
        if(pin_type == input){
            GPIO_PORTC_DIR_R &= ~(1<<pin_num);
        }
        else if (pin_type == output){
            GPIO_PORTC_DIR_R |= (1<<pin_num);
        }
        else{
            /*FOR MISRA RULES*/
        }
        break;
    case PORTD :
        if(pin_type == input){
            GPIO_PORTD_DIR_R &= ~(1<<pin_num);
        }
        else if (pin_type == output){
            GPIO_PORTD_DIR_R |= (1<<pin_num);
        }
        else{
            /*FOR MISRA RULES*/
        }
        break;
    case PORTE :
        if(pin_type == input){
            GPIO_PORTE_DIR_R &= ~(1<<pin_num);
        }
        else if (pin_type == output){
            GPIO_PORTE_DIR_R |= (1<<pin_num);
        }
        else{
            /*FOR MISRA RULES*/
        }
        break ;
    case PORTF :
        if(pin_type == input){
            GPIO_PORTF_DIR_R &= ~(1<<pin_num);
        }
        else if (pin_type == output){
            GPIO_PORTF_DIR_R |= (1<<pin_num);
        }
        else{
            /*FOR MISRA RULES*/
        }
        break ;
    }
}

Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId){
    Dio_LevelType read ;
    if((ChannelId >= 0) && (ChannelId <= 7)){
        ChannelId = ChannelId - (8*0);
        read = (GPIO_PORTA_DATA_R & (1 << ChannelId)) >> ChannelId;
        if(read == 1){
            read = STD_HIGH;
        }
        else if(read == 0){
            read = STD_LOW;
        }
        else{
            /*FOR MISRA RULES*/
        }
    }
    else if(ChannelId <= 15 && ChannelId >= 8){
        ChannelId = ChannelId - (8*1);
        read = (GPIO_PORTB_DATA_R & (1 << ChannelId)) >> ChannelId;
        if(read == 1){
            read = STD_HIGH;
        }
        else if(read == 0){
            read = STD_LOW;
        }
        else{
            /*FOR MISRA RULES*/
        }
    }
    else if(ChannelId <= 23 && ChannelId >= 16){
        ChannelId = ChannelId - (8*2);
        read = (GPIO_PORTC_DATA_R & (1 << ChannelId)) >> ChannelId;
        if(read == 1){
            read = STD_HIGH;
        }
        else if(read == 0){
            read = STD_LOW;
        }
        else{
            /*FOR MISRA RULES*/
        }
    }
    else if (ChannelId <= 31 && ChannelId >= 24){
        ChannelId = ChannelId - (8*3);
        read = (GPIO_PORTD_DATA_R & (1 << ChannelId)) >> ChannelId;
        if(read == 1){
            read = STD_HIGH;
        }
        else if(read == 0){
            read = STD_LOW;
        }
        else{
            /*FOR MISRA RULES*/
        }
    }
    else if (ChannelId <= 39 && ChannelId >= 32){
        ChannelId = ChannelId - (8*4);
        read = (GPIO_PORTE_DATA_R & (1 << ChannelId)) >> ChannelId;
        if(read == 1){
            read = STD_HIGH;
        }
        else if(read == 0){
            read = STD_LOW;
        }
        else{
            /*FOR MISRA RULES*/
        }
    }
    else if (ChannelId <= 47 && ChannelId >= 40){
        ChannelId = ChannelId - (8*5);
        read = (GPIO_PORTF_DATA_R & (1 << ChannelId)) >> ChannelId;
        if(read == 1){
            read = STD_HIGH;
        }
        else if(read == 0){
            read = STD_LOW;
        }
        else{
            /*FOR MISRA RULES*/
        }
    }
    else{
        /*FOR MISRA*/
    }
    return read ;
}
void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level){
    if((ChannelId >= 0) && (ChannelId <= 7)){
        ChannelId = ChannelId - (8*0);
        if(Level == STD_HIGH){
            GPIO_PORTA_DATA_R |= (1<<ChannelId);
        }
        else if(Level == STD_LOW){
            GPIO_PORTA_DATA_R &= ~(1<<ChannelId);
        }
        else{
            /*FOR MISRA RULES*/
        }
    }
    else if(ChannelId <= 15 && ChannelId >= 8){
        ChannelId = ChannelId - (8*1);
        if(Level == STD_HIGH){
            GPIO_PORTB_DATA_R |= (1<<ChannelId);
        }
        else if(Level == STD_LOW){
            GPIO_PORTB_DATA_R &= ~(1<<ChannelId);
        }
        else{
            /*FOR MISRA RULES*/
        }
    }
    else if(ChannelId <= 23 && ChannelId >= 16){
        ChannelId = ChannelId - (8*2);
        if(Level == STD_HIGH){
            GPIO_PORTC_DATA_R |= (1<<ChannelId);
        }
        else if(Level == STD_LOW){
            GPIO_PORTC_DATA_R &= ~(1<<ChannelId);
        }
        else{
            /*FOR MISRA RULES*/
        }
    }
    else if (ChannelId <= 31 && ChannelId >= 24){
        ChannelId = ChannelId - (8*3);
        if(Level == STD_HIGH){
            GPIO_PORTD_DATA_R |= (1<<ChannelId);
        }
        else if(Level == STD_LOW){
            GPIO_PORTD_DATA_R &= ~(1<<ChannelId);
        }
        else{
            /*FOR MISRA RULES*/
        }
    }
    else if (ChannelId <= 39 && ChannelId >= 32){
        ChannelId = ChannelId - (8*4);
        if(Level == STD_HIGH){
            GPIO_PORTE_DATA_R |= (1<<ChannelId);
        }
        else if(Level == STD_LOW){
            GPIO_PORTE_DATA_R &= ~(1<<ChannelId);
        }
        else{
            /*FOR MISRA RULES*/
        }
    }
    else if (ChannelId <= 47 && ChannelId >= 40){
        ChannelId = ChannelId - (8*5);
        if(Level == STD_HIGH){
            GPIO_PORTF_DATA_R |= (1<<ChannelId);
        }
        else if(Level == STD_LOW){
            GPIO_PORTF_DATA_R &= ~(1<<ChannelId);
        }
        else{
            /*FOR MISRA RULES*/
        }
    }
    else{
        /*FOR MISRA*/
    }
}


Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId){
    Dio_PortLevelType read_port;
    if(PortId == 0){
        read_port = GPIO_PORTA_DATA_R;
    }
    else if(PortId == 1){
        read_port = GPIO_PORTB_DATA_R;
    }
    else if(PortId == 2){
        read_port = GPIO_PORTC_DATA_R;
    }
    else if(PortId == 3){
        read_port = GPIO_PORTD_DATA_R;
    }
    else if(PortId == 4){
        read_port = GPIO_PORTE_DATA_R;
    }
    else if(PortId == 5){
        read_port = GPIO_PORTF_DATA_R;
    }
    else{
        /*FOR MISRA RULES*/
    }

    return read_port;
}

void Dio_WritePort (Dio_PortType PortId,Dio_PortLevelType Level){
    if(PortId == 0){
        GPIO_PORTA_DATA_R = Level;
    }
    else if(PortId == 1){
        GPIO_PORTB_DATA_R = Level;
    }
    else if(PortId == 2){
        GPIO_PORTC_DATA_R = Level;
    }
    else if(PortId == 3){
        GPIO_PORTD_DATA_R = Level;
    }
    else if(PortId == 4){
        GPIO_PORTE_DATA_R = Level;
    }
    else if(PortId == 5){
        GPIO_PORTF_DATA_R = Level;
    }
    else{
        /*FOR MISRA RULES*/
    }
}


