/*
 * Dispatcher.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#include "Dispatcher.h"
#include "Arduino.h"
#include "../testing/configuration.h"

Dispatcher::Dispatcher() :
	index(0)
{
	for(int i=0; i<MAXITEMS; i++){
		buffer[i] = NULL;
	}

}

Dispatcher::~Dispatcher() {
	this->clearBuffer();

#ifdef DEBUG
	Serial.println("Calling Destructor of Dispatcher");
#endif /* DEBUG */
}

void Dispatcher::addCommand(Command* command){
	if(index < MAXITEMS){
		buffer[index++] = command;
	}
#ifdef DEBUG
	else {
		Serial.println("Buffer is full, dispatch or clear");
	}
#endif /* DEBUG */
}

void Dispatcher::clearBuffer(){
	for(int i=0; i<MAXITEMS; i++){
		if(buffer[i] != NULL){
			delete buffer[i];
			buffer[i] = NULL;
		}
#ifdef DEBUG
		else {
			Serial.println("NULL object found");
		}
#endif /* DEBUG */
	}
}

void Dispatcher::dispatch(){
	for(int i=0; i<index; i++){
		buffer[i]->operator ()();
		delete buffer[i];
		buffer[i] = NULL;
	}
	index = 0;
}
