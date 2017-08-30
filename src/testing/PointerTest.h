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
#include "configuration.h"

#include "../controller/includeControllers.h"

class PointerTest {
public:
	PointerTest();
   ~PointerTest();

#ifdef DEBUG
   void printContents(int option);
#endif

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
