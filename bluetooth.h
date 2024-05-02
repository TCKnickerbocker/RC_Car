#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "newxc8_header.h"

void usartWriteChar(char c);
void usartWriteCommand(const char *cmd);
char usartReadChar();
void usartReadUntil(char *dest, const char *end_str);
void read_d_response(char *dest, const char *end_str);
void usartInit();
void bleInit(const char *name);
void readBLE(enum driveState curDriveState, enum turnState curTurnState);


#endif // BLUETOOTH_H
