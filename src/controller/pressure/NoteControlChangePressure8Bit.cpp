/*
 * NoteControlChange8Bit.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#include "../../command/NoteControlChange8BitCommand.h"
#include "../../command/ControlChange8BitCommand.h"

#include "NoteControlChangePressure8Bit.h"

NoteControlChangePressure8Bit::NoteControlChangePressure8Bit() :
	channel(0),
	pitch(0),
	velocity(0),
	velocityOption(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	range(0),
	value7Bit(0),
	updated(false),
	sendNote(false),
	dispatcher(NULL)
{
}

NoteControlChangePressure8Bit::NoteControlChangePressure8Bit(const int* data) :
	channel(0),
	pitch(0),
	velocity(0),
	velocityOption(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	range(0),
	value7Bit(0),
	updated(false),
	sendNote(false),
	dispatcher(NULL)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("NoteControlChangePressure8Bit successfully initialized");
	} else {
		Serial.println("Error occurred in NoteControlChangePressure8Bit while loading data");
	}
#endif /* DEBUG */
}

NoteControlChangePressure8Bit::NoteControlChangePressure8Bit(const int* data, Dispatcher* dispatcher) :
	channel(0),
	pitch(0),
	velocity(0),
	velocityOption(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	parameter(0),
	range(0),
	value7Bit(0),
	updated(false),
	sendNote(false),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("NoteControlChangePressure8Bit successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in NoteControlChangePressure8Bit while loading data");
	}
#endif /* DEBUG */
}

NoteControlChangePressure8Bit::~NoteControlChangePressure8Bit() {
	dispatcher = NULL;
}


/* NoteControlChangePressure8Bit::update()
 *
 * Calculate values.
 *
 * add new NoteControlChangePressure8BitCommand
 *
 * arg 1: uint8_t channel
 * arg 2: uint8_t pitch
 * arg 3: uint8_t velocity
 * arg 4: uint8_t ccNumber
 * arg 5: uint8_t ccValue
 *
 */

void NoteControlChangePressure8Bit::update(const uint32_t* time){
	if(updated){
		if(value7Bit != 0){
			uint8_t scalar = 0;
			scalar = (range * value7Bit) >> 7;
			scalar += bottomValue;

			if(sendNote == true){
				if(velocityOption == 1){
					uint8_t tmpVelocity = (velocity * value7Bit) >> 7;

					dispatcher->addCommand(new NoteControlChange8BitCommand(channel,
																			pitch,
																			tmpVelocity,
																			controlChangeNumber,
																			scalar));
				} else {
					dispatcher->addCommand(new NoteControlChange8BitCommand(channel,
																			pitch,
																			velocity,
																			controlChangeNumber,
																			scalar));
				}
				sendNote = false;
			} else {
				dispatcher->addCommand(new ControlChange8BitCommand(channel,
																	controlChangeNumber,
																	scalar));

			}
		} else {
			dispatcher->addCommand(new NoteControlChange8BitCommand(channel,
																	pitch,
																	0,
																	controlChangeNumber,
																	0));
			sendNote = false;
		}
		updated = false;
	}
}

void NoteControlChangePressure8Bit::setParameter(const uint16_t* value){
	uint8_t tmp = *value >> 9;

	if(tmp != value7Bit){
		if(value7Bit == 0){
			sendNote = true;
		}
		value7Bit = tmp;
		parameter = *value;
		updated = true;
	}
}

uint16_t NoteControlChangePressure8Bit::getParameter(){
	return parameter;
}

boolean NoteControlChangePressure8Bit::setConfiguration(const int* data){
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		data[6] == 0x00 &&
		data[10] == 0xFF
      )
	{
		channel = data[2];
		pitch = data[3];
		velocity = data[4];
		velocityOption = data[5];
		controlChangeNumber = data[7];
		topValue = data[8];
		bottomValue = data[9];

		range = topValue - bottomValue;

		result = true;
	}
	return result;
}

#ifdef DEBUG
    void NoteControlChangePressure8Bit::printContents(){
    	String result = String("Note Control Change 8 Bit \n");
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"Pitch        : " + pitch + "\n";
    	result += (String)"Velocity     ; " + velocity + "\n";
    	result += (String)"Vel Option   : " + velocityOption + "\n";
    	result += (String)"CC nr        : " + controlChangeNumber + "\n";
    	result += (String)"TopValue     : " + topValue + "\n";
    	result += (String)"BottomValue  : " + bottomValue + "\n";
    	result += (String)"Range        : " + range + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */
