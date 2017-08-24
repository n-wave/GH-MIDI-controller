/*
 * ControlChangeFadeToggle16Bit.cpp
 *
 *  Created on: Aug 23, 2017
 *      Author: mario
 */

#include "ControlChangeFadeToggle16Bit.h"

ControlChangeFadeToggle16Bit::ControlChangeFadeToggle16Bit() :
	toggleOption(0),
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	enabled(0),
	ledPin(0),
	dispatcher(NULL)
{
}

ControlChangeFadeToggle16Bit::ControlChangeFadeToggle16Bit(const int* data) :
	toggleOption(0),
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	enabled(0),
	ledPin(0),
	dispatcher(NULL)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeFade16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeFade16Bit::ControlChangeFadeToggle16Bit(const int*) while loading data");
	}
#endif /* DEBUG */
}

ControlChangeFadeToggle16Bit::ControlChangeFadeToggle16Bit(const int* data, Dispatcher* dispatcher) :
	toggleOption(0),
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	enabled(0),
	ledPin(0),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeFade16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeFade16Bit::ControlChangeFadeToggle16Bit(const int*, Dispatcher*) while loading data");
	}
#endif /* DEBUG */
}

ControlChangeFadeToggle16Bit::ControlChangeFadeToggle16Bit(const int* data, uint8_t ledPin, Dispatcher* dispatcher) :
	toggleOption(0),
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	enabled(0),
	ledPin(ledPin),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeFade16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeFade16Bit::ControlChangeFadeToggle16Bit(const int*, uint8_t, Dispatcher*) while loading data");
	}
#endif /* DEBUG */
}

ControlChangeFadeToggle16Bit::~ControlChangeFadeToggle16Bit() {
	dispatcher = NULL;
}

void ControlChangeFadeToggle16Bit::update(const uint32_t* time) {

}

void ControlChangeFadeToggle16Bit::setParameter(const uint16_t* value){
	parameter = *value;
}

uint16_t ControlChangeFadeToggle16Bit::getParameter(){
	return parameter;
}

boolean ControlChangeFadeToggle16Bit::setConfiguration(const int* data) {
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		(data[3] == 0x01 || data[3] == 0x03) &&
		data[15] == 0xFF
	  )
	{
		channel = data[2];
		toggleOption = (data[3] & 0B00000010) >> 1;
		controlChangeNumberMSB = data[4];
		controlChangeNumberLSB = controlChangeNumberMSB + 32;

		start = this->convertBytesTo14Bit(data[5], data[6]);
		hold = this->convertBytesTo14Bit(data[7], data[8]);
		end = this->convertBytesTo14Bit(data[9], data[10]);

		fadeIn = this->convertBytesTo16Bit(data[11], data[12]);
		fadeOut = this->convertBytesTo16Bit(data[13], data[14]);

		result = true;
	}
	return result;
}

/**
 *  Convert Supplied MSB and LSB values to the
 *  14Bit value they represent, store and return
 *  the result in a 16Bit value
 */

uint16_t ControlChangeFadeToggle16Bit::convertBytesTo14Bit(uint8_t msb, uint8_t lsb){
	uint16_t result = 0;
	uint16_t MSB = (msb & 0x7F) << 7;
	uint16_t LSB = lsb & 0x7F;

	result = MSB | LSB;

	return result;
}

/**
 *  Convert Supplied MSB and LSB values to the
 *  16Bit value they represent, store and return
 *  the result in a 16Bit value
 */

uint16_t ControlChangeFadeToggle16Bit::convertBytesTo16Bit(uint8_t msb, uint8_t lsb){
	uint16_t result = 0;
	uint16_t MSB = (msb & 0xFF) << 8;
	uint16_t LSB = lsb & 0xFF;

	result = MSB | LSB;

	return result;
}

#ifdef DEBUG
    void ControlChangeFadeToggle16Bit::printContents(){
    	String result = String("Control Change Fade 16 Bit \n");
    	result == (String)"Toggle Option: " + toggleOption + "\n";
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"CC number msb: " + controlChangeNumberMSB + "\n";
    	result += (String)"CC number lsb: " + controlChangeNumberLSB + "\n";
    	result += (String)"Start        : " + start + "\n";
    	result += (String)"Hold         : " + hold + "\n";
    	result += (String)"End          : " + end + "\n";
    	result += (String)"FadeIn       : " + fadeIn + "\n";
    	result += (String)"Fadeout      : " + fadeOut + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";

    	result += (String)"Enabled      : " + enabled + "\n";
    	result += (String)"Ledpin       : " + ledPin + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */
