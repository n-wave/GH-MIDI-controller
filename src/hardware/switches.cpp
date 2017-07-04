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
 * i.e IDLE STATE HIGH Active LOW 
 * Invert state when polling
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
                     
volatile unsigned char switches[16] =  {0,  //neck switch 1
                                        0,  //neck switch 2
                                        0,  //neck switch 3
                                        0,  //neck switch 4
                                        0,  //neck switch 5
                                        0,  //neck switch 6
                                        0,  //tab switch 1
                                        0,  //tab switch 2
                                        0,  //start
                                        0,  //select
                                        0,  //hold/foot switch
                                        0,  //joystick switch
                                        0,  //scene 1
                                        0,  //scene 2
                                        0,  //scene 3  
                                        0}; //scene 4

unsigned int switchIndex = 0;
                                       
void initSwitches() {
  pinMode(COMMON_Z, INPUT_PULLUP); //enable pullup resistor for 16bit channel multiplexer
  pinMode(ADDRESS_0, OUTPUT);
  pinMode(ADDRESS_1, OUTPUT);
  pinMode(ADDRESS_2, OUTPUT);
  pinMode(ADDRESS_3, OUTPUT);
  GPIOB_PDOR = B00000000;
  switchIndex = 0;
}

void readSwitches(){
  GPIOB_PDOR = switchIndex;
  
  delayMicroseconds(5);
  switches[switchIndex] = !digitalReadFast(COMMON_Z);
    
   switchIndex++;
   switchIndex &= 15;
}


