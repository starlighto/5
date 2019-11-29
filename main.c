/*
 * GccApplication14.c
 *
 * Created: 2019-02-09 오전 2:30:29
 * Author : BITDOL
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define enablemotor1() PORTD&=~0x04
#define disablemotor1() PORTD|=0x04
#define speedmotor1(s) OCR3B=s

int main(void)
{
	DDRD=0xff;
	PORTD=0x80;
	DDRE=0b00010000;
	PORTE=0b00010000;
	
	TCCR3A|=(1<<WGM30);
	TCCR3B|=(1<<WGM32);
	
	TCCR1A|=(1<<COM3B1);
	TCCR1B|=(1<<CS31)|(1<<CS30);;
	
	OCR3B=0;
	
	while(1){
		enablemotor1();
		PORTD|=(1<<1);
		for (int i=0;i<256;i++)
		{speedmotor1(i);
			_delay_ms(25);
		}
		_delay_ms(1000);
		speedmotor1(0);
		disablemotor1();
	}
	return 0;
	
}

