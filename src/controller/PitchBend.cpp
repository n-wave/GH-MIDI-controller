/*
 * PitchBend.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#include "PitchBend.h"

PitchBend::PitchBend() :
	channel(0),
	parameter(0)
{

}

PitchBend::PitchBend(const int* data) :
	channel(0),
	parameter(0)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("PitchBend successfully initialized");
	} else {
		Serial.println("Error occurred in PitchBend while loading data");
	}
#endif /* DEBUG */
}
PitchBend::~PitchBend(){
	// TODO Auto-generated destructor stub
}

void PitchBend::execute(){

}

void PitchBend::update(const uint32_t* time){

}

void PitchBend::setParameter(const uint16_t* value){
	parameter = *value;
}

uint16_t PitchBend::getParameter(){
	return parameter;
}

boolean PitchBend::setConfiguration(const int* data){
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == id &&
		data[3] == 0xFF
	  )
	{
		channel = data[2];
		result = true;
	}

	return result;
}

#ifdef DEBUG
void PitchBend::printContents(){
	String result = String("Pitch Bend \n");
	result += (String)"MIDI Channel : " + channel + "\n";
	result += (String)"Parameter    : " + parameter + "\n";

	Serial.println(result);
}
#endif /* DEUUG */
