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
	onValue(0),
	offValue(0),
	parameter(0),
	toggle(false),
	updated(false),
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
	onValue(0),
	offValue(0),
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
	onValue(0),
	offValue(0),
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
	onValue(0),
	offValue(0),
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


void NoteControlChangeToggle8Bit::update(){
	if(updated){
		if(toggleOption == 1){
			if(toggle){
				dispatcher->addCommand(new NoteControlChange8BitCommand(channel,
																		pitch,
																		velocity,
																		controlChangeNumber,
																		onValue));
			} else {
				dispatcher->addCommand(new NoteControlChange8BitCommand(channel,
																		pitch,
																		0,
																		controlChangeNumber,
																		offValue));
			}
			digitalWrite(ledPin, toggle);
		} else {
			if(parameter != 0){
				dispatcher->addCommand(new NoteControlChange8BitCommand(channel,
																		pitch,
																		velocity,
																		controlChangeNumber,
																		onValue));
			} else {
				dispatcher->addCommand(new NoteControlChange8BitCommand(channel,
																		pitch,
																		0,
																		controlChangeNumber,
																		offValue));
			}
			digitalWrite(ledPin, parameter);
		}
		updated = false;
	}
}


void NoteControlChangeToggle8Bit::setParameter(const uint16_t* value){
	if(parameter != *value){
		parameter = *value;

		if(parameter == 1){
			toggle = !toggle;
		}

		updated = true;
	}
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
		onValue = data[8];
		offValue = data[9];
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
    	result += (String)"OnValue      : " + onValue + "\n";
    	result += (String)"OffValue     : " + offValue + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";
    	result += (String)"Toggle       : " + toggle + "\n";
    	result += (String)"Led Pin      : " + ledPin + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */


