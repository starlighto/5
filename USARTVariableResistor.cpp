#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

unsigned char G_DATA(void){
	while(!(UCSR0A&0X80));
	return UDR0;
}
void S_DATA(unsigned char DATA){
	while(!(UCSR0A&0X20));
	UDR0=DATA;
}
int G_VALUE(void){
	ADMUX=0x0;
	ADCSRA=0xE7;
	while((ADCSRA&0x10)==0);
	return ADCW;
}
int main(void)
{
	int r=0;
	unsigned char str[4];
	int i=0;
	DDRF=0x00;
	
	UCSR0A=0x00;
	UCSR0B=0b00011000;
	UCSR0C=0b00000110;
	
	UBRR0H=0;
	UBRR0L=103;
	
	while (1)
	{
		r=G_VALUE()/(1023/255);
		str[3]=r/1000;
		str[2]=(r%1000)/100;
		str[1]=((r%1000)%100)/10;
		str[0]=r%10;
		while(i<4){
			S_DATA(str[3-i]+48); //0이 아스키코드로 +48
			i++;
		}
		i=0;
		S_DATA(10); //줄바꿈
		_delay_ms(500);
	}
}

