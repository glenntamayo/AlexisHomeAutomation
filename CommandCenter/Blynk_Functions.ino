BLYNK_WRITE_DEFAULT() {
  switch(request.pin) {
   case 10:
    Appl2Sched.timeOn = blynkMenuTime.intTime[param.asInt() - 1];
    break;
   case 11:
    Appl2Sched.timeOff = blynkMenuTime.intTime[param.asInt() - 1];
    break;
   case 14:
    Appl1Sched.timeOn = blynkMenuTime.intTime[param.asInt() - 1]; 
    break;
   case 15:
    Appl1Sched.timeOff = blynkMenuTime.intTime[param.asInt() - 1]; 
    break;
   case 31:
    blynkBigElecFan.collect(param.asInt());
    break;
   case 32:
    blynkSmallElecFan.collect(param.asInt());
    break;
   case 33:
    blynkApp3.collect(param.asInt());
    break;
   case 34:
    blynkApp4.collect(param.asInt());
    break;
   case 41:
    
    break;
  }
}

BLYNK_WRITE(V1) {
  String incoming = param.asStr();
  if (String("getMsm") == incoming) {
    terminal.println(ulMinutesSinceMidnight);
  } else if (String("schedTimeOn2") == incoming) {
    terminal.println(Appl1Sched.timeOn);
  } else if (String("schedTimeOnActive2") == incoming) {
    //terminal.println(blynkSmallElecFan.schedTimeOnActive);
  } else if (String("state2") == incoming) {
    terminal.println(blynkSmallElecFan.state);
  } else if (String("timeStatus") == incoming) {
    terminal.println(timeStatus());
  } else if (String("statusAll") == incoming) {
    String response = "\n'";
    response.concat("Msm:\t");
    response.concat(ulMinutesSinceMidnight);
    
    response.concat('\n');
    response.concat("Appl1 Time On:\t");
    response.concat(Appl1Sched.timeOn);
    
    response.concat('\n');
    response.concat("Appl1 Time Off:\t");
    response.concat(Appl1Sched.timeOff);
    
    response.concat('\n');
    response.concat("Appl2 Time On:\t");
    response.concat(Appl2Sched.timeOn);
    
    response.concat('\n');
    response.concat("Appl2 Time Off:\t");
    response.concat(Appl2Sched.timeOff);
    
    terminal.println(response);
  }
  terminal.flush();
}

BLYNK_CONNECTED() {
  updateMenu();
}


void updateMenu() {
  Blynk.setProperty(V10, "labels", blynkMenuTime.item[0], blynkMenuTime.item[1], blynkMenuTime.item[2], blynkMenuTime.item[3],
                                   blynkMenuTime.item[4], blynkMenuTime.item[5], blynkMenuTime.item[6], blynkMenuTime.item[7],
                                   blynkMenuTime.item[8], blynkMenuTime.item[9], blynkMenuTime.item[10], blynkMenuTime.item[11],
                                   blynkMenuTime.item[12], blynkMenuTime.item[13], blynkMenuTime.item[14], blynkMenuTime.item[15],
                                   blynkMenuTime.item[16], blynkMenuTime.item[17], blynkMenuTime.item[18], blynkMenuTime.item[19],
                                   blynkMenuTime.item[20], blynkMenuTime.item[21], blynkMenuTime.item[22], blynkMenuTime.item[23], 
                                   blynkMenuTime.item[24], blynkMenuTime.item[25], blynkMenuTime.item[26], blynkMenuTime.item[27],
                                   blynkMenuTime.item[28], blynkMenuTime.item[29], blynkMenuTime.item[30], blynkMenuTime.item[31],
                                   blynkMenuTime.item[32], blynkMenuTime.item[33], blynkMenuTime.item[34], blynkMenuTime.item[35],
                                   blynkMenuTime.item[36], blynkMenuTime.item[37], blynkMenuTime.item[38], blynkMenuTime.item[39],
                                   blynkMenuTime.item[40], blynkMenuTime.item[41], blynkMenuTime.item[42], blynkMenuTime.item[43],
                                   blynkMenuTime.item[44], blynkMenuTime.item[45], blynkMenuTime.item[46], blynkMenuTime.item[47],
                                   blynkMenuTime.item[48], blynkMenuTime.item[49], blynkMenuTime.item[50], blynkMenuTime.item[51],
                                   blynkMenuTime.item[52], blynkMenuTime.item[53], blynkMenuTime.item[54], blynkMenuTime.item[55],
                                   blynkMenuTime.item[56], blynkMenuTime.item[57], blynkMenuTime.item[58], blynkMenuTime.item[59],
                                   blynkMenuTime.item[60], blynkMenuTime.item[61], blynkMenuTime.item[62], blynkMenuTime.item[63],
                                   blynkMenuTime.item[64], blynkMenuTime.item[65], blynkMenuTime.item[66], blynkMenuTime.item[67],
                                   blynkMenuTime.item[68], blynkMenuTime.item[69], blynkMenuTime.item[70], blynkMenuTime.item[71],
                                   blynkMenuTime.item[72], blynkMenuTime.item[73], blynkMenuTime.item[74], blynkMenuTime.item[75],
                                   blynkMenuTime.item[76], blynkMenuTime.item[77], blynkMenuTime.item[78], blynkMenuTime.item[79],
                                   blynkMenuTime.item[80], blynkMenuTime.item[81], blynkMenuTime.item[82], blynkMenuTime.item[83],
                                   blynkMenuTime.item[84], blynkMenuTime.item[85], blynkMenuTime.item[86], blynkMenuTime.item[87],
                                   blynkMenuTime.item[88], blynkMenuTime.item[89], blynkMenuTime.item[90], blynkMenuTime.item[91],
                                   blynkMenuTime.item[92], blynkMenuTime.item[93], blynkMenuTime.item[94], blynkMenuTime.item[95]);
  Blynk.setProperty(V11, "labels", blynkMenuTime.item[0], blynkMenuTime.item[1], blynkMenuTime.item[2], blynkMenuTime.item[3],
                                   blynkMenuTime.item[4], blynkMenuTime.item[5], blynkMenuTime.item[6], blynkMenuTime.item[7],
                                   blynkMenuTime.item[8], blynkMenuTime.item[9], blynkMenuTime.item[10], blynkMenuTime.item[11],
                                   blynkMenuTime.item[12], blynkMenuTime.item[13], blynkMenuTime.item[14], blynkMenuTime.item[15],
                                   blynkMenuTime.item[16], blynkMenuTime.item[17], blynkMenuTime.item[18], blynkMenuTime.item[19],
                                   blynkMenuTime.item[20], blynkMenuTime.item[21], blynkMenuTime.item[22], blynkMenuTime.item[23], 
                                   blynkMenuTime.item[24], blynkMenuTime.item[25], blynkMenuTime.item[26], blynkMenuTime.item[27],
                                   blynkMenuTime.item[28], blynkMenuTime.item[29], blynkMenuTime.item[30], blynkMenuTime.item[31],
                                   blynkMenuTime.item[32], blynkMenuTime.item[33], blynkMenuTime.item[34], blynkMenuTime.item[35],
                                   blynkMenuTime.item[36], blynkMenuTime.item[37], blynkMenuTime.item[38], blynkMenuTime.item[39],
                                   blynkMenuTime.item[40], blynkMenuTime.item[41], blynkMenuTime.item[42], blynkMenuTime.item[43],
                                   blynkMenuTime.item[44], blynkMenuTime.item[45], blynkMenuTime.item[46], blynkMenuTime.item[47],
                                   blynkMenuTime.item[48], blynkMenuTime.item[49], blynkMenuTime.item[50], blynkMenuTime.item[51],
                                   blynkMenuTime.item[52], blynkMenuTime.item[53], blynkMenuTime.item[54], blynkMenuTime.item[55],
                                   blynkMenuTime.item[56], blynkMenuTime.item[57], blynkMenuTime.item[58], blynkMenuTime.item[59],
                                   blynkMenuTime.item[60], blynkMenuTime.item[61], blynkMenuTime.item[62], blynkMenuTime.item[63],
                                   blynkMenuTime.item[64], blynkMenuTime.item[65], blynkMenuTime.item[66], blynkMenuTime.item[67],
                                   blynkMenuTime.item[68], blynkMenuTime.item[69], blynkMenuTime.item[70], blynkMenuTime.item[71],
                                   blynkMenuTime.item[72], blynkMenuTime.item[73], blynkMenuTime.item[74], blynkMenuTime.item[75],
                                   blynkMenuTime.item[76], blynkMenuTime.item[77], blynkMenuTime.item[78], blynkMenuTime.item[79],
                                   blynkMenuTime.item[80], blynkMenuTime.item[81], blynkMenuTime.item[82], blynkMenuTime.item[83],
                                   blynkMenuTime.item[84], blynkMenuTime.item[85], blynkMenuTime.item[86], blynkMenuTime.item[87],
                                   blynkMenuTime.item[88], blynkMenuTime.item[89], blynkMenuTime.item[90], blynkMenuTime.item[91],
                                   blynkMenuTime.item[92], blynkMenuTime.item[93], blynkMenuTime.item[94], blynkMenuTime.item[95]);
  Blynk.setProperty(V14, "labels", blynkMenuTime.item[0], blynkMenuTime.item[1], blynkMenuTime.item[2], blynkMenuTime.item[3],
                                   blynkMenuTime.item[4], blynkMenuTime.item[5], blynkMenuTime.item[6], blynkMenuTime.item[7],
                                   blynkMenuTime.item[8], blynkMenuTime.item[9], blynkMenuTime.item[10], blynkMenuTime.item[11],
                                   blynkMenuTime.item[12], blynkMenuTime.item[13], blynkMenuTime.item[14], blynkMenuTime.item[15],
                                   blynkMenuTime.item[16], blynkMenuTime.item[17], blynkMenuTime.item[18], blynkMenuTime.item[19],
                                   blynkMenuTime.item[20], blynkMenuTime.item[21], blynkMenuTime.item[22], blynkMenuTime.item[23], 
                                   blynkMenuTime.item[24], blynkMenuTime.item[25], blynkMenuTime.item[26], blynkMenuTime.item[27],
                                   blynkMenuTime.item[28], blynkMenuTime.item[29], blynkMenuTime.item[30], blynkMenuTime.item[31],
                                   blynkMenuTime.item[32], blynkMenuTime.item[33], blynkMenuTime.item[34], blynkMenuTime.item[35],
                                   blynkMenuTime.item[36], blynkMenuTime.item[37], blynkMenuTime.item[38], blynkMenuTime.item[39],
                                   blynkMenuTime.item[40], blynkMenuTime.item[41], blynkMenuTime.item[42], blynkMenuTime.item[43],
                                   blynkMenuTime.item[44], blynkMenuTime.item[45], blynkMenuTime.item[46], blynkMenuTime.item[47],
                                   blynkMenuTime.item[48], blynkMenuTime.item[49], blynkMenuTime.item[50], blynkMenuTime.item[51],
                                   blynkMenuTime.item[52], blynkMenuTime.item[53], blynkMenuTime.item[54], blynkMenuTime.item[55],
                                   blynkMenuTime.item[56], blynkMenuTime.item[57], blynkMenuTime.item[58], blynkMenuTime.item[59],
                                   blynkMenuTime.item[60], blynkMenuTime.item[61], blynkMenuTime.item[62], blynkMenuTime.item[63],
                                   blynkMenuTime.item[64], blynkMenuTime.item[65], blynkMenuTime.item[66], blynkMenuTime.item[67],
                                   blynkMenuTime.item[68], blynkMenuTime.item[69], blynkMenuTime.item[70], blynkMenuTime.item[71],
                                   blynkMenuTime.item[72], blynkMenuTime.item[73], blynkMenuTime.item[74], blynkMenuTime.item[75],
                                   blynkMenuTime.item[76], blynkMenuTime.item[77], blynkMenuTime.item[78], blynkMenuTime.item[79],
                                   blynkMenuTime.item[80], blynkMenuTime.item[81], blynkMenuTime.item[82], blynkMenuTime.item[83],
                                   blynkMenuTime.item[84], blynkMenuTime.item[85], blynkMenuTime.item[86], blynkMenuTime.item[87],
                                   blynkMenuTime.item[88], blynkMenuTime.item[89], blynkMenuTime.item[90], blynkMenuTime.item[91],
                                   blynkMenuTime.item[92], blynkMenuTime.item[93], blynkMenuTime.item[94], blynkMenuTime.item[95]);
  Blynk.setProperty(V15, "labels", blynkMenuTime.item[0], blynkMenuTime.item[1], blynkMenuTime.item[2], blynkMenuTime.item[3],
                                   blynkMenuTime.item[4], blynkMenuTime.item[5], blynkMenuTime.item[6], blynkMenuTime.item[7],
                                   blynkMenuTime.item[8], blynkMenuTime.item[9], blynkMenuTime.item[10], blynkMenuTime.item[11],
                                   blynkMenuTime.item[12], blynkMenuTime.item[13], blynkMenuTime.item[14], blynkMenuTime.item[15],
                                   blynkMenuTime.item[16], blynkMenuTime.item[17], blynkMenuTime.item[18], blynkMenuTime.item[19],
                                   blynkMenuTime.item[20], blynkMenuTime.item[21], blynkMenuTime.item[22], blynkMenuTime.item[23], 
                                   blynkMenuTime.item[24], blynkMenuTime.item[25], blynkMenuTime.item[26], blynkMenuTime.item[27],
                                   blynkMenuTime.item[28], blynkMenuTime.item[29], blynkMenuTime.item[30], blynkMenuTime.item[31],
                                   blynkMenuTime.item[32], blynkMenuTime.item[33], blynkMenuTime.item[34], blynkMenuTime.item[35],
                                   blynkMenuTime.item[36], blynkMenuTime.item[37], blynkMenuTime.item[38], blynkMenuTime.item[39],
                                   blynkMenuTime.item[40], blynkMenuTime.item[41], blynkMenuTime.item[42], blynkMenuTime.item[43],
                                   blynkMenuTime.item[44], blynkMenuTime.item[45], blynkMenuTime.item[46], blynkMenuTime.item[47],
                                   blynkMenuTime.item[48], blynkMenuTime.item[49], blynkMenuTime.item[50], blynkMenuTime.item[51],
                                   blynkMenuTime.item[52], blynkMenuTime.item[53], blynkMenuTime.item[54], blynkMenuTime.item[55],
                                   blynkMenuTime.item[56], blynkMenuTime.item[57], blynkMenuTime.item[58], blynkMenuTime.item[59],
                                   blynkMenuTime.item[60], blynkMenuTime.item[61], blynkMenuTime.item[62], blynkMenuTime.item[63],
                                   blynkMenuTime.item[64], blynkMenuTime.item[65], blynkMenuTime.item[66], blynkMenuTime.item[67],
                                   blynkMenuTime.item[68], blynkMenuTime.item[69], blynkMenuTime.item[70], blynkMenuTime.item[71],
                                   blynkMenuTime.item[72], blynkMenuTime.item[73], blynkMenuTime.item[74], blynkMenuTime.item[75],
                                   blynkMenuTime.item[76], blynkMenuTime.item[77], blynkMenuTime.item[78], blynkMenuTime.item[79],
                                   blynkMenuTime.item[80], blynkMenuTime.item[81], blynkMenuTime.item[82], blynkMenuTime.item[83],
                                   blynkMenuTime.item[84], blynkMenuTime.item[85], blynkMenuTime.item[86], blynkMenuTime.item[87],
                                   blynkMenuTime.item[88], blynkMenuTime.item[89], blynkMenuTime.item[90], blynkMenuTime.item[91],
                                   blynkMenuTime.item[92], blynkMenuTime.item[93], blynkMenuTime.item[94], blynkMenuTime.item[95]);
}

 
void cbMasterSchedule() {
  if (Appl1Sched.timeOn == ulMinutesSinceMidnight) {
    sendCommand(pipeNumJadeRelay, RELAY1_HIGH);
  }  

  if (Appl1Sched.timeOff == ulMinutesSinceMidnight) {
    sendCommand(pipeNumJadeRelay, RELAY1_LOW);
  }  
  
  if (Appl2Sched.timeOn == ulMinutesSinceMidnight) {
    sendCommand(pipeNumJadeRelay, RELAY2_HIGH);
  }  

  if (Appl2Sched.timeOff == ulMinutesSinceMidnight) {
    sendCommand(pipeNumJadeRelay, RELAY2_LOW);
  }  

}



void BlynkLoop() {
  if (wifiMulti.run() == WL_CONNECTED) { 
    ArduinoOTA.handle();
    if (Blynk.connected()) {
    } else {
      Blynk.connect();
    }
    Blynk.run();
    blynkBigElecFan.singleShot();
    blynkSmallElecFan.singleShot();
    blynkApp3.singleShot();
    blynkApp4.singleShot();

    
  }      
}
