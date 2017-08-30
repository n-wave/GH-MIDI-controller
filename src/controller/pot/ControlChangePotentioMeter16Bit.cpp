/*
 * ControlChangePotentioMeter16Bit.cpp
 *
 *  Created on: Aug 24, 2017
 *      Author: mario
 */

#include "ControlChangePotentioMeter16Bit.h"
#include "../../command/ControlChange16BitCommand.h"

ControlChangePotentioMeter16Bit::ControlChangePotentioMeter16Bit() :
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	topValue(0),
	bottomValue(0),
    range(0),
	parameter(0),
	updated(false),
	dispatcher(NULL)
{
}

ControlChangePotentioMeter16Bit::ControlChangePotentioMeter16Bit(const int* data) :
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	topValue(0),
	bottomValue(0),
    range(0),
	parameter(0),
	updated(false),
	dispatcher(NULL)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangePotentioMeter16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangePotentioMeter16Bit while loading data");
	}
#endif /* DEBUG */
}

ControlChangePotentioMeter16Bit::ControlChangePotentioMeter16Bit(const int* data, Dispatcher* dispatcher) :
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	topValue(0),
	bottomValue(0),
    range(0),
	parameter(0),
	updated(false),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangePotentioMeter16Bit successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in ControlChangePotentioMeter16Bit while loading data");
	}
#endif /* DEBUG */

}

ControlChangePotentioMeter16Bit::~ControlChangePotentioMeter16Bit() {
	dispatcher = NULL;
}


/* ControlChangeFade8Bit::update()
 *
 * Calculate values.
 *
 * add new ControlChangePotentioMeter16BitCommand
 *
 * arg 1: uint8_t channel
 * arg 2: uint8_t ccNumberMSB
 * arg 3: uint8_t ccValueMSB
 * arg 4: uint8_t ccNumerLSB
 * arg 5: uint8_t ccValueLSB
 */

void ControlChangePotentioMeter16Bit::update(const uint32_t* time) {
	if(updated == true){
		uint8_t controlChangeValueMSB = 0;
		uint8_t controlChangeValueLSB = 0;

		uint16_t scalar = 0;  // Temporary holder
		scalar = (range*parameter) >> 14;
		scalar += bottomValue;

		controlChangeValueMSB = (scalar >> 7) & 0B01111111;
		controlChangeValueLSB = scalar & 0B01111111; //Mask only needed bytes

		dispatcher->addCommand(new ControlChange16BitCommand(channel,				  //Midi Channel
															 controlChangeNumberMSB,  //Control Change MSB
															 controlChangeValueMSB,   //MSB Value
															 controlChangeNumberLSB,  //Control Change LSB
															 controlChangeValueLSB)); //LSB Value
		updated = false;
	}
}

void ControlChangePotentioMeter16Bit::setParameter(const uint16_t* value) {
	uint16_t tmp = *value;

	if(tmp != parameter){
		parameter = tmp;
		updated = true;
	}
}

uint16_t ControlChangePotentioMeter16Bit::getParameter() {
	return parameter;
}

boolean ControlChangePotentioMeter16Bit:: setConfiguration(const int* data) {
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		data[3] == 0x01 &&
		data[9] == 0xFF
	  )
	{
		channel = data[2];
		controlChangeNumberMSB = data[4];
		controlChangeNumberLSB = controlChangeNumberMSB + 32;

		topValue = this->convertBytesTo14Bit(data[5], data[6]);
		bottomValue = this->convertBytesTo14Bit(data[7], data[8]);

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

uint16_t ControlChangePotentioMeter16Bit::convertBytesTo14Bit(uint8_t msb, uint8_t lsb){
	uint16_t result = 0;
	uint16_t MSB = (msb & 0x7F) << 7;
	uint16_t LSB = lsb & 0x7F;

	result = MSB | LSB;

	return result;
}

#ifdef DEBUG
    void ControlChangePotentioMeter16Bit::printContents(){
    	String result = String("Control Change 16Bit \n");

    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"CC nr MSB    : " + controlChangeNumberMSB + "\n";
    	result += (String)"CC nr LSB    : " + controlChangeNumberLSB + "\n";
    	result += (String)"Top Value    : " + topValue + "\n";
    	result += (String)"Bottom Value : " + bottomValue + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */
