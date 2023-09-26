#ifndef EXTI_PRIVATE_FILE
#define EXTI_PRIVATE_FILE

//Registers Addresses
#define MCUCR                       *(volatile u8*)(0x55)
#define MCUCSR                      *(volatile u8*)(0x54)
#define GICR                        *(volatile u8*)(0x5B)
#define GIFR                        *(volatile u8*)(0x5A)

//Control Bits
#define EXTI_MCUCR_ISC00    0
#define EXTI_MCUCR_ISC01    1
#define EXTI_MCUCR_ISC10    2
#define EXTI_MCUCR_ISC11    3
#define EXTI_MCUSCR_ISC2    6

