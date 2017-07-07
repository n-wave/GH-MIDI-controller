/*
 * NoteVelocity.h
 *
 *  Created on: Jul 4, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_NOTEVELOCITY_H_
#define SRC_CONTROLLER_NOTEVELOCITY_H_

#include "controller.h"

class NoteVelocity : public Controller {
public:
	NoteVelocity();
	NoteVelocity(const int* data);
	~NoteVelocity();

    void execute();
    void update(const uint32_t* time);

    void setParameter(const uint16_t* value);
    uint16_t getParameter();
    boolean setConfiguration(const int* data);

#ifdef DEBUG
    String toString();
#endif /* DEBUG */


private:
    const uint8_t id = 0xE1;
    uint8_t channel;
    uint8_t pitch;
    uint8_t velocity;
    uint8_t velocityOption;

    uint16_t parameter;
};

#endif /* SRC_CONTROLLER_NOTEVELOCITY_H_ */
