/*
 * Scene.h
 *
 *  Created on: Jul 7, 2017
 *      Author: mario
 */

#ifndef SRC_BUILDERS_SCENE_H_
#define SRC_BUILDERS_SCENE_H_

#include "Arduino.h"

#include "../testing/configuration.h"
#include "../controller/controller.h"
#include "../controller/ProgramChange.h"
#include "../dispatcher/Dispatcher.h"

class Scene {
public:
	Scene();
	Scene(const String& name);
	Scene(const String& name, Dispatcher* dispatcher);

	virtual ~Scene();

	void updateControllers();

	boolean setSceneData(const int* data);
	boolean setController(int number, int type, const int* data);

#ifdef DEBUG
	void printPogramChangeContents();
	void printPogramChangeContent(int index);
	void printControllerContents();
	void printControllerContent(int index);
#endif /* DEBUG */

private:
	enum {NROFCONTROLLERS = 28};

	const uint8_t ID = 0xEE;

	void setName(const String& name);



	int nrOfProgramChanges;
	String name;
	Controller* controllers[NROFCONTROLLERS];
	ProgramChange** programChange;
	Dispatcher* dispatcher;
};

#endif /* SRC_BUILDERS_SCENE_H_ */
