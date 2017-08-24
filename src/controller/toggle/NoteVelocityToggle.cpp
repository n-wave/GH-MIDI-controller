/*
 * NoteVelocityToggle.cpp
 *
 *  Created on: Aug 22, 2017
 *      Author: mario
 */

#include "NoteVelocityToggle.h"
#include "../../command/NoteVelocityCommand.h"

NoteVelocityToggle::NoteVelocityToggle() :
	channel(0),
	toggleOption(0),
	pitch(0),
	velocity(0),
	parameter(0),
	enabled(false),
	ledPin(0),
	dispatcher(NULL)
{}

NoteVelocityToggle::NoteVelocityToggle(const int* data) :
	channel(0),
	toggleOption(0),
	pitch(0),
	velocity(0),
	parameter(0),
	enabled(false),
	ledPin(0),
	dispatcher(NULL)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("NoteVelocityToggle successfully initialized");
	} else {
		Serial.println("Error occurred in NoteVelocity::NoteVelocityToggle(const int*) while loading data");
	}
#endif /* DEBUG */
}

NoteVelocityToggle::NoteVelocityToggle(const int* data, Dispatcher* dispatcher) :
	channel(0),
	toggleOption(0),
	pitch(0),
	velocity(0),
	parameter(0),
	enabled(false),
	ledPin(0),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("NoteVelocityToggle successfully initialized");
	} else {
		Serial.println("Error occurred in NoteVelocity::NoteVelocityToggle(const int*, Dispatcher*) while loading data");
	}
#endif /* DEBUG */
}

NoteVelocityToggle::NoteVelocityToggle(const int* data, uint8_t ledPin, Dispatcher* dispatcher) :
	channel(0),
	toggleOption(0),
	pitch(0),
	velocity(0),
	parameter(0),
	enabled(false),
	ledPin(ledPin),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("NoteVelocityToggle successfully initialized");
	} else {
		Serial.println("Error occurred in NoteVelocity::NoteVelocityToggle(const int*, uint8_t ledPin, Dispatcher*) while loading data");
	}
#endif /* DEBUG */
}

NoteVelocityToggle::~NoteVelocityToggle() {
	dispatcher = NULL;
}


void NoteVelocityToggle::update(const uint32_t* time){
	dispatcher->addCommand(new NoteVelocityCommand(16, 52, 110));
}

void NoteVelocityToggle::setParameter(const uint16_t* value){
	parameter = *value;
}

uint16_t NoteVelocityToggle::getParameter(){
	return parameter;
}

boolean NoteVelocityToggle::setConfiguration(const int* data){
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		data[6] == 0xFF
	  )
	{
		toggleOption = data[2];
		channel = data[3];
		pitch = data[4];
		velocity = data[5];

		result = true;
	}
	return result;
}

#ifdef DEBUG
    void NoteVelocityToggle::printContents(){
    	String result = String("Note Velocity \n");
    	result += (String)"Toggle Option: " + toggleOption + "\n";
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"Pitch        : " + pitch + "\n";
    	result += (String)"Velocity     : " + velocity + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";
    	result += (String)"Enabled      : " + enabled + "\n";
    	result += (String)"Led Pin      : " + ledPin + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */


