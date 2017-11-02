/*
 * NoteControlChange16Bit.h
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_NOTECONTROLCHANGE16BIT_H_
#define SRC_CONTROLLER_NOTECONTROLCHANGE16BIT_H_

#include "../common/controller.h"

class NoteControlChangePressure16Bit: public Controller {
public:
	NoteControlChangePressure16Bit();
	NoteControlChangePressure16Bit(const int* data);
	NoteControlChangePressure16Bit(const int* data, Dispatcher* dispatcher);
    ~NoteControlChangePressure16Bit();

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
    uint8_t controlChangeNumberMSB;
    uint8_t controlChangeNumberLSB;

    uint16_t topValue;
    uint16_t bottomValue;
    uint16_t range;
    uint16_t parameter;

    boolean updated;
    boolean sendNote;

    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_NOTECONTROLCHANGE16BIT_H_ */
