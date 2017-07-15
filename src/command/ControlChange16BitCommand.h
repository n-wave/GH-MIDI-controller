/*
 * ControlChange16BitCommand.h
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#ifndef SRC_COMMAND_CONTROLCHANGE16BITCOMMAND_H_
#define SRC_COMMAND_CONTROLCHANGE16BITCOMMAND_H_

#include "Command.h"
#include "Arduino.h"

class ControlChange16BitCommand: public Command {
public:
	ControlChange16BitCommand(const uint8_t& channel,
							  const uint8_t& ccNumberMSB,
							  const uint8_t& ccValueMSB,
							  const uint8_t& ccNumberLSB,
							  const uint8_t& ccValueLSB);

	~ControlChange16BitCommand();

	void operator ()() const;
private:
	ControlChange16BitCommand();
	ControlChange16BitCommand(const ControlChange16BitCommand&);
	ControlChange16BitCommand& operator=(const ControlChange16BitCommand&);

	uint8_t channel;
	uint8_t ccNumberMSB;
	uint8_t ccValueMSB;
	uint8_t ccNumberLSB;
	uint8_t ccValueLSB;
};

#endif /* SRC_COMMAND_CONTROLCHANGE16BITCOMMAND_H_ */
