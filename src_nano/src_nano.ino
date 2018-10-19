#include <SoftwareSerial.h>

SoftwareSerial BTslave(3, 2); // RX, TX
const int stopPin = 7;   // Pin to open shutter.
const int openPin = 8;   // Pin to stop shutter movement.
const int closePin = 9;  // Pin to close shutter. 

const int stopEnd = 4;   // Pin to control open end of stroke.
const int closeEnd = 5;   // Pin to control close end of stroke.
const int openEnd = 6;   // Pin to control close end of stroke.

bool prevClose;
bool prevOpen;

char moveDir = 's';      // Set default state of move direction.

int BateryPin = A0;
String endSwStatus;
String endSwPrevious = "no value";


void setup() 
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // Set pins to input signals.
  pinMode(openEnd, INPUT);
  pinMode(closeEnd, INPUT);

  // Set pins to output signals.
  pinMode(openPin, OUTPUT);
  pinMode(closePin, OUTPUT);
  pinMode(stopPin, OUTPUT);

  // wait for serial port to connect. Needed for native USB port only.
  while (!Serial) {}

  // set the data rate for the SoftwareSerial port.
  BTslave.begin(9600);
}

void loop() 
{
  if (BTslave.available()) 
  {
    moveDir = BTslave.read();
    switch(moveDir)
    {
      // Case open
      case 'a':
        digitalWrite(closePin, LOW);
        digitalWrite(stopPin, LOW);
        digitalWrite(openPin, HIGH);
        delay(100);
        digitalWrite(openPin, LOW);
        delay(500);
        break;
      // Case close
      case 'd':
        digitalWrite(openPin, LOW);
        digitalWrite(stopPin, LOW);
        digitalWrite(closePin, HIGH);
        delay(100);
        digitalWrite(closePin, LOW);
        delay(500);
        break;
      // Case stop
      case 's':
        digitalWrite(openPin, LOW);
        digitalWrite(closePin, LOW);
        digitalWrite(stopPin, HIGH);
        delay(100);
        digitalWrite(stopPin, LOW);
        delay(500);
        break;
      // Case batery request
      case 'b':
        BTslave.println(bateryLevel());
        break;
      case 'i':
        BTslave.println(readStatus());
        break;
    }
  }

  endSwStatus = readStatus();
  if (endSwStatus != endSwPrevious){
    BTslave.println(endSwStatus);
    endSwPrevious = endSwStatus;
  }
  delay(1000);
}


// Reads the value from the batery and compute the value in volts.
String bateryLevel()
{
  int batValue;
  float volts;
  float coef = 62.83;
  String sVolts;

  batValue = analogRead(BateryPin);
  volts = batValue / coef;
  sVolts = (String) volts;
  return sVolts;
}

// Reads the end switchs status and return it
String readStatus(){
  if (!digitalRead(openEnd)){
    return "Full Open";
  }
  else if (!digitalRead(closeEnd)){
    return "Close";
  }
  else{
    return "Open";
  }
}

