//------------------------------------------------
// #### PROYECTO KIRNO REDPILL - Custom Board ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### MAIN.C ###################################
//------------------------------------------------

// Includes --------------------------------------------------------------------
#include "stm32g0xx.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gpio.h"
#include "it.h"
#include "tim.h"
// #include "usart.h"
#include "hard.h"
#include "adc.h"
// #include "dma.h"
#include "flash_program.h"

#include "test_functions.h"



// Externals -------------------------------------------------------------------
// --- To or from timers ------------------------------
volatile unsigned short wait_ms_var = 0;

// --- To or from usart ------------------------------
volatile unsigned char usart1_have_data = 0;
volatile unsigned char usart2_have_data = 0;

// --- For the ADC ------------------------------
volatile unsigned short adc_ch [ADC_CHANNEL_QUANTITY];
volatile unsigned char adc_int_seq_ready = 0;


parameters_typedef __attribute__ ((section("memParams"))) const parameters_constants =
{
    .num_reportar = "12345678",
    .imei = "0000"
};


// Globals ---------------------------------------------------------------------


// Module Private Functions ----------------------------------------------------
void TimingDelay_Decrement(void);
void SysTickError (void);


//-------------------------------------------//
// @brief  Main program.
// @param  None
// @retval None
//------------------------------------------//
int main(void)
{
    //GPIO Configuration.
    GPIO_Config();

    //Start the SysTick Timer
#ifdef CLOCK_FREQ_64_MHZ
    if (SysTick_Config(64000))
        SysTickError();
#endif
#ifdef CLOCK_FREQ_48_MHZ
    if (SysTick_Config(48000))
        SysTickError();
#endif
#ifdef CLOCK_FREQ_16_MHZ
    if (SysTick_Config(16000))
        SysTickError();
#endif

    //--- Hardware Tests Functions ---
    TF_Hardware_Tests ();
    
    return 0;
}

//--- End of Main ---//

void TimingDelay_Decrement(void)
{
    if (wait_ms_var)
        wait_ms_var--;

}


void SysTickError (void)
{
    //Capture systick error...
    while (1)
    {
        if (LED)
            LED_OFF;
        else
            LED_ON;

        for (unsigned char i = 0; i < 255; i++)
        {
            asm ("nop \n\t"
                 "nop \n\t"
                 "nop \n\t" );
        }
    }
}


//--- end of file ---//
