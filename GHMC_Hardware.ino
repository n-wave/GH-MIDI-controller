#include "Arduino.h"

#include "src/testing/PointerTest.h"
#include "src/testing/Test.h"

ProgramChange pc = ProgramChange();

/*
int programChangeData[] = {
							0xF0, //0 Start Byte
							0xE0, //1 Option ID
							0x01, //2 Channel
							0x02, //3 Bank
							0x03, //4 Program
							0xFF  //5 End Byte
					   };
*/

//Test test = Test();
PointerTest* test;
boolean run = true;
String result;

void setup()
{
	Serial.begin(9600);
	delay(1000);

	test = new PointerTest();
}

// The loop function is called in an endless loop
void loop()
{

	delay(2000);
	if(run){
		/**
		 *  Dynamic Initialization should take place in loop
		 * 	If defined as global variable, the class will not be
		 * 	successfully intialialized on the heap.
		 **/


		for(int i=0; i<9; i++){

			Serial.println("------------------------");
			Serial.print("Printing Controller : ");
			Serial.println(i);
			Serial.println("------------------------\n");

			result = test->getContents(i);
			Serial.println(result);

			delay(500);
		}
		Serial.println("Exiting for Loop");
		run = false;
	}
}
