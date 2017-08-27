/*
 * ControlChange8Bit.h
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_CONTROLCHANGE8BIT_H_
#define SRC_CONTROLLER_CONTROLCHANGE8BIT_H_

#include "../controller.h"

class ControlChangePressure8Bit : public Controller {
public:
	ControlChangePressure8Bit();
	ControlChangePressure8Bit(const int* data);
	ControlChangePressure8Bit(const int* data, Dispatcher* dispatcher);


	~ControlChangePressure8Bit();

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
    uint8_t range;
    uint16_t parameter;
    uint8_t value7Bit;
    boolean updated;

    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_CONTROLCHANGE8BIT_H_ */
