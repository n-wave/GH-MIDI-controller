/*
 * NoteControlChange8Bit.h
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_NOTECONTROLCHANGE8BIT_H_
#define SRC_CONTROLLER_NOTECONTROLCHANGE8BIT_H_

#include "../common/controller.h"

class NoteControlChangePressure8Bit : public Controller {
public:
	NoteControlChangePressure8Bit();
	NoteControlChangePressure8Bit(const int* data);
	NoteControlChangePressure8Bit(const int* data, Dispatcher* dispatcher);

	~NoteControlChangePressure8Bit();

    void update();

    void setParameter(const uint16_t* value);
    boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */

private:
    const uint8_t ID = 0xE2;
    uint8_t channel;
    uint8_t pitch;
    uint8_t velocity;
    uint8_t velocityOption;
    uint8_t controlChangeNumber;
    uint8_t topValue;
    uint8_t bottomValue;

    uint8_t parameter;

    uint8_t range;
    boolean updated;
    boolean sendNote;

    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_NOTECONTROLCHANGE8BIT_H_ */
