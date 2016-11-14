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
#include <ti/drivers/PIN.h>

int _width = ST7735_TFTWIDTH;
int _height = ST7735_TFTHEIGHT_144;

#include <stdint.h>

SPI_Handle spiHandle;
SPI_Params spiParams;
SPI_Transaction spiTransaction;


uint8_t transmitBuffer[1];


const int spiBitRate = 4000000; //4MHZ


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



TempusDisplay::TempusDisplay(){}

inline void TempusDisplay::spiwrite(uint8_t c) {



	transmitBuffer[0] = c;

	spiTransaction.count = 1;
	spiTransaction.txBuf = transmitBuffer;
	spiTransaction.rxBuf = NULL;

	SPI_transfer(spiHandle, &spiTransaction);



	//System_printf("spiwrite( %d )\n", c);
}

void TempusDisplay::tempusDisplaySetup(PIN_Handle spiPnHndl){
	_spiPinHandle = spiPnHndl;

}

void TempusDisplay::initDisplay(uint8_t options) {


	SPI_Params_init(&spiParams);
	spiParams.transferMode = SPI_MODE_BLOCKING;
	spiParams.transferCallbackFxn = NULL;
	spiParams.mode = SPI_MASTER;
	spiParams.bitRate = spiBitRate;
	spiParams.dataSize = 8;
	spiHandle = SPI_open(0, &spiParams);
	if (!spiHandle) {
		System_printf("SPI did not open \n");
	}
	colstart = rowstart = 0; // May be overridden in init func

	PIN_setOutputValue(_spiPinHandle, PIN_ID(_cs), 0);

	//System_printf("Reset\n");
	PIN_setOutputValue(_spiPinHandle, PIN_ID(_rst), 1);
	__delay_cycles(24000000);
	PIN_setOutputValue(_spiPinHandle, PIN_ID(_rst), 0);
	__delay_cycles(24000000);
	PIN_setOutputValue(_spiPinHandle, PIN_ID(_rst), 1);
	__delay_cycles(24000000);
	//System_printf("Reset End\n");

	//System_printf("Comandos\n");
	//Rcmd1
	writecommand(ST7735_SWRESET);
	__delay_cycles(7200000);
	writecommand(ST7735_SLPOUT);
	__delay_cycles(24000000);
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

	 _height = ST7735_TFTHEIGHT_144;
	//Rcmd2red
	writecommand(ST7735_CASET);
	writedata(0x00);
	writedata(0x00);
	writedata(0x00);
	writedata(0x7F);

	writecommand(ST7735_RASET);
	writedata(0x00);
	writedata(0x00);
	writedata(0x00);
	writedata(0x7F);
	  colstart = 0;
	  rowstart = 32;
	//Rcmd3
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
	__delay_cycles(480000);
	writecommand(ST7735_DISPON);
	__delay_cycles(24000000);

	tabcolor = options;
	//System_printf("Fin comandos \n");
	SPI_close(spiHandle);
}
void TempusDisplay::closeSPI() {

SPI_close(spiHandle);
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


	SPI_Params_init(&spiParams);
	spiParams.transferMode = SPI_MODE_BLOCKING;
	spiParams.transferCallbackFxn = NULL;
	spiParams.mode = SPI_MASTER;
	spiParams.bitRate = spiBitRate;
	spiParams.dataSize = 8;
	spiHandle = SPI_open(0, &spiParams);
	if (!spiHandle) {
		System_printf("SPI did not open \n");
	}

	if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height))
		return;

	setAddrWindow(x, y, x + 1, y + 1);

	//*rsport |= rspinmask;
	PIN_setOutputValue(_spiPinHandle, PIN_ID(_dc), 0);

	//*csport &= ~cspinmask;
	PIN_setOutputValue(_spiPinHandle, PIN_ID(_cs), 0);

	spiwrite(color >> 8);
	spiwrite(color);

	//*csport |= cspinmask;
	PIN_setOutputValue(_spiPinHandle, PIN_ID(_cs), 1);

	SPI_close(spiHandle);

}



void TempusDisplay::writecommand(uint8_t c) {
	//System_printf("Escribiendo Comando\n");

	//*rsport &= ~rspinmask;
	PIN_setOutputValue(_spiPinHandle, PIN_ID(_dc), 0);
	//*csport &= ~cspinmask;
	PIN_setOutputValue(_spiPinHandle, PIN_ID(_cs), 0);

//Serial.print("C ");
	spiwrite(c);

	//*csport |= cspinmask;
	PIN_setOutputValue(_spiPinHandle, PIN_ID(_cs), 1);

}

void TempusDisplay::writedata(uint8_t c) {

	//*rsport |=  rspinmask;
	PIN_setOutputValue(_spiPinHandle, PIN_ID(_dc), 1);

	//*csport &= ~cspinmask;
	PIN_setOutputValue(_spiPinHandle, PIN_ID(_cs), 0);

//Serial.print("D ");
	spiwrite(c);

	//*csport |= cspinmask;
	PIN_setOutputValue(_spiPinHandle, PIN_ID(_cs), 1);

}

