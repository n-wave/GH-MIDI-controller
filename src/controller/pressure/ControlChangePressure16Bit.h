/*
 * ControlChange16Bit.h
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_CONTROLCHANGE16BIT_H_
#define SRC_CONTROLLER_CONTROLCHANGE16BIT_H_

#include "../common/controller.h"

class ControlChangePressure16Bit : public Controller {
public:
	ControlChangePressure16Bit();
	ControlChangePressure16Bit(const int* data);
	ControlChangePressure16Bit(const int* data, Dispatcher* dispatcher);

    ~ControlChangePressure16Bit();

    void update();

    void setParameter(const uint16_t* value);

    boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */

private:

    const uint8_t ID = 0xE5;

    uint8_t channel;
    uint8_t controlChangeNumberMSB;
    uint8_t controlChangeNumberLSB;
    uint16_t topValue;
    uint16_t bottomValue;

    uint16_t range;
    uint16_t parameter;

    boolean updated;

    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_CONTROLCHANGE16BIT_H_ */
