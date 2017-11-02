/*
 * NoteControlChangeToggle8Bit.h
 *
 *  Created on: Aug 22, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_NOTECONTROLCHANGETOGGLE8BIT_H_
#define SRC_CONTROLLER_NOTECONTROLCHANGETOGGLE8BIT_H_

#include "../common/controller.h"

class NoteControlChangeToggle8Bit: public Controller {
public:
	NoteControlChangeToggle8Bit();
	NoteControlChangeToggle8Bit(const int* data);
	NoteControlChangeToggle8Bit(const int* data, Dispatcher* dispatcher);
	NoteControlChangeToggle8Bit(const int* data, uint8_t ledPin, Dispatcher* dispatcher);

	~NoteControlChangeToggle8Bit();

	void update();

	void setParameter(const uint16_t* value);
	boolean setConfiguration(const int* data);

#ifdef DEBUG
	void printContents();
#endif /* DEBUG */

private:
	const uint8_t ID = 0xE8;
    uint8_t channel;
    uint8_t toggleOption;
    uint8_t pitch;
    uint8_t velocity;
    uint8_t controlChangeNumber;
    uint8_t onValue;
    uint8_t offValue;

    uint16_t parameter;

	boolean toggle;
	boolean updated;
	uint8_t ledPin;

    Dispatcher* dispatcher;

};

#endif /* SRC_CONTROLLER_NOTECONTROLCHANGETOGGLE8BIT_H_ */
