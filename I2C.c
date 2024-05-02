#include "newxc8_header.h"

// Initializes I2C
void initTWI() {
    PORTA.DIRSET = PIN2_bm | PIN3_bm;
    PORTA.PIN2CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN3CTRL = PORT_PULLUPEN_bm;
    
    TWI0.CTRLA |= TWI_SDAHOLD_50NS_gc;
    
    TWI0.MSTATUS = TWI_RIF_bm | TWI_WIF_bm | TWI_CLKHOLD_bm | TWI_RXACK_bm |
            TWI_ARBLOST_bm | TWI_BUSERR_bm | TWI_BUSSTATE_IDLE_gc;
    
    TWI0.MBAUD = 10;    
    TWI0.MCTRLA = TWI_ENABLE_bm;
}

// Read data from joystick
void readJoystickBytes(uint8_t *dest, uint8_t len) { // len should be 4
    TWI0.MADDR = (0x20 << 1) | 0;  // set write mode with addr 20 for joystick
    while (!(TWI0.MSTATUS & TWI_WIF_bm));   // Wait for maddr response
    
    uint8_t joystickAddr = 0x03;
    uint8_t bCount = 0; 
    TWI0.MDATA = joystickAddr; // starts reads from 0x03 -> read to 06
    while (!(TWI0.MSTATUS & TWI_WIF_bm));
    TWI0.MADDR = (0x20 << 1) | 1;
   
    TWI0.MCTRLB = TWI_MCMD_REPSTART_gc;
    
    while(bCount < len){
        while (!(TWI0.MSTATUS & TWI_RIF_bm));
        dest[bCount] = TWI0.MDATA;
        bCount += 1;

        if (bCount != len){
            TWI0.MCTRLB = TWI_ACKACT_ACK_gc | TWI_MCMD_RECVTRANS_gc;
        }
        joystickAddr+=1;
    }
    // NACK and STOP the bus
    TWI0.MCTRLB = TWI_ACKACT_NACK_gc | TWI_MCMD_STOP_gc;     
}


// Writes data to display... 
// Non-bluetooth writes: a = driveMode, b = pos/neg direction, c/d = drivepower (as per joystick reading)
// Bluetooth writes: indicates whether moving forwards or backwards
void displayData(uint8_t a, uint8_t b, uint8_t c, uint8_t d){
    TWI0.MADDR = (0x71 << 1) | 0;  // set write mode with addr 71
    while (!(TWI0.MSTATUS & TWI_WIF_bm));    // Wait for maddr response
    
    uint8_t myData[4] = {a, b, c, d};
    for (int i = 0; i < 4; i++) {
        TWI0.MDATA = myData[i];
        while (!(TWI0.MSTATUS & TWI_WIF_bm));
    }
    
    TWI0.MCTRLB |= TWI_MCMD_STOP_gc;
}
