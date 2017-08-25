/*
 * PointerTest.cpp
 *
 *  Created on: Jul 6, 2017
 *      Author: mario
 */

#include "PointerTest.h"

PointerTest::PointerTest() {
	// TODO Auto-generated constructor stub
	this->initialize();
}

PointerTest::~PointerTest() {
	for(int i=0; i<NROFOBJECTS; i++){
		delete controllers[i];
		controllers[i] = NULL;
	}
}


void PointerTest::initialize(){

	for(int i=0; i<NROFOBJECTS; i++){
		controllers[i] = NULL;
	}

	controllers[0] = new ProgramChange();
	controllers[1] = new PitchBendNoteRibbon();
	controllers[2] = new PitchBendRibbon();
	controllers[3] = new NoteVelocity();
	controllers[4] = new NoteControlChange8Bit();
	controllers[5] = new NoteControlChange16Bit();
	controllers[6] = new ControlChangeFade8Bit();
	controllers[7] = new ControlChangeFade16Bit();
	controllers[8] = new ControlChange8Bit();
	controllers[9] = new ControlChange16Bit();

	this->initializeProgramChange();
	this->initializePitchBendNote();
	this->initializePitchBend();
	this->initializeNoteVelocity();
	this->initializeNoteControlChange8Bit();
	this->initializeNoteControlChange16Bit();
	this->initializeControlChangeFade8Bit();
	this->initializeControlChangeFade16Bit();
	this->initializeControlChange8Bit();
	this->initializeControlChange16Bit();
}

#ifdef DEBUG
void PointerTest::printContents(int option){
	switch(option){
		case 0:
			controllers[0]->printContents();
			break;
		case 1:
			controllers[1]->printContents();
			break;
		case 2:
			controllers[2]->printContents();
			break;
		case 3:
			controllers[3]->printContents();
			break;
		case 4:
			controllers[4]->printContents();
			break;
		case 5:
			controllers[5]->printContents();
			break;
		case 6:
			controllers[6]->printContents();
			break;
		case 7:
			controllers[7]->printContents();
			break;
		case 8:
			controllers[8]->printContents();
			break;
		case 9:
			controllers[9]->printContents();
			break;
		default:
			Serial.println("Option out of range");
			break;
	}


}
#endif /* DEBUG */

void PointerTest::initializeProgramChange(){
	const int data[] = {
						0xF0, //0 Start Byte
						0xE0, //1 Option ID
						0x01, //2 Channel
						0x02, //3 Bank
						0x03, //4 program
						0xFF  //5 End Byte
					   };

	if(controllers[0] != NULL){
		if(controllers[0]->setConfiguration(data)){
			Serial.println("Successfully loaded configuration data in ProgramChange Object");
		} else {
			Serial.println("Supplied wrong configuration data to ProgramChange Object");
		}
	} else {
		Serial.println("ProgramChange Object has not been initialized");
	}
}

void PointerTest::initializePitchBendNote(){
	const int data[] = {
						0xF0, //0 Start Byte
						0xE4, //1 Option ID
						0x02, //2 Channel
						0x03, //3 Pitch
						0x04, //4 Velocity
						0xFF  //5 End
					   };

	if(controllers[1] != NULL){
		if(controllers[1]->setConfiguration(data)){
			Serial.println("Successfully loaded configuration data in PitchBendNote Object");
		} else {
			Serial.println("Supplied wrong configuration data to PitchBendNote Object");
		}
	} else {
		Serial.println("PitchBendNote Object has not been initialized");
	}
}

void PointerTest::initializePitchBend(){
	const int data[] = {
						0xF0, //0 Start Byte
						0xE3, //1 Option Id
						0x03, //2 Channel
						0xFF  //3 End
					   };

	if(controllers[2] != NULL){
		if(controllers[2]->setConfiguration(data)){
			Serial.println("Successfully loaded configuration data in PitchBend Object");
		} else {
			Serial.println("Supplied wrong configuration data to PitchBend Object");
		}
	} else {
		Serial.println("PitchBend Object has not been initialized");
	}
}

void PointerTest::initializeNoteVelocity(){
	const int data[] = {
						0xF0, //0 Start Byte
						0xE1, //1 Option ID
						0x05, //2 Channel
						0x04, //3 Pitch
						0x05, //4 Velocity
						0x00, //5 Velocity Option
						0xFF  //6 End Byte
					   };

	if(controllers[3] != NULL){
		if(controllers[3]->setConfiguration(data)){
			Serial.println("Successfully loaded configuration data in NoteVelocity Object");
		} else {
			Serial.println("Supplied wrong configuration data to NoteVelocity Object");
		}
	} else {
		Serial.println("NoteVelocity Object has not been initialized");
	}
}

void PointerTest::initializeNoteControlChange8Bit(){
	const int data[] = {
						0xF0, //0 Start Byte
						0xE2, //1 Option ID
						0x05, //2 MIDI Channel
						0x06, //3 Pitch
						0x07, //4 Velocity
						0x00, //5 Velocity Option
						0x00, //6 Resolution Option
						0x07, //7 Control Change Option
						0x08, //8 Top Value
						0x09, //9 Bottom Value
						0xFF  //10 End Byte
					   };


	if(controllers[4] != NULL){
		if(controllers[4]->setConfiguration(data)){
			Serial.println("Successfully loaded configuration data in NoteControlChange8Bit Object");
		} else {
			Serial.println("Supplied wrong configuration data to NoteControlChange8Bit Object");
		}
	} else {
		Serial.println("NoteControlChange8Bit Object has not been initialized");
	}
}

void PointerTest::initializeNoteControlChange16Bit(){
	const int data[] = {
						0xF0, //0 Start Byte
						0xE2, //1 Option ID
						0x05, //2 MIDI Channel
						0x06, //3 Pitch
						0x08, //4 Velocity
						0x00, //5 Velocity Option
						0x01, //6 Resolution Option
						0x07, //7 Control Change Number
						0x00, //8 Top Value MSB
						0x7F, //9 Top Value LSB
						0x7F, //10 Bottom Value
						0x7F, //11 Bottom Value
						0xFF  //12 End Byte
					   };

	if(controllers[5] != NULL){
		if(controllers[5]->setConfiguration(data)){
			Serial.println("Successfully loaded configuration data in NoteControlChange16Bit Object");
		} else {
			Serial.println("Supplied wrong configuration data to NoteControlChange16Bit Object");
		}
	} else {
		Serial.println("NoteControlChange16Bit Object has not been initialized");
	}
}

void PointerTest::initializeControlChangeFade8Bit(){
	const int data[] = {
						0xF0, //0 Start Byte
						0xE6, //1 Option ID
						0x06, //2 Channel
						0x00, //3 Resolution
						0x07, //4 Control Change Number
						0x08, //5 Start
						0x09, //6 Hold
						0x0A, //7 End
						0x07, //8 Fade in MSB
						0x00, //9 Fade in LSB
						0x00, //10 Fade Out MSB
						0xFF, //11 Fade Out LSB
						0xFF  //12 End Byte
					   };
	if(controllers[6] != NULL){
		if(controllers[6]->setConfiguration(data)){
			Serial.println("Successfully loaded configuration data in ControlChangeFade8Bit Object");
		} else {
			Serial.println("Supplied wrong configuration data to ControlChangeFade8Bit Object");
		}
	} else {
		Serial.println("ControlChangeFade8Bit Object has not been initialized");
	}
}

void PointerTest::initializeControlChangeFade16Bit(){
	const int data[] = {
						0xF0, //0 Start Byte
						0xE6, //1 Option ID
						0x06, //2 Channel
						0x01, //3 Resolution
						0x08, //4 Control Change Number
						0x00, //5 Start MSB
						0x00, //6 Start LSB
						0x00, //7 Hold MSB
						0x7F, //8 Hold LSB
						0x7F, //9 End MSB
						0x7F, //10 End LSB
						0x00, //11 Fade In MSB
						0xFF, //12 Fade in LSB
						0x07, //13 Fade Out MSB
						0xFF, //14 Fade out LSB
						0xFF  //15 End Byte
					   };

	if(controllers[7] != NULL){
		if(controllers[7]->setConfiguration(data)){
			Serial.println("Successfully loaded configuration data in ControlChangeFade16Bit Object");
		} else {
			Serial.println("Supplied wrong configuration data to ControlChangeFade16Bit Object");
		}
	} else {
		Serial.println("ControlChangeFade16Bit Object has not been initialized");
	}
}

void PointerTest::initializeControlChange8Bit(){
	const int data[] = {
						0xF0, //0 Start Byte
						0xE5, //1 Option Id
						0x07, //2 Channel
						0x00, //3 Resolution
						0x09, //4 Control Change NR
						0x0A, //5 TopValue
						0x7F, //6 Bottom Value
						0xFF  //7 End Byte
					   };

	if(controllers[8] != NULL){
		if(controllers[8]->setConfiguration(data)){
			Serial.println("Successfully loaded configuration data in ControlChange8Bit Object");
		} else {
			Serial.println("Supplied wrong configuration data to ControlChange8Bit Object");
		}
	} else {
		Serial.println("ControlChange8Bit Object has not been initialized");
	}
}

void PointerTest::initializeControlChange16Bit(){
	const int data[] = {
						0xF0, //0 Start Byte
						0xE5, //1 Option Id
						0x07, //2 Channel
						0x01, //3 Resolution
						0x09, //4 Control Change NR
						0x00, //5 TopValue MSB
						0x7F, //6 TopValue LSB
						0x7F, //7 Bottom Value MSB
						0x7F, //8 Bottom Value LSB
						0xFF  //9 End Byte
					   };

	if(controllers[9] != NULL){
		if(controllers[9]->setConfiguration(data)){
			Serial.println("Successfully loaded configuration data in ControlChange16Bit Object");
		} else {
			Serial.println("Supplied wrong configuration data to ControlChange16Bit Object");
		}
	} else {
		Serial.println("ControlChange16Bit Object has not been initialized");
	}
}
