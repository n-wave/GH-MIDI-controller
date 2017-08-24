/*
 * ControlChangeToggle8Bit.cpp
 *
 *  Created on: Aug 22, 2017
 *      Author: mario
 */

#include "ControlChangeToggle8Bit.h"
#include "../../command/ControlChange8BitCommand.h"

ControlChangeToggle8Bit::ControlChangeToggle8Bit() :
    toggleOption(0),
	channel(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	enabled(false),
	ledPin(0),
	dispatcher(NULL)

{
	// TODO Auto-generated constructor stub

}

ControlChangeToggle8Bit::ControlChangeToggle8Bit(const int* data) :
	toggleOption(0),
	channel(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	enabled(false),
	ledPin(0),
	dispatcher(NULL)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeToggle8Bit successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in ControlChangeToggle8Bit::ControlChangeToggle8Bit(const int* data) while loading data");
	}
#endif /* DEBUG */
}

ControlChangeToggle8Bit::ControlChangeToggle8Bit(const int* data, Dispatcher* dispatcher) :
	toggleOption(0),
	channel(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	enabled(false),
	ledPin(0),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeToggle8Bit successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in ControlChangeToggle8Bit::ControlChangeToggle8Bit(const int* data, Dispatcher* dispatcher) while loading data");
	}
#endif /* DEBUG */
}

ControlChangeToggle8Bit::ControlChangeToggle8Bit(const int* data, uint8_t ledPin, Dispatcher* dispatcher) :
	toggleOption(0),
	channel(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	enabled(false),
	ledPin(0),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeToggle8Bit successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in ControlChangeToggle8Bit::ControlChangeToggle8Bit(const int* data, uint8_t ledPin, Dispatcher* dispatcher) while loading data");
	}
#endif /* DEBUG */
}

ControlChangeToggle8Bit::~ControlChangeToggle8Bit()
{
	dispatcher = NULL;
}


void ControlChangeToggle8Bit::update(const uint32_t* time){

}

void ControlChangeToggle8Bit::setParameter(const uint16_t* value){
	parameter = *value;
}

uint16_t ControlChangeToggle8Bit::getParameter(){
	return parameter;
}

boolean ControlChangeToggle8Bit::setConfiguration(const int* data){
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		data[4] == 0x00 &&
		data[8] == 0xFF
	  )
	{
		toggleOption = data[2];
		channel = data[3];
		controlChangeNumber = data[5];
		topValue = data[6];
		bottomValue = data[7];

		result = true;
	}

	return result;
}

#ifdef DEBUG
    void ControlChangeToggle8Bit::printContents(){
    	String result = String("Control Change Toggle 8Bit \n");

    	result += (String)"Toggle Option: " + toggleOption + "\n";
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"CC nr        : " + controlChangeNumber + "\n";
    	result += (String)"Top Value    : " + topValue + "\n";
    	result += (String)"Bottom Value : " + bottomValue + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";

    	result += (String)"Enabled      : " + enabled + "\n";
    	result += (String)"LedPin       : " + ledPin + "\n";
    	Serial.println(result);
    }
#endif /* DEBUG */

