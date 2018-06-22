void irRemoteLoop() {
  uint64_t resultsValue = 0ull;
  if(irRecv.decode(&results)){
    //select action according to remote control button
    resultsValue = results.value;
    //serialPrintUint64(resultsValue);
    //Serial.println();
    irRecv.resume();
  }

  switch(resultsValue){
    case 0x40FF22DDull: // AVT-MUTE
    case 0x97B50AED: //AVT-MUTE 1838B
    case 0x80BFA35C: //Cignal Exit
    case 0x9AD8293F: //Cignal-Exit 1838B
    case 0xC578C8FD: //Sharp LCDTV Blue
    case 0xE2F8: //PCremote NUMLOCK
    case 0x1E: //Hisense FAV
    case 0x81E: //Hisense FAV
      cbBigElecFan();
      break;
    case 0x40FF1AE5: //AVT-ANGLE
    case 0xDE595951: //AVT-ANGLE 1838B
    case 0x80BF41BE: //Cignal-Back
    case 0x71260B15: //Cignal-Back 1838B
    case 0xBF16B916: //Sharp LCDTV Red
    case 0xE2E0: //PCremote DESKTOP
    case 0x3B: //Hisense GOTO
    case 0x83B: //Hisense GOTO
      cbSmallElecFan();
      break;
    case 0x40FF20DF: //AVT-Power
      cbApp3();
      break;
    case 0x40FFE01F: //AVT-SRC
      cbApp4();
      break;
  }
}
