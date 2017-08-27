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
	onValueMSB(0),
	onValueLSB(0),
	offValueMSB(0),
	offValueLSB(0),
	parameter(0),
	updated(false),
	dispatcher(NULL)
{
}

ControlChangeSwitch16Bit::ControlChangeSwitch16Bit(const int* data) :
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	onValueMSB(0),
	onValueLSB(0),
	offValueMSB(0),
	offValueLSB(0),
	parameter(0),
	updated(false),
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
	onValueMSB(0),
	onValueLSB(0),
	offValueMSB(0),
	offValueLSB(0),
	parameter(0),
	updated(false),
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
 * arg 2: uint8_t controlChangeNumberMSB
 * arg 3: uint8_t controlChangeValueMSB
 * arg 4: uint8_t controlChangeNumberLSB
 * arg 5: uint8_t controlChangeValueLSB
 */

void ControlChangeSwitch16Bit::update(const uint32_t* time) {
	if(updated){
		if(parameter > 0){
			dispatcher->addCommand(new ControlChange16BitCommand(channel,
																 controlChangeNumberMSB,
																 onValueMSB,
																 controlChangeNumberLSB,
																 onValueLSB));
		} else {
			dispatcher->addCommand(new ControlChange16BitCommand(channel,
																 controlChangeNumberMSB,
																 offValueMSB,
																 controlChangeNumberLSB,
																 offValueLSB));
		}
		updated = false;
	}
}

void ControlChangeSwitch16Bit::setParameter(const uint16_t* value) {
	if(parameter != *value){
		parameter = *value;
		updated = true;
	}
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

		onValueMSB = data[5];
		onValueLSB = data[6];
		offValueMSB = data[7];
		offValueLSB = data[8];

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

    	uint16_t onValue = convertBytesTo14Bit(onValueMSB, onValueLSB);
    	uint16_t offValue = convertBytesTo14Bit(offValueMSB, offValueLSB);


    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"CC nr MSB    : " + controlChangeNumberMSB + "\n";
    	result += (String)"CC nr LSB    : " + controlChangeNumberLSB + "\n";
    	result += (String)"On Value     : " + onValue + "\n";
    	result += (String)"On Value MSB : " + onValueMSB + "\n";
    	result += (String)"On Value LSB : " + onValueLSB + "\n";
    	result += (String)"Off Value    : " + offValue + "\n";
    	result += (String)"Off Value MSB: " + offValueMSB + "\n";
    	result += (String)"Off Value LSB: " + offValueLSB + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */

