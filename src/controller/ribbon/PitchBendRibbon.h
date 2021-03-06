/*
 * PitchBend.h
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_PITCHBEND_H_
#define SRC_CONTROLLER_PITCHBEND_H_

#include "../common/controller.h"


class PitchBendRibbon: public Controller {
public:
	PitchBendRibbon();
	PitchBendRibbon(const int* data);
	PitchBendRibbon(const int* data, Dispatcher* dispatcher);
    ~PitchBendRibbon();

    void update();

    void setParameter(const uint16_t* value);;
    boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */

private:
    const uint8_t ID = 0xE3;
    uint8_t channel;
    uint16_t parameter;
    boolean updated;
    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_PITCHBEND_H_ */
