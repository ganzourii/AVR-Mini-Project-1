/*
 *  ClockProject.c
 *
 *  Created on: Aug 16, 2018
 *  Author: Ahmad Ganzouri
 *
 *
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char i;
unsigned char Num[6] = {0,0,0,0,0,0};

ISR (TIMER1_COMPA_vect)
{   Num[0]++;
	if (Num[0] > 9)
	{
		Num[0]=0;
		Num[1]++;
		if (Num[1] > 5)
		{
		Num[1]=0;
		Num[2]++;
		if (Num[2] > 9)
		{
		Num[2]=0;
		Num[3]++;
		if (Num[3] > 5)
		{
		Num[3]=0;
		Num[4]++;
		if (Num[4] > 9)
		{
		Num[4]=0;
		Num[5]++;
		if (Num[5] > 9)
		{
		Num[5]=0;
		   }
		  }
		 }
		}
	  }
	}


}

void Timer1_Init(void)
{
	TCNT1  =  0 ;
	OCR1A  = 15624;
	TCCR1A = (1 << FOC1A); /* Non PWM */
	TCCR1B = (1 << WGM12) | (1 << CS12);  /* WGM12 to  set CTC Mode - CS12 to Set prescaler Fcpu/256 */
	TIMSK  = (1 << OCIE1A); /* Setting CTC Interrupt */
	 /* Setting the TOP to get f timer = 1Hz. */
}


ISR (INT0_vect)
{
	for (i=0;i<6;i++)
	{
		Num[i]=0;
	}

	Timer1_Init();
}

void INT0_Init(void)
{
	SREG &= ~(1<<7);
	DDRD &= ~(1 << PD2); /* Set PD2 as input pin */
	PORTD |= (1<<PD2);    /* Enable the internal Pull Up */
	GICR |= (1<<INT0);    /* Enable the INT0 Interrupt */
	MCUCR = (1 <<ISC01); /* Set the interrupt with the falling edge */
	SREG |= (1<<7);       /* Enable I-bit */
}


int main (void)
{

	INT0_Init();

	DDRC |=  0x0F;
	PORTC &= 0xF0;
	DDRB |= 0x3F;
	SREG |= (1<<7);

	Timer1_Init();



	while(1)
	{


				for (i=0;i<6;i++)
					{
					PORTB =	(PORTB & 0xC0) | (1 << i);
					PORTC = (PORTC & 0xF0) | (Num[i] & 0x0F);
					_delay_ms(1);
					}

	}
}
