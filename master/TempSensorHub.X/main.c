 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
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
#include "mcc_generated_files/system/system.h"  // Include the master header file generated by MCC
#include <stdio.h>
#include "mcc_generated_files/system/system.h"
#include <string.h>

#define STRAP_PIN      PORTAbits.RA0
#define DEBUG

// Function declarations
void SPI_Write(uint16_t);
uint16_t SPI_Read(void);
void UART_SendChar(uint8_t);
uint8_t UART_ReceiveChar(void);
void TMP122_Init();
void putch(char);
uint16_t read_temperature();
void Error_Handler(char *);

// Function implementations

void SPI_Write(uint16_t data) {
    uint8_t buffer[2]; 
    buffer[0] = (data >> 8) & 0xFF; // High byte 
    buffer[1] = data & 0xFF; // Low byte 
    SPI1_BufferExchange(buffer, 2); // Send the buffer }
}

uint16_t SPI_Read(void) {
    uint8_t buffer[2]; 
    buffer[0] = 0x12;
    buffer[1] = 0x34;
    uint16_t data; 
    SPI1_BufferExchange(buffer, 2); // Receive the buffer 
    if (buffer == 0xFFFF) {
        Error_Handler("SPI Read Error");
    }
    data = (buffer[0] << 8) | buffer[1]; // Combine high and low bytes 
    return data;
}

void UART2_SendChar(uint8_t data) {
    while (!UART2_IsTxReady());
    EUSART2_Write(data);
}

// Function to send a string via UART2
void UART2_SendString(const char* str) {
    while (*str != '\0') {        // While we haven't reached the end of the string
        UART2_SendChar(*str);      // Send each character
        str++;                     // Move to the next character
    }
}

void UART_SendChar(uint8_t data) {
    while (!UART1_IsTxReady());
    EUSART1_Write(data);
}

uint8_t UART_ReceiveChar(void) {
    while (!UART1__IsRxReady());
    return EUSART1_Read();
}

void putch(char data) {
    while (!EUSART2_IsTxReady());
    EUSART2_Write(data);
}

void TMP122_Init(void) {
    SPI_Write(0x0000);  // Initialize TMP122
}

uint16_t read_temperature(void) {
    return SPI_Read();  // Read temperature data
}

void Error_Handler(char *message) {
    // Handle error
    printf("Error: %s\n", message);
    while (1);
}



void test1(int loop){
    for( int i=0; i<loop; i++) {
        LATD2 = 1;  // Set RD2 high
        __delay_ms(500);  // Wait for 1 second

        LATD2 = 0;  // Set RD2 lows
        __delay_ms(500);  // Wait for 1 second
    }
}

void UART_WriteString(const char *message)
{
    for(int i = 0; i < (int)strlen(message); i++)
    {
        while(!UART2.IsTxReady())
        {
            ;
        };
        (void) UART2.Write(message[i]);
    }
}

// Define system frequency and baud rate
#define _XTAL_FREQ 12000000  // 8 MHz internal oscillator
#define BAUD_RATE 9600      // Desired baud rate

void main(void) {
    
    SYSTEM_Initialize();  // Initialize the system using MCC
    EUSART2_Enable();
    EUSART2_TransmitEnable();
    TRISAbits.TRISA0 = 1;  // Set STRAP_PIN as input
    ANSA0 = 0; 
    
    

 //   if (STRAP_PIN) {
   if (true) {    
        // Master mode
       
       //set cs as  output
        TRISDbits.TRISD5 = 0;  // Set D5 as output
        LATD5 = 1; //set it to high, cs is not not eable by default
        test1(1);
        UART2_SendString("Mode: master\n\r");
        if (SSP1CON1bits.SSPEN == false)
        {
            SSP1STAT = 0x0;
            SSP1CON1 = 0xa;
            SSP1CON3 = 0x10;
            SSP1ADD  = 0x17;
            SSP1CON1bits.SSPEN = 1;
        }

        uint16_t temperature;  

        while (1) {
            LATD5 = 0; 
            temperature = read_temperature();
            LATD5 = 1; 
            UART_SendChar((temperature >> 8) & 0xFF);  // Send high byte
            UART_SendChar(temperature & 0xFF);  // Send low byte
#ifdef DEBUG
            temperature = temperature >> 7;
            printf("Temperature: %u\n\r", temperature);  // Debugging output
#endif
            __delay_ms(100);  // Delay 1 second
        }
    } else {
        test1(2);
        // Slave mode
        uint8_t high_byte, low_byte;
        uint16_t data;

        while (1) {
            high_byte = UART_ReceiveChar();
            low_byte = UART_ReceiveChar();
            data = (high_byte << 8) | low_byte;  // Combine high and low bytes
            SPI_Write(data);  // Send data via SPI
            printf("Received data: %u\n", data);  // Debugging output
        }
    }
}
