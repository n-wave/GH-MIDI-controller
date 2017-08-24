/*
 * ProgramChange.h
 *
 *  Created on: Jul 4, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_PROGRAMCHANGE_H_
#define SRC_CONTROLLER_PROGRAMCHANGE_H_

#include "controller.h"

class ProgramChange : public Controller {
public:
	ProgramChange();
	ProgramChange(const int* data);
	ProgramChange(const int* data, Dispatcher* dispatcher);

    ~ProgramChange();

    void update(const uint32_t* time);

    void setParameter(const uint16_t* value);
    uint16_t getParameter();

    boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */

private:
    const uint8_t ID = 0xE0;
    uint8_t channel;
    uint8_t bank;
    uint8_t program;

    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_PROGRAMCHANGE_H_ */
