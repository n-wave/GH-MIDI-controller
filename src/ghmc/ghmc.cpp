/*
 * ghmc.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: mario
 */


#include "ghmc.h"

namespace ghmc {

	namespace debug {

	} // namespace debug

	namespace byte {
		uint16_t convertBytesTo14Bit(uint8_t msb, uint8_t lsb){
			uint16_t result = 0;
			uint16_t MSB = (msb & 0x7F) << 7;
			uint16_t LSB = lsb & 0x7F;

			result = MSB | LSB;

			return result;
		}

		uint16_t convertBytesTo16Bit(uint8_t msb, uint8_t lsb){
			uint16_t result = 0;
			uint16_t MSB = (msb & 0XFF) << 8;
			uint16_t LSB = lsb & 0xFF;

			result = MSB | LSB;

			return result;
		}
	} // namespace byte

} // namespace ghmc

