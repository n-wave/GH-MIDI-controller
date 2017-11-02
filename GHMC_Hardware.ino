
#include "src/testing/configuration.h"

#include  "src/serial/SerialCommunication.h"
#include "src/builders/Scene.h"
#include "src/hardware/switches.h"
#include "src/protocol/ProtocolInterperter.h"
#include "src/protocol/ProtocolToString.h"

#include "src/dispatcher/Dispatcher.h"
#include "src/hardware/LTC1867.h"
#include "src/state/StateMachine.h"

ProtocolInterperter interperter = ProtocolInterperter();
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
boolean sensorsUpdated = false;
boolean enableMidi = true;

void setup()
{
	delay(100);

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
		   configureScenes();
		  startupLedSequence();

		  startup = false;
		  samplingClock.begin(updateSensors, 15); // Start Sampling the sensors
		  	  	  	  	  	  	  	  	  	  	  //16 stable
		  	  	  	  	  	  	  	  	  	  	  //15 stable -> 65Hz leave headroom we need to do more calculations
		  	  	  	  	  	  	  	  	  	  	  //14 stable
		  	  	  	  	  	  	  	  	  	  	  //13 unstable

		  	  	  	  	  	  	  	  	  	  	  //unstable
	  }


	  readSwitches();

	  digitalWrite(3, LOW);
	  digitalWrite(4, LOW);
	  digitalWrite(5, LOW);
	  digitalWrite(6, HIGH);

	  if(sensorsUpdated){
		  LTC1867_calculateAverage();
		  if(enableMidi){
			sceneOne.setParameters();
		  	sceneOne.updateControllers();
		  }
		  sensorsUpdated = false;
	  }


	  dispatcher.dispatch();


	  //State 1: Normal Operation
	  //State 2: Programming mode disable IntervalTimer
	  //State 3: Debug

	  if(stateMachine.update()){
		  switch(stateMachine.getState())
		  {
	  	    case 1:
	  	      //Disable interrupts temporary experiencing
	  	      //hangup without this, because of the
	  	      //Ptr's to the buffers which are set in LTC1867_reset;
	  	      noInterrupts();
	  	      cycles = 0;
	  		  LTC1867_reset();
	  	      succeslLedSequence();
	  	      configureScenes();
	  		  enableMidi = true;
	  		  interrupts();
	  		  samplingClock.begin(updateSensors, 15);
	  		  break;
	  	    case 2: //Entering programming Mode disable the sampling clock and Midi
	  	      enableMidi = false;
		      samplingClock.end();
		  	  break;
	  	    case 3:
	  	      //Upload failed not reconfiguring Scenes
	  	      noInterrupts();
	  	      cycles = 0;
	  		  LTC1867_reset();
	  	  	  enableMidi = true;
	  	  	  interrupts();
	  	  	  samplingClock.begin(updateSensors, 15);
	  	  	  break;
	  	    case 4: //Entering Debug or Disable Midi message has been received
		      enableMidi = false;
		      break;
	  	    case 5:
	  	      enableMidi = true; //Enable MIDI message has been received turn on Midi
	  	      break;
    	  }
	  }
}

void updateSensors(){
	   cycles = cycles & 1023; // summing 128 times use 511 for 64 times

	   if(cycles == 0){
		 LTC1867_swapBuffer();
	     sensorsUpdated = true;
	   }

	   LTC1867_readSensors();


	   cycles++;
}


void configureScenes(){
	interperter.configureScene(sceneOne, 0);
	interperter.configureScene(sceneTwo, 1);
    interperter.configureScene(sceneThree, 2);
	interperter.configureScene(sceneFour, 3);

}

void succeslLedSequence(){
	for(int i=0; i<3; i++){
		digitalWrite(20, HIGH);
		delay(50);
		digitalWrite(20, LOW);
		delay(50);
	  }

	  digitalWrite(20, HIGH);
}

void startupLedSequence(){
	int ledDelay;

	digitalWrite(3, LOW);
   	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	digitalWrite(6, LOW);
	digitalWrite(20, LOW);

	for(int i=22; i>20; i--){
		digitalWrite(i, HIGH);
		delay(150);
		digitalWrite(i, LOW);
	}

	for(int i=6; i>=3; i--){
		digitalWrite(i, HIGH);
		delay(150);
		digitalWrite(i, LOW);
	}


	for(int i=0; i<10; i++){
		ledDelay = 120-(i*10);
		digitalWrite(20, HIGH);
		delay(ledDelay);
		digitalWrite(20, LOW);
		delay(ledDelay);
	  }

	  digitalWrite(20, HIGH);
}


