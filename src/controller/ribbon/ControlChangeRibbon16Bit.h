/*
 * ControlChangeRibbon16Bit.h
 *
 *  Created on: Aug 25, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_RIBBON_CONTROLCHANGERIBBON16BIT_H_
#define SRC_CONTROLLER_RIBBON_CONTROLCHANGERIBBON16BIT_H_

#include "../common/controller.h"

class ControlChangeRibbon16Bit : public Controller {
public:
	ControlChangeRibbon16Bit();
	ControlChangeRibbon16Bit(const int* data);
	ControlChangeRibbon16Bit(const int* data, Dispatcher* dispatcher);

    ~ControlChangeRibbon16Bit();

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
    uint8_t parameter;

    boolean updated;

    Dispatcher* dispatcher;
};
#endif /* SRC_CONTROLLER_RIBBON_CONTROLCHANGERIBBON16BIT_H_ */
