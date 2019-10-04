/*
 * TIMER_module.h
 *
 *  Created on: Oct 4, 2019
 *      Author: marim
 */

#ifndef TIMER_MODULE_H_
#define TIMER_MODULE_H_


#include"standard_types.h"
#include"common_macros.h"
#include"AVR_configrations.h"

typedef enum{
	TIMER0 , TIMER1 , TIMER2
}timerSelect;

//operation mode for timer
typedef enum{
	NORMAL, CTC_0=2 , CTC_1=4
}operationMode;
//prescaling for timer0 and timer1
typedef enum {
	NO_CLOCK_0, FCPU_0, FCPU_8_0 , FCPU_64_0, FCPU_256_0 , FCPU_1024_0
}clockSelect_Timer0;

//prescaling for timer2
typedef enum{
	NO_CLOCK_2 , FCPU_2, FCPU_8_2 ,FCPU_32_2 ,FCPU_64_2, FCPU_128_2 , FCPU_256_2 , FCPU_1024_2
}clockSelect_Timer2;
typedef struct {
	timerSelect channelNum;
	operationMode mode;
	clockSelect_Timer0 clock0;
	clockSelect_Timer2 clock2;
	uint16 counterInit;
	uint16 outputCompare;
}timerConfigration;

void timer_init(const timerConfigration *);
void callBackFunction(void(*ptr)(void));

#endif /* TIMER_MODULE_H_ */
