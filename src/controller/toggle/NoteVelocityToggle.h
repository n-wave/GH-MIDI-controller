/*
 * NoteVelocityToggle.h
 *
 *  Created on: Aug 22, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_NOTEVELOCITYTOGGLE_H_
#define SRC_CONTROLLER_NOTEVELOCITYTOGGLE_H_

#include "../controller.h"

class NoteVelocityToggle: public Controller {
public:
	NoteVelocityToggle();
	NoteVelocityToggle(const int* data);
	NoteVelocityToggle(const int* data, Dispatcher* dispatcher);
	NoteVelocityToggle(const int* data, uint8_t ledPin, Dispatcher* dispatcher);

	~NoteVelocityToggle();

	void update(const uint32_t* time);

	void setParameter(const uint16_t* value);
	uint16_t getParameter();
	boolean setConfiguration(const int* data);

#ifdef DEBUG
	void printContents();
#endif /* DEBUG */

private:
	const uint8_t ID = 0xE7;
	uint8_t channel;
	uint8_t toggleOption;
	uint8_t pitch;
	uint8_t velocity;

	uint16_t parameter;

	boolean enabled;
	uint8_t ledPin;

	Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_NOTEVELOCITYTOGGLE_H_ */
