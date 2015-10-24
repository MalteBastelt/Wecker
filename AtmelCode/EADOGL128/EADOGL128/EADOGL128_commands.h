#define LCD_CS SBIT(PORTD, 6)
#define LCD_RST SBIT(PORTD, 7)
#define LCD_A0 SBIT(PORTB, 0)
#define LCD_D SBIT(PORTD, 5)
#define LCD_CLK SBIT(PORTB, 1)//PB7

uint8_t pixelMatrix [128] [8];

void lcdInit();

void sendCmd(uint8_t data);

void sendData(uint8_t data);


//Reihe setzen c = {0..127}
//Eine Reihe enth�lt 8 Pages
//0x0:  leastSignificant bits werden gesendet
//0x10: mostSignificant bits werden gesendet
void setColumn(uint8_t col);


//Page setzen p={0..7};
//Eine Page enth�lt 8px
//0xB0: Page = 0;
void setPage(uint8_t p);

void clear_LCD();

void set_pixel(uint8_t x, uint8_t y);

void reset_pixel(uint8_t x, uint8_t y);

void update_LCD();

int print_symbol(int height, int width,  uint8_t symbol[height/8*width], int xStart, int yStart);

void print_letter(int height, int width, int asciiCode, int xStart, int yStart);

void print_smallNumber(int xStart, int yStart, int number);

void print_bigNumber(int xStart, int yStart, int number);