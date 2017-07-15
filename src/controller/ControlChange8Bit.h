/*
 * ControlChange8Bit.h
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_CONTROLCHANGE8BIT_H_
#define SRC_CONTROLLER_CONTROLCHANGE8BIT_H_

#include "controller.h"
#include "../dispatcher/Dispatcher.h"

class ControlChange8Bit : public Controller {
public:
	ControlChange8Bit();
	ControlChange8Bit(const int* data);
	ControlChange8Bit(const int* data, Dispatcher* dispatcher);


	virtual ~ControlChange8Bit();

    void execute();
    void update(const uint32_t* time);

    void setParameter(const uint16_t* value);
    uint16_t getParameter();
    boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */

private:
    const uint8_t id = 0xE5;
    uint8_t channel;
    uint8_t controlChangeNumber;
    uint8_t topValue;
    uint8_t bottomValue;

    uint16_t parameter;

    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_CONTROLCHANGE8BIT_H_ */
