#include "newxc8_header.h"

// Writes a single char via USART 
void usartWriteChar(char c) {
    while (!(USART0.STATUS & USART_DREIF_bm)){;}     
    USART0.TXDATAL = c;
}

// Writes the contents of a command via USART, char by char
void usartWriteCommand(const char *cmd) {
    for (uint8_t i = 0; cmd[i] != '\0'; i++) {
        usartWriteChar(cmd[i]);
    }
}

// Reads a single char via USART 
char usartReadChar() {
    while (!(USART0.STATUS & USART_RXCIF_bm)){;}
    return USART0.RXDATAL;
}


void usartReadUntil(char *dest, const char *end_str) {
    memset(dest, 0, BUF_SIZE);
    uint8_t end_len = strlen(end_str);
    uint8_t bytes_read = 0;
    while (bytes_read < end_len || strcmp(dest + bytes_read - end_len, end_str) != 0) {
        dest[bytes_read] = usartReadChar();
        bytes_read++;
    }
}

// Reads a longer response from commands (unused))
void read_d_response(char *dest, const char *end_str){
    memset(dest, 0, 512);
    uint8_t end_len = strlen(end_str);
    uint8_t bytes_read = 0;
    while (bytes_read < end_len || strcmp(dest + bytes_read - end_len, end_str) != 0) {
        dest[bytes_read] = usartReadChar();
        bytes_read++;
    }   
}

// Starts up USART0
void usartInit() {
    PORTA.DIR &= ~PIN1_bm;
    PORTA.DIR |= PIN0_bm;
    
    USART0.BAUD = (uint16_t)USART_BAUD_VALUE(9600);

    // Setup send, receive, normal mode
    USART0.CTRLB |= USART_TXEN_bm; 
    USART0.CTRLB |= USART_RXEN_bm; 
    USART0.CTRLB |= USART_RXMODE_NORMAL_gc; 
    
    USART0.CTRLC |= USART_CMODE_ASYNCHRONOUS_gc;
    USART0.CTRLC |= USART_CHSIZE_8BIT_gc; 
}

// Initializes  & advertises a characteristic
void bleInit(const char *name) {
    PORTF.DIRSET = PIN3_bm;
    PORTF.OUTSET = PIN3_bm;

    PORTD.DIRSET = PIN3_bm | PIN2_bm;
    PORTD.OUTCLR = PIN3_bm;
    _delay_ms(10);
    PORTD.OUTSET = PIN3_bm;

    PORTD.OUTCLR = PIN2_bm;
    _delay_ms(200);

    char buf[BUF_SIZE];
    usartWriteCommand("$$$");
    usartReadUntil(buf, BLE_RADIO_PROMPT);
    
    strcpy(buf, "S-,");
    strcat(buf, name);
    strcat(buf, "\r\n");
    usartWriteCommand(buf);
    usartReadUntil(buf, BLE_RADIO_PROMPT);
    
    strcpy(buf, "PZ\r\n");
    usartWriteCommand(buf);
    usartReadUntil(buf, BLE_RADIO_PROMPT);
    
    strcpy(buf, "PS,010203040506070809000A0B0C0D0E0F\r\n");  
    usartWriteCommand(buf);
    usartReadUntil(buf, BLE_RADIO_PROMPT);
    
    strcpy(buf, "PC,010203040506070809000A0B0C0D0E0F,0A,02\r\n");
    usartWriteCommand(buf);
    usartReadUntil(buf, BLE_RADIO_PROMPT);
    
    strcpy(buf, "SHW,0072,00\r\n");
    usartWriteCommand(buf);
    usartReadUntil(buf, BLE_RADIO_PROMPT);
    
    printStr("Advertising via Bluetooth\r\n");
}

// Reads characteristic value and calls display & driving accordingly
void readBLE(enum driveState curDriveState, enum turnState curTurnState){
    printStr("Reading from BLE\r\n");
    char buf[BUF_SIZE];
    strcpy(buf, "SHR,0072\r\n");
    usartWriteCommand(buf);
    usartReadUntil(buf, BLE_RADIO_PROMPT);
    printBuf(buf);
    
    // Extract integer reading from str
    char tmp[3];
    sscanf(buf, "%2s", tmp);
    uint8_t val = (uint8_t)atoi(tmp);
    PORTA.DIR |= PIN5_bm;
    
    uint8_t cVal = 12;
    uint8_t fVal = 12;
    uint8_t bVal = 12;
    
    uint8_t zeroVal = 0;
    uint8_t midVal = 128;
    uint8_t maxVal = 255;

    uint8_t nVal = 78;
    uint8_t blankVal = 17;
    uint8_t lineVal = 45;

    if (val == 0) {  // Stationary
        curDriveState = NoDrive;
        curTurnState = NoTurn;

        // call activate motors, display Conn
        activate_motors(midVal, zeroVal, nVal, nVal);
        displayData(cVal, zeroVal, lineVal, lineVal); 
//        displayData(cVal, zerVal, nVal, nVal); 
    }
    else if (val == 1){  // Backwards
        activate_motors(zeroVal, zeroVal, curDriveState, curTurnState);
        displayData(cVal, blankVal, blankVal, fVal); 
    }
    else if (val == 2){  // Forwards
        activate_motors(maxVal, zeroVal, curDriveState, curTurnState);
        displayData(cVal, blankVal, blankVal, bVal); 
    }
    else{
        printStr("Buf was unreadable... \r\n");
    }
}
