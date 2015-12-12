/*
Autor: Malte Ollenschläger
Dieses Werk ist lizenziert unter einer Creative Commons Namensnennung - Nicht-kommerziell - Weitergabe unter gleichen Bedingungen 4.0 International Lizenz.
*/

#define  UP true
#define DOWN false

#define MP3_T3 3
#define MP3_T1 1
#define MP3_T4 4
#define MP3_T5 5
#define MP3_ONOFF 6
#define AMP_MUTE 7
#define AMP_STBY 8
#define PUSH_DURATION 70
#define PUSH_DURATION_LONG 5000

void boot_amp();

void shutdown_amp();

void amp_on();

void amp_off();

void mute_on();

void mute_off();

void mp3Player_onoff();

//void mp3Player_off();

void next_song();

void music_pause();

void volume(bool);

void push_button(uint8_t);

void release_button(uint8_t);