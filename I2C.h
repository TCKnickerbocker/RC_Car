#ifndef I2C_H
#define I2C_H

void initTWI();
void readJoystickBytes(uint8_t *dest, uint8_t len);
void displayData(uint8_t a, uint8_t b, uint8_t c, uint8_t d);

#endif // I2C_H
