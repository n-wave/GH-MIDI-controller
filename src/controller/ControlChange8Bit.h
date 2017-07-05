/*
 * ControlChange8Bit.h
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_CONTROLCHANGE8BIT_H_
#define SRC_CONTROLLER_CONTROLCHANGE8BIT_H_

#include "controller.h"

class ControlChange8Bit : public Controller {
public:
	ControlChange8Bit();
	virtual ~ControlChange8Bit();

    void execute();
    void update(const uint32_t* time);

    void setParameter(const uint16_t* value);
    uint16_t getParameter();
    void setConfiguration(const int* data);
private:
};

#endif /* SRC_CONTROLLER_CONTROLCHANGE8BIT_H_ */
