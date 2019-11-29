#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define enablemotor1() PORTD&=~0x04
#define disablemotor1() PORTD|=0x04
#define speedmotor1(s) OCR3B=s     //2^16-1까지

int G_VALUE(void){
	ADMUX=0X0; //단극성 입력 
	ADCSRA=0XE7; //128분주비,7번 ADC Enable_6번 ADC변환 시작 탕!_5번 ADC RUN 0만들기 전까지 센서값 받기
	
	while((ADCSRA&0X10)==0x0); //변환완료검사,ADC변환이 완료되면(ADC버퍼에 값이 저장되면) ADIF라고 하는 인터럽트 플래그가 set된다 while문으로 ADIF가 1이 될때까지 기다려.
	return ADCW;              //저항에 걸리는 전압[6V]을 0~1023사이의 디지털 값으로 변환한 값 .문자형 입력값을 변환해서 반환_INT형
}
unsigned char P_DATA(void){
	while(!(UCSR0A&0X80));//값 받기
	return UDR0;
}
void S_DATA(unsigned char DATA){
	while(!(UCSR0A&0X20));//값 출력
	UDR0=DATA;
}
int main(void)
{
	float r = 0;
	unsigned char st;
	
	DDRD=0xff;//출력
	PORTD=0x80;//pd7에 5v인가
	
	DDRE=0b00010000;
	PORTE=0b00010000;
	
	TCCR3A|=(1<<WGM30);//타이머/카운트 38.비트 고속 pwm모드[top값:0x00ff] ocr3b 255까지
	TCCR3B|=(1<<WGM32);
	
	TCCR3A|=(1<<COM3B1);
	TCCR3B|=(1<<CS31)|(1<<CS30); //타이머 카운터: 분주비 64[사용 안함]
	OCR3B=0;                     //dc motor
	
	DDRF=0X00;
	UCSR0A=0X0;
	UCSR0B=0B00010000;
	UCSR0C=0B00000110;
	UBRR0H=0;
	UBRR0L=103;                  //uart
	
	while(1){
			r = G_VALUE()/(1023/255);//ADC값 R에 저장
			
			st='a';
			enablemotor1();
			PORTD|=(1<<1);
			
			/*if (P_DATA==st)
			{PORTD|=(1<<1);} //CW_in1:low,in2:high,enable:low,pwm:high/OR 1을 1비트만큼 왼쪽으로 이동
			else
			{PORTD =0B10001000;}//CCW_in1[1]:high,in2[2]:low,enable[3]:low,pwm[5]:high*/
			
			speedmotor1(r);//0~255까지
			_delay_ms(10);		
			disablemotor1();
			}
	return 0;
}




