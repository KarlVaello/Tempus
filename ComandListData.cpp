/*
 * ComandList.cpp
 *
 *  Created on: 27 de oct. de 2016
 *      Author: carlosvaellomartinez
 */

#include "ComandListData.h"
#include <stdint.h>

ComandListData::ComandListData(char id, uint8_t command, uint16_t dly_ms) {

	_id = id;
	_dly_ms = dly_ms;
	_command = command;

}
ComandListData::ComandListData(char id, uint8_t command, uint8_t cmds[],int a) {
	_id = id;
	_command = command;
	for (int j = 0; j < sizeof(cmds); j++) {
		_cmds[j] = cmds[j];
	}

}

ComandListData::ComandListData(void) {
}
ComandListData::~ComandListData(void) {
}

char ComandListData::getID() {
	return _id;
}

int ComandListData::getDelayMS() {
	return _dly_ms;
}

uint8_t ComandListData::getCommand() {
	return _command;
}

uint8_t* ComandListData::getCommandInstructions() {

	return _cmds;
}
