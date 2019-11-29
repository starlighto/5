#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char led=0xFE;

int main(void)
{
	DDRD=0xFF;
	PORTD=led;
	TIMSK=0x04;
	TCCR1A=0x00;
	TCCR1B=0x05;
	TCCR1C=0x00;
	TCNT1=49911;
	sei();
	while (1);
}
ISR(TIMER1_OVF_vect){
	TCNT1=49911;
	led=(led<<1)|0x01;
	if(led==0xFF)led=0xFE;
	PORTD=led;
}

