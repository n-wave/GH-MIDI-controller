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
	Scene(String name);
	virtual ~Scene();

	String getName();

	boolean setSceneData(const int* data);
	boolean setController(int number, int type, const int* data);

#ifdef DEBUG
	void printPogramChangeContents();
#endif /* DEBUG */

private:
	void setName(String name);

	int nrOfProgramChanges;
	String name;
	Controller* controllers[NROFCONTROLLERS];
	ProgramChange** programChange;
};

#endif /* SRC_BUILDERS_SCENE_H_ */
