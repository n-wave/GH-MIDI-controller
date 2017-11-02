/*
 * DisabledController.cpp
 *
 *  Created on: Jul 12, 2017
 *      Author: mario
 */

#include "DisabledController.h"

DisabledController::DisabledController() :
	parameter(0)
{
	// TODO Auto-generated constructor stub

}

DisabledController::DisabledController(const int* data) :
	parameter(0)
{
#ifndef DEBUG
	this->setConfiguration(data);
#endif


#ifdef DEBUG
	boolean succes = this->setConfiguration(data);

	if(succes){
		Serial.println("Disabled Controller successfully initialized");
	} else {
		Serial.println("Error occurred in DisabledController::DisabledController(const int*)");
	}
#endif /* DEBUG */
}

DisabledController::~DisabledController() {
	// TODO Auto-generated destructor stub
}


void DisabledController::update(){}

void DisabledController::setParameter(const uint16_t* value){
	/* Disabled Controller nothing to see here */
}

boolean DisabledController::setConfiguration(const int* data){
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		data[2] == 0xFF
	  )
	{
		result = true;
	}
	return result;
}

#ifdef DEBUG
	void DisabledController::printContents(){
		Serial.println("Disabled Controller \n");
	}
#endif /* DEBUG */
