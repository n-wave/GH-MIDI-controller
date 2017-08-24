/*
 * PitchBendNote.h
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_PITCHBENDNOTE_H_
#define SRC_CONTROLLER_PITCHBENDNOTE_H_

#include "../controller.h"


class PitchBendNote : public Controller {
public:
	PitchBendNote();
	PitchBendNote(const int* data);
	PitchBendNote(const int* data, Dispatcher* dispatcher);

    ~PitchBendNote();

    void update(const uint32_t* time);

    void setParameter(const uint16_t* value);
    uint16_t getParameter();
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
    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_PITCHBENDNOTE_H_ */
