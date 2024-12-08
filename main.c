/*
 * File:   newmain.c
 * Author: edgar
 *
 * Created on December 4, 2024, 12:23 PM
 */
#include <xc.h>
#include <stdio.h>

// Configuration bits
//CONFIG1
#pragma config FEXTOSC = HS    // External Oscillator Selection bits->XT (crystal oscillator) above 500kHz, below 4MHz; PFM set to medium power
#pragma config RSTOSC = EXT1X    // Reset Oscillator Selection bits->EXTOSC operating per FEXTOSC bits
#pragma config CLKOUTEN = OFF    // Clock Out Enable bit->CLKOUT function is disabled; i/o or oscillator function on OSC2
#pragma config CSWEN = OFF    // Clock Switch Enable bit->The NOSC and NDIV bits cannot be changed by user software
#pragma config FCMEN = ON    // Fail-Safe Clock Monitor Enable bit->FSCM timer enabled

//CONFIG2
#pragma config MCLRE = ON    // Master Clear Enable bit->MCLR pin is Master Clear function
#pragma config LPBOREN = OFF    // Low-Power BOR Enable bit->ULPBOR disabled
#pragma config BOREN = ON    // Brown-out Reset Enable bits->Brown-out Reset Enabled, SBOREN bit is ignored
#pragma config BORV = HI    // Brown-out Reset Voltage Selection bit->Brown-out Reset Voltage (VBOR) is set to 2.7V
#pragma config ZCD = OFF    // ZCD Disable bit->Zero-cross detect circuit is disabled at POR.
#pragma config PPS1WAY = ON    // PPSLOCKED One-Way Set Enable bit->The PPSLOCK bit can be cleared and set only once in software
#pragma config STVREN = ON    // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a reset

//CONFIG3
#pragma config WDTCPS = WDTCPS_31    // WDT Period Select bits->Divider ratio 1:65536; software control of WDTPS
#pragma config WDTE = OFF    // WDT Operating Mode bits->WDT Disabled, SWDTEN is ignored
#pragma config WDTCWS = WDTCWS_7    // WDT Window Select bits->window always open (100%); software control; keyed access not required
#pragma config WDTCCS = SC    // WDT Input Clock Select bits->Software Control

//CONFIG4
#pragma config BBSIZE = BB512    // Boot Block Size Selection bits->512 words boot block size
#pragma config BBEN = OFF    // Boot Block Enable bit->Boot Block disabled
#pragma config SAFEN = OFF    // Storage Area Flash (SAF) Enable bit->SAF disabled
#pragma config WRTAPP = OFF    // Application Block Write Protection bit->Application Block not write protected
#pragma config WRTB = OFF    // Boot Block Write Protection bit->Boot Block not write protected
#pragma config WRTC = OFF    // Configuration Register Write Protection bit->Configuration Register not write protected
#pragma config WRTSAF = OFF    // Storage Area Flash (SAF) Write Protection bit->SAF not write protected
#pragma config LVP = ON    // Low Voltage Programming Enable bit->Low Voltage programming enabled. MCLR/Vpp pin function is MCLR.

//CONFIG5
#pragma config CP = OFF    // Program Flash Memory Code Protection bit->UserNVM code protection disabled

// Define constants for MSSP
#define SPI_SCK_TRIS   TRISBbits.TRISB5 // SCK (Clock) TRIS bit
#define SPI_IO_TRIS    TRISBbits.TRISB4 // Single I/O (Bidirectional) TRIS bit
#define SPI_CS_TRIS    TRISBbits.TRISB3 // Chip Select (CS) TRIS bit
#define SPI_IO_PIN     LATBbits.LATB4   // Single I/O (Bidirectional) pin
#define SPI_CS_PIN     LATBbits.LATB3   // Chip Select (CS) pin
#define STRAP_PIN      PORTAbits.RA0    // Strap pin to determine role

// Define constants for UART 
#define UART_TX_TRIS TRISCbits.TRISC6		//UART TX TRIS Bit
#define UART_RX_TRIS TRISCbits.TRISC7		//UART RX TRIS Bit
#define isHighSpeedBRG TX1STAbits.BRGH		//Baud Rate Generator (BRG) High Speed Enable Bit
#define is16bitBRG BAUD1CONbits.BRG16		//Set (1) or not set (0) BRG to 16 bits
#define BaudRate SP1BRG						//Baud Rate setting
#define bps9600 207							//Baud rate set to 9600bps
#define isSynchronous TX1STAbits.SYNC		//UART set to Sync (1) or Async (0)
#define isUartPortEnabled RC1STAbits.SPEN	//UART Port Enable bit
#define isTransmitEnabled TX1STAbits.TXEN	//UART Transmission Enable Bit
#define isReceptionOngoing RC1STAbits.CREN	//UART Continuous Reception Enable Bit

#define _XTAL_FREQ 8000000U
//Define debug port for printf()
//#define UART_DBTX_TRIS TRISCbits.TRISC6		//UART TX TRIS Bit
//#define UART_DBRX_TRIS TRISCbits.TRISC7		//UART RX TRIS Bit
//declare functions. May be moved to a header file
void SPI_Init();
void UART_Init();
void SPI_Write(uint16_t);
uint16_t SPI_Read(void);
void UART_SendChar(uint8_t);
uint8_t UART_ReceiveChar(void);
void TMP122_Init();
void putch(char);
uint16_t read_temperature();
/**
 * Initializes the SPI module and sets up the necessary pins.
 */
void SPI_Init(void) {
	SSP1CON1 = 0x20;       // Enable SPI (SSPEN enabled), CKP = 0, SSPM = 0000 (SPI Master mode, clock = Fosc/4)
	SSP1STAT = 0x00;       // Sampling at middle of data output time, SPI mode 0,0
	SSP1ADD = 1;           // Set SSP1ADD for 1 Mbps SCK frequency

	// Set SCK and SDIO as output/input as necessary. Set CS direction and value
	SPI_SCK_TRIS = 0;  // SCK as output
	SPI_IO_TRIS = 1;  // SDIO as input (initially)
	SPI_CS_TRIS = 0;  // CS as output
	SPI_CS_PIN = 1;  // Initially deselect the TMP122
}

void SPI_Write(uint16_t data) {  //16-bit data
	SPI_IO_TRIS = 0;  // Set SDIO as output
	SPI_CS_PIN = 0;  // Select the TMP122
	//PIC16F15376 cannot handle 16 bits so splitting to two 8-bit data is necessary
	uint8_t high_byte = (data >> 8) & 0xFF; // Extract high byte.
	uint8_t low_byte = data & 0xFF;         // Extract low byte
	SSP1BUF = high_byte;    // Send high byte
	while (!SSP1STATbits.BF); // Wait until transmission is complete
	(void)SSP1BUF;          // Read buffer to clear it using method of typecasting as void
	SSP1BUF = low_byte;     // Send low byte
	while (!SSP1STATbits.BF); // Wait until transmission is complete
	(void)SSP1BUF;          // Read buffer to clear it using method of typecasting as void
	SPI_CS_PIN = 1;  // Deselect the TMP122
	SPI_IO_TRIS = 1;  // Set I/O pin as input
}

uint16_t SPI_Read(void) {
	uint16_t data = 0;
	uint8_t high_byte = 0;
	uint8_t low_byte = 0;
	SPI_IO_TRIS = 1;  // Set SDIO as input
	SPI_CS_PIN = 0;  // Select the TMP122
	SSP1BUF = 0x00;        // Initiate SPI read by writing dummy byte
	while (!SSP1STATbits.BF); // Wait until data is received
	high_byte = SSP1BUF;   // Read high byte
	SSP1BUF = 0x00;        // Initiate SPI read by writing dummy byte
	while (!SSP1STATbits.BF); // Wait until data is received
	low_byte = SSP1BUF;    // Read low byte
	data = (high_byte << 8) | low_byte; // Combine high and low bytes
	return data;
}

void UART_Init(void) {
	// Set TX as output, RX as input
	UART_TX_TRIS = 0;  // TX as output
	UART_RX_TRIS = 1;  // RX as input
	
	// Initialize UART module
	isHighSpeedBRG = 1;    // High speed						
	is16bitBRG = 1; // 16-bit Baud Rate Generator				
	BaudRate = bps9600;      // Baud rate 9600 at 8MHz Fosc		
															//	
	isSynchronous = 0;    // Asynchronous mode 					
	isUartPortEnabled = 1;    // Enable serial port				
	isTransmitEnabled = 1;    // Enable transmission			
	isReceptionOngoing = 1;    // Enable continuous reception	
}

void UART_SendChar(uint8_t data) {
        while (!PIR3bits.TX1IF); // Wait until buffer is empty	
        TXREG = data;          // Transmit data
}

uint8_t UART_ReceiveChar(void) {
        while (!PIR3bits.RC1IF); // Wait until data is received
        return RCREG;           // Return received data
}

void putch(char data) {
	while (!PIR3bits.TX1IF); // Wait until buffer is empty
	TXREG = data;          // Transmit data
}

void TMP122_init(void) {
	SPI_CS_PIN = 0;            // Select the TMP122
	SPI_Write(0x0000);     // Write command to initialize TMP122 (depending on the sensor's datasheet)
	SPI_CS_PIN = 1;            // Deselect the TMP122
}

uint16_t read_temperature(void) {
	SPI_CS_PIN = 0;            // Select the TMP122
	uint16_t temp_data = SPI_Read(); // Read temperature data
	SPI_CS_PIN = 1;            // Deselect the TMP122
	return temp_data;
}

void main(void) {
	// Initialize system
	OSCCON1 = 0x70;         // Set external oscillator to 8MHz (set bits accordingly)
	ANSELA = 0x00;         // Set PORTA as digital I/O
	
	// Initialize SPI and UART
	SPI_Init();
	UART_Init();
	
	// Determine role (High for master, Low for slave)
	TRISAbits.TRISA0 = 1;  // Set STRAP_PIN as input
	
	if (STRAP_PIN) {
		// Master mode
		TMP122_init();     // Initialize TMP122 sensor
		
		uint16_t temperature;
		
		while (1) {
				// Read temperature data from TMP122
				temperature = read_temperature();
				
				// Send temperature data via UART (high and low bytes)
				UART_SendChar((temperature >> 8) & 0xFF); // Send high byte
				UART_SendChar(temperature & 0xFF);        // Send low byte
				
				// Debugging output
				printf("Temperature: %u\n", temperature);
				
				// Add delay as needed
				__delay_ms(1000); // Delay 1 second
		}
	} else {
		// Slave mode
		uint8_t high_byte, low_byte;
		uint16_t data;
		while (1) {
			// Receive high and low bytes of data via UART
			high_byte = UART_ReceiveChar();
			low_byte = UART_ReceiveChar();
			// Combine high and low bytes to form the 16-bit data
			data = (high_byte << 8) | low_byte;
			// Send data via SPI
			SPI_Write(data);
			// Debugging output
			printf("Received data: %u\n", data);
		}
	}
}