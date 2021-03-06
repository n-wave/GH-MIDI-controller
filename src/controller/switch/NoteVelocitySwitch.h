/*
 * NoteVelocitySwitch.h
 *
 *  Created on: Aug 24, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_SWITCH_NOTEVELOCITYSWITCH_H_
#define SRC_CONTROLLER_SWITCH_NOTEVELOCITYSWITCH_H_

#include "../common/controller.h"

class NoteVelocitySwitch: public Controller {
public:
	NoteVelocitySwitch();
	NoteVelocitySwitch(const int* data);
	NoteVelocitySwitch(const int* data, Dispatcher* dispatcher);

	~NoteVelocitySwitch();

    void update();

    void setParameter(const uint16_t* value);
    boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */


private:
    const uint8_t ID = 0xE1;
    uint8_t channel;
    uint8_t pitch;
    uint8_t velocity;

    uint8_t parameter;
    boolean updated;

    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_SWITCH_NOTEVELOCITYSWITCH_H_ */
