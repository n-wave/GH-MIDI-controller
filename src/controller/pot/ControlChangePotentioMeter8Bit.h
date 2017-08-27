/*
 * ControlChangePotentioMeter8Bit.h
 *
 *  Created on: Aug 24, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_POT_CONTROLCHANGEPOTENTIOMETER8BIT_H_
#define SRC_CONTROLLER_POT_CONTROLCHANGEPOTENTIOMETER8BIT_H_

#include "../controller.h"

class ControlChangePotentioMeter8Bit : public Controller{
public:
	ControlChangePotentioMeter8Bit();
	ControlChangePotentioMeter8Bit(const int* data);
	ControlChangePotentioMeter8Bit(const int* data, Dispatcher* dispatcher);

	~ControlChangePotentioMeter8Bit();

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
	    uint16_t parameter; //Raw data from ADC

	    uint8_t value7Bit; //converted 7Bit
	    boolean updated;

	    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_POT_CONTROLCHANGEPOTENTIOMETER8BIT_H_ */
