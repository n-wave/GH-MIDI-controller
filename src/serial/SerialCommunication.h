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
  SerialCommunication(long baudrate);
  ~SerialCommunication();

  int readSerial();

  int getRequestedScene();
  int getRequestedController();

private:
  void sendIdentificationBlock();
  void sendContinueBlock();
  void sendSuccessBlock();
  void sendFailedBlock();
  
  int compareSerialBlocks(const uint8_t* data);

  void writeBufferToSerial(const uint8_t* data);
  void updateEEPROM(const uint8_t* data, int length); 
  boolean calculateCyclicRedundancyCheckFromEEPROM();

  boolean compareStartCommunicationBlock(const uint8_t* data);
  boolean compareCalculateCyclicRedundancyCheck(const uint8_t* data);
  boolean compareCyclicRedundancyBeginBlock(const int* data);
  boolean compareCyclicRedundancyEndBlock(const int* data);

  /* Debug messages */
  boolean compareDebugEnable(const uint8_t* data);
  boolean compareDebugCommands(const uint8_t* data);
  boolean compareMemoryCheck(const uint8_t* data);
  boolean comparePrintEEPROM(const uint8_t* data);
  boolean comparePrintContents(const uint8_t* data);
  boolean comparePrintController(const uint8_t* data);
  boolean comparePrintAnalogSensors(const uint8_t* data);
  boolean comparePrintSwitches(const uint8_t* data);
  boolean compareLedTest(const uint8_t* data);

  boolean compareDebugDisable(const uint8_t* data);



  long baudRate;
  boolean crc; 
  int dataIndex; 

  int eepromSize;
  int eepromCurrentAddress;
  int requestedScene;
  int requestedController;


  uint8_t data[32];

  int eepromBuffer[32];
  uint8_t crcBuffer[4];

  static uint8_t id01gh[6]; //Identification Message
  static uint8_t contsc[6]; //Continue Message
  static uint8_t succes[6]; //data successfully transferred to EEPROM
  static uint8_t failta[6]; //failed transfer send again
};

#endif //SERIALCOMMUNICATION_H


