#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include "Arduino.h"

/** 
 *  Serial Communication
 *  
 *@author Mario Van Etten 
 *@data   21-06-2017 
 *  
 *Serial Communication Handles
 *incoming serial data and 
 *outgoing serial data it 
 *also writes the data into 
 *EEPROM memory. To be used 
 *in the main execution state 
 *by the ProtocolInterpreter 
 *to initialize the classes.
 */

class SerialCommunication
{
public:  
  SerialCommunication();
  ~SerialCommunication();

  void readSerial();

  void sendIdentificationBlock();
  void sendContinueBlock();
  void sendSuccessBlock();
  void sendFailedBlock();
  
  void compareSerialBlocks(const uint8_t* data);
  boolean compareStartCommunicationBlock(const uint8_t* data);
  boolean compareCalculateCyclicRedundancyCheck(const uint8_t* data);


private: 
  void writeBufferToSerial(const uint8_t* data);
  void updateEEPROM(const uint8_t* data, int length); 
  
  boolean calculateCyclicRedundancyCheckFromEEPROM();

  boolean compareCyclicRedundancyBeginBlock(const int* data);
  boolean compareCyclicRedundancyEndBlock(const int* data);


  long baudrate;
  boolean crc; 
  int dataIndex; 

  int eepromSize;
  int eepromCurrentAddress;
   
  uint8_t data[32];

  int eepromBuffer[32];
  uint8_t crcBuffer[4];

  static uint8_t id01gh[6]; //Identification Message
  static uint8_t contsc[6]; //Continue Message
  static uint8_t succes[6];
  static uint8_t failta[6];

};

#endif //SERIALCOMMUNICATION_H


