/*
 * PitchBendCommand.h
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#ifndef SRC_COMMAND_PITCHBENDCOMMAND_H_
#define SRC_COMMAND_PITCHBENDCOMMAND_H_

#include "Command.h"
#include "Arduino.h"

class PitchBendCommand : public Command {
public:
	PitchBendCommand(const uint8_t channel,
					 const uint16_t pbValue);

	virtual ~PitchBendCommand();

	void operator ()() const;

private:
	PitchBendCommand();
	PitchBendCommand(const PitchBendCommand&);
	PitchBendCommand& operator=(const PitchBendCommand&);

	uint8_t channel;
	uint16_t pbValue;
};

#endif /* SRC_COMMAND_PITCHBENDCOMMAND_H_ */
