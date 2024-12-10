/**
 * UART Mirror Characters - Callback Example Driver File
 * 
 * @file uart-example.c
 * 
 * @addtogroup uart-example
 * 
 * @brief This is the generated example implementation for the UART Mirroring Characters - Callback driver.
 *
 * @version UART Mirror Characters - Callback Example Version 1.0.0
*/
/*
� [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

/* Use Case 4 - Callback implementation. Copy this code to your project source, e.g., to main.c  */
/* ------------------------------------------------------------------
#include "mcc_generated_files/system/system.h"
#include <string.h>

void UART_echoCharacters(void);

void UART_FramingErrorCallback(void);
void UART_OverrunErrorCallback(void);

void UART_FramingErrorCallback(void)
{
     (void)printf("UART Framing Error Occurred.\r\n");
}

void UART_OverrunErrorCallback(void)
{
     (void)printf("UART Buffer Overrun Error Occurred.\r\n");
}
void UART_echoCharacters(void)
{
    uint8_t serialCOMRxdByte;  
    serialCOMRxdByte = UART.Read();
    UART.Write(serialCOMRxdByte);     
}

int main(void)
{
    SYSTEM_Initialize();
    UART.FramingErrorCallbackRegister(&UART_FramingErrorCallback);
    UART.OverrunErrorCallbackRegister(&UART_OverrunErrorCallback);
    UART.RxCompleteCallbackRegister(&UART_echoCharacters);
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    (void) printf("Hello World!\r\n");
    (void) printf("Type characters in the terminal, to have them echoed back ...\r\n");
    
    while(1)
    {
        ;
    }
}
------------------------------------------------------------------ */
/**
 End of File
*/
