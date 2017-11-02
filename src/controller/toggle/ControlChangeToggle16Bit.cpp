/*
 * ControlChangeToggle16Bit.cpp
 *
 *  Created on: Aug 23, 2017
 *      Author: mario
 */

#include "ControlChangeToggle16Bit.h"
#include "../../command/ControlChange16BitCommand.h"
#include "../../ghmc/ghmc.h"

using ghmc::byte::convertBytesTo14Bit;

ControlChangeToggle16Bit::ControlChangeToggle16Bit() :
	toggleOption(0),
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	onValueMSB(0),
	onValueLSB(0),
	offValueMSB(0),
	offValueLSB(0),
	parameter(0),
	toggle(false),
	updated(false),
	ledPin(0),
	dispatcher(NULL)
{
}

ControlChangeToggle16Bit::ControlChangeToggle16Bit(const int* data)  :
	toggleOption(0),
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	onValueMSB(0),
	onValueLSB(0),
	offValueMSB(0),
	offValueLSB(0),
	parameter(0),
	toggle(false),
	updated(false),
	ledPin(0),
	dispatcher(NULL)
{
#ifndef DEBUG
	this->setConfiguration(data);
#endif

#ifdef DEBUG
	boolean success = this->setConfiguration(data);

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
	onValueMSB(0),
	onValueLSB(0),
	offValueMSB(0),
	offValueLSB(0),
	parameter(0),
	toggle(false),
	updated(false),
	ledPin(0),
	dispatcher(dispatcher)
{
#ifndef DEBUG
	this->setConfiguration(data);
#endif

#ifdef DEBUG
	boolean success = this->setConfiguration(data);

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
	onValueMSB(0),
	onValueLSB(0),
	offValueMSB(0),
	offValueLSB(0),
	parameter(0),
	toggle(false),
	updated(false),
	ledPin(ledPin),
	dispatcher(dispatcher)
{
#ifndef DEBUG
	this->setConfiguration(data);
#endif
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);


#ifdef DEBUG
	boolean success = this->setConfiguration(data);

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

void ControlChangeToggle16Bit::update()
{
	if(updated){
		if(toggleOption == 1){
			if(toggle){
				dispatcher->addCommand(new ControlChange16BitCommand(channel,
																	 controlChangeNumberMSB,
																	 onValueMSB,
																	 controlChangeNumberLSB,
																	 onValueLSB
																	 ));
			} else {
				dispatcher->addCommand(new ControlChange16BitCommand(channel,
																	 controlChangeNumberMSB,
																	 offValueMSB,
																	 controlChangeNumberLSB,
																	 offValueMSB));
			}
			digitalWrite(ledPin, toggle);
		} else {
			if(parameter == 1){
				dispatcher->addCommand(new ControlChange16BitCommand(channel,
																	 controlChangeNumberMSB,
																	 onValueMSB,
																	 controlChangeNumberLSB,
																	 onValueLSB
																	 ));
			} else {
				dispatcher->addCommand(new ControlChange16BitCommand(channel,
																	 controlChangeNumberMSB,
																	 offValueMSB,
																	 controlChangeNumberLSB,
																	 offValueMSB));
			}
			digitalWrite(ledPin, parameter);
		}
		updated = false;
	}
}

void ControlChangeToggle16Bit::setParameter(const uint16_t* value){
	if(parameter != *value){
		parameter = *value;

		if(parameter == 1){
			toggle = !toggle;

		}
		updated = true;
	}
}

boolean ControlChangeToggle16Bit:: setConfiguration(const int* data) {
		boolean result = false;

		if(
			data[0] == 0xF0 &&
			data[1] == ID &&
			data[4] == 0x01 &&
			data[10] == 0xFF
		  )
		{
			toggleOption = data[2];
			channel = data[3];
			controlChangeNumberMSB = data[5];
			controlChangeNumberLSB = controlChangeNumberMSB + 32;

			onValueMSB = data[6];
			onValueLSB = data[7];
			offValueMSB = data[8];
			offValueLSB = data[9];

			result = true;
		}

		return result;
	}

#ifdef DEBUG
void ControlChangeToggle16Bit::printContents(){
	String result = String("Control Change Toggle 16Bit \n");

	uint16_t onValue = convertBytesTo14Bit(onValueMSB, onValueLSB);
	uint16_t offValue = convertBytesTo14Bit(offValueMSB, onValueLSB);


	result += (String)"Toggle Option: " + toggleOption + "\n";
	result += (String)"MIDI Channel : " + channel + "\n";
	result += (String)"CC nr MSB    : " + controlChangeNumberMSB + "\n";
	result += (String)"CC nr LSB    : " + controlChangeNumberMSB + "\n";
	result += (String)"On Value     : " + onValue + "\n";
	result += (String)"On Value MSB : " + onValueMSB + "\n";
	result += (String)"On Value LSB : " + onValueLSB + "\n";
	result += (String)"Off Value    : " + offValue + "\n";
	result += (String)"Off Value MSB: " + offValueMSB + "\n";
	result += (String)"Off Value LSB: " + offValueLSB + "\n";
	result += (String)"Parameter    : " + parameter + "\n";

	result += (String)"Enabled      : " + toggle + "\n";
	result += (String)"LedPin       : " + ledPin + "\n";
	Serial.println(result);
}
#endif // DEBUG
