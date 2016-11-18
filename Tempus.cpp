/*
 *  ======== empty_min.c ========
 */
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>

/* TI-RTOS Header files */
#include <ti/sysbios/knl/Task.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/SPI.h>
#include <TFTILI9163C.h>

/* Board Header files */
#include "Board.h"


#define TFT_CS  19  // Chip select line for TFT display
#define TFT_DC   4 // Data/command line for TFT
#define TFT_RST  1  // Reset line for TFT (or connect to +5V)

TFT_ILI9163C* tft = new TFT_ILI9163C();

bool inLoop = true;
bool b = false;
/* Pin driver handles */



static PIN_State buttonPinState;
static PIN_Handle buttonPinHandle;

static PIN_State spiPinState;
static PIN_Handle spiPinHandle;

PIN_Config spiPinTable[] =
		{
PIN_ID(19) | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW| PIN_PUSHPULL | PIN_DRVSTR_MAX,
PIN_ID(4) | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW| PIN_PUSHPULL | PIN_DRVSTR_MAX,
PIN_ID(1) | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW| PIN_PUSHPULL | PIN_DRVSTR_MAX,
PIN_TERMINATE };

/*
 * Application button pin configuration table:
 *   - Buttons interrupts are configured to trigger on falling edge.
 */
PIN_Config buttonPinTable[] = {
Board_BUTTON0 | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
Board_BUTTON1 | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
PIN_TERMINATE };

Char myTaskStack[1024];
Task_Struct myTaskStruct;


// ======== LOOP ========
void loop() {


}

Void taskFxn(UArg arg0, UArg arg1) {
	//System_printf("Start task\n");

	//System_printf("Start Display Setup\n");

	tft->begin();

	//System_printf("End Display Setup\n");

	System_printf("Draw pixel at 10x10, in black\n");

	for(int i = 0; i < 140; i++){
		for (int j = 0; j < 140;j++){
			System_printf("i: %d ; j: %d\n", i, j);

			tft->drawPixel(i, j, BLACK);

		}
	}

	System_printf("Draw pixel\n");

	while (inLoop) {
		loop();
	}

}


// ======== SETUP ========
void setup() {

	//System_printf("\n");
	//System_printf("Start Setup\n");
	/* Call board init functions */
	Board_initGeneral();
	SPI_init();
	//Board_initSPI();


	// to enable interrupts and start the scheduler and kick BIOS into gear.
	spiPinHandle = PIN_open(&spiPinState, spiPinTable);
	if (!spiPinHandle) {
		System_abort("Error initializing board LED pins\n");
	}
	PIN_setOutputValue(spiPinHandle, PIN_ID(17), 1);

	PIN_setOutputValue(spiPinHandle, PIN_ID(1), 1);

	buttonPinHandle = PIN_open(&buttonPinState, buttonPinTable);
	if (!buttonPinHandle) {
		System_abort("Error initializing button pins\n");
	}



	tft->tempusDisplaySetup(spiPinHandle);

	/* Configure task. */
	Task_Params taskParams;
	Task_Params_init(&taskParams);
	taskParams.stack = myTaskStack;
	taskParams.stackSize = sizeof(myTaskStack);
	Task_construct(&myTaskStruct, taskFxn, &taskParams, NULL);

	//System_printf("End Setup\n");
}



/*
 *  ======== main ========
 */
Int main() {

	setup();

	BIOS_start();
	//BIOS_exit(0); /* terminates program and dumps SysMin output */

	return (0);
}

