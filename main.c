/*
 * dcmotorspeedcw.cpp
 *
 * Created: 2019-02-18 오후 10:09:04
 * Author :ADC+DC MOTOR
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define enablemotor1() PORTD &=~0x04
#define disablemotor1() PORTD|=0x04
#define speedmotor1(s) OCR3B=s //ocr범위

int G_VALUE(void){
	ADMUX=0X0; //기준전압 =aref 지정
	ADCSRA=0XE7; //7번 ADC Enable_6번 ADC변환 시작 탕!_5번 ADC RUN 0만들기 전까지 센서값 받기
	
	while((ADCSRA&0X10)==0);//변환완료검사.ADC변환이 완료되면(ADC버퍼에 값이 저장되면) ADIF라고 하는 인터럽트 플래그가 set된다 while문으로 ADIF가 1이 될때까지 기다려.
	return ADCW;   //저항에 걸리는 전압을 0~1023사이의 디지털 값으로 변환한 값 .문자형 입력값을 변환해서 반환_INT형, adc=in/기준전압*1024
}

void S_DATA(unsigned char DATA){
	while(!(UCSR0A&0X20));//값 출력
	UDR0=DATA;
}
int main(void)
{
	//unsigned int r=0;
	
	DDRD=0xff;
	PORTD=0x80;//pd7 인가
	DDRE=0b00010000;
	PORTE=0b00010000;
	
	TCCR3A|=(1<<WGM30);
	TCCR3B|=(1<<WGM32);
	
	TCCR1A|=(1<<COM3B1);
	TCCR1B|=(1<<CS31)|(1<<CS30);;
	OCR3B=0;//dc motor
	
	DDRF=0X00;
	UCSR0A=0X00;
	UCSR0B=0B00011000;
	UCSR0C=0B00000110;
	UBRR0H=0;
	UBRR0L=103;//uart
	
	while(1){
			//r=G_VALUE()*1023;//ADC값 R에 저장
			enablemotor1();
			unsigned char ad;
			
			while(!(UCSR0A&0X80));//값 받기
			ad=UDR0;
			
			if (ad=='A')
			{PORTD=0B01001000;} //CW_in1:low,in2:high,enable:low,pwm:high[0B01001000]/OR 1을 1비트만큼 왼쪽으로 이동
			else
			{PORTD=0B10001000;}//CCW_in1:high,in2:low,enable:low,pwm:high 0B01110111
					
			speedmotor1(10000);
			_delay_ms(1000);
			
			//speedmotor1(0);
			disablemotor1();
			 S_DATA(ad);
			}
		S_DATA(10);
		_delay_ms(500);
	
}
//?UART로 입력값이 저항과 방향 두개인데?



