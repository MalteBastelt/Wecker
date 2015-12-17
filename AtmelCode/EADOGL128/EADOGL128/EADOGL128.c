/*
Autor: Malte Ollenschläger
Dieses Werk ist lizenziert unter einer Creative Commons Namensnennung - Nicht-kommerziell - Weitergabe unter gleichen Bedingungen 4.0 International Lizenz.
*/ 

//SUCHE NACH "PRÜFE"

int cnt = 0;

#include "EADOGL128.h"

int hour = 14;
int minute = 0;
int seconds = 0;

int alarm_hour = 0;
int alarm_minute = 0;
int snoozeDuration = 5;//Minuten
uint8_t snoozeCounter = 0;

int day=30;
int month = 9;
int year = 2015;
int daysThisMonth = 31;

int timeXPos = 0;
int alarmXPos = 0;
static int timeYPos = 9;
volatile int timeUpdate=0;
long int timeAdvance = 0;
bool increment = true;

bool alarm = false;
bool menuOpen = false;
int volumeChange = 0;

int test = 0;
int rotary = 0;
volatile bool btn_drehenc_pushed = false;
volatile bool btn_light_pushed = false;
float btn_press_duration = 0;


int old_selectedItem = 0;

int hourWidth = 0;
int minuteWidth = 0;
uint8_t herzSymb[32];
uint8_t herzKleinSymb[HERZ_KLEIN_WIDTH];
uint8_t herzKleinOffenSymb[HERZ_KLEIN_WIDTH];
uint8_t hakenSymb[HAKEN_WIDTH];


int light_sec_off;
bool light_status = OFF;
	

int main(void)
{
	_delay_ms(1000); //Oszillator powerup


	set_ports();//Ein- und Ausgänge einstellen
	configureTimerAndInterrupts();//Benötigte Interrupts aktivieren, Timer einstellen
	
	lcdInit();
	clear_LCD();
    print_stdDisplay();
	
	sei(); //globale Interrupts aktivieren

	while(1) {
		if(btn_light_pushed == true){
			check_light();
		}
		if(rotary!=0){//Drehen soll hier keine Auswirkung haben
			rotary = 0;
		}
		if(check_TimeUpdate()  ){
			if(!menuOpen) { 
				update_time();
			}
			if((hour == alarm_hour) && (minute == alarm_minute) && (alarm)){
				wakeUp_User();
			}
		}
		if(btn_drehenc_pushed){
			
			//Timer starten zum Zählen
			start_btnPress();
			//warten, solange Taste gedrückt ist
			while((PINB & (1<<PINB2)) && (btn_press_duration<BTN_PRESS_LONG)){_delay_ms(50);}//KANN DELAY WEGGELASSEN WERDEN?
			//Zeitmessung beenden
			stop_btnPress();
			//falls länger als BTN_PRESS_LONG gedrückt wurde, Menü öffnen
			if(btn_press_duration > BTN_PRESS_LONG){ 
				for(int i=0; i<32; i++){
					herzSymb[i] = pgm_read_byte(&herz[0][i]);
				}
				for(int i=0; i<HERZ_KLEIN_WIDTH; i++){
					herzKleinSymb[i] = pgm_read_byte(&herzKlein[0][i]);
					herzKleinOffenSymb[i] = pgm_read_byte(&herzKleinOffen[0][i]);
				}
				for(int i=0; i<HAKEN_WIDTH; i++){//PRÜFEN hakenSymb i<60
					hakenSymb[i] = pgm_read_byte(&haken[0][i]);
				}
				menuOpen = true;
				show_mainMenu(STDDISPLAY);
			} 
			btn_drehenc_pushed = false;
			menuOpen = false;
		}
		goodNight();
	}
	
}

ISR(PCINT0_vect){//Drehencoder oder Lichtschalter wurde gedrückt
		if((PINB & (1<<PINB2))){ //Drehencoder gedrückt
			btn_drehenc_pushed = true;
			//btn_light_pushed = true;//DEBUG
			if(light_status==ON){//Leuchtdauer verlängern, falls Licht an ist
				light_sec_off = (seconds + LIGHT_ON_DURATION)%60;
			}
		} 
		if((PINB & (1<<PINB1))) {//Lichtschalter gedrückt
				btn_light_pushed = true;//Flag wird in main() abgearbeitet
		}
	}


ISR(PCINT2_vect){
	bool A = (PIND & (1<<PIND5));
	bool B = (PIND & (1<<PIND6));
	if(B==A)
		rotary ++;
	else
		rotary --;
	if(light_status==ON){
		light_sec_off = (seconds + LIGHT_ON_DURATION)%60;
	}
	
}	

	
ISR(TIMER2_OVF_vect) {//Quarz-Overflow (1s vorbei)
	timeAdvance ++;//zählt wie viele Sekunden seit letzter Korrektur vorbei sind
	//if( (timeAdvance>0) && (timeAdvance<137932) ){
	//DAS HIER AN, FALLS timeAdvance = 1: 
	//if((timeAdvance != 137932) && increment ){ //nach 137932s ist Wecker 2s zu schnell FÜR MESSUNG AUSGESTELLT
		seconds ++;
		if( seconds == 60 ) {
			timeUpdate++;
			seconds = 0;
			//PRÜFEN: hier muss User evtl. geweckt werden
		}
	/*} else {
		//timeAdvance = -1;//damit auch im nächsten Durchgang die Sekunden nicht inkrementiert werden, da insgesamt 2s zu schnell
		// FOLGENDES WIRD DURCH timeAdvance = -1;, was eigentlich timeAdvance=1 ist. ersetzt: START 
		if(increment) //ist zum ersten mal hier drin -> timeAdvance == 137932
			increment = false;
		else //zum zweiten Mal -> darf wieder nicht inkrementieren, weil insgesamt 2s zu schnell (hier noch 1s)
			increment = true;	
	}*///FÜR MESSUNG AUSGTESTELLT	
	if( (light_status) && (seconds == light_sec_off) ){
		//Alle Beleuchtungen ausschalten
		LCD_LED = 0;
		LED_NORWAY = 0;
		LED_AUSTRALIA = 0;
		light_status = OFF;
	}
}
	
ISR(TIMER0_OVF_vect){//Timer zur Messung der Drückdauer eines Tasters
	//8Mhz / 256 = 31250 Hz
	//256 [ticks/Interrupt] / 31250 [ticks / s] = 8.192 [ms / Interrupt]
	btn_press_duration += 0.008192;	
}

void set_ports(){
	DDRB = 0xFF;//Ausgänge
	DDRB &= ~(1<<PORTB1);//Taster Licht
	DDRB &= ~(1<<PORTB2);//Drehencoder D
	DDRB &= ~(1<<PORTB6);//2 Oszillator Eingänge
	DDRB &= ~(1<<PORTB7);
	PORTB &= ~(1<<PORTB0);//Amp aus
	
	DDRC = 0xFF;//Ausgänge Display
	
	DDRD = 0xFF;//Ausgänge
	//Taster am mp3-Player werden als Eingänge gesetzt. Nur bei Nutzug auf Ausgang
	DDRD &= ~(1<<PORTD0);//Mp3-OnOff/PlayPause
	DDRD &= ~(1<<PORTD1);//4 Taster mp3-Player laut/leiser etc.
	DDRD &= ~(1<<PORTD2);
	DDRD &= ~(1<<PORTD3);
	DDRD &= ~(1<<PORTD4);
	DDRD &= ~(1<<PORTD5);//Drehenocer A
	DDRD &= ~(1<<PORTD6);//Drehencoder B
	PORTD &= ~(1<<PORTD7);//Amp Mute

	LCD_RST = 1;
	LCD_CS = 1;
	LCD_CLK = 1;
}

void configureTimerAndInterrupts() {
	//TIMER2 (Uhr)
	ASSR |= (1<<AS2); //Activate asynchronous clock for Timer2
	TCNT2 = 0; //set Timer2 counter = 0
	TCCR2B |= (1<<CS22)|(1<<CS20); //Prescaler 128
	TIMSK2 |= (1<<TOIE2); //Overflow-interrupt
	
	//TIMER1 (Druckdauer von Tasten messen)
	TIMSK0 = (1<<TOIE0);//Overflow-Interrupt --> 8-bit, 255
	
	//Licht-Taster und Drehencoder-Taster
	PCICR = (1<<PCIE0);//PCINT[7:0] enable
	PCMSK0 = (1<<PCINT1);//Drücken von Lichtschalter
	PCMSK0 |=(1<<PCINT2);//Drücken von Drehencoder

	//Drehencoder drehen
	PCICR |= (1<<PCIE2);//PCINT[23:16]
	PCMSK2 = (1<<PCINT21);//Interrupt bei Pinänderung durch Drehung Drehencoder
	//PCMSK2 |=(1<<PCINT22);
}

void wakeUp_User(){
	mute_on();//Verstärker muten, damit kein Knack beim Einschalten entsteht
	mp3Player_onoff();
	_delay_ms(10000);//warten bis mp3Player an ist
	next_song();
	play_pause();
	boot_amp();
	if(snoozeCounter == 0){
		next_song();
	}
	mute_off();
	play_pause();//Play
	bool user_awake = false;
	
	while((!btn_light_pushed) && (rotary == 0) && (!btn_drehenc_pushed)){//Könnte auch von Sekundenzähler aufgewacht sein
		goodNight();
		if(check_TimeUpdate());
			update_time();
	}
	
	if(snoozeCounter==0){
		if(btn_light_pushed){
			//while(!btn_light_pushed){_delay_ms(100);}
			start_btnPress();
			while((PINB & (1<<PINB1)) && (btn_press_duration<BTN_PRESS_LONG)){_delay_ms(50);}
			stop_btnPress();
			if(btn_press_duration>=BTN_PRESS_LONG){
				user_awake = true;
			} else {
				snooze();
				snoozeCounter = 1;
			}
		} else {
			snooze();
			snoozeCounter = 1;
		}
	} else {
		while(!user_awake){
			goodNight();
			if(check_TimeUpdate())
				update_time();
			start_btnPress();
			while((PINB & (1<<PINB1)) && (btn_press_duration<BTN_PRESS_LONG)){_delay_ms(50);}
			stop_btnPress();
			if(btn_press_duration>=BTN_PRESS_LONG){
				user_awake = true;
				snoozeCounter = 0;
				
			}
		}
	}
	play_pause();//Pause
	shutdown_amp();
	mp3Player_onoff();
}

void snooze(){
	alarm_minute = minute + snoozeDuration % 60;
	if(alarm_minute < 5)
		alarm_hour = hour + 1;
	else
		alarm hour = hour;
	
}

void check_light(){
	if(btn_light_pushed){
		//Timer starten zum zählen
		start_btnPress();
		//warten, solange Taste gedrückt ist
		while((PINB & (1<<PINB1)) && (btn_press_duration<BTN_PRESS_LONG)){_delay_ms(50);}//KANN DELAY WEGGELASSEN WERDEN?
		//Zeitmessung beenden
		stop_btnPress();
		//falls länger als BTN_PRESS_LONG gedrückt wurde, Alarm toggeln
		if((btn_press_duration > BTN_PRESS_LONG) && (menuOpen==false)){
			alarm = !alarm;
			print_stdDisplay();
		} else {//ansonsten Licht einschalten
			LCD_LED = 1;//Hintergrundbeleuchtung Display an
			LED_NORWAY = 1;//Beleuchtung Norwegen an
			LED_AUSTRALIA = 1;//Beleuchtung Australien an
			light_sec_off = (seconds + LIGHT_ON_DURATION)%60;
			light_status = ON;
		}
		cli();
		btn_light_pushed = false;//Flag zurücksetzen
		sei();
	}
}

void print_menuItems(char item1[], char item2[], char item3[], char item4[]){
	clear_pixelMatrix();
	int xPosItem = 20;
	int yPosItem = 3;
	
	//Item1
	int item1_ASCII [strlen(item1)];
	convertString(item1, item1_ASCII);
	print_ASCIIString(xPosItem, yPosItem, item1_ASCII, sizeof(item1_ASCII)/sizeof(item1_ASCII[0]));
	yPosItem += 15;

	//Item2
	int item2_ASCII [strlen(item2)];
	convertString(item2, item2_ASCII);
	print_ASCIIString(xPosItem, yPosItem, item2_ASCII, sizeof(item2_ASCII)/sizeof(item2_ASCII[0]));
	yPosItem += 15;

	//Item3
	int item3_ASCII [strlen(item3)];
	convertString(item3, item3_ASCII);
	print_ASCIIString(xPosItem, yPosItem, item3_ASCII, sizeof(item3_ASCII)/sizeof(item3_ASCII[0]));
	yPosItem += 15;

	//Item4
	int item4_ASCII [strlen(item4)];
	convertString(item4, item4_ASCII);
	print_ASCIIString(xPosItem, yPosItem, item4_ASCII, sizeof(item4_ASCII)/sizeof(item4_ASCII[0]));
	
	//Haken
	print_symbol(16,17, hakenSymb,108,46);
}


int get_menuSelection(int numItems, int selectedItem){
	print_menuSelection(selectedItem, numItems);
	update_LCD();
	cli();
	rotary = 0;
	btn_drehenc_pushed = false;
	sei();
	while(!btn_drehenc_pushed){
		if(rotary != 0){
			cli();
			selectedItem += rotary;
			rotary = 0;
			sei();
			selectedItem = selectedItem % (numItems+1);
			if(selectedItem < 0){
				selectedItem += numItems+1;
			}
			print_menuSelection(selectedItem, numItems);
			update_LCD();
		}
		goodNight();
		check_light();
	}
	cli();
	btn_drehenc_pushed = false;
	sei();
	return selectedItem;
}
	
	
void show_mainMenu(){
	int item = 0;
	bool stayOpened = true; //wird benötigt um Rückgabewert aus Menu2 zu speichern
	while((item<4) && (stayOpened == true)){	
		print_menuItems("Weckzeit", "Uhrzeit", "Datum", ". . .");
		update_LCD();
		item = get_menuSelection(4, item);
		switch (item) {
			case 0: set_alarm(); break;
			case 1: set_time(TIME_TYPE); break;
			case 2: set_date(); break;
			case 3: stayOpened = show_mainMenu2(); break;//STAY OPENED ÜBERFLÜSSIG (?)
			case 4: print_stdDisplay(); break;
			default: print_stdDisplay(); break;
		}
	}
}

bool show_mainMenu2(){
	int item = 1;
	while((item > 0) && (item<4)){
		print_menuItems(". . .","Snoozedauer", "Lautstärke", "Boombox");
		update_LCD();
		item = get_menuSelection(4, item);
		switch (item) {
			case 0: break; //"..." ausgewählt -> in Menü1 zurückkehren
			case 1: set_snoozeDuration(); break;
			case 2: set_audio(); break;
			case 3: boombox(); break;
			case 4: print_stdDisplay(); break;
			default: print_stdDisplay(); break;
		}
	}
	if(item == 0){
		return true;
	} else {
		return false;
	}
}


void set_alarm(){
	set_time(ALARM_TYPE);
}


void set_timeParameter(int *timeParameter, int maxTime, bool timeType){ //timeParameter = {minute, hour, alarmMinute, alarmHour}
	while(!btn_drehenc_pushed) {
		if(rotary!=0) {
			cli();
			*timeParameter += rotary;
			rotary = 0;
			*timeParameter = *timeParameter % maxTime;
			if(*timeParameter<0){
				*timeParameter += maxTime;
			}
			seconds = 0;
			sei();
			for(int x = timeXPos; x < timeXPos + hourWidth + minuteWidth + 2*SPACE_TO_DOTS + TIMEDOT_WIDTH; x++){
				for(int y = 0; y < timeYPos + BIG_NUMBER_HEIGHT; y++)
					reset_pixel(x,y);
			}
			print_time(timeType);
			if(maxTime == 60)
				print_symbol(8,HERZ_KLEIN_WIDTH,herzKleinOffenSymb,timeXPos+hourWidth + 2*SPACE_TO_DOTS + TIMEDOT_WIDTH + minuteWidth/2-4, 2);
			else
				print_symbol(8,HERZ_KLEIN_WIDTH,herzKleinOffenSymb,timeXPos+hourWidth/2-4, 2);
			update_LCD();
		}
		goodNight();
		check_light();
	}
	cli();
	btn_drehenc_pushed = false;
	sei();
}

void set_time(bool timeType){
	int *hou = &hour;
	int *min = &minute;
	update_timeXPos(hour, minute);
	if (timeType == ALARM_TYPE){
		hou = &alarm_hour;
		min = &alarm_minute;
		update_timeXPos(alarm_hour, alarm_minute);
	}
	int item = 0;
	int old_selectedItem = 1;
	cli();
	btn_drehenc_pushed = false;
	sei();
	clear_pixelMatrix();
	print_time(timeType);
	
	print_symbol(16,17, hakenSymb,108,46);
	print_symbol(8,HERZ_KLEIN_WIDTH,herzKleinSymb,timeXPos+get_timeWidth(alarm_hour)/2-4, 2);
	update_LCD();
	while(item != 2){
		while(!btn_drehenc_pushed){
			if(rotary != 0){
				item += rotary;
				cli();
				rotary = 0;
				sei();
				item = item % 3;
				if(item<0){
					item += 3;
				}
				
				switch (old_selectedItem){
					case 0: for(int x = 0; x<128; x++){
								for(int y = 2; y<10; y++)
									reset_pixel(x,y);
							} break;
					case 1: for(int x = 0; x<128; x++){
								for(int y = 2; y<10; y++)
								reset_pixel(x,y);
							}break;
					case 2: for(int x = 92; x<102; x++){
								for(int y = 2+3*15+5; y<2+3*15+8+5; y++)
									reset_pixel(x,y);
							}break;
				}
				switch (item) {
					case 0: print_symbol(8,HERZ_KLEIN_WIDTH,herzKleinSymb,timeXPos+hourWidth/2-4, 2); break;
					case 1: print_symbol(8,HERZ_KLEIN_WIDTH,herzKleinSymb,timeXPos+hourWidth+2*SPACE_TO_DOTS+ TIMEDOT_WIDTH + minuteWidth/2-4, 2); break;
					case 2: print_symbol(8,HERZ_KLEIN_WIDTH,herzKleinSymb, 92, 2+3*15+5);break;
				}
				old_selectedItem = item;
				update_LCD();
			}
			goodNight();
			check_light();
		}
		cli();
		btn_drehenc_pushed = false;
		sei();
		switch (item) {
			case 0: {
				print_symbol(8,HERZ_KLEIN_WIDTH,herzKleinOffenSymb,timeXPos+hourWidth/2-4, 2); 
				update_LCD(); 
				set_timeParameter(hou, 24, timeType); 
				print_symbol(8,HERZ_KLEIN_WIDTH,herzKleinSymb,timeXPos+hourWidth/2-4, 2);
				break;
			}
			
			case 1: {
				print_symbol(8,HERZ_KLEIN_WIDTH,herzKleinOffenSymb,timeXPos+hourWidth+2*SPACE_TO_DOTS+ TIMEDOT_WIDTH + minuteWidth/2-4, 2); 
				update_LCD(); 
				set_timeParameter(min, 60, timeType); 
				print_symbol(8,HERZ_KLEIN_WIDTH,herzKleinSymb,timeXPos+hourWidth+2*SPACE_TO_DOTS+ TIMEDOT_WIDTH + minuteWidth/2-4, 2);
				break;
			}
			case 2: {	seconds = 0;
						cli();
						TCNT2 = 0;
						timeAdvance = 0;
						timeUpdate = 0;
						sei();
						break;
			}
		}
		update_LCD();
	}
}

void set_date(){
	clear_pixelMatrix();
	print_date(POS_DATE_SET);
	print_year();
	print_symbol(16,17, hakenSymb,108,46);
	print_symbol(8, HERZ_KLEIN_WIDTH, herzKleinSymb, get_dateXPos() + get_dayWidth() / 2 - 4, POS_DATE_SET - 10);
	update_LCD();
	int old_selectedItem = 0;
	int item = 0;
	
	while (item != 3){
		cli();
		btn_drehenc_pushed = false;
		sei();
		while(!btn_drehenc_pushed){
			if(rotary != 0){
				item += rotary;
				cli();
				rotary = 0;
				sei();
				item = item % 4;
				if(item<0){
					item += 4;
				}
			
				switch (old_selectedItem){
					case 0: for(int x = 0; x<128; x++){
						for(int y = 0; y<10; y++)
						reset_pixel(x,y);
					} break;
					case 1: for(int x = 0; x<128; x++){
						for(int y = 0; y<10; y++)
						reset_pixel(x,y);
					}break;
					case 2: for(int x = 0; x<128; x++){
						for(int y = 30; y<40; y++)
						reset_pixel(x,y);
					}break;
					case 3: for(int x = 94; x<104; x++){
						for(int y = 2+3*15+5; y<2+3*15+5+8; y++)
						reset_pixel(x,y);
					}break;
				}
				switch (item) {
					case 0: print_symbol(8, HERZ_KLEIN_WIDTH, herzKleinSymb, get_dateXPos() + get_dayWidth() / 2 - 4, POS_DATE_SET - 10); break; //-4 = halbe Länge Herz
					case 1: print_symbol(8, HERZ_KLEIN_WIDTH, herzKleinSymb, get_dateXPos() + get_dayWidth() + get_monthWidth() / 2 - 4, POS_DATE_SET - 10); break;
					case 2: print_symbol(8, HERZ_KLEIN_WIDTH, herzKleinSymb, get_yearXPos() + get_yearWidth() / 2 - 4, YPOS_YEAR - 10);break;
					case 3: print_symbol(8, HERZ_KLEIN_WIDTH, herzKleinSymb, 94, 2+3*15+5);break;
				}
				old_selectedItem = item;
				update_LCD();
			}
			goodNight();
			check_light();
		}
		cli();
		btn_drehenc_pushed = false;
		sei();
		switch (item) {
			case 0: {
				print_symbol(8, HERZ_KLEIN_WIDTH, herzKleinOffenSymb, get_dateXPos() + get_dayWidth() / 2 - 4, POS_DATE_SET - 10);
				update_LCD();
				set_day();
				print_symbol(8, HERZ_KLEIN_WIDTH, herzKleinSymb, get_dateXPos() + get_dayWidth() / 2 - 4, POS_DATE_SET - 10);
				break;
			}
			case 1:{
				print_symbol(8, HERZ_KLEIN_WIDTH, herzKleinOffenSymb, get_dateXPos() + get_dayWidth() + get_monthWidth() / 2 - 4, POS_DATE_SET - 10);
				update_LCD();
				set_month();
				print_symbol(8, HERZ_KLEIN_WIDTH, herzKleinSymb, get_dateXPos() + get_dayWidth() + get_monthWidth() / 2 - 4, POS_DATE_SET - 10);
				break;
			}
			case 2: {
				print_symbol(8, HERZ_KLEIN_WIDTH, herzKleinOffenSymb,  get_yearXPos() + get_yearWidth() / 2 - 4, YPOS_YEAR - 10);
				update_LCD();
				set_year();
				print_symbol(8, HERZ_KLEIN_WIDTH, herzKleinSymb,  get_yearXPos() + get_yearWidth() / 2 - 4, YPOS_YEAR - 10);
				break;
			}
			default: break;
		}
		update_LCD();
	}
}

void set_day(){
	cli();
	btn_drehenc_pushed = false;
	sei();
	while(!btn_drehenc_pushed){
		if(rotary != 0){
			day += rotary;
			cli();
			rotary = 0;
			sei();
			if (day < 1) {
				day += pgm_read_byte(&daysPerMonth[month]);
			}
			if (day > pgm_read_byte(&daysPerMonth[month])){
				day -= pgm_read_byte(&daysPerMonth[month]);
			}
			for(int x = 0; x<128; x++){
				for(int y = 0; y<10; y++)
				reset_pixel(x,y);
			}
			
			print_date(POS_DATE_SET);
			print_symbol(8, HERZ_KLEIN_WIDTH, herzKleinOffenSymb, get_dateXPos() + get_dayWidth() / 2 - 4, POS_DATE_SET - 10);
			update_LCD();
		}
		goodNight();
		check_light();
	}
}

void set_month(){
	cli();
	btn_drehenc_pushed = false;
	sei();
	while(!btn_drehenc_pushed){
		if(rotary != 0){
			month += rotary;
			cli();
			rotary = 0;
			sei();
			month = month % 12;
			if (month < 0) {
				month += 12;
			}
			if(day > pgm_read_byte(&daysPerMonth[month])){
				day = pgm_read_byte(&daysPerMonth[month]);
			}
			for(int x = 0; x<128; x++){
				for(int y = 0; y<10; y++)
				reset_pixel(x,y);
			}
			
			print_date(POS_DATE_SET);
			print_symbol(8, HERZ_KLEIN_WIDTH, herzKleinOffenSymb, get_dateXPos() + get_dayWidth() + get_monthWidth() / 2 - 4, POS_DATE_SET - 10);
			update_LCD();
		}
		goodNight();
		check_light();
	}
}

void set_year(){
	cli();
	btn_drehenc_pushed = false;
	sei();
	while(!btn_drehenc_pushed){
		if(rotary != 0){
			year += rotary;
			cli();
			rotary = 0;
			sei();
			if (year < 0) {
				year = 9999;
			}
			if(year > 9999){
				year -= 10000;
			}
			for(int x = 0; x<128; x++){
				for(int y = 30; y<40; y++)
				reset_pixel(x,y);
			}
			for(int x = 0; x<90; x++){
				for(int y = YPOS_YEAR; y<YPOS_YEAR + 17; y++){
					reset_pixel(x,y);
				}
			}
			print_year();
			print_symbol(8, HERZ_KLEIN_WIDTH, herzKleinOffenSymb, get_yearXPos() + get_yearWidth() / 2 - 4, YPOS_YEAR - 10);
			update_LCD();
		}
		goodNight();
		check_light();
	}
	goodNight();
	check_light();
}



int get_dateXPos() {
	return ((127 - get_dateWidth()) / 2 + 1);
}


void print_menuSelection(int item, int numItems){
	remove_menuSelection(old_selectedItem, numItems);
	
	if(item<numItems){
		print_symbol(16,16, herzSymb,2,2+item*15);
	} else {
		print_symbol(16,16, herzSymb, 92, 2+3*15);
	}
	
	old_selectedItem = item;
}

void remove_menuSelection(int item, int numItems){
	if(item < numItems){
		for(int x = 0; x<19; x++){
			for(int y = 0; y<64; y++)
				reset_pixel(x,y);
		}
	} else {
		for(int x = 92; x<108; x++){
			for(int y = 48; y<64; y++)
				reset_pixel(x,y);
		}
	}
}

void print_ASCIIString(int xStart, int yPos, int* string, int size){
	int tempXPos = xStart;
	for(int i=0; i<size; i++){
		if(string[i] < 0 ){//Leerzeichen
			tempXPos += 3;
		} else {
			print_letter(alphaHeight, pgm_read_byte(&alphaWidth[string[i]]), string[i], tempXPos, yPos);
			tempXPos+=pgm_read_byte(&alphaWidth[string[i]])+1;
		}
	}
	
}
	
	

	

	void clear_pixelMatrix(){
		for(int i = 0; i<128; i++){
			for(int j = 0; j<8; j++){
				pixelMatrix[i][j]=0;
			}
		}
	}
	
	void print_stdDisplay(){
		clear_pixelMatrix();
		print_time(TIME_TYPE);
		print_date(POS_DATE_STD);
		if(alarm){
			print_alarmLogo();
		}
		update_LCD();
	}
	
	void start_btnPress(){
			btn_press_duration = 0;
			TCNT0 = 0;
			TCCR0B = (1<<CS02);//Prescaler 256		
	}
	
	void stop_btnPress(){
		TCCR0B = 0; //TIMER0 aus
	}
	
	
	
	bool check_TimeUpdate() {
		cli();
		if (timeUpdate > 0) {
			sei();
			return true;
		} else {
			sei();
			return false;
		}
		
	}
	
	void reset_alarmLogo() {
		for(int x = 1; x<10; x++){
			for(int y = 2; y<2+16; y++)
				reset_pixel(x,y);
		}
	}
	
	void print_alarmLogo() {
		uint8_t weckerSymb[72];
		for(int i=0; i<72; i++){
			weckerSymb[i] = pgm_read_byte(&note[0][i]);
		}
		print_symbol(16,9,weckerSymb,1/*116*/,2);
	}
	
	void update_time() {
		//update_timeXPos();//Alten Zeit löschen
		for(int x = timeXPos; x<128; x++) {
			for(int y = timeYPos; y<timeYPos+BIG_NUMBER_HEIGHT; y++) {
				reset_pixel(x,y);
			}
		}
		minute += timeUpdate;
		timeUpdate = 0;
		if(minute > 59) {
			minute = minute % 60;
			hour++;
		}
		if(hour > 23) {
			hour = 0;
			increment_date();
		}
		print_time(TIME_TYPE);
		update_LCD();
	}
	
	
	void increment_date() {
		day ++;
		if(day > daysThisMonth) {
			day = 1;
			month++;
			if(month == 1 && ((year%4) == 0))
			daysThisMonth = 29;
			else
			daysThisMonth = pgm_read_byte(&daysPerMonth[month]);
		}
		if(month==12) {
			month=0;
			year ++;
		}
		print_date(POS_DATE_STD);
	}
	
	void print_time(bool type) {
		int h = hour;
		int m = minute;
		if(type == ALARM_TYPE){
			h = alarm_hour;
			m = alarm_minute;
		}
		update_timeXPos(h, m);
		int tempXPos = print_hour(h);
		tempXPos = print_timeDot(tempXPos, timeYPos);
		print_minute(m, tempXPos + SPACE_TO_DOTS);
	}
	
	int print_timeDot(int xStart, int yStart) {
		for(int x=0; x<5; x++){
			for(int y=0; y<32; y++){
				if((pgm_read_byte(&timeDot[x*32/8+y/8])) & (1<<(y%8))){
					set_pixel(xStart+x,yStart+y);
					} else {
					reset_pixel(xStart+x,yStart+y);
				}
			}
		}
		return xStart + 5;
	}
	
	void update_timeXPos(int h, int m) {
		uint8_t width = 0;
		hourWidth = get_timeWidth(h);
		minuteWidth = get_timeWidth(m);
		width = hourWidth  + SPACE_TO_DOTS + TIMEDOT_WIDTH + SPACE_TO_DOTS + minuteWidth;
		timeXPos = (127-width)/2;
	}
	
	int get_timeWidth(int t){
		int timeWidth = pgm_read_byte(&bigNumberWidth[t%10]) + INTER_DIGIT_SPACE; //first digit
		timeWidth += pgm_read_byte(&bigNumberWidth[t/10]); //second digit
		return timeWidth;
	}
	
	int print_hour(int h) {
		
		int tempX = timeXPos;//timeXPos-(pgm_read_byte(&bigNumberWidth[hour%10])+SPACE_TO_DOTS);
		print_bigNumber(tempX,timeYPos,h/10);
		tempX += pgm_read_byte(&bigNumberWidth[h/10])+INTER_DIGIT_SPACE;
		print_bigNumber(tempX,timeYPos,h%10);
		return (tempX+pgm_read_byte(&bigNumberWidth[h%10]) + SPACE_TO_DOTS);
	}
	
	void print_minute(int min, int tempX) {
		if(min<10) { //Null als erste Minutenzahl
			print_bigNumber(tempX,timeYPos,0);
			tempX += pgm_read_byte(&bigNumberWidth[0])+INTER_DIGIT_SPACE;
		} else {
			print_bigNumber(tempX,timeYPos,min/10);
			tempX += pgm_read_byte(&bigNumberWidth[min/10])+INTER_DIGIT_SPACE;
		}
		print_bigNumber(tempX,timeYPos,min%10);

	}
	
	void print_date(int yPos) {
		for(int x = 0; x<128; x++) {
			for(int y=yPos; y<yPos+18; y++ ){
				reset_pixel(x,y);
			}
		}
		/*int dayWidth = get_dayWidth();
		int monthWidth = get_monthWidth();
		int dateWidth = dayWidth + monthWidth + 6; //6=Punkt + Leerzeichen
		int xPosDate = (127 - dateWidth) / 2 + 1;*/
		int xPosDate = get_dateXPos();
		
		if ((yPos == POS_DATE_STD) && (day==14) && (month==1)){
			uint8_t roseSymb[90];
			for(int i=0; i<90; i++){
				roseSymb[i] = pgm_read_byte(&rose[0][i]);
			}
			print_symbol(16, 45, roseSymb, (127 - ROSE_WIDTH) / 2 + 1, POS_DATE_STD);
		} else if ((yPos == POS_DATE_STD) && (day==4) && (month==7)) {
			int spruch [11];
			convertString("Alles Liebe", spruch);
			int xSpruch = (127 - get_stringWidth(spruch, 11)) / 2 + 1;
			print_ASCIIString(xSpruch, POS_DATE_STD, spruch, 11);
			uint8_t herzSymb[32];
			for(int i=0; i<32; i++){
				herzSymb[i] = pgm_read_byte(&herz[0][i]);
			}
			print_symbol(16, 16, herzSymb, xSpruch - 16 - 4, POS_DATE_STD);
			print_symbol(16, 16, herzSymb, xSpruch + get_stringWidth(spruch, 11) + 4, POS_DATE_STD);
		} else {
			print_day(xPosDate, yPos);	//Tag
			print_letter(alphaHeight, pgm_read_byte(&alphaWidth[54]), 54, xPosDate + get_dayWidth() + 1, yPos); //Punkt
			print_month(xPosDate + get_dayWidth() + 6, yPos); //Monat ..+6=Punkt+Leerzeichen
		}
	}
	
	int get_stringWidth(int string [], int length){//in px
		int width = -1;
		for(int i = 0; i < length; i++){
			if(string[i] < 0){
				width += 3;
			} else {
				width += pgm_read_byte(&alphaWidth[string[i]])+1;
			}
		}
		return width;
	}
	
    int get_dateWidth(){
		return get_dayWidth() + get_monthWidth() + 6;	
	}
	
	void print_month(int xPos, int yPos) {
		int tempXPos = xPos;
		int tempYPos = yPos;
		int tempLetter;		
		for (int i=0; i<maxMonthLength; i++) {
			tempLetter = pgm_read_byte(&months[month][i]);
			if (tempLetter<54) {
				if((tempLetter == 6) || (tempLetter == 15) || (tempLetter == 16) || (tempLetter == 24)) {
					tempYPos = yPos + 1;
				} else {
					tempYPos = yPos;
				}
				if(tempLetter == 1) {
					tempXPos --;
				}
				print_letter(alphaHeight, pgm_read_byte(&alphaWidth[tempLetter]), tempLetter, tempXPos, tempYPos);
				tempXPos+=pgm_read_byte(&alphaWidth[tempLetter])+1;
			}
		}
	}
	
	
	
	void print_day(int xPos, int yPos) {
		int tempDay = day;
		if(tempDay > 9) {
			print_smallNumber(xPos, yPos, tempDay/10);
			print_smallNumber(xPos + pgm_read_byte(&smallNumberWidth[tempDay/10]) + 1, yPos, tempDay%10);
		} else {
			print_smallNumber(xPos, yPos, tempDay);
		}
	}
	
	int get_yearXPos(){
		return (127 - get_yearWidth()) / 2 + 1;
	}
	
	void print_year(){
		int xPos = get_yearXPos();
		int tempYear = year;
		
		print_smallNumber(xPos, YPOS_YEAR, tempYear /1000);
		xPos += pgm_read_byte(&smallNumberWidth[tempYear / 1000])+1;
		tempYear -= tempYear / 1000 * 1000;
		
		print_smallNumber(xPos, YPOS_YEAR, tempYear /100);
		xPos += pgm_read_byte(&smallNumberWidth[tempYear / 100])+1;
		tempYear -= tempYear / 100 * 100;
		
		print_smallNumber(xPos, YPOS_YEAR, tempYear /10);
		xPos += pgm_read_byte(&smallNumberWidth[tempYear / 10])+1;
		tempYear -= tempYear / 10 * 10;
		
		print_smallNumber(xPos, YPOS_YEAR, tempYear);
		xPos += pgm_read_byte(&smallNumberWidth[tempYear]);

	}
	
	int get_yearWidth(){
		int width = -1;
		int tempYear = year;
		while(tempYear > 0) {
			width += pgm_read_byte(&smallNumberWidth[tempYear%10])+1;
			tempYear /= 10;
		}
		return width;
	}
	
	int get_dayWidth() {
		int tempDay = day;
		int width = -1;	
		width += pgm_read_byte(&smallNumberWidth[tempDay%10])+1; //+1für Leerzeichen
		if(day > 9) {
			width += pgm_read_byte(&smallNumberWidth[tempDay/10])+1;
		}
		return width;
	}
	
	int get_monthWidth() {
		int width = -1;
		int tempLetter;
		for (int i = 0; i<maxMonthLength; i++) {
			tempLetter = pgm_read_byte(&months[month][i]);
			if(tempLetter == 53) { //53 => empty
				
			} else {
				width += pgm_read_byte(&alphaWidth[tempLetter])+1;
			}
		}
		return width;
	}
	
	void convertString(char string[], int asciiArr[]) {
		int index; //Index für das hinterlegte Alphabet-Array
		for(int i = 0; i<strlen(string); i++) {
			//ASCII-Dezimalzahl des Zeichens umwandeln
			if(((int)string[i]>64) && ((int)string[i]<91)) {
				//Großbuchstabe
				index = (int)string[i]-65+26;
			} else if( ((int)string[i]>96) && ((int)string[i]<123) ){
				//Kleinbuchstabe
				index = (int)string[i]-97;
			} else {
				//Sonderzeichen
				switch((int)string[i]){
					case 252: index=55; break;//ü
					case 228: index=52;break; //ä
					case 46:  index=54; break;//.
					case 32:  index=-1; break;//Leerzeichen
					default: index = -1;
				}
				/*if((int)string[i]==252)//ü
					index = 55;
				if((int)string[i]==46)//.
					index = 54;
				if((int)string[i]==32)
					index = -1;*/
				
			}
			asciiArr[i] = index;
		}
		/*print_smallNumber(50,40,(int)string[3]/100);
		print_smallNumber(60,40,(int)(string[3]-200)/10);
		print_smallNumber(70,40,(int)(string[3]-250));*/
	}
	
	void goodNight() {
		while((!btn_drehenc_pushed) && (rotary==0) && (!btn_light_pushed) && (timeUpdate==0)){ //nur aufwachen, wenn nicht "taster losgelassen" oder "sekunde weitergestellt (1-59s)" die Ursache ist
			SMCR |= (1<<SE);//Sleep enable
			SMCR |= ((1<<SM1)|(1<<SM0));//Sleep mode: Power-Save mode
			OCR2A = 1;//Sichergehen, dass genug Zeit seit letztem Schlafen vergangen ist
			while((ASSR & (1<<OCR2AUB)));//Warten bis Schreiben fertig, erst dann darf man schlafen 
			sleep_cpu();
		}
	}

int charArraySize(char ch[]){
	return (sizeof(ch)/sizeof(ch[0]));
}


void set_snoozeDuration(){
	btn_drehenc_pushed = false;
	int item = 0;
	clear_pixelMatrix();
	clear_LCD();
	print_symbol(16,17, hakenSymb,108,46);
	while(item!=1){
		int width = pgm_read_byte(&bigNumberWidth[snoozeDuration%10]);
		if(snoozeDuration>9){
			width += pgm_read_byte(&bigNumberWidth[snoozeDuration/10]);
		}
		printSnoozetime();
		while(!btn_drehenc_pushed){
			item+=rotary;
			item=item%2;
			if(item<0)
				item+=2;
			rotary = 0;
			if(item == 0){
				print_symbol(8,HERZ_KLEIN_WIDTH,herzKleinSymb,64-4, 2); 
				for(int x = 92; x<92+16; x++){
					for(int y = 2+3*15; y<64; y++)
					reset_pixel(x,y);
				}
			} else {
				print_symbol(16,16, herzSymb, 92, 2+3*15);
				for(int x = 64-8; x<64+8; x++){
					for(int y = 2; y<11; y++)
					reset_pixel(x,y);
				}
			}
			update_LCD();
			goodNight();
			check_light();	
		}
		btn_drehenc_pushed = false;
		for(int x = 64-8; x<64+8; x++){
			for(int y = 2; y<11; y++)
			reset_pixel(x,y);
		}
		if(item==0){
			print_symbol(8,HERZ_KLEIN_WIDTH,herzKleinOffenSymb,64-HERZ_KLEIN_WIDTH/2, 2);
			update_LCD();
			while(!btn_drehenc_pushed){
				if(rotary!=0){
					for(int x = 64-width/2; x<64+width/2;x++){
						for(int y = timeYPos; y<timeYPos+BIG_NUMBER_HEIGHT; y++)
						reset_pixel(x,y);
					}
					snoozeDuration+=rotary;
					snoozeDuration=snoozeDuration%99;
					if(snoozeDuration<0)
					snoozeDuration+=99;
					rotary = 0;
				}
				printSnoozetime();
				update_LCD();
				goodNight();
				check_light();
			}
			btn_drehenc_pushed = false;
		}
	}
}


void set_audio(){
	btn_drehenc_pushed = false;
	int item = 0;
	clear_pixelMatrix();
	clear_LCD();
	print_symbol(16,17, hakenSymb,108,46);
	int warte_ASCII [strlen("Bitte warten")];
	convertString("Bitte warten", warte_ASCII);
	print_ASCIIString(20,16, warte_ASCII, sizeof(warte_ASCII)/sizeof(warte_ASCII[0]));
	update_LCD();
	mp3Player_onoff();//On
	_delay_ms(1000);
	boot_amp();
	play_pause();
	//Speaker-Symbol aus EEPROM holen
	uint8_t speakerSymb[SPEAKER_WIDTH];
	for(int i=0; i<SPEAKER_WIDTH; i++){
		speakerSymb[i] = pgm_read_byte(&speaker[0][i]);
	}
	clear_pixelMatrix();
	clear_LCD();
	print_symbol(16,17, hakenSymb,108,46);
	print_symbol(24,31,speakerSymb,(128-31)/2,(64-24)/2);
	while(item!=1){
		while(!btn_drehenc_pushed){
			
			item+=rotary;
			item=item%2;
			if(item<0)
			item+=2;
			rotary = 0;
			if(item == 0){
				//ggf. offenes Herz entfernen
				for(int x = 64-HERZ_KLEIN_WIDTH/2; x<64-HERZ_KLEIN_WIDTH/2+2; x++){
					for(int y = 2; y<11; y++)		
						reset_pixel(x,y);
				}
				print_symbol(8,HERZ_KLEIN_WIDTH,herzKleinSymb,64-4, 2);//kleines Herz über Speaker malen
				for(int x = 92; x<92+16; x++){//Großes Herz am Haken entfernen
					for(int y = 2+3*15; y<64; y++)
					reset_pixel(x,y);
				}
				} else {
				print_symbol(16,16, herzSymb, 92, 2+3*15);//Großes Herz am Haken malen
				for(int x = 64-8; x<64+8; x++){//kleines Herz über Speaker entfernen
					for(int y = 2; y<11; y++)
					reset_pixel(x,y);
				}
			}
			update_LCD();
			goodNight();
			check_light();
		}
		btn_drehenc_pushed = false;
		for(int x = 64-8; x<64+8; x++){
			for(int y = 2; y<11; y++)
			reset_pixel(x,y);
		}
		if(item==0){
			print_symbol(8,HERZ_KLEIN_WIDTH,herzKleinOffenSymb,64-HERZ_KLEIN_WIDTH/2, 2);
			update_LCD();
			btn_drehenc_pushed = false;
			while(!btn_drehenc_pushed){
				goodNight();
				if(rotary>0){
					volume(UP);
					rotary = 0;
				} else {
					volume(DOWN);
					btn_light_pushed = true; //DEBUG
					rotary = 0;
				}
				check_light();
			}
			btn_drehenc_pushed = false;
		}
	}
	clear_pixelMatrix();
	clear_LCD();
	print_ASCIIString(20,16, warte_ASCII, sizeof(warte_ASCII)/sizeof(warte_ASCII[0]));
	update_LCD();
	shutdown_amp();
	mp3Player_onoff();
}

void boombox(){
	boot_amp();
	clear_LCD();
	clear_pixelMatrix();
	uint8_t weckerSymb[72];
	for(int i=0; i<72; i++){
		weckerSymb[i] = pgm_read_byte(&note[0][i]);
	}
	print_symbol(16,9,weckerSymb,55,24);
	print_symbol(16,17, hakenSymb,108,46);
	print_symbol(16,16, herzSymb, 92, 2+3*15);
	update_LCD();
	while(!btn_drehenc_pushed){
		goodNight();
		check_light();
	}
	shutdown_amp();
}

void printSnoozetime(){
	int width = pgm_read_byte(&bigNumberWidth[snoozeDuration%10]);
	if(snoozeDuration>9){
		width += pgm_read_byte(&bigNumberWidth[snoozeDuration/10]);
	}
	for(int x = 0; x<128; x++){
		for(int y = timeYPos; y<timeYPos + BIG_NUMBER_HEIGHT; y++)
			reset_pixel(x,y);
	}
	
	if(snoozeDuration>9){
		print_bigNumber(64-width/2,timeYPos,snoozeDuration/10);
		print_bigNumber(64-width/2+pgm_read_byte(&bigNumberWidth[snoozeDuration/10])+2,timeYPos,snoozeDuration%10);
	}else{
		print_bigNumber(64-width/2,timeYPos,snoozeDuration);
	}
}

		

