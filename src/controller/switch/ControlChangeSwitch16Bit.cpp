/*
 * ControlChangeSwitch16Bit.cpp
 *
 *  Created on: Aug 24, 2017
 *      Author: mario
 */

#include "ControlChangeSwitch16Bit.h"

#include "../../command/ControlChange16BitCommand.h"

ControlChangeSwitch16Bit::ControlChangeSwitch16Bit() :
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	dispatcher(NULL)
{
}

ControlChangeSwitch16Bit::ControlChangeSwitch16Bit(const int* data) :
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	dispatcher(NULL)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeSwitch16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeSwitch16Bit while loading data");
	}
#endif /* DEBUG */
}

ControlChangeSwitch16Bit::ControlChangeSwitch16Bit(const int* data, Dispatcher* dispatcher) :
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeSwitch16Bit successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in ControlChangeSwitch16Bit while loading data");
	}
#endif /* DEBUG */

}

ControlChangeSwitch16Bit::~ControlChangeSwitch16Bit() {
	dispatcher = NULL;
}


/* ControlChangeFade8Bit::update()
 *
 * Calculate values.
 *
 * add new ControlChangeSwitch16BitCommand
 *
 * arg 1: uint8_t channel
 * arg 2: uint8_t ccNumberMSB
 * arg 3: uint8_t ccValueMSB
 * arg 4: uint8_t ccNumerLSB
 * arg 5: uint8_t ccValueLSB
 */

void ControlChangeSwitch16Bit::update(const uint32_t* time) {
	dispatcher->addCommand(new ControlChange16BitCommand(1, 8, 120, 40, 4));
}

void ControlChangeSwitch16Bit::setParameter(const uint16_t* value) {
	parameter = *value;
}

uint16_t ControlChangeSwitch16Bit::getParameter() {
	return parameter;
}

boolean ControlChangeSwitch16Bit:: setConfiguration(const int* data) {
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		data[3] == 0x01 &&
		data[9] == 0xFF
	  )
	{
		channel = data[2];
		controlChangeNumberMSB = data[4];
		controlChangeNumberLSB = controlChangeNumberMSB + 32;

		topValue = this->convertBytesTo14Bit(data[5], data[6]);
		bottomValue = this->convertBytesTo14Bit(data[7], data[8]);

		result = true;
	}
	return result;
}

/**
 *  Convert Supplied MSB and LSB values to the
 *  14Bit value they represent, store and return
 *  the result in a 16Bit value
 */

uint16_t ControlChangeSwitch16Bit::convertBytesTo14Bit(uint8_t msb, uint8_t lsb){
	uint16_t result = 0;
	uint16_t MSB = (msb & 0x7F) << 7;
	uint16_t LSB = lsb & 0x7F;

	result = MSB | LSB;

	return result;
}

#ifdef DEBUG
    void ControlChangeSwitch16Bit::printContents(){
    	String result = String("Control Change Switch 16Bit \n");

    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"CC nr MSB    : " + controlChangeNumberMSB + "\n";
    	result += (String)"CC nr LSB    : " + controlChangeNumberLSB + "\n";
    	result += (String)"Top Value    : " + topValue + "\n";
    	result += (String)"Bottom Value : " + bottomValue + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */

