/*
 * Digital_Clock.c
 *
 *  Created on: May 15, 2021
 *      Author: moham
 */
#define F_CPU 1000000
/////////////////////////////////////
#include <avr/io.h>
#include <avr/interrupt.h>
#include "util/delay.h"
///////////////////////////////////////
typedef struct time
{
	unsigned short S; //seconds
	unsigned short M; //minutes
	unsigned short H; //hours
} time;

time T;
unsigned char TICK1_FLAG = 0;
////////////////////////////////////
int main()
{

	TIMER1_INIT();
	INT1_INIT();
	INT0_INIT();
	INT2_INIT();
	PORTS_INIT();
	SREG |= (1 << 7); //ENABLE GLOBAL INTERRUPT

	unsigned char i = 0;
	T.S = 0;
		T.M = 0;
		T.H = 0;
	while (1)
	{
		///update time if tick occurred
		if (TICK1_FLAG == 1)
		{
			T.S++;
			if (T.S > 60)
			{
				T.S = 0;
				T.M++;
				if (T.M > 60)
				{
					T.M = 0;
					T.H++;
					if (T.H > 24)
					{
						T.H = 0;
					}
				}
			}

			TICK1_FLAG = 0;
		}

		///////////////////////display time on 7 segment
		for (i = 0; i < 6; i++)
		{
			PORTA = (PORTA & 0XC0) | ((1 << i) & 0x3F);
			switch (i)
			{
			case 0:
				PORTC = (PORTC & 0XF0) | ((T.S % 10) & 0x0F);//first digit on seconds on first 7-seg
				break;
			case 1:
				PORTC = (PORTC & 0XF0) | ((T.S / 10) & 0x0F);//second digit on seconds on second 7-seg
				break;
			case 2:
				PORTC = (PORTC & 0XF0) | ((T.M % 10) & 0x0F);//same continues
				break;
			case 3:
				PORTC = (PORTC & 0XF0) | ((T.M / 10) & 0x0F);
				break;
			case 4:
				PORTC = (PORTC & 0XF0) | ((T.H % 10) & 0x0F);
				break;
			case 5:
				PORTC = (PORTC & 0XF0) | ((T.H / 10) & 0x0F);
				break;
			}
			_delay_ms(6);
		}
	}
}
//////////////////////////////////////////////ISRS
ISR(INT0_vect)
{
	//reset clock
	T.S = 0;
	T.M = 0;
	T.H = 0;
}

ISR(INT2_vect)
{
	//resume the stop watch.
	 TCCR1B |= ((1 << CS12) | (1 << CS10));

	
}
ISR(INT1_vect)
{
	////pause stopwatch
	 TCCR1B &= ~((1 << CS12) | (1 << CS10));

	 //DISABLE CLOCK SOURCE
}
ISR(TIMER1_COMPA_vect)
{
	TICK1_FLAG = 1;
}
