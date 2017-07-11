/*
 * Scene.h
 *
 *  Created on: Jul 7, 2017
 *      Author: mario
 */

#ifndef SRC_BUILDERS_SCENE_H_
#define SRC_BUILDERS_SCENE_H_
#define NROFCONTROLLERS 28

#include "Arduino.h"

#include "../testing/configuration.h"
#include "../controller/controller.h"
#include "../controller/ProgramChange.h"

class Scene {
public:
	Scene();
	Scene(const String& name);

	virtual ~Scene();

	boolean setSceneData(const int* data);
	boolean setController(int number, int type, const int* data);

#ifdef DEBUG
	void printPogramChangeContents();
	void printPogramChangeContent(int index);
	void printControllerContents();
	void printControllerContent(int index);
#endif /* DEBUG */

private:

	void setName(const String& name);

	int nrOfProgramChanges;
	String name;
	Controller* controllers[NROFCONTROLLERS];
	ProgramChange** programChange;
};

#endif /* SRC_BUILDERS_SCENE_H_ */
