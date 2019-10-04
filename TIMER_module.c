/*
 * TIMER_module.c
 *
 *  Created on: Oct 4, 2019
 *      Author: marim
 */



#include"TIMER_module.h"
static void (*G_ptr) (void) = NULL;
//executed code for overflow interrupt in timer0
ISR(TIMER0_OVF_vect){
	if(G_ptr != NULL){
		(* G_ptr)();    //call the function
	}
}
//executed code for compare interrupt in timer0
ISR(TIMER0_COMP_vect){
	if(G_ptr != NULL){
		(* G_ptr)();    //call the function
	}
}
//executed code for overflow interrupt in timer2
ISR(TIMER2_OVF_vect){
	if(G_ptr != NULL){
		(* G_ptr)();    //call the function
	}
}
//executed code for  compare interrupt in timer2
ISR(TIMER2_COMP_vect){
	if(G_ptr != NULL){
			(* G_ptr)();    //call the function
		}
}
//executed code for overflow interrupt in timer1
ISR(TIMER1_OVF_vect){
	if(G_ptr != NULL){
		(* G_ptr)();    //call the function
	}
}
//executed code for compare interrupt in timer1
ISR(TIMER1_COMPA_vect){
	if(G_ptr != NULL){
		(* G_ptr)();    //call the function
	}
}

void timer_init(const timerConfigration* ptrStruc){
	//activate timer0
	if(ptrStruc -> channelNum == TIMER0){
		//activate bit7 in TCCR0
		SET_BIT(TCCR0,FOC0);
		//inserting timer operation mode in bit 3 and bit 6 in TCCR0 register
		TCCR0 = (TCCR0 & 0xB7) | ((((ptrStruc -> mode << 2) & 0x08) | ((ptrStruc -> mode << 6) & 0x40)) |(0x80));
		//inserting clock in the first 3 bits in TCCR0 register
		TCCR0 = (TCCR0 & 0xF8) | (ptrStruc -> clock0);
		//counter initialization
		TCNT0 = (uint8)(ptrStruc -> counterInit) ;
		//activate normal mode operation
		if(ptrStruc -> mode == NORMAL){
			CLEAR_BIT(TCCR0,COM00);
			CLEAR_BIT(TCCR0,COM01);
			//enable overflow interrupt
			SET_BIT(TIMSK,TOIE0);
		}
		//activate compare mode operation
		else {
			CLEAR_BIT(TCCR0,COM00);
			CLEAR_BIT(TCCR0,COM01);
			OCR0 = (uint8)(ptrStruc -> outputCompare);
			//enable compare mode interrupt
			SET_BIT(TIMSK,OCIE0);
		}
	}
	//activate timer2
	else if (ptrStruc -> channelNum == TIMER2){
		SET_BIT(TCCR2,FOC2);
		//inserting timer operation mode in bit 3 and bit 6 in TCCR2 register
		TCCR2 = (TCCR2 & 0xB7) | ((((ptrStruc -> mode << 2) & 0x08) | ((ptrStruc -> mode << 6) & 0x40)) |(0x80));
		//inserting clock in the first 3 bits in TCCR2 register
		TCCR2 = (TCCR2 & 0xF8) | (ptrStruc -> clock2);
		//counter initialization
		TCNT2 = (uint8)(ptrStruc -> counterInit) ;
		//activate normal mode operation
		if(ptrStruc -> mode == NORMAL){
			CLEAR_BIT(TCCR2,COM20);
			CLEAR_BIT(TCCR2,COM21);
			//enable overflow interrupt
			SET_BIT(TIMSK,TOIE2);
		}
		//activate compare mode operation
		else {
			CLEAR_BIT(TCCR2,COM20);
			CLEAR_BIT(TCCR2,COM21);
			OCR2 = (uint8)(ptrStruc -> outputCompare);
			//enable compare mode interrupt
			SET_BIT(TIMSK,OCIE2);
		}
	}
	//activate timer1
	else {
         CLEAR_BIT(TCCR1A,COM1A0);
         CLEAR_BIT(TCCR1A,COM1A1);
         SET_BIT(TCCR1A,FOC1A);
         //inserting timer mode operation in TCCR1A and TCCR1B
         TCCR1A = (TCCR1A & 0xFC) | ((ptrStruc -> mode) & 0x03);
         TCCR1B = (TCCR1B & 0xE7) | (((ptrStruc -> mode)<<1) & 0x18);
         //inserting clock
         TCCR1B = (TCCR1B & 0xF8) | (ptrStruc -> clock0);
         //counter initialization
         TCNT1= ptrStruc -> counterInit ;
         if(ptrStruc -> mode == NORMAL){
        	 //enable interrupt
        	 SET_BIT(TIMSK,TOIE1);
         }
         else {
        	 OCR1A= ptrStruc -> outputCompare;
        	 //enable interrupt
        	 SET_BIT(TIMSK,OCIE1A);
         }

	}
}
	void callBackFunction (void(*ptr)(void)){
		G_ptr=ptr;
	}

