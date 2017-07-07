/*
 * ProgramChange.cpp
 *
 *  Created on: Jul 4, 2017
 *      Author: mario
 */

#include "ProgramChange.h"


ProgramChange::ProgramChange() :
	channel(0),
	bank(0),
	program(0)
{
	// TODO Auto-generated constructor stub
}

ProgramChange::ProgramChange(const int* data) :
	channel(0),
	bank(0),
	program(0)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ProgramChange successfully initialized");
	} else {
		Serial.println("Error occurred in ProgramChange while loading data");
	}
#endif /* DEBUG */
}

ProgramChange::~ProgramChange() {
	// TODO Auto-generated destructor stub
}

void ProgramChange::execute(){

}

void ProgramChange::update(const uint32_t* time){

}

void ProgramChange::setParameter(const uint16_t * value){

}

uint16_t ProgramChange::getParameter(){
	return -1;
}

boolean ProgramChange::setConfiguration(const int* data){
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == id &&
		data[5] == 0xFF
	  )
	{
		channel = data[2];
		bank = data[3];
		program = data[4];

		result = true;
	}

	return result;
}

#ifdef DEBUG
    String ProgramChange::toString(){
    	String result = String("Program Change \n");
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"Bank         : " + bank + "\n";
    	result += (String)"program      : " + program + "\n";

    	return result;
    }
#endif /* DEBUG */
