/*
 * ProtocolInterperter.cpp
 *
 *  Created on: Jul 7, 2017
 *      Author: mario
 */

#include "ProtocolInterperter.h"
#include "EEPROM.h"

ProtocolInterperter::ProtocolInterperter() :
	memCheck(false),
	crc(CyclicRedundancyCheck())
{
	memCheck = this->checkMemory();

#ifdef DEBUG
	if(memCheck){
		Serial.println("-------------------");
		Serial.println("Memory check passed");
		Serial.println("-------------------");
	} else {
		Serial.println("-----------------------");
		Serial.println("Memory check has failed");
		Serial.println("-----------------------");
	}
#endif /* DEBUG */
}

ProtocolInterperter::~ProtocolInterperter() {
	// TODO Auto-generated destructor stub
}

boolean ProtocolInterperter::getMemoryStatus(){
	return memCheck;
}

boolean ProtocolInterperter::configureScene(Scene& scene, int sceneNumber){
	boolean result = false;

	if(sceneNumber >= 0 && sceneNumber < 4 ){
		int sceneBuffer[488];
		int dataBuffer[16];
		int bufferIndex = 0;
		int dataIndex = 0;


		this->setSceneBuffer(sceneBuffer, sceneNumber);

		while(dataIndex < 8){
			dataBuffer[dataIndex++] = sceneBuffer[bufferIndex++];
		}

		/* Start Loading Scene Data */

		if(this->compareSceneBlock(dataBuffer,sceneNumber)){

			#ifdef DEBUG
			Serial.println("loading scene Data");
			Serial.println("------------------");
			Serial.print("  Scene Number : ");
		    Serial.println(sceneNumber);
			Serial.println("------------------");
			#endif

			dataIndex = 0; //Reset dataIndex for dataBuffer

			/* Scene nr datablock has beend confirmed
			 * next 16 Bytes are the SceneData, start
			 * filling up the dataBuffer from scratch and
			 * supply it to the scene.
			 */

			while(dataIndex < 16){
				dataBuffer[dataIndex++] = sceneBuffer[bufferIndex++];
			}

			if(dataBuffer[0] == 0xF0 && dataBuffer[1] == 0xEA && dataBuffer[15] == 0xFF){
				/* The 16 Bytes in the buffer coincides with the sceneData */
				scene.setSceneData(dataBuffer);

			} else {
				#ifdef DEBUG
				Serial.println("Error occurred in ProtocolInterperter::configureScene(const Scene&, int)");
				Serial.println("SceneData is corrupted, doesn't coincide with the protocol, exiting method");
				#endif /* DEBUG */
				return result;
			}

		} else {
			#ifdef DEBUG
			Serial.println("Error occurred in ProtocolInterperter::configureScene(const Scene&, int)");
			Serial.println("Couldnt't find the SCENENR data block, exiting method");
			#endif
			return result;
		}

		/* End Loading Scene Data */

		/* Next Step is Loading up the start Block and comparing it */
		dataIndex = 0;

		while(dataIndex < 8){
			dataBuffer[dataIndex++] = sceneBuffer[bufferIndex++];
		}

		if(this->compareStartBlock(dataBuffer)){
			/* Start Block Has Been found
			 * Start loading up the controllers
			 **/

			#ifdef DEBUG
			Serial.println("Found Start Block, loading the controller data");
			#endif

			boolean run = true;
			int controllerNumber = 0;


			while(run){
				dataIndex = 0;

				while(dataIndex < 8){
					dataBuffer[dataIndex++] = sceneBuffer[bufferIndex++];
				}

				if(this->compareEndBlock(dataBuffer) || bufferIndex >= 488 || controllerNumber >= 28){
					run = false;
					result = true;
				} else {
					/* Keep filling the Buffer */
					while(dataIndex < 16){
						dataBuffer[dataIndex++] = sceneBuffer[bufferIndex++];
					}

					int type = this->getType(dataBuffer);
					scene.setController(controllerNumber, type, dataBuffer);
					controllerNumber++;
				}
			}
		} else {
			#ifdef DEBUG
			Serial.println("Error occurred in ProtocolInterperter::configureScene(const Scene&, int)");
			Serial.println("Couldnt't find the Start data block, exiting method");
			#endif

			return result;
		}
	}
#ifdef DEBUG
	else {
		Serial.println("Error occurred in ProtocolInterperter::configureScene(int, int*)");
		Serial.println("Supplied wrong sceneNumber");
	}
#endif /* DEBUG */
	return result;
}


void ProtocolInterperter::setSceneBuffer(int* data, int sceneNumber){
	int bufferIndex = 0;
	int startIndex = 0;
	int endIndex = 0;
	boolean run = true;

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

	while(run){
		data[bufferIndex] = EEPROM.read(startIndex);

		bufferIndex++;
		startIndex++;


		if(bufferIndex >= 488 || startIndex >= endIndex){
			run = false;
		}
	}
}

/* Supply with 16Bit block of data from thereon
 * the data in the buffer will be matched
 * with the expected data for specific dataStructures
 * and an number will be returned corresponding with
 * the matching controllers.
 *
 */

int ProtocolInterperter::getType(const int* data){
	if(data[0] == 0xF0)
	{
		/* Disabled Controller Data Block*/
		if(data[1] == 0xEF && data[3] == 0xFF){
			return 0;
		}
		/* Program Change Data Block */
		if(data[1] == 0xE0 && data[5] == 0xFF){
			return 1;
		}
		/* Note Velocity Data Block */
		if(data[1] == 0xE1 && data[6] == 0xFF){
			return 2;
		}
		/* Note Control Change 8Bit Data Block */
		if(data[1] == 0xE2 && data[6] == 0x00 && data[10] == 0xFF){
			return 3;
		}
		/* Note Control Change 16Bit Data Block */
		if(data[1] == 0xE2 && data[6] == 0x01 && data[12] == 0xFF){
			return 4;
		}
		/* Pitch Bend Data */
		if(data[1] == 0xE3 && data[3] == 0xFF){
			return 5;
		}
		/* Pitch Bend Note Data */
		if(data[1] == 0xE4 && data[5] == 0xFF){
			return 6;
		}
		/* Control Change 8Bit Data */
		if(data[1] == 0xE5 && data[3] == 0x00 && data[7] == 0xFF){
			return 7;
		}
		/* Control Change 16Bit Data */
		if(data[1] == 0xE5 && data[3] == 0x01 && data[9] == 0xFF){
			return 8;
		}
		/* Control Change Fade 8Bit Data */
		if(data[1] == 0xE6 && data[3] == 0x00 && data[12] == 0xFF){
			return 9;
		}
		/* Control Change Fade 16Bit Data */
		if(data[1] == 0xE6 && data[3] == 0x01 && data[15] == 0xFF){
			return 10;
		}
		/* Note Velocity Toggle data*/
		if(data[1] == 0xE7 && data[6] == 0xFF){
			return 11;
		}
		/* Note Control Change Toggle 8Bit data*/
		if(data[1] == 0xE8 && data[6] == 0x00 && data[10] == 0xFF){
			return 12;
		}
		/* Note Control Change Toggle 16Bit data*/
		if(data[1] == 0xE8 && data[6] == 0x01 && data[12] == 0xFF){
			return 13;
		}
		/* Control Change Toggle 8Bit data*/
		if(data[1] == 0xE9 && data[4] == 0x00 && data[8] == 0xFF){
			return 14;
		}
		/* Control Change Toggle 16Bit data*/
		if(data[1] == 0xE9 && data[4] == 1 && data[10] == 0xFF){
			return 15;
		}
		/* Control Change Fade Toggle 8Bit */
		if(data[1] == 0xEA && data[12] == 0xFF && (data[3] == 0 || data[3] == 2)){
			return 16;
		}
		/* Control Change Fade Toggle 16Bit */
		if(data[1] == 0xEA && data[15] == 0xFF && (data[3] == 1 || data[3] == 3)){
			return 17;
		}
	}
	return 0; // If no matching structures are found return 0
			  // The scene will load a disabled controller on 0
}


/* Check if the data stored in EEPROM memory
 * Hasn't been corrupted in any way, By
 * checking if the dataBlocks are present
 * in memory on the specified places defined
 * by the protocol document. Than proceed
 * by retrieving the stored crc in the eeprom
 * and compare it with the calculated eeprom.
 *
 */

boolean ProtocolInterperter::checkMemory(){
	boolean result = false;

	long calCRC = 0L;
	long retCRC = 0L;

	int index = 0;
	int crcBuffer[4];
	int crcBgnBuffer[8];
	int crcEndBuffer[8];

	int buffer[1952];

	/* Fill preset data */
	for(int i=0; i<1952; i++){
	  buffer[i] = EEPROM.read(i);
	  delayMicroseconds(150);
	}

	/* calculate crc */
	calCRC = crc.calculateCyclicRedundancyCheck(buffer, 1952);

	/* fill crcBgnBuffer if data in EEPROM
	 * is valid it should contain CRCBGNBL
	 */
	for(int i=1952; i<1960; i++){
		crcBgnBuffer[index] = EEPROM.read(i);
		index++;
	}
	index = 0;

	/* fill crcBgnBuffer if data in EEPROM
	 * is valid it should contain CRCBGNBL
	 */

	for(int i=1964; i<1972; i++){
		crcEndBuffer[index] = EEPROM.read(i);
		index++;
	}

	if(this->compareCyclicRedundancyCheckBeginBlock(crcBgnBuffer) &&
	    this->compareCyclicRedundancyCheckEndBlock(crcEndBuffer))
	{

	/* Fill crcBuffer with crc Stored in EEPROm */
		crcBuffer[0] = EEPROM.read(1960);
		crcBuffer[1] = EEPROM.read(1961);
		crcBuffer[2] = EEPROM.read(1962);
		crcBuffer[3] = EEPROM.read(1963);

		retCRC = crc.convertToLong(crcBuffer, 4);
	}

	if(calCRC == retCRC){
		result = true;
	}

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
#ifdef COMPAREBLOCKS
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
#endif /* COMPAREBLOCKS */

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
#ifdef COMPAREBLOCKS

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
#endif /* COMPAREBLOCKS */

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
#ifdef COMPAREBLOCKS
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
#endif /* COMPAREBLOCKS */
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
#ifdef COMPAREBLOCKS
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
#endif /* COMPAREBLOCKS */
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
#ifdef COMPAREBLOCKS
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
#endif /* COMPAREBLOCKS */
	return result;
}
