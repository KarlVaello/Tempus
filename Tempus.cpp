/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== empty_min.c ========
 */
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>

/* TI-RTOS Header files */
// #include <ti/drivers/I2C.h>
#include <ti/drivers/PIN.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>

/* Board Header files */
#include "Board.h"

#include "TempusDisplay.h"

#define TFT_CS  19  // Chip select line for TFT display
#define TFT_DC   20 // Data/command line for TFT
#define TFT_RST  17  // Reset line for TFT (or connect to +5V)

TempusDisplay* tft = new TempusDisplay(TFT_CS, TFT_DC, TFT_RST);

bool inLoop = true;
bool b = false;
/* Pin driver handles */
static PIN_Handle oldPinHandle;
/* Global memory storage for a PIN_Config table */
static PIN_State oldPinState;

static PIN_State buttonPinState;
static PIN_Handle buttonPinHandle;

PIN_Config oldPinTable[] = {
PIN_ID(1) | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX,

PIN_TERMINATE };

/*
 * Application button pin configuration table:
 *   - Buttons interrupts are configured to trigger on falling edge.
 */
PIN_Config buttonPinTable[] = {
Board_BUTTON0 | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
Board_BUTTON1 | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
PIN_TERMINATE };



// ======== SETUP ========
void setup() {

 	System_printf("\n");
	System_printf("Start Setup\n");
	/* Call board init functions */
	Board_initGeneral()
	;
	// to enable interrupts and start the scheduler and kick BIOS into gear.

	oldPinHandle = PIN_open(&oldPinState, oldPinTable);
	if (!oldPinHandle) {
		System_abort("Error initializing board LED pins\n");
	}

	buttonPinHandle = PIN_open(&buttonPinState, buttonPinTable);
	if (!buttonPinHandle) {
		System_abort("Error initializing button pins\n");
	}

	System_printf("End Setup\n");

	System_printf("Start Display Setup\n");

	tft->initDisplay(INITR_BLACKTAB);

	System_printf("End Display Setup\n");

	System_printf("Draw pixel at 10x10, in black\n");
	tft->drawPixel(10,10,ST7735_BLACK);

}

// ======== LOOP ========
void loop() {

	if (!PIN_getInputValue(PIN_ID(13))) {

		System_printf("Button\n");
		PIN_setOutputValue(oldPinHandle, PIN_ID(6), 1);
		PIN_setOutputValue(oldPinHandle, PIN_ID(7), 1);

	} else {

		PIN_setOutputValue(oldPinHandle, PIN_ID(6), 1);
		PIN_setOutputValue(oldPinHandle, PIN_ID(7), 0);

		PIN_setOutputValue(oldPinHandle, PIN_ID(6), 0);
		PIN_setOutputValue(oldPinHandle, PIN_ID(7), 1);
	}
}

/*
 *  ======== main ========
 */
Int main() {

	setup();

	while (inLoop) {
		loop();
	}
	//BIOS_start();
	//BIOS_exit(0); /* terminates program and dumps SysMin output */

	return (0);
}

