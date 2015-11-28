/*
Autor: Malte Ollenschläger
Dieses Werk ist lizenziert unter einer Creative Commons Namensnennung - Nicht-kommerziell - Weitergabe unter gleichen Bedingungen 4.0 International Lizenz.
*/
#include "mp3.h"
#include "sbit.h"

void amp_on(){
	//Standby off
	//Vcc On
}

void amp_off(){
	//Standby on
	//Vcc off
}

void mute_on(){
	
}

void mute_off(){
	
}

void mp3Player_on(){
	_delay_ms(2000);
}

void mp3Player_off(){
	
}

void next_song(){
	push_button(MP3_T1);
	push_button(MP3_T5);
	_delay_ms(PUSH_DURATION);
	release_button(MP3_T1);
	release_button(MP3_T5);
}

void play_pause(){

}

void volume(bool direction){
	if(direction == UP){
		push_button(MP3_T4);
		push_button(MP3_T5);
		_delay_ms(PUSH_DURATION);
		release_button(MP3_T4);
		release_button(MP3_T5);
	} else {
		push_button(MP3_T3);
		push_button(MP3_T5);
		_delay_ms(PUSH_DURATION);
		release_button(MP3_T3);
		release_button(MP3_T5);
	}
}

void push_button(uint8_t button){
	switch(button){
		case MP3_T1: 
			DDRD |= (1<<PORTD6);//Pin als Ausgang setzen
			PORTD &= ~(1<<PORTD6);//Pin auf GND setzen
			break;
		case MP3_T3:
			DDRD |= (1<<PORTD5);
			PORTD &= ~(1<<PORTD5);
			break;
		case MP3_T4:
			DDRD |= (1<<PORTD7);
			PORTD &= ~(1<<PORTD7);
			break;
		case MP3_T5:
			DDRB |= (1<<PORTB0);
			PORTB &= ~(1<<PORTB0);	
			break;	
	}
}

void release_button(uint8_t button){
	switch(button){
		case MP3_T1:
			DDRD &= ~(1<<PORTD6);//Pin als Eingang setzen
			PORTD |= (1<<PORTD6);//Pin sicherheitshalber auf eins
			break;	
		case MP3_T3:
			DDRD &= ~(1<<PORTD5);
			PORTD |= (1<<PORTD5);
			break;	
		case MP3_T4:
			DDRD &= ~(1<<PORTD7);
			PORTD |= (1<<PORTD7);
			break;	
		case MP3_T5:
			DDRB &= ~(1<<PORTB0);
			PORTB |= (1<<PORTB0);
			break;	
	}
}