/*
 * ControlChangeFadeSwitch16Bit.h
 *
 *  Created on: Aug 24, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_SWITCH_CONTROLCHANGEFADESWITCH16BIT_H_
#define SRC_CONTROLLER_SWITCH_CONTROLCHANGEFADESWITCH16BIT_H_

#include "../common/controller.h"
#include "../../testing/configuration.h"

class ControlChangeFadeSwitch16Bit: public Controller {
public:
	ControlChangeFadeSwitch16Bit();
	ControlChangeFadeSwitch16Bit(const int* data);
	ControlChangeFadeSwitch16Bit(const int* data, Dispatcher* dispatcher);

	virtual ~ControlChangeFadeSwitch16Bit();

    void update(const uint32_t* time);

    void setParameter(const uint16_t* value);
    uint16_t getParameter();
    boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */


private:
    typedef void(ControlChangeFadeSwitch16Bit::*MethodPointer)();

    void sendOutHoldValue();
    void sendOutEndValue();

    void fadeInIncrement();
    void fadeOutIncrement();

    void fadeInDecrement();
    void fadeOutDecrement();

    uint16_t convertBytesTo14Bit(uint8_t msb, uint8_t lsb);
    uint16_t convertBytesTo16Bit(uint8_t msb, uint8_t lsb);

    const uint8_t ID = 0xE6;
    uint8_t channel;
    uint8_t controlChangeNumberMSB;
    uint8_t controlChangeNumberLSB;

    uint16_t start;
    uint8_t startMSB;
    uint8_t startLSB;

    uint16_t hold;	//leave in for the check in decrement functions
    uint8_t holdMSB;
    uint8_t holdLSB;

    uint16_t end;	//leave in for the check in decrement functions
    uint8_t endMSB;
    uint8_t endLSB;

    uint16_t fadeIn;
    uint16_t fadeOut;

    uint16_t parameter;

    boolean fadeInEnabled;
    boolean fadeOutEnabled;

    uint32_t currentValue;
    uint32_t fadeInStepSize;
    uint32_t fadeOutTimeConstant;
    uint32_t fadeOutStepSize;

    uint8_t endModus;
    uint8_t state;

    Dispatcher* dispatcher;
    MethodPointer methodPointerArray[3];
};

#endif /* SRC_CONTROLLER_SWITCH_CONTROLCHANGEFADESWITCH16BIT_H_ */
