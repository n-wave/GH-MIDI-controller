/*
 * StateMachine.cpp
 *
 *  Created on: Oct 27, 2017
 *      Author: mario
 */

#include "StateMachine.h"
#include "../testing/configuration.h"


/*
 *
 *     long baudRate;
    SerialCommunication serial;
    ProtocolToString printer;

    unsigned long startTime;
    unsigned long printTime; //Printing analog or switchvalues
    unsigned long ledTime;   //Led indicator speed
    boolean ledToggle;
    int state;
 *
 *
 *
 */
StateMachine::StateMachine() :
	baudRate(115200),
	serial(SerialCommunication(baudRate)),
	printer(ProtocolToString()),
	currentTime(0),
	printStartTime(0),
	ledStartTime(0),
    updated(false),
	ledToggle(true),
	programMode(false),
	debugMode(false),
	printAnalogValues(false),
	printSwitchValues(false),

	ledPin(20),
	state(1),
	serialResult(0)
{
}

StateMachine::StateMachine(long baudrate) :
	baudRate(baudrate),
	serial(SerialCommunication(baudRate)),
	printer(ProtocolToString()),
	currentTime(0),
	printStartTime(0),
	ledStartTime(0),
	updated(false),
	ledToggle(true),
	programMode(false),
	debugMode(false),
	printAnalogValues(false),
	printSwitchValues(false),
	ledPin(20),
	state(1),
	serialResult(0)
{
}

StateMachine::~StateMachine() {
	Serial.end();
}

boolean StateMachine::update(){
	currentTime = millis();
	int tmpResult = serial.readSerial();

	if(serialResult != tmpResult){
		updated = true;
		serialResult = tmpResult;
	} else {
		updated = false;
	}

	digitalWrite(20, ledToggle);

	switch(serialResult){
		case 1:
		  state = 2; //Entered programming mode close samplingClock in main
		  programMode = true;
		  debugMode = false;
		  break;
		case 2:
		  state = 1; //Entered Normal device mode reset cycles, the LTC1867 and reset the sampling clock
		  ledToggle = true;
		  programMode = false;
		  debugMode = false;
		  break;
		case 3:
		  state = 3;
		  debugMode = true;
		  Serial.println("/-----------------------------------------/");
		  Serial.println("/-----------Entering Debug Mode-----------/");
		  this->printDebugCommands();
		  break;
	}

	/* Flash led while in programming mode */
	if(programMode){
		if((currentTime - ledStartTime) > 150){
			ledStartTime = currentTime;
			ledToggle = !ledToggle;
		}
	}

	if(debugMode){
			//Disable when a DEBUG message has been received
			if(serialResult > 3){
				printAnalogValues = false;
				printSwitchValues = false;
			}

			switch(serialResult){
				case 4:
			      printDebugCommands();
				  break;
				case 5:
				  printer.printMemoryCheck();
				  break;
				case 6:
				  printer.printEEPROM();
			  	  break;
				case 7:
				  printer.printContentsToString();
			  	  break;
				case 8:
				  printer.printController(serial.getRequestedScene(), serial.getRequestedController());
			  	  break;
				case 9:
				  printAnalogValues = true;
				  Serial.println("Analog sensors true");
				  break;
				case 10:
				  printSwitchValues = true;
				  Serial.println("Switches true");
				  break;
				case 11:
				  Serial.println("          Testing LED indicators          ");
			      Serial.println("/-----------------------------------------/");
				  testLedIndicators();
				  Serial.println("            Led test Finished             ");
			      Serial.println("/-----------------------------------------/");
				  break;
				case 255:
				  Serial.print("\n");
				  Serial.println("Exiting Debug Mode");
				  debugMode = false;
				  ledToggle = true;
				  break;
			}

			if((currentTime - printStartTime) > 50){
				printStartTime = currentTime;

			  if(printAnalogValues){
				  this->printAnalogSensors();
			  }

			  if(printSwitchValues){
				  this->printSwitches();
			  }
			}

			/* Led flashing for Debug Modus */
			if((currentTime - ledStartTime) > 750){
				ledStartTime = currentTime;
			  ledToggle = !ledToggle;
			}
		}
	return updated;
}

int StateMachine::getState(){
	return state;
}
/*
 * Call in the setup
 * If not the device
 * will not properly
 * start
 */
void StateMachine::init()
{
	currentTime = millis();
	ledStartTime = currentTime;
	printStartTime = currentTime;

    Serial.begin(baudRate);

	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, ledToggle);

}

void StateMachine::printDebugCommands()
{
	Serial.println("/-----------------------------------------/");
	Serial.println("/-----------------commands----------------/");
	Serial.println("/-----------------------------------------/");
	Serial.println("0. : DBGENA : Enable debugging");
	Serial.println("1. : DBGCOM : Print commands");
	Serial.println("2. : MEMCHK : Memory Check (perform crc)");
	Serial.println("3. : PRINTE : print EEPROM in HEX format");
	Serial.println("4. : PRINTC : Print controller settings");
	Serial.println("5. : SCxCxx : Print specific controller");
	Serial.println("              from a specific scene");
	Serial.println(" >>: SC(1-4): Scene number 1 to 4");
	Serial.println(" >>: Cxx    : Controller 1 to 28");
	Serial.println(" >>: C00    : Print Scene Data");
	Serial.println(" <<: SC1C11 : Prints controller 11");
	Serial.println("		      from Scene 1");
	Serial.println("6. : ANAENA : Enable analog sensors");
	Serial.println("7. : SWSENA : Enable Switches");
	Serial.println("8. : LEDTST : Test led indicatorss");
	Serial.println("9. : DBGDIS : Exit debugging");
	Serial.println("/-----------------------------------------/");
}

/* Prints averaged and mapped values
 * Sensors are mappen to 14Bit values
 */
void StateMachine::printAnalogSensors()
{
	for(int i=0; i<20; i++){
		    Serial.print("\n");
		  }

		  Serial.println("/---------------------------/");
		  Serial.println(" Averaged and Mapped values ");
		  Serial.println("/---------------------------/");
		  		/* ADC 1 */
		  	  	//Head potentiometer 1
		  		Serial.print("H1 :");
		  		Serial.print(averagedValues[0]);
		  		Serial.print(" : ");
		  		Serial.println(mappedValues[0]);
		  		//Head potentiometer 2
		  		Serial.print("H2:");
		  		Serial.print(averagedValues[1]);
		  		Serial.print(" : ");
		  		Serial.println(mappedValues[1]);
		  		//Head potentiometer 3
		  		Serial.print("H3:");
		  		Serial.print(averagedValues[2]);
		  		Serial.print(" : ");
		  		Serial.println(mappedValues[2]);
		  		//Head potentiometer 4
		  		Serial.print("H4:");
		  		Serial.print(averagedValues[3]);
		  		Serial.print(" : ");
		  		Serial.println(mappedValues[3]);
		  		//Head potentiometer 5
		  		Serial.print("H5:");
		  		Serial.print(averagedValues[4]);
		  		Serial.print(" : ");
		  		Serial.println(mappedValues[4]);
		  		//Head potentiometer 6
		  		Serial.print("H6:");
		  		Serial.print(averagedValues[5]);
		  		Serial.print(" : ");
		  		Serial.println(mappedValues[5]);
		  		 //Ribbon 1
		  		Serial.print("R1:");
		  		Serial.print(averagedValues[6]);
		  		Serial.print(" : ");
		  		Serial.println(mappedValues[6]);
		  		//Ribbon 2
		  		Serial.print("R2:");
		  		Serial.print(averagedValues[7]);
		  		Serial.print(" : ");
		  		Serial.println(mappedValues[7]);

		  		/* ADC 2 */
		  		//Pressure 1
		  		Serial.print("P1:");
		  		Serial.print(averagedValues[8]);
		  		Serial.print(" : ");
		  		Serial.println(mappedValues[8]);
		  		//Pressure 2
		  		Serial.print("P2:");
		  		Serial.print(averagedValues[9]);
		  		Serial.print(" : ");
		  		Serial.println(mappedValues[9]);
		  		//Pressure 3
		  		Serial.print("P3:");
		  		Serial.print(averagedValues[10]);
		  		Serial.print(" : ");
		  		Serial.println(mappedValues[10]);
		  		//Body Pot 1
		  		Serial.print("B1:");
		  		Serial.print(averagedValues[11]);
		  		Serial.print(" : ");
		  		Serial.println(mappedValues[11]);
		  		//Body Pot 2
		  		Serial.print("B2:");
		  		Serial.print(averagedValues[12]);
		  		Serial.print(" : ");
		  		Serial.println(mappedValues[12]);
		  		//Body Pot 3
		  		Serial.print("B3:");
		  		Serial.print(averagedValues[13]);
		  		Serial.print(" : ");
		  		Serial.println(mappedValues[13]);
		  		//X axis
		  		Serial.print("Xa:");
		  		Serial.print(averagedValues[14]);
		  		Serial.print(" : ");
		  		Serial.println(mappedValues[14]);
		  		//Y axis
		  		Serial.print("Ya:");
		  		Serial.print(averagedValues[15]);
		  		Serial.print(" : ");
		  		Serial.println(mappedValues[15]);

		  		Serial.println("/---------------------------/");
}

void StateMachine::printSwitches(){
	for(int i=0; i<18; i++){
    Serial.print("\n");
  }

  /* Switches */

    Serial.println("/---------------------------/");
	Serial.println(" 	     Switches            ");
    Serial.println("/---------------------------/");

	Serial.print("N1:");                     //Neck Switch 1
	Serial.println(switches[0]);
	Serial.print("N2:");                     //Neck Switch 2
	Serial.println(switches[1]);
	Serial.print("N3:");                     //Neck Switch 3
	Serial.println(switches[2]);
	Serial.print("N1:");                     //Neck Switch 4
	Serial.println(switches[3]);
	Serial.print("N2:");                     //Neck Switch 5
	Serial.println(switches[4]);
	Serial.print("N3:");                     //Neck Switch 6
	Serial.println(switches[5]);
	Serial.print("Up:");                      //Up Switch
	Serial.println(switches[6]);
	Serial.print("Do:");                      //Down Switch
	Serial.println(switches[7]);

	Serial.print("ST:");                     //Neck Switch 1
	Serial.println(switches[8]);
	Serial.print("SE:");                     //Neck Switch 2
	Serial.println(switches[9]);
	Serial.print("S1:");                     //Neck Switch 3
	Serial.println(switches[10]);
	Serial.print("S2:");                     //Neck Switch 4
	Serial.println(switches[11]);
	Serial.print("S3:");                     //Neck Switch 5
	Serial.println(switches[12]);
	Serial.print("S4:");                     //Neck Switch 6
	Serial.println(switches[13]);
	Serial.print("PS:");                      //Up Switch
	Serial.println(switches[14]);
	Serial.print("jS:");                      //Down Switch
	Serial.println(switches[15]);
}

void StateMachine::testLedIndicators(){
	  digitalWrite(3, LOW);
	  digitalWrite(4, LOW);
	  digitalWrite(5, LOW);
	  digitalWrite(6, LOW);

	  digitalWrite(22, LOW);
	  digitalWrite(21, LOW);
	  digitalWrite(20, LOW);

	  delay(500);

	  for(int i=22; i>20; i--){
		  digitalWrite(i, HIGH);
		  delay(500);
		  digitalWrite(i, LOW);
	  }

	  for(int i=6; i>=3; i--){
		  digitalWrite(i, HIGH);
		  delay(500);
		  digitalWrite(i, LOW);
	  }



	  digitalWrite(20, HIGH);
}

