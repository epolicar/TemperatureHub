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
#include <string.h>

#define STRAP_PIN     PB_PORT // Pin = hi -> master 
#define TIME_TO_READ  100           // time between reading sensor 
#define TICK_THRESHOLD 10 // Define an appropriate threshold for ticks
#define DEFAULT_TEMPERATURE 0x0019 // 25 degC
#define DEBUG

volatile uint16_t tick_counter = 0; // Timer tick count 

// Function declarations
void SPI_Write(uint16_t);
uint16_t SPI_Read(void);
void UART_SendChar(uint8_t);
uint8_t UART_ReceiveChar(void);
void TMP122_Init();
uint16_t read_temperature();
void Error_Handler(char *);
uint8_t high_byte_spi = 0;
uint8_t low_byte_spi = 0;
uint8_t data_ptr = 0;
void reset_counter();
void ticker();
void test1(int);
void UART_WriteString(const char *);
void process_serial_data(void);
void response_to_spi(void);
void uart1_handler(void);

// Function implementations

uint16_t SPI_Read(void) {
//    SDI_SetDigitalInput(); //set RB4 as input											 
    uint8_t buffer[2]; 
    uint16_t data; 
    SPI1_BufferExchange(buffer, 2); // Receive the buffer 
    data = ((uint16_t)buffer[0] << 8) | (uint16_t)buffer[1]; // Combine high and low bytes 
    if (data == 0xFFFF) {
        Error_Handler("SPI Read Error");
    }
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


uint16_t read_temperature(void) {
    return SPI_Read();  // Read temperature data
}

void Error_Handler(char *message) {
    // Handle error
    printf("Error: %s\n", message);
    while (1);
}



void ticker(void){
    tick_counter++; // increment this counter each TMR0 period (1 mS)) in which an interrupt is flagged
    // Interrupt flag cleared automatically in TMR0_ISR()
}

void reset_counter(void) {
    tick_counter = 0;
}

void test1(int loop){
    for( int i=0; i<loop; i++) {
        LATD2 = 1;  // Set RD2 high
        __delay_ms(500);  // Wait for 1 second

        LATD2 = 0;  // Set RD2 lows
        __delay_ms(500);  // Wait for 1 second
    }
}

// Define system frequency and baud rate
#define BAUD_RATE 9600      // Desired baud rate
uint8_t high_byte_serial, low_byte_serial;

#define BUFFER_SIZE 2
typedef struct {
    uint16_t buffer[BUFFER_SIZE];
    volatile uint8_t head;
    volatile uint8_t tail;
    volatile bool full;
} CircularBuffer;

CircularBuffer dataBuffer = { .head = 0, .tail = 0, .full = false };

// Add data to the buffer
void buffer_write(CircularBuffer *buf, uint16_t data) {
    buf->buffer[buf->head] = data;
    
    if (buf->full) {
        buf->tail = (buf->tail + 1) % BUFFER_SIZE;  // Overwrite oldest data
    }

    buf->head = (buf->head + 1) % BUFFER_SIZE;
    buf->full = (buf->head == buf->tail);
}

// Read data from the buffer
bool buffer_read(CircularBuffer *buf, uint16_t *data) {
    if (buf->head == buf->tail && !buf->full) {
        return false;  // Buffer empty
    }

    *data = buf->buffer[buf->tail];
    buf->tail = (buf->tail + 1) % BUFFER_SIZE;
    buf->full = false;
    return true;
}

void uart1_handler(void)
{
    if (tick_counter > TICK_THRESHOLD) {
        high_byte_serial = EUSART1_Read();
    }else {
        low_byte_serial = EUSART1_Read();
        uint16_t data = ((uint16_t)high_byte_serial << 8) | (uint16_t)low_byte_serial;
        buffer_write(&dataBuffer, data);
        //printf("%x\r\n", data);
    }
    tick_counter = 0; //reset the counter
}

void SPI1_OpenMaster(void) {
    SSP1CON1bits.SSPEN = false; //reset SPI
    //Reconfigure to host
    SSP1STAT = 0x64;
    SSP1CON1 = 0x00;
    SSP1CON3 = 0x10;
    SSP1ADD  = 0x01;
	SSP1CON1bits.SSPEN = true; //enable SPI
};

void SPI1_OpenSlave(void) {
    //Reconfigure to slave
    SSP1CON1bits.SSPEN = false; //reset SPI    
    SSP1STAT = 0x64;
    SSP1CON1 = 0x04;
    SSP1CON3 = 0x10;
    SSP1ADD  = 0x00;    
	SSP1CON1bits.SSPEN = true; //enable SPI
	SPI1_Open(0);
};

void main(void) {
    /*
     * SYSTEM_Initialize does the following
     * EUSART1
     * ABDEN disabled; WUE disabled; BRG16 16bit_generator; SCKP Non-Inverted; 
     * BAUD1CON = 0x48; 
     * 
     * ADDEN disabled; CREN enabled -> continuous reception; 
     * SREN disabled; RX9 8-bit; SPEN enabled -> UART enabled
     * RC1STA = 0x90; 
     * 
     * TX9D 0x0; BRGH hi_speed; SENDB sync_break_complete; SYNC asynchronous; 
     * TXEN enabled -> transmission enabled; TX9 8-bit; CSRC client; 
     * TX1STA = 0x26; 
     * 
     * SPBRGL 207; //9600 baud
     * SP1BRGL = 0xCF; 
     * 
     * SPBRGH 0; 
     * SP1BRGH = 0x0; 
     * 
     * EUSART2 
     * same as EUSART 1 
     * 
     * SPI CLK: RB5
     * SPI SDO/I: RB4
     * SPI CS: RD5
     * TX: RC6
     * RX: RC7
     * 
     * Debug RX:RD1
     * Debug TX:RD0
     * 
     */    
    SYSTEM_Initialize();  // Initialize the system using MCC
    EUSART2_Enable();
    EUSART2_TransmitEnable();

    //All this already configured in pins.c, but configuring again
    //Slave configuration

    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    TMR0_PeriodMatchCallbackRegister(ticker);

    TMR0_Start();
    
    if (STRAP_PIN) {
   
        /****** Master mode:*******/ 
        //Master configuration
        PB_SetDigitalMode(); 
        SDO_SetDigitalMode();
        SCK_SetDigitalMode();
        TX1_SetDigitalMode();
        RX1_SetDigitalMode();
        TX2_SetDigitalMode();
        RX2_SetDigitalMode();
        SS_SetDigitalMode();

        PB_SetDigitalInput(); //Personality: RA0
        SDO_SetDigitalInput(); //SPI SDI: RB4
        SCK_SetDigitalOutput(); // SPI CLK out: RB5
        TX1_SetDigitalOutput(); // TX: RC6
        RX1_SetDigitalInput(); // RX: RC7
        TX2_SetDigitalOutput(); // Debug TX:RD0
        RX2_SetDigitalInput(); // Debug RX:RD1
        SS_SetDigitalOutput(); // SPI CS out: RD5
        
        SPI1_OpenMaster();
        
        test1(1);
        UART2_SendString("Mode: master\n\r");
        uint16_t temperature;

        while (1) {
            SS_SetLow(); 
            temperature = read_temperature(); // Get temperature data from TMP122
            SS_SetHigh();
            UART_SendChar((temperature >> 8) & 0xFF);  //  Send high byte in SPI buffer
            UART_SendChar(temperature & 0xFF);  // Send low byte
#ifdef DEBUG
            temperature = temperature >> 7;
            printf("Temperature: %u\n\r", temperature);  // Debugging output
            __delay_ms(TIME_TO_READ);  // Delay in milliseconds, default = 100 mS
#endif
            __delay_ms(50);  // Delay 1 second
        }
    } else {
        /****** Master mode:*******/
        //Slave configuration
        PB_SetDigitalMode(); 
        SDO_SetDigitalMode();
        SCK_SetDigitalMode();
        TX1_SetDigitalMode();
        RX1_SetDigitalMode();
        TX2_SetDigitalMode();
        RX2_SetDigitalMode();
        SS_SetDigitalMode();

        PB_SetDigitalInput(); //Personality: RA0
        SDO_SetDigitalOutput(); //SPI SDO: RB4
        SCK_SetDigitalInput(); // SPI CLK in: RB5
        TX1_SetDigitalOutput(); // TX: RC6
        RX1_SetDigitalInput(); // RX: RC7
        TX2_SetDigitalOutput(); // Debug TX:RD0
        RX2_SetDigitalInput(); // Debug RX:RD1
        SS_SetDigitalInput(); // SPI CS in: RD5
        
        SPI1_OpenSlave();
        
        UART2_SendString("Mode: slave\n\r");
        // Slave mode
        //CS_TRIS = 1; //RB3 is input
        SCK_TRIS = 1; //RB5 is inputs
        bool detect_high_cs = false;
        UART2_SendString("enabling usart1\n\r");
        EUSART1_Enable();
        EUSART1_ReceiveEnable();
        EUSART1_TransmitEnable();
        UART2_SendString("registering handler\n\r");
        EUSART1_RxCompleteCallbackRegister(&uart1_handler);
        
        //UART.RxCompleteCallbackRegister(&UART_echoCharacters);
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();        
        
        
        UART2_SendString("entering loop\n\r");
        uint16_t data_temp;
        uint16_t data_spi = 0x1234;
        while (1) {
            start_label:
            if (buffer_read(&dataBuffer, &data_temp)) {
                data_spi = data_temp;
                printf("%x\r\n", data_spi);
            } 
            //data_spi = 0x0F80;

			SSP1BUF = data_spi >> 8; //send the high-byte
            data_ptr = 1;
            while (!PIR3bits.SSP1IF)
            {
                //SS is low, check if SS goes up
                if(!SS_GetValue()){
                    detect_high_cs = true;
                } else {
                    //if it's high then read the buffer
                    goto start_label;
                }
                
                if (detect_high_cs){
                    if(SS_GetValue()){
                        data_ptr = 0;
                        break;
                    }
                }
                // Wait for flag to get set */
            }
            
            if(data_ptr)
            {
                PIR3bits.SSP1IF = 0;       //clear flag to get ready for the next transmission     
                SSP1BUF = data_spi & 0xFF; //send the low-byte
            }
            while (!PIR3bits.SSP1IF)
            {
                //check if the ss goes up
                if(SS_GetValue()){
                    data_ptr = 0;
                    break;
                }
            }
        }
    }
}