/*
 * ControlChangeRibbon8Bit.h
 *
 *  Created on: Aug 25, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_RIBBON_CONTROLCHANGERIBBON8BIT_H_
#define SRC_CONTROLLER_RIBBON_CONTROLCHANGERIBBON8BIT_H_

#include "../controller.h"

class ControlChangeRibbon8Bit: public Controller {
public:
	ControlChangeRibbon8Bit();
	ControlChangeRibbon8Bit(const int* data);
	ControlChangeRibbon8Bit(const int* data, Dispatcher* dispatcher);


	~ControlChangeRibbon8Bit();

    void update(const uint32_t* time);

    void setParameter(const uint16_t* value);
    uint16_t getParameter();
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

    uint16_t parameter;

    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_RIBBON_CONTROLCHANGERIBBON8BIT_H_ */
