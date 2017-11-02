/*
 * ControlChangeSwitch8Bit.h
 *
 *  Created on: Aug 24, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_SWITCH_CONTROLCHANGESWITCH8BIT_H_
#define SRC_CONTROLLER_SWITCH_CONTROLCHANGESWITCH8BIT_H_

#include "../common/controller.h"

class ControlChangeSwitch8Bit: public Controller {
public:
	ControlChangeSwitch8Bit();
	ControlChangeSwitch8Bit(const int* data);
	ControlChangeSwitch8Bit(const int* data, Dispatcher* dispatcher);

	~ControlChangeSwitch8Bit();

    void update();

    void setParameter(const uint16_t* value);
    boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */

private:
    const uint8_t ID = 0xE5;
    uint8_t channel;
    uint8_t controlChangeNumber;
    uint8_t topValue;
    uint8_t bottomValue;

    uint8_t parameter;
    boolean updated;

    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_SWITCH_CONTROLCHANGESWITCH8BIT_H_ */
