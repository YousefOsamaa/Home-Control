#include "../General/STD.h"
#include "../General/ErrorStates.h"
#include <util/delay.h>

#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/Keypad/Keypad_Interface.h"
#include "../HAL/LED/LED_Interface.h"
#include "../HAL/Buzzer/Buzzer_Interface.h"
#include "../HAL/Relay/Relay_Interface.h"

#include "HomeControl_Config.h"
#include "HomeControl_Private.h"


//System State
static u8 u8_SystemState = HOME_SCREEN;
//Invalid password entries counter
static u8 u8_IncorrectPasswordEntry = 0;
//System password
static u8 au8_Password [HOMECONTROL_PASSWORD_MAX_LENGTH] = HOMECONTROL_PASSWORD;
//LED chosen
u8 u8_ChosenLED = LED_NOT_CHOSEN;


//APIs implementation
extern ErrorState_t HomeControl_enu_Initialization(void)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    LCD_enu_Initialization();
    Keypad_enu_Initialization();
    LED_enu_Initialization();
    Buzzer_enu_Initialization();
    Relay_enu_Initialization();

    Local_u8_ErrorFlag = ES_OK;

    return Local_u8_ErrorFlag;
}

extern ErrorState_t HomeControl_enu_HomeControlSystem (void)
{
    while (u8_SystemState != SHUTDOWN)
    {

        switch(u8_SystemState)
        {
            case HOME_SCREEN:
            {

                //printing the home screen
                enu_PrintScreen(HOME_SCREEN);
                //1 second delay
                _delay_ms(2000);

                u8_SystemState = LOGIN_SCREEN;
            }
            break;
    

            case LOGIN_SCREEN:
            {
                //printing the home screen
                enu_PrintScreen(LOGIN_SCREEN);
                
                while((u8_IncorrectPasswordEntry < HOMECONTROL_MAX_TRIALS) && (u8_SystemState == LOGIN_SCREEN))
                {

                    u8 Local_u8_keyValue;
                    u8 Local_u8_CharacterCounter = 0;
                    u8 Local_u8_IncorrectPasswordFlag = False;


                    //Displaying the failed trails count
                    LCD_enu_GoToPosition(LCD_ROW_2,LCD_COLUMN_16,LCD_PAGE_1);
                    LCD_enu_SendData(u8_IncorrectPasswordEntry + ASCII_OFFSET );


                    //Placing cursor on the beginning of the line to print the asterisk
                    LCD_enu_GoToPosition(LCD_ROW_2,LCD_COLUMN_1,LCD_PAGE_1);
                    //User entering password
                    while (Local_u8_CharacterCounter < HOMECONTROL_PASSWORD_LENGTH)
                    {
                        //Getting key pressed
                        Keypad_enu_GetButtonPressedValue(&Local_u8_keyValue);

                        if (Local_u8_keyValue != KEYPAD_NOT_PRESSED_VALUE)
                        {
                            Local_u8_CharacterCounter++;
                            LCD_enu_SendData('*');

                            //Checking if the password is correct
                            if(Local_u8_keyValue != au8_Password[Local_u8_CharacterCounter - 1])
                            {   
                                Local_u8_IncorrectPasswordFlag = True;
                            }
                        }
                    } 

                    if(Local_u8_IncorrectPasswordFlag)
                    {
                        
                        //Clearing second row
                        LCD_enu_ClearRow(LCD_ROW_2,LCD_PAGE_1);

                        //Printing Incorrect Password
                        LCD_enu_GoToPosition(LCD_ROW_2,LCD_COLUMN_1,LCD_PAGE_1);
                        LCD_enu_SendString("INCORRECT!");
                        enu_WrongChoiceSelected(LCD_PAGE_1);
                        _delay_ms(2000);

                        //Clearing second row
                        LCD_enu_ClearRow(LCD_ROW_2,LCD_PAGE_1);

                        //Incrementing the count
                        u8_IncorrectPasswordEntry++;        
                        
                    }
                    else
                    {
                        //Clearing second row
                        LCD_enu_ClearRow(LCD_ROW_2,LCD_PAGE_1);

                        //Printing correct Password
                        LCD_enu_GoToPosition(LCD_ROW_2,LCD_COLUMN_1,LCD_PAGE_1);
                        LCD_enu_SendString("CORRECT!");
                        _delay_ms(2000);

                        //Clearing the second row
                        LCD_enu_ClearRow(LCD_ROW_2,LCD_PAGE_1);

                        //Resetting counter to zero 
                        u8_IncorrectPasswordEntry = 0;

                        u8_SystemState = CONTROL_MENU;

                    }
                    
                    
                }

                if(u8_IncorrectPasswordEntry == HOMECONTROL_MAX_TRIALS)
                {
                    u8_SystemState = ALERT;
                }
                
            }
            break;
            
            case CONTROL_MENU:
            {
                u8 Local_u8_KeyValue;

                //printing the home screen
                enu_PrintScreen(CONTROL_MENU);

                while((Local_u8_KeyValue == KEYPAD_NOT_PRESSED_VALUE) || (u8_SystemState == CONTROL_MENU))
                {
                    Keypad_enu_GetButtonPressedValue(&Local_u8_KeyValue);

                    if(Local_u8_KeyValue == '1')
                    {
                        u8_SystemState = CONTROL_LED_MENU;
                    }
                    else if (Local_u8_KeyValue == '2')
                    {

                        u8_SystemState = CONTROL_AC_OPTION;
                    }
                    else if (Local_u8_KeyValue == '3')
                    {
                        
                        u8_SystemState = CONTROL_TEMPERATURE_OPTION;
                    }
                    else if (Local_u8_KeyValue == '4')
                    {
                        u8_SystemState = CONTROL_EXIT_OPTION;
                    }
                    else if (Local_u8_KeyValue != KEYPAD_NOT_PRESSED_VALUE)
                    {
                        enu_WrongChoiceSelected(LCD_PAGE_1);
                    }
                    
                }

            }
            break; 

            case CONTROL_LED_MENU:
            {
                u8 Local_u8_KeyValue;

                //printing the home screen
                enu_PrintScreen(CONTROL_LED_MENU);            

                while((Local_u8_KeyValue == KEYPAD_NOT_PRESSED_VALUE) || (u8_SystemState == CONTROL_LED_MENU))
                {
                    Keypad_enu_GetButtonPressedValue(&Local_u8_KeyValue);

                    if(Local_u8_KeyValue == '1')
                    {
                        u8_ChosenLED = LED_0;
                        u8_SystemState = LED_INNER_MENU;
                    }
                    else if (Local_u8_KeyValue == '2')
                    {
                        u8_ChosenLED = LED_1;
                        u8_SystemState = LED_INNER_MENU;
                    }
                    else if (Local_u8_KeyValue == '3')
                    {
                        u8_ChosenLED = LED_2;
                        u8_SystemState = LED_INNER_MENU;
                    }
                    else if (Local_u8_KeyValue == '4')
                    {
                        u8_SystemState = CONTROL_MENU;
                    }
                    else if(Local_u8_KeyValue != KEYPAD_NOT_PRESSED_VALUE)
                    {
                        enu_WrongChoiceSelected(LCD_PAGE_1);
                    }
                }

            }
            break;

            case LED_INNER_MENU:
            {   
                u8 Local_u8_KeyValue;

                //printing the LED_INNER_MENU
                enu_PrintScreen(LED_INNER_MENU);

                while((Local_u8_KeyValue == KEYPAD_NOT_PRESSED_VALUE) || (u8_SystemState == LED_INNER_MENU))
                {
                    Keypad_enu_GetButtonPressedValue(&Local_u8_KeyValue);

                    if(Local_u8_KeyValue == '1')
                    {
                        LED_enu_TurnOnLED(u8_ChosenLED);
                    }
                    else if(Local_u8_KeyValue == '2')
                    {
                        LED_enu_TurnOffLED(u8_ChosenLED);
                        
                    }   
                    else if (Local_u8_KeyValue == '3')
                    {
                        u8_ChosenLED = LED_NOT_CHOSEN;
                        u8_SystemState = CONTROL_LED_MENU;
                    }
                    else if(Local_u8_KeyValue != KEYPAD_NOT_PRESSED_VALUE)
                    {
                        enu_WrongChoiceSelected(LCD_PAGE_1);
                    }
                }




            }    
            break;


            case CONTROL_AC_OPTION:
            {
                u8 Local_u8_KeyValue;

                //printing the home screen
                enu_PrintScreen(CONTROL_AC_OPTION);

                while((Local_u8_KeyValue == KEYPAD_NOT_PRESSED_VALUE) || (u8_SystemState == CONTROL_AC_OPTION))
                {
                    Keypad_enu_GetButtonPressedValue(&Local_u8_KeyValue);

                    if(Local_u8_KeyValue == '1')
                    {
                        Relay_enu_TuronOnRelay(RELAY_0);
                    }
                    else if(Local_u8_KeyValue == '2')
                    {
                    
                        Relay_enu_TuronOffRelay(RELAY_0);
                        
                    }   
                    else if (Local_u8_KeyValue == '3')
                    {
                        u8_SystemState = CONTROL_LED_MENU;
                    }
                    else if(Local_u8_KeyValue != KEYPAD_NOT_PRESSED_VALUE)
                    {
                        enu_WrongChoiceSelected(LCD_PAGE_1);
                    }
                }
            }
            break;

            case CONTROL_TEMPERATURE_OPTION:
            {
                u8 Local_u8_KeyValue;

                //printing the home screen
                enu_PrintScreen(CONTROL_TEMPERATURE_OPTION);

                //Displaying Temperature (Hardcoded for now)
                LCD_enu_GoToPosition(LCD_ROW_1, LCD_COLUMN_15,LCD_PAGE_1);
                LCD_enu_SendString("25");

                while((Local_u8_KeyValue == KEYPAD_NOT_PRESSED_VALUE) || (u8_SystemState == CONTROL_TEMPERATURE_OPTION))
                {

                    //Getting key pressed
                    Keypad_enu_GetButtonPressedValue(&Local_u8_KeyValue);

                    if(Local_u8_KeyValue == '1')
                    {
                        u8_SystemState = CONTROL_MENU;
                    }
                    else if(Local_u8_KeyValue != KEYPAD_NOT_PRESSED_VALUE)
                    {
                        //If wrong choice was entered
                        enu_WrongChoiceSelected(LCD_PAGE_1);
                    }
                    
                }

            

            }
            break;

            case CONTROL_EXIT_OPTION:
            {
                //printing the home screen
                enu_PrintScreen(CONTROL_EXIT_OPTION);
                //Fake delay
                _delay_ms(2000);

                u8_SystemState = SHUTDOWN;
            }
            break;

            case ALERT:
            {
                //printing the home screen
                enu_PrintScreen(ALERT);
                Buzzer_enu_TurnOnAllBuzzers();

                while(1)
                {
                    //until certain action is done 
                }
            }
            break;

            default:
            break;
        }

    }

    //Clearing page when system shutsdown
    LCD_enu_ClearPage(LCD_PAGE_1);
}



static ErrorState_t enu_PrintScreen(u8 Copy_u8_ScreenToPrint)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    switch (Copy_u8_ScreenToPrint)
    {

        case HOME_SCREEN:
        
        //Clearing Page
        LCD_enu_ClearPage(LCD_PAGE_1);
        
        //Displaying 'Welcome'
        LCD_enu_GoToPosition(LCD_ROW_1,LCD_COLUMN_5,LCD_PAGE_1);
        LCD_enu_SendString("WELCOME!");
        
        //Displaying 'PLease wait, System is Loading...'
        LCD_enu_GoToPosition(LCD_ROW_2,LCD_COLUMN_5,LCD_PAGE_1);
        LCD_enu_SendString("LOADING...");

        break;

        case LOGIN_SCREEN:
        //Clearing Page
        LCD_enu_ClearPage(LCD_PAGE_1);
        
        //Displaying 'Enter Password'
        LCD_enu_GoToPosition(LCD_ROW_1,LCD_COLUMN_1,LCD_PAGE_1);
        LCD_enu_SendString("ENTER PASSWORD: ");

        break;
        
        case CONTROL_MENU:
        //Clearing Page
        LCD_enu_ClearPage(LCD_PAGE_1);

        //Displaying 1-LED MENU
        LCD_enu_GoToPosition(LCD_ROW_1,LCD_COLUMN_1,LCD_PAGE_1);
        LCD_enu_SendString("1-LED");

        //Displaying 1-LED MENU
        LCD_enu_GoToPosition(LCD_ROW_1,LCD_COLUMN_8,LCD_PAGE_1);
        LCD_enu_SendString("2-AC");

        //Displaying 1-LED MENU
        LCD_enu_GoToPosition(LCD_ROW_2,LCD_COLUMN_1,LCD_PAGE_1);
        LCD_enu_SendString("3-TEMP");

        //Displaying 1-LED MENU
        LCD_enu_GoToPosition(LCD_ROW_2,LCD_COLUMN_8,LCD_PAGE_1);
        LCD_enu_SendString("4-EXIT");
        break; 
        

        case CONTROL_LED_MENU:
        //Clearing Page
        LCD_enu_ClearPage(LCD_PAGE_1);

        //Displaying '1-LED 1
        LCD_enu_GoToPosition(LCD_ROW_1,LCD_COLUMN_1,LCD_PAGE_1);
        LCD_enu_SendString("1-LED0");

        //Displaying '2-LED 2
        LCD_enu_GoToPosition(LCD_ROW_1,LCD_COLUMN_9,LCD_PAGE_1);
        LCD_enu_SendString("2-LED1");

        //Displaying '3-LED 3
        LCD_enu_GoToPosition(LCD_ROW_2,LCD_COLUMN_1,LCD_PAGE_1);
        LCD_enu_SendString("3-LED2");


        //Displaying '4-BACK'
        LCD_enu_GoToPosition(LCD_ROW_2,LCD_COLUMN_9,LCD_PAGE_1);
        LCD_enu_SendString("4-BACK");
        break;
        
        case LED_INNER_MENU:
        //Clearing Page
        LCD_enu_ClearPage(LCD_PAGE_1);

        //Displaying '1-ON'
        LCD_enu_GoToPosition(LCD_ROW_1,LCD_COLUMN_1,LCD_PAGE_1);
        LCD_enu_SendString("1-ON");

        //Displaying '2-OFF'
        LCD_enu_GoToPosition(LCD_ROW_1,LCD_COLUMN_8,LCD_PAGE_1);
        LCD_enu_SendString("2-OFF");

        //Displaying '3-BACK'
        LCD_enu_GoToPosition(LCD_ROW_2,LCD_COLUMN_1,LCD_PAGE_1);
        LCD_enu_SendString("3-BACK");
        break;


        case CONTROL_AC_OPTION:
        //Clearing Page
        LCD_enu_ClearPage(LCD_PAGE_1);

        //Displaying '1-ON'
        LCD_enu_GoToPosition(LCD_ROW_1,LCD_COLUMN_1,LCD_PAGE_1);
        LCD_enu_SendString("1-ON");

        //Displaying '2-OFF'
        LCD_enu_GoToPosition(LCD_ROW_1,LCD_COLUMN_8,LCD_PAGE_1);
        LCD_enu_SendString("2-OFF");

        //Displaying '3-BACK'
        LCD_enu_GoToPosition(LCD_ROW_2,LCD_COLUMN_1,LCD_PAGE_1);
        LCD_enu_SendString("3-BACK");
        break;
        

        case CONTROL_TEMPERATURE_OPTION:
        //Clearing Page
        LCD_enu_ClearPage(LCD_PAGE_1);
        
        //Displaying 'Temperature ='
        LCD_enu_GoToPosition(LCD_ROW_1,LCD_COLUMN_1,LCD_PAGE_1);
        LCD_enu_SendString("TEMPERATURE = ");
        
        //Displaying '1-BACK'
        LCD_enu_GoToPosition(LCD_ROW_2,LCD_COLUMN_1,LCD_PAGE_1);
        LCD_enu_SendString("1-BACK");
        break;
        

        case CONTROL_EXIT_OPTION:
        //Clearing Page
        LCD_enu_ClearPage(LCD_PAGE_1);

        //Displaying 'GOODBYE!'
        LCD_enu_GoToPosition(LCD_ROW_1,LCD_COLUMN_5,LCD_PAGE_1);
        LCD_enu_SendString("GOODBYE!");
        
        //Displaying 'PLease wait, System is Loading...'
        LCD_enu_GoToPosition(LCD_ROW_2,LCD_COLUMN_5,LCD_PAGE_1);
        LCD_enu_SendString("LOADING...");
        break;
        

        case ALERT:
        //Clearing Page
        LCD_enu_ClearPage(LCD_PAGE_1);

        //Alert message characters
        u8 HomeControl_au8_AlertMessage []= { 0x00,0x00,0x0E,0x01,0x1F,0x00,0x00,0x00,  //ح
                                  0x00,0x00,0x00,0x04,0x07,0x04,0x04,0x18,  //ر
                                  0x00,0x04,0x04,0x04,0x04,0x00,0x00,0x00,  //ا
                                  0x00,0x00,0x07,0x05,0x1F,0x00,0x00,0x00,  //م
                                  0x00,0x00,0x07,0x04,0x12,0x11,0x0E,0x00   //ي
                                };


        LCD_enu_DrawSpecialCharacter( HomeControl_au8_AlertMessage,5,LCD_CUSTOM_PATTERN_0,LCD_ROW_1,LCD_COLUMN_10,LCD_PAGE_1,LCD_AC_DEC);
        //Reetting AC to increase agin
        LCD_enu_SendCommand(0x06);
        
        //Displaying '!!!!!!!'
        LCD_enu_GoToPosition(LCD_ROW_2,LCD_COLUMN_5,LCD_PAGE_1);
        LCD_enu_SendString("!!!!!!!");

        break;

        
        default:
        Local_u8_ErrorFlag = ES_OUT_OF_RANGE;
        break;
    }


    return Local_u8_ErrorFlag;    
}

static ErrorState_t enu_WrongChoiceSelected(u8 Copy_Page_Number)
{
    u8 Local_u8_ErrorFlag = ES_NOK;


    //Displaying 'X' for wrong choice entered
    LCD_enu_GoToPosition(LCD_ROW_2,LCD_COLUMN_16,Copy_Page_Number);
    LCD_enu_SendData('X');
    _delay_ms(500);
                        
    LCD_enu_GoToPosition(LCD_ROW_2,LCD_COLUMN_16,Copy_Page_Number);
    LCD_enu_SendData(' ');

    Local_u8_ErrorFlag = ES_OK;

    return Local_u8_ErrorFlag;
}
