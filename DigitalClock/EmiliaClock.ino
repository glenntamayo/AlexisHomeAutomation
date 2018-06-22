#include <nRF24L01.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/
#include <RF24.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/
#include "RF24_ggt.h"
#include "SevenSegment_ggt.h"
#include "Timer.h"  

//****************PIN ASSSIGNMENTS********************
const byte DATA = 7;
const byte LATCH = 8;
const byte CLOCK = 9;
const byte digit0 = 3;
const byte digit1 = 4;
const byte digit2 = 6;
const byte digit3 = 5;
const byte pinColon = 2;

const byte pinCE = 14; //This pin is used to set the nRF24 to standby (0) or active mode (1)
const byte pinCSN = 15; //This pin is used to tell the nRF24 whether the SPI communication is a command or message to send out

//----------------/PIN ASSSIGNMENTS--------------------

//****************GLOBAL VARIABLES*********************
unsigned long previousMillisRadio = 0;

const unsigned long settingBlinkRate = 300;
const byte PovBlinkRate = 10;

struct timeDataStruct{
  byte hour;
  byte minute;
  byte second;
}timeData;

#define WHICH_NODE 4     // must be a number from 1 - 6 identifying the PTX node
const uint64_t wAddress[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL};
const uint64_t PTXpipe = wAddress[ WHICH_NODE - 1 ];   // Pulls the address from the above array for this node's pipe
//---------------/GLOBAL VARIABLES---------------------

//****************CLASS CONSTRUCTORS*********************
SevenSegment DigitalClock(DATA, LATCH, CLOCK, digit0, digit1, digit2, digit3);
Timer t;

RF24 radio(pinCE, pinCSN); // Create your nRF24 object or wireless SPI connection
//---------------/CLASS CONSTRUCTORS---------------------


void setup(){
  Serial.begin(115200);                 // Start the serial terminal

  radio.begin();            //Start the nRF24 module
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(108);          // the higher channels tend to be more "open"
  radio.openReadingPipe(0,PTXpipe);  //open reading or receive pipe
  radio.stopListening();

  DigitalClock.setup();
  pinMode(pinColon, OUTPUT);
  
  digitalWrite(pinColon, HIGH);

  //adjust RTC using computer time
  //DigitalClock.RtcAdjust(__DATE__, __TIME__);
  
  //t.every(3600000, cbRtcUpdate);
  t.oscillate(pinColon, 500, HIGH);
  t.every(60000, cbTimeIncrement);
  t.every(5000, cbCheckMasterUpdateTime);

  cbTimeIncrement();
  radio.startListening();
}

/****************** MAIN CODE ******************/

void loop(){
  t.update();
  
  DigitalClock.displayPOV(2);

}

void cbCheckMasterUpdateTime() {
  if(radio.available() ) {
    while (radio.available()) {
      radio.read(&timeData, sizeof(timeData));
    }
    DateTime now = DigitalClock.getRtcTime();
    /*
      Serial.print(F("RTC Time hour: "));
      Serial.println(now.hour());
      Serial.print(F("RTC Time minute: "));
      Serial.println(now.minute());
      Serial.print(F("Web Time hour: "));
      Serial.println(timeData.hour);
      Serial.print(F("Web Time minute: "));
      Serial.println(timeData.minute);
    */
    if(timeData.hour == now.hour() && timeData.minute == now.minute()) {
      //Serial.println(F("the web time and rtc time match"));
    } else {
      //Serial.println(F("the web time and rtc time DO NOT match, need to adjust"));
      //byte timeDataHour12;
      /*
      if (timeData.hour > 12) {
          timeDataHour12 = timeDataHour12 - 12;
      }
      */
      DateTime webTimetoRtc = DateTime(0, 0, 0, timeData.hour, timeData.minute, timeData.second); 
      DigitalClock.RTC.adjust(webTimetoRtc);
      DigitalClock.syncRtcToDisplay();
    }
    
  } else {
    //Serial.println(F("no command from master"));  
  }
}

byte receiveCommand() {
  byte _masterCommand; //variable to store received value
  radio.read( &_masterCommand,1); //read value
  return _masterCommand;
}

void cbTimeIncrement() {
  DigitalClock.timeIncrement();
  DigitalClock.syncRtcToDisplay();
}
