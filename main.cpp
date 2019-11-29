#define F_CPU 16000000L
#include <util/delay.h>
#include <avr/io.h>

int main(void)
{
	unsigned char ch[5];
	int i;
	
	UCSR0A= 0x0;
	UCSR0B = 0b00011000;
	UCSR0C=0b00000110;

	UBRR0H = 0;
	UBRR0L=103;

	while(1){
		for(i=0;i<3;i++){
		while((UCSR0A&0x80)==0x0); // RXC0=1까지 대기하다가 다음칸으로 넘겨주고 
		ch[i] = UDR0;              //받기
		}
		for(i=0;i<3;i++){
		while((UCSR0A&0x20)==0x0); //이문장이 실행되기 전까지 값이 쌓이다가 -> 값 출력!
		UDR0=ch[i];   //출력
		}
	}return 0;
}
