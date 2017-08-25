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
#include "../controller/sensor/NoteControlChange8Bit.h"
#include "../controller/sensor/NoteControlChange16Bit.h"
#include "../controller/sensor/ControlChangeFade8Bit.h"
#include "../controller/sensor/ControlChangeFade16Bit.h"
#include "../controller/sensor/ControlChange8Bit.h"
#include "../controller/sensor/ControlChange16Bit.h"
#include "../controller/controller.h"
#include "../controller/ribbon/PitchBendNoteRibbon.h"
#include "../controller/ribbon/PitchBendRibbon.h"
#include "../controller/sensor/NoteVelocity.h"

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
    NoteVelocity noteVelocity;
    NoteControlChange8Bit noteControlChange8Bit;
    NoteControlChange16Bit noteControlChange16Bit;
    ControlChangeFade8Bit controlChangeFade8Bit;
    ControlChangeFade16Bit controlChangeFade16Bit;
    ControlChange8Bit controlChange8Bit;
    ControlChange16Bit controlChange16Bit;


};

#endif /* SRC_TESTING_TEST_H_ */
