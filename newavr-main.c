#include "newxc8_header.h"
#include "car.h"
#include "I2C.h"
#include "printing.h"
#include "rtc.h"
#include "bluetooth.h"



// ----------------------------- INIT VARS: ----------------------------- //

int8_t joystickData[6];  

volatile uint8_t horizontalPos;
volatile uint8_t verticalPos;

volatile uint8_t joystickButtonPos;
volatile uint8_t joystickButtonChanged;

volatile uint8_t bluetooth;

volatile enum driveState curDriveState = NoDrive;
volatile enum turnState curTurnState = NoTurn;


// ----------------------------- BEGIN FUNCS ----------------------------- //


/* 
 * I elected to use opposite directions of the orientation printed on the joystick 
 * peripheral to provide users with a right-handed controller grip.
*/
void handleJoystick(){
    readJoystickBytes((uint8_t *) joystickData, 6);
    verticalPos = joystickData[0];  // Drive (reading 1 byte))
    horizontalPos = joystickData[2];  // Turn (reading 1 byte))

    joystickButtonPos = joystickData[4];
    joystickButtonChanged = joystickData[5];
    
    if (joystickButtonChanged){
        updateHorn(joystickButtonPos);
    }
    activate_motors(verticalPos, horizontalPos, curDriveState, curTurnState);
}


// Calls displayData() with the appropriate params
void handleDisplay(){
    if (!bluetooth){
        // Map from [0,255] to [-100,100]
        int scaledValue = (int)((verticalPos / 255.0) * 200) - 99; 
        uint8_t sign = 17; // no display
        uint8_t hundreds = abs(scaledValue) / 100;
        uint8_t tens = (abs(scaledValue) / 10) % 10;
        uint8_t ones = abs(scaledValue) % 10;

        if (scaledValue > 0) {  // negative display
            printStr("Negative Display\r\n");
            sign = 45;
        } else {  // negative
            printStr("Positive Display\r\n");
        }
        displayData(sign, hundreds, tens, ones);   
    }
    // bluetooth mode display handled in readBLE()
}

// Sets up directions, pullup status on all used ports
void initPorts(){
    // lights ports
    PORTA.DIR |=  PIN5_bm | PIN6_bm | PIN7_bm; 
    PORTD.DIR |= PIN5_bm;
    
    // Motor & speaker PWM ports:
    PORTC.DIR |= PIN0_bm | PIN1_bm;
    
    // Motor Direction (defaulted to forwards):
    PORTD.DIR |= PIN6_bm;
    
    // Motor turning ports
    PORTA.DIR |= PIN1_bm | PIN7_bm;
    
    // I2C ports. Also set in initTWI()
    PORTA.DIR |= PIN2_bm | PIN3_bm;
    
    // Bluetooth Button
    PORTA.DIR &= ~PIN4_bm;
    PORTA.PIN4CTRL |= PORT_PULLUPEN_bm | PORT_ISC_RISING_gc;
}



// Calls all functions to initialize the car
void init(){
    initPorts();
    initTWI();
    init_portC_PWM();
    setup_printing_via_USART2();
    printStr("Running Program!\r\n");
    init_RTC();
    
    // For bluetooth control option (via LightBlue App):
    usartInit();
    bleInit("DennisRodeman");
    bluetooth = 0;
}


int main(void) {
    sei();
    init();
    while (1) {     
    }
}



// -------------------------- INTERRUPTS ----------------------------------- //

// Timer Overflow Interrupt -> read
ISR(RTC_CNT_vect) {
    if (!bluetooth){
        handleJoystick();   
    }
    else{
        readBLE(curDriveState, curTurnState);
    }
    handleDisplay();
    RTC.INTFLAGS = RTC_OVF_bm;  // clear interrupt flag
}

// ButtonPush Interrupt
ISR(PORTA_PORT_vect){
    printStr("ButtonPush Interrupt\r\n");
    if (BLUETOOTH_BUTTON_INTERRUPT) {
        if (bluetooth){  // Bluetooth already enabled - disable
            bluetooth = 0;
            // Signal that the bluetooth has been deactivated
            TURN_LEFT_LIGHT_OFF();
            TURN_RIGHT_LIGHT_OFF();
        }
        else{
            bluetooth = 1;
            // Signal that the bluetooth has been activated
            TURN_LEFT_LIGHT_ON();
            TURN_RIGHT_LIGHT_ON();
        }
        CLEAR_BLUETOOTH_BUTTON_INTERRUPT;
    }
}

