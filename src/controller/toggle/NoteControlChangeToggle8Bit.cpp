/*
 * NoteControlChangeToggle8Bit.cpp
 *
 *  Created on: Aug 22, 2017
 *      Author: mario
 */

#include "NoteControlChangeToggle8Bit.h"
#include "../../command/NoteControlChange8BitCommand.h"

NoteControlChangeToggle8Bit::NoteControlChangeToggle8Bit() :
	channel(0),
	toggleOption(0),
	pitch(0),
	velocity(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	enabled(false),
	ledPin(0),
	dispatcher(NULL)
{
}

NoteControlChangeToggle8Bit::NoteControlChangeToggle8Bit(const int* data) :
	channel(0),
	toggleOption(0),
	pitch(0),
	velocity(0),
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
		Serial.println("NoteControlChangeToggle8Bit successfully initialized");
	} else {
		Serial.println("Error occurred in NoteControlChangeToggle8Bit::NoteControlChangeToggle8Bit(const int*) while loading data");
	}
#endif /* DEBUG */

}

NoteControlChangeToggle8Bit::NoteControlChangeToggle8Bit(const int* data, Dispatcher* dispatcher) :
	channel(0),
	toggleOption(0),
	pitch(0),
	velocity(0),
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
		Serial.println("NoteControlChangeToggle8Bit successfully initialized");
	} else {
		Serial.println("Error occurred in NoteControlChangeToggle8Bit::NoteControlChangeToggle8Bit(const int*, Dispatcher* ) while loading data");
	}
#endif /* DEBUG */
}

NoteControlChangeToggle8Bit::NoteControlChangeToggle8Bit(const int* data, uint8_t ledPin, Dispatcher* dispatcher) :
	channel(0),
	toggleOption(0),
	pitch(0),
	velocity(0),
	controlChangeNumber(0),
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
		Serial.println("NoteControlChangeToggle8Bit successfully initialized");
	} else {
		Serial.println("Error occurred in NoteControlChangeToggle8Bit::NoteControlChangeToggle8Bit(const int*, uint8_t ledPin, Dispatcher* ) while loading data");
	}
#endif /* DEBUG */
}

NoteControlChangeToggle8Bit::~NoteControlChangeToggle8Bit()
{
	dispatcher = NULL;
}


/* NoteControlChange8Bit::update()
 *
 * Calculate values.
 *
 * add new NoteControlChange8BitCommand
 *
 * arg 1: uint8_t channel
 * arg 2: uint8_t pitch
 * arg 3: uint8_t velocity
 * arg 4: uint8_t ccNumber
 * arg 5: uint8_t ccValue
 *
 */


void NoteControlChangeToggle8Bit::update(const uint32_t* time){
	dispatcher->addCommand(new NoteControlChange8BitCommand(0, 64, 100, 13, 90));
}


void NoteControlChangeToggle8Bit::setParameter(const uint16_t* value){
	parameter = *value;
}

uint16_t NoteControlChangeToggle8Bit::getParameter(){
	return parameter;
}

boolean NoteControlChangeToggle8Bit::setConfiguration(const int* data){
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		data[6] == 0x00 &&
		data[10] == 0xFF
      )
	{
		toggleOption = data[2];
		channel = data[3];
		pitch = data[4];
		velocity = data[5];
		controlChangeNumber = data[7];
		topValue = data[8];
		bottomValue = data[9];
		result = true;
	}
	return result;
}

#ifdef DEBUG
    void NoteControlChangeToggle8Bit::printContents(){
    	String result = String("Note Control Change 8 Bit \n");
    	result += (String)"Toggle Option: " + toggleOption + "\n";
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"Pitch        : " + pitch + "\n";
    	result += (String)"Velocity     ; " + velocity + "\n";
    	result += (String)"CC nr        : " + controlChangeNumber + "\n";
    	result += (String)"TopValue     : " + topValue + "\n";
    	result += (String)"BottomValue  : " + bottomValue + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";
    	result += (String)"Enabled      : " + enabled + "\n";
    	result += (String)"Led Pin      : " + ledPin + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */


