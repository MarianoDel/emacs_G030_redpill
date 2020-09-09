//------------------------------------------------
// ## Internal Test Functions Module
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### TEST_FUNCTIONS.C #########################
//------------------------------------------------

// Includes --------------------------------------------------------------------
#include "test_functions.h"
#include "stm32g0xx.h"
#include "hard.h"
#include "tim.h"
#include "usart.h"
#include "adc.h"
#include "dma.h"

#include <stdio.h>



// Externals -------------------------------------------------------------------
extern volatile unsigned char usart1_have_data;
extern volatile unsigned char usart2_have_data;
extern volatile unsigned char adc_int_seq_ready;
extern volatile unsigned short adc_ch [];

// Globals ---------------------------------------------------------------------


// Module Private Types & Macros -----------------------------------------------


// Module Private Functions ----------------------------------------------------


// Module Functions ------------------------------------------------------------
void TF_Led (void)
{
    while (1)
    {
        if (LED)
            LED_OFF;
        else
            LED_ON;

        Wait_ms(300);
    }
}


void TF_Gpio_Input (void)
{
    while (1)
    {
        if (PIN2_IN)
            PIN1_ON;
        else
            PIN1_OFF;

        Wait_ms(100);
    }
}


//PB5 & PB6 are in the same pin
void TF_Gpio_Share_Outputs (void)
{
    while (1)
    {
        if (LED)
        {
            PB5_PB6_ON;
            LED_OFF;
        }
        else
        {
            PB5_PB6_OFF;
            LED_ON;
        }

        Wait_ms(300);
    }
}


void TF_Usart1_Single (void)
{
    Usart1Config();

    while (1)
    {
        Usart1SendSingle('M');
        Wait_ms(1000);

        if (LED)
            LED_OFF;
        else
            LED_ON;
    }
}


void TF_Usart1_Multiple (void)
{
    for (unsigned char i = 0; i < 5; i++)
    {
        LED_ON;
        Wait_ms(250);
        LED_OFF;
        Wait_ms(250);
    }
    
    Usart1Config();

    while (1)
    {
        Usart1Send("Mariano\n");
        Wait_ms(1000);

        if (LED)
            LED_OFF;
        else
            LED_ON;
    }
}


void TF_Usart1_TxRx (void)
{
    for (unsigned char i = 0; i < 5; i++)
    {
        LED_ON;
        Wait_ms(250);
        LED_OFF;
        Wait_ms(250);
    }
    
    Usart1Config();

    char s_to_send [100] = { 0 };
    Usart1Send("Ready to test...\n");
    while (1)
    {
        if (usart1_have_data)
        {
            usart1_have_data = 0;
            
            if (LED)
                LED_OFF;
            else
                LED_ON;
            
            Usart1ReadBuffer((unsigned char *) s_to_send, 100);
            Wait_ms(1000);
            Usart1Send(s_to_send);
        }
    }
}


void TF_Usart1_Adc (void)
{
    for (unsigned char i = 0; i < 5; i++)
    {
        LED_ON;
        Wait_ms(250);
        LED_OFF;
        Wait_ms(250);
    }
    
    Usart1Config();
    AdcConfig();

    unsigned short adc_sample = 0;
    unsigned char cntr = 0;
    char s_to_send [100] = { 0 };
    Usart1Send("\nTesting ADC...\n");
    while (1)
    {
        Wait_ms(1000);
        adc_sample = ReadADC1_SameSampleTime (ADC_Channel_8);
        sprintf(s_to_send, "index: %d sample: %d\n", cntr, adc_sample);
        Usart1Send(s_to_send);
        cntr++;

        if (LED)
            LED_OFF;
        else
            LED_ON;

    }
}


void TF_Usart1_Adc_Int (void)
{
    for (unsigned char i = 0; i < 5; i++)
    {
        LED_ON;
        Wait_ms(250);
        LED_OFF;
        Wait_ms(250);
    }
    
    Usart1Config();
    AdcConfig();

    unsigned short cntr = 0;
    char s_to_send [100] = { 0 };
    Usart1Send("\nTesting ADC with ints...\n");

    // Start the conversion
    ADC1->CR |= (uint32_t)ADC_CR_ADSTART;

    while (1)
    {
        if (adc_int_seq_ready)
        {
            adc_int_seq_ready = 0;
            if (cntr < 10000)
                cntr++;
            else
            {
                sprintf(s_to_send, "index: %d sample: %d\n", cntr, adc_ch[0]);
                Usart1Send(s_to_send);
                cntr = 0;
            }
        }
    }
}


void TF_Usart1_Adc_Dma (void)
{
    for (unsigned char i = 0; i < 5; i++)
    {
        LED_ON;
        Wait_ms(250);
        LED_OFF;
        Wait_ms(250);
    }
    
    Usart1Config();

    //-- ADC Init
    AdcConfig();

    //-- DMA configuration and Init
    DMAConfig();
    DMA1_Channel1->CCR |= DMA_CCR_EN;

    ADC1->CR |= ADC_CR_ADSTART;


    unsigned short cntr = 0;
    char s_to_send [100] = { 0 };
    Usart1Send("\nTesting ADC with dma transfers...\n");
    // DMAEnableInterrupt();

    while (1)
    {
        if (sequence_ready)
        {
            sequence_ready_reset;
            if (cntr < 10000)
                cntr++;
            else
            {
                sprintf(s_to_send, "index: %d sample: %d\n", cntr, adc_ch[0]);
                Usart1Send(s_to_send);
                cntr = 0;
            }
        }            
    }
}


void TF_Usart2_Single (void)
{
    Usart2Config();

    while (1)
    {
        Usart2SendSingle('M');
        Wait_ms(1000);

        if (LED)
            LED_OFF;
        else
            LED_ON;
    }
}


void TF_Usart2_Multiple (void)
{
    for (unsigned char i = 0; i < 5; i++)
    {
        LED_ON;
        Wait_ms(250);
        LED_OFF;
        Wait_ms(250);
    }
    
    Usart2Config();

    while (1)
    {
        Usart2Send("Mariano\n");
        Wait_ms(1000);

        if (LED)
            LED_OFF;
        else
            LED_ON;
    }
}


//--- end of file ---//
