/*
 * ControlChangeRibbon8Bit.cpp
 *
 *  Created on: Aug 25, 2017
 *      Author: mario
 */

#include "ControlChangeRibbon8Bit.h"

#include "../../command/ControlChange8BitCommand.h"

ControlChangeRibbon8Bit::ControlChangeRibbon8Bit() :
	channel(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	range(0),
	parameter(0),
	value7Bit(0),
	updated(false),
	dispatcher(NULL)
{
	// TODO Auto-generated constructor stub
}

ControlChangeRibbon8Bit::ControlChangeRibbon8Bit(const int* data) :
	channel(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	range(0),
	parameter(0),
	value7Bit(0),
	updated(false),
	dispatcher(NULL)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeRibbon8Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeRibbon8Bit while loading data");
	}
#endif /* DEBUG */
}

ControlChangeRibbon8Bit::ControlChangeRibbon8Bit(const int* data, Dispatcher* dispatcher) :
	channel(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	range(0),
	parameter(0),
	value7Bit(0),
	updated(false),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeRibbon8Bit successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in ControlChangeRibbon8Bit while loading data");
	}
#endif /* DEBUG */
}

ControlChangeRibbon8Bit::~ControlChangeRibbon8Bit() {
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


void ControlChangeRibbon8Bit::update(const uint32_t* time) {
	if(updated){
		uint8_t scalar = (value7Bit*range) >> 7;
		scalar += bottomValue;

		dispatcher->addCommand(new ControlChange8BitCommand(channel, controlChangeNumber, scalar));
		updated = false;
	}
}

void ControlChangeRibbon8Bit::setParameter(const uint16_t* value) {
	uint8_t tmp = *value >> 9;

	if(tmp != value7Bit){
		parameter = *value; //Raw ADC Value 16Bit
		value7Bit = tmp;
		updated = true;
	}
}

uint16_t ControlChangeRibbon8Bit::getParameter() {
	return parameter;
}

boolean ControlChangeRibbon8Bit::setConfiguration(const int* data) {
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

		range = topValue - bottomValue;

		result = true;
	}

	return result;
}

#ifdef DEBUG
    void ControlChangeRibbon8Bit::printContents(){
    	String result = String("Control Change Ribbon 8Bit \n");

    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"CC nr        : " + controlChangeNumber + "\n";
    	result += (String)"Top Value    : " + topValue + "\n";
    	result += (String)"Bottom Value : " + bottomValue + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */
