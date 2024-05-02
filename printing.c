#include "newxc8_header.h"

// From Mitch's post
void setup_printing_via_USART2(void)
{
    /* Set TX pin as output and RX pin as input */
    PORTF.DIRSET = PIN0_bm;
    PORTF.DIRCLR = PIN1_bm;
    
    /* Set the BAUD Rate using the macro from the tutorial
     *      Use 9600 as the standard baud rate. You will need to match this in Putty
     */
    USART2.BAUD = (uint16_t)USART2_BAUD_VALUE(9600);
    
    /* Enable transmission for USART2 */
    USART2.CTRLB |= USART_TXEN_bm;
}

void printStr(char *str)
 {
    for(size_t i = 0; i < strlen(str); i++)
    {
        while (!(USART2.STATUS & USART_DREIF_bm));      
        USART2.TXDATAL = str[i];
    }
 }

void printBuf(char* buf){
    int i = 0;
    while (buf[i] != '\0') {
        i++;
    }
    buf[i++] = '\r';
    buf[i++] = '\n';
    buf[i] = '\0'; // Ensure buf is null-termd
    printStr(buf);
}