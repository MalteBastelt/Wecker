/*
 * Schlaftest.c
 *
 * Created: 26.07.2015 21:02:08
 *  Author: Malte
 */ 


#include <avr/io.h>
#include <avr/sleep.h>

int main(void)
{
	DDRC = 0;
	PORTC = 0;
    while(1)
    {
        SMCR |= (1<<SE);
        SMCR |= ((1<<SM1)|(1<<SM0));
        OCR2A = 1;//Sichergehen, dass genug Zeit seit letztem Schlafen vergangen ist
        while((ASSR & (1<<OCR2AUB)));//Warten bis Schreiben fertig, erst dann darf man schlafen
        sleep_cpu();
    }
}