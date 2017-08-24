/*
 * NoteControlChangeToggle16Bit.cpp
 *
 *  Created on: Aug 22, 2017
 *      Author: mario
 */

#include "NoteControlChangeToggle16Bit.h"
#include "../../command/NoteControlChange16BitCommand.h"

NoteControlChangeToggle16Bit::NoteControlChangeToggle16Bit() :
	toggleOption(0),
	channel(0),
	pitch(0),
	velocity(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	enabled(0),
	ledPin(0),
	dispatcher(NULL)
{
}

NoteControlChangeToggle16Bit::NoteControlChangeToggle16Bit(const int* data) :
	toggleOption(0),
	channel(0),
	pitch(0),
	velocity(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	enabled(0),
	ledPin(0),
	dispatcher(NULL)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("NoteControlChange16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in NoteControlChangeToggle16Bit::NoteControlChange16Bit(const int*) while loading data");
	}
#endif /* DEBUG */
}

NoteControlChangeToggle16Bit::NoteControlChangeToggle16Bit(const int* data, Dispatcher* dispatcher) :
	toggleOption(0),
	channel(0),
	pitch(0),
	velocity(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	enabled(0),
	ledPin(0),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("NoteControlChange16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in NoteControlChangeToggle16Bit::NoteControlChangeToggle16Bit(const int*, Dispatcher*) while loading data");
	}
#endif /* DEBUG */
}

NoteControlChangeToggle16Bit::NoteControlChangeToggle16Bit(const int* data, uint8_t ledPin, Dispatcher* dispatcher) :
	toggleOption(0),
	channel(0),
	pitch(0),
	velocity(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	enabled(0),
	ledPin(ledPin),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);
#ifdef DEBUG
	if(success){
		Serial.println("NoteControlChange16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in NoteControlChangeToggle16Bit::NoteControlChangeToggle16Bit(const int*, uint8_t ledPin, Dispatcher*) while loading data");
	}
#endif /* DEBUG */
}

NoteControlChangeToggle16Bit::~NoteControlChangeToggle16Bit() {
	dispatcher = NULL;
}


void NoteControlChangeToggle16Bit::update(const uint32_t* time){
	dispatcher->addCommand(new NoteControlChange16BitCommand(2, 80, 100, 12, 100, 44, 10));
}

void NoteControlChangeToggle16Bit::setParameter(const uint16_t* value){
	parameter = *value;
}

uint16_t NoteControlChangeToggle16Bit::getParameter(){
	return parameter;
}

boolean NoteControlChangeToggle16Bit::setConfiguration(const int* data){
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		data[6] == 0x01 &&
		data[12] == 0xFF
	  )
	{
		toggleOption = data[2];
		channel = data[3];
		pitch = data[4];
		velocity = data[5];
		controlChangeNumberMSB = data[7];
		controlChangeNumberLSB = controlChangeNumberMSB + 32;

		topValue = this->convertBytesTo14Bit(data[8], data[9]);
		bottomValue = this->convertBytesTo14Bit(data[10], data[11]);

		result = true;
	}

	return result;
}
/**
 *  Convert Supplied MSB and LSB values to the
 *  14Bit value they represent, store and return
 *  the result in a 16Bit value
 */

uint16_t NoteControlChangeToggle16Bit::convertBytesTo14Bit(uint8_t msb, uint8_t lsb){
	uint16_t result = 0;
	uint16_t MSB = (msb & 0x7F) << 7;
	uint16_t LSB = lsb & 0x7F;

	result = MSB | LSB;

	return result;
}

#ifdef DEBUG
    void NoteControlChangeToggle16Bit::printContents(){
    	String result = String("Note Control Change 16Bit \n");
    	result += (String)"Toggle Option: " + toggleOption + "\n";
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"Pitch        : " + pitch + "\n";
    	result += (String)"Velocity     : " + velocity + "\n";
    	result += (String)"CC nr MSB    : " + controlChangeNumberMSB + "\n";
    	result += (String)"CC nr LSB    : " + controlChangeNumberLSB + "\n";
    	result += (String)"Top Value    : " + topValue + "\n";
    	result += (String)"Bottom Value : " + bottomValue + "\n";

    	result += (String)"Parameter    : " + parameter + "\n";
    	result += (String)"Enabled      : " + enabled + "\n";
    	result += (String)"LedPin       : " + ledPin + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */

