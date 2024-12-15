/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.0.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

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

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA0 aliases
#define PB_TRIS                 TRISAbits.TRISA0
#define PB_LAT                  LATAbits.LATA0
#define PB_PORT                 PORTAbits.RA0
#define PB_WPU                  WPUAbits.WPUA0
#define PB_OD                   ODCONAbits.ODCA0
#define PB_ANS                  ANSELAbits.ANSA0
#define PB_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define PB_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define PB_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define PB_GetValue()           PORTAbits.RA0
#define PB_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define PB_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define PB_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define PB_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define PB_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define PB_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define PB_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define PB_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)
// get/set IO_RB3 aliases
#define SDI_TRIS                 TRISBbits.TRISB3
#define SDI_LAT                  LATBbits.LATB3
#define SDI_PORT                 PORTBbits.RB3
#define SDI_WPU                  WPUBbits.WPUB3
#define SDI_OD                   ODCONBbits.ODCB3
#define SDI_ANS                  ANSELBbits.ANSB3
#define SDI_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define SDI_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define SDI_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define SDI_GetValue()           PORTBbits.RB3
#define SDI_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define SDI_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define SDI_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define SDI_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define SDI_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define SDI_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define SDI_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define SDI_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)
// get/set IO_RB4 aliases
#define SDO_TRIS                 TRISBbits.TRISB4
#define SDO_LAT                  LATBbits.LATB4
#define SDO_PORT                 PORTBbits.RB4
#define SDO_WPU                  WPUBbits.WPUB4
#define SDO_OD                   ODCONBbits.ODCB4
#define SDO_ANS                  ANSELBbits.ANSB4
#define SDO_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define SDO_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define SDO_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define SDO_GetValue()           PORTBbits.RB4
#define SDO_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define SDO_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define SDO_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define SDO_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define SDO_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define SDO_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define SDO_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define SDO_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)
// get/set IO_RB5 aliases
#define SCK_TRIS                 TRISBbits.TRISB5
#define SCK_LAT                  LATBbits.LATB5
#define SCK_PORT                 PORTBbits.RB5
#define SCK_WPU                  WPUBbits.WPUB5
#define SCK_OD                   ODCONBbits.ODCB5
#define SCK_ANS                  ANSELBbits.ANSB5
#define SCK_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define SCK_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define SCK_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define SCK_GetValue()           PORTBbits.RB5
#define SCK_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define SCK_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define SCK_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define SCK_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define SCK_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define SCK_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define SCK_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define SCK_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)
// get/set IO_RC6 aliases
#define TX1_TRIS                 TRISCbits.TRISC6
#define TX1_LAT                  LATCbits.LATC6
#define TX1_PORT                 PORTCbits.RC6
#define TX1_WPU                  WPUCbits.WPUC6
#define TX1_OD                   ODCONCbits.ODCC6
#define TX1_ANS                  ANSELCbits.ANSC6
#define TX1_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define TX1_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define TX1_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define TX1_GetValue()           PORTCbits.RC6
#define TX1_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define TX1_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define TX1_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define TX1_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define TX1_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define TX1_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define TX1_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define TX1_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)
// get/set IO_RC7 aliases
#define RX1_TRIS                 TRISCbits.TRISC7
#define RX1_LAT                  LATCbits.LATC7
#define RX1_PORT                 PORTCbits.RC7
#define RX1_WPU                  WPUCbits.WPUC7
#define RX1_OD                   ODCONCbits.ODCC7
#define RX1_ANS                  ANSELCbits.ANSC7
#define RX1_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RX1_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RX1_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RX1_GetValue()           PORTCbits.RC7
#define RX1_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RX1_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RX1_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define RX1_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define RX1_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define RX1_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define RX1_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define RX1_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)
// get/set IO_RD0 aliases
#define TX2_TRIS                 TRISDbits.TRISD0
#define TX2_LAT                  LATDbits.LATD0
#define TX2_PORT                 PORTDbits.RD0
#define TX2_WPU                  WPUDbits.WPUD0
#define TX2_OD                   ODCONDbits.ODCD0
#define TX2_ANS                  ANSELDbits.ANSD0
#define TX2_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define TX2_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define TX2_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define TX2_GetValue()           PORTDbits.RD0
#define TX2_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define TX2_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define TX2_SetPullup()          do { WPUDbits.WPUD0 = 1; } while(0)
#define TX2_ResetPullup()        do { WPUDbits.WPUD0 = 0; } while(0)
#define TX2_SetPushPull()        do { ODCONDbits.ODCD0 = 0; } while(0)
#define TX2_SetOpenDrain()       do { ODCONDbits.ODCD0 = 1; } while(0)
#define TX2_SetAnalogMode()      do { ANSELDbits.ANSD0 = 1; } while(0)
#define TX2_SetDigitalMode()     do { ANSELDbits.ANSD0 = 0; } while(0)
// get/set IO_RD1 aliases
#define RX2_TRIS                 TRISDbits.TRISD1
#define RX2_LAT                  LATDbits.LATD1
#define RX2_PORT                 PORTDbits.RD1
#define RX2_WPU                  WPUDbits.WPUD1
#define RX2_OD                   ODCONDbits.ODCD1
#define RX2_ANS                  ANSELDbits.ANSD1
#define RX2_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define RX2_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define RX2_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define RX2_GetValue()           PORTDbits.RD1
#define RX2_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define RX2_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define RX2_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define RX2_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define RX2_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define RX2_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define RX2_SetAnalogMode()      do { ANSELDbits.ANSD1 = 1; } while(0)
#define RX2_SetDigitalMode()     do { ANSELDbits.ANSD1 = 0; } while(0)
// get/set IO_RD5 aliases
#define SS_TRIS                 TRISDbits.TRISD5
#define SS_LAT                  LATDbits.LATD5
#define SS_PORT                 PORTDbits.RD5
#define SS_WPU                  WPUDbits.WPUD5
#define SS_OD                   ODCONDbits.ODCD5
#define SS_ANS                  ANSELDbits.ANSD5
#define SS_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define SS_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define SS_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define SS_GetValue()           PORTDbits.RD5
#define SS_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define SS_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define SS_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define SS_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define SS_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define SS_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define SS_SetAnalogMode()      do { ANSELDbits.ANSD5 = 1; } while(0)
#define SS_SetDigitalMode()     do { ANSELDbits.ANSD5 = 0; } while(0)
/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/