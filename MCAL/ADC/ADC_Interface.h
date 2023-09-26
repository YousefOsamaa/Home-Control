#ifndef ADC_INTERFACE_FILE
#define ADC_INTERFACE_FILE


#include "../../General/STD.h"
#include "../../General/ErrorStates.h"


//APIs prototypes

extern ErrorState_t ADC_enu_Initialization(void);

extern ErrorState_t ADC_enu_SetDataDirection(u8 Copy_u8_DataDirection);

extern ErrorState_t ADC_enu_SetTriggerringSource(u8 Copy_u8_TriggeringSource);

extern ErrorState_t ADC_enu_SetADIF(void);

extern ErrorState_t ADC_enu_ClearADIF(void);

extern ErrorState_t ADC_enu_SetADIE(void);

extern ErrorState_t ADC_enu_ClearADIE(void);

extern ErrorState_t ADC_enu_ReadADIF(u8* Copy_pu8_Result);

extern  ErrorState_t ADC_enu_ReadADSC(u8* Copy_pu8_Result);

extern ErrorState_t ADC_enu_ChangePrescalerFactor(u8 Copy_u8_DivisonFactor);

extern ErrorState_t ADC_enu_StartConversion(u8 Copy_u8_Channel, u16* Copy_pu16_Result);

extern ErrorState_t ADC_enu_ReadADCH(u8* Copy_pu8_Result);

extern ErrorState_t ADC_enu_ReadADCL(u8* Copy_pu8_Result);




#endif