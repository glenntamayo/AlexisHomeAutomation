//Glenn Gil Tamayo
//April 23, 2018

#include <ESP8266WiFiMulti.h>
#include <ArduinoOTA.h>
#include <BlynkSimpleEsp8266.h>
#include <BlynkButton_ggt.h>
//#include <BlynkMenu_ggt.h>
#include <SPI.h> //Call SPI library so you can communicate with the nRF24L01+
#include <nRF24L01.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/
#include <RF24.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/
#include "RF24_ggt.h"
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <time.h>
#include <TimeLib.h> 

#define BLYNK_YELLOW  "#ED9D00"
#define BLYNK_GREEN   "#23C48E"
#define BLYNK_BLUE    "#04C0F8"
#define BLYNK_DARD_BLUE    "#5F7CD8"
#define BLYNK_RED    "#D3435C"

//****************PIN ASSSIGNMENTS********************
const int pinCE = D1; //This pin is used to set the nRF24 to standby (0) or active mode (1)
const int pinCSN = D2; //This pin is used to tell the nRF24 whether the SPI communication is a command or message to send out
const int receiverPin = D3;

//----------------/PIN ASSSIGNMENTS--------------------

//****************GLOBAL VARIABLES*********************
char auth[] = "fe394d2a030d47e384ab0aaf05c66671";

IPAddress gateway(192,168,1,1);           // gateway of your network
IPAddress subnet(255,255,255,0);          // subnet mask of your network
WiFiServer server(80);
ESP8266WiFiMulti wifiMulti;

struct structRelay{
  int timeOn = -1;
  int timeOff = -1;
};
structRelay Appl1Sched;
structRelay Appl2Sched;

struct timeDataStruct{
  byte hour;
  byte minute;
  byte second;
}timeData;

struct structBlynkMenuTime{
  const char item[97][9];
  const int intTime[97];
};
structBlynkMenuTime blynkMenuTime = {
  {"Not Set", 
    "12:00 AM", "12:15 AM", "12:30 AM", "12:45 AM",
    "1:00 AM",  "1:15 AM",  "1:30 AM",  "1:45 AM",
    "2:00 AM",  "2:15 AM",  "2:30 AM",  "2:45 AM",
    "3:00 AM",  "3:15 AM",  "3:30 AM",  "3:45 AM",
    "4:00 AM",  "4:15 AM",  "4:30 AM",  "4:45 AM",
    "5:00 AM",  "5:15 AM",  "5:30 AM",  "5:45 AM",
    "6:00 AM",  "6:15 AM",  "6:30 AM",  "6:45 AM",
    "7:00 AM",  "7:15 AM",  "7:30 AM",  "7:45 AM",
    "8:00 AM",  "8:15 AM",  "8:30 AM",  "8:45 AM",
    "9:00 AM",  "9:15 AM",  "9:30 AM",  "9:45 AM",
    "10:00 AM", "10:15 AM", "10:30 AM", "10:45 AM",
    "11:00 AM", "11:15 AM", "11:30 AM", "11:45 AM",
    "12:00 PM", "12:15 PM", "12:30 PM", "12:45 PM",
    "1:00 PM",  "1:15 PM",  "1:30 PM",  "1:45 PM",
    "2:00 PM",  "2:15 PM",  "2:30 PM",  "2:45 PM",
    "3:00 PM",  "3:15 PM",  "3:30 PM",  "3:45 PM",
    "4:00 PM",  "4:15 PM",  "4:30 PM",  "4:45 PM",
    "5:00 PM",  "5:15 PM",  "5:30 PM",  "5:45 PM",
    "6:00 PM",  "6:15 PM",  "6:30 PM",  "6:45 PM",
    "7:00 PM",  "7:15 PM",  "7:30 PM",  "7:45 PM",
    "8:00 PM",  "8:15 PM",  "8:30 PM",  "8:45 PM",
    "9:00 PM",  "9:15 PM",  "9:30 PM",  "9:45 PM",
    "10:00 PM", "10:15 PM", "10:30 PM", "10:45 PM",
    "11:00 PM", "11:15 PM", "11:30 PM", "11:45 PM"
  },
  {-1,
   0, 15, 30, 45,
   60, 75, 90, 105,
   120, 135, 150, 165,
   180, 195, 210, 225,
   240, 255, 270, 285,
   300, 315, 330, 345,
   360, 375, 390, 405,
   420, 435, 450, 465,
   480, 495, 510, 525,
   540, 555, 570, 585,
   600, 615, 630, 645,
   660, 675, 690, 795,
   720, 735, 750, 765,
   780, 795, 810, 825,
   840, 855, 870, 885,
   900, 915, 930, 945,
   960, 975, 990, 1005,
   1020, 1035, 1050, 1065,
   1080, 1095, 1110, 1125,
   1140, 1155, 1170, 1185,
   1200, 1215, 1230, 1245,
   1260, 1275, 1290, 1305,
   1320, 1335, 1350, 1365,
   1380, 1395, 1410, 1425
  }
};

byte hourNow = 0;
byte minuteNow = 0;

//---------------/GLOBAL VARIABLES---------------------

//****************CLASS CONSTRUCTORS*********************
RF24 radio(pinCE, pinCSN); // Declare object from nRF24 library (Create your wireless SPI)

IRrecv irRecv(receiverPin);
decode_results results;

BlynkButton blynkBigElecFan;
BlynkButton blynkSmallElecFan;
BlynkButton blynkApp3;
BlynkButton blynkApp4;

WidgetTerminal terminal(V1);

unsigned long ulMinutesSinceMidnight;

Timer t;
//---------------/CLASS CONSTRUCTORS---------------------


void setup() {
  Serial.begin(115200);  //start serial to communication
  
  wifiMulti.addAP("TAMAYO2.4", "lekleklek");
  wifiMulti.addAP("ggdt_iphone", "Winterfell1");
  Blynk.config(auth);
  ArduinoOTA.begin();
  
  blynkBigElecFan.setup(cbBigElecFan, 1000);
  blynkSmallElecFan.setup(cbSmallElecFan, 1000);
  blynkApp3.setup(cbApp3, 1000);
  blynkApp4.setup(cbApp4, 1000);

  configTime(8 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  t.every(43200000, cbUpdateTime);
  t.every(20000, cbMasterSchedule);
  t.every(60000, cbEveryMinute);
  //t.every(21600000, cbSendTimeToEmilia); TRUE
  t.every(10000, cbSendTimeToEmilia); //DEBUG
  
  radioSetup();
  
}

void loop()  {
  irRemoteLoop();
  BlynkLoop();
  t.update();

  ///PUT THIS iS RADIO LOOP
  if(radio.available() ) {
    byte masterCommand = receiveCommand();
    if (masterCommand == AC_STATUS_OFF) {
      sendCommand(pipeNumJadeRelay, RELAY2_LOW);
    }
  }

  
}

void cbSendTimeToEmilia() {
  radio.stopListening();
  radio.openWritingPipe(rAddress[pipeNumDigiClock]);
  cbUpdateTime();
  timeData.hour = hourNow;
  timeData.minute = minuteNow;
  if (!radio.write( &timeData, sizeof(timeData) )){
     Serial.println(F("failed"));
  }
  radio.startListening();
  /*
  sendCommand(pipeNumDigiClock, START_TRANSMISSION);
  sendCommand(pipeNumDigiClock, hourNow);
  sendCommand(pipeNumDigiClock, NEXT_BYTE_TRANSMISSION);
  sendCommand(pipeNumDigiClock, minuteNow);
  sendCommand(pipeNumDigiClock, END_TRANSMISSION);
  */
}

void cbEveryMinute() {
  if (ulMinutesSinceMidnight == 0) {
    cbUpdateTime();
  } else {
    ulMinutesSinceMidnight += 1;
  }
  //restart to zero if next midnight is reached
  if (ulMinutesSinceMidnight > 1440) {
    ulMinutesSinceMidnight = 0;
  }
}

void cbUpdateTime() {
  time_t now = time(nullptr);
  hourNow = hour(now);
  minuteNow = minute(now);
  ulMinutesSinceMidnight = hourNow * 60 + minuteNow;
}
