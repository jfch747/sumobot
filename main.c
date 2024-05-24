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
#define FCY 8000000
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/tmr2.h"
#include "mcc_generated_files/oc4.h"
#include "mcc_generated_files/oc2.h"
#include "mcc_generated_files/adc1.h"
#include "mcc_generated_files/uart1.h"
#include <math.h>
#include "lcd.h"
#include "mcc_generated_files/tmr1.h"
#include <libpic30.h>


void system_init() {
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0000;
    LATB = 0x0000;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0x001F;
    TRISB = 0x0000;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPU1 = 0x0000;
    CNPU2 = 0x0000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    //AD1PCFG = 0x0E3C;
    AD1PCFG = 0xFFFF;

}

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    
    SYSTEM_Initialize();
    system_init();
    int in_b = 0;
    int a = 0;
    TMR2_Start();
    UART1_Initialize();
    OC4_Start();
    OC2_Start();
    int LCD_AUXILIAR=0;
    char face[] = ":3";
    #define Trig LATBbits.LATB7
    #define pin_echo PORTAbits.RA2
    //NO USAR RB14, RB13, RB11, RB10

    LCD_Initialize(); //Preder, configurar a 4 bits
    DisplayClr(); // borrar lo que tenga la pantalla
    LCDGoto(0, 0); //poner el cursor en la posicion inicial
    
    
    
    while (1)
    {
        // motor 1
        OC4RS = 0xFFFF; 
        // motor 2
        OC2RS = 0xFFFF;  
      
        if (UART1_IsRxReady()){
            a = U1RXREG;
            in_b = 1;
        }
        
        if (in_b == 1){
            //inicializacion LCD
            LCD_PORT = LCD_AUXILIAR;
            LCDPutStr(face); //NO USAR RB14, RB13, RB11, RB10
            /*uint16_t distancia = 0;
            uint16_t duracion = 0;
            uint16_t t1 = 0;
            
            AD1PCFGbits.PCFG2 = 1;  // Set RA2 (AN2) to digital
            AD1PCFGbits.PCFG9 = 1;  // Set RB7 (AN9) to digital
            TRISAbits.TRISA2 = 1;  // Set RA2 as input
            TRISBbits.TRISB7 = 0;  // Set RB7 as output
            uint16_t D = 0;
            
            Trig = 1;
            __delay_us(10);
            Trig = 0;
            //__delay_us(10);
            while (pin_echo == 0){
                TMR1_Start();
            }
            while (pin_echo == 1){
                TMR1_Stop();
                t1 = TMR1;
                duracion = t1/2; 
            }
                     
            if (duracion <= 23200){
                D = 1;
            } 
            if ((D == 0)||(L_aux < 500)){
                OC4R = 0x9998;
                OC2R = 0x1;
                //buscando
            }
            else if ((D == 1)&&(L_aux > 500)){
                OC4R = 0xE664;
                OC2R = 0xE664;
                //empujando
            }         */

            uint16_t D = ADC1_GetConversion(channel_IRD);
            uint16_t L = ADC1_GetConversion(channel_IRL);
            uint16_t D_aux = (int)(65535*((float)D))/100;
            uint16_t L_aux = (int)(65535*((float)L))/100;
            
            if ((D_aux > 500)||(L_aux < 500)){
                OC4R = 0x9998;
                OC2R = 0x1;
                //buscando
            }
            else if ((D_aux < 500)&&(L_aux > 500)){
                OC4R = 0xE664;
                OC2R = 0xE664;
                //empujando
            }
        }
        
        else {
            OC4R = 0x1;
            OC2R = 0x1;
        }
    }
    return 1;
}
/**
 End of File
*/

