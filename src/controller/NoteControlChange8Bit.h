/*
 * NoteControlChange8Bit.h
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_NOTECONTROLCHANGE8BIT_H_
#define SRC_CONTROLLER_NOTECONTROLCHANGE8BIT_H_

#include "controller.h"
#include "../dispatcher/Dispatcher.h"

class NoteControlChange8Bit : public Controller {
public:
	NoteControlChange8Bit();
	NoteControlChange8Bit(const int* data);
	NoteControlChange8Bit(const int* data, Dispatcher* dispatcher);

	~NoteControlChange8Bit();

    void execute();
    void update(const uint32_t* time);

    void setParameter(const uint16_t* value);
    uint16_t getParameter();
    boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */

private:
    const uint8_t id = 0xE2;
    uint8_t channel;
    uint8_t pitch;
    uint8_t velocity;
    uint8_t velocityOption;
    uint8_t controlChangeNumber;
    uint8_t topValue;
    uint8_t bottomValue;

    uint16_t parameter;
    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_NOTECONTROLCHANGE8BIT_H_ */
