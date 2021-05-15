#include <avr/io.h>
#include "util/delay.h"
#include <avr/interrupt.h>
void PORTS_INIT()
{
    //init port c for 7447 decoder
    DDRC |= 0X0F;   //FIRST 4 PINS AS OUTPUT;
    PORTC &= ~0x0F; //set the 4 pins as 0
    /////init port a for 7 seg anodes
    DDRA |= 0X3F;   //FIRST 6 PORTS AS OUTPUT;
    PORTA &= ~0X3F; //SET THE 6 PINS AS ZERO
}
void TIMER1_INIT()
{
    TCCR1A = (1 << FOC1A);
    TCCR1B = (1 << CS12) | (1 << CS10)|(1<<WGM12); //1024 PRESCALAR AND CTC MODE ENABLE

    /*
NON PWM MODE ->FOC1A
CTC MODE ->WGM01
1024 PRESCALAR ->(1<<CS02)|(1<<CS00)

*/
    OCR1A = 977;            // COUNT TO 1 SECOND WITH 1024 PRESCALAR
    TCNT1 = 0;              //INIT BY 0
    TIMSK |= (1 << OCIE1A); //ENABLE INTERRUPT WITH TIMER 1A
}

void INT0_INIT()
{
    //falling edge internal pullup init
    DDRD &= ~(1 << PD2); //SET PD2 AS INPUT;
    PORTD |= (1 << PD2); //ENABLE INTERNAL PULLUP RESISTOR FOR PD2
    GICR |= (1 << INT0); //ENABLE INTERRUPTS FOR PORTD2/INT0

    //ENABLE FALLING EDGE INTERRUPT:
    MCUCR |= (1 << ISC01);  //
    MCUCR &= ~(1 << ISC00); //
}
//////////////ISR FOR INT0

void INT1_INIT()
{
    //rising edge using the external pull down
    DDRD &= ~(1 << PD3);  //SET PD3 AS INPUT;
    PORTD &= ~(1 << PD3); //DISABLE INTERNAL PULLUP RESISTOR FOR PD3
    GICR |= (1 << INT1);  //ENABLE INTERRUPTS FOR PORTD3/INT1

    MCUCR |= (1 << ISC11) | (1 << ISC10); // //ENABLE RISING EDGE INTERRUPT:
}

void INT2_INIT()
{
    //Falling edge using the internal pull up
    DDRB &= ~(1 << PB2); //SET PB2 AS INPUT;
    PORTB |= (1 << PB2); //ENABLE INTERNAL PULLUP RESISTOR FOR PB2
    GICR |= (1 << INT2); //ENABLE INTERRUPTS FOR PORTB2/INT1

    //ENABLE FALLING EDGE INTERRUPT:
    MCUCSR &= ~(1 << ISC2); //
}
