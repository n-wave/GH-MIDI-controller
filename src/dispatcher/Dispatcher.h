/*
 * Dispatcher.h
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#ifndef SRC_DISPATCHER_DISPATCHER_H_
#define SRC_DISPATCHER_DISPATCHER_H_

#include "../command/Command.h"

class Dispatcher {
public:
	Dispatcher();
    ~Dispatcher();

    void addCommand(Command* command);
    void dispatch();
    void clearBuffer();

private:
    enum {MAXITEMS = 32};

	int index;
	Command* buffer[MAXITEMS];
};

#endif /* SRC_DISPATCHER_DISPATCHER_H_ */
