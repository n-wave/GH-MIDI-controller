/*
 * Command.h
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#ifndef SRC_COMMAND_COMMAND_H_
#define SRC_COMMAND_COMMAND_H_

class Command {
public:
	Command();

	virtual ~Command() = 0;
	virtual void operator ()() const = 0;

private:
	Command(const Command&);
	Command& operator=(const Command&);
};

#endif /* SRC_COMMAND_COMMAND_H_ */
