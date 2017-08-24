/*
 * ControlChangeFadeToggle16Bit.h
 *
 *  Created on: Aug 23, 2017
 *      Author: mario
 */

#ifndef SRC_CONTROLLER_CONTROLCHANGEFADETOGGLE16BIT_H_
#define SRC_CONTROLLER_CONTROLCHANGEFADETOGGLE16BIT_H_

#include "../controller.h"

class ControlChangeFadeToggle16Bit: public Controller {
public:
	ControlChangeFadeToggle16Bit();
	ControlChangeFadeToggle16Bit(const int* data);
	ControlChangeFadeToggle16Bit(const int* data, Dispatcher* dispatcher);
	ControlChangeFadeToggle16Bit(const int* data, uint8_t ledPin, Dispatcher* dispatcher);

	~ControlChangeFadeToggle16Bit();

	void update(const uint32_t* time);
	void setParameter(const uint16_t* value);
	uint16_t getParameter();
	boolean setConfiguration(const int* data);

#ifdef DEBUG
    void printContents();
#endif /* DEBUG */

private:
    uint16_t convertBytesTo14Bit(uint8_t msb, uint8_t lsb);
    uint16_t convertBytesTo16Bit(uint8_t msb, uint8_t lsb);

    const uint8_t ID = 0xEA;
    uint8_t toggleOption;
    uint8_t channel;
    uint8_t controlChangeNumberMSB;
    uint8_t controlChangeNumberLSB;
    uint16_t start;
    uint16_t hold;
    uint16_t end;
    uint16_t fadeIn;
    uint16_t fadeOut;

    uint16_t parameter;
    boolean enabled;
    uint8_t ledPin;

    Dispatcher* dispatcher;
};

#endif /* SRC_CONTROLLER_CONTROLCHANGEFADETOGGLE16BIT_H_ */
