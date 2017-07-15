/*
 * PitchBend.h
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_PITCHBEND_H_
#define SRC_CONTROLLER_PITCHBEND_H_

#include "controller.h"
#include "../dispatcher/Dispatcher.h"

class PitchBend: public Controller {
public:
	PitchBend();
	PitchBend(const int* data);
	PitchBend(const int* data, Dispatcher* dispatcher);
    ~PitchBend();

    void execute();
    void update(const uint32_t* time);

    void setParameter(const uint16_t* value);
    uint16_t getParameter();
    boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */

private:
    const uint8_t id = 0xE3;
    uint8_t channel;

    uint16_t parameter;
    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_PITCHBEND_H_ */
