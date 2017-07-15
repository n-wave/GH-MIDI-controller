/*
 * NoteVelocityCommand.h
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#ifndef SRC_COMMAND_NOTEVELOCITYCOMMAND_H_
#define SRC_COMMAND_NOTEVELOCITYCOMMAND_H_

#include "Command.h"
#include "Arduino.h"

class NoteVelocityCommand : public Command {
public:
	NoteVelocityCommand(const uint8_t& channel,
						const uint8_t& pitch,
						const uint8_t& velocity);

    ~NoteVelocityCommand();

    void operator ()() const;

private:
	NoteVelocityCommand();
	NoteVelocityCommand(const NoteVelocityCommand&);
	NoteVelocityCommand& operator=(const NoteVelocityCommand&);

	uint8_t channel;
	uint8_t pitch;
	uint8_t velocity;
};

#endif /* SRC_COMMAND_NOTEVELOCITYCOMMAND_H_ */
