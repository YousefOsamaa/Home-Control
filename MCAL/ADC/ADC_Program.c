#include "../../General/STD.h"
#include "../../General/ErrorStates.h"

#include "ADC_Private.h"
#include "ADC_Config.h"



//APIs implementation

extern ErrorState_t ADC_enu_Initialization(void)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    //Handling voltage reference source:
    #if ADC_V_REFERENCE_SOURCE ==  ADC_AREF
        //Bits contain 00
        ADMUX &= ~(3 << ADMUX_REFS0 );
    
    #elif ADC_V_REFERENCE_SOURCE == ADC_AVCC
        //Bits contain 01
        ADMUX |= (1 << ADMUX_REFS0);
        ADMUX &= ~(1 << ADMUX_REFS1);
    
    #elif ADC_V_REFERENCE_SOURCE == ADC_INTERNAL
        //Bits contain 11
        ADMUX |= (3 << ADMUX_REFS0);
    
    #else
        #error "ADC_V_REFERENCE_SOURCE is invalid"
    
    #endif 


    //Handling Data adjustment direction
    #if  ADC_DATA_ADJUSTMENT == ADC_LEFT_ADJUSTED
        //Setting ADLAR bit
        ADMUX |= ( 1 << ADMUX_ADLAR);
    
    #elif ADC_DATA_ADJUSTMENT == ADC_RIGHT_ADJUSTED
        //Clearing ADLAR bit
        ADMUX &= ~( 1 << ADMUX_ADLAR);
    
    #else
        #error "ADC_DATA_ADJUSTMENT is invalid"
    
    #endif

    //Handling Trigger Mode 
    #if ADC_TRIGGER_SOURCE == ADC_SINGLE_CONVERSION
        //Clearing ADATE bit
        ADCSRA &= ~( 1 << ADCSRA_ADATE);

        
        SFIOR &= ~(7 >> SFIOR_ADTS0); //BITS CONTAIN 000
    #elif  ADC_TRIGGER_SOURCE == ADC_FREE_RUNNING
        //Setting ADATE bit
        ADCSRA |=  ( 1 << ADCSRA_ADATE);

        SFIOR |= (ADC_FREE_RUNNING << SFIOR_ADTS0); //Bits contain 000
    
    #elif ADC_TRIGGER_SOURCE == ADC_ANALOG_COMPARATOR
        /Setting ADATE bit
        ADCSRA |=  ( 1 << ADCSRA_ADATE);
        
        SFIOR |= (ADC_ANALOG_COMPARATOR << SFIOR_ADTS0); //Bits contain 001
    
    #elif ADC_TRIGGER_SOURCE == ADC_EXTERNL_INT0
        //Setting ADATE bit
        ADCSRA |=  ( 1 << ADCSRA_ADATE);

        SFIOR |= (ADC_EXTERNL_INT0 << SFIOR_ADTS0); //Bits contain 010
    
    #elif ADC_TRIGGER_SOURCE == ADC_TIMER0_COMPARE_MATCH
        //Setting ADATE bit
        ADCSRA |=  ( 1 << ADCSRA_ADATE);

        SFIOR |= (ADC_TIMER0_COMPARE_MATCH << SFIOR_ADTS0); //Bits contain 011
    
    #elif ADC_TRIGGER_SOURCE == ADC_TIMER0_OVERFLOW
        //Setting ADATE bit
        ADCSRA |=  ( 1 << ADCSRA_ADATE);
        
        SFIOR |= (ADC_TIMER0_OVERFLOW << SFIOR_ADTS0); //Bits contain 100
    
    #elif ADC_TRIGGER_SOURCE == ADC_TIMER_COMPARE_MATCH_B
        //Setting ADATE bit
        ADCSRA |=  ( 1 << ADCSRA_ADATE);
        
        SFIOR |= (ADC_TIMER_COMPARE_MATCH_B << SFIOR_ADTS0); //Bits contain 101
    
    #elif ADC_TRIGGER_SOURCE == ADC_TIMER1_OVERFLOW
        //Setting ADATE bit
        ADCSRA |=  ( 1 << ADCSRA_ADATE);
        
        SFIOR |= (ADC_TIMER1_OVERFLOW << SFIOR_ADTS0); //Bits contain 110
    
    #elif ADC_TRIGGER_SOURCE == ADC_TIMER1_CAPTURE_EVENT
        //Setting ADATE bit
        ADCSRA |=  ( 1 << ADCSRA_ADATE);
        
        SFIOR |= (ADC_TIMER1_CAPTURE_EVENT << SFIOR_ADTS0); //Bits contain 111
        
    #else
        #error "ADC_TRIGGER_SOURCE is invalid "
    
    #endif


    //Handling Interrupt Event Status (PIE)
    #if ADC_INT_EVENT_STATUS == ADC_INT_ENABLE
        ADCSRA |= ( 1 << ADCSRA_ADIE); //Bit contains 1 
    
    #elif ADC_INT_EVENT_STATUS == ADC_INT_DISABLE
        ADCSRA &= ~( 1 << ADCSRA_ADIE); //Bit contains 0 
    
    #else
        #error "ADC_INT_EVENT_STATUS is invalid "
    
    #endif

    //Handling ADC clock speed
    ADCSRA &= ~ (7 << ADCSRA_ADPS0);
    #if ADC_PS_FACTOR == ADC_PS_2
        ADCSRA |= (ADC_PS_2 << ADCSRA_ADPS0); //Bits contain 001

    #elif ADC_PS_FACTOR == ADC_PS_4
        ADCSRA |= (ADC_PS_4 << ADCSRA_ADPS0); //Bits contain 010

    #elif ADC_PS_FACTOR == ADC_PS_8
        ADCSRA |= (ADC_PS_8 << ADCSRA_ADPS0); //Bits contain 011

    #elif ADC_PS_FACTOR == ADC_PS_16
        ADCSRA |= (ADC_PS_16 << ADCSRA_ADPS0); //Bits contain 100

    #elif ADC_PS_FACTOR == ADC_PS_32
        ADCSRA |= (ADC_PS_32 << ADCSRA_ADPS0); //Bits contain 101

    #elif ADC_PS_FACTOR == ADC_PS_64
        ADCSRA |= (ADC_PS_64 << ADCSRA_ADPS0); //Bits contain 011

    #elif ADC_PS_FACTOR == ADC_PS_128
        ADCSRA |= (ADC_PS_64 << ADCSRA_ADPS0); //Bits contain 111

    #else
        #error "ADC_PS_FACTOR is invalid"
    #endif

    //Handling input channels

        //Code



    // /Powering ADC
    ADCSRA |= (1 << ADCSRA_ADEN );

    Local_u8_ErrorFlag = ES_OK;
    return Local_u8_ErrorFlag; 
}

extern ErrorState_t ADC_enu_SetDataDirection(u8 Copy_u8_DataDirection)
{
    u8 Local_u8_ErrorFlag = ES_NOK;
    
    if(Copy_u8_DataDirection == ADC_LEFT_ADJUSTED)
    {
        //Setting ADLAR bit
        ADMUX |= ( 1 << ADMUX_ADLAR);

    }
    else if (Copy_u8_DataDirection == ADC_RIGHT_ADJUSTED)
    {
        //Clearing ADLAR bit
        ADMUX &= ~( 1 << ADMUX_ADLAR);

    }
    else
    {
        Local_u8_ErrorFlag = ES_OUT_OF_RANGE;
    }
    

    return Local_u8_ErrorFlag;
}

extern ErrorState_t ADC_enu_SetTriggerringSource(u8 Copy_u8_TriggeringSource)
{
    u8 Local_u8_ErrorFlag = ES_NOK;
    


    switch (Copy_u8_TriggeringSource)
    {
        case ADC_SINGLE_CONVERSION:
        //Clearing ADATE bit
        ADCSRA &= ~( 1 << ADCSRA_ADATE);
        Local_u8_ErrorFlag = ES_OK;
        break;

        case ADC_FREE_RUNNING : 
        //Setting ADATE bit
        ADCSRA |=  ( 1 << ADCSRA_ADATE);

        SFIOR |= (ADC_FREE_RUNNING << SFIOR_ADTS0); //Bits contain 000
        Local_u8_ErrorFlag = ES_OK;
        break;
        
        case ADC_ANALOG_COMPARATOR:
        //Setting ADATE bit
        ADCSRA |=  ( 1 << ADCSRA_ADATE);

        SFIOR |= (ADC_ANALOG_COMPARATOR << SFIOR_ADTS0); //Bits contain 001
        Local_u8_ErrorFlag = ES_OK;
        break;
        case ADC_EXTERNL_INT0: 
        //Setting ADATE bit
        ADCSRA |=  ( 1 << ADCSRA_ADATE);

        SFIOR |= (ADC_EXTERNL_INT0 << SFIOR_ADTS0); //Bits contain 010
        Local_u8_ErrorFlag = ES_OK;
        break;

        case ADC_TIMER0_COMPARE_MATCH: 
        //Setting ADATE bit
        ADCSRA |=  ( 1 << ADCSRA_ADATE);

        SFIOR |= (ADC_TIMER0_COMPARE_MATCH << SFIOR_ADTS0); //Bits contain 011
        Local_u8_ErrorFlag = ES_OK;
        break;

        case ADC_TIMER0_OVERFLOW: 
        //Setting ADATE bit
        ADCSRA |=  ( 1 << ADCSRA_ADATE);

        SFIOR |= (ADC_TIMER0_OVERFLOW << SFIOR_ADTS0); //Bits contain 100
        Local_u8_ErrorFlag = ES_OK;
        break;

        case ADC_TIMER_COMPARE_MATCH_B: 
        //Setting ADATE bit
        ADCSRA |=  ( 1 << ADCSRA_ADATE);

        SFIOR |= (ADC_TIMER_COMPARE_MATCH_B << SFIOR_ADTS0); //Bits contain 101
        Local_u8_ErrorFlag = ES_OK;
        break;

        case ADC_TIMER1_OVERFLOW: 
        //Setting ADATE bit
        ADCSRA |=  ( 1 << ADCSRA_ADATE);

        SFIOR |= (ADC_TIMER1_OVERFLOW << SFIOR_ADTS0); //Bits contain 110
        Local_u8_ErrorFlag = ES_OK;
        break;

        case ADC_TIMER1_CAPTURE_EVENT: 
        //Setting ADATE bit
        ADCSRA |=  ( 1 << ADCSRA_ADATE);

        SFIOR |= (ADC_TIMER1_CAPTURE_EVENT << SFIOR_ADTS0); //Bits contain 111
        Local_u8_ErrorFlag = ES_OK;
        break;



        default:
        Local_u8_ErrorFlag = ES_OUT_OF_RANGE;
        break;
    }

        
        

    return Local_u8_ErrorFlag;
}

extern ErrorState_t ADC_enu_SetADIF(void)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    ADCSRA |= ( 1 << ADCSRA_ADIF); //Bit contains 1 

    Local_u8_ErrorFlag = ES_OK;
    
    return Local_u8_ErrorFlag;
}

extern ErrorState_t ADC_enu_ClearADIF(void)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    ADCSRA &= ~( 1 << ADCSRA_ADIF); //Bit contains 0 

    Local_u8_ErrorFlag = ES_OK;
    

    return Local_u8_ErrorFlag;
}

extern ErrorState_t ADC_enu_SetADIE(void)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    ADCSRA |= ( 1 << ADCSRA_ADIE); //Bit contains 1 

    Local_u8_ErrorFlag = ES_OK;
    
    return Local_u8_ErrorFlag;
}

extern ErrorState_t ADC_enu_ClearADIE(void)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    ADCSRA &= ~( 1 << ADCSRA_ADIE); //Bit contains 0 

    Local_u8_ErrorFlag = ES_OK;
    

    return Local_u8_ErrorFlag;
}

extern ErrorState_t ADC_enu_ReadADIF(u8* Copy_pu8_Result)
{
    u8 Local_u8_ErrorFlag = ES_NOK;
    
    if(Copy_pu8_Result)
    {
        
        *Copy_pu8_Result = 1 & (ADCSRA >> ADCSRA_ADIF);

        Local_u8_ErrorFlag = ES_OK;
    }   
    else
    {
        Local_u8_ErrorFlag = ES_NULL_POINTER;
    }

    return Local_u8_ErrorFlag;
}

extern  ErrorState_t ADC_enu_ReadADSC(u8* Copy_pu8_Result)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    if(Copy_pu8_Result)
    {
        
        *Copy_pu8_Result = 1 & (ADCSRA >> ADCSRA_ADSC);

        Local_u8_ErrorFlag = ES_OK;
    }   
    else
    {
        Local_u8_ErrorFlag = ES_NULL_POINTER;
    }


    return Local_u8_ErrorFlag; 
}

extern ErrorState_t ADC_enu_ChangePrescalerFactor(u8 Copy_u8_DivisonFactor)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    switch (Copy_u8_DivisonFactor)
    {
        case ADC_PS_2:
        ADCSRA |= (ADC_PS_2 << ADCSRA_ADPS0); //Bits contain 001
        break;
        
        case ADC_PS_4:
        ADCSRA |= (ADC_PS_4 << ADCSRA_ADPS0); //Bits contain 010
        break;
        
        case ADC_PS_8:
        ADCSRA |= (ADC_PS_8 << ADCSRA_ADPS0); //Bits contain 011
        break;
        
        case ADC_PS_16:
        ADCSRA |= (ADC_PS_16 << ADCSRA_ADPS0); //Bits contain 100
        break;
        
        case ADC_PS_32:
        ADCSRA |= (ADC_PS_32 << ADCSRA_ADPS0); //Bits contain 101
        break;
        
        case ADC_PS_64:
        ADCSRA |= (ADC_PS_64 << ADCSRA_ADPS0); //Bits contain 110
        break;

        case ADC_PS_128:
        ADCSRA |= (ADC_PS_128 << ADCSRA_ADPS0); //Bits contain 111
        break;

        default:
        Local_u8_ErrorFlag = ES_OUT_OF_RANGE;
        break;
    };
    return Local_u8_ErrorFlag;
}

extern ErrorState_t ADC_enu_StartConversion(u8 Copy_u8_Channel, u16* Copy_pu16_Result)
{
    u8 Local_u8_Error = ES_NOK;

    if(Copy_pu16_Result)
    {
        //Selecting input Channel
        switch (Copy_u8_Channel)
        {
            case ADC_ADC0:
            break;
            case ADC_ADC1:
            break;
            case ADC_ADC2:
            break;
            case ADC_ADC3:
            break;
            case ADC_ADC4:
            break;
            case ADC_ADC5:
            break;
            case ADC_ADC6:
            break;
            case ADC_ADC7:
            break;
            default:
            Local_u8_Error = ES_OUT_OF_RANGE;
            break;
        }

        //Starts a conversion
        ADCSRA |= ( 1 << ADCSRA_ADSC);
        
        Local_u8_Error = ES_OK;
    }
    else
    {
        Local_u8_Error = ES_NULL_POINTER;
    }
    return;
}

extern ErrorState_t ADC_enu_ReadADCH(u8* Copy_pu8_Result)
{
    u8 Local_u8_ErrorFlag = ES_NOK;


    #if ADC_DATA_ADJUSTMENT == ADC_LEFT_ADJUSTED
    
     #warning "This function returns a huge error due to ADC_DATA_ADJUSTMENT current configuration"
    
    #endif

    if(Copy_pu8_Result)
    {
        *Copy_pu8_Result = ADCH;

        Local_u8_ErrorFlag = ES_OK;
    }
    else
    {
        Local_u8_ErrorFlag = ES_NULL_POINTER;
    }


    return Local_u8_ErrorFlag; 
}

extern ErrorState_t ADC_enu_ReadADCL(u8* Copy_pu8_Result)
{
    u8 Local_u8_ErrorFlag = ES_NOK;

    #if ADC_DATA_ADJUSTMENT == ADC_RIGHT_ADJUSTED
    
     #warning "This function returns a huge error due to ADC_DATA_ADJUSTMENT current configuration"
    
    #endif

    if(Copy_pu8_Result)
    {
        *Copy_pu8_Result = ADCL;

        Local_u8_ErrorFlag = ES_OK;
    }
    else
    {
        Local_u8_ErrorFlag = ES_NULL_POINTER;
    }


    return Local_u8_ErrorFlag; 
}