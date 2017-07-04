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
    ~ProgramChange();

    void execute();
    void update(const uint32_t* time);

    void setParameter(const uint16_t* value);
    uint16_t getParameter();
    void setConfiguration(const int* data);
private:
};

#endif /* SRC_CONTROLLER_PROGRAMCHANGE_H_ */
