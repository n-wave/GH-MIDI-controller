/*
 * ControlChangeFadeSwitch16Bit.cpp
 *
 *  Created on: Aug 24, 2017
 *      Author: mario
 */

#include "ControlChangeFadeSwitch16Bit.h"
#include "../../command/ControlChange16BitCommand.h"

ControlChangeFadeSwitch16Bit::ControlChangeFadeSwitch16Bit() :
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	start(0),
	startMSB(0),
	startLSB(0),
	hold(0),
	holdMSB(0),
	holdLSB(0),
	end(0),
	endMSB(0),
	endLSB(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	fadeInEnabled(false),
	fadeOutEnabled(false),
	currentValue(0),
	fadeInStepSize(0),
	fadeOutTimeConstant(0),
	fadeOutStepSize(0),
	endModus(0),
	state(0),
	dispatcher(NULL)
{
	for(int i=0; i<3; i++){
		methodPointerArray[i] = NULL;
	}
}

ControlChangeFadeSwitch16Bit::ControlChangeFadeSwitch16Bit(const int* data) :
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	start(0),
	startMSB(0),
	startLSB(0),
	hold(0),
	holdMSB(0),
	holdLSB(0),
	end(0),
	endMSB(0),
	endLSB(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	fadeInEnabled(false),
	fadeOutEnabled(false),
	currentValue(0),
	fadeInStepSize(0),
	fadeOutTimeConstant(0),
	fadeOutStepSize(0),
	endModus(0),
	state(0),
	dispatcher(NULL)
{

#ifndef DEBUG
	this->setConfiguration(data);
#endif

	for(int i=0; i<3; i++){
		methodPointerArray[i] = NULL;
	}

#ifdef DEBUG
	boolean success = this->setConfiguration(data);

	if(success){
		Serial.println("ControlChangeFadeSwitch16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeFadeSwitch16Bit while loading data");
	}
#endif /* DEBUG */
}

ControlChangeFadeSwitch16Bit::ControlChangeFadeSwitch16Bit(const int* data, Dispatcher* dispatcher) :
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	start(0),
	startMSB(0),
	startLSB(0),
	hold(0),
	holdMSB(0),
	holdLSB(0),
	end(0),
	endMSB(0),
	endLSB(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	fadeInEnabled(false),
	fadeOutEnabled(false),
	currentValue(0),
	fadeInStepSize(0),
	fadeOutTimeConstant(0),
	fadeOutStepSize(0),
	endModus(0),
	state(0),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

	for(int i=0; i<3; i++){
		methodPointerArray[i] = NULL;
	}


	if(success){
		if(fadeIn >= 20){
			currentValue = start;

			if(start < hold){
				/*
				 *  We don't have to bitshift the values by << 10
				 *  the range suffices by multiplying with 1000 here
				 *  the 14Bit values are in a sufficient range
				 *
				 */

				fadeInStepSize = ((hold-start)*1000)/(SAMPLERATE * fadeIn);
				noInterrupts();
				methodPointerArray[0] = &ControlChangeFadeSwitch16Bit::fadeInIncrement;
				interrupts();
			} else if(start > hold){
				fadeInStepSize = ((start-hold)*1000)/(SAMPLERATE*fadeIn);

				noInterrupts();
				methodPointerArray[0] = &ControlChangeFadeSwitch16Bit::fadeInDecrement;
				interrupts();
			}
		} else if(fadeIn < 20){
			noInterrupts();
			methodPointerArray[0] = &ControlChangeFadeSwitch16Bit::sendOutHoldValue;
			interrupts();
		}

		if(fadeOut >= 20){

			fadeOutTimeConstant = SAMPLERATE*fadeOut;

			if(end < hold){
				fadeOutStepSize = ((hold-end)*1000)/fadeOutTimeConstant;
				endModus = 1; //negative direction decrement
			} else if(end > hold){
				fadeOutStepSize =  ((end - hold)*1000)/fadeOutTimeConstant;
				endModus = 2;// positive direction increment
			}

				noInterrupts();
				methodPointerArray[1] = &ControlChangeFadeSwitch16Bit::fadeOutDecrement;
				methodPointerArray[2] = &ControlChangeFadeSwitch16Bit::fadeOutIncrement;
				interrupts();
			} else if(fadeOut < 20){
				endModus = 0;

				noInterrupts();
				methodPointerArray[1] = &ControlChangeFadeSwitch16Bit::sendOutEndValue;
				methodPointerArray[2] = &ControlChangeFadeSwitch16Bit::sendOutEndValue;
				interrupts();
		}
	}

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeFadeSwitch16Bit successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in ControlChangeFadeSwitch16Bit while loading data");
	}
#endif /* DEBUG */
}

ControlChangeFadeSwitch16Bit::~ControlChangeFadeSwitch16Bit() {
	for(int i=0; i<3; i++){
		methodPointerArray[i] = NULL;
	}

	dispatcher = NULL;
}

/* ControlChangeFade8Bit::update()
 *
 * Calculate values.
 *
 * add new ControlChange16BitCommand
 *
 * arg 1: uint8_t channel
 * arg 2: uint8_t ccNumberMSB
 * arg 3: uint8_t ccValueMSB
 * arg 4: uint8_t ccNumerLSB
 * arg 5: uint8_t ccValueLSB
 *
 * 	dispatcher->addCommand(new ControlChange16BitCommand(10, 11, 13, 43, 10));
 *
 */

void ControlChangeFadeSwitch16Bit::update(const uint32_t* time) {
	if(methodPointerArray[state] != NULL){
		(this->*methodPointerArray[state])();
	}
}

void ControlChangeFadeSwitch16Bit::setParameter(const uint16_t* value) {
	if(parameter != *value){
		parameter = *value;

		if(parameter == 1){
			state = 0;
			fadeInEnabled = true;
			fadeOutEnabled = false;
			currentValue = start;
		}

		if(parameter == 0){
			if(endModus != 0){
				if(end < currentValue && state != 1){
					fadeOutStepSize = ((currentValue - end)*1000)/fadeOutTimeConstant;
					state = 1;
				}

				if(end > currentValue && state != 2){
					fadeOutStepSize = ((end - currentValue)*1000)/fadeOutTimeConstant;
					state = 2;
				}
			} else {
				state = 1;
			}
			fadeInEnabled = false;
			fadeOutEnabled = true;
		}
	}
}

void ControlChangeFadeSwitch16Bit::fadeInIncrement(){
	if(fadeInEnabled){
		currentValue += fadeInStepSize;

		if(currentValue < hold){
			uint8_t msbValue = (currentValue >> 7) & 0x7F;
			uint8_t lsbValue = currentValue & 0x7F;

			dispatcher->addCommand(new ControlChange16BitCommand(channel,
																 controlChangeNumberMSB,
																 msbValue,
																 controlChangeNumberLSB,
																 lsbValue
																 ));
		} else {
			dispatcher->addCommand(new ControlChange16BitCommand(channel,
																 controlChangeNumberMSB,
																 holdMSB,
																 controlChangeNumberLSB,
																 holdLSB
																 ));

			currentValue = hold;
			fadeInEnabled = false;
		}

	}
}

void ControlChangeFadeSwitch16Bit::fadeOutIncrement(){
	if(fadeOutEnabled){
		currentValue += fadeOutStepSize;

		if(currentValue < end){
			uint8_t msbValue = (currentValue >> 7) & 0x7F;
			uint8_t lsbValue = currentValue & 0x7F;

			dispatcher->addCommand(new ControlChange16BitCommand(channel,
																 controlChangeNumberMSB,
																 msbValue,
																 controlChangeNumberLSB,
																 lsbValue
																 ));
		} else {
			dispatcher->addCommand(new ControlChange16BitCommand(channel,
																 controlChangeNumberMSB,
																 endMSB,
																 controlChangeNumberLSB,
																 endLSB
																));

			fadeOutEnabled = false;
		}
	}
}

void ControlChangeFadeSwitch16Bit::fadeInDecrement(){
	if(fadeInEnabled){
		currentValue -= fadeInStepSize;

		if(currentValue > hold && fadeInStepSize < currentValue && currentValue != hold){
			uint8_t msbValue = (currentValue >> 7) & 0x7F;
			uint8_t lsbValue = currentValue & 0x7F;

			dispatcher->addCommand(new ControlChange16BitCommand(channel,
																 controlChangeNumberMSB,
																 msbValue,
																 controlChangeNumberLSB,
																 lsbValue
																 ));
		} else {
			dispatcher->addCommand(new ControlChange16BitCommand(channel,
																 controlChangeNumberMSB,
																 holdMSB,
																 controlChangeNumberLSB,
																 holdLSB
																));


			currentValue = hold;
			fadeInEnabled = false;
		}

	}
}

void ControlChangeFadeSwitch16Bit::fadeOutDecrement(){
	if(fadeOutEnabled){
		currentValue -= fadeOutStepSize;

		if(currentValue > end  && fadeOutStepSize < currentValue && currentValue != end){
			uint8_t msbValue = (currentValue >> 7) & 0x7F;
			uint8_t lsbValue = currentValue & 0x7F;

			dispatcher->addCommand(new ControlChange16BitCommand(channel,
																 controlChangeNumberMSB,
																 msbValue,
																 controlChangeNumberLSB,
																 lsbValue
																 ));
		} else {
			dispatcher->addCommand(new ControlChange16BitCommand(channel,
																 controlChangeNumberMSB,
																 endMSB,
																 controlChangeNumberLSB,
																 endLSB
																));
			fadeOutEnabled = false;
		}
	}
}

void ControlChangeFadeSwitch16Bit::sendOutHoldValue(){
	if(fadeInEnabled){
		dispatcher->addCommand(new ControlChange16BitCommand(channel,
															 controlChangeNumberMSB,
															 holdMSB,
															 controlChangeNumberLSB,
															 holdLSB
															));

		currentValue = hold;
		fadeInEnabled = false;
	}
}

void ControlChangeFadeSwitch16Bit::sendOutEndValue(){
	if(fadeOutEnabled){
		dispatcher->addCommand(new ControlChange16BitCommand(channel,
															 controlChangeNumberMSB,
															 endMSB,
															 controlChangeNumberLSB,
															 endLSB
															));
		fadeOutEnabled = false;
	}
}

uint16_t ControlChangeFadeSwitch16Bit::getParameter() {
	return parameter;
}

boolean ControlChangeFadeSwitch16Bit::setConfiguration(const int* data) {
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		data[3] == 0x01 &&
		data[15] == 0xFF
	  )
	{
		channel = data[2];
		controlChangeNumberMSB = data[4];
		controlChangeNumberLSB = controlChangeNumberMSB + 32;

		startMSB = data[5];
		startLSB = data[6];
		holdMSB = data[7];
		holdLSB = data[8];
		endMSB = data[9];
		endLSB = data[10];

		start = this->convertBytesTo14Bit(startMSB, startLSB);
		hold = this->convertBytesTo14Bit(holdMSB, holdLSB);
		end = this->convertBytesTo14Bit(endMSB, endLSB);


		fadeIn = this->convertBytesTo16Bit(data[11], data[12]);
		fadeOut = this->convertBytesTo16Bit(data[13], data[14]);

		result = true;
	}
	return result;
}

/**
 *  Convert Supplied MSB and LSB values to the
 *  14Bit value they represent, store and return
 *  the result in a 16Bit value
 */

uint16_t ControlChangeFadeSwitch16Bit::convertBytesTo14Bit(uint8_t msb, uint8_t lsb){
	uint16_t result = 0;
	uint16_t MSB = (msb & 0x7F) << 7;
	uint16_t LSB = lsb & 0x7F;

	result = MSB | LSB;

	return result;
}

/**
 *  Convert Supplied MSB and LSB values to the
 *  16Bit value they represent, store and return
 *  the result in a 16Bit value
 */

uint16_t ControlChangeFadeSwitch16Bit::convertBytesTo16Bit(uint8_t msb, uint8_t lsb){
	uint16_t result = 0;
	uint16_t MSB = (msb & 0xFF) << 8;
	uint16_t LSB = lsb & 0xFF;

	result = MSB | LSB;

	return result;
}

#ifdef DEBUG
    void ControlChangeFadeSwitch16Bit::printContents(){
		uint16_t start = this->convertBytesTo14Bit(startMSB, startLSB);
		uint16_t hold = this->convertBytesTo14Bit(holdMSB, holdLSB);
		uint16_t end = this->convertBytesTo14Bit(endMSB, endLSB);

    	String result = String("Control Change Fade 16 Bit \n");
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"CC number msb: " + controlChangeNumberMSB + "\n";
    	result += (String)"CC number lsb: " + controlChangeNumberLSB + "\n";
    	result += (String)"Start        : " + start + "\n";
    	result += (String)"Hold         : " + hold + "\n";
    	result += (String)"End          : " + end + "\n";
    	result += (String)"FadeIn       : " + fadeIn + "\n";
    	result += (String)"Fadeout      : " + fadeOut + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */
