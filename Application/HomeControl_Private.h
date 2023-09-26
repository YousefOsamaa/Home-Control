#ifndef HOMECONTROL_PRIVATE_FILE
#define HOMECONTROL_PRIVATE_FILE

//Password constraints
#define HOMECONTROL_MAX_TRIALS   3
#define HOMECONTROL_PASSWORD_MAX_LENGTH    15

//LED random VAlue
#define LED_NOT_CHOSEN  0xFF


//System Pages
typedef enum
{
    HOME_SCREEN,
    LOGIN_SCREEN,
    CONTROL_MENU,
    CONTROL_LED_MENU,
    LED_INNER_MENU,
    CONTROL_AC_OPTION,
    CONTROL_TEMPERATURE_OPTION,
    CONTROL_EXIT_OPTION,
    ALERT,
    SHUTDOWN
}HomeControl_enu_SystemState;


//Local functions' prototypes

static ErrorState_t enu_PrintScreen(u8 Copy_u8_ScreenToPrint);

static ErrorState_t enu_WrongChoiceSelected(u8 Copy_Page_Number);



#endif