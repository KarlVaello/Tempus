/*
 * ComandList.h
 *
 *  Created on: 27 de oct. de 2016
 *      Author: carlosvaellomartinez
 */

#ifndef __COMANDLISTDATA_H
#define __COMANDLISTDATA_H

#include <stdint.h>

class ComandListData {
public:
	char _id;
	uint16_t _dly_ms;
	uint8_t _command;
	uint8_t _cmds[];

	ComandListData(void);
	ComandListData(char id, uint8_t command, uint16_t dly_ms);
	ComandListData(char id, uint8_t command, uint8_t cmds[], int a);
	~ComandListData(void);

	char getID();
	int getDelayMS();
	uint8_t getCommand();
	uint8_t* getCommandInstructions();
};

#endif
