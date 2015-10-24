#include "EADOGL128_commands.h"

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
	sendCmd(0x16);//0x10 lt. Datenblatt//meins: 16
	sendCmd(0xAC);
	sendCmd(0x00);
	sendCmd(0xAF);
}

void sendCmd(uint8_t data) {
	LCD_CS = 0;
	for (int i = 0; i<8; i++) {
		LCD_CLK = 0;
		LCD_D = 0;
		if (data & 0x80) {
			LCD_D = 1;
		}
		LCD_CLK = 1;
		data = data<<1;
	}
	LCD_CS = 1;
	LCD_D = 0;
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

void clear_LCD() {
	for(int x = 0; x<128; x++){
		for(int y = 0; y<8; y++){
			setPage(y);
			setColumn(x);
			sendData(0);
			//reset_Pixel(x, y);
		}
	}
	//update_LCD();
}

void set_pixel(uint8_t x, uint8_t y) {
	int page = y/8;
	int pixel = y-page*8;
	uint8_t setzMaske = (1<<pixel);
	pixelMatrix[x] [page] |= setzMaske;//stdDisplay [x] [page] |= setzMaske;
}

void reset_pixel(uint8_t x, uint8_t y) {
	int page = y/8;
	int pixel = y-page*8;
	uint8_t setzMaske =~ (1<<pixel);
	pixelMatrix [x] [page] &= setzMaske;
}

void update_LCD() {
	for(int col = 0; col<128; col++){
		for(int page = 0; page<8; page++){
			setPage(page);
			setColumn(col);
			sendData(pixelMatrix[col][page]);//sendData(stdDisplay[col][page]);
		}
	}
}

int print_symbol(int height, int width,  uint8_t symbol[height/8*width], int xStart, int yStart) {
	for(int x=0; x<width; x++){
		for(int y=0; y<height; y++){
			if((symbol[x*height/8+y/8]) & (1<<(y%8))){
				set_pixel(xStart+x,yStart+y);
				} else {
				reset_pixel(xStart+x,yStart+y);
			}
		}
	}
	return xStart + width;
}



void print_letter(int height, int width, int asciiCode, int xStart, int yStart) {
	for(int x = 0; x<width; x++) {
		for(int y = 0; y<height; y++) {
			if(pgm_read_byte(&alphabet[asciiCode][x*2+y/8]) & (1<<(y%8))){
				set_pixel(xStart+x,yStart+y);
				} else {
				reset_pixel(xStart+x,yStart+y);
			}
		}
	}
}

void print_smallNumber(int xStart, int yStart, int number) {
	for(int x = 0; x<pgm_read_byte(&smallNumberWidth[number]); x++) {
		for(int y = 0; y<alphaHeight; y++) {
			if(pgm_read_byte(&smallNumber[number][x*2+y/8]) & (1<<(y%8))){
				set_pixel(xStart+x,yStart+y);
				} else {
				reset_pixel(xStart+x,yStart+y);
			}
		}
	}
}

void print_bigNumber(int xStart, int yStart, int number) {
	for(int x = 0; x<pgm_read_byte(&bigNumberWidth[number]); x++) {
		for(int y = 0; y<32; y++) {
			if(pgm_read_byte(&bigNumber[number][x*BIG_NUMBER_HEIGHT/8+y/8]) & (1<<(y%8))){
				set_pixel(xStart+x,yStart+y);
				} else {
				reset_pixel(xStart+x,yStart+y);
			}
		}
	}
}