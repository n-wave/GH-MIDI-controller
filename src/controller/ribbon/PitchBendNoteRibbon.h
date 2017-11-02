/*
 * PitchBendNote.h
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_PITCHBENDNOTE_H_
#define SRC_CONTROLLER_PITCHBENDNOTE_H_

#include "../common/controller.h"


class PitchBendNoteRibbon : public Controller {
public:
	PitchBendNoteRibbon();
	PitchBendNoteRibbon(const int* data);
	PitchBendNoteRibbon(const int* data, Dispatcher* dispatcher);

    ~PitchBendNoteRibbon();

    void update();

    void setParameter(const uint16_t* value);
    boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */

private:
    const uint8_t ID = 0xE4;
    uint8_t channel;
    uint8_t pitch;
    uint8_t velocity;

    uint16_t parameter;

    boolean updated;
    boolean sendNote;

    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_PITCHBENDNOTE_H_ */
