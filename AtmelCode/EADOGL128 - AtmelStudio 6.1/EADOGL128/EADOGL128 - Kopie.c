/*
 * EA_DOGL128.c
 *
 * Created: 11.03.2015 11:27:58
 *  Author: Malte
 * 
 */ 

#include "EADOGL128.h"
uint8_t pixelMaske [128] [8];


int main(void)
{
	DDRB = 0xFF;
	DDRD = 0xFF;
	PORTB = 0;
	PORTD = 0;
	
	LCD_RST = 1;
	LCD_CS = 1;
	LCD_CLK = 1;
	lcdInit();
	_delay_ms(1000);
	clearLCD();
	_delay_ms(200);
		for(int col = 0; col<128; col++){
			for(int page = 0; page<8; page++){
				setPage(page);
				setColumn(col);
				if((col%5) != 0){
					sendData(0);
					} else {
					sendData(0xff);
				}
			}
		}
	_delay_ms(1000);
	for(int x = 30; x<60; x++) {
		for (int y = 30; y<60; y++) {
			setPixel(x,y);
		}
	}
	updateLCD();
	_delay_ms(2000);
	printSymbol(wecker, 0, 0);
	updateLCD();
	
	while(1){	
		
		
		//Alle Pixel an/aus
		/*sendCmd(0xA4);
		_delay_ms(2000);
		sendCmd(0xA5);
		_delay_ms(2000);*/
	}
	//}
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
	sendCmd(0x16);//10
	sendCmd(0xAC);
	sendCmd(0x00);
	sendCmd(0xAF);
	//sendCmd(0xA4);//All points normal
	//sendCmd(0x10);//HB column-address
	//sendCmd(0x1); //LB column-address
}

void sendCmd(uint8_t data) {
	LCD_CS = 0;
	_delay_us(1);
	for (int i = 0; i<8; i++) {
		LCD_CLK = 0;
		LCD_D = 0;
		if (data & 0x80) {
			LCD_D = 1;
		}
		_delay_us(1);
		LCD_CLK = 1;
		_delay_us(1);
		data = data<<1;
	}
	LCD_CS = 1;
	LCD_D = 0;
	_delay_us(1);
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
	for(int col = 0; col<128; col++)
	for(int page = 0; page<8; page++){
		setPage(page);
		setColumn(col);
		sendData(0);
	}
}

void setPixel(uint8_t x, uint8_t y) {
	int page = y/8;
	int pixel = y-page*8;
	uint8_t setzMaske = (1<<pixel);
	pixelMaske [x] [page] |= setzMaske;
}

void updateLCD() {
	for(int col = 0; col<128; col++){
		for(int page = 0; page<8; page++){
			setPage(page);
			setColumn(col);
			sendData(pixelMaske[col][page]);
		}
	}
}

void printSymbol(const uint8_t symbol[][24], int xStart, int yStart) {
	for(int x=0; x<sizeof(symbol[0]); x++){
		for(int y=0; y<sizeof(symbol); y++){
			if((symbol[y/8] [x]) & (1<<y)){
				setPixel(xStart+x,yStart+y);
			}
		}
	}

}
