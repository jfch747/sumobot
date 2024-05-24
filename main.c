/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.4
        Device            :  PIC24FJ64GB002
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB 	          :  MPLAB X v6.05
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/tmr2.h"
#include "mcc_generated_files/oc4.h"
#include "mcc_generated_files/adc1.h"
#include "mcc_generated_files/uart1.h"
#include <math.h>

/*void TMR2_CallBack(void){
    // motor 1
    OC1RS = 0xFFFF; 
    OC1R = 0xEFFF;
    // motor 2
    OC2RS = 0xFFFF;  
    OC2R = 0xEFFF;
}*/

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    
    SYSTEM_Initialize();
    
    int in_b = 0;
    int a = 0;
    TMR2_Start();
    UART1_Initialize();
    OC4_Start();
    OC2_Start();

    
    while (1)
    {
        // motor 1
        OC4RS = 0xFFFF; 
        //OC4R = 0xE664;
        // motor 2
        OC2RS = 0xFFFF;  
        //OC2R = 0xE664; 
        
        //UART1_RX_DATA_AVAILABLE
        
        if (UART1_IsRxReady()){
            a = U1RXREG;
            in_b = 1;
        }
        
        if (in_b == 1){
            uint16_t D = ADC1_GetConversion(channel_IRD);
            uint16_t L = ADC1_GetConversion(channel_IRL);
            uint16_t D_aux = (int)(65535*((float)D))/100;
            uint16_t L_aux = (int)(65535*((float)D))/100;
            
            if ((D_aux > 500)||(L_aux < 500)){
                OC4R = 0x9998;
                OC2R = 0x1;
            }
            else if ((D_aux < 500)&&(L_aux > 500)){
                
                OC4R = 0xE664;
                OC2R = 0xE664;
            }
            
        }
        
        else {
            OC4R = 0x1;
            OC2R = 0x1;
        }
        
        /*if (in_b == 1){
            if ( (D < 500) && ( L => 500) ){
            // motor 1
            OC4RS = 0xFFFF; 
            OC4R = 0xEFFF;
            // motor 2
            OC2RS = 0xFFFF;  
            OC2R = 0xEFFF;
            }
            else if ((D => 500) || (L <= 500) ){
                //motor 1
                OC4RS = 0xFFFF; 
                OC4R = 0xFFFF;
                // motor 2
                OC2RS = 0xFFFF;  
                OC2R = 0xEFFF;
            }
        }  */
    }

    return 1;
}
/**
 End of File
*/

