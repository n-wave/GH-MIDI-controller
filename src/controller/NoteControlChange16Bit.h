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
    void setConfiguration(const int* data);
private:
};

#endif /* SRC_CONTROLLER_NOTECONTROLCHANGE16BIT_H_ */
