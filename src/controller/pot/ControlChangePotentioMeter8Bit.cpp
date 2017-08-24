/*
 * ControlChangePotentioMeter8Bit.cpp
 *
 *  Created on: Aug 24, 2017
 *      Author: mario
 */

#include "ControlChangePotentioMeter8Bit.h"
#include "../../command/ControlChange8BitCommand.h"

ControlChangePotentioMeter8Bit::ControlChangePotentioMeter8Bit() :
	channel(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	dispatcher(NULL)
{
	// TODO Auto-generated constructor stub
}

ControlChangePotentioMeter8Bit::ControlChangePotentioMeter8Bit(const int* data) :
	channel(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	dispatcher(NULL)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangePotentioMeter8Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangePotentioMeter8Bit while loading data");
	}
#endif /* DEBUG */
}

ControlChangePotentioMeter8Bit::ControlChangePotentioMeter8Bit(const int* data, Dispatcher* dispatcher) :
	channel(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangePotentioMeter8Bit successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in ControlChangePotentioMeter8Bit while loading data");
	}
#endif /* DEBUG */
}

ControlChangePotentioMeter8Bit::~ControlChangePotentioMeter8Bit() {
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


void ControlChangePotentioMeter8Bit::update(const uint32_t* time) {
	dispatcher->addCommand(new ControlChange8BitCommand(1, 12, 27));
}

void ControlChangePotentioMeter8Bit::setParameter(const uint16_t* value) {
	parameter = *value;
}

uint16_t ControlChangePotentioMeter8Bit::getParameter() {
	return parameter;
}

boolean ControlChangePotentioMeter8Bit::setConfiguration(const int* data) {
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
    void ControlChangePotentioMeter8Bit::printContents(){
    	String result = String("Control Change 8Bit \n");

    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"CC nr        : " + controlChangeNumber + "\n";
    	result += (String)"Top Value    : " + topValue + "\n";
    	result += (String)"Bottom Value : " + bottomValue + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */