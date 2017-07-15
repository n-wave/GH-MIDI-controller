/*
 * ControlChange8BitCommand.h
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#ifndef SRC_COMMAND_CONTROLCHANGE8BITCOMMAND_H_
#define SRC_COMMAND_CONTROLCHANGE8BITCOMMAND_H_

#include "Command.h"
#include "Arduino.h"

class ControlChange8BitCommand: public Command {
public:
	ControlChange8BitCommand(const uint8_t& channel,
							 const uint8_t& ccNumber,
							 const uint8_t& ccValue);

	~ControlChange8BitCommand();

	void operator ()() const;
private:
	ControlChange8BitCommand();
	ControlChange8BitCommand(const ControlChange8BitCommand&);
	ControlChange8BitCommand& operator=(const ControlChange8BitCommand&);

	uint8_t channel;
	uint8_t ccNumber;
	uint8_t ccValue;

};

#endif /* SRC_COMMAND_CONTROLCHANGE8BITCOMMAND_H_ */
