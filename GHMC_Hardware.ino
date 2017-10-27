
#include "src/testing/configuration.h"

#include  "src/serial/SerialCommunication.h"
#include "src/builders/Scene.h"
#include "src/hardware/switches.h"
#include "src/protocol/ProtocolInterperter.h"
#include "src/protocol/ProtocolToString.h"

#include "src/dispatcher/Dispatcher.h"
#include "src/hardware/LTC1867.h"
#include "src/state/StateMachine.h"

StateMachine stateMachine = StateMachine(115200);

Dispatcher dispatcher = Dispatcher();

Scene sceneOne = Scene("Scene One", &dispatcher);
Scene sceneTwo = Scene("Scene Two", &dispatcher);
Scene sceneThree = Scene("Scene Three", &dispatcher);
Scene sceneFour = Scene("Scene Four", &dispatcher);


IntervalTimer samplingClock;

int cycles = 0;
boolean startup = true;
boolean stateChanged = false;

void setup()
{
	delay(1000);

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
	LTC1867_init(); //Tested and working
	stateMachine.init();
}

// The loop function is called in an endless loop
void loop()
{

	  if(startup){
		  //configureSceneTest();

		  startup = false;
		  samplingClock.begin(updateSensors, 20); // Start Sampling the sensors
	  }


	  readSwitches();

	  digitalWrite(3, LOW);
	  digitalWrite(4, LOW);
	  digitalWrite(5, LOW);
	  digitalWrite(6, LOW);

	  digitalWrite(22, LOW);
	  digitalWrite(21, LOW);

	  //State 1: Normal Operation
	  //State 2: Programming mode disable IntervalTimer
	  //State 3: Debug

	  if(stateMachine.update()){
		  switch(stateMachine.getState())
		  {
	  	    case 1:
	  	      cycles = 0;
	  		  LTC1867_reset();
	  		  samplingClock.begin(updateSensors, 20);
	  		  break;
	  	    case 2:
		      samplingClock.end();
		  	  break;
    	  }
	  }
}

void updateSensors(){
	   cycles = cycles & 1023; // summing 128 times use 511 for 64 times

	   if(cycles == 0){
	     LTC1867_calculateAverage();
	   }

	   LTC1867_readSensors();


	   cycles++;
}






void configureSceneTest(){
	ProtocolInterperter interperter = ProtocolInterperter();

	interperter.configureScene(sceneOne, 0);
	delay(100);
	interperter.configureScene(sceneTwo, 1);
	delay(100);
	interperter.configureScene(sceneThree, 2);
	delay(100);
	interperter.configureScene(sceneFour, 3);
	delay(100);

	sceneOne.printControllerContents();
	sceneTwo.printControllerContents();
	sceneThree.printControllerContents();
	sceneFour.printControllerContents();
}





