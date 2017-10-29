/*
 * StateMachine.h
 *
 *  Created on: Oct 27, 2017
 *      Author: mario
 */

#ifndef SRC_STATE_STATEMACHINE_H_
#define SRC_STATE_STATEMACHINE_H_

#include "Arduino.h"
#include "../serial/SerialCommunication.h"
#include "../protocol/ProtocolToString.h"
#include "../hardware/switches.h"
#include "../hardware/LTC1867.h"

/**
 * 				 Mario van Etten
 * 		 		    27-10-2017
 *
 *
 * wrapper class for incomin Serial communication
 * Debug messages and updating the led indicator
 * based on the state of the device. Call update
 * in the main loop.
 *
 * 				3 states are possible
 *
 * 1. Normal operation : sampling takes place
 * 2. Programming : EEPROM memory is written
 * 3. Debug : debugging mode is enabled and
 *    information can be received by sending
 *    commands to the serial port. Sampling
 *    of the analog sensors can be individually
 *    enabled.
 *
 * the commands for the debugging are the following
 *  0 : DBGENA : Enable debugging
 *  1 : DBGCOM : Print commands
 *  2 : MEMCHK : Memory Check (performs crc for now)
 *  3  : PRINTE : print EEPROM
 *  4 : PRINTC : Print controller settings.
 *  5 : SCxCxx : Print specific controller
 *               from a specific scene
 *  >>: SC(1-4): Scene number 1 to 4
 *  >>: Cxx    : Controller 1 to 28
 *  >>: C00    : Print Scene Data
 *  >>: SC1C11 : Prints controller 11 of scene 1
 *  6 : ANAENA : Enable polling analog sensors
 *               and print the values
 *  7 : SWSENA : Enable polling switches and
 *               print the values
 *  8 : LEDTST : Test led indicators
 *  9 : MIDENA : Enable MIDI
 * 10 : MIDDIS : Disable MIDI
 * 11 : DBGDIS : Exit debugging
 *
 * When debugging is enabled the led start flashing at
 * a interval of 1 sec
 **/


class StateMachine {
public:
	StateMachine();
	StateMachine(long baudRate);
    ~StateMachine();

    int getState();
    boolean update(); //return true if state has changed
    void init();
private:

    void printDebugCommands();
    void printAnalogSensors();
    void printSwitches();
    void testLedIndicators();

    long baudRate;
    SerialCommunication serial;
    ProtocolToString printer;

    unsigned long currentTime;
    unsigned long printStartTime; //Printing analog or switchvalues
    unsigned long ledStartTime;   //Led indicator speed

    boolean updated;
    boolean ledToggle;
    boolean programMode;
    boolean debugMode;
    boolean printAnalogValues;
    boolean printSwitchValues;
    boolean midiEnabled;
    int ledPin;
    int state;				//state of the device
    int serialResult;

};

#endif /* SRC_STATE_STATEMACHINE_H_ */
