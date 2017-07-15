/*
 * ProgramChangeCommand.h
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#ifndef SRC_COMMAND_PROGRAMCHANGECOMMAND_H_
#define SRC_COMMAND_PROGRAMCHANGECOMMAND_H_

#include "Command.h"
#include "Arduino.h"

class ProgramChangeCommand : public Command {
public:
	ProgramChangeCommand(const uint8_t& channel,
						 const uint8_t& bank,
						 const uint8_t& program);

	~ProgramChangeCommand();

	void operator ()() const;

private:
	ProgramChangeCommand();
	ProgramChangeCommand(const ProgramChangeCommand&);
	ProgramChangeCommand& operator=(const ProgramChangeCommand&);

	uint8_t channel;
	uint8_t bank;
	uint8_t program;
};

#endif /* SRC_COMMAND_PROGRAMCHANGECOMMAND_H_ */
