/*
 * ControlChangeFadeSwitch8Bit.h
 *
 *  Created on: Aug 24, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_SWITCH_CONTROLCHANGEFADESWITCH8BIT_H_
#define SRC_CONTROLLER_SWITCH_CONTROLCHANGEFADESWITCH8BIT_H_

#include "../controller.h"

class ControlChangeFadeSwitch8Bit {
public:
	ControlChangeFadeSwitch8Bit();
	ControlChangeFadeSwitch8Bit(const int* data);
	ControlChangeFadeSwitch8Bit(const int* data, Dispatcher* dispatcher);

	~ControlChangeFadeSwitch8Bit();

    void update(const uint32_t* time);

    void setParameter(const uint16_t* value);
    uint16_t getParameter();
    boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */

private:
    uint16_t convertBytesTo16Bit(uint8_t msb, uint8_t lsb);

    const uint8_t ID = 0xE6;
    uint8_t channel;
    uint8_t controlChangeNumber;
    uint8_t start;
    uint8_t hold;
    uint8_t end;
    uint16_t fadeIn;
    uint16_t fadeOut;

    uint16_t parameter;

    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_SWITCH_CONTROLCHANGEFADESWITCH8BIT_H_ */
