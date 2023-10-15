
#ifndef MCAL_DIO_H_
#define MCAL_DIO_H_


#define STD_HIGH 1
#define STD_LOW 0

typedef enum {
    PORTA,PORTB,PORTC,PORTD,PORTE,PORTF
}PORT_NAME;

typedef enum {
    input,output
}PIN_DIRECTION;


typedef unsigned char uint8 ;
typedef uint8 Dio_LevelType;
typedef uint8 Dio_ChannelType;
typedef uint8 Dio_PortLevelType;
typedef uint8 Dio_PortType;




void PORT_init(PORT_NAME port);
void PortPin_Direction (PORT_NAME port_name ,PIN_DIRECTION pin_type ,uint8 pin_num);
Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId);
void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level);
Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId);
void Dio_WritePort (Dio_PortType PortId,Dio_PortLevelType Level);







#endif /* MCAL_DIO_H_ */
