/*
 * DisabledController.h
 *
 *  Created on: Jul 12, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_DISABLEDCONTROLLER_H_
#define SRC_CONTROLLER_DISABLEDCONTROLLER_H_

#include "controller.h"

class DisabledController: public Controller {
public:
	DisabledController();
	DisabledController(const int* data);
	~DisabledController();

    void update();

    void setParameter(const uint16_t* value);
    boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */
    const uint8_t ID = 0xEF;
    uint16_t parameter;
};

#endif /* SRC_CONTROLLER_DISABLEDCONTROLLER_H_ */
