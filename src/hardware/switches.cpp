#include "switches.h"
#include <Arduino.h>

/**
 *      Mario van Etten 
 *   
 *         02-03-2017
 *      
 * poll 16 switches connected
 * to a 4067 16 channel configured
 * as multiplexer. common output z
 * goed to pin 15 configured as
 * input and an enabled pullup
 * resistor. switches are connected
 * to GND
 * 
 * i.e IDLE STATE LOW Active HIGH
 * The address pins are inverted
 * 
 * Channels are selected by anding
 * GPIO_PBOR with for loop index
 *      
 *      
 * COMMON_Z  pin 15 Input Enable pullup
 * ADDRESS_0 pin 16 = port B0
 * ADDRESS_1 pin 17 = port B1
 * ADDRESS_2 pin 19 = port B2
 * ADDRESS_3 pin 18 = port B3
 * 
 */
                     

namespace switches
{
	uint8_t common_z = 15;
	uint8_t address_a = 16;
	uint8_t address_b = 17;
	uint8_t address_c = 19;
	uint8_t address_d = 18;

	uint16_t values[16] =  {
							0,  //neck switch 1
							0,  //neck switch 2
							0,  //neck switch 3
							0,  //neck switch 4
							0,  //neck switch 5
							0,  //neck switch 6
							0,  //tab switch 1
							0,  //tab switch 2
							0,  //start
							0,  //select
							0,  //scene 1
							0,  //scene 2
							0,  //scene 3
							0,  //scene 4
							0,  //joystick switch
							0   //pot switch
							};

	unsigned int switchIndex = 0;

	void init(){
		pinMode(common_z, INPUT); //enable pullup resistor for 16bit channel multiplexer
		pinMode(address_a, OUTPUT);
		pinMode(address_b, OUTPUT);
		pinMode(address_c, OUTPUT);
		pinMode(address_d, OUTPUT);
		GPIOB_PDOR &= ~B0000;
		switchIndex = 0;
	}

	void read(){
		GPIOB_PDOR = ~switchIndex; //Because of the hex inverter invert the address
  
		delayMicroseconds(3);
		values[switchIndex] = digitalReadFast(common_z);
    
		switchIndex++;
		switchIndex &= 15;
	}

	uint8_t pollSceneSwitches(){
		uint8_t result = 0;

		for(int i=10; i<14; i++){
			if(values[i] == 1){
				result = i-9;
			}
		}

		return result;
	}
} //namespace swmc
