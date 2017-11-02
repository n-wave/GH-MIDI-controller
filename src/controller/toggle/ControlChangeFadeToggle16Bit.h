/*
 * ControlChangeFadeToggle16Bit.h
 *
 *  Created on: Aug 23, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_CONTROLCHANGEFADETOGGLE16BIT_H_
#define SRC_CONTROLLER_CONTROLCHANGEFADETOGGLE16BIT_H_

#include "../common/controller.h"

class ControlChangeFadeToggle16Bit: public Controller {
public:
	ControlChangeFadeToggle16Bit();
	ControlChangeFadeToggle16Bit(const int* data);
	ControlChangeFadeToggle16Bit(const int* data, Dispatcher* dispatcher);
	ControlChangeFadeToggle16Bit(const int* data, uint8_t ledPin, Dispatcher* dispatcher);

	~ControlChangeFadeToggle16Bit();

	void update();
	void setParameter(const uint16_t* value);
	boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */

private:

    typedef void(ControlChangeFadeToggle16Bit::*MethodPointer)();

    void sendOutHoldValue();
    void sendOutEndValue();

    void fadeInIncrement();
    void fadeOutIncrement();
    void fadeInDecrement();
    void fadeOutDecrement();

    const uint8_t ID = 0xEA;
    uint8_t toggleOption;
    uint8_t channel;
    uint8_t controlChangeNumberMSB;
    uint8_t controlChangeNumberLSB;

    uint16_t start;
    uint8_t startMSB;
    uint8_t startLSB;

    uint16_t hold;
    uint8_t holdMSB;
    uint8_t holdLSB;

    uint16_t end;
    uint8_t endMSB;
    uint8_t endLSB;

    uint16_t fadeIn;
    uint16_t fadeOut;

    uint16_t parameter;
    boolean toggle;
    boolean fadeInEnabled;
    boolean fadeOutEnabled;

    uint32_t currentValue;
    uint32_t fadeInStepSize;
    uint32_t fadeOutTimeConstant;
    uint32_t fadeOutStepSize;

    uint8_t endModus;
    uint8_t state;

    uint8_t ledPin;
    boolean updated;

    Dispatcher* dispatcher;
    MethodPointer methodPointerArray[3];
};

#endif /* SRC_CONTROLLER_CONTROLCHANGEFADETOGGLE16BIT_H_ */
