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
#include "../controller/controller.h"

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
    PitchBendNote pitchBendNote;
    PitchBend pitchBend;
    NoteVelocity noteVelocity;
    NoteControlChange8Bit noteControlChange8Bit;
    NoteControlChange16Bit noteControlChange16Bit;
    ControlChangeFade8Bit controlChangeFade8Bit;
    ControlChangeFade16Bit controlChangeFade16Bit;
    ControlChange8Bit controlChange8Bit;
    ControlChange16Bit controlChange16Bit;


};

#endif /* SRC_TESTING_TEST_H_ */
