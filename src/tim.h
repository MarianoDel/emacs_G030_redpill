//---------------------------------------------
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32G030
// ##
// #### TIM.H ################################
//---------------------------------------------

// Prevent recursive inclusion -------------------------------------------------
#ifndef __TIM_H
#define __TIM_H

// Module Exported Types Constants and Macros ----------------------------------


// Module Exported Functions ---------------------------------------------------
void TIM_1_Init(void);
// void TIM3_IRQHandler (void);
void TIM_3_Init(void);
// void TIM_6_Init (void);
// void TIM14_IRQHandler (void);
// void TIM_14_Init(void);
// void TIM16_IRQHandler (void);
// void TIM_16_Init(void);
// void TIM17_IRQHandler (void);
// void TIM_17_Init(void);
void Update_TIM1_CH3 (unsigned short);
// void Update_TIM3_CH1 (unsigned short);
// void Update_TIM3_CH2 (unsigned short);
void Update_TIM3_CH3 (unsigned short);
// void Update_TIM3_CH4 (unsigned short);

// void OneShootTIM16 (unsigned short);
// void TIM16Enable (void);
// void TIM16Disable (void);

void Wait_ms (unsigned short wait);

#endif    /* __TIM_H */

//--- end of file ---//
