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
Test test = Test();
boolean run = true;
String result;

void setup()
{

	/*
	delay(1000);
	if(pc.setConfiguration(programChangeData)){
		succes = String("Successfully loaded data");
	} else {
		succes = String("Couldn't load data");
	}
	*/
// Add your initialization code here
	Serial.begin(9600);

}

// The loop function is called in an endless loop
void loop()
{
	delay(2000);
	if(run){
		Serial.println("test");
		for(int i=0; i<9; i++){

			Serial.println("--------------------------\n");
			Serial.println("Printing Controller : ");
			Serial.println("--------------------------\n");

			result = test.getString(i);
			Serial.println(result);

			delay(500);
		}
		Serial.println("Exiting for Loop");
		run = false;
	}
}
