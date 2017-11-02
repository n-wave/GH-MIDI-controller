/*
 * ControlChangeToggle16Bit.h
 *
 *  Created on: Aug 23, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_CONTROLCHANGETOGGLE16BIT_H_
#define SRC_CONTROLLER_CONTROLCHANGETOGGLE16BIT_H_

#include "../common/controller.h"

class ControlChangeToggle16Bit: public Controller {
public:
	ControlChangeToggle16Bit();
	ControlChangeToggle16Bit(const int* data);
	ControlChangeToggle16Bit(const int* data, Dispatcher* dispatcher);
	ControlChangeToggle16Bit(const int* data, uint8_t ledPin, Dispatcher* dispatcher);

	~ControlChangeToggle16Bit();

	void update();
	void setParameter(const uint16_t* value);
	boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */

private:
    const uint16_t ID = 0xE9;

    uint8_t toggleOption;
    uint8_t channel;
    uint8_t controlChangeNumberMSB;
    uint8_t controlChangeNumberLSB;
    uint8_t onValueMSB;
    uint8_t onValueLSB;
    uint8_t offValueMSB;
    uint8_t offValueLSB;

    uint16_t parameter;

    boolean toggle;
    boolean updated;
    uint8_t ledPin;

    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_CONTROLCHANGETOGGLE16BIT_H_ */
