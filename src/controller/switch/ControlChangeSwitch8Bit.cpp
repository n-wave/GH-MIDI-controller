/*
 * ControlChangeSwitch8Bit.cpp
 *
 *  Created on: Aug 24, 2017
 *      Author: mario
 */

#include "ControlChangeSwitch8Bit.h"

#include "../../command/ControlChange8BitCommand.h"

ControlChangeSwitch8Bit::ControlChangeSwitch8Bit() :
	channel(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	updated(false),
	dispatcher(NULL)
{
	// TODO Auto-generated constructor stub
}

ControlChangeSwitch8Bit::ControlChangeSwitch8Bit(const int* data) :
	channel(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	updated(false),
	dispatcher(NULL)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeSwitch8Bit successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in ControlChangeSwitch8Bit while loading data");
	}
#endif /* DEBUG */
}

ControlChangeSwitch8Bit::ControlChangeSwitch8Bit(const int* data, Dispatcher* dispatcher) :
	channel(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	updated(false),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeSwitch8Bit successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in ControlChangeSwitch8Bit while loading data");
	}
#endif /* DEBUG */
}

ControlChangeSwitch8Bit::~ControlChangeSwitch8Bit() {
	dispatcher = NULL;
}


/* ControlChangeBit::update()
 *
 * Calculate values.
 *
 * add new PitchBendNote Command
 *
 * arg 1: uint8_t channel
 * arg 2: uint8_t ccNumber
 * arg 3: uint8_t ccValue
 *
 */


void ControlChangeSwitch8Bit::update(const uint32_t* time) {
	if(updated){
		if(parameter > 0){
			dispatcher->addCommand(new ControlChange8BitCommand(channel,
																controlChangeNumber,
																topValue));
		} else {
			dispatcher->addCommand(new ControlChange8BitCommand(channel,
																controlChangeNumber,
																bottomValue));
		}
		updated = false;
	}
}

void ControlChangeSwitch8Bit::setParameter(const uint16_t* value) {
	if(parameter != *value){
		parameter = *value;
		updated = true;
	}
}

uint16_t ControlChangeSwitch8Bit::getParameter() {
	return parameter;
}

boolean ControlChangeSwitch8Bit::setConfiguration(const int* data) {
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		data[3] == 0x00 &&
		data[7] == 0xFF
	  )
	{
		channel = data[2];
		controlChangeNumber = data[4];
		topValue = data[5];
		bottomValue = data[6];

		result = true;
	}

	return result;
}

#ifdef DEBUG
    void ControlChangeSwitch8Bit::printContents(){
    	String result = String("Control Change 8Bit \n");

    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"CC nr        : " + controlChangeNumber + "\n";
    	result += (String)"Top Value    : " + topValue + "\n";
    	result += (String)"Bottom Value : " + bottomValue + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */
