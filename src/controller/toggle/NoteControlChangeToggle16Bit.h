/*
 * NoteControlChangeToggle16Bit.h
 *
 *  Created on: Aug 22, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_NOTECONTROLCHANGETOGGLE16BIT_H_
#define SRC_CONTROLLER_NOTECONTROLCHANGETOGGLE16BIT_H_

#include "../common/controller.h"

class NoteControlChangeToggle16Bit: public Controller {
public:
	NoteControlChangeToggle16Bit();
	NoteControlChangeToggle16Bit(const int* data);
	NoteControlChangeToggle16Bit(const int* data, Dispatcher* dispatcher);
	NoteControlChangeToggle16Bit(const int* data, uint8_t ledPin, Dispatcher* dispatcher);

	~NoteControlChangeToggle16Bit();

	void update();

	void setParameter(const uint16_t* value);
	boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */

private:

    const uint8_t ID = 0xE8;

    uint8_t toggleOption;
    uint8_t channel;
    uint8_t pitch;
    uint8_t velocity;
    uint8_t controlChangeNumberMSB;
    uint8_t controlChangeNumberLSB;

    uint8_t onValueMSB;
    uint8_t onValueLSB;

    uint8_t offValueMSB;
    uint8_t offValueLSB;

    uint16_t parameter;

    boolean toggle;
    boolean updated;

    uint8_t ledPin;

    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_NOTECONTROLCHANGETOGGLE16BIT_H_ */
