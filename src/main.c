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

// #include "core_cm0.h"
#include "adc.h"
// #include "dma.h"
#include "flash_program.h"

// #include "sim900_800.h"
// #include "funcs_gsm.h"
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

// --- To or from timers ------------------------------

// volatile unsigned short timer_standby = 0;
// volatile unsigned short timer_prender_ringing = 0;
// volatile unsigned short tcp_kalive_timer;
// //volatile unsigned char display_timer;
// volatile unsigned char timer_meas;




// Module Private Functions ----------------------------------------------------
void TimingDelay_Decrement(void);
// void Wait_ms (unsigned short);


//-------------------------------------------//
// @brief  Main program.
// @param  None
// @retval None
//------------------------------------------//
int main(void)
{
    // char s_lcd [100];

    //GPIO Configuration.
    GPIO_Config();

    //ACTIVAR SYSTICK TIMER
#ifdef CLOCK_FREQ_64_MHZ
    if (SysTick_Config(64000))
#endif
#ifdef CLOCK_FREQ_16_MHZ
    if (SysTick_Config(16000))
#endif
    {
        while (1)	/* Capture error */
        {
            if (LED)
                LED_OFF;
            else
                LED_ON;

            for (unsigned char i = 0; i < 255; i++)
            {
                asm (	"nop \n\t"
                        "nop \n\t"
                        "nop \n\t" );
            }
        }
    }


    //--- Welcome code ---//
    // TF_Led();
    // TF_Usart1_Multiple();
    // TF_Usart1_TxRx();
    // TF_Usart1_Adc();
    // TF_Usart1_Adc_Int();
    // TF_Usart1_Adc_Dma();
    // TF_Usart2_Single();
    // TF_Usart2_Multiple();
    // TF_Tim3_Pwm();
    // TF_Usart1_Flash_Empty_Page ();
    TF_Usart1_Flash_Write_Data ();
    
    return 0;
}

//--- End of Main ---//

// void Wait_ms (unsigned short wait)
// {
//     wait_ms_var = wait;
//     while (wait_ms_var);
// }


void TimingDelay_Decrement(void)
{
    if (wait_ms_var)
        wait_ms_var--;

}

//--- end of file ---//

