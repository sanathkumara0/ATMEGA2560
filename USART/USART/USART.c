/*
 * USART.c
 *
 * Created: 6/21/2024 12:23:55 PM
 *  Author: Sanath Kumara
 */ 
#include "USART.h"

//USART0 used for USB connection 
void initUART0(uint16_t baud_rate){
	// Set baud rate registers
	uint16_t ubrr = F_CPU / 16 / baud_rate - 1;
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;

	// Enable receiver and transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	// Set frame format: 8 data bits, 1 stop bit, no parity
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void initUART1(uint16_t baud_rate){
	// Set baud rate registers
	uint16_t ubrr = F_CPU / 16 / baud_rate - 1;
	UBRR1H = (uint8_t)(ubrr >> 8);
	UBRR1L = (uint8_t)ubrr;

	// Enable receiver and transmitter
	UCSR1B = (1 << RXEN0) | (1 << TXEN0);

	// Set frame format: 8 data bits, 1 stop bit, no parity
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
}

void sendCharUSART0(char data){
	while (!(UCSR0A & (1 << UDRE0))); // Wait for empty transmit buffer
	UDR0 = data; // Send 'A'
}

void sendCharUSART1(char data){
	while (!(UCSR1A & (1 << UDRE1))); // Wait for empty transmit buffer
	UDR1 = data; 
}

char receiveCharUSART0(){
	while (!(UCSR0A & (1 << RXC0))); // Wait for data to be received
	char receivedChar = UDR0; // Read received data
	return receivedChar;
}

char receiveCharUSART1(){
	while (!(UCSR1A & (1 << RXC1))); // Wait for data to be received
	char receivedChar = UDR1; // Read received data
	return receivedChar;
}