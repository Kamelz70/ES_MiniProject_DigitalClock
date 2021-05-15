/*
 * APIs.c
 *
 *  Created on: May 15, 2021
 *      Author: moham
 */
#define F_CPU 1000000
#include <avr/io.h>
#include <avr/interrupt.h>

void PORTS_INIT(){
    //init port c for 7447 decoder
    DDRC|=0X0F;//FIRST 4 PINS AS OUTPUT;
    PORTC&=~0x0F;//set the 4 pins as 0

    /////init port a for 7 seg anodes
    DDRA|=0X3F;//FIRST 6 PORTS AS OUTPUT;
    PORTA &=~ 0X3F;//SET THE 6 PINS AS ZERO
}
void TIMER1_INIT()
{

	}

void INT0_INIT()
{
    //falling edge internal pullup init
    DDRD&=~(1<<PD2);//SET PD2 AS INPUT;
    PORTD|=(1<<PD2);//ENABLE INTERNAL PULLUP RESISTOR FOR PD2
    GICR|=(1<<INT0);//ENABLE INTERRUPTS FOR PORTD2/INT0

    //ENABLE FALLING EDGE INTERRUPT:
    MCUCR|=(1<<ISC01);//
    MCUCR&=~(1<<ISC00);//


	}
    //////////////ISR FOR INT0

void INT1_INIT()
{
    //rising edge using the external pull down
        DDRD&=~(1<<PD3);//SET PD3 AS INPUT;
    PORTD&=~(1<<PD3);//DISABLE INTERNAL PULLUP RESISTOR FOR PD3
    GICR|=(1<<INT1);//ENABLE INTERRUPTS FOR PORTD3/INT1

    MCUCR|=(1<<ISC11)|(1<<ISC10);// //ENABLE RISING EDGE INTERRUPT:
	}

void INT2_INIT()
{
    //Falling edge using the internal pull up
        DDRB&=~(1<<PB2);//SET PB2 AS INPUT;
    PORTB|=(1<<PB2);//ENABLE INTERNAL PULLUP RESISTOR FOR PB2
    GICR|=(1<<INT2);//ENABLE INTERRUPTS FOR PORTB2/INT1

    //ENABLE FALLING EDGE INTERRUPT:
    MCUCSR&=~(1<<ISC2);//

}


ISR(INT0_vect)
{
    //reset clock

}

ISR(INT2_vect)
{
//resume the stop watch.
}
ISR(INT1_vect)
{
    ////pause stopwatch
}
