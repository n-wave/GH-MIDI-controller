
#ifndef SWITCHES_H
#define SWITCHES_H

#include <Arduino.h>

/* switches midi controller */

namespace switches
{
	extern uint8_t common_z;
	extern uint8_t address_a;
	extern uint8_t address_b;
	extern uint8_t address_c;
	extern uint8_t address_d;

	extern uint16_t values[16];
	extern byte addressMultiplexer[16];
	extern unsigned int switchIndex;

	void init();
	void read();

	uint8_t pollSceneSwitches();

} //name swmc
#endif

