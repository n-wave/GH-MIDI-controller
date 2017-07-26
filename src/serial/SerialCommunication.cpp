#include "SerialCommunication.h"
#include "CyclicRedundancyCheck.h"
#include "EEPROM.h"

/** Tested and Verified **/

SerialCommunication::SerialCommunication()
  : baudrate(9600), 
    crc(false),
    dataIndex(0),
    eepromSize(0),
    eepromCurrentAddress(0)
{

  for(int i=0; i<32; i++){
    data[i] = 0x00;
    eepromBuffer[i] = 0x00;
  }
  
  eepromSize = (EEPROM.length()-1);
  
  Serial.begin(baudrate);
}

SerialCommunication::~SerialCommunication()
{
  Serial.end();  
}

void SerialCommunication::readSerial(){

  int bufferSize = Serial.available();

  if(bufferSize > 0 && bufferSize <= 32){
    dataIndex &= 31; //Keep the Array in the specified bound.
    data[dataIndex] = Serial.read(); //Fill the array.

    dataIndex++;
  } else{
      dataIndex = 0;
      
      /** Flush Buffer **/     
      if(bufferSize > 32){   
        for(int i=0; i<bufferSize; i++){
          Serial.read();
        }
      }
  }
  
  if(dataIndex == 6 && bufferSize <= 6){
    compareSerialBlocks(data);
    dataIndex = 0;
  }
  /** Actual data representing the 
   *  preset values.
   */
  if(dataIndex == 32){   
    updateEEPROM(data, 32);
    sendContinueBlock();
    dataIndex = 0;
  }  
}

void SerialCommunication::writeBufferToSerial(const uint8_t* data){
  for(int i=0; i<6; i++){
    Serial.write(data[i]);
    delayMicroseconds(100);
  }  
}

/** Update EEPROM 
 *  
 *  EEPROM.update checks if the data 
 *  in the memory is the same if true, 
 *  it doesn't overwrite the memory cell
 *  prolonging the life of the memory.
 *  Use eepromIndex to update to memory 
 *  Adress, wrap around if it exceeds 
 *  eeprom memory. If this happens 
 *  it will ultimately result in failing 
 *  the crc calculation.
 *  
 */

void SerialCommunication::updateEEPROM(const uint8_t* data, int length){
  for(int i=0; i<length; i++){
    eepromCurrentAddress &= eepromSize;

    EEPROM.update(eepromCurrentAddress, data[i]);
      
    eepromCurrentAddress++;
    delayMicroseconds(100);
  }
}


/** Calculate Cyclic Redundancy Check from EEPROM **/ 
boolean SerialCommunication::calculateCyclicRedundancyCheckFromEEPROM()
{ 
  boolean result = false;
  int bgnBlockBuffer[8];
  int endBlockBuffer[8];
  
  if(eepromCurrentAddress == 1984){
    int bgnIndex = 1952;
    int endIndex = 1964;
    long crcConvert = 0L;
    long crcIntern = 0L;

    for(int i=0; i<8; i++){
      bgnBlockBuffer[i] = EEPROM.read(bgnIndex++);
      delayMicroseconds(250);
    }

  for(int i=0; i<8; i++){
      endBlockBuffer[i] = EEPROM.read(endIndex++);
      delayMicroseconds(250);
    }
  
    if(compareCyclicRedundancyBeginBlock(bgnBlockBuffer) && compareCyclicRedundancyEndBlock(endBlockBuffer))
    {
      //result = true;
      CyclicRedundancyCheck crc = CyclicRedundancyCheck();
      int index = 1960;     
      int crcBuffer[4];
      for(int i=0; i<4; i++){
        crcBuffer[i] = EEPROM.read(index);
        index++;
      }

      crcConvert = crc.convertToLong(crcBuffer ,4);

      int dataBuffer[1952];
          
      for(int i=0; i<1952; i++){
        dataBuffer[i] = EEPROM.read(i);  
        delayMicroseconds(100);
      }

      crcIntern = crc.calculateCyclicRedundancyCheck(dataBuffer, 1952);

      if(crcIntern == crcConvert){  
        result = true;
      }
    }
  }
  return result;
}

/** Send Identification Message */

void SerialCommunication::sendIdentificationBlock(){
  writeBufferToSerial(id01gh);
}

void SerialCommunication::sendContinueBlock(){
  writeBufferToSerial(contsc);
}

void SerialCommunication::sendSuccessBlock(){
  writeBufferToSerial(succes);
}

void SerialCommunication::sendFailedBlock(){
  writeBufferToSerial(failta);
}

 
/** 
 *  findMessageBlock compares the incoming serial 
 *  data. When succesfully received take apprioprate
 *  action(s).  
 */

void SerialCommunication::compareSerialBlocks(const uint8_t* data){
/** 
 * Start Communication Block (STARTC) has been received. 
 * Send Identification Block (ID01GH). The java program 
 * will now start sending data to the MCU in chunks of 32 
 * bytes. These are written/updated to the EEPROM.
 */ 
 
    if(compareStartCommunicationBlock(data)){
      eepromCurrentAddress = 0;
      sendIdentificationBlock();
      return;
    }
/**
 * Cyclic Redundancy Check (CRCBGN) has been received. 
 * send Continue Block (CONT) and set crc to true. 
 * The next four bytes will be the chopped up crc.
 * This will then be used to calculate the crc based
 * on the data written to the EEPROM memory.
 */
    
    if(compareCalculateCyclicRedundancyCheck(data)){
       
      if(calculateCyclicRedundancyCheckFromEEPROM()){
       sendSuccessBlock();
      } else {
       sendFailedBlock(); 
      } 
      return;
    }
}


/**   
 *  Compare supplied data in the buffer, if true 
 *  EEPROM data can be written in memory.  
 */
  boolean SerialCommunication::compareStartCommunicationBlock(const uint8_t* data){
    boolean result = false; 

    if(
        data[0] == 0x53 &&
        data[1] == 0x54 &&
        data[2] == 0x41 &&
        data[3] == 0x52 &&
        data[4] == 0x54 &&
        data[5] == 0x43
      )
     {
      result = true;
     }

    return result;   
  }

boolean SerialCommunication::compareCalculateCyclicRedundancyCheck(const uint8_t* data){
  boolean result = false;

  if(
      data[0] == 0x43 &&
      data[1] == 0x41 &&
      data[2] == 0x4C &&
      data[3] == 0x43 &&
      data[4] == 0x52 &&
      data[5] == 0x43 
     )
  {
    result = true;
  }
  return result;
}

boolean SerialCommunication::compareCyclicRedundancyBeginBlock(const int* data){
  boolean result = false;

  if(
      data[0] == 0x43 &&  //C
      data[1] == 0x52 &&  //R
      data[2] == 0x43 &&  //C
      data[3] == 0x42 &&  //B
      data[4] == 0x47 &&  //G
      data[5] == 0x4E &&  //N
      data[6] == 0x42 &&  //B
      data[7] == 0x4C     //L
    )
  {
    result = true;    
  }

  return result;
}

boolean SerialCommunication::compareCyclicRedundancyEndBlock(const int* data){
  boolean result = false;

  if(
      data[0] == 0x43 &&  //C
      data[1] == 0x52 &&  //R
      data[2] == 0x43 &&  //C 
      data[3] == 0x45 &&  //E
      data[4] == 0x4E &&  //N
      data[5] == 0x44 &&  //D
      data[6] == 0x42 &&  //B
      data[7] == 0x4C     //L
     )
  {
      result = true;
  }
  
  return result;
}

uint8_t SerialCommunication::id01gh[6] = {
                                          0x49, //I
                                          0x44, //D
                                          0x00, //0
                                          0x01, //1
                                          0x47, //G
                                          0x48  //H    
                                         };

uint8_t SerialCommunication::contsc[6] = {
                                          0x43, //C
                                          0x4F, //O
                                          0x4E, //N
                                          0x54, //T
                                          0x53, //S
                                          0x43  //C
                                         };

uint8_t SerialCommunication::succes[6] = {
                                          0x53, //S
                                          0x55, //U
                                          0x43, //C
                                          0x43, //C
                                          0x45, //E
                                          0x53  //S  
                                         };

uint8_t SerialCommunication::failta[6] = {
                                          0x46, //F
                                          0x41, //A
                                          0x49, //I
                                          0x4C, //L
                                          0x54, //T
                                          0x41  //A    
                                         };




 
