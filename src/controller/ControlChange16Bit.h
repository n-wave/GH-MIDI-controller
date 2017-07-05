/*
 * ControlChange16Bit.h
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_CONTROLCHANGE16BIT_H_
#define SRC_CONTROLLER_CONTROLCHANGE16BIT_H_

#include "controller.h"

class ControlChange16Bit : public Controller {
public:
	ControlChange16Bit();
    ~ControlChange16Bit();

    void execute();
    void update(const uint32_t* time);

    void setParameter(const uint16_t* value);
    uint16_t getParameter();
    void setConfiguration(const int* data);
private:
};

#endif /* SRC_CONTROLLER_CONTROLCHANGE16BIT_H_ */
