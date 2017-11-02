/*
 * NoteControlChangeFadeToggle8Bit.cpp
 *
 *  Created on: Aug 23, 2017
 *      Author: mario
 */

#include "ControlChangeFadeToggle8Bit.h"
#include "../../command/ControlChange8BitCommand.h"
#include "../../ghmc/ghmc.h"

using ghmc::byte::convertBytesTo16Bit;

ControlChangeFadeToggle8Bit::ControlChangeFadeToggle8Bit() :
	toggleOption(0),
	channel(0),
	controlChangeNumber(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	toggle(false),
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
	ledPin(0),
	updated(false),
	dispatcher(NULL)
{
	// TODO Auto-generated constructor stub

}

ControlChangeFadeToggle8Bit::ControlChangeFadeToggle8Bit(const int* data) :
	toggleOption(0),
	channel(0),
	controlChangeNumber(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	toggle(false),
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
	ledPin(0),
	updated(false),
	dispatcher(NULL)
{

#ifndef DEBUG
	this->setConfiguration(data);
#endif

#ifdef DEBUG
	boolean success = this->setConfiguration(data);

	if(success){
		Serial.println("ControlChangeFade16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeFade8ToggleBit::ControlChangeFade16ToggleBit(const int* data) while loading data");
	}
#endif /* DEBUG */
}

ControlChangeFadeToggle8Bit::ControlChangeFadeToggle8Bit(const int* data, Dispatcher* dispatcher) :
	toggleOption(0),
	channel(0),
	controlChangeNumber(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	toggle(false),
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
	ledPin(0),
	updated(false),
	dispatcher(dispatcher)
{
#ifndef DEBUG
	this->setConfiguration(data);
#endif

#ifdef DEBUG
	boolean success = this->setConfiguration(data);

	if(success){
		Serial.println("ControlChangeFade16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeFade8ToggleBit::ControlChangeFade16ToggleBit(const int* data, Dispatcher*) while loading data");
	}
#endif /* DEBUG */
}

ControlChangeFadeToggle8Bit::ControlChangeFadeToggle8Bit(const int* data, uint8_t ledPin, Dispatcher* dispatcher) :
	toggleOption(0),
	channel(0),
	controlChangeNumber(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	toggle(false),
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
	ledPin(ledPin),
	updated(false),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

	for(int i=0; i<3; i++){
		methodPointerArray[i] = NULL;
	}

	if(success){
		if(fadeIn >= 20){
			currentValue = startValue;

			if(start < hold){
				fadeInStepSize = ((holdValue-startValue) * 1000)/(SAMPLERATE * fadeIn);
				noInterrupts();
				methodPointerArray[0] = &ControlChangeFadeToggle8Bit::fadeInIncrement;
				interrupts();
			} else if(start > hold){
				fadeInStepSize = ((startValue - holdValue) * 1000)/(SAMPLERATE * fadeIn);

				noInterrupts();
				methodPointerArray[0] = &ControlChangeFadeToggle8Bit::fadeInDecrement;
				interrupts();
			}
		}else if(fadeIn < 20){
			noInterrupts();
			methodPointerArray[0] = &ControlChangeFadeToggle8Bit::sendOutHoldValue;
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
		methodPointerArray[1] = &ControlChangeFadeToggle8Bit::fadeOutDecrement;
		methodPointerArray[2] = &ControlChangeFadeToggle8Bit::fadeOutIncrement;
		interrupts();
		} else if(fadeOut < 20){
			endModus = 0;

			noInterrupts();
			methodPointerArray[1] = &ControlChangeFadeToggle8Bit::sendOutEndValue;
			methodPointerArray[2] = &ControlChangeFadeToggle8Bit::sendOutEndValue;
			interrupts();
		}
	}


	#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeFade16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeFade8ToggleBit::ControlChangeFade16ToggleBit(const int* data, uint8_t, Dispatcher* dispatcher) while loading data");
	}
#endif /* DEBUG */
}

ControlChangeFadeToggle8Bit::~ControlChangeFadeToggle8Bit() {
	for(int i=0; i<3; i++){
		methodPointerArray[i] = NULL;
	}
	dispatcher = NULL;
}

void ControlChangeFadeToggle8Bit::update(const uint32_t* time){
	if(methodPointerArray[state] != NULL){
		(this->*methodPointerArray[state])();
	}
}

void ControlChangeFadeToggle8Bit::setParameter(const uint16_t* value){
	if(parameter != *value){
		updated = false;
		parameter = *value;

		if(toggleOption == 1){

			if(parameter == 1){
				toggle = !toggle;
				updated = true;
			}

		} else if(toggleOption == 0) {
			toggle = parameter;
			updated = true;
		}

		if(updated){
			if(toggle == 1){
				state = 0;
				fadeInEnabled = true;
				fadeOutEnabled = false;
				currentValue = startValue;

			}

			if(toggle == 0){
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
		digitalWrite(ledPin, toggle);
	}
}

void ControlChangeFadeToggle8Bit::fadeInIncrement(){
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

void ControlChangeFadeToggle8Bit::fadeOutIncrement(){
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

void ControlChangeFadeToggle8Bit::fadeInDecrement(){
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

void ControlChangeFadeToggle8Bit::fadeOutDecrement(){
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

void ControlChangeFadeToggle8Bit::sendOutHoldValue(){
	if(fadeInEnabled){
		dispatcher->addCommand(new ControlChange8BitCommand(channel,
														controlChangeNumber,
														hold));

		currentValue = holdValue;
		fadeInEnabled = false;
	}
}

void ControlChangeFadeToggle8Bit::sendOutEndValue(){
	if(fadeOutEnabled){
		dispatcher->addCommand(new ControlChange8BitCommand(channel,
															controlChangeNumber,
															end));

		fadeOutEnabled = false;
	}
}

uint16_t ControlChangeFadeToggle8Bit::getParameter(){
	return parameter;
}

boolean ControlChangeFadeToggle8Bit::setConfiguration(const int* data) {
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		(data[3] == 0x00 || data[3] == 0x02) &&
		data[12] == 0xFF
	  )
	{
		channel = data[2];
		toggleOption = (data[3] & 0B00000010) >> 1;
		controlChangeNumber = data[4];
		start = data[5];
		hold = data[6];
		end = data[7];

		fadeIn = ghmc::byte::convertBytesTo16Bit(data[8], data[9]);
		fadeOut = ghmc::byte::convertBytesTo16Bit(data[10], data[9]);

		//fadeIn = this->convertBytesTo16Bit(data[8], data[9]);
		//fadeOut = this->convertBytesTo16Bit(data[10], data[11]);

		startValue = start << 7;
		holdValue = hold << 7;
		endValue = end << 7;


		result = true;
	}

	return result;
}

#ifdef DEBUG
void ControlChangeFadeToggle8Bit::printContents(){
	String result = String("Control Change Fade 8Bit \n");
	result += (String)"MIDI Channel : " + channel + "\n";
	result += (String)"Toggle Option: " + toggleOption + "\n";
	result += (String)"CC number    : " + controlChangeNumber + "\n";
	result += (String)"Start        : " + start + "\n";
	result += (String)"Hold         : " + hold + "\n";
	result += (String)"End          : " + end + "\n";
	result += (String)"FadeIn       : " + fadeIn + "\n";
	result += (String)"FadeOut      : " + fadeOut + "\n";
	result += (String)"Parameter    : " + parameter + "\n";
	result += (String)"Enabled      : " + enabled + "\n";
	result += (String)"LedPin       : " + ledPin + "\n";

	Serial.println(result);
}
#endif /* DEBUG */
