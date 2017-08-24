/*
 * ControlChangeToggle16Bit.h
 *
 *  Created on: Aug 23, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_CONTROLCHANGETOGGLE16BIT_H_
#define SRC_CONTROLLER_CONTROLCHANGETOGGLE16BIT_H_

#include "../controller.h"

class ControlChangeToggle16Bit: public Controller {
public:
	ControlChangeToggle16Bit();
	ControlChangeToggle16Bit(const int* data);
	ControlChangeToggle16Bit(const int* data, Dispatcher* dispatcher);
	ControlChangeToggle16Bit(const int* data, uint8_t ledPin, Dispatcher* dispatcher);

	~ControlChangeToggle16Bit();

	void update(const uint32_t* time);

	void setParameter(const uint16_t* value);
	uint16_t getParameter();

	boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */

private:
    uint16_t convertBytesTo14Bit(uint8_t msb, uint8_t lsb);

    const uint16_t ID = 0xE9;

    uint8_t toggleOption;
    uint8_t channel;
    uint8_t controlChangeNumberMSB;
    uint8_t controlChangeNumberLSB;
    uint16_t topValue;
    uint16_t bottomValue;

    uint16_t parameter;

    boolean enabled;
    uint8_t ledPin;

    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_CONTROLCHANGETOGGLE16BIT_H_ */