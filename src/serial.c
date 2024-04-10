#include <stdio.h>
#include <avr/io.h>
#include "serial.h"
#include "led.h"

void uartInit(unsigned int ubrr) {
    // Set baud rate.
    UBRR0H = (unsigned char)(ubrr >> 8); // High byte of the baud rate.
    UBRR0L = (unsigned char)ubrr; // Low byte of the baud rate.
    // UART Control and Status Register B: Enable receiver and transmitter.
    UCSR0B = (1 << RXEN0) | (1 << TXEN0); 
    // UART Control and Status Register C: Set frame format: 8 data, 1 stop bit.
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
};

void uartPutChar(const char c) {
    // UCSR0A is the UART Control and Status Register A. The UDRE0 bit indicates whether,
    // the UART Data Register (UDR0) is empty and ready to transmit a new byte.
    while(!(UCSR0A & (1 << UDRE0))); // Wait for empty transmit buffer.
    UDR0 = c; // Transmit character.
};

void uartPutInt(int i) {
    char buffer[10];
    sprintf(buffer, "%d", i);
    uartPutString(buffer);
};

void uartPutFloat(float f) {
    char buffer[10];
    sprintf(buffer, "%.2f", f);
    uartPutString(buffer);
};  

void uartPutString(const char *s) {
    // Iterate over each character, received from the pointer.
    while(*s != '\0'){
        uartPutChar(*s++); // Transmit character.
    }
};

char uartGetChar() {
    // UCSR0A is used here to check the UART Receive Complete (RXC0) bit. 
    // This bit indicates whether there is data available in the UART receive buffer.
    while(!(UCSR0A & (1 << RXC0)));
    // Get and return received data from buffer.
    return UDR0;
};

// This function is combined with the previous "uartEcho"-function, to minimise disturbance when receiving data.
void uartRecStringAndEcho(char *s) {
    // Read characters until a newline character is received.
    char receivedChar = uartGetChar();
    while(receivedChar != '\n') {
        *s = receivedChar;
        uartPutChar(receivedChar); // Echo received character.
        s++;
        receivedChar = uartGetChar();
    }
    *s = '\0'; // Null-terminate the string
};