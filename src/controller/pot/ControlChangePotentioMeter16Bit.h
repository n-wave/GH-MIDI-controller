/*
 * ControlChangePotentioMeter16Bit.h
 *
 *  Created on: Aug 24, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_POT_CONTROLCHANGEPOTENTIOMETER16BIT_H_
#define SRC_CONTROLLER_POT_CONTROLCHANGEPOTENTIOMETER16BIT_H_

#include "../common/controller.h"

class ControlChangePotentioMeter16Bit: public Controller {
public:
	ControlChangePotentioMeter16Bit();
	ControlChangePotentioMeter16Bit(const int* data);
	ControlChangePotentioMeter16Bit(const int* data, Dispatcher* dispatcher);

    ~ControlChangePotentioMeter16Bit();

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

#endif /* SRC_CONTROLLER_POT_CONTROLCHANGEPOTENTIOMETER16BIT_H_ */
