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
	~NoteVelocity();

    void execute();
    void update(const uint32_t* time);

    void setParameter(const uint16_t* value);
    uint16_t getParameter();
    void setConfiguration(const int* data);

private:

};

#endif /* SRC_CONTROLLER_NOTEVELOCITY_H_ */
