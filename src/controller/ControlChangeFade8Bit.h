/*
 * ControlChangeFade8Bit.h
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_CONTROLCHANGEFADE8BIT_H_
#define SRC_CONTROLLER_CONTROLCHANGEFADE8BIT_H_

#include "controller.h"

class ControlChangeFade8Bit : public Controller {
public:
	ControlChangeFade8Bit();
	~ControlChangeFade8Bit();

    void execute();
    void update(const uint32_t* time);

    void setParameter(const uint16_t* value);
    uint16_t getParameter();
    boolean setConfiguration(const int* data);

#ifdef DEBUG
    String toString();
#endif /* DEBUG */

private:
    uint16_t convertBytesTo16Bit(uint8_t msb, uint8_t lsb);

    const uint8_t id = 0xE6;
    uint8_t channel;
    uint8_t controlChangeNumber;
    uint8_t start;
    uint8_t hold;
    uint8_t end;
    uint16_t fadeIn;
    uint16_t fadeOut;

    uint16_t parameter;
};

#endif /* SRC_CONTROLLER_CONTROLCHANGEFADE8BIT_H_ */
