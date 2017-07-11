/*
 * ProtocolInterperter.cpp
 *
 *  Created on: Jul 7, 2017
 *      Author: mario
 */

#include "ProtocolInterperter.h"
#include "EEPROM.h"

ProtocolInterperter::ProtocolInterperter() :
	startIndex(0),
	endIndex(0),
	memCheck(false),
	crc(CyclicRedundancyCheck())
{
	memCheck = this->checkMemory();

#ifdef DEBUG
	if(memCheck){
		Serial.println("Memory check passed");
	} else {
		Serial.println("Memory check has failed");
	}
#endif /* DEBUG */
}

ProtocolInterperter::~ProtocolInterperter() {
	// TODO Auto-generated destructor stub
}

boolean ProtocolInterperter::getMemoryStatus(){
	return memCheck;
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
				this->startIndex = 0;
				this->endIndex = 488;
				break;
			case 1:
				this->startIndex = 488;
				this->endIndex = 976;
				break;
			case 2:
				this->startIndex = 976;
				this->endIndex = 1464;
				break;
			case 3:
				this->startIndex = 1464;
				this->endIndex = 1952;
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

int ProtocolInterperter::getType(const int* data){

	/* Disabled Controller Data Block*/
	if(data[0] == 0xF0 && data[1] == 0xEF && data[3] == 0xFF){
		return 0;
	}
	/* Program Change Data Block */
	if(data[0] == 0xF0 && data[1] == 0xE0 && data[5] == 0xFF){
		return 1;
	}
	/* Note Velocity Data Block */
	if(data[0] == 0xF0 && data[1] == 0xE1 && data[6] == 0xFF){
		return 2;
	}
    /* Note Control Change 8Bit Data Block */
	if(data[0] == 0xF0 && data[1] == 0xE2 && data[6] == 0x00 && data[10] == 0xFF){
		return 3;
	}
	/* Note Control Change 16Bit Data Block */
	if(data[0] == 0xF0 && data[1] == 0xE2 && data[6] == 0x01 && data[12] == 0xFF){
		return 4;
	}
	/* Pitch Bend Data */
	if(data[0] == 0xF0 && data[1] == 0xE3 && data[3] == 0xFF){
		return 5;
	}
	/* Pitch Bend Note Data */
	if(data[0] == 0xF0 && data[1] == 0xE4 && data[5] == 0xFF){
		return 6;
	}
	/* Control Change 8Bit Data */
	if(data[0] == 0xF0 && data[1] == 0xE5 && data[3] == 0x00 && data[7] == 0xFF){
		return 7;
	}
	/* Control Change 16Bit Data */
	if(data[0] == 0xF0 && data[1] == 0xE5 && data[3] == 0x01 && data[9] == 0xFF){
		return 8;
	}
	/* Control Change Fade 8Bit Data */
	if(data[0] == 0xF0 && data[1] == 0xE6 && data[3] == 0x00 && data[12] == 0xFF){
		return 9;
	}
	/* Control Change Fade 16Bit Data */
	if(data[0] == 0xF0 && data[1] == 0xE6 && data[3] == 0x01 && data[15] == 0xFF){
		return 10;
	}

	return 0;
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

	/* Fill preset data */
	for(int i=0; i<1952; i++){
	  eepromBuffer[i] = EEPROM.read(i);
	  delayMicroseconds(150);
	}

	/* calculate crc */
	calCRC = crc.calculateCyclicRedundancyCheck(this->eepromBuffer, 1952);

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
