#define COMMON_Z 15 //common pin 16 ch multiplexer
#define ADDRESS_0 16
#define ADDRESS_1 17
#define ADDRESS_2 19
#define ADDRESS_3 18

#ifndef SWITCHES_H
#define SWITCHES_H

#include <Arduino.h>

extern volatile unsigned char switches[16];
extern byte addressMultiplexer[16];
extern unsigned int switchIndex;

void initSwitches();
void readSwitches();

#endif

