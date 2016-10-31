/*
 * Tempus_ST7735S.cpp
 *
 *  Created on: 27 de oct. de 2016
 *      Author: carlosvaellomartinez
 */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <ti/drivers/SPI.h>
#include <TempusDisplay.h>
#include "CC1350_LAUNCHXL.h"
#include "ComandListData.h"

int _width = ST7735_TFTWIDTH;
int _height = ST7735_TFTHEIGHT_18;

#include <stdint.h>

SPI_Handle spiHandle;
SPI_Params spiParams;
SPI_Transaction spiTransaction;

const int spiBitRate = 4000000; //4MHZ
static PIN_Handle spiPinHandle;
static PIN_State spiPinState;

PIN_Config spiPinTable[] =
		{
				PIN_ID(
						_cs) | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH| PIN_PUSHPULL | PIN_DRVSTR_MAX,
				PIN_ID(
						_rs) | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH| PIN_PUSHPULL | PIN_DRVSTR_MAX,
				PIN_ID(
						_rst) | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH| PIN_PUSHPULL | PIN_DRVSTR_MAX,
				PIN_TERMINATE };

// Constructor when using software SPI.  All output pins are configurable.
TempusDisplay::TempusDisplay(int8_t cs, int8_t rs, int8_t sid, int8_t sclk,
		int8_t rst) {
	_cs = cs;
	_rs = rs;
	_sid = sid;
	_sclk = sclk;
	_rst = rst;
	hwSPI = false;
}

// Constructor when using hardware SPI.  Faster, but must use SPI pins
// specific to each board type (e.g. 11,13 for Uno, 51,52 for Mega, etc.)
TempusDisplay::TempusDisplay(int8_t cs, int8_t rs, int8_t rst) {
	_cs = cs;
	_rs = rs;
	_rst = rst;
	hwSPI = true;
	_sid = _sclk = 0;
}

// delay secands
void TempusDisplay::delay_s(unsigned int dly) {

	while (dly--) {
		__delay_cycles(48000000);
	}
}

// delay microseconds
void TempusDisplay::delay_ms(unsigned int dly) {

	while (dly--) {
		__delay_cycles(48000000);
	}
}

inline void TempusDisplay::spiwrite(uint8_t c) {
	System_printf("Escribiendo spiwrite( %d )\n", c);

	uint8_t transmitBuffer[1];

	SPI_Params_init(&spiParams);
	spiParams.transferMode = SPI_MODE_BLOCKING;
	spiParams.transferTimeout = SPI_WAIT_FOREVER;
	spiParams.transferCallbackFxn = NULL;
	spiParams.mode = SPI_MASTER;
	spiParams.bitRate = spiBitRate;
	spiParams.dataSize = 6;
	spiHandle = SPI_open(0, &spiParams);

	if (!spiHandle) {
		System_printf("SPI did not open \n");
	} else {

		transmitBuffer[0] = c;

		spiTransaction.count = 1;
		spiTransaction.txBuf = transmitBuffer;
		spiTransaction.rxBuf = NULL;

		//SPI_transfer(spiHandle, &spiTransaction);

	}
	SPI_close(spiHandle);

	System_printf("fin spiwrite\n");

}

// Companion code to the above tables.  Reads and issues
// a series of LCD commands stored in PROGMEM byte array.
void TempusDisplay::commandList(ComandListData adrs[]) {
	System_printf("commandList\n");

	//uint8_t numCommands;
	int numArgs;
	uint16_t ms;

	int numCommands = nElements(adrs);
	System_printf("numCommands: %d\n", numCommands);

	for (int i = 0; i <= numCommands; i++) {
		writecommand(adrs[i].getCommand());
		if (adrs[i].getID() == 'D') {
			ms = adrs[i].getDelayMS();
			if (ms) {
				if (ms == 255) {
					ms = 500;     // If 255, delay for 500 ms
				}
				//delay_ms(ms);
			}
		} else if (adrs[i].getID() == 'C') {
			numArgs = nElements(adrs[i].getCommandInstructions());
			for (int j = 0; j <= numArgs; j--) {
				writedata(adrs[i].getCommandInstructions()[j]);
			}
		}
		System_printf("i: %d\n", i);
	}
}

// Initialization code common to both 'B' and 'R' type displays
void TempusDisplay::commonInit(ComandListData *cmdListCI) {
	System_printf("commonInit\n");
	int cmdListSize = nElements(cmdListCI);
	System_printf("cmdListSize: %d\n", cmdListSize);
	colstart = rowstart = 0; // May be overridden in init func

	SPI_Params_init(&spiParams);
	spiParams.mode = SPI_MASTER;
	spiParams.bitRate = spiBitRate;
	spiParams.dataSize = 6;

	spiHandle = SPI_open(0, &spiParams);

	spiPinHandle = PIN_open(&spiPinState, spiPinTable);

	//en arduino digitalPinToPort(PIN)
	//digitalPinToPort(10) = PB
	//en portOutputRegister(PORT)
	//a = portOutputRegiste(PB) = &PORTB
	// esto hace que el puerto PB se de salida de pines del 8 al 13
	// esto te permite hacer algo como a = B10101000
	//csport = portOutputRegister(digitalPinToPort(_cs));
	//rsport = portOutputRegister(digitalPinToPort(_rs));

	//esto te permite hacer algo como

	//cspinmask = digitalPinToBitMask(_cs);
	//rspinmask = digitalPinToBitMask(_rs);
	//*rsport |= rspinmask;
	//*rsport = *rsport | rspinmask
	//01010000 |= 00001000 -> 00001000
	//01011000 |= 00001000 -> 01011000
	//*csport &= ~cspinmask;
	//*csport = *csport & ~cspinmask;
	//cspinmask = 00010010
	//~cspinmask = 11101101
	//01010000 &= 00001000 -> 00000000
	//01011000 &= 00001000 -> 00001000

	//#define TFT_CS  10  // Chip select line for TFT display
	//#define TFT_RST  9  // Reset line for TFT (or see below...)
	//#define TFT_DC   8  // Data/command line for TFT

	//csport = portOutputRegister(digitalPinToPort(_cs));
	//csport = portOutputRegister(digitalPinToPort(10));
	//digitalPinToPort(10) = PB
	//portOutputRegister(PB) = &PORTB
	//csport = &PORTB

	//rsport = portOutputRegister(digitalPinToPort(_rs));
	//rsport = portOutputRegister(digitalPinToPort(10));
	//digitalPinToPort(9) = PB
	//portOutputRegister(PB) = &PORTB
	//rsport = &PORTB

	//cspinmask = digitalPinToBitMask(_cs);
	//cspinmask = digitalPinToBitMask(10);
	//digitalPinToBitMask(10) = 	_BV(2);
	//cspinmask = _BV(2) ->  0b00000100.;
	//rspinmask = digitalPinToBitMask(_rs);
	//cspinmask = digitalPinToBitMask(9);
	//digitalPinToBitMask(9) = 	_BV(1);
	//cspinmask = _BV(1) ->  0b00000010.;

	//*rsport = *rsport | rspinmask
	//*rsport = 1 | 1 = 1
	//*rsport = 0 | 1 = 1
	//RS will be always high
	//*rsport = *rsport | ~rspinmask
	//*rsport = 1 | ~1 = 1
	//*rsport = 0 | ~1 = 1
	//RS will be always high

	//*csport = *csport & ~cspinmask;
	//*csport = 1 & ~1 = 1 & 0 = 0
	//*csport = 0 & ~1 = 0 & 0 = 0
	//CS low so it'll be always listen to us

	// toggle RST low to reset; CS low so it'll listen to us
	//*csport &= ~cspinmask;
	PIN_setOutputValue(spiPinHandle, PIN_ID(_cs), 0);

	if (_rst) {
		System_printf("reset\n");

		PIN_setOutputValue(spiPinHandle, PIN_ID(_rst), 1);
		//delay_ms(500);
		__delay_cycles(24000000);

		PIN_setOutputValue(spiPinHandle, PIN_ID(_rst), 0);
		//delay_ms(500);
		__delay_cycles(24000000);

		PIN_setOutputValue(spiPinHandle, PIN_ID(_rst), 1);
		//delay_ms(500);
		__delay_cycles(24000000);

	}

	if (cmdListCI) {
		System_printf("if-Cmd-List\n");

		commandList(cmdListCI);
	}
}

uint8_t CASET[4] = { 0x00, 0x00, 0x00, 0x7F };
uint8_t RASET[4] = { 0x00, 0x00, 0x00, 0x9F };
ComandListData Rcmd2red[] = { ComandListData('C', ST7735_CASET, CASET, 0), //Column addr set
ComandListData('C', ST7735_CASET, RASET, 0), //Memory access control (directions) row addr/col addr, bottom to top refresh
		};

void TempusDisplay::initDisplay(uint8_t options) {

	colstart = rowstart = 0; // May be overridden in init func

	spiPinHandle = PIN_open(&spiPinState, spiPinTable);
	PIN_setOutputValue(spiPinHandle, PIN_ID(_cs), 0);

	if (_rst) {
		System_printf("Reset\n");
		PIN_setOutputValue(spiPinHandle, PIN_ID(_rst), 1);
		//delay_ms(500);
		__delay_cycles(24000000);
		PIN_setOutputValue(spiPinHandle, PIN_ID(_rst), 0);
		//delay_ms(500);
		__delay_cycles(24000000);
		PIN_setOutputValue(spiPinHandle, PIN_ID(_rst), 1);
		//delay_ms(500);
		__delay_cycles(24000000);
		System_printf("Reset End\n");
	}
	System_printf("Comandos\n");

	writecommand(ST7735_SWRESET);
	//delay 150
	writecommand(ST7735_SWRESET);
	//delay 255
	writecommand(ST7735_FRMCTR1);
	writedata(0x01);
	writedata(0x2C);
	writedata(0x2D);
	writecommand(ST7735_FRMCTR2);
	writedata(0x01);
	writedata(0x2C);
	writedata(0x2D);
	writecommand(ST7735_FRMCTR3);
	writedata(0x01);
	writedata(0x2C);
	writedata(0x2D);
	writedata(0x01);
	writedata(0x2C);
	writedata(0x2D);
	writecommand(ST7735_INVCTR);
	writedata(0x07);
	writecommand(ST7735_PWCTR1);
	writedata(0xA2);
	writedata(0x02);
	writedata(0x84);
	writecommand(ST7735_PWCTR2);
	writedata(0xC5);
	writecommand(ST7735_PWCTR3);
	writedata(0x0A);
	writedata(0x00);
	writecommand(ST7735_PWCTR4);
	writedata(0x8A);
	writedata(0x2A);
	writecommand(ST7735_PWCTR5);
	writedata(0x8A);
	writedata(0xEE);
	writecommand(ST7735_VMCTR1);
	writedata(0x0E);
	writecommand(ST7735_INVOFF);
	writecommand(ST7735_MADCTL);
	writedata(0xC8);
	writecommand(ST7735_COLMOD);
	writedata(0x05);

	/*    0x02, 0x1c, 0x07, 0x12,
	 0x37, 0x32, 0x29, 0x2d,
	 0x29, 0x25, 0x2B, 0x39,
	 0x00, 0x01, 0x03, 0x10,*/
	writecommand(ST7735_GMCTRP1);
	writedata(0x02);
	writedata(0x1c);
	writedata(0x07);
	writedata(0x12);

	writedata(0x37);
	writedata(0x32);
	writedata(0x29);
	writedata(0x2d);

	writedata(0x29);
	writedata(0x25);
	writedata(0x2B);
	writedata(0x39);

	writedata(0x00);
	writedata(0x01);
	writedata(0x03);
	writedata(0x10);

	/*    0x03, 0x1d, 0x07, 0x06,
	 0x2E, 0x2C, 0x29, 0x2D,
	 0x2E, 0x2E, 0x37, 0x3F,
	 0x00, 0x00, 0x02, 0x10,*/
	writecommand(ST7735_GMCTRN1);
	writedata(0x03);
	writedata(0x1d);
	writedata(0x07);
	writedata(0x06);

	writedata(0x2E);
	writedata(0x2C);
	writedata(0x29);
	writedata(0x2D);

	writedata(0x2E);
	writedata(0x2E);
	writedata(0x37);
	writedata(0x3F);

	writedata(0x00);
	writedata(0x00);
	writedata(0x02);
	writedata(0x10);

	writecommand(ST7735_NORON);
	//delay 10
	writecommand(ST7735_DISPON);
	//delay 100

	if (options == INITR_BLACKTAB) {
		writecommand(ST7735_MADCTL);
		writedata(0xC0);
	}

	tabcolor = options;
	System_printf("Fin comandos \n");

}

// Initialization for ST7735R screens (green or red tabs)
void TempusDisplay::initR(uint8_t options) {
	//System_printf("initR\n");
	//int Rcmd1Size = nElements(Rcmd1);
	//System_printf("Rcmd1 size: %d\n", Rcmd1Size);
	System_printf("CommonInit---Rcmd1\n");
	//commonInit(Rcmd1);
	//if (options == INITR_GREENTAB) {
	//commandList(Rcmd2green);
	//colstart = 2;
	//rowstart = 1;
	//} else if (options == INITR_144GREENTAB) {
	_height = 144;
	//commandList(Rcmd2green144);
	//colstart = 2;
	//rowstart = 3;
	//} else {
	// colstart, rowstart left at default '0' values
	//commandList(Rcmd2red);
	//}
	//int Rcmd3Size = nElements(Rcmd3);
	//System_printf("Rcmd3 size: %d\n", Rcmd3Size);
	System_printf("commandList---Rcmd3\n");
	//commandList(Rcmd3);

// if black, change MADCTL color filter
	/*if (options == INITR_BLACKTAB) {
	 writecommand(ST7735_MADCTL);
	 writedata(0xC0);
	 }

	 tabcolor = options;*/
}
void TempusDisplay::setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1,
		uint8_t y1) {

	writecommand(ST7735_CASET); // Column addr set
	writedata(0x00);
	writedata(x0 + colstart);     // XSTART
	writedata(0x00);
	writedata(x1 + colstart);     // XEND

	writecommand(ST7735_RASET); // Row addr set
	writedata(0x00);
	writedata(y0 + rowstart);     // YSTART
	writedata(0x00);
	writedata(y1 + rowstart);     // YEND

	writecommand(ST7735_RAMWR); // write to RAM
}

void TempusDisplay::drawPixel(int16_t x, int16_t y, uint16_t color) {

	if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height))
		return;

	setAddrWindow(x, y, x + 1, y + 1);

	//*rsport |= rspinmask;
	PIN_setOutputValue(spiPinHandle, PIN_ID(_cs), 0);

	//*csport &= ~cspinmask;
	PIN_setOutputValue(spiPinHandle, PIN_ID(_cs), 0);

	spiwrite(color >> 8);
	spiwrite(color);

	//*csport |= cspinmask;
	PIN_setOutputValue(spiPinHandle, PIN_ID(_cs), 1);

}

void TempusDisplay::writecommand(uint8_t c) {
	System_printf("Escribiendo Comando\n");

	//*rsport &= ~rspinmask;
	PIN_setOutputValue(spiPinHandle, PIN_ID(_rs), 0);
	//*csport &= ~cspinmask;
	PIN_setOutputValue(spiPinHandle, PIN_ID(_cs), 0);

//Serial.print("C ");
	spiwrite(c);

	//*csport |= cspinmask;
	PIN_setOutputValue(spiPinHandle, PIN_ID(_cs), 1);

}

void TempusDisplay::writedata(uint8_t c) {

	//*rsport |=  rspinmask;
	PIN_setOutputValue(spiPinHandle, PIN_ID(_rs), 1);

	//*csport &= ~cspinmask;
	PIN_setOutputValue(spiPinHandle, PIN_ID(_cs), 0);

//Serial.print("D ");
	spiwrite(c);

	//*csport |= cspinmask;
	PIN_setOutputValue(spiPinHandle, PIN_ID(_cs), 1);

}

