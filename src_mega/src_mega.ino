#include <TimerOne.h>
#define BTmaster  Serial1
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
    Serial1.print(c);
    //wait some time
    delay(100);
  }

  if(Serial1.available())
  {
    Serial.write(Serial1.read());
  }
}

