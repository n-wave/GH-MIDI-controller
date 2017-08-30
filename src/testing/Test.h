/*
 * Test.h
 *
 *  Created on: Jul 6, 2017
 *      Author: mario
 */

#ifndef SRC_TESTING_TEST_H_
#define SRC_TESTING_TEST_H_

#include "Arduino.h"
#include "configuration.h"

#include "../controller/includeControllers.h"

class Test {
public:
	Test();
    ~Test();

    void printContents(int option);

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

    ProgramChange programChange;
    PitchBendNoteRibbon pitchBendNote;
    PitchBendRibbon pitchBend;
    NoteVelocityPressure noteVelocity;
    NoteControlChangePressure8Bit noteControlChange8Bit;
    NoteControlChangePressure16Bit noteControlChange16Bit;
    ControlChangeFadePressure8Bit controlChangeFade8Bit;
    ControlChangeFadePressure16Bit controlChangeFade16Bit;
    ControlChangePressure8Bit controlChange8Bit;
    ControlChangePressure16Bit controlChange16Bit;


};

#endif /* SRC_TESTING_TEST_H_ */
