/*
 * ControlChangeFadeToggle8Bit.h
 *
 *  Created on: Aug 23, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_CONTROLCHANGEFADETOGGLE8BIT_H_
#define SRC_CONTROLLER_CONTROLCHANGEFADETOGGLE8BIT_H_

#include "../common/controller.h"

class ControlChangeFadeToggle8Bit: public Controller {
public:
	ControlChangeFadeToggle8Bit();
	ControlChangeFadeToggle8Bit(const int* data);
	ControlChangeFadeToggle8Bit(const int* data, Dispatcher* dispatcher);
	ControlChangeFadeToggle8Bit(const int* data, uint8_t ledPin, Dispatcher* dispatcher);

	~ControlChangeFadeToggle8Bit();

	void update(const uint32_t* time);

	void setParameter(const uint16_t* value);
	uint16_t getParameter();

	boolean setConfiguration(const int* data);

#ifdef DEBUG
	void printContents();
#endif /*DEBUG */

private:
	typedef void(ControlChangeFadeToggle8Bit::*MethodPointer)();

    void sendOutHoldValue();
    void sendOutEndValue();
    void fadeInIncrement();
    void fadeInDecrement();
    void fadeOutIncrement();
    void fadeOutDecrement();

    const uint8_t ID = 0xEA;
    uint8_t toggleOption;
    uint8_t channel;
    uint8_t controlChangeNumber;
    uint16_t start;
    uint16_t hold;
    uint16_t end;
    uint16_t fadeIn;
    uint16_t fadeOut;

    uint16_t parameter;
    boolean toggle;
    boolean fadeInEnabled;
    boolean fadeOutEnabled;

    uint32_t startValue;
    uint32_t holdValue;
    uint32_t endValue;

    uint32_t currentValue;
    uint32_t fadeInStepSize;
    uint32_t fadeOutTimeConstant;
    uint32_t fadeOutStepSize;

    uint8_t endModus;
    uint8_t state;

    uint8_t ledPin;

    boolean updated = false;

    Dispatcher* dispatcher;
    MethodPointer methodPointerArray[3];
};

#endif /* SRC_CONTROLLER_CONTROLCHANGEFADETOGGLE8BIT_H_ */
