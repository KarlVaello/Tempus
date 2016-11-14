#ifndef TEMPUSDISPLAY_H
#define TEMPUSDISPLAY_H

#include <stdbool.h>
#include <stdint.h>

#include "ComandListData.h"
#include <ti/drivers/GPIO.h>
#include <ti/drivers/SPI.h>
#include <ti/drivers/PIN.h>

// some flags for initR() :(
#define INITR_GREENTAB 0x0
#define INITR_REDTAB   0x1
#define INITR_BLACKTAB   0x2

#define INITR_18GREENTAB    INITR_GREENTAB
#define INITR_18REDTAB      INITR_REDTAB
#define INITR_18BLACKTAB    INITR_BLACKTAB
#define INITR_144GREENTAB   0x1

#define ST7735_TFTWIDTH  128
// for 1.44" display
#define ST7735_TFTHEIGHT_144 128
// for 1.8" display
#define ST7735_TFTHEIGHT_18  160

#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09

#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13

#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E

#define ST7735_PTLAR   0x30
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5

#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD

#define ST7735_PWCTR6  0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

// Color definitions
#define	ST7735_BLACK   0x0000
#define	ST7735_BLUE    0x001F
#define	ST7735_RED     0xF800
#define	ST7735_GREEN   0x07E0
#define ST7735_CYAN    0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW  0xFFE0
#define ST7735_WHITE   0xFFFF

volatile uint32_t *dataport;
volatile uint32_t *clkport;
volatile uint32_t *csport;
volatile uint32_t *rsport;


#define _cs 19
#define _dc  4
#define _rst  1
/*uint32_t _cs;
uint32_t _rs;
uint32_t _rst;
uint32_t _sid;
uint32_t _sclk;*/

uint32_t datapinmask;
uint32_t clkpinmask;
uint32_t cspinmask;
uint32_t rspinmask;
uint32_t colstart; // some displays need this changed
uint32_t rowstart; // some displays need this changed

PIN_Handle _spiPinHandle;

#define nElements(array) (sizeof(array) / sizeof(array[0]))

class TempusDisplay{
public:
	TempusDisplay(void);
	~TempusDisplay(void);

	void tempusDisplaySetup(PIN_Handle spiPnHndl);
	void initDisplay(uint8_t options);
	void setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
	void drawPixel(int16_t x, int16_t y, uint16_t color);
	//void uint16_t Color565(uint8_t r, uint8_t g, uint8_t b);
	void closeSPI();
private:
	uint8_t tabcolor;

	void spiwrite(uint8_t);
	void writecommand(uint8_t c);
	void writedata(uint8_t d);
	void commandList(ComandListData adrs[]);

	uint8_t  spiread(void);

	void delay_ms(unsigned int dly);
	void delay_s(unsigned int dly);

	bool hwSPI;
};

#endif
