/*
 * ProtocolInterperter.cpp
 *
 *  Created on: Jul 7, 2017
 *      Author: mario
 */

#include "ProtocolInterperter.h"

ProtocolInterperter::ProtocolInterperter() :
	startIndex(0),
	endIndex(0)
{
	// TODO Auto-generated constructor stub

}

ProtocolInterperter::~ProtocolInterperter() {
	// TODO Auto-generated destructor stub
}


void ProtocolInterperter::configureScene(const Scene& scene, int sceneNumber){
	if(this->setIndices(sceneNumber)){



	}
}

/**
 * The configuration data for one scene is stored in
 * blocks of 488 bytes. The controller has four scenes
 * stored in EEPROM memory. This function sets start
 * and end indices based on the scene number that needs
 * to be configured.
 */

boolean ProtocolInterperter::setIndices(int sceneNumber){
	boolean result = false;

	if(sceneNumber >= 0 && sceneNumber < 4){
		switch(sceneNumber){
			case 0:
				startIndex = 0;
				endIndex = 488;
				break;
			case 1:
				startIndex = 488;
				endIndex = 976;
				break;
			case 2:
				startIndex = 976;
				endIndex = 1464;
				break;
			case 3:
				startIndex = 1464;
				endIndex = 1952;
				break;
		}
	result = true;
	}
#ifdef DEBUG
	else {
		Serial.println("Error occurred in ProtocolInterperter::setIndices(int sceneNumber)");
		Serial.println("Supplied wrong scene Number");
	}
#endif /* DEBUG */

	return result;
}

boolean ProtocolInterperter::compareSceneBlock(const int* data, int number){
	boolean result = false;

	if(
		data[0] == 'S' && //0x53, 83
		data[1] == 'C' && //0x43, 67
		data[2] == 'E' && //0x45, 69
		data[3] == 'N' && //0x4E, 78
		data[4] == 'E' && //0x45, 69
		data[5] == 'N' && //0x4E, 78
		data[6] == 'R' && //0x52, 82
		data[7] == number
	  )
	{
		result = true;
	}
#ifdef DEBUG
	else {
		Serial.println("Error occurred in ProtocolInterperter::compareSceneBlock(const int* data, int number)");
		Serial.println("Print data in the supplied array");

		for(int i=0; i<8; i++){
			Serial.print("Byte [");
			Serial.print(i);
			Serial.print("] ");
			Serial.println(data[i]);
		}
	}
#endif /* DEBUG */

	return result;
}

boolean ProtocolInterperter::compareStartBlock(const int* data){
	boolean result = false;

	if(
		data[0] == 'S' && //0x53, 83
		data[1] == 'T' && //0x54, 84
		data[2] == 'R' && //0x52, 82
		data[3] == 'B' && //0x42, 66
		data[4] == 'L' && //0x4C, 76
		data[5] == 'O' && //0x4F, 79
		data[6] == 'C' && //0x43, 67
		data[7] == 'K'	  //0x4B, 75
	  )
	{
		result = true;
	}
#ifdef DEBUG
	else {
		Serial.println("Error occurred in ProtocolInterperter::compareStartBlock(const int *data)");
		Serial.println("Print data in the supplied array");

		for(int i=0; i<8; i++){
			Serial.print("Byte [");
			Serial.print(i);
			Serial.print("] ");
			Serial.println(data[i]);
		}
	}
#endif /* DEBUG */
	return result;
}

boolean ProtocolInterperter::compareEndBlock(const int* data){
	boolean result = false;

	if(
		data[0] == 'E' && //0x45, 69
		data[1] == 'N' && //0x4E, 78
		data[2] == 'D' && //0x44, 68
		data[3] == 'B' && //0x42, 66
		data[4] == 'L' && //0x4C, 76
		data[5] == 'O' && //0x4F, 79
		data[6] == 'C' && //0x43, 67
		data[7] == 'K'	  //0x4B, 75
	  )
	{
		result = true;
	}
#ifdef DEBUG
	else {
		Serial.println("Error occurred in ProtocolInterperter::compareEndBlock(const int* data)");
		Serial.println("Print data in the supplied array");

		for(int i=0; i<8; i++){
			Serial.print("Byte [");
			Serial.print(i);
			Serial.print("] ");
			Serial.println(data[i]);
		}
	}
#endif /* DEBUG */
	return result;
}

boolean ProtocolInterperter::compareCyclicRedundancyCheckBeginBlock(const int* data){
	boolean result = false;

	if(
		data[0] == 'C' && //0x43, 67
		data[1] == 'R' && //0x52, 82
		data[2] == 'C' && //0x43, 67
		data[3] == 'B' && //0x42, 66
		data[4] == 'G' && //0x47, 71
		data[5] == 'N' && //0x4E, 78
		data[6] == 'B' && //0x42, 66
		data[7] == 'L'	  //0x4C, 76
 	  )
	{
		result = true;
	}
#ifdef DEBUG
	else {
		Serial.println("Error occurred in ProtocolInterperter::compareCyclicRedundancyCheckBeginBlock(const int* data)");
		Serial.println("Print data in the supplied array");

		for(int i=0; i<8; i++){
			Serial.print("Byte [");
			Serial.print(i);
			Serial.print("] ");
			Serial.println(data[i]);
		}
	}
#endif /* DEBUG */
	return result;
}

boolean ProtocolInterperter::compareCyclicRedundancyCheckEndBlock(const int* data){
	boolean result = false;

	if(
		data[0] == 'C' && //0x43, 67
		data[1] == 'R' && //0x52, 82
		data[2] == 'C' && //0x43, 67
		data[3] == 'E' && //0x45, 69
		data[4] == 'N' && //0x4E, 78
		data[5] == 'D' && //0x44, 68
		data[6] == 'B' && //0x42, 66
		data[7] == 'L'	  //0x4C, 76
	  )
	{
		result = true;
	}
#ifdef DEBUG
	else {
		Serial.println("Error occurred in ProtocolInterperter::compareCyclicRedundancyCheckEndBlock(const int* data)");
		Serial.println("Print data in the supplied array");

		for(int i=0; i<8; i++){
			Serial.print("Byte [");
			Serial.print(i);
			Serial.print("] ");
			Serial.println(data[i]);
		}
	}
#endif /* DEBUG */
	return result;
}
