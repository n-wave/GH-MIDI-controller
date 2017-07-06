/*
 * NoteControlChange16Bit.h
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_NOTECONTROLCHANGE16BIT_H_
#define SRC_CONTROLLER_NOTECONTROLCHANGE16BIT_H_

#include "controller.h"

class NoteControlChange16Bit: public Controller {
public:
	NoteControlChange16Bit();
    ~NoteControlChange16Bit();

    void execute();
    void update(const uint32_t* time);

    void setParameter(const uint16_t* value);
    uint16_t getParameter();
    boolean setConfiguration(const int* data);

#ifdef DEBUG
    String toString();
#endif /* DEBUG */

private:
    uint16_t convertBytesTo14Bit(uint8_t msb, uint8_t lsb);

    const uint8_t id = 0xE2;
    uint8_t channel;
    uint8_t pitch;
    uint8_t velocity;
    uint8_t velocityOption;
    uint8_t controlChangeNumberMSB;
    uint8_t controlChangeNumberLSB;
    uint16_t topValue;
    uint16_t bottomValue;

    uint16_t parameter;
};

#endif /* SRC_CONTROLLER_NOTECONTROLCHANGE16BIT_H_ */
