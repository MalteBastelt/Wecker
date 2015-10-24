/*
 * EA_DOGL128.c
 *
 * Created: 11.03.2015 11:27:58
 *  Author: Malte
 * 
 */ 

int cnt = 0;

#include "EADOGL128.h"
uint8_t stdDisplay [128] [8];
//uint8_t displayContent [128][8];
int hour = 0;
int minute = 0;
int seconds = 0;
int day=31;
int month = 8;
int year = 2016;
int daysThisMonth = 31;
int timeXPos = 0;
int test = 0;
int timeUpdate=0;
//long int timeAdvance = 0;


int main(void)
{
	_delay_ms(1000); //Oszillator powerup
	DDRB = 0xFF;//Ausgang
	//DDRB &= ~(1<<PORTB6);//Oszillator Eingänge
	//DDRB &= ~(1<<PORTB7);
	DDRD = 0xFF;//Ausgang
	DDRC = 0;//Eingang
//	PORTB = 0xff;
//	PORTD = 0xff;
	
	LCD_RST = 1;
	LCD_CS = 1;
	LCD_CLK = 1;
	lcdInit();
	clearLCD();
	printTime();
	updateLCD(stdDisplay);
/*
	
	ASSR |= (1<<AS2); //Activate asynchronous clock
	TCNT2 = 0; //set Timer2 counter = 0
    TCCR2B |= (1<<CS22)|(1<<CS20); //Prescaler 128
	OCR2A = 255;
	//TCCR2A |= (1<<WGM21); //Waveform mode: CTC
	TIMSK2 |= (1<<TOIE2); //Overflow-interrupt
	while(!(PINC & (1<<PINC5))){_delay_us(1);}
	TCNT2 = 0;

	//Quarz testen 
	if(PINC & (1<<PINC5)) {
		//PIN toggeln
		OCR2A = 1;
		//TCCR2A |= (1<<WGM21); //Waveform mode: CTC
		TCCR2B |= (1<<CS20); 
	}
	else {
		//Interrupt jede Sekunde
		OCR2A = 255;
		//TCCR2A |= (1<<WGM21); //Waveform mode: CTC
		TCCR2B |= (1<<CS22)|(1<<CS20); //Prescaler 128
	}
	if(PINC & (1<<PINC4)) 
		TCCR2A |= (1<<COM2B0);//Toggle PIN on compare-match
	else { 
		TCCR2A |= (1<<WGM21); //Clear timer on compare-match
		TIMSK2 |= (1<<TOIE2); //Overflow-interrupt
	}
	

	
	
	sei(); //Interrupts aktivieren
*/
	//printTime();
	//printAlarmLogo();
	//printDate();
	while(1) {
		/*cli();
		int timeUpdate2 = timeUpdate;
		sei();
		if(timeUpdate2 == 1) {
			incrementTime();
			timeUpdate2 = 0;
			timeUpdate = 0;
		}*/
	}
	
}
	
	/*ISR(TIMER2_OVF_vect) {
		timeAdvance ++;
		if(timeAdvance != 100000){
			seconds ++;
			if( seconds == 60 ) {
				timeUpdate = 1;
				seconds = 0;
				//aufwecken
			}
		} else {
			timeAdvance = 31034;
		}
		
	
		
		//if(cnt == 0) {
		//	PORTD |= 8;
		//	cnt = 1;
		//	//minute = TCNT2;
		//} else {
		//	cnt = 0;
		//	PORTD &= ~8;
		//}
	
	}*/
	
	void resetAlarmLogo() {
		for(int x = 1; x<10; x++){
			for(int y = 2; y<2+16; y++)
				resetPixel(x,y, stdDisplay);
		}
	}
	
	void printAlarmLogo() {
		uint8_t weckerSymb[72];
		for(int i=0; i<72; i++){
			weckerSymb[i] = pgm_read_byte(&note[0][i]);
		}
		printSymbol(16,9,weckerSymb,1/*116*/,2);
	}
	
	void incrementTime() {
		updateTimeXPos();
		for(int x = timeXPos; x<128; x++) {
			for(int y = TIMEY; y<TIMEY+BIG_NUMBER_HEIGHT; y++) {
				resetPixel(x,y, stdDisplay);
			}
		}
		minute ++;
		if(minute > 59) {
			minute = 0;
			hour++;
		}
		if(hour == 24) {
			hour = 0;
			incrementDate();
		}
		printTime();
		updateLCD(stdDisplay);
	}
	
	
	void incrementDate() {
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
		printDate();
		//updateLCD();
	}
	
	void printTime() {
		
		uint8_t dotSymb[20];
		for(int i=0; i<20; i++){
			dotSymb[i] = pgm_read_byte(&timeDot[i]);
		}
		int tempXPos = printHour();
		tempXPos = printSymbol(32,5,dotSymb,tempXPos,TIMEY);
		printMinute(tempXPos + SPACE_TO_DOTS);
	}
	
	void updateTimeXPos() {
		uint8_t width = 0;
		width += pgm_read_byte(&bigNumberWidth[hour%10]) + SPACE_TO_DOTS;
		width += pgm_read_byte(&bigNumberWidth[hour/10])  + INTER_DIGIT_SPACE;
		width += pgm_read_byte(&bigNumberWidth[minute/10])+ SPACE_TO_DOTS;
		width += pgm_read_byte(&bigNumberWidth[minute%10]) + INTER_DIGIT_SPACE;
		width += TIMEDOT_WIDTH;
		timeXPos = (127-width)/2;
	}
	
	int printHour() {
		updateTimeXPos();
		int tempX = timeXPos;//timeXPos-(pgm_read_byte(&bigNumberWidth[hour%10])+SPACE_TO_DOTS);
		printBigNumber(tempX,TIMEY,hour/10);
		tempX += pgm_read_byte(&bigNumberWidth[hour/10])+INTER_DIGIT_SPACE;
		printBigNumber(tempX,TIMEY,hour%10);
		return (tempX+pgm_read_byte(&bigNumberWidth[hour%10]) + SPACE_TO_DOTS);
	}
	
	void printMinute(int tempX) {
		if(minute<10) { //Null als erste Minutenzahl
			printBigNumber(tempX,TIMEY,0);
			tempX += pgm_read_byte(&bigNumberWidth[0])+INTER_DIGIT_SPACE;
		} else {
			printBigNumber(tempX,TIMEY,minute/10);
			tempX += pgm_read_byte(&bigNumberWidth[minute/10])+INTER_DIGIT_SPACE;
		}
		printBigNumber(tempX,TIMEY,minute%10);

	}
	
	void printDate() {
		for(int x = 0; x<128; x++) {
			for(int y=47; y<64; y++ ){
				resetPixel(x,y, stdDisplay);
			}
		}
		int dayWidth = getDayWidth();
		int monthWidth = getMonthWidth();
		int dateWidth = dayWidth + monthWidth + 6; //6=Punkt + Leerzeichen
		//dateWidth = 72;
		int xPosDate = (127 - dateWidth)/2 + 1/*+ dateWidth%2*/;
		printDay(xPosDate);	//Tag
		printLetter(alphaHeight, pgm_read_byte(&alphaWidth[54]), 54, xPosDate + dayWidth + 1, yPosDate, stdDisplay); //Punkt
		printMonth(xPosDate + dayWidth + 6); //Monat ..+6=Punkt+Leerzeichen
	}
	

	
	void printMonth(int xPos) {
		int tempXPos = xPos;
		int yPos = yPosDate;
		int tempLetter;		
		for (int i=0; i<maxMonthLength; i++) {
			tempLetter = pgm_read_byte(&months[month][i]);
			if (tempLetter<54) {
				if((tempLetter == 6) || (tempLetter == 15) || (tempLetter == 16) || (tempLetter == 24)) {
					yPos = yPos + 1;
				} else {
					yPos = yPosDate;
				}
				if(tempLetter == 1) {
					tempXPos --;
				}
				printLetter(alphaHeight, pgm_read_byte(&alphaWidth[tempLetter]), tempLetter, tempXPos, yPos, stdDisplay);
				tempXPos+=pgm_read_byte(&alphaWidth[tempLetter])+1;
			}
		}
	}
	
	
	
	void printDay(int xPos) {
		int tempDay = day;
		if(tempDay > 9) {
			printSmallNumber(xPos, yPosDate, tempDay/10, stdDisplay);
			printSmallNumber(xPos + pgm_read_byte(&smallNumberWidth[tempDay/10]) + 1, yPosDate, tempDay%10, stdDisplay);
		} else {
			printSmallNumber(xPos, yPosDate, tempDay, stdDisplay);
		}
	}
	
	int getDayWidth() {
		int tempDay = day;
		int width = -1;	
		width += pgm_read_byte(&smallNumberWidth[tempDay%10])+1; //+1für Leerzeichen
		if(day > 9) {
			width += pgm_read_byte(&smallNumberWidth[tempDay/10])+1;
		}
		return width;
	}
	
	int getMonthWidth() {
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
		for(int i = 0; i<sizeof(string)/sizeof(string[0]); i++) {
			//ASCII-Dezimalzahl des Zeichens umwandeln
			if((int)string[i]<97) {
				//Großbuchstabe
				index = (int)string[i]-65+26;
				} else {
				//Kleinbuchstabe
				index = (int)string[i]-97;
			}
			asciiArr[i] = index;
		}
	}


		
void lcdInit() {
	sendCmd(0x40);
	sendCmd(0xA1);
	sendCmd(0xC0);
	sendCmd(0xA6);
	sendCmd(0xA2);
	sendCmd(0x2F);
	sendCmd(0xF8);
	sendCmd(0x00);
	sendCmd(0x27);
	sendCmd(0x81);
	sendCmd(0x16);//0x10 lt. Datenblatt
	sendCmd(0xAC);
	sendCmd(0x00);
	sendCmd(0xAF);
}

void sendCmd(uint8_t data) {
	LCD_CS = 0;
	//_delay_us(1);
	for (int i = 0; i<8; i++) {
		LCD_CLK = 0;
		LCD_D = 0;
		if (data & 0x80) {
			LCD_D = 1;
		}
		//_delay_us(1);
		LCD_CLK = 1;
		//_delay_us(1);
		data = data<<1;
	}
	LCD_CS = 1;
	LCD_D = 0;
	//_delay_us(1);
}

void sendData(uint8_t data) {
	LCD_A0 = 1;
	sendCmd(data);
	LCD_A0 = 0;
}

void setColumn(uint8_t col) {
	sendCmd(0x0 | (col & 0xF));
	sendCmd(0x10 | ((col>>4) & 0xF));
}


void setPage(uint8_t p) {
	sendCmd(0xB0 + p);
}

void clearLCD() {
	for(int x = 0; x<128; x++){
		for(int y = 0; y<8; y++){
			setPage(y);
			setColumn(x);
			sendData(0);
			//resetPixel(x, y);
		}
	}
	//updateLCD();
}

void setPixel(uint8_t x, uint8_t y, uint8_t disp[128][8]) {
	int page = y/8;
	int pixel = y-page*8;
	uint8_t setzMaske = (1<<pixel);
	disp[x] [page] |= setzMaske;//stdDisplay [x] [page] |= setzMaske;
}

void resetPixel(uint8_t x, uint8_t y, uint8_t disp[128][8]) {
	int page = y/8;
	int pixel = y-page*8;
	uint8_t setzMaske =~ (1<<pixel);
	disp [x] [page] &= setzMaske;
}

void updateLCD(uint8_t disp[128][8]) {
	for(int col = 0; col<128; col++){
		for(int page = 0; page<8; page++){
			setPage(page);
			setColumn(col);
			sendData(disp[col][page]);//sendData(stdDisplay[col][page]);
		}
	}
}

int printSymbol(int height, int width,  uint8_t symbol[height/8*width], int xStart, int yStart) {
	for(int x=0; x<width; x++){
		for(int y=0; y<height; y++){
			if((symbol[x*height/8+y/8]) & (1<<(y%8))){
				setPixel(xStart+x,yStart+y, stdDisplay);
				} else {
				resetPixel(xStart+x,yStart+y, stdDisplay);
			}
		}
	}
	return xStart + width;
}

void printLetter(int height, int width, int asciiCode, int xStart, int yStart, uint8_t disp[128][8]) {
	for(int x = 0; x<width; x++) {
		for(int y = 0; y<height; y++) {
			if(pgm_read_byte(&alphabet[asciiCode][x*2+y/8]) & (1<<(y%8))){
				setPixel(xStart+x,yStart+y, disp);
				} else {
				resetPixel(xStart+x,yStart+y, disp);
			}
		}
	}
}

void printSmallNumber(int xStart, int yStart, int number, uint8_t disp[128][8]) {
	for(int x = 0; x<pgm_read_byte(&smallNumberWidth[number]); x++) {
		for(int y = 0; y<alphaHeight; y++) {
			if(pgm_read_byte(&smallNumber[number][x*2+y/8]) & (1<<(y%8))){
				setPixel(xStart+x,yStart+y, disp);
				} else {
				resetPixel(xStart+x,yStart+y, disp);
			}
		}
	}
}

void printBigNumber(int xStart, int yStart, int number) {
	for(int x = 0; x<pgm_read_byte(&bigNumberWidth[number]); x++) {
		for(int y = 0; y<32; y++) {
			if(pgm_read_byte(&bigNumber[number][x*BIG_NUMBER_HEIGHT/8+y/8]) & (1<<(y%8))){
				setPixel(xStart+x,yStart+y, stdDisplay);
				} else {
				resetPixel(xStart+x,yStart+y, stdDisplay);
			}
		}
	}
}
