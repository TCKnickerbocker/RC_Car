#ifndef CAR_H
#define CAR_H

void init_portC_PWM();
void updateHorn(uint8_t status);
void activate_motors(uint16_t forwardBackwardVal, uint16_t turnVal, enum driveState curDriveState, enum turnState curTurnState);

#endif // CAR_H
