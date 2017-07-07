/*
 * Scene.cpp
 *
 *  Created on: Jul 7, 2017
 *      Author: mario
 */

#include "Scene.h"

#include "../controller/PitchBendNote.h"
#include "../controller/PitchBend.h"
#include "../controller/NoteVelocity.h"
#include "../controller/NoteControlChange8Bit.h"
#include "../controller/NoteControlChange16Bit.h"
#include "../controller/ControlChangeFade8Bit.h"
#include "../controller/ControlChangeFade16Bit.h"
#include "../controller/ControlChange8Bit.h"
#include "../controller/ControlChange16Bit.h"

Scene::Scene() :
	nrOfProgramChanges(0),
	name(String()),
	programChange(NULL)

{
	// TODO Auto-generated constructor stub
	setName("Default");

	for(int i=0;i<NROFCONTROLLERS; i++){
		controllers[i] = NULL;
	}
}

Scene::Scene(String name) :
	nrOfProgramChanges(0),
	name(String(name)),
	programChange(NULL)
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
		data[1] == 0xEA &&
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

				index++;
				channelIndex += 3;
				bankIndex += 3;
				programIndex += 3;

				if(index == nrOfProgramChanges){
					run = false;
				}
			#ifdef DEBUG
				    Serial.println("--------------------");
					Serial.println("Testing setSceneData");
				    Serial.println("--------------------");
					Serial.print("nrOfProgramChanges : ");
					Serial.println(nrOfProgramChanges);
					Serial.print("index : ");
					Serial.println(index);
					Serial.print("channelIndex : ");
					Serial.println(channelIndex);
					Serial.print("bankIndex : ");
					Serial.println(bankIndex);
					Serial.print("programIndex : ");
					Serial.println(programIndex);

					Serial.println("Created Program Change Data");

					for(int i=0; i<6; i++){
						Serial.print("Byte[");
						Serial.print(i);
						Serial.print("] : ");
						Serial.println(dataBuffer[i]);
					}
			#endif /* DEBUG */

			} while(run);

		}
	}

	return result;
}

boolean Scene::setController(int number, int type, const int* data){
	boolean result = false;

	if(
	   number >= 0 &&
	   number < 28 &&
	   type >= 0 &&
	   type <= 9
	  )
	{
		switch(type){
			case 0:
				controllers[number] = new ProgramChange(data);
				break;
			case 1:
				controllers[number] = new NoteVelocity(data);
				break;
			case 2:
				controllers[number] = new NoteControlChange8Bit(data);
				break;
			case 3:
				controllers[number] = new NoteControlChange16Bit(data);
				break;
			case 4:
				controllers[number] = new PitchBend(data);
				break;
			case 5:
				controllers[number] = new PitchBendNote(data);
				break;
			case 6:
				controllers[number] = new ControlChange8Bit(data);
				break;
			case 7:
				controllers[number] = new ControlChange16Bit(data);
				break;
			case 8:
				controllers[number] = new ControlChangeFade8Bit(data);
				break;
			case 9:
				controllers[number] = new ControlChangeFade16Bit(data);
				break;
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

void Scene::setName(String name){
	this->name = name;
}

String Scene::getName(){
	return name;
}

#ifdef DEBUG
void Scene::printPogramChangeContents(){
	if(nrOfProgramChanges > 0){
		String result = String();

		for(int i=0; i<nrOfProgramChanges; i++){
			result = programChange[i]->toString();

			delay(250);
			Serial.println(result);
		}
	} else {
		Serial.println("No programChange objects initialized");
	}
}
#endif /* DEBUG */
