#include <TimerOne.h>
#define BTmaster Serial1
String c;

void setup() {
  // Setup interfaces
  BTmaster.begin(9600);
  Serial.begin(9600);
  Serial.setTimeout(100);
}

void loop() {

  if(Serial.available())
  {
    c = Serial.readString();
    Serial.print("Command send :");
    Serial.print(c);
    BTmaster.print(c);
    //wait some time
    delay(100);
  }

  if(BTmaster.available())
  {
    Serial.write(BTmaster.read());
  }
}

