#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT4_vect){
	PORTD=0xff;
}

int main(void)
{	
    while (1){
		EIMSK|=(1<<INT4);
		EICRB|= 0x00;
		//EICRB|=(1<<ISC41);
	
		DDRD=0xff;
		
		DDRE=0x00;
		sei();
		PORTD=0x00;
			}
		return 0;
}


