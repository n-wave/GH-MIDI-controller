
#include "src/testing/configuration.h"

//#include "src/testing/PointerTest.h"
#include  "src/serial/SerialCommunication.h"
//#include "src/testing/Test.h"
#include "src/builders/Scene.h"
#include "src/hardware/switches.h"
#include "src/protocol/ProtocolInterperter.h"

#include "src/protocol/ProtocolToString.h"

#include "src/dispatcher/Dispatcher.h"
#include "src/hardware/LTC1867.h"

SerialCommunication serial = SerialCommunication();

Dispatcher dispatcher = Dispatcher();

Scene sceneOne = Scene("Scene One", &dispatcher);
Scene sceneTwo = Scene("Scene Two", &dispatcher);
Scene sceneThree = Scene("Scene Three", &dispatcher);
Scene sceneFour = Scene("Scene Four", &dispatcher);


IntervalTimer samplingClock;



int cycles = 0;

boolean run = true;
int count = 0;
String result;

unsigned long startTime = 0L;
unsigned long currentTime = 0L;

void setup()
{
	  pinMode(3, OUTPUT);
	  pinMode(4, OUTPUT);
	  pinMode(5, OUTPUT);
	  pinMode(6, OUTPUT);

	  pinMode(22, OUTPUT);
	  pinMode(21, OUTPUT);
	  pinMode(20, OUTPUT);

	  digitalWrite(3, LOW);
	  digitalWrite(4, LOW);
	  digitalWrite(5, LOW);
	  digitalWrite(6, LOW);

	  digitalWrite(22, LOW);
	  digitalWrite(21, LOW);
	  digitalWrite(20, LOW);


	  initSwitches(); //Tested and working
	  LTC1867_init();

	  startTime = millis();

	 // configureSceneTest();

	  //Try to go as low as possible in complete implementation
	  //Teensy is overclocked to 96MHz


	  //20 stable with loop-print console  +/- 50 Hz update freq
	  //16 stable with updateSensor Timer  +/- 62 Hz update freq
	  //8 stable only with ADC for now     +/- 97 Hz update freq
	  // when everything is implmented


	samplingClock.begin(updateSensors, 20); // Start Sampling the sensors
}

// The loop function is called in an endless loop
void loop()
{
	  delay(1000);
	  currentTime = millis();


	  digitalWrite(3, LOW);
	  digitalWrite(4, LOW);
	  digitalWrite(5, LOW);
	  digitalWrite(6, LOW);

	  digitalWrite(22, LOW);
	  digitalWrite(21, LOW);
	  digitalWrite(20, HIGH);



	  readSwitches();


	   if((currentTime - startTime) > 50){
	    startTime = currentTime;
	   //  printValues();
	 }


	if(run){
		#ifdef DEBUG
		//configureDispatcherTest();
		//configureSceneTest();
		//pogramChangeTest();

		ProtocolToString printer = ProtocolToString();
		//printer.printContentsToString();

		printer.printEEPROM();

		run = false;
		#endif /* DEBUG */

	}
/*
	if(count == 100){
			run = false;
			time = millis();
			Serial.println(time);
		}
		count++;
	}
	*/

	serial.readSerial();
}

void updateSensors(){
	   cycles = cycles & 1023; // summing 128 times use 511 for 64 times

	   if(cycles == 0){
	     LTC1867_calculateAverage();
	   }

	   LTC1867_readSensors();


	   cycles++;
}

#ifdef DEBUG
	void printValues(){
		for(int i=0; i<18; i++){
	    Serial.print("\n");
	  }

	  Serial.println("Averaged and Mapped values");

	  Serial.println("Mapped Values");
	  		/* ADC 1 */
	  	  	//Head potentiometer 1
	  		Serial.print("H1 :");
	  		Serial.print(averagedValues[0]);
	  		Serial.print(" : ");
	  		Serial.println(mappedValues[0]);
	  		//Head potentiometer 2
	  		Serial.print("H2:");
	  		Serial.print(averagedValues[1]);
	  		Serial.print(" : ");
	  		Serial.println(mappedValues[1]);
	  		//Head potentiometer 3
	  		Serial.print("H3:");
	  		Serial.print(averagedValues[2]);
	  		Serial.print(" : ");
	  		Serial.println(mappedValues[2]);
	  		//Head potentiometer 4
	  		Serial.print("H4:");
	  		Serial.print(averagedValues[3]);
	  		Serial.print(" : ");
	  		Serial.println(mappedValues[3]);
	  		//Head potentiometer 5
	  		Serial.print("H5:");
	  		Serial.print(averagedValues[4]);
	  		Serial.print(" : ");
	  		Serial.println(mappedValues[4]);
	  		//Head potentiometer 6
	  		Serial.print("H6:");
	  		Serial.print(averagedValues[5]);
	  		Serial.print(" : ");
	  		Serial.println(mappedValues[5]);
	  		 //Ribbon 1
	  		Serial.print("R1:");
	  		Serial.print(averagedValues[6]);
	  		Serial.print(" : ");
	  		Serial.println(mappedValues[6]);
	  		//Ribbon 2
	  		Serial.print("R2:");
	  		Serial.print(averagedValues[7]);
	  		Serial.print(" : ");
	  		Serial.println(mappedValues[7]);

	  		/* ADC 2 */
	  		//Pressure 1
	  		Serial.print("P1:");
	  		Serial.print(averagedValues[8]);
	  		Serial.print(" : ");
	  		Serial.println(mappedValues[8]);
	  		//Pressure 2
	  		Serial.print("P2:");
	  		Serial.print(averagedValues[9]);
	  		Serial.print(" : ");
	  		Serial.println(mappedValues[9]);
	  		//Pressure 3
	  		Serial.print("P3:");
	  		Serial.print(averagedValues[10]);
	  		Serial.print(" : ");
	  		Serial.println(mappedValues[10]);
	  		//Body Pot 1
	  		Serial.print("B1:");
	  		Serial.print(averagedValues[11]);
	  		Serial.print(" : ");
	  		Serial.println(mappedValues[11]);
	  		//Body Pot 2
	  		Serial.print("B2:");
	  		Serial.print(averagedValues[12]);
	  		Serial.print(" : ");
	  		Serial.println(mappedValues[12]);
	  		//Body Pot 3
	  		Serial.print("B3:");
	  		Serial.print(averagedValues[13]);
	  		Serial.print(" : ");
	  		Serial.println(mappedValues[13]);
	  		//X axis
	  		Serial.print("Xa:");
	  		Serial.print(averagedValues[14]);
	  		Serial.print(" : ");
	  		Serial.println(mappedValues[14]);
	  		//Y axis
	  		Serial.print("Ya:");
	  		Serial.print(averagedValues[15]);
	  		Serial.print(" : ");
	  		Serial.println(mappedValues[15]);
	 }



	void printToConsole(){
		for(int i=0; i<32; i++){
	    Serial.print("\n");
	  }

	  /* Switches */

		Serial.print("N1:");                     //Neck Switch 1
		Serial.println(switches[0]);
		Serial.print("N2:");                     //Neck Switch 2
		Serial.println(switches[1]);
		Serial.print("N3:");                     //Neck Switch 3
		Serial.println(switches[2]);
		Serial.print("N1:");                     //Neck Switch 4
		Serial.println(switches[3]);
		Serial.print("N2:");                     //Neck Switch 5
		Serial.println(switches[4]);
		Serial.print("N3:");                     //Neck Switch 6
		Serial.println(switches[5]);
		Serial.print("Up:");                      //Up Switch
		Serial.println(switches[6]);
		Serial.print("Do:");                      //Down Switch
		Serial.println(switches[7]);

		Serial.print("ST:");                     //Neck Switch 1
		Serial.println(switches[8]);
		Serial.print("SE:");                     //Neck Switch 2
		Serial.println(switches[9]);
		Serial.print("S1:");                     //Neck Switch 3
		Serial.println(switches[10]);
		Serial.print("S2:");                     //Neck Switch 4
		Serial.println(switches[11]);
		Serial.print("S3:");                     //Neck Switch 5
		Serial.println(switches[12]);
		Serial.print("S4:");                     //Neck Switch 6
		Serial.println(switches[13]);
		Serial.print("PS:");                      //Up Switch
		Serial.println(switches[14]);
		Serial.print("jS:");                      //Down Switch
		Serial.println(switches[15]);
}
#endif DEBUG

//#ifdef DEBUG


/*
void configureDispatcherTest(){

	sceneOne.updateControllers();

	dispatcher.dispatch();
}
*/


void configureSceneTest(){
	ProtocolInterperter interperter = ProtocolInterperter();

	interperter.configureScene(sceneOne, 0);
	delay(250);
	interperter.configureScene(sceneTwo, 1);
	delay(250);
	interperter.configureScene(sceneThree, 2);
	delay(250);
	interperter.configureScene(sceneFour, 3);
	delay(250);

	sceneOne.printControllerContents();
	sceneTwo.printControllerContents();
	sceneThree.printControllerContents();
	sceneFour.printControllerContents();
}

/*
void pogramChangeTest(){
	int dataTestOne[16] = {
							0XF0, 0xEA, 0x00, 0x00,
							0x00, 0x00, 0x00, 0x00,
							0x00, 0x00, 0x00, 0x00,
							0x00, 0x00, 0x00, 0xFF
						  };

	int dataTestTwo[16] = {
							0XF0, 0xEA, 0x01, 0x01,
							0x02, 0x00, 0x00, 0x00,
							0x04, 0x00, 0x00, 0x00,
							0x00, 0x00, 0x00, 0xFF
						  };

	int dataTestThree[16] = {
							  0XF0, 0xEA, 0x03, 0x01,
							  0x02, 0x03, 0x02, 0x03,
							  0x04, 0x03, 0x04, 0x05,
							  0x04, 0x08, 0x07, 0xFF
						    };

	int dataTestFour[16] = {
							  0XF0, 0xEA, 0x04, 0x01,
							  0x02, 0x03, 0x02, 0x03,
							  0x04, 0x03, 0x04, 0x05,
							  0x04, 0x05, 0x06, 0xFF
						    };

	sceneOne.setSceneData(dataTestOne);
	sceneTwo.setSceneData(dataTestTwo);
	sceneThree.setSceneData(dataTestThree);
	sceneFour.setSceneData(dataTestFour);

	sceneOne.printPogramChangeContents();
	sceneTwo.printPogramChangeContents();
	sceneThree.printPogramChangeContents();
	sceneFour.printPogramChangeContents();

}



*/

/*
void pointerTest(){
	/**
	 *  Dynamic Initialization should take place in loop
	 * 	If defined as global variable, the class will not be
	 * 	successfully intialialized on the heap.
	 **/
/*
	PointerTest* test = new PointerTest();

	for(int i=0; i<10; i++){

		Serial.println("------------------------");
		Serial.print("Printing Controller : ");
		Serial.println(i);
		Serial.println("------------------------\n");

		test->printContents(i);
		Serial.println(result);

		delay(500);
	}
	Serial.println("Exiting for Loop");
}




#endif
*/
