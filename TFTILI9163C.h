#ifndef _TFTILI9163CLIB_H_
#define _TFTILI9163CLIB_H_

#include <stdbool.h>
#include <stdint.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/SPI.h>
#include <ti/drivers/PIN.h>

#include "_DisplaySettings/FTILI9163C_settings.h"


//--------- Keep out hands from here!-------------

#define	BLACK   		0x0000
#define WHITE   		0xFFFF

PIN_Handle _spiPinHandle;
#define _cs 19
#define _dc  4
#define _rst  1

class TFT_ILI9163C  {

 public:
	
	TFT_ILI9163C(void);
	~TFT_ILI9163C(void);

	void begin(void);
	void tempusDisplaySetup(PIN_Handle spiPnHndl);

	void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);//graphic Addressing
	void setCursor(int16_t x,int16_t y);//char addressing
	void pushColor(uint16_t color);
	void fillScreen(uint16_t color=0x0000);
	void clearScreen(uint16_t color=0x0000);//same as fillScreen
	void drawPixel(int16_t x, int16_t y, uint16_t color);
	void setRotation(uint8_t r);
	void invertDisplay(bool i);
	uint8_t errorCode(void);
	void idleMode(bool onOff);
	void display(bool onOff);
	void sleepMode(bool mode);
	void startPushData(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
	void pushData(uint16_t color);
	void endPushData();
	void writeScreen24(const uint32_t *bitmap,uint16_t size=_TFTWIDTH*_TFTHEIGHT);
	inline uint16_t Color565(uint8_t r, uint8_t g, uint8_t b) {return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);};
  //convert 24bit color into packet 16 bit one (credits for this are all mine)
	inline uint16_t Color24To565(int32_t color_) { return ((((color_ >> 16) & 0xFF) / 8) << 11) | ((((color_ >> 8) & 0xFF) / 4) << 5) | (((color_) &  0xFF) / 8);}
	void 		setBitrate(uint32_t n);	

 protected:
	volatile uint8_t		_Mactrl_Data;//container for the memory access control data
	uint8_t					_colorspaceData;

	void _setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);//graphic Addressing for Teensy
	
	void spiwrite(uint8_t c);
	void		writecommand(uint8_t c);
	void		writedata(uint8_t d);
	void		writedata16(uint16_t d);
	
 private:
	void 		colorSpace(uint8_t cspace);
	void 		setAddr(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
	uint8_t		sleep;
	void 		chipInit();
	bool 		boundaryCheck(int16_t x,int16_t y);
	void 		homeAddress();
	uint8_t		_initError;
};
#endif
