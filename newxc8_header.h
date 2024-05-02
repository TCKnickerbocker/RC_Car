#ifndef NEWXC8_HEADER_H
#define NEWXC8_HEADER_H

#define F_CPU 3333333
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/atomic.h>
#include <avr/cpufunc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// USART for printing & connecting to laptop
#define BUF_SIZE 128
#define BLE_RADIO_PROMPT "CMD> "

#define SAMPLES_PER_BIT 16
#define USART_BAUD_VALUE(BAUD_RATE) (uint16_t) ((F_CPU << 6) / (((float) SAMPLES_PER_BIT) * (BAUD_RATE)) + 0.5)
#define USART2_BAUD_VALUE(BAUD_RATE) (uint16_t) ((F_CPU << 6) / (((float) SAMPLES_PER_BIT) * (BAUD_RATE)) + 0.5)

// PWM vals
#define PWM_PERIOD 1200

// Motor
#define MOTOR_FORWARDS() PORTD.OUT &= ~PIN6_bm;
#define MOTOR_BACKWARDS() PORTD.OUT |= PIN6_bm;

#define TURN_RIGHT() PORTD.OUT |= PIN7_bm;
#define STOP_TURN_RIGHT() PORTD.OUT &= ~PIN7_bm;

#define TURN_LEFT() PORTD.OUT |= PIN1_bm;
#define STOP_TURN_LEFT() PORTD.OUT &= ~PIN1_bm;


// Joystick interrupt (I2C)
#define TWI_IS_CLOCKHELD() TWI0.MSTATUS & TWI_CLKHOLD_bm
#define TWI_IS_BUSERR() TWI0.MSTATUS & TWI_BUSERR_bm
#define TWI_IS_ARBLOST() TWI0.MSTATUS & TWI_ARBLOST_bm
#define TWI_READ true
#define TWI_WRITE false
#define TWI_IS_BUSBUSY() ((TWI0.MSTATUS & TWI_BUSSTATE_BUSY_gc) == TWI_BUSSTATE_BUSY_gc)

#define TWI_WAIT() while (!(TWI0.MSTATUS & TWI_WIF_bm))


// Speaker & Lights

#define TURN_HEADLIGHTS_ON() PORTA.OUT |= PIN5_bm;
#define TURN_HEADLIGHTS_OFF() PORTA.OUT &= ~PIN5_bm;

#define TURN_LEFT_LIGHT_ON() PORTA.OUT |= PIN6_bm;
#define TURN_LEFT_LIGHT_OFF() PORTA.OUT &= ~PIN6_bm;

#define TURN_RIGHT_LIGHT_ON() PORTA.OUT |= PIN7_bm;
#define TURN_RIGHT_LIGHT_OFF() PORTA.OUT &= ~PIN7_bm;

#define TURN_BRAKELIGHTS_ON() PORTD.OUT |= PIN5_bm;
#define TURN_BRAKELIGHTS_OFF() PORTD.OUT &= ~PIN5_bm;


// Bluetooth
#define BLUETOOTH_BUTTON_INTERRUPT PORTA.INTFLAGS & PIN4_bm
#define CLEAR_BLUETOOTH_BUTTON_INTERRUPT PORTA.INTFLAGS &= PIN4_bm

enum driveState { Forwards, Backwards, NoDrive };
enum turnState { Left, Right, NoTurn };


#endif /* NEWXC8_HEADER_H */
