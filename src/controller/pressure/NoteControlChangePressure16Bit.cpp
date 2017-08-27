/*
 * NoteControlChange16Bit.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#include "NoteControlChangePressure16Bit.h"
#include "../../command/NoteControlChange16BitCommand.h"
#include "../../command/ControlChange16BitCommand.h"

NoteControlChangePressure16Bit::NoteControlChangePressure16Bit() :
	channel(0),
	pitch(0),
	velocity(0),
	velocityOption(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	topValue(0),
	bottomValue(0),
	range(0),
	parameter(0),
	value14Bit(0),
	updated(false),
	sendNote(false),
	dispatcher(NULL)
{
	// TODO Auto-generated constructor stub
}

NoteControlChangePressure16Bit::NoteControlChangePressure16Bit(const int* data) :
	channel(0),
	pitch(0),
	velocity(0),
	velocityOption(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	topValue(0),
	bottomValue(0),
	range(0),
	parameter(0),
	value14Bit(0),
	updated(false),
	sendNote(false),
	dispatcher(NULL)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("NoteControlChangePressure16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in NoteControlChangePressure16Bit::NoteControlChangePressure16Bit(const int*) while loading data");
	}
#endif /* DEBUG */
}

NoteControlChangePressure16Bit::NoteControlChangePressure16Bit(const int* data, Dispatcher* dispatcher) :
	channel(0),
	pitch(0),
	velocity(0),
	velocityOption(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	topValue(0),
	bottomValue(0),
	range(0),
	parameter(0),
	value14Bit(0),
	updated(false),
	sendNote(false),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("NoteControlChangePressure16Bit successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in NoteControlChangePressure16Bit::NoteControlChangePressure16Bit(const int*, Dispatcher* )while loading data");
	}
#endif /* DEBUG */
}

NoteControlChangePressure16Bit::~NoteControlChangePressure16Bit() {
	dispatcher = NULL;
}

/* NoteControlChangePressure16Bit::update()
 *
 * Calculate values.
 *
 * add new NoteControlChangeCommand Command
 *
 * arg 1: uint8_t channel
 * arg 2: uint8_t pitch
 * arg 3: uint8_t velocity
 * arg 4: uint8_t ccNumberMSB
 * arg 5: uint8_t ccValueMSB
 * arg 6: uint8_t ccNumberLSB
 * arg 7: uint8_t ccValueLSB
 *
 */

void NoteControlChangePressure16Bit::update(const uint32_t* value){
	if(updated){
		if(value14Bit != 0){
			uint16_t scalar = (range * value14Bit) >> 14;
			scalar += bottomValue;

			uint8_t controlChangeValueMSB = (scalar >> 7) & 0B01111111;
			uint8_t controlChangeValueLSB = scalar & 0B01111111;

			if(sendNote == true){
				if(velocityOption == 1){
					uint8_t tmpValue7Bit = value14Bit >> 7;
					uint8_t tmpVelocity = (velocity * tmpValue7Bit) >> 7;

					dispatcher->addCommand(new NoteControlChange16BitCommand(channel,
																			 pitch,
																			 tmpVelocity,
																			 controlChangeNumberMSB,
																			 controlChangeValueMSB,
																			 controlChangeNumberLSB,
																			 controlChangeValueLSB));

					dispatcher->addCommand(new NoteControlChange16BitCommand(channel,
																			 pitch,
																			 velocity,
																			 controlChangeNumberMSB,
																			 controlChangeValueMSB,
																			 controlChangeNumberLSB,
																			 controlChangeValueLSB));
				}
				sendNote = false;
			} else {
				dispatcher->addCommand(new ControlChange16BitCommand(channel,
																	 controlChangeNumberMSB,
																	 controlChangeValueMSB,
																	 controlChangeNumberLSB,
																	 controlChangeValueLSB));

			}
		} else {
			dispatcher->addCommand(new NoteControlChange16BitCommand(channel,
																	 pitch,
																	 0,
																	 controlChangeNumberMSB,
																	 0,
																	 controlChangeNumberLSB,
																	 0));
			sendNote = false;
		}
		updated = false;
	}


	dispatcher->addCommand(new NoteControlChange16BitCommand(2, 80, 100, 12, 100, 44, 10));
}

void NoteControlChangePressure16Bit::setParameter(const uint16_t* value){
	uint16_t tmp = *value >> 7;

	if(tmp != value14Bit){
		if(value14Bit == 0){
			sendNote = true;
		}
		value14Bit = tmp;
		parameter = *value;
		updated = true;
	}
}

uint16_t NoteControlChangePressure16Bit::getParameter(){
	return parameter;
}

boolean NoteControlChangePressure16Bit::setConfiguration(const int* data){
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		data[6] == 0x01 &&
		data[12] == 0xFF
	  )
	{
		channel = data[2];
		pitch = data[3];
		velocity = data[4];
		velocityOption = data[5];
		controlChangeNumberMSB = data[7];
		controlChangeNumberLSB = controlChangeNumberMSB + 32;

		topValue = this->convertBytesTo14Bit(data[8], data[9]);
		bottomValue = this->convertBytesTo14Bit(data[10], data[11]);

		range = topValue - bottomValue;

		result = true;
	}

	return result;
}
/**
 *  Convert Supplied MSB and LSB values to the
 *  14Bit value they represent, store and return
 *  the result in a 16Bit value
 */

uint16_t NoteControlChangePressure16Bit::convertBytesTo14Bit(uint8_t msb, uint8_t lsb){
	uint16_t result = 0;
	uint16_t MSB = (msb & 0x7F) << 7;
	uint16_t LSB = lsb & 0x7F;

	result = MSB | LSB;

	return result;
}

#ifdef DEBUG
    void NoteControlChangePressure16Bit::printContents(){
    	String result = String("Note Control Change 16Bit \n");
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"Pitch        : " + pitch + "\n";
    	result += (String)"Velocity     : " + velocity + "\n";
    	result += (String)"Vel Option   : " + velocityOption + "\n";
    	result += (String)"CC nr MSB    : " + controlChangeNumberMSB + "\n";
    	result += (String)"CC nr LSB    : " + controlChangeNumberLSB + "\n";
    	result += (String)"Top Value    : " + topValue + "\n";
    	result += (String)"Bottom Value : " + bottomValue + "\n";

    	result += (String)"Parameter    : " + parameter + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */

