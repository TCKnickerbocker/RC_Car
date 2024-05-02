#include "newxc8_header.h"

// PWM Outputs used: C0, C1
void init_portC_PWM(){
    PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTC_gc; // reroute to portC - pins 0-2 
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_CMP1EN_bm;

    TCA0.SINGLE.EVCTRL &= ~(TCA_SINGLE_CNTEI_bm);

    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV16_gc | TCA_SINGLE_ENABLE_bm;
    
    TCA0.SINGLE.PER = PWM_PERIOD; // F_CPU = CPU Frequency
    TCA0.SINGLE.CMP0 = 0; // 1/2 freq would be 6510
    TCA0.SINGLE.CMP1 = 0;  // CMP1 = turn left
    // Turn right is PD1 because PWM ports are very limited on device
}

// Turns horn on/off
void updateHorn(uint8_t status){
    if (!status){  // Turn horn on
        printStr("Updating Horn with Positive Status\r\n");
        TCA0.SINGLE.CMP1 = PWM_PERIOD / 2;
    }
    else{  // turn horn off
        printStr("Updating Horn with Zero Status\r\n");
        TCA0.SINGLE.CMP1 = 0;
    }
}

// 
void activate_motors(uint16_t forwardBackwardVal, uint16_t turnVal, enum driveState curDriveState, enum turnState curTurnState) {
    // Calculate a divisor for the speed:
    uint8_t speed_div;
    if (forwardBackwardVal <= 25 || forwardBackwardVal >= 230) {  // High speed
        speed_div = 1;
    } else {  // Low speed
        speed_div = 2;
    }
    
    // DRIVING STATES:
    
    if (forwardBackwardVal <= 132 && forwardBackwardVal >= 124){  // Not driving
        printStr("Stationary Drive\r\n");
        TCA0.SINGLE.CMP0 = 0;
        TURN_HEADLIGHTS_OFF();
        TURN_BRAKELIGHTS_OFF();
        curDriveState = NoDrive;
    }
    
    else if (forwardBackwardVal < 124){   // move forwards
        printStr("Driving Forwards\r\n");
        TCA0.SINGLE.CMP0 = PWM_PERIOD / speed_div;
        MOTOR_FORWARDS();  // update turn direction
        TURN_HEADLIGHTS_ON();
        TURN_BRAKELIGHTS_OFF();
        curDriveState = Forwards;
    }
    
    else{  // move backwards
        printStr("Driving Backwards\r\n");
        TCA0.SINGLE.CMP0 = PWM_PERIOD / speed_div;  
        MOTOR_BACKWARDS();
        TURN_HEADLIGHTS_OFF();
        TURN_BRAKELIGHTS_ON();
        curDriveState = Backwards;
    }
    
    // TURNING STATES:
    
    if (turnVal <= 132 && turnVal >= 124){  // Not turning
        printStr("No Turn\r\n");
        STOP_TURN_RIGHT();  // stop turning
        STOP_TURN_LEFT();  // stop turning
        TURN_LEFT_LIGHT_OFF();
        TURN_RIGHT_LIGHT_OFF();
        curTurnState = NoTurn;
    }
    
    else if (turnVal > 132) {  // Left turn
        printStr("Left Turn\r\n");
        STOP_TURN_RIGHT();
        TURN_RIGHT_LIGHT_OFF();
        TURN_LEFT_LIGHT_ON();
        TURN_LEFT();
        curTurnState = Left;
    }
    else{  // Right turn
        printStr("Right Turn\r\n");
        STOP_TURN_LEFT();
        TURN_LEFT_LIGHT_OFF();
        TURN_RIGHT_LIGHT_ON();
        TURN_RIGHT();
        curTurnState = Right;  
    }
}

