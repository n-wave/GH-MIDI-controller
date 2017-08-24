/*
 * NoteControlChangeFadeToggle8Bit.cpp
 *
 *  Created on: Aug 23, 2017
 *      Author: mario
 */

#include "ControlChangeFadeToggle8Bit.h"
#include "../../command/ControlChange8BitCommand.h"

ControlChangeFadeToggle8Bit::ControlChangeFadeToggle8Bit() :
	toggleOption(0),
	channel(0),
	controlChangeNumber(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	enabled(false),
	ledPin(0),
	dispatcher(NULL)
{
	// TODO Auto-generated constructor stub

}

ControlChangeFadeToggle8Bit::ControlChangeFadeToggle8Bit(const int* data) :
	toggleOption(0),
	channel(0),
	controlChangeNumber(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	enabled(false),
	ledPin(0),
	dispatcher(NULL)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeFade16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeFade8ToggleBit::ControlChangeFade16ToggleBit(const int* data) while loading data");
	}
#endif /* DEBUG */
}

ControlChangeFadeToggle8Bit::ControlChangeFadeToggle8Bit(const int* data, Dispatcher* dispatcher) :
	toggleOption(0),
	channel(0),
	controlChangeNumber(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	enabled(false),
	ledPin(0),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeFade16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeFade8ToggleBit::ControlChangeFade16ToggleBit(const int* data, Dispatcher*) while loading data");
	}
#endif /* DEBUG */
}

ControlChangeFadeToggle8Bit::ControlChangeFadeToggle8Bit(const int* data, uint8_t ledPin, Dispatcher* dispatcher) :
	toggleOption(0),
	channel(0),
	controlChangeNumber(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	enabled(false),
	ledPin(ledPin),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

	#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeFade16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeFade8ToggleBit::ControlChangeFade16ToggleBit(const int* data, uint8_t, Dispatcher* dispatcher) while loading data");
	}
#endif /* DEBUG */
}

ControlChangeFadeToggle8Bit::~ControlChangeFadeToggle8Bit() {
	dispatcher = NULL;
}

void ControlChangeFadeToggle8Bit::update(const uint32_t* time){
	dispatcher->addCommand(new ControlChange8BitCommand(5, 14, 127));
}

void ControlChangeFadeToggle8Bit::setParameter(const uint16_t* value){
	parameter = *value;
}

uint16_t ControlChangeFadeToggle8Bit::getParameter(){
	return parameter;
}

boolean ControlChangeFadeToggle8Bit::setConfiguration(const int* data) {
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		(data[3] == 0x00 || data[3] == 0x02) &&
		data[12] == 0xFF
	  )
	{
		channel = data[2];
		toggleOption = (data[3] & 0B00000010) >> 1;
		controlChangeNumber = data[4];
		start = data[5];
		hold = data[6];
		end = data[7];
		fadeIn = this->convertBytesTo16Bit(data[8], data[9]);
		fadeOut = this->convertBytesTo16Bit(data[10], data[11]);

		result = true;
	}

	return result;
}

uint16_t ControlChangeFadeToggle8Bit::convertBytesTo16Bit(uint8_t msb, uint8_t lsb){
	uint16_t result = 0;
	uint16_t MSB = (msb & 0XFF) << 8;
	uint16_t LSB = lsb & 0xFF;

	result = MSB | LSB;

	return result;
}

#ifdef DEBUG
void ControlChangeFadeToggle8Bit::printContents(){
	String result = String("Control Change Fade 8Bit \n");
	result += (String)"MIDI Channel : " + channel + "\n";
	result += (String)"Toggle Option: " + toggleOption + "\n";
	result += (String)"CC number    : " + controlChangeNumber + "\n";
	result += (String)"Start        : " + start + "\n";
	result += (String)"Hold         : " + hold + "\n";
	result += (String)"End          : " + end + "\n";
	result += (String)"FadeIn       : " + fadeIn + "\n";
	result += (String)"FadeOut      : " + fadeOut + "\n";
	result += (String)"Parameter    : " + parameter + "\n";
	result += (String)"Enabled      : " + enabled + "\n";
	result += (String)"LedPin       : " + ledPin + "\n";

	Serial.println(result);
}
#endif /* DEBUG */
