
#include "src/testing/configuration.h"

#include "src/testing/PointerTest.h"
#include "src/testing/Test.h"
#include "src/builders/Scene.h"
#include "src/protocol/ProtocolInterperter.h"
#include "src/dispatcher/Dispatcher.h"

Dispatcher dispatcher = Dispatcher();

Scene sceneOne = Scene("Scene One", &dispatcher);
Scene sceneTwo = Scene("Scene Two", &dispatcher);
Scene sceneThree = Scene("Scene Three", &dispatcher);
Scene sceneFour = Scene("Scene Four", &dispatcher);

boolean run = true;
int count = 0;
String result;

long time = 0L;

void setup()
{


	Serial.begin(9600);
	delay(1000);
	ProtocolInterperter interperter = ProtocolInterperter();
	interperter.configureScene(sceneOne, 0);

    time = millis();
	Serial.println(time);
}

// The loop function is called in an endless loop
void loop()
{


	if(run){
		#ifdef DEBUG
		configureDispatcherTest();
		//configureSceneTest();
		//pogramChangeTest();
		#endif /* DEBUG */
		if(count == 100){
			run = false;
			time = millis();
			Serial.println(time);
		}
		count++;
	}
}

#ifdef DEBUG

void configureDispatcherTest(){

	sceneOne.updateControllers();

	dispatcher.dispatch();
}



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






void pointerTest(){
	/**
	 *  Dynamic Initialization should take place in loop
	 * 	If defined as global variable, the class will not be
	 * 	successfully intialialized on the heap.
	 **/
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
