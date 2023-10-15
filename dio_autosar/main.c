#include "MCAL/dio.h"

int main(void)
{
    Dio_LevelType pin_value;
    PORT_init(PORTF);
    PortPin_Direction(PORTF,output,1);
    Dio_WriteChannel(41, STD_HIGH);
    pin_value = Dio_ReadChannel(41);
	return 0;
}
