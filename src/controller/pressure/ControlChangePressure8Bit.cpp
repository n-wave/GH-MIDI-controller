/*
 * ControlChange8Bit.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#include "../../command/ControlChange8BitCommand.h"
#include "ControlChangePressure8Bit.h"

ControlChangePressure8Bit::ControlChangePressure8Bit() :
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

ControlChangePressure8Bit::ControlChangePressure8Bit(const int* data) :
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
		Serial.println("ControlChangePressure8Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangePressure8Bit while loading data");
	}
#endif /* DEBUG */
}

ControlChangePressure8Bit::ControlChangePressure8Bit(const int* data, Dispatcher* dispatcher) :
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
		Serial.println("ControlChangePressure8Bit successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in ControlChangePressure8Bit while loading data");
	}
#endif /* DEBUG */
}

ControlChangePressure8Bit::~ControlChangePressure8Bit() {
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


void ControlChangePressure8Bit::update(const uint32_t* time) {
	if(updated == true){
		uint8_t  scalar = 0;

		scalar = (value7Bit*range) >> 7; //Multiply with range and convert back to 7Bit (max amount = 2^14)
		scalar += bottomValue;			//Add offset i.e. the bottom value

		dispatcher->addCommand(new ControlChange8BitCommand(channel, controlChangeNumber, scalar));
		updated = false;
	}
}

void ControlChangePressure8Bit::setParameter(const uint16_t* value) {
	uint8_t tmp = *value >> 9;

	if(tmp != value7Bit){
		parameter = *value; //Raw ADC Value 16Bit
		value7Bit = tmp;
		updated = true;
	}
}

uint16_t ControlChangePressure8Bit::getParameter() {
	return parameter;
}

boolean ControlChangePressure8Bit::setConfiguration(const int* data) {
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
    void ControlChangePressure8Bit::printContents(){
    	String result = String("Control Change 8Bit \n");

    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"CC nr        : " + controlChangeNumber + "\n";
    	result += (String)"Top Value    : " + topValue + "\n";
    	result += (String)"Bottom Value : " + bottomValue + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */