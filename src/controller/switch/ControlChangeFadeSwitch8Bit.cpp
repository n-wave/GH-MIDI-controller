/*
 * ControlChangeFadeSwitch8Bit.cpp
 *
 *  Created on: Aug 24, 2017
 *      Author: mario
 */

#include "ControlChangeFadeSwitch8Bit.h"
#include "../../command/ControlChange8BitCommand.h"

ControlChangeFadeSwitch8Bit::ControlChangeFadeSwitch8Bit() :
	channel(0),
	controlChangeNumber(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	fadeInEnabled(false),
	fadeOutEnabled(false),
    startValue(0), // calculated start Value
    holdValue(0), //calculated hold value
    endValue(0),  //calcuated end Value
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

ControlChangeFadeSwitch8Bit::ControlChangeFadeSwitch8Bit(const int* data) :
	channel(0),
	controlChangeNumber(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	fadeInEnabled(false),
	fadeOutEnabled(false),
    startValue(0), // calculated start Value
    holdValue(0), //calculated hold value
    endValue(0),  //calcuated end Value
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
		Serial.println("ControlChangeFadeSwitch8Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeFadeSwitch8Bit while loading data");
	}
#endif /* DEBUG */
}

ControlChangeFadeSwitch8Bit::ControlChangeFadeSwitch8Bit(const int* data, Dispatcher* dispatcher) :
	channel(0),
	controlChangeNumber(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	fadeInEnabled(false),
	fadeOutEnabled(false),
    startValue(0), // calculated start Value
    holdValue(0), //calculated hold value
    endValue(0),  //calcuated end Value
    currentValue(0),
    fadeInStepSize(0),
	fadeOutTimeConstant(0),
    fadeOutStepSize(0),
	endModus(0),
	state(0),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

	/* The floating point algorithm works but
	 * we are using floats, one possible solution
	 * to this problem is to use a higher valued
	 * integer thus for the 7Bit value we multiply
	 * by (128 * 1000) or (value << 7) * 1000
	 * to get the value in the 14 Bit range
	 * to bit shift to the right at the end
	 * of the increment  and sent a MIDI Message
	 * to the computer/ this method will be an
	 * approximation but for this application
	 * it suffices
	 *
	 * use MethodPointerArray[3] for the
	 * Appropriate method based on the current
	 * state.
	 */

	/*
	if(success && fadeIn >= 20){
		fadeInPeriods = timeMultiplier * fadeIn;
		fadeIncrement = hold/fadeInPeriods;
	}
	*/

	for(int i=0; i<3; i++){
		methodPointerArray[i] = NULL;
	}


	if(success){
		if(fadeIn >= 20){
			currentValue = startValue;

			if(start < hold){
				fadeInStepSize = ((holdValue-startValue) * 1000)/(SAMPLERATE * fadeIn);
				noInterrupts();
				methodPointerArray[0] = &ControlChangeFadeSwitch8Bit::fadeInIncrement;
				interrupts();
			} else if(start > hold){
				fadeInStepSize = ((startValue - holdValue) * 1000)/(SAMPLERATE * fadeIn);

				noInterrupts();
				methodPointerArray[0] = &ControlChangeFadeSwitch8Bit::fadeInDecrement;
				interrupts();
			}
		}else if(fadeIn < 20){
			noInterrupts();
			methodPointerArray[0] = &ControlChangeFadeSwitch8Bit::sendOutHoldValue;
			interrupts();
		}

		if(fadeOut >= 20){
			fadeOutTimeConstant = SAMPLERATE*fadeOut;

			if(end < hold){
				fadeOutStepSize = ((holdValue-endValue) * 1000)/fadeOutTimeConstant;
				endModus = 1; //negative direction decrement
			} else if(end > hold){
				fadeOutStepSize =  ((endValue - holdValue) * 1000)/fadeOutTimeConstant;
				endModus = 2;// positive direction increment
			}

			noInterrupts();
			methodPointerArray[1] = &ControlChangeFadeSwitch8Bit::fadeOutDecrement;
			methodPointerArray[2] = &ControlChangeFadeSwitch8Bit::fadeOutIncrement;
			interrupts();
		} else if(fadeOut < 20){
			endModus = 0;

			noInterrupts();
			methodPointerArray[1] = &ControlChangeFadeSwitch8Bit::sendOutEndValue;
			methodPointerArray[2] = &ControlChangeFadeSwitch8Bit::sendOutEndValue;
			interrupts();
		}
	}

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeFadeSwitch8Bit successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in ControlChangeFadeSwitch8Bit while loading data");
	}
#endif /* DEBUG */
}

ControlChangeFadeSwitch8Bit::~ControlChangeFadeSwitch8Bit() {
	for(int i=0; i<3; i++){
		methodPointerArray[i] = NULL;
	}

	dispatcher = NULL;
}


/* ControlChangeFadeSwitch8Bit::update()
 *
 * Calculate values.
 *
 * add new PitchBendNote Command
 *
 * arg 1: uint8_t channel
 * arg 2: uint8_t ccNumber
 * arg 3: uint8_t ccValue
 *
 */

void ControlChangeFadeSwitch8Bit::update(const uint32_t* time) {

	if(methodPointerArray[state] != NULL){
		(this->*methodPointerArray[state])();
	}
}

void ControlChangeFadeSwitch8Bit::setParameter(const uint16_t* value) {
	if(parameter != *value){
		parameter = *value;

		if(parameter == 1){
			state = 0;
			fadeInEnabled = true;
			fadeOutEnabled = false;
			currentValue = startValue;
		}

		/*
		 *  If the EndValue is bigger than the current value we should
		 * increment so the endModus switches from increment to decrement
		 * also check the state if it didn't change from incrementing
		 * to decrementing ignore the calculation entirely
		 * ignore
		 *
		 */

		if(parameter == 0){
			if(endModus != 0){
				if(endValue < currentValue && state != 1){
					fadeOutStepSize = ((currentValue-endValue)*1000)/fadeOutTimeConstant;
					state = 1;
				}

				if(endValue > currentValue && state != 2){
					fadeOutStepSize = ((endValue-currentValue)*1000)/fadeOutTimeConstant;
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

void ControlChangeFadeSwitch8Bit::fadeInIncrement(){
	if(fadeInEnabled){
		currentValue += fadeInStepSize;

		if(currentValue < holdValue){
			uint8_t tmp = currentValue >> 7;
			dispatcher->addCommand(new ControlChange8BitCommand(channel,
																controlChangeNumber,
																tmp));
		} else {
			dispatcher->addCommand(new ControlChange8BitCommand(channel,
																	controlChangeNumber,
																	hold));

			currentValue = holdValue;
			fadeInEnabled = false;
		}
	}
}

void ControlChangeFadeSwitch8Bit::fadeOutIncrement(){
	if(fadeOutEnabled){
		currentValue += fadeOutStepSize;

		if(currentValue < endValue){
			uint8_t tmp = currentValue >> 7;
			dispatcher->addCommand(new ControlChange8BitCommand(channel,
																controlChangeNumber,
																tmp));
		} else {
			dispatcher->addCommand(new ControlChange8BitCommand(channel,
																controlChangeNumber,
																end));
			fadeOutEnabled = false;
		}
	}
}

void ControlChangeFadeSwitch8Bit::fadeInDecrement(){
	if(fadeInEnabled){
		currentValue -= fadeInStepSize;
		uint8_t tmp = currentValue >> 7;

	   /**
		* Need extra check with decrementing because of the
		* possible overflow when the decrement result goes
		* negative this occurs when the settings have
		* a short delay time and a high delta value between
		* the beginning and target value.
		*
		* Also the tmp is checked against the target value
		* to avoid sending duplicate values to the USB port
		**/

		if(currentValue > holdValue && fadeInStepSize < currentValue && tmp != hold){
			dispatcher->addCommand(new ControlChange8BitCommand(channel,
																	controlChangeNumber,
																	tmp));

		} else {
			dispatcher->addCommand(new ControlChange8BitCommand(channel,
																	controlChangeNumber,
																	hold));

			currentValue = holdValue;
			fadeInEnabled = false;
		}
	}
}

void ControlChangeFadeSwitch8Bit::fadeOutDecrement(){
	if(fadeOutEnabled){
		currentValue -= fadeOutStepSize;
		uint8_t tmp = currentValue >> 7;

		if(currentValue > endValue  && fadeOutStepSize < currentValue && tmp != end){
			    dispatcher->addCommand(new ControlChange8BitCommand(channel,
																    controlChangeNumber,
																     tmp));
		} else {
			dispatcher->addCommand(new ControlChange8BitCommand(channel,
																controlChangeNumber,
																end));
			fadeOutEnabled = false;
		}
	}
}

void ControlChangeFadeSwitch8Bit::sendOutHoldValue(){
	if(fadeInEnabled){
		dispatcher->addCommand(new ControlChange8BitCommand(channel,
														controlChangeNumber,
														hold));

		currentValue = holdValue;
		fadeInEnabled = false;
	}
}

void ControlChangeFadeSwitch8Bit::sendOutEndValue(){
	if(fadeOutEnabled){
		dispatcher->addCommand(new ControlChange8BitCommand(channel,
															controlChangeNumber,
															end));

		fadeOutEnabled = false;
	}
}

uint16_t ControlChangeFadeSwitch8Bit::getParameter() {
	return parameter;
}

boolean ControlChangeFadeSwitch8Bit::setConfiguration(const int* data) {
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		data[3] == 0x00 &&
		data[12] == 0xFF
	  )
	{
		channel = data[2];
		controlChangeNumber = data[4];
		start = data[5];
		hold = data[6];
		end = data[7];
		fadeIn = this->convertBytesTo16Bit(data[8], data[9]);
		fadeOut = this->convertBytesTo16Bit(data[10], data[11]);

		startValue = start << 7;
		holdValue = hold << 7; //Bring up the 7Bit values to 14 bit and
							   //calculate from that point
		endValue = end << 7;

		result = true;
	}

	return result;
}

/**
 *  Convert Supplied MSB and LSB values to the
 *  16Bit value they represent, store and return
 *  the result in a 16Bit value
 */

uint16_t ControlChangeFadeSwitch8Bit::convertBytesTo16Bit(uint8_t msb, uint8_t lsb){
	uint16_t result = 0;
	uint16_t MSB = (msb & 0XFF) << 8;
	uint16_t LSB = lsb & 0xFF;

	result = MSB | LSB;

	return result;
}

#ifdef DEBUG
void ControlChangeFadeSwitch8Bit::printContents(){
	String result = String("Control Change Fade Switch 8Bit \n");
	result += (String)"MIDI Channel : " + channel + "\n";
	result += (String)"CC number    : " + controlChangeNumber + "\n";
	result += (String)"Start        : " + start + "\n";
	result += (String)"Hold         : " + hold + "\n";
	result += (String)"End          : " + end + "\n";
	result += (String)"FadeIn       : " + fadeIn + "\n";
	result += (String)"FadeOut      : " + fadeOut + "\n";
	result += (String)"Parameter    : " + parameter + "\n";

	Serial.println(result);
}
#endif /* DEBUG */
