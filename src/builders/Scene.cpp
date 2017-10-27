/*
 * Scene.cpp
 *
 *  Created on: Jul 7, 2017
 *      Author: mario
 */

#include "Scene.h"

#include "../controller/includeControllers.h"

Scene::Scene() :
	nrOfProgramChanges(0),
	name(String()),
	programChange(NULL),
	dispatcher(NULL)
{
	// TODO Auto-generated constructor stub
	setName("Default");

	for(int i=0;i<NROFCONTROLLERS; i++){
		controllers[i] = NULL;
	}
}

Scene::Scene(const String& name) :
	nrOfProgramChanges(0),
	name(String(name)),
	programChange(NULL),
	dispatcher(NULL)
{
}

Scene::Scene(const String& name, Dispatcher* dispatcher) :
	nrOfProgramChanges(0),
	name(String(name)),
	programChange(NULL),
	dispatcher(dispatcher)
{
}

Scene::~Scene() {
	for(int i=0; i<NROFCONTROLLERS; i++){
		delete controllers[i];
		controllers[i] = NULL;
	}

	if(nrOfProgramChanges > 0 && programChange != NULL){
		for(int i=0; i<nrOfProgramChanges; i++){
			delete programChange[i];
			programChange = NULL;
		}
		delete[] programChange;
	}
	dispatcher = NULL;
}

void Scene::updateControllers(){
	for(int i=0; i<NROFCONTROLLERS; i++){
		controllers[i]->update(0);
	}
}

/**
 * Supply the current scene with the scene data
 * retrieved from memory, based on the contents
 * Memory for the programChange controllers will
 * be allocated. And programChange DataStructures
 * will be created for the Objects.
 */

boolean Scene::setSceneData(const int* data){
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		data[15] == 0xFF
	  )
	{
		nrOfProgramChanges = data[2];

		if(nrOfProgramChanges > 0 && nrOfProgramChanges <= 4){
			boolean run = true;
			int index = 0;
			int channelIndex = 3;
			int bankIndex = 4;
			int programIndex = 5;

			programChange = new ProgramChange*[nrOfProgramChanges];

			do {
				int dataBuffer[6];

				dataBuffer[0] = 0xF0;
				dataBuffer[1] = 0xE0;
				dataBuffer[2] = data[channelIndex];
				dataBuffer[3] = data[bankIndex];
				dataBuffer[4] = data[programIndex];
				dataBuffer[5] = 0xFF;

				programChange[index] = new ProgramChange(dataBuffer);
				delay(50);

				index++;
				channelIndex += 3;
				bankIndex += 3;
				programIndex += 3;

				if(index == nrOfProgramChanges){
					run = false;
				}
			} while(run);
		}
	}
	return result;
}

/*
 * Set controller based on the controller number, which represent
 * different sensors. Make a decision based on the current
 * selected controller and the type provided by the data structure
 * residing in the EEPROM memory and initialize the corresponding
 * object.
 */

boolean Scene::setController(int number, int type, const int* data){
	boolean result = false;

	if(
	   number >= 0 &&
	   number < 28 &&
	   type >= 0 &&
	   type <= 17 &&
	   dispatcher != NULL
	  )
	{
	#ifdef DEBUG
		Serial.print("Controller nr : ");
		Serial.print(number);
		Serial.print(" : ");
	#endif /* DEBUG */


		/* PotentioMeters
		 *
		 * channel 0 Head PotentioMeter 1
		 * channel 1 Head PotentioMeter 2
		 * channel 2 Head PotentioMeter 3
		 * channel 3 Head PotentioMeter 4
		 * channel 4 Head PotentioMeter 5
		 * channel 5 Head PotentioMeter 6
		 *
		 * channel 11 Body Potentiometer 1
		 * channel 12 Body Potentiometer 2
		 * channel 13 Body PotentioMeter 3
		 * channel 14 joyStick X-axis
		 * channel 15 joyStick Y-axis
		 *
		 */


		if((number >= 0 && number <= 5) || (number >= 11 && number <= 15)){
			switch(type){
				case 0:
					controllers[number] = new DisabledController(data);
					break;
				case 7:
					controllers[number] = new ControlChangePotentioMeter8Bit(data, dispatcher);
					break;
				case 8:
					controllers[number] = new ControlChangePotentioMeter16Bit(data, dispatcher);
					break;
			}
		}

		/*
		 * Ribbon controller
		 *
		 * channel 6 Ribbon 1
		 * channel 7 Ribbon 2
		 */

		if(number >= 6 && number <= 7){
			switch(type){
				case 0:
					controllers[number] = new DisabledController(data);
					break;
				case 5:
					controllers[number] = new PitchBendRibbon(data, dispatcher);
					break;
				case 6:
					controllers[number] = new PitchBendNoteRibbon(data, dispatcher);
					break;
				case 7:
					controllers[number] = new ControlChangeRibbon8Bit(data, dispatcher);
					break;
				case 8:
					controllers[number] = new ControlChangeRibbon16Bit(data, dispatcher);
					break;
			}
		}

		/*
		 * Pressure sensors
		 *
		 * channel 8 Pressure Sensor 1
		 * channel 9 Pressure Sensor 2
		 * channel 10 Pressure Sensor 3
		 *
		 */


		if(number >= 8 && number <= 10){
			switch(type){
				case 0:
					controllers[number] = new DisabledController(data);
					break;
				case 2:
					controllers[number] = new NoteVelocityPressure(data, dispatcher);
					break;
				case 3:
					controllers[number] = new NoteControlChangePressure8Bit(data,dispatcher);
					break;
				case 4:
					controllers[number] = new NoteControlChangePressure16Bit(data, dispatcher);
					break;
				case 7:
					controllers[number] = new ControlChangePressure8Bit(data,dispatcher);
					break;
				case 8:
					controllers[number] = new ControlChangePressure16Bit(data, dispatcher);
					break;
				case 9:
					controllers[number] = new ControlChangeFadePressure8Bit(data, dispatcher);
					break;
				case 10:
					controllers[number] = new ControlChangeFadePressure16Bit(data, dispatcher);
					break;
			}
		}

		if(number >= 16 && number <= 25){
			switch(type){
				case 0:
					controllers[number] = new DisabledController(data);
					break;
				case 1:
					controllers[number] = new ProgramChangeSwitch(data, dispatcher);
					break;
				case 2:
					controllers[number] = new NoteVelocitySwitch(data, dispatcher);
					break;
				case 7:
					controllers[number] = new ControlChangeSwitch8Bit(data, dispatcher);
					break;
				case 8:
					controllers[number] = new ControlChangeSwitch16Bit(data, dispatcher);
					break;
				case 9:
					controllers[number] = new ControlChangeFadeSwitch8Bit(data, dispatcher);
					break;
				case 10:
					controllers[number] = new ControlChangeFadeSwitch16Bit(data, dispatcher);
					break;
			}
		}

		if(number >= 26 && number <= 27){
			int ledPin = 0;

			if(number == 30){
				ledPin = 21; //Joy Stick Switch Led
			} else {
				ledPin = 22; //Foot Switch led
			}

			switch(type){
				case 0:
					controllers[number] = new DisabledController(data);
					break;
				case 11:
					controllers[number] = new NoteVelocityToggle(data, ledPin, dispatcher);
					break;
				case 12:
					controllers[number] = new NoteControlChangeToggle8Bit(data, ledPin, dispatcher);
					break;
				case 13:
					controllers[number] = new NoteControlChangeToggle16Bit(data, ledPin, dispatcher);
					break;
				case 14:
					controllers[number] = new ControlChangeToggle8Bit(data, ledPin, dispatcher);
					break;
				case 15:
					controllers[number] = new ControlChangeToggle16Bit(data, ledPin, dispatcher);
					break;
				case 16:
					controllers[number] = new ControlChangeFadeToggle8Bit(data, ledPin, dispatcher);
					break;
				case 17:
					controllers[number] = new ControlChangeFadeToggle16Bit(data, ledPin, dispatcher);
					break;
			}
		}

		result = true;
	}
#ifdef DEBUG
	else {
		Serial.println("Error occurred while trying to set the controller");
		Serial.print("Number : ");
		Serial.println(number);
		Serial.print("Type : ");
		Serial.println(type);
	}
#endif /* Debug */
	return result;
}

void Scene::setName(const String& name){
	this->name = name;
}

#ifdef DEBUG

void Scene::printPogramChangeContents(){
	int tmpNrOfPC = this->nrOfProgramChanges;

	if(tmpNrOfPC > 0){

		Serial.println(name);
		Serial.print("Number Of Program Changes : ");
		Serial.println(tmpNrOfPC);

		for(int i=0; i<tmpNrOfPC; i++){
			Serial.print("index : ");
			Serial.println(i);
			programChange[i]->printContents();
			delay(250);
		}
	} else {
		Serial.println("Error occurred in Scene::printProgramChangeContents()");
		Serial.print(name);
		Serial.print(" : ");
		Serial.println("No programChange objects initialized");
	}
}

void Scene::printPogramChangeContent(int index){
	int tmpNrOfPC = this->nrOfProgramChanges;

	Serial.println(name);
	Serial.print("Number Of Program Changes : ");
	Serial.println(tmpNrOfPC);

	if(index >= 0 && index < tmpNrOfPC){

	//	programChange[index]->printContents();

	} else {
		Serial.println("Error occurred in Scene::printProgramChangeContent(int)");
		Serial.print(name);
		Serial.print(" : ");
		Serial.println("Index out of bound");
	}
}

void Scene::printControllerContents(){
	Serial.println("-----------");
	Serial.println(name);
	Serial.println("-----------");

	for(int i=0; i<NROFCONTROLLERS; i++){
		Serial.print("Controller : ");
		Serial.println(i);

		this->printControllerContent(i);
		delay(50);
	}
}

void Scene::printControllerContent(int index){
	if(index >=0 && index < 28){
		controllers[index]->printContents();
	} else {
		Serial.println("Error occurred in Scene::printControllerContent(int)");
		Serial.print(name);
		Serial.print(" : ");
		Serial.println("Index out of bound");
	}
}


#endif /* DEBUG */
