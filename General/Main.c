#include "../Application/HomeControl_Interface.h"
#include "../HAL/Keypad/Keypad_Interface.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../MCAL/DIO/DIO_Interface.h"
#include <util/delay.h>
#include "../MCAL/EXTI/EXTI_Interface.h"
#include "../MCAL/SREG/SREG_Interface.h"

void tog (void)
{
	DIO_enu_SetPinValue(DIO_PIN_GROUP_C,DIO_PIN_7,DIO_HIGH);

}

int main (void)
{
    //Initializations
	HomeControl_enu_Initialization();
	
	//System Operation
	HomeControl_enu_HomeControlSystem();

	return 0;
}


















										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										
										

































