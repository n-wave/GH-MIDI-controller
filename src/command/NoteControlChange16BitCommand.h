/*
 * NoteControlChange16BitCommand.h
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#ifndef SRC_COMMAND_NOTECONTROLCHANGE16BITCOMMAND_H_
#define SRC_COMMAND_NOTECONTROLCHANGE16BITCOMMAND_H_

#include "Command.h"
#include "Arduino.h"

class NoteControlChange16BitCommand : public Command{
public:
	NoteControlChange16BitCommand(const uint8_t& channel,
								  const uint8_t& pitch,
								  const uint8_t& velocity,
								  const uint8_t& ccNumberMSB,
								  const uint8_t& ccValueMSB,
								  const uint8_t& ccNumberLSB,
								  const uint8_t& ccValueLSB);

	~NoteControlChange16BitCommand();

	void operator ()() const;

private:
	NoteControlChange16BitCommand();
	NoteControlChange16BitCommand(const NoteControlChange16BitCommand&);
	NoteControlChange16BitCommand& operator=(const NoteControlChange16BitCommand&);

	uint8_t channel;
	uint8_t pitch;
	uint8_t velocity;
	uint8_t ccNumberMSB;
	uint8_t ccValueMSB;
	uint8_t ccNumberLSB;
	uint8_t ccValueLSB;
};

#endif /* SRC_COMMAND_NOTECONTROLCHANGE16BITCOMMAND_H_ */
