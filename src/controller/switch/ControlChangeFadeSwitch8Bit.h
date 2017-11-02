/*
 * ControlChangeFadeSwitch8Bit.h
 *
 *  Created on: Aug 24, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_SWITCH_CONTROLCHANGEFADESWITCH8BIT_H_
#define SRC_CONTROLLER_SWITCH_CONTROLCHANGEFADESWITCH8BIT_H_

#include "../common/controller.h"
#include "../../testing/configuration.h"

class ControlChangeFadeSwitch8Bit : public Controller {
public:
	ControlChangeFadeSwitch8Bit();
	ControlChangeFadeSwitch8Bit(const int* data);
	ControlChangeFadeSwitch8Bit(const int* data, Dispatcher* dispatcher);

	~ControlChangeFadeSwitch8Bit();

    void update();

    void setParameter(const uint16_t* value);

    boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */

private:
    typedef void(ControlChangeFadeSwitch8Bit::*MethodPointer)();

    void fadeInIncrement();
    void fadeInDecrement();

    void fadeOutIncrement();
    void fadeOutDecrement();

    void sendOutHoldValue();
    void sendOutEndValue();

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

    boolean fadeInEnabled;
    boolean fadeOutEnabled;

    /* Needed for comparison leave them, instead of recalculating */
    uint32_t startValue; // calculated start Value
    uint32_t holdValue;  //calculated hold value
    uint32_t endValue;   //calculated end Value

    uint32_t currentValue;
    uint32_t fadeInStepSize;
    uint32_t fadeOutTimeConstant;
    uint32_t fadeOutStepSize;

    uint8_t endModus;// (end < hold) ? true : false;
    uint8_t state;

    Dispatcher* dispatcher;
    MethodPointer methodPointerArray[3];

};

#endif /* SRC_CONTROLLER_SWITCH_CONTROLCHANGEFADESWITCH8BIT_H_ */
