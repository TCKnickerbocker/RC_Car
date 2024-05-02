//#include "newxc8_header.h"
////#include "motor.c"
//
//
//void changeLights(){
//    switch (curDriveState){
//        case Forwards:
//            if (curLightState != Brights){
//                if (curLightState == Brakelights){
//                    toggleBrakelights(0);  // turn brakelights off
//                }
//                toggleBrights(1);
//                curLightState = Brights;
//            }
//            break;
//        case Backwards:
//            if (curLightState == Brights){
//                toggleBrights(0);  // turn off brights
//            }
//            toggleBrakelights(1);
//            curLightState = Brakelights;
//            break;
//        case Stationary:
//            if (curLightState == Brights){
//                toggleBrights(0);  // turn off brights
//            }
//            else if (curLightState == Brakelights){
//                toggleBrakelights(0);  // turn off brakelights
//            }
//            curLightState = Headlights;
//            break;
//    }
//}
//
//
//// Turns brakelights on/off
//void toggleBrakelights(uint8_t on){
//    if (on){
//        PORTA.OUT |= PIN6_bm;
//        PORTA.OUT |= PIN7_bm;
//    }
//    else{
//        PORTA.OUT &= ~PIN6_bm;
//        PORTA.OUT &= ~PIN7_bm;
//    }
//}
//
//// Turns brights on/off
//void toggleBrights(uint8_t on){
//    if (on){
//        PORTA.OUT |= PIN5_bm;
//    }
//    else{
//        PORTA.OUT &= ~PIN5_bm;
//    }
//}
//
