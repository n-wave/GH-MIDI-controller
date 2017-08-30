/*
 * ProgramChangeSwitch.h
 *
 *  Created on: Aug 29, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_SWITCH_PROGRAMCHANGESWITCH_H_
#define SRC_CONTROLLER_SWITCH_PROGRAMCHANGESWITCH_H_

#include "../common/controller.h"

class ProgramChangeSwitch: public Controller {
public:
	ProgramChangeSwitch();
	ProgramChangeSwitch(const int* data);
	ProgramChangeSwitch(const int* data, Dispatcher* dispatcher);

    ~ProgramChangeSwitch();

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
    uint8_t parameter;

    boolean updated;

    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_SWITCH_PROGRAMCHANGESWITCH_H_ */
