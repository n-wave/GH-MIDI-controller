#include "CyclicRedundancyCheck.h"

CyclicRedundancyCheck::CyclicRedundancyCheck(){}

CyclicRedundancyCheck::~CyclicRedundancyCheck(){}

/**
 * long calculateCyclicRedundancyCheck(const int* dataArray, int& length);
 * 
 * Calculate the CRC based on the values supplied in the 
 * dataArray argument and return the result as a long
 * 
 */

long CyclicRedundancyCheck::calculateCyclicRedundancyCheck(const int* dataArray, int length)
{
  long crc = ~0L;

  for(int i=0; i<length; i++){
    crc = crcTable[(crc ^ dataArray[i]) & 0x0f] ^ (crc >> 4);
    crc = crcTable[(crc ^ (dataArray[i] >> 4)) & 0x0f] ^ (crc >> 4);
    crc = ~crc;
  }
  return crc;
}

/**
 * 
 *  void CyclicedundancyCheck(long& data, int* dataArray, int& length);
 *  
 *  Convert the long argument into a four individual bytes 
 *  And store them in the supplied dataArray argument.
 * 
 */

void CyclicRedundancyCheck::convertToByteArray(long& data, int* dataArray, int length){
  if(length == 4){
    dataArray[0] = (int)(data & 0xFF);
    dataArray[1] = (int)((data >> 8) & 0xFF);
    dataArray[2] = (int)((data >> 16) & 0xFF);
    dataArray[3] = (int)((data >> 24) & 0xFF);
  }
}

/** 
 *  Long CyclicRedundancyCheck(const in* dataArray);
 *  
 *  Pass array containing four values, representing 
 *  the converted CRC and convert it to a long
 *  representation
 *  
 */

long CyclicRedundancyCheck::convertToLong(const int* dataArray, int length){
  long data = 0L;

  if(length == 4){
    data = (dataArray[0] & 0xFF) |
           (dataArray[1] & 0xFF) << 8 |
           (dataArray[2] & 0xFF) << 16 |
           (dataArray[3] & 0xFF) << 24;  
  }
  return data;
}



