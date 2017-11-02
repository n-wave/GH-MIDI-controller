/*
 * NoteControlChangeToggle16Bit.cpp
 *
 *  Created on: Aug 22, 2017
 *      Author: mario
 */

#include "NoteControlChangeToggle16Bit.h"
#include "../../command/NoteControlChange16BitCommand.h"

NoteControlChangeToggle16Bit::NoteControlChangeToggle16Bit() :
	toggleOption(0),
	channel(0),
	pitch(0),
	velocity(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	onValueMSB(0),
	onValueLSB(0),
	offValueMSB(0),
	offValueLSB(0),
	parameter(0),
	toggle(false),
	updated(false),
	ledPin(0),
	dispatcher(NULL)
{
}

NoteControlChangeToggle16Bit::NoteControlChangeToggle16Bit(const int* data) :
	toggleOption(0),
	channel(0),
	pitch(0),
	velocity(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	onValueMSB(0),
	onValueLSB(0),
	offValueMSB(0),
	offValueLSB(0),
	parameter(0),
	toggle(false),
	updated(false),
	ledPin(0),
	dispatcher(NULL)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("NoteControlChange16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in NoteControlChangeToggle16Bit::NoteControlChange16Bit(const int*) while loading data");
	}
#endif /* DEBUG */
}

NoteControlChangeToggle16Bit::NoteControlChangeToggle16Bit(const int* data, Dispatcher* dispatcher) :
	toggleOption(0),
	channel(0),
	pitch(0),
	velocity(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	onValueMSB(0),
	onValueLSB(0),
	offValueMSB(0),
	offValueLSB(0),
	parameter(0),
	toggle(false),
	updated(false),
	ledPin(0),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("NoteControlChange16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in NoteControlChangeToggle16Bit::NoteControlChangeToggle16Bit(const int*, Dispatcher*) while loading data");
	}
#endif /* DEBUG */
}

NoteControlChangeToggle16Bit::NoteControlChangeToggle16Bit(const int* data, uint8_t ledPin, Dispatcher* dispatcher) :
	toggleOption(0),
	channel(0),
	pitch(0),
	velocity(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	onValueMSB(0),
	onValueLSB(0),
	offValueMSB(0),
	offValueLSB(0),
	parameter(0),
	toggle(false),
	updated(false),
	ledPin(ledPin),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);

#ifdef DEBUG
	if(success){
		Serial.println("NoteControlChange16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in NoteControlChangeToggle16Bit::NoteControlChangeToggle16Bit(const int*, uint8_t ledPin, Dispatcher*) while loading data");
	}
#endif /* DEBUG */
}

NoteControlChangeToggle16Bit::~NoteControlChangeToggle16Bit() {
	dispatcher = NULL;
}

/* NoteControlChange16Bit::update()
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

void NoteControlChangeToggle16Bit::update(const uint32_t* time){
	if(updated){
		if(toggleOption == 1){
			if(toggle){
				dispatcher->addCommand(new NoteControlChange16BitCommand(channel,
																		 pitch,
																		 velocity,
																		 controlChangeNumberMSB,
																		 onValueMSB,
																		 controlChangeNumberLSB,
																		 onValueLSB));
			} else {
				dispatcher->addCommand(new NoteControlChange16BitCommand(channel,
																		 pitch,
																		 0,
																		 controlChangeNumberMSB,
																		 offValueMSB,
																		 controlChangeNumberLSB,
																		 offValueLSB));
			}
			digitalWrite(ledPin, toggle);
		} else {
			if(parameter != 0){
				dispatcher->addCommand(new NoteControlChange16BitCommand(channel,
																		 pitch,
																		 velocity,
																		 controlChangeNumberMSB,
																		 onValueMSB,
																		 controlChangeNumberLSB,
																		 onValueLSB));
			} else {
				dispatcher->addCommand(new NoteControlChange16BitCommand(channel,
																		 pitch,
																		 0,
																		 controlChangeNumberMSB,
																		 offValueMSB,
																		 controlChangeNumberLSB,
																		 offValueLSB));
			}
			digitalWrite(ledPin, parameter);
			}
		updated = false;
	}
}

void NoteControlChangeToggle16Bit::setParameter(const uint16_t* value){
	if(parameter != *value){
		parameter = *value;

		if(parameter == 1){
			toggle = !toggle;
		}

		updated = true;
	}
}

uint16_t NoteControlChangeToggle16Bit::getParameter(){
	return parameter;
}

boolean NoteControlChangeToggle16Bit::setConfiguration(const int* data){
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		data[6] == 0x01 &&
		data[12] == 0xFF
	  )
	{
		toggleOption = data[2];
		channel = data[3];
		pitch = data[4];
		velocity = data[5];
		controlChangeNumberMSB = data[7];
		controlChangeNumberLSB = controlChangeNumberMSB + 32;

		onValueMSB = data[8];
		onValueLSB = data[9];

		offValueMSB = data[10];
		offValueLSB = data[11];

		result = true;
	}

	return result;
}
/**
 *  Convert Supplied MSB and LSB values to the
 *  14Bit value they represent, store and return
 *  the result in a 16Bit value
 */

uint16_t NoteControlChangeToggle16Bit::convertBytesTo14Bit(uint8_t msb, uint8_t lsb){
	uint16_t result = 0;
	uint16_t MSB = (msb & 0x7F) << 7;
	uint16_t LSB = lsb & 0x7F;

	result = MSB | LSB;

	return result;
}

#ifdef DEBUG
    void NoteControlChangeToggle16Bit::printContents(){
    	uint16_t onValue = this->convertBytesTo14Bit(onValueMSB, onValueLSB);
    	uint16_t offValue = this->convertBytesTo14Bit(onValueMSB, onValueLSB);

    	String result = String("Note Control Change 16Bit \n");
    	result += (String)"Toggle Option: " + toggleOption + "\n";
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"Pitch        : " + pitch + "\n";
    	result += (String)"Velocity     : " + velocity + "\n";
    	result += (String)"CC nr MSB    : " + controlChangeNumberMSB + "\n";
    	result += (String)"CC nr LSB    : " + controlChangeNumberLSB + "\n";
    	result += (String)"Top Value    : " + onValue + "\n";
    	result += (String)"Bottom Value : " + offValue + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";
    	result += (String)"Toggle       : " + toggle + "\n";
    	result += (String)"LedPin       : " + ledPin + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */

