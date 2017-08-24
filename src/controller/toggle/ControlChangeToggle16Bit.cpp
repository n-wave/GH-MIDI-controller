/*
 * ControlChangeToggle16Bit.cpp
 *
 *  Created on: Aug 23, 2017
 *      Author: mario
 */

#include "ControlChangeToggle16Bit.h"
#include "../../command/ControlChange16BitCommand.h"

ControlChangeToggle16Bit::ControlChangeToggle16Bit() :
	toggleOption(0),
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	enabled(false),
	ledPin(0),
	dispatcher(NULL)
{
}

ControlChangeToggle16Bit::ControlChangeToggle16Bit(const int* data)  :
	toggleOption(0),
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
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
		Serial.println("ControlChange16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeToggle16Bit::ControlChangeToggle16Bit(const int*) while loading data");
	}
#endif /* DEBUG */
}

ControlChangeToggle16Bit::ControlChangeToggle16Bit(const int* data, Dispatcher* dispatcher)  :
	toggleOption(0),
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
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
		Serial.println("ControlChange16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeToggle16Bit::ControlChangeToggle16Bit(const int*, Dispatcher*) while loading data");
	}
#endif /* DEBUG */
}

ControlChangeToggle16Bit::ControlChangeToggle16Bit(const int* data, uint8_t ledPin, Dispatcher* dispatcher)  :
	toggleOption(0),
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	enabled(false),
	ledPin(ledPin),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChange16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeToggle16Bit::ControlChangeToggle16Bit(const int*, uint8_t ,Dispatcher*) while loading data");
	}
#endif /* DEBUG */
}

ControlChangeToggle16Bit::~ControlChangeToggle16Bit()
{
	dispatcher = NULL;
}

void ControlChangeToggle16Bit::update(const uint32_t* time)

	/* ControlChangeFade8Bit::update()
	 *
	 * Calculate values.
	 *
	 * add new ControlChange16BitCommand
	 *
	 * arg 1: uint8_t channel
	 * arg 2: uint8_t ccNumberMSB
	 * arg 3: uint8_t ccValueMSB
	 * arg 4: uint8_t ccNumerLSB
	 * arg 5: uint8_t ccValueLSB
	 * */
{
	dispatcher->addCommand(new ControlChange16BitCommand(1, 8, 120, 40, 4));
}

void ControlChangeToggle16Bit::setParameter(const uint16_t* value){
	parameter = *value;
}

uint16_t ControlChangeToggle16Bit::getParameter(){
	return parameter;
}

boolean ControlChangeToggle16Bit:: setConfiguration(const int* data) {
		boolean result = false;

		if(
			data[0] == 0xF0 &&
			data[1] == ID &&
			data[4] == 0x00 &&
			data[10] == 0xFF
		  )
		{
			toggleOption = data[2];
			channel = data[3];
			controlChangeNumberMSB = data[5];
			controlChangeNumberLSB = controlChangeNumberMSB + 32;
			topValue = this->convertBytesTo14Bit(data[6], data[7]);
			bottomValue = this->convertBytesTo14Bit(data[8], data[9]);

			result = true;
		}

		return result;
	}

uint16_t ControlChangeToggle16Bit::convertBytesTo14Bit(uint8_t msb, uint8_t lsb){
	uint16_t result = 0;
	uint16_t MSB = (msb & 0x7F) << 7;
	uint16_t LSB = lsb & 0x7F;

	result = MSB | LSB;

	return result;
}

void ControlChangeToggle16Bit::printContents(){
	String result = String("Control Change Toggle 16Bit \n");

	result += (String)"Toggle Option: " + toggleOption + "\n";
	result += (String)"MIDI Channel : " + channel + "\n";
	result += (String)"CC nr MSB    : " + controlChangeNumberMSB + "\n";
	result += (String)"CC nr LSB    : " + controlChangeNumberMSB + "\n";
	result += (String)"Top Value    : " + topValue + "\n";
	result += (String)"Bottom Value : " + bottomValue + "\n";
	result += (String)"Parameter    : " + parameter + "\n";

	result += (String)"Enabled      : " + enabled + "\n";
	result += (String)"LedPin       : " + ledPin + "\n";
	Serial.println(result);
}
