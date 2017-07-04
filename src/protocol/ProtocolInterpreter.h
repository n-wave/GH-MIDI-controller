#ifndef PROTOCOLINTERPRETER_H
#define PROTOCOLINTERPRETER_H

/** ProtocolInterpreter 
 *  
 *@author Mario Van Etten
 *@date     21-01-2017  
 *  
 *Interpretes the data in the 
 *EEPROM memory and initializes 
 *the objects for the specified 
 *Analog and Digital Sensors   
 *accordingly.
 *
 *@todo Create wrapper class for 
 *holding  the Scene "sensor" objects 
 *and supply a pointer to this 
 *object.
 *
 *Also do a startup checkup to make 
 *sure none of the data in the 
 *EEPROM is corrupted use the crc
 *calculation.
 */


class ProtocolInterpreter
{
public:
  ProtocolInterpreter();
  ~ProtocolInterpreter();

  
  

private:

};

#endif//PROTOCOLINTERPRETER
