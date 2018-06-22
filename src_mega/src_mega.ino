#include <TimerOne.h>
#define BTmaster  Serial1
#define BTslave   Serial2
String c;


//void timerInterruption ();

void setup() {
  // put your setup code here, to run once:
  BTmaster.begin(9600);
  BTslave.begin(9600);
  Serial.begin(9600);
  Serial.setTimeout(100);

//  Timer1.initialize();
//  Timer1.start();
//  Timer1.attachInterrupt(timerInterruption);

  delay(1000);
  BTmaster.println("AT");
  //BTmaster.println("AT+INQ");
  
  Serial1.available();

//  delay(3000);
//  Serial1.print("AT+CONN1");
//  Serial1.available();

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

