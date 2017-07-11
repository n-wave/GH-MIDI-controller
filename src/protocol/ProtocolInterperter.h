/*
 * ProtocolInterperter.h
 *
 *  Created on: Jul 7, 2017
 *      Author: mario
 */

#ifndef SRC_PROTOCOL_PROTOCOLINTERPERTER_H_
#define SRC_PROTOCOL_PROTOCOLINTERPERTER_H_


#include "Arduino.h"
#include "../testing/configuration.h"
#include "../builders/Scene.h"
#include "../serial/CyclicRedundancyCheck.h"

class ProtocolInterperter {
public:
	ProtocolInterperter();
	~ProtocolInterperter();

	boolean getMemoryStatus();
	void configureScene(const Scene& scene, int sceneNumber);


private:
	boolean checkMemory();
	boolean setIndices(int sceneNumber);

	int getType(const int* data);

	boolean compareSceneBlock(const int* data, int number);
	boolean compareStartBlock(const int* data);
	boolean compareEndBlock(const int* data);
	boolean compareCyclicRedundancyCheckBeginBlock(const int* data);
	boolean compareCyclicRedundancyCheckEndBlock(const int* data);



	int startIndex;
	int endIndex;
	boolean memCheck;
	CyclicRedundancyCheck crc;
	int eepromBuffer[1952];
};

#endif /* SRC_PROTOCOL_PROTOCOLINTERPERTER_H_ */
