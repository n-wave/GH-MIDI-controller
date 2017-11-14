/*
 * ghmc.h
 *
 *  Created on: Nov 2, 2017
 *      Author: mario
 */

#ifndef SRC_GHMC_GHMC_H_
#define SRC_GHMC_GHMC_H_

#include "Arduino.h"
/*
 * project specific namespace for recurring functions
 * like the convertBytes and compare messages used
 * in multiple classes
 *
 */
namespace ghmc{

	//Function for byt eConversions
	namespace byte{
		uint16_t convertBytesTo14Bit(uint8_t msb, uint8_t lsb);
		uint16_t convertBytesTo16Bit(uint8_t msb, uint8_t lsb);
	} // namespace byte

}



#endif /* SRC_GHMC_GHMC_H_ */
