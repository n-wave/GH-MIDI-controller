/*
 * Test.cpp
 *
 *  Created on: Jul 6, 2017
 *      Author: mario
 */

#include "Test.h"

Test::Test() {
	// TODO Auto-generated constructor stub

}

Test::~Test() {
	// TODO Auto-generated destructor stub
}

void Test::initialize(){

}

void Test::initializeProgramChange(){
	programChange = ProgramChange();

	const int data[] = {
						0xF0, //0 Start Byte
						0xE0, //1 Option ID
						0x01, //2 Channel
						0x02, //3 Bank
						0x03, //4 program
						0xFF  //5 End Byte
					   };

	programChange.setConfiguration(data);
}


void Test::initializePitchBendNote(){
	pitchBendNote = PitchBendNote();

	const int data[] = {
						0xF0, //0 Start Byte
						0xE4, //1 Option ID
						0x02, //2 Channel
						0x03, //3 Pitch
						0x04, //4 Velocity
						0xFF  //5 End
					   };

	pitchBendNote.setConfiguration(data);
}

void Test::initializePitchBend(){
	pitchBend = PitchBend();

	const int data[] = {
						0xF0, //0 Start Byte
						0xE3, //1 Option Id
						0x03, //2 Channel
						0xFF  //3 End
					   };
}
void Test::initializeNoteVelocity(){
	noteVelocity = NoteVelocity();

	const int data[] = {
						0xF0, //0 Start Byte
						0xE1, //1 Option ID
						0x04, //2 Pitch
						0x05, //3 Velocity
						0x00, //4 Velocity Option
						0xFF  //5 End Byte
					   };

	noteVelocity.setConfiguration(data);
}

void Test::initializeNoteControlChange8Bit(){
	noteControlChange8Bit = NoteControlChange8Bit();

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

	noteControlChange8Bit.setConfiguration(data);
}

void Test::initializeNoteControlChange16Bit(){
	noteControlChange16Bit = NoteControlChange16Bit();

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

	noteControlChange16Bit.setConfiguration(data);
}

void Test::initializeControlChangeFade8Bit(){
	controlChangeFade8Bit = ControlChangeFade8Bit();

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

	controlChangeFade8Bit.setConfiguration(data);
}

void Test::initializeControlChangeFade16Bit(){
	controlChangeFade16Bit = ControlChangeFade16Bit();

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
						0x7F, //14 Fade out LSB
						0xFF  //15 End Byte
					   };

	controlChangeFade16Bit.setConfiguration(data);
}

void Test::initializeControlChange8Bit(){
	controlChange8Bit = ControlChange8Bit();

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

	controlChange8Bit.setConfiguration(data);
}


void Test::initializeControlChange16Bit(){
	controlChange16Bit = ControlChange16Bit();

	const int data[] = {
						0xF0, //0 Start Byte
						0xE5, //1 Option Id
						0x07, //2 Channel
						0x00, //3 Resolution
						0x09, //4 Control Change NR
						0x00, //5 TopValue MSB
						0x7F, //6 TopValue LSB
						0x7F, //7 Bottom Value MSB
						0x7F, //8 Bottom Value LSB
						0xFF  //9 End Byte
					   };

	controlChange16Bit.setConfiguration(data);
}

