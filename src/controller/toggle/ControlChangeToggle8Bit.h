/*
 * ControlChangeToggle8Bit.h
 *
 *  Created on: Aug 22, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_CONTROLCHANGETOGGLE8BIT_H_
#define SRC_CONTROLLER_CONTROLCHANGETOGGLE8BIT_H_

#include "../common/controller.h"

class ControlChangeToggle8Bit: public Controller {
public:
	ControlChangeToggle8Bit();
	ControlChangeToggle8Bit(const int* data);
	ControlChangeToggle8Bit(const int* data, Dispatcher* dispatcher);
	ControlChangeToggle8Bit(const int* data, uint8_t ledPin, Dispatcher* dispatcher);

	~ControlChangeToggle8Bit();

    void update();
	void setParameter(const uint16_t* value);
	boolean setConfiguration(const int* data);

#ifdef DEBUG
	void printContents();
#endif /* DEBUG */

private:
    const uint8_t ID = 0xE9;
    uint8_t toggleOption;
    uint8_t channel;
    uint8_t controlChangeNumber;
    uint8_t onValue;
    uint8_t offValue;

    uint16_t parameter;

    boolean toggle;
    boolean updated;
    uint8_t ledPin;

    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_CONTROLCHANGETOGGLE8BIT_H_ */
