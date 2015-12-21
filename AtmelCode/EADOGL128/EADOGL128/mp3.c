/*
Autor: Malte Ollenschläger
Dieses Werk ist lizenziert unter einer Creative Commons Namensnennung - Nicht-kommerziell - Weitergabe unter gleichen Bedingungen 4.0 International Lizenz.
*/
#include "mp3.h"
#include "sbit.h"

void boot_amp(){//Um Knack beim Einschalten zu verhindern
	mute_on();
	amp_on();
	_delay_ms(200);
	mute_off();
}

void shutdown_amp(){
	mute_on();
	_delay_ms(200);
	amp_off();
	//mute_off();
}

void amp_on(){
	push_button(AMP_STBY);
	_delay_ms(200);
}

void amp_off(){
	release_button(AMP_STBY);
}

void mute_on(){
	release_button(AMP_MUTE);
}

void mute_off(){
	push_button(AMP_MUTE);
}

void mp3Player_onoff(){
	push_button(MP3_ONOFF);
	_delay_ms(PUSH_DURATION_LONG);
	release_button(MP3_ONOFF);
	_delay_ms(PUSH_DURATION_LONG+3000);//Pause vor nächstem Tastendruck erzwingen
}

void next_song(){
	push_button(MP3_T1);
	_delay_ms(PUSH_DURATION);
	release_button(MP3_T1);
	_delay_ms(PUSH_DURATION);//Pause vor nächstem Tastendruck erzwingen
}

void play_pause(){
	push_button(MP3_ONOFF);
	_delay_ms(PUSH_DURATION);
	release_button(MP3_ONOFF);
	_delay_ms(PUSH_DURATION);//Pause vor nächstem Tastendruck erzwingen
}

void volume(bool direction){
	if(direction == UP){
		push_button(MP3_T4);
		_delay_ms(PUSH_DURATION);
		release_button(MP3_T4);
	} else {
		push_button(MP3_T3);
		_delay_ms(PUSH_DURATION);
		release_button(MP3_T3);
	}
	_delay_ms(PUSH_DURATION);//Pause vor nächstem Tastendruck erzwingen
}

void push_button(uint8_t button){
	
	switch(button){
		case MP3_T1: 
			DDRD |= (1<<PORTD2);//Pin als Ausgang setzen
			PORTD &= ~(1<<PORTD2);//Pin auf GND setzen
			break;
		case MP3_T3:
			DDRD |= (1<<PORTD1);
			PORTD &= ~(1<<PORTD1);
			break;
		case MP3_T4:
			DDRD |= (1<<PORTD3);
			PORTD &= ~(1<<PORTD3);
			break;
		case MP3_ONOFF:
			DDRD |= (1<<PORTD0);
			PORTD |= (1<<PORTD0);
			break;
		case AMP_MUTE:
			//DDRD |= (1<<PORTD7);
			PORTD |= (1<<PORTD7);	
			break;
		case AMP_STBY:
			//DDRB |= (1<<PORTB0);
			PORTB |= (1<<PORTB0);				
	}
}

void release_button(uint8_t button){
	switch(button){
		case MP3_T1:
			PORTD |= (1<<PORTD2);//Pin sicherheitshalber auf eins
			DDRD &= ~(1<<PORTD2);//Pin als Eingang setzen
			break;	
		case MP3_T3:
			PORTD |= (1<<PORTD1);
			DDRD &= ~(1<<PORTD1);
			break;	
		case MP3_T4:
			PORTD |= (1<<PORTD3);
			DDRD &= ~(1<<PORTD3);
			break;	
		case MP3_ONOFF:
			PORTD &= ~(1<<PORTD0);
			DDRD &= ~(1<<PORTD0);
			break;
		case AMP_MUTE:
			PORTD &= ~(1<<PORTD7);
			//DDRD &= ~(1<<PORTD7);
			break;
		case AMP_STBY:
			PORTB &= ~(1<<PORTB0);
			//DDRB &= ~(1<<PORTB0);
			
			break;
	}
}