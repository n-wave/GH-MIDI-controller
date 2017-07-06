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
	// TODO Auto-generated constructor stub

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
		result = false;
	}

	return result;
}

#ifdef DEBUG
String PitchBend::toString(){
	String result = String("Pitch Bend");
	result += (String)"MIDI Channel : " + channel + "\n";
	result += (String)"Parameter    : " + parameter + "\n";
	return result;
}
#endif /* DEUUG */
