/*
 * PitchBend.h
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_PITCHBEND_H_
#define SRC_CONTROLLER_PITCHBEND_H_

#include "controller.h"

class PitchBend: public Controller {
public:
	PitchBend();
    ~PitchBend();

    void execute();
    void update(const uint32_t* time);

    void setParameter(const uint16_t* value);
    uint16_t getParameter();
    boolean setConfiguration(const int* data);

#ifdef DEBUG
    String toString();
#endif /* DEBUG */

private:
    const uint8_t id = 0xE3;
    uint8_t channel;

    uint16_t parameter;
};

#endif /* SRC_CONTROLLER_PITCHBEND_H_ */
