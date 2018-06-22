// An example demonstrating the multiceiver capability of the NRF24L01+
// in a star network with one PRX hub and up to six PTX nodes
//This sketch is a modification from a video on the ForceTronics YouTube Channel,
//which code was leveraged from http://maniacbug.github.io/RF24/starping_8pde-example.html
//This sketch is free to the public to use and modify at your own risk


#include <SPI.h> //Call SPI library so you can communicate with the nRF24L01+
#include <nRF24L01.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/
#include <RF24.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/
#include "Relay_ggt.h"
#include "RF24_ggt.h"

//****************PIN ASSSIGNMENTS********************
const int BigElecFanPin = 4;
const int SmallElecFanPin = 5;
const int App3Pin = 6;
const int App4Pin = 7;
const int pinCE = 9; //This pin is used to set the nRF24 to standby (0) or active mode (1)
const int pinCSN = 10; //This pin is used to tell the nRF24 whether the SPI communication is a command or message to send out
//----------------/PIN ASSSIGNMENTS--------------------

//****************GLOBAL VARIABLES*********************

#define WHICH_NODE 2     // must be a number from 1 - 6 identifying the PTX node
const uint64_t wAddress[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL};
const uint64_t PTXpipe = wAddress[ WHICH_NODE - 1 ];   // Pulls the address from the above array for this node's pipe
//---------------/GLOBAL VARIABLES---------------------

//****************CLASS CONSTRUCTORS*********************
Relay BigElecFan(BigElecFanPin);
Relay SmallElecFan(SmallElecFanPin);
Relay App3(App3Pin);
Relay App4(App4Pin);

RF24 radio(pinCE, pinCSN); // Create your nRF24 object or wireless SPI connection
//---------------/CLASS CONSTRUCTORS---------------------

void setup() {
  Serial.begin(115200);   //start serial to communicate process
  radio.begin();            //Start the nRF24 module
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(108);          // the higher channels tend to be more "open"
  radio.openReadingPipe(0,PTXpipe);  //open reading or receive pipe
  radio.startListening();
}

void loop() {
  while ( !radio.available() ) { //run while no receive data and not timed out
  }
  byte masterCommand = receiveCommand();
  //Serial.println(masterCommand);
  switch(masterCommand){
    case RELAY1_FLIP:
      BigElecFan.flip(2000);
      break;
    case RELAY2_FLIP:
      SmallElecFan.flip(2000);
      break;
    case RELAY3_FLIP:
      App3.flip(2000);
      break;
    case RELAY4_FLIP:
      App4.flip(2000);
      break;
    case RELAY1_HIGH:
      BigElecFan.relayHigh();
      break;
    case RELAY2_HIGH:
      SmallElecFan.relayHigh();
      break;
    case RELAY3_HIGH:
      App3.relayHigh();
      break;
    case RELAY4_HIGH:
      App4.relayHigh();
      break;
    case RELAY1_LOW:
      BigElecFan.relayLow();
      break;
    case RELAY2_LOW:
      SmallElecFan.relayLow();
      break;
    case RELAY3_LOW:
      App3.relayLow();
      break;
    case RELAY4_LOW:
      App4.relayLow();
      break;
  }
    
  
  //delay(200);
}

byte receiveCommand() {
  byte _masterCommand; //variable to store received value
  radio.read( &_masterCommand,1); //read value
  return _masterCommand;
}
