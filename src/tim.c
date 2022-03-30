//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32G030
// ##
// #### TIM.C ################################
//---------------------------------------------

// Includes --------------------------------------------------------------------
#include "tim.h"
#include "stm32g0xx.h"
#include "hard.h"


// Module Types Constants and Macros -------------------------------------------
#define RCC_TIM1_CLK    (RCC->APBENR2 & 0x00000800)
#define RCC_TIM1_CLK_ON    (RCC->APBENR2 |= 0x00000800)
#define RCC_TIM1_CLK_OFF    (RCC->APBENR2 &= ~0x00000800)

#define RCC_TIM3_CLK    (RCC->APBENR1 & 0x00000002)
#define RCC_TIM3_CLK_ON    (RCC->APBENR1 |= 0x00000002)
#define RCC_TIM3_CLK_OFF    (RCC->APBENR1 &= ~0x00000002)

#define RCC_TIM6_CLK    (RCC->APBENR1 & 0x00000010)
#define RCC_TIM6_CLK_ON    (RCC->APBENR1 |= 0x00000010)
#define RCC_TIM6_CLK_OFF    (RCC->APBENR1 &= ~0x00000010)

#define RCC_TIM7_CLK    (RCC->APBENR1 & 0x00000020)
#define RCC_TIM7_CLK_ON    (RCC->APBENR1 |= 0x00000020)
#define RCC_TIM7_CLK_OFF    (RCC->APBENR1 &= ~0x00000020)

#define RCC_TIM14_CLK    (RCC->APBENR2 & 0x00008000)
#define RCC_TIM14_CLK_ON    (RCC->APBENR2 |= 0x00008000)
#define RCC_TIM14_CLK_OFF    (RCC->APBENR2 &= ~0x00008000)

#define RCC_TIM15_CLK    (RCC->APBENR2 & 0x00010000)
#define RCC_TIM15_CLK_ON    (RCC->APBENR2 |= 0x00010000)
#define RCC_TIM15_CLK_OFF    (RCC->APBENR2 &= ~0x00010000)

#define RCC_TIM16_CLK    (RCC->APBENR2 & 0x00020000)
#define RCC_TIM16_CLK_ON    (RCC->APBENR2 |= 0x00020000)
#define RCC_TIM16_CLK_OFF    (RCC->APBENR2 &= ~0x00020000)

#define RCC_TIM17_CLK    (RCC->APBENR2 & 0x00040000)
#define RCC_TIM17_CLK_ON    (RCC->APBENR2 |= 0x00040000)
#define RCC_TIM17_CLK_OFF    (RCC->APBENR2 &= ~0x00040000)


// Externals -------------------------------------------------------------------
// extern volatile unsigned char timer_1seg;
// extern volatile unsigned short timer_led_comm;
extern volatile unsigned short wait_ms_var;


// Globals ---------------------------------------------------------------------
// volatile unsigned short timer_1000 = 0;


// Module Private Functions ----------------------------------------------------


// Module Functions ------------------------------------------------------------
void Update_TIM1_CH3 (unsigned short a)
{
    TIM1->CCR3 = a;
}


// void Update_TIM3_CH1 (unsigned short a)
// {
//     TIM3->CCR1 = a;
// }

// void Update_TIM3_CH2 (unsigned short a)
// {
//     TIM3->CCR2 = a;
// }

void Update_TIM3_CH3 (unsigned short a)
{
    TIM3->CCR3 = a;
}

// void Update_TIM3_CH4 (unsigned short a)
// {
//     TIM3->CCR4 = a;
// }

void Wait_ms (unsigned short wait)
{
    wait_ms_var = wait;
    while (wait_ms_var);
}

//-------------------------------------------//
// @brief  TIM configure.
// @param  None
// @retval None
//------------------------------------------//
void TIM3_IRQHandler (void)	//1 ms
{
    if (TIM3->SR & 0x01)	//bajo el flag
        TIM3->SR = 0x00;
}


void TIM_1_Init (void)
{
    unsigned long temp;

    if (!RCC_TIM1_CLK)
        RCC_TIM1_CLK_ON;

    //Configuracion del timer.
    TIM1->CR1 = 0x00;		//clk int / 1; upcounting
    // TIM1->CR2 |= TIM_CR2_MMS_1;		//UEV -> TRG0

    TIM1->SMCR = 0x0000;
    // TIM1->CCMR1 = 0x0060;    //CH1 output PWM mode 1 (channel active TIM1->CNT < TIM1->CCR1)
    TIM1->CCMR2 = 0x0060;    //CH3 output PWM mode 1 (channel active TIM1->CNT < TIM1->CCR1)
    
    TIM1->CCER |= TIM_CCER_CC3E;    //CH3 enable on pin direct polarity

    TIM1->BDTR |= TIM_BDTR_MOE;
    
    TIM1->ARR = 600;    // 80khz on 48MHz
    TIM1->CNT = 0;

    TIM1->PSC = 0;

    //Alternate Fuction Pin Configurations
    temp = GPIOB->AFR[0];
    temp &= 0xF0FFFFFF;    
    temp |= 0x01000000;    //PB6 -> AF1
    GPIOB->AFR[0] = temp;

    // Enable timer interrupt ver UDIS
    // TIM1->DIER |= TIM_DIER_UIE;
    // NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
    // NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 1);
    
    TIM1->CR1 |= TIM_CR1_CEN;
}


void TIM_3_Init (void)
{
    if (!RCC_TIM3_CLK)
        RCC_TIM3_CLK_ON;

    //Configuracion del timer.
    TIM3->CR1 = 0x00;		//clk int / 1; upcounting
    // TIM3->CR2 |= TIM_CR2_MMS_1;		//UEV -> TRG0
//	TIM3->CCMR2 = 0x7070;			//CH4 y CH3 output PWM mode 2
    // TIM3->CCMR1 = 0x0060;			//CH1 PWM mode 2
    TIM3->CCMR2 = 0x0060;        //CH3 PWM mode 2
    TIM3->CCER |= TIM_CCER_CC3E;        //CH3 enable on pin

    // TIM3->ARR = 1000;        //64MHz / 1000
    TIM3->ARR = 21;        // 48MHz / 22
    TIM3->CNT = 0;
    TIM3->PSC = 0;
    // TIM3->PSC = 11;

    //TIM3->EGR = TIM_EGR_UG;

    // Enable timer ver UDIS
    //TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CR1 |= TIM_CR1_CEN;

    //Alternative pin config.
    //Alternate Fuction
    unsigned int temp;
    temp = GPIOB->AFR[0];
    temp &= 0xFFFFFFF0;
    temp |= 0x00000001;    //PB0 -> AF1
    GPIOB->AFR[0] = temp;

}

// void TIM_6_Init (void)
// {
//     if (!RCC_TIM6_CLK)
//         RCC_TIM6_CLK_ON;

//     //Configuracion del timer.
//     TIM6->CR1 = 0x00;		//clk int / 1; upcounting
//     TIM6->PSC = 47;			//tick cada 1us
//     TIM6->ARR = 0xFFFF;			//para que arranque
//     //TIM6->CR1 |= TIM_CR1_CEN;
// }

// void TIM14_IRQHandler (void)	//100uS
// {
//     if (TIM14->SR & 0x01)
//         TIM14->SR = 0x00;
// }


// void TIM_14_Init (void)
// {

//     //NVIC_InitTypeDef NVIC_InitStructure;

//     if (!RCC_TIM14_CLK)
//         RCC_TIM14_CLK_ON;

//     /*
//     //Configuracion del timer.
//     TIM14->ARR = 2000; //10m
//     TIM14->CNT = 0;
//     TIM14->PSC = 479;
//     TIM14->EGR = TIM_EGR_UG;

//     // Enable timer ver UDIS
//     TIM14->DIER |= TIM_DIER_UIE;
//     TIM14->CR1 |= TIM_CR1_CEN;

//     NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn;
//     NVIC_InitStructure.NVIC_IRQChannelPriority = 5;
//     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//     NVIC_Init(&NVIC_InitStructure);
//     */

//     //Configuracion del timer.
//     TIM14->CR1 = 0x00;		//clk int / 1; upcounting; uev
//     TIM14->PSC = 47;			//tick cada 1us
//     TIM14->ARR = 0xFFFF;			//para que arranque
//     TIM14->EGR |= 0x0001;
// }

// void TIM16_IRQHandler (void)	//es one shoot
// {
//     if (TIM16->SR & 0x01)
//         TIM16->SR = 0x00;
// }


// void TIM_16_Init (void)
// {
//     if (!RCC_TIM16_CLK)
//         RCC_TIM16_CLK_ON;

//     //Configuracion del timer.
//     TIM16->CR1 = 0x00;		//clk int / 1; upcounting; uev
//     TIM16->ARR = 0xFFFF;
//     TIM16->CNT = 0;
//     //TIM16->PSC = 7999;	//tick 1ms
//     //TIM16->PSC = 799;	//tick 100us
//     TIM16->PSC = 47;			//tick 1us
//     TIM16->EGR = TIM_EGR_UG;

//     // Enable timer ver UDIS
//     //	TIM16->DIER |= TIM_DIER_UIE;
//     //	TIM16->CR1 |= TIM_CR1_CEN;
// }

// void OneShootTIM16 (unsigned short a)
// {
//     TIM16->ARR = a;
//     TIM16->CR1 |= TIM_CR1_CEN;
// }

// void TIM16Enable (void)
// {
//     TIM16->CR1 |= TIM_CR1_CEN;
// }

// void TIM16Disable (void)
// {
//     TIM16->CR1 &= ~TIM_CR1_CEN;
// }


// void TIM17_IRQHandler (void)	//200uS
// {
//     if (TIM17->SR & 0x01)
//         TIM17->SR = 0x00;		//bajar flag
// }


// void TIM_17_Init (void)
// {
//     if (!RCC_TIM17_CLK)
//         RCC_TIM17_CLK_ON;

//     //Configuracion del timer.
//     TIM17->ARR = 400;		//400us
//     TIM17->CNT = 0;
//     TIM17->PSC = 47;

//     // Enable timer interrupt ver UDIS
//     TIM17->DIER |= TIM_DIER_UIE;
//     TIM17->CR1 |= TIM_CR1_URS | TIM_CR1_CEN;	//solo int cuando hay overflow y one shot

//     NVIC_EnableIRQ(TIM17_IRQn);
//     NVIC_SetPriority(TIM17_IRQn, 8);
// }

//--- end of file ---//
