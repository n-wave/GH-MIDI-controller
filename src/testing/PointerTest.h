/*
 * Test.h
 *
 *  Created on: Jul 6, 2017
 *      Author: mario
 */

#ifndef SRC_TESTING_POINTERTEST_H_
#define SRC_TESTING_POINTERTEST_H_

#define NROFOBJECTS 10

#include "Arduino.h"

#include "../controller/controller.h"

#include "../controller/ProgramChange.h"
#include "../controller/PitchBendNote.h"
#include "../controller/PitchBend.h"
#include "../controller/NoteVelocity.h"
#include "../controller/NoteControlChange8Bit.h"
#include "../controller/NoteControlChange16Bit.h"
#include "../controller/ControlChangeFade8Bit.h"
#include "../controller/ControlChangeFade16Bit.h"
#include "../controller/ControlChange8Bit.h"
#include "../controller/ControlChange16Bit.h"

class PointerTest {
public:
	PointerTest();
   ~PointerTest();


   String getContents(int option);

private:
   void initialize();
   void initializeProgramChange();
   void initializePitchBendNote();
   void initializePitchBend();
   void initializeNoteVelocity();
   void initializeNoteControlChange8Bit();
   void initializeNoteControlChange16Bit();
   void initializeControlChangeFade8Bit();
   void initializeControlChangeFade16Bit();
   void initializeControlChange8Bit();
   void initializeControlChange16Bit();

   Controller* controllers[NROFOBJECTS];

};

#endif /* SRC_TESTING_POINTERTEST_H_ */
