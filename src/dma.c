//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### DMA.C #################################
//---------------------------------------------

#include "dma.h"
#include "stm32g0xx.h"

#include "adc.h"


/* Externals variables ---------------------------------------------------------*/
extern volatile unsigned short adc_ch [];

/* Global variables ---------------------------------------------------------*/


/* Module Definitions ---------------------------------------------------------*/


/* Module functions ---------------------------------------------------------*/
void DMAConfig(void)
{
    /* DMA1 clock enable */
    if (!RCC_DMA_CLK)
        RCC_DMA_CLK_ON;

    //Configuro el control del DMA CH1
    DMA1_Channel1->CCR = 0;
    //priority very high
    //memory halfword
    //peripheral halfword
    //increment memory
    DMA1_Channel1->CCR |= DMA_CCR_PL | DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0 | DMA_CCR_MINC;
    //DMA1_Channel1->CCR |= DMA_Mode_Circular | DMA_CCR_TCIE;
    //cicular mode
    DMA1_Channel1->CCR |= DMA_CCR_CIRC;

    //Tamano del buffer a transmitir
    DMA1_Channel1->CNDTR = ADC_CHANNEL_QUANTITY;

    //Address del periferico
    DMA1_Channel1->CPAR = (uint32_t) &ADC1->DR;

    //Address en memoria
    DMA1_Channel1->CMAR = (uint32_t) &adc_ch[0];

    //Mapeo los request del periferico al channel del dma en DMAMUX
    //ch0 de dmamux = ch1 de dma
    DMAMUX1_Channel0->CCR |= DMAMUX_CxCR_DMAREQ_ID_2 | DMAMUX_CxCR_DMAREQ_ID_0;

    //Enable
    //DMA1_Channel1->CCR |= DMA_CCR_EN;
#ifdef DMA_WITH_INTERRUPT
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);
    NVIC_SetPriority(DMA1_Channel1_IRQn, 5);
#endif
}


#ifdef DMA_WITH_INTERRUPT
void DMAEnableInterrupt (void)
{
    DMA1_Channel1->CCR |= DMA_CCR_TCIE;
}


void DMADisableInterrupt (void)
{
    DMA1_Channel1->CCR &= ~DMA_CCR_TCIE;
}


void DMA1_Channel1_IRQHandler (void)
{
    if (sequence_ready)
    {
        // Clear DMA TC flag
        sequence_ready_reset;

        // if (LED)
        //     LED_OFF;
        // else
        //     LED_ON;
    }
}
#endif

//---- end of file ----//
