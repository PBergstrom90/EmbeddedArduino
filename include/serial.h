#ifndef SERIAL_H_
#define SERIAL_H_

// Macros for UART communication.
#define LED_PIN 3 // PD3 (Arduino pin 3)
#define BUTTON_PIN 5 // PD5 (Arduino pin 5)
#define F_CPU 16000000L // 16 MHz clock speed.
#define BAUD 9600 // Baud rate for UART communication.
#define UBRR F_CPU/16/BAUD-1 // Asynchronous normal mode - Page 146 ATmega328P Datasheet.

void uartInit(unsigned int ubrr);
void uartPutChar(char c);
void uartPutString(const char *s);
char uartGetChar();
void uartRecStringAndEcho(char *s);

#endif // _SERIAL_H_