/*
 * ControlChangeSwitch16Bit.h
 *
 *  Created on: Aug 24, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_SWITCH_CONTROLCHANGESWITCH16BIT_H_
#define SRC_CONTROLLER_SWITCH_CONTROLCHANGESWITCH16BIT_H_

#include "../common/controller.h"

class ControlChangeSwitch16Bit : public Controller{
public:
	ControlChangeSwitch16Bit();
	ControlChangeSwitch16Bit(const int* data);
	ControlChangeSwitch16Bit(const int* data, Dispatcher* dispatcher);

	~ControlChangeSwitch16Bit();

	void update(const uint32_t* time);

	void setParameter(const uint16_t* value);
	uint16_t getParameter();
	boolean setConfiguration(const int* data);

#ifdef DEBUG
	void printContents();
#endif /* DEBUG */

private:
	uint16_t convertBytesTo14Bit(uint8_t msb, uint8_t lsb);

	const uint8_t ID = 0xE5;

	uint8_t channel;
	uint8_t controlChangeNumberMSB;
	uint8_t controlChangeNumberLSB;

	uint8_t onValueMSB;
	uint8_t onValueLSB;
	uint8_t offValueMSB;
	uint8_t offValueLSB;

	uint8_t parameter;
	boolean updated;

	Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_SWITCH_CONTROLCHANGESWITCH16BIT_H_ */
