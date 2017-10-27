#ifndef PROTOCOLTOSTRING_H
#define PROTOCOLTOSTRING_H

#include "Arduino.h"
#include "../serial/CyclicRedundancyCheck.h"
/** 
 *  Prints out the current data hold in 
 *  the EEPROM memory and converts it to 
 *  readable Strings, based on the 
 *  protocol information. Only to be used
 *  while testing.
 */

class ProtocolToString
{
public:
  ProtocolToString();
  ~ProtocolToString();  

  int compareProtocolBlocks(const int* data);

  void printMemoryCheck();
  void printEEPROM();
  void printContentsToString();

  void printController(int scene, int number);

private:
  int sceneBlockFound;

  String dataBlockToString(int option);
  String dataStructureToString(const int* data);

  boolean compareSceneBlock(const int* data);
  boolean compareStartBlock(const int* data);
  boolean compareEndBlock(const int* data);
  boolean compareCyclicRedundancyCheckBeginBlock(const int* data);
  boolean compareCyclicRedundancyCheckEndBlock(const int* data);

  String programChangeToString(const int* data);
  String noteVelocityToString(const int* data);
  String noteControlChangeToString(const int* data);
  String pitchBendToString(const int* data);
  String pitchBendNoteToString(const int* data);
  String controlChangeToString(const int* data);
  String controlChangeFadeToString(const int* data);

  String noteVelocityToggleToString(const int* data);
  String noteControlChangeToggleToString(const int* data);
  String controlChangeToggleToString(const int* data);
  String controlChangeFadeToggleToString(const int* data);

  String disabledControllerToString(const int* data);
  String sceneDataToString(const int* data);

  String contents;
  int eepromBuffer[1984];

  CyclicRedundancyCheck crc;;
};


#endif //PROTOCOLTOSTRING_H
