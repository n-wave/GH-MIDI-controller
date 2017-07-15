/*
 * NoteControlChange8BitCommand.h
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#ifndef SRC_COMMAND_NOTECONTROLCHANGE8BITCOMMAND_H_
#define SRC_COMMAND_NOTECONTROLCHANGE8BITCOMMAND_H_

#include "Command.h"
#include "Arduino.h"

class NoteControlChange8BitCommand: public Command {
public:
	NoteControlChange8BitCommand(const uint8_t& channel,
								 const uint8_t& pitch,
								 const uint8_t& velocity,
								 const uint8_t& ccNumber,
								 const uint8_t& ccValue);

	~NoteControlChange8BitCommand();

	void operator ()() const;

private:
	NoteControlChange8BitCommand();
	NoteControlChange8BitCommand(const NoteControlChange8BitCommand&);
	NoteControlChange8BitCommand& operator=(const NoteControlChange8BitCommand&);

	uint8_t channel;
	uint8_t pitch;
	uint8_t velocity;
	uint8_t ccNumber;
	uint8_t ccValue;
};

#endif /* SRC_COMMAND_NOTECONTROLCHANGE8BITCOMMAND_H_ */
