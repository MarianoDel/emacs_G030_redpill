//----------------------------------------------------
// #### PROYECTO KIRNO REDONDA GSM - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### HARD.H #######################################
//----------------------------------------------------

// Define to prevent recursive inclusion ---------------------------------------
#ifndef HARD_H_
#define HARD_H_


//----------- Defines For Configuration -------------

//----------- Hardware Board Version -------------

//-------- Type of Program ----------------

//-------- Clock Frequency ------------------------------------
#define CLOCK_FREQ_64_MHZ    //ojo modificar a mano system_stm32g0xx.c SystemInit
// #define CLOCK_FREQ_16_MHZ    //ojo modificar a mano system_stm32g0xx.c SystemInit

//-------- End Of Defines For Configuration ------

//GPIOB pin7    Usart1 Rx

//GPIOB pin7    Output
#define PIN1    ((GPIOB->ODR & 0x0080) != 0)
#define PIN1_ON    (GPIOB->BSRR = 0x00000080)
#define PIN1_OFF    (GPIOB->BSRR = 0x00800000)

//GPIOA pin0    NRST

//GPIOA pin8    Input
#define PIN2_IN    ((GPIOA->IDR & 0x0100) == 0)

//GPIOA pin12    LED
#define LED    ((GPIOA->ODR & 0x1000) != 0)
#define LED_ON    (GPIOA->BSRR = 0x00001000)
#define LED_OFF    (GPIOA->BSRR = 0x10000000)

//GPIOA pin13    SWDIO

//GPIOB pin5 
#define PB5_PB6    ((GPIOB->ODR & 0x0020) != 0)
#define PB5_PB6_ON    (GPIOB->BSRR = 0x00000020)
#define PB5_PB6_OFF    (GPIOB->BSRR = 0x00200000)

//GPIOB pin6    Usart1 Tx
// #define PB5_PB6    ((GPIOB->ODR & 0x0040) != 0)
// #define PB5_PB6_ON    (GPIOB->BSRR = 0x00000040)
// #define PB5_PB6_OFF    (GPIOB->BSRR = 0x00400000)



//GPIOA pin4
// #define NETLIGHT	((GPIOA->IDR & 0x0010) != 0)



// Exported Constants  ---------------------------------------------------------


// Exported Types --------------------------------------------------------------


//--- Stringtify Utils -----------------------
#define str_macro(s) #s


// Module Exported Functions ---------------------------------------------------

#endif /* HARD_H_ */
