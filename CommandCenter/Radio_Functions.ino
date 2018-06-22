void radioSetup() {
  radio.begin();  //Start the nRF24 module

  radio.setPALevel(RF24_PA_LOW);  // "short range setting" - increase if you want more range AND have a good power supply
  radio.setChannel(108);          // the higher channels tend to be more "open"

  // Open up to six pipes for PRX to receive data
  radio.openReadingPipe(0,rAddress[0]);
  radio.openReadingPipe(1,rAddress[1]);
  radio.openReadingPipe(2,rAddress[2]);
  radio.openReadingPipe(3,rAddress[3]);
  radio.openReadingPipe(4,rAddress[4]);
  radio.openReadingPipe(5,rAddress[5]);

  irRecv.enableIRIn();
  
  radio.startListening();  
}

bool sendCommand(byte xMitter, byte command) {
    bool worked; //variable to track if write was successful
    radio.stopListening(); //Stop listening, start receiving data.
    radio.openWritingPipe(rAddress[xMitter]);
    if(!radio.write(&command, 1))  worked = false;
    else worked = true; //it was received
    radio.startListening(); //Switch back to a receiver
    return worked;  //return whether write was successful
}

bool sendString(byte xMitter, char* command ) {
    bool worked; //variable to track if write was successful
    radio.stopListening(); //Stop listening, start receiving data.
    radio.openWritingPipe(rAddress[xMitter]);
    if(!radio.write(&command, sizeof(command)))  worked = false;
    else worked = true; //it was received
    radio.startListening(); //Switch back to a receiver
    return worked;  //return whether write was successful
}

byte receiveCommand() {
  byte _masterCommand; //variable to store received value
  radio.read( &_masterCommand,1); //read value
  return _masterCommand;
}

void cbBigElecFan() {
  sendCommand(pipeNumJadeRelay, RELAY1_FLIP);
}

void cbSmallElecFan() {
  sendCommand(pipeNumJadeRelay, RELAY2_FLIP);
}

void cbApp3() {
  sendCommand(pipeNumJadeRelay, RELAY3_FLIP);
}

void cbApp4() {
  sendCommand(pipeNumJadeRelay, RELAY4_FLIP);
}
