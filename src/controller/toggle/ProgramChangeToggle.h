/*
 * ProgramChangeToggle.h
 *
 *  Created on: Aug 28, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_TOGGLE_PROGRAMCHANGETOGGLE_H_
#define SRC_CONTROLLER_TOGGLE_PROGRAMCHANGETOGGLE_H_

#include "../common/controller.h"

class ProgramChangeToggle: public Controller {
public:
	ProgramChangeToggle();
	ProgramChangeToggle(const int* data);
	ProgramChangeToggle(const int* data, Dispatcher* dispatcher);
	ProgramChangeToggle(const int* data, uint8_t ledPin, Dispatcher* dispatcher);

	~ProgramChangeToggle();

	void update();

	void setParameter(const uint16_t* value);

	boolean setConfiguration(const int* data);

#ifdef DEBUG
	void printContents();
#endif /* DEBUG */

private:
	const uint8_t ID = 0xE0;
	uint8_t channel;
	uint8_t bank;
	uint8_t program;

	uint16_t parameter;

	uint8_t ledPin;
	boolean toggle;
	boolean updated;

	Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_TOGGLE_PROGRAMCHANGETOGGLE_H_ */
