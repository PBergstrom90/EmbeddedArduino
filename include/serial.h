#ifndef SERIAL_H_
#define SERIAL_H_

// Macros for UART communication.
#define LED_PIN 3 // PD3 (Arduino pin 3)
#define BUTTON_PIN 5 // PD5 (Arduino pin 5)
#define BUTTON_PIN_REGISTER PIND
#define F_CPU 16000000L // 16 MHz clock speed.
#define BAUD 9600 // Baud rate for UART communication.
#define UBRR F_CPU/16/BAUD-1 // Asynchronous normal mode - Page 146 ATmega328P Datasheet.

void uartInit(unsigned int ubrr);
bool uartDataAvailable();
void uartPutChar(char c);
void uartPutInt(int i);
void uartPutFloat(float f);
void uartPutString(const char *s);
char uartGetChar();
void uartRecStringAndEcho(char *s);

#endif // _SERIAL_H_