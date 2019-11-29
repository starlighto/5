/*
 * GccApplication13.cpp
 *
 * Created: 2019-02-09 오전 12:53:20
 * Author : BITDOL
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
void main(void)
{
	unsigned char ch;
	
	UCSR0A= 0x0;
	UCSR0B = 0b00011000;
	UCSR0C=0b00000110;

	UBRR0H = 0;
	UBRR0L=103;

	while(1){

		while((UCSR0A&0x80)==0x0); // RXC0=1 까지 대기
		{
			ch = UDR0;
		}


		while((UCSR0A&0x20)==0x0); //UDRE0=1 까지 대기
		{
			UDR0=ch;
		}

	}
}