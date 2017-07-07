/*
 * NoteVelocity.cpp
 *
 *  Created on: Jul 4, 2017
 *      Author: mario
 */

#include "NoteVelocity.h"

NoteVelocity::NoteVelocity() :
	channel(0),
	pitch(0),
	velocity(0),
	velocityOption(0),
	parameter(0)
{

}

NoteVelocity::NoteVelocity(const int* data) :
	channel(0),
	pitch(0),
	velocity(0),
	velocityOption(0),
	parameter(0)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("NoteVelocity successfully initialized");
	} else {
		Serial.println("Error occurred in NoteVelocity while loading data");
	}
#endif /* DEBUG */
}

NoteVelocity::~NoteVelocity() {
	// TODO Auto-generated destructor stub
}

void NoteVelocity::execute(){

}

void NoteVelocity::update(const uint32_t* time){

}

void NoteVelocity::setParameter(const uint16_t* value){
	parameter = *value;
}

uint16_t NoteVelocity::getParameter(){
	return parameter;
}

boolean NoteVelocity::setConfiguration(const int* data){
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == id &&
		data[6] == 0xFF
	  )
	{
		channel = data[2];
		pitch = data[3];
		velocity = data[4];
		velocityOption = data[5];

		result = true;
	}
	return result;
}

#ifdef DEBUG
    String NoteVelocity::toString(){
    	String result = String("Note Velocity \n");
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"Pitch        : " + pitch + "\n";
    	result += (String)"Velocity     : " + velocity + "\n";
    	result += (String)"Vel Option   : " + velocityOption + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";
    	return result;
    }
#endif /* DEBUG */

