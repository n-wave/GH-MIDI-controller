/*
 * AllNotesOffCommand.h
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#ifndef SRC_COMMAND_ALLNOTESOFFCOMMAND_H_
#define SRC_COMMAND_ALLNOTESOFFCOMMAND_H_

#include "Command.h"
#include "Arduino.h"

class AllNotesOffCommand: public Command {
public:
	AllNotesOffCommand();
    ~AllNotesOffCommand();

    void operator ()() const;
private:
    uint8_t channel;
    uint8_t ccNumber;
    uint8_t ccValue;
};

#endif /* SRC_COMMAND_ALLNOTESOFFCOMMAND_H_ */
