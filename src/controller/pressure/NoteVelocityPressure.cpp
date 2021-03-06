/*
 * NoteVelocityPressure.cpp
 *
 *  Created on: Jul 4, 2017
 *      Author: mario
 */

#include "../../command/NoteVelocityCommand.h"
#include "NoteVelocityPressure.h"

NoteVelocityPressure::NoteVelocityPressure() :
	channel(0),
	pitch(0),
	velocity(0),
	velocityOption(0),
	parameter(0),
	updated(false),
	dispatcher(NULL)
{

}

NoteVelocityPressure::NoteVelocityPressure(const int* data) :
	channel(0),
	pitch(0),
	velocity(0),
	velocityOption(0),
	parameter(0),
	updated(false),
	dispatcher(NULL)
{
#ifndef DEBUG
	this->setConfiguration(data);
#endif

#ifdef DEBUG

	boolean success = this->setConfiguration(data);

	if(success){
		Serial.println("NoteVelocityPressure successfully initialized");
	} else {
		Serial.println("Error occurred in NoteVelocityPressure::NoteVelocityPressure(const int*) while loading data");
	}
#endif /* DEBUG */
}

NoteVelocityPressure::NoteVelocityPressure(const int* data, Dispatcher* dispatcher) :
	channel(0),
	pitch(0),
	velocity(0),
	velocityOption(0),
	parameter(0),
	updated(false),
	dispatcher(dispatcher)
{
#ifndef DEBUG
	this->setConfiguration(data);
#endif

#ifdef DEBUG
	boolean success = this->setConfiguration(data);

	if(success){
		Serial.println("NoteVelocityPressure successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in NoteVelocityPressure::NoteVelocityPressure(const int*, Dispatcher) while loading data");
	}
#endif /* DEBUG */
}

NoteVelocityPressure::~NoteVelocityPressure() {
	dispatcher = NULL;
}

/* NoteVelocityPressure::update()
 *
 * Calculate values.
 *
 * add new NoteVelocityPressureCommand
 *
 * arg 1: uint8_t channel
 * arg 2: uint8_t pitch
 * arg 3: uint8_t velocity
 *
 */

void NoteVelocityPressure::update(){
	if(updated){
			if(parameter != 0){
				if(velocityOption == 1){
					uint8_t tmpVelocity;

					tmpVelocity = (parameter >= velocity) ? velocity : parameter;

					dispatcher->addCommand(new NoteVelocityCommand(channel,
																   pitch,
																   tmpVelocity));
				}else {
					dispatcher->addCommand(new NoteVelocityCommand(channel,
																   pitch,
																   velocity));
				}
		} else {
			dispatcher->addCommand(new NoteVelocityCommand(channel,
												    	   pitch,
														   0));
		}

	updated = false;
	}
}
void NoteVelocityPressure::setParameter(const uint16_t* value){
	uint8_t tmp = *value >> 7;

	if(tmp != parameter){
		/** transition from zero to positive
		 *  or vice versa
		 */
		if(parameter == 0 || tmp == 0)
		{
			parameter = tmp;
			updated = true;
		}
	}
}


boolean NoteVelocityPressure::setConfiguration(const int* data){
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
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
    void NoteVelocityPressure::printContents(){
    	String result = String("Note Velocity \n");
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"Pitch        : " + pitch + "\n";
    	result += (String)"Velocity     : " + velocity + "\n";
    	result += (String)"Vel Option   : " + velocityOption + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */

