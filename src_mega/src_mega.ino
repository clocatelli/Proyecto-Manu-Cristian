String c;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial.setTimeout(20);
    sendCommand("AT");
//  sendCommand("AT+ROLE0");
//  sendCommand("AT+UUID0xFFE0");
//  sendCommand("AT+CHAR0xFFE1");
//  sendCommand("AT+NAMEbluino");
}

void sendCommand(String command){
  Serial.print("Command send :");
  Serial.print(command);
  Serial1.print(command);
  //wait some time
  delay(100);
  
  /*while (Serial1.available()) {
    Serial.write(Serial1.read());
  }
  Serial.println("Reply end");*/
}

void loop() {

  if(Serial.available())
  {
    c = Serial.readString();
    sendCommand(c);
  }

  if(Serial1.available())
  {
    Serial.write(Serial1.read());
  }

  

}
