#include "ProtocolToString.h"
#include "EEPROM.h"


ProtocolToString::ProtocolToString() :
  sceneBlockFound(0),
  crc(CyclicRedundancyCheck())
{
  for(int i=0; i<1984; i++){
    eepromBuffer[i] = EEPROM.read(i);
    delayMicroseconds(25);
  }
}

ProtocolToString::~ProtocolToString(){}

void ProtocolToString::printMemoryCheck(){
	boolean result = crc.memoryCheck();

	if(result){
	    int index = 1960;
	    int crcBuffer[4];
	    long crcInMemory = 0L;


	    for(int i=0; i<4; i++){
	      crcBuffer[i] = eepromBuffer[index];
	      index++;
	    }

	    crcInMemory = crc.convertToLong(crcBuffer, 4);

		Serial.println("/---------------------------/");
		Serial.println("/----Memory Check passed----/");
		Serial.println("/---------------------------/");
		Serial.print("CRC : ");
		Serial.println(crcInMemory);
		Serial.println("/---------------------------/");

		for(int i=0; i<4; i++){
	        Serial.print("Byte[");
	        Serial.print(i);
	        Serial.print("] ");
	        Serial.println(crcBuffer[i]);
		}
		Serial.println("/---------------------------/");
	} else {
		Serial.println("/---------------------------/");
		Serial.println("/----Memory Check failed----/");
		Serial.println("/---------------------------/");
	}

}


void ProtocolToString::printEEPROM(){
    for(int i=0; i<1984; i++ ){
      delayMicroseconds(25);

      Serial.print("byte");
      Serial.print("[");
      Serial.print(i+1);
      Serial.print("] ");
      Serial.println(eepromBuffer[i], HEX);
  }
}


void ProtocolToString::printContentsToString(){
  String values;
  boolean run = true;

  int crcBuffer[4];
  long crcValue = 0L;
  int state = 0;

  int dataIndex = 0;
  int dataBuffer[16];
  int bufferIndex = 0;
    
  while(run)
  {
    bufferIndex = 0;
    values = "";
    dataBuffer[16] = {0};
    
    while(bufferIndex < 8){
      dataBuffer[bufferIndex] = eepromBuffer[dataIndex];
      bufferIndex++;
      dataIndex++;
    }

    state = compareProtocolBlocks(dataBuffer);
    
    if(state == 0){
        while(bufferIndex < 16){
        dataBuffer[bufferIndex] = eepromBuffer[dataIndex]; 
        bufferIndex++;
        dataIndex++;
      }
      values += dataStructureToString(dataBuffer);  
    }

    if(state == 1)
    {
      values += String(":----------------: \n");
      values += dataBlockToString(state);
      values += dataBuffer[7];
      values += "\n";
      values += String(":----------------: \n");

      state = 0;
    }

    if(state > 1 && state < 4){
        values += String("/----------------/\n");
        values += dataBlockToString(state);
        values += String("/----------------/\n");


    }

    if(state == 4){
      
        values += dataBlockToString(state);
        bufferIndex = 0;

        while(bufferIndex < 4){
          crcBuffer[bufferIndex] = eepromBuffer[dataIndex];

          values += String("byte[");
          values += String(bufferIndex);
          values += String("] ");
          values += crcBuffer[bufferIndex];
          values += String("\n");
          
          bufferIndex++;
          dataIndex++;
        }
        crcValue = crc.convertToLong(crcBuffer, 4);
        values += String("\n----------------\n");
        values += String("CRC : ");
        values += String(crcValue);
        values += String("\n----------------\n");
    }

    /** End of the contents  have been reached **/
    if(state == 5){
      values += dataBlockToString(state);
      values += String("End has been reached. Exiting loop");
      run = false;     
    }
    Serial.print(values);
    delay(10);
  }
  Serial.print("Bytes read : ");
  Serial.println(dataIndex);
  Serial.print("nr times compare sceneblock called : ");
  Serial.print(sceneBlockFound);
  /*Print CRC */ 
}

void ProtocolToString::printController(int scene, int controller)
{
	int index;
	int startIndex;
	int controllerIndex;


	int blockBuffer[8] = {0};
	int dataBuffer[16] = {0};

	String tmpString = "";

	switch(scene)
	{
		case 1:
		  startIndex = 0;
		  break;
		case 2:
          startIndex = 488;
		  break;
		case 3:
		  startIndex = 976;
		  break;
		case 4:
          startIndex = 1464;
		  break;
	}

	for(int i=0; i<8;i++){
		blockBuffer[i] = eepromBuffer[startIndex+i];
	}

	if(compareSceneBlock(blockBuffer) != true || blockBuffer[7] != scene-1){
		Serial.println("Error ocurred couldn't find scene block");
		return;
	}

	Serial.println("");
	Serial.println("Retrieving Data");
	delay(250);

	if(controller == 0){
		index = startIndex + 8;

		for(int i=0; i<16; i++){
			dataBuffer[i] = eepromBuffer[i+index];
		}
		tmpString += dataStructureToString(dataBuffer);
	} else if(controller > 0){
		controllerIndex = 16*(controller-1);
		index = startIndex + 32 + controllerIndex;;

		for(int i=0; i<16; i++){
			dataBuffer[i] = eepromBuffer[i+index];
		}
		tmpString += dataStructureToString(dataBuffer);
	}

	Serial.print("Scene : ");
	Serial.println(blockBuffer[7] + 1);
	delay(100);
	Serial.print("Controller :");
	Serial.println(controller);
	Serial.println("");
	delay(100);

	Serial.println(tmpString);
}


/** Return an Int Based on the 8 Byte Block supplied 
 *  as argument 
 */

int ProtocolToString::compareProtocolBlocks(const int* data){
  if(compareSceneBlock(data)){
    sceneBlockFound++;
    return 1; // Scene Block
  }

  if(compareStartBlock(data)){
    return 2; //Start Block
  }

  if(compareEndBlock(data)){
    return 3; //End Block
  }

  if(compareCyclicRedundancyCheckBeginBlock(data)){
    return 4; //CRC Begin
  }

  if(compareCyclicRedundancyCheckEndBlock(data)){
    return 5; //5: CRC End
  }

  return 0;
}

String ProtocolToString::dataBlockToString(int option){
  String values;
  
  switch(option){
    case 1:      
      values += String("   Scene nr : ");
      break;
    case 2:
      values += String("   Start Block \n");
      break;
    case 3:
      values += String("    End Block \n");
      break;
    case 4: 
      values += String("CRC Begin Block \n"); 
      break;
    case 5:
      values += String(" CRC End Block \n");
      break;  
  }

  return values;
}

String ProtocolToString::dataStructureToString(const int* data){
  String values;
  int id = data[1];

  switch(id){
    case 0xE0: //Program Change
      values += programChangeToString(data);
      break;
    case 0XE1: //Note Velocity
      values += noteVelocityToString(data);
      break;
    case 0xE2: //Note Control Change  
      values += noteControlChangeToString(data);
      break;
    case 0xE3: //Pitch Bend  
      values += pitchBendToString(data);
      break;
    case 0xE4: //Pitch Bend Note
      values += pitchBendNoteToString(data);
      break;
    case 0xE5: //Control Change 
      values += controlChangeToString(data);
      break;
    case 0xE6: //Control Change Fade
      values += controlChangeFadeToString(data);
      break;
    case 0xE7: //Note Velocity Toggle
      values += noteVelocityToggleToString(data);
      break;
    case 0xE8: //Note Control Change toggle
      values += noteControlChangeToggleToString(data);
      break;
    case 0xE9: //Control Change Toggle
      values += controlChangeToggleToString(data);
      break;
    case 0xEA: //Control Change Fade Toggle
      values += controlChangeFadeToggleToString(data);
      break;
    case 0xEE: //Scene Data
      values += sceneDataToString(data);
      break;
    case 0xEF: //Disabled Controller
      values += disabledControllerToString(data);
      break;
  }

  return values;
}

String ProtocolToString::programChangeToString(const int* data){
  String values;
  int startByte = data[0];
  int optionId = data[1];
  int endByte = data[5];

  if(startByte == 0xF0 && optionId == 0xE0 && endByte == 0xFF){
    values += String(data[0]) + " : Start Byte \n";
    values += String(data[1]) + " : Program Change ID \n";
    values += String(data[2]) + " : MIDI Channel \n";
    values += String(data[3]) + " : Bank Select \n";
    values += String(data[4]) + " : Program Select \n";
    values += String(data[5]) + " : End Byte \n";

    for(int i=6; i<16; i++){
      delayMicroseconds(10);
      if(data[i] == 0x00){
        values += String(data[i]) + " : Zero Padding \n";
      } else {
        values += String("Error \n");
      }
    }
  } else {
    values = String("Error while parsing program change data \n");
  }
  return values;
}

String ProtocolToString::noteVelocityToString(const int* data){
  String values;
  int startByte = data[0];
  int optionId = data[1];
  int endByte = data[6];

  if(startByte == 0xF0 && optionId == 0xE1 && endByte == 0xFF){
    values += String(data[0]) + " : Start Byte \n";
    values += String(data[1]) + " : Note Velocity ID \n";
    values += String(data[2]) + " : MIDI Channel \n";
    values += String(data[3]) + " : Pitch \n";
    values += String(data[4]) + " : Velocity \n";
    values += String(data[5]) + " : Link/Static Option \n";
    values += String(data[6]) + " : End Byte \n";

    for(int i=7; i<16; i++){
      delayMicroseconds(10);
      if(data[i] == 0x00){
        values += String(data[i]) + " : Zero Padding \n";
      } else {
        values += String("Error \n");
      }
    }
  } else {
    values = String("Error While Parsing Note Velocity Data \n");
  }
  return values;
}

String ProtocolToString::noteControlChangeToString(const int* data){
  String values;
  int startByte = data[0];
  int optionId = data[1];
  int resolutionByte = data[6];

  if(startByte == 0xF0 && optionId == 0xE2 && resolutionByte == 0x00 && data[10] == 0xFF){
    values += String(data[0]) + " : Start Byte \n";
    values += String(data[1]) + " : Note Control Change ID \n";
    values += String(data[2]) + " : MIDI Channel \n";
    values += String(data[3]) + " : Pitch \n";
    values += String(data[4]) + " : Velocity \n";
    values += String(data[5]) + " : Link/Static Option \n";
    values += String(data[6]) + " : Resolution 8-bit \n";
    values += String(data[7]) + " : Control Change Number \n";  
    values += String(data[8]) + " : Top Value \n";
    values += String(data[9]) + " : Bottom Value \n";
    values += String(data[10]) + " : End Byte \n";  

    for(int i=11; i<16; i++){
       delayMicroseconds(10);
       if(data[i] == 0x00){
            values += String(data[i]) + " : Zero Padding \n";
          } else {
            values += "Error \n";
       }      
    }
  } else if(startByte == 0xF0 && optionId == 0xE2 && resolutionByte == 0x01 && data[12] == 0xFF){
      values += String(data[0]) + " : Start Byte \n";
      values += String(data[1]) + " : Note Control Change ID \n";
      values += String(data[2]) + " : MIDI Channel \n";
      values += String(data[3]) + " : Pitch \n";
      values += String(data[4]) + " : Velocity \n";
      values += String(data[5]) + " : Link/Static Option \n";
      values += String(data[6]) + " : Resolution 14-bit \n";
      values += String(data[7]) + " : Control Change Number \n";
      values += String(data[8]) + " : Top Value MSB \n";
      values += String(data[9]) + " : Top Value LSB \n";
      values += String(data[10]) + " : Bottom Value MSB \n";
      values += String(data[11]) + " : Bottom Value LSB \n";
      values += String(data[12]) + " : End Byte \n";

      for(int i=13; i<16; i++){
        delayMicroseconds(10);
        if(data[i] == 0x00){
            values += String(data[i]) + " : Zero Padding \n";
          } else {
            values += "Error \n";
       }        
    }
  } else {
      values += String("Error while parsing Note Control Change data \n");
  }
  return values;
}

String ProtocolToString::pitchBendToString(const int* data){
  String values;
  int startByte = data[0];
  int optionId = data[1];
  int endByte = data[3];

  if(startByte == 0xF0 && optionId == 0xE3 && endByte == 0xFF){
    values += String(data[0]) + " : Start Byte \n";
    values += String(data[1]) + " : Pitch Bend ID \n";
    values += String(data[2]) + " : MIDI Channel \n";
    values += String(data[3]) + " : End Byte \n";

    for(int i=4; i<16; i++){
      delayMicroseconds(10);
      if(data[i] == 0x00){
        values += String(data[i]) + " : Zero Padding \n";
      } else {
        values += String("Error \n");
       }
    }
  } else {
    values += String("Error while parsing Pitch Bend data");
  }
  return values;
}
  
String ProtocolToString::pitchBendNoteToString(const int* data){
  String values;
  int startByte = data[0];
  int optionId = data[1];
  int endByte = data[5]; 

  if(startByte == 0xF0 && optionId == 0xE4 && endByte == 0xFF){
    values += String(data[0]) + " : Start Byte \n";
    values += String(data[1]) + " : Pitch Bend Note ID \n";
    values += String(data[2]) + " : MIDI Channel \n"; 
    values += String(data[3]) + " : Pitch \n";
    values += String(data[4]) + " : Velocity \n";
    values += String(data[5]) + " : End Byte \n";   

    for(int i=6; i<16; i++){
      delayMicroseconds(10);
      if(data[i] == 0x00){
        values += String(data[i]) + " : Zero Padding \n";
      } else {
        values += "Error \n";
      }
    }
  } else {
    values += String("Error while Parsing Pitch Bend Note Data \n");
  }

  return values;
}

String ProtocolToString::controlChangeToString(const int* data){
  String values;
  int startByte = data[0];
  int optionId = data[1];
  int resolutionByte = data[3];

  if(startByte == 0xF0 && optionId == 0xE5 && resolutionByte == 0x00){
    values += String(data[0]) + " : Start Byte \n";
    values += String(data[1]) + " : Control Change ID \n";
    values += String(data[2]) + " : MIDI Channel \n";
    values += String(data[3]) + " : Resolution 8-bit \n";
    values += String(data[4]) + " : Control Change Number \n";
    values += String(data[5]) + " : Top Value \n";
    values += String(data[6]) + " : Bottom Value \n";
    values += String(data[7]) + " : End Byte \n";
  
    for(int i=8; i<16; i++){
      delayMicroseconds(10);
      if(data[i] == 0x00){
        values += String(data[i]) + " : Zero Padding \n";
        } else {
            values += "Error \n";
        }
    } 
  } else if(startByte == 0xF0 && optionId == 0xE5 && resolutionByte == 0x01){
      values += String(data[0]) + " : Start Byte \n";
      values += String(data[1]) + " : Control Change ID \n";
      values += String(data[2]) + " : MIDI Channel \n";
      values += String(data[3]) + " : Resolution 14-bit \n";
      values += String(data[4]) + " : Control Change Number \n";
      values += String(data[5]) + " : Top Value MSB\n";
      values += String(data[6]) + " : Top Value LSB\n";
      values += String(data[7]) + " : Bottom Value MSB \n";
      values += String(data[8]) + " : Bottom Value MSB \n";
      values += String(data[9]) + " : End Byte \n";      

      for(int i=10; i<16; i++){
        if(data[i] == 0x00){
          values += String(data[i]) + " : Zero Padding \n";
        } else {
          values += "Error \n";
        }
      }
  } else {
    values = String("Error while parsing Control Change \n");
  }
  return values;
}

  
  String ProtocolToString::controlChangeFadeToString(const int* data){
    String values; 
    int startByte = data[0];
    int optionId = data[1];
    int resolutionByte = data[3];

    if(startByte == 0xF0 && optionId == 0xE6 && resolutionByte == 0x00 && data[12] == 0xFF){
      values += String(data[0]) + " : Start Byte \n";
      values += String(data[1]) + " : Control Change Fade ID \n";
      values += String(data[2]) + " : MIDI Channel \n";
      values += String(data[3]) + " : Resolution 8-bit \n";
      values += String(data[4]) + " : Control Change Number \n";
      values += String(data[5]) + " : Start \n";
      values += String(data[6]) + " : Hold \n";
      values += String(data[7]) + " : End \n";
      values += String(data[8]) + " : Fade In MSB \n";
      values += String(data[9]) + " : Fade In LSB \n";
      values += String(data[10]) + " : Fade Out MSB \n";
      values += String(data[11]) + " : Fade Out LSB \n";
      values += String(data[12]) + " : End Byte \n";
        
      for(int i=13; i<16; i++){
        delayMicroseconds(10);
        if(data[i] == 0x00){
          values += String(data[i]) + " : Zero Padding \n";
        } else {
          values += "Error \n";
        }     
      }
    } else if(startByte == 0xF0 && optionId == 0xE6 && resolutionByte == 0x01 && data[15] == 0xFF){
      values += String(data[0]) + " : Start Byte \n";
      values += String(data[1]) + " : Control Change Fade ID \n";
      values += String(data[2]) + " : MIDI Channel \n";
      values += String(data[3]) + " : Resolution 14-bit \n";
      values += String(data[4]) + " : Control Change Number \n";
      values += String(data[5]) + " : Start MSB\n";
      values += String(data[6]) + " : Start LSB\n";
      values += String(data[7]) + " : Hold MSB \n";
      values += String(data[8]) + " : Hold LSB \n";
      values += String(data[9]) + " : End MSB \n";
      values += String(data[10]) + " : End LSB \n";     
      values += String(data[11]) + " : Fade In MSB \n";
      values += String(data[12]) + " : Fade In LSB \n";
      values += String(data[13]) + " : Fade Out MSB \n";
      values += String(data[14]) + " : Fade Out LSB \n";
      values += String(data[15]) + " : End Byte \n";
        

    } else {
      values = String("Error while parsing Control Change Fade Data \n");
    }      
  return values;  
}

String ProtocolToString::sceneDataToString(const int* data){
  String values;
  int startByte = data[0];
  int optionId = data[1];
  int endByte = data[15];

  if(startByte == 0xF0 && optionId == 0xEE && endByte == 0xFF){
    values += String(data[0]) + " : Start Byte \n";
    values += String(data[1]) + " : Scene Data Id \n";
    values += String(data[2]) + " : Option \n";
    values += String(data[3]) + " : MIDI Channel 1 \n";
    values += String(data[4]) + " : Bank 1 \n";
    values += String(data[5]) + " : Program 1 \n";
    values += String(data[6]) + " : MIDI Channel 2 \n";
    values += String(data[7]) + " : Bank 2 \n";
    values += String(data[8]) + " : Program 2 \n";
    values += String(data[9]) + " : MIDI Channel 3 \n";
    values += String(data[10]) + " : Bank 3 \n";
    values += String(data[11]) + " : Program 3 \n";
    values += String(data[12]) + " : MIDI Channel 4 \n";
    values += String(data[13]) + " : Bank 4 \n";
    values += String(data[14]) + " : Program 4 \n";
    values += String(data[15]) + " : End Byte \n";    
  } else {
    values += String("Error while parsing Scene Data \n");
  }
  return values ;
}
  
String ProtocolToString::noteVelocityToggleToString(const int* data){
  String values;
  int startByte = data[0];
  int optionId = data[1];
  int endByte = data[6];

  if(startByte == 0xF0 && optionId == 0xE7 && endByte == 0xFF){
      values += String(data[0]) + " : Start Byte \n";
      values += String(data[1]) + " : Note Velocity Toggle ID \n";
      values += String(data[2]) + " : Switch Option \n";
      values += String(data[3]) + " : MIDI Channel \n";
      values += String(data[4]) + " : Pitch \n";
      values += String(data[5]) + " : Velocity \n";
      values += String(data[6]) + " : End Byte \n";

      for(int i=7; i<16; i++){
        delayMicroseconds(10);
        if(data[i] == 0x00){
          values += String(data[i]) + " : Zero Padding \n";
        } else {
          values += "Error \n";
        }
        }
  } else {
    values += String("Error while parsing Note Velocity Toggle Data");
  }
  return values;
}

String ProtocolToString::noteControlChangeToggleToString(const int* data){
  String values;
  int startByte = data[0];
  int optionId = data[1];
  int resolutionByte = data[6];

  if(startByte == 0xF0 && optionId == 0xE8 && resolutionByte == 0x00 && data[10] == 0xFF){
    values += String(data[0]) + " : Start Byte \n";
    values += String(data[1]) + " : Note Control Change Toggle ID \n";
    values += String(data[2]) + " : Toggle Option \n";
    values += String(data[4]) + " : Pitch \n";
    values += String(data[5]) + " : Velocity \n";
    values += String(data[6]) + " : Resolution 8-bit \n";
    values += String(data[7]) + " : Control Change Number \n";
    values += String(data[8]) + " : Top Value \n";
    values += String(data[9]) + " : Bottom Value \n";
    values += String(data[10]) + " : End Byte \n";

    for(int i=11; i<16; i++){
      delayMicroseconds(10);
      if(data[i] == 0x00){
        values += String(data[i]) + " : Zero Padding \n";
      } else {
        values += "Error \n";
      }
    }

  } else if(startByte == 0xF0 && optionId == 0xE8 && resolutionByte == 0x01 && data[12] == 0xFF){
    values += String(data[0]) + " : Start Byte \n";
    values += String(data[1]) + " : Note Control Change Toggle ID \n";
    values += String(data[2]) + " : Toggle Option \n";
    values += String(data[3]) + " : MIDI Channel \n";
    values += String(data[4]) + " : Pitch \n";
    values += String(data[5]) + " : Velocity \n";
    values += String(data[6]) + " : Resolution 14-bit \n";
    values += String(data[7]) + " : Control Change Number \n";
    values += String(data[8]) + " : Top Value MSB \n";
    values += String(data[9]) + " : Top Value LSB \n";
    values += String(data[10]) + " : Bottom Value MSB \n";
    values += String(data[11]) + " : Bottom Value LSB \n";
    values += String(data[12]) + " : End Byte \n";

    for(int i=13; i<16; i++){
      delayMicroseconds(10);
      if(data[i] == 0){
        values += String(data[i]) + " : Zero Padding \n";
      } else {
        values += "Error";
      }
    }
  } else {
    values += String("Error while parsing Note Control Change Toggle Data \n");
  }
  return values;
}

String ProtocolToString::controlChangeToggleToString(const int* data){
  String values;

  int startByte = data[0];
  int optionId = data[1];
  int resolutionByte = data[4];

  if(startByte == 0xF0 && optionId == 0xE9 && resolutionByte == 0x00 && data[8] == 0xFF){
    values += String(data[0]) + " : Start Byte \n";
    values += String(data[1]) + " : Control Change Toggle ID \n";
    values += String(data[2]) + " : Toggle Option \n";
    values += String(data[3]) + " : MIDI Channel \n";
    values += String(data[4]) + " : Resolution 8-bit \n";
    values += String(data[5]) + " : Control Change Number \n";
    values += String(data[6]) + " : Top Value \n";
    values += String(data[7]) + " : Bottom Value \n";
    values += String(data[8]) + " : End Byte \n";

    for(int i=9; i<16; i++){
      delayMicroseconds(10);
      if(data[i] == 0){
        values += String(data[i]) + " : Zero Padding \n";
      } else {
        values += "Error \n";
      }
    }
  } else if(startByte == 0xF0 && optionId == 0xE9 && resolutionByte == 0x01 && data[10] == 0xFF){
    values += String(data[0]) + " : Start Byte \n";
    values += String(data[1]) + " : Control Change Toggle ID \n";
    values += String(data[2]) + " : Toggle Option \n";
    values += String(data[3]) + " : MIDI Channel \n";
    values += String(data[4]) + " : Resolution 14-bit \n";
    values += String(data[5]) + " : Control Change Number \n";
    values += String(data[6]) + " : Top Value MSB\n";
    values += String(data[7]) + " : Top Value LSB\n";
    values += String(data[8]) + " : Bottom Value MSB \n";
    values += String(data[9]) + " : Bottom Value MSB \n";
    values += String(data[10]) + " : End Byte \n";

    for(int i=11; i<16; i++){
      delayMicroseconds(10);
      if(data[i] == 0){
        values += String(data[i]) + " : Zero Padding \n";
      } else {
        values += "Error \n";
      }
    }
  } else {
    values += String("Error while parsing Control Change Toggle Data \n");
  }

  return values;
}

String ProtocolToString::controlChangeFadeToggleToString(const int* data){
  String values;
  int startByte = data[0];
  int optionId = data[1];

  int toggleOption = (data[3] & 0B00000010) >> 1;
  int resolutionByte = data[3] & 0B00000001;

  if(startByte == 0xF0 && optionId == 0xEA && resolutionByte == 0x00 && data[12] == 0xFF){
    values += String(data[0]) + " : Start Byte \n";
    values += String(data[1]) + " : Control Change Fade Toggle ID \n";
    values += String(toggleOption) +  " : Toggle Option extracted from resolution\n";
    values += String(data[2]) + " : MIDI Channel \n";
    values += String(resolutionByte) + " : Resolution 8-bit \n";
    values += String(data[4]) + " : Control Change Number \n";
    values += String(data[5]) + " : Start \n";
    values += String(data[6]) + " : Hold \n";
    values += String(data[7]) + " : End \n";
    values += String(data[8]) + " : Fade In MSB \n";
    values += String(data[9]) + " : Fade In LSB \n";
    values += String(data[10]) + " : Fade Out MSB \n";
    values += String(data[11]) + " : Fade Out LSB \n";
    values += String(data[12]) + " : End Byte \n";

    for(int i=13; i<16; i++){
      delayMicroseconds(10);
      if(data[i] == 0){
        values += String(data[i]) + " : Zero Padding \n";
      } else {
        values += "Error";
      }
    }
  } else if(startByte == 0xF0 && optionId == 0xEA && resolutionByte == 0x01 && data[15] == 0xFF){
    values += String(data[0]) + " : Start Byte \n";
    values += String(data[1]) + " : Control Change Fade Toggle ID \n";
    values += String(toggleOption) + " : Toggle Option extracted from resolution \n";
    values += String(data[2]) + " : MIDI Channel \n";
    values += String(resolutionByte) + " : Resolution 14-bit \n";
    values += String(data[4]) + " : Control Change Number \n";
    values += String(data[5]) + " : Start MSB\n";
    values += String(data[6]) + " : Start LSB\n";
    values += String(data[7]) + " : Hold MSB \n";
    values += String(data[8]) + " : Hold LSB \n";
    values += String(data[9]) + " : End MSB \n";
    values += String(data[10]) + " : End LSB \n";
    values += String(data[11]) + " : Fade In MSB \n";
    values += String(data[12]) + " : Fade In LSB \n";
    values += String(data[13]) + " : Fade Out MSB \n";
    values += String(data[14]) + " : Fade Out LSB \n";
    values += String(data[15]) + " : End Byte \n";
  } else {
    values += String("Error while parsing Control Change Fade Toggle Data \n");
  }

  return values;
}



String ProtocolToString::disabledControllerToString(const int* data){
  String values;
  int startByte = data[0];
  int optionId = data[1];
  int endByte = data[2];

  if(startByte == 0xF0 && optionId == 0xEF && endByte == 0xFF){
    values += String(data[0]) + " : Start Byte \n";
    values += String(data[1]) + " : Disabled Controller ID \n";
    values += String(data[2]) + " : End Byte \n";

    for(int i=3; i<16; i++){
      delayMicroseconds(10);
      if(data[i] == 0){
        values += String(data[i]) + " : Zero Padding \n";
      } else {
        values += "Error";
      }
    }

  } else {
    values = String("Error while parsing Disabled Controller Data \n");
  }

  return values;
}

boolean ProtocolToString::compareSceneBlock(const int* data){
  boolean result = false; 

  if(
      data[0] == 'S' &&
      data[1] == 'C' &&
      data[2] == 'E' &&
      data[3] == 'N' &&
      data[4] == 'E' &&
      data[5] == 'N' &&
      data[6] == 'R'
    )
  {
    result = true;    
  }
  return result;
}

boolean ProtocolToString::compareStartBlock(const int* data){
  boolean result = false;

  if(
      data[0] == 'S' &&
      data[1] == 'T' && 
      data[2] == 'R' &&
      data[3] == 'B' &&
      data[4] == 'L' &&
      data[5] == 'O' &&
      data[6] == 'C' &&
      data[7] == 'K'
    )
  {
    result = true;  
  }
  
  return result;
}

boolean ProtocolToString::compareEndBlock(const int* data){
  boolean result = false;

  if(
      data[0] == 'E' &&
      data[1] == 'N' &&
      data[2] == 'D' &&
      data[3] == 'B' &&
      data[4] == 'L' &&
      data[5] == 'O' &&
      data[6] == 'C' &&
      data[7] == 'K'
    )
  {
    result = true;  
  }
  return result;
}

boolean ProtocolToString::compareCyclicRedundancyCheckBeginBlock(const int* data){
  boolean result = false;

  if(
      data[0] == 'C' &&
      data[1] == 'R' &&
      data[2] == 'C' &&
      data[3] == 'B' &&
      data[4] == 'G' &&
      data[5] == 'N' &&
      data[6] == 'B' &&
      data[7] == 'L' 
    )
  {
    result = true;
  }
  return result;
}
boolean ProtocolToString::compareCyclicRedundancyCheckEndBlock(const int* data){
  boolean result = false;

  if(
      data[0] == 'C' &&
      data[1] == 'R' &&
      data[2] == 'C' &&
      data[3] == 'E' &&
      data[4] == 'N' && 
      data[5] == 'D' &&
      data[6] == 'B' &&
      data[7] == 'L'
    )
  {
    result = true;   
  }
  return result;
}

