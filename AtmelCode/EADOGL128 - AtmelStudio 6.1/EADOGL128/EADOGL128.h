/*
Reihe = Spalte
Page  = acht gebündelte Pixel -> Page 0(1) enthält Reihen 0-7(8-15)
*/

#ifndef EADOGL128_H
#define EADOGL128_H

#define F_CPU 8000000 //>4*f_ExtQuarz
#define F_CRYSTAL 32768
#define PRESCALER_TIMER2 128
#include <util/delay.h>
#include <avr/sbit.h>
#include <avr/io.h>
#include <math.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <avr/sleep.h>
#include <string.h>//strlen()
#include "symbols"
#include "EADOGL128_commands.c"


#define BTN_PRESS_LONG 1.5f //1.5 Sekunden ist langes drücken einer Taste
#define ALARM_TYPE true//genutzt für Anzeige von Alarm- oder Uhrzeit
#define TIME_TYPE false
#define POS_DATE_SET 12
#define POS_DATE_STD 47
#define YPOS_YEAR 40
#define OFF false
#define ON true
#define LIGHT_ON_DURATION 3 //wieviele Sekunden bleibt Licht an, wenn Taster gedrückt


//Konvertiert einen String in eine Reihenfolge von letter
void convertString(char [], int []);

int get_monthWidth();

int get_dayWidth();

void print_date();

void print_day(int, int);

void print_month(int, int);

void print_time(bool);

int print_hour();

void print_minute();

void update_timeXPos();

void increment_date();

void update_time();

void reset_alarmLogo();

void print_alarmLogo();

bool check_TimeUpdate();

void goodNight();

void configureTimerAndInterrupts();

int print_timeDot(int, int); 

void start_btnPress();

void stop_btnPress();

void show_mainMenu();

void print_stdDisplay();

void print_mainMenu();

void clear_pixelMatrix();

void print_ASCIIString(int, int, int*, int);

void print_menuSelection(int);

void remove_menuSelection(int);

int get_menuSelection(int, int);

void set_alarm();

void set_time(bool);

void set_date();

void show_mainMenu2();

void set_timeParameter(int *, int, bool);

void wait_drehencDone();

void wakeUp_Anja();

int get_timeWidth(int);

int get_yearWidth();

void print_year();

int get_dateWidth();

int get_yearXPos();

int get_dateXPos();

void set_day();

void set_month();

void set_year();

int get_stringWidth();
#endif