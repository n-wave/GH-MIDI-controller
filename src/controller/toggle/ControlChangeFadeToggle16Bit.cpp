/*
 * ControlChangeFadeToggle16Bit.cpp
 *
 *  Created on: Aug 23, 2017
 *      Author: mario
 */

#include "ControlChangeFadeToggle16Bit.h"
#include "../../command/ControlChange16BitCommand.h"

ControlChangeFadeToggle16Bit::ControlChangeFadeToggle16Bit() :
	toggleOption(0),
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
	toggle(0),
	fadeInEnabled(false),
	fadeOutEnabled(false),
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

	for(int i=0; i<3; i++){
		methodPointerArray[i] = NULL;
	}

}

ControlChangeFadeToggle16Bit::ControlChangeFadeToggle16Bit(const int* data) :
	toggleOption(0),
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
	toggle(0),
	fadeInEnabled(false),
	fadeOutEnabled(false),
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

	for(int i=0; i<3; i++){
		methodPointerArray[i] = NULL;
	}

#ifdef DEBUG
	boolean success = this->setConfiguration(data);

	if(success){
		Serial.println("ControlChangeFade16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeFade16Bit::ControlChangeFadeToggle16Bit(const int*) while loading data");
	}
#endif /* DEBUG */
}

ControlChangeFadeToggle16Bit::ControlChangeFadeToggle16Bit(const int* data, Dispatcher* dispatcher) :
	toggleOption(0),
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
	toggle(0),
	fadeInEnabled(false),
	fadeOutEnabled(false),
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


	for(int i=0; i<3; i++){
		methodPointerArray[i] = NULL;
	}

#ifdef DEBUG
	boolean success = this->setConfiguration(data);

	if(success){
		Serial.println("ControlChangeFade16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeFade16Bit::ControlChangeFadeToggle16Bit(const int*, Dispatcher*) while loading data");
	}
#endif /* DEBUG */
}

ControlChangeFadeToggle16Bit::ControlChangeFadeToggle16Bit(const int* data, uint8_t ledPin, Dispatcher* dispatcher) :
	toggleOption(0),
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
	toggle(0),
	fadeInEnabled(false),
	fadeOutEnabled(false),
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
				currentValue = start;

				if(start < hold){
					fadeInStepSize = ((hold-start)*1000)/(SAMPLERATE * fadeIn);
					noInterrupts();
					methodPointerArray[0] = &ControlChangeFadeToggle16Bit::fadeInIncrement;
					interrupts();
				} else if(start > hold){
					fadeInStepSize = ((start-hold)*1000)/(SAMPLERATE*fadeIn);

					noInterrupts();
					methodPointerArray[0] = &ControlChangeFadeToggle16Bit::fadeInDecrement;
					interrupts();
				}
			} else if(fadeIn < 20){
				noInterrupts();
				methodPointerArray[0] = &ControlChangeFadeToggle16Bit::sendOutHoldValue;
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
					methodPointerArray[1] = &ControlChangeFadeToggle16Bit::fadeOutDecrement;
					methodPointerArray[2] = &ControlChangeFadeToggle16Bit::fadeOutIncrement;
					interrupts();
				} else if(fadeOut < 20){
					endModus = 0;

					noInterrupts();
					methodPointerArray[1] = &ControlChangeFadeToggle16Bit::sendOutEndValue;
					methodPointerArray[2] = &ControlChangeFadeToggle16Bit::sendOutEndValue;
					interrupts();
			}
		}


#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeFade16Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeFade16Bit::ControlChangeFadeToggle16Bit(const int*, uint8_t, Dispatcher*) while loading data");
	}
#endif /* DEBUG */
}

ControlChangeFadeToggle16Bit::~ControlChangeFadeToggle16Bit() {
	for(int i=0; i<3; i++){
		methodPointerArray[i] = NULL;
	}
	dispatcher = NULL;
}

void ControlChangeFadeToggle16Bit::update(const uint32_t* time) {
	if(methodPointerArray[state] != NULL){
		(this->*methodPointerArray[state])();
	}
}

void ControlChangeFadeToggle16Bit::setParameter(const uint16_t* value){
	if(parameter != *value){
		updated = false;
		parameter = *value;

		if(toggleOption == 1){
			 /*
			  * updated =  high when toggle is updated
			  *
			  * Needed the Extra check for circumventing
			  * the extra value that otherwise would be
			  * sent to the USB port
			  *
			  */

			if(parameter > 0){
				toggle = !toggle;
				updated = true;
			}
		} else {
			toggle = parameter;
			updated = true;
		}

		if(updated == true){
			if(toggle == 1){
				state = 0;
				fadeInEnabled = true;
				fadeOutEnabled = false;
				currentValue = start;
			}

			if(toggle == 0){
				if(endModus != 0){
					if(end < currentValue && state != 1){
						fadeOutStepSize = ((currentValue-end)*1000)/fadeOutTimeConstant;
						state = 1;
					}

					if(end > currentValue && state != 2){
						fadeOutStepSize = ((end-currentValue)*1000)/fadeOutTimeConstant;
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

void ControlChangeFadeToggle16Bit::fadeInIncrement(){
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

void ControlChangeFadeToggle16Bit::fadeOutIncrement(){
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

void ControlChangeFadeToggle16Bit::fadeInDecrement(){
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

void ControlChangeFadeToggle16Bit::fadeOutDecrement(){
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

void ControlChangeFadeToggle16Bit::sendOutHoldValue(){
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

void ControlChangeFadeToggle16Bit::sendOutEndValue(){
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

uint16_t ControlChangeFadeToggle16Bit::getParameter(){
	return parameter;
}

boolean ControlChangeFadeToggle16Bit::setConfiguration(const int* data) {
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		(data[3] == 0x01 || data[3] == 0x03) &&
		data[15] == 0xFF
	  )
	{
		channel = data[2];
		toggleOption = (data[3] & 0B00000010) >> 1;
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

uint16_t ControlChangeFadeToggle16Bit::convertBytesTo14Bit(uint8_t msb, uint8_t lsb){
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

uint16_t ControlChangeFadeToggle16Bit::convertBytesTo16Bit(uint8_t msb, uint8_t lsb){
	uint16_t result = 0;
	uint16_t MSB = (msb & 0xFF) << 8;
	uint16_t LSB = lsb & 0xFF;

	result = MSB | LSB;

	return result;
}

#ifdef DEBUG
    void ControlChangeFadeToggle16Bit::printContents(){
    	String result = String("Control Change Fade 16 Bit \n");
    	result == (String)"Toggle Option: " + toggleOption + "\n";
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"CC number msb: " + controlChangeNumberMSB + "\n";
    	result += (String)"CC number lsb: " + controlChangeNumberLSB + "\n";
    	result += (String)"Start        : " + start + "\n";
    	result += (String)"Hold         : " + hold + "\n";
    	result += (String)"End          : " + end + "\n";
    	result += (String)"FadeIn       : " + fadeIn + "\n";
    	result += (String)"Fadeout      : " + fadeOut + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";

    	result += (String)"Enabled      : " + enabled + "\n";
    	result += (String)"Ledpin       : " + ledPin + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */
