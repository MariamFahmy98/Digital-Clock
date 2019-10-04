/*
 * application.c
 *
 *  Created on: Oct 4, 2019
 *      Author: marim
 */

#include"TIMER_module.h"

uint8 count_Seconds=0;
uint8 count_Minutes=0;
uint8 count_hours=0;
uint8 count=0;
uint8 digitSeconds,digitMinutes,digithours;
uint8 count_Seconds1,count_Minutes1,count_hours1;

void enableInterrupt0 (void){
	GICR |= (1<<INT0);
	MCUCR |= (1<<ISC01);    //making interrupt with the falling edge
	MCUCR &= ~(1<<ISC00);
	DDRD &= ~(1<<PD2);
	PORTD |= (1<<PD2);

}
ISR(INT0_vect){
	count++;
	if(count<2){
		//for stopping the digital watch
		timerConfigration config = {TIMER1,CTC_1,NO_CLOCK_0,0,0,0};
		timer_init(&config);
	}
	else{
		count=0;
		timerConfigration config = {TIMER1,CTC_1,FCPU_1024_0,0,0,1000};
		timer_init(&config);
	}
}
void enableInterrupt2(void){
	GICR |= (1<<INT2);
	MCUCSR &= ~(1<<ISC2);   //making interrupt with the falling edge
	DDRB &= ~(1<<PB2);
	PORTB |= (1<<PB2);
}
ISR(INT2_vect){
	// for reseting the digital watch
		count_hours=0;
		count_Minutes=0;
		count_Seconds=0;

}
void calculateSeconds(void){
	count_Seconds++;
	digitSeconds= count_Seconds % 10;
	count_Seconds1= count_Seconds / 10;
	if(count_Seconds==59){
		count_Seconds=0;
		count_Minutes++;
		digitMinutes= count_Minutes % 10;
		count_Minutes1= count_Minutes / 10;
		if(count_Minutes==59){
			count_Minutes=0;
			count_hours++;
			digithours = count_hours % 10;
			count_hours1= count_hours / 10;
			if(count_hours==24){
				count_hours=0;
			}
		}
	}
}
int main(void){
	SREG=(1<<7);
	enableInterrupt0();
	enableInterrupt2();
	timerConfigration config= {TIMER1,CTC_1,FCPU_1024_0,0,0,1000};
	timer_init( & config );
	callBackFunction(calculateSeconds);
	DDRC |= 0x0f;        //the first 4 pins in PORTC are outputs to the decoder
	PORTC &= 0xf0;       //the first 4 pins are initialized by zero
	DDRA |= 0x3f;        //the first 6 pins in PORTA are output (connected to npn transistors)
	PORTA = 0x01;        //PORTA is initialized by one (activating the first 7 segment of seconds)
	while(1){
		PORTA = 0x01;
		PORTC = (PORTC & 0xf0) | (digitSeconds & 0x0f);
		_delay_ms(5);
		PORTA = 0x02;
		PORTC = (PORTC & 0xf0) | (count_Seconds1 & 0x0f);
		_delay_ms(5);
		PORTA = 0x04;
		PORTC = (PORTC & 0xf0) | (digitMinutes & 0x0f);
		_delay_ms(5);
		PORTA = 0x08;
		PORTC = (PORTC & 0xf0) | (count_Minutes1 & 0x0f);
		_delay_ms(5);
		PORTA = 0x10;
		PORTC = (PORTC & 0xf0) | (digithours & 0x0f);
		_delay_ms(5);
		PORTA = 0x20;
		PORTC = (PORTC & 0xf0) | (count_hours & 0x0f);
		_delay_ms(5);
	}
}
