/*
 * PitchBendNoteCommand.h
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#ifndef SRC_COMMAND_PITCHBENDNOTECOMMAND_H_
#define SRC_COMMAND_PITCHBENDNOTECOMMAND_H_

#include "Command.h"
#include "Arduino.h"

class PitchBendNoteCommand: public Command {
public:
	PitchBendNoteCommand(const uint8_t& channel,
						 const uint8_t& pitch,
						 const uint8_t& velocity,
						 const uint16_t& pbValue);

	~PitchBendNoteCommand();

	void operator ()() const;
private:
	PitchBendNoteCommand();
	PitchBendNoteCommand(const PitchBendNoteCommand&);
	PitchBendNoteCommand& operator=(const PitchBendNoteCommand&);

	uint8_t channel;
	uint8_t pitch;
	uint8_t velocity;
	uint16_t pbValue;
};

#endif /* SRC_COMMAND_PITCHBENDNOTECOMMAND_H_ */
