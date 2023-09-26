#ifndef HOMECONTROL_INTERFACE_FILE
#define HOMECONTROL_INTERFACE_FILE


#include "../General/STD.h"
#include "../General/ErrorStates.h"



//APIs prototypes

extern ErrorState_t HomeControl_enu_Initialization(void);

extern ErrorState_t HomeControl_enu_HomeControlSystem (void);

extern ErrorState_t HomeControl_enu_GotoPage (u8 Copy_u8_Page);

#endif