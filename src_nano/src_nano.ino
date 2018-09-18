#include <SoftwareSerial.h>

SoftwareSerial BTslave(3, 2); // RX, TX
const int openPin = 7;   // Pin to open shutter.
const int closePin = 8;  // Pin to close shutter.
const int stopPin = 9;   // Pin to stop shutter movement.

const int openEnd = 4;   // Pin to open shutter.
const int closeEnd = 5;  // Pin to close shutter.
const int stopEnd = 6;   // Pin to stop shutter movement.

char moveDir = 's';      // Set default state of move direction.

int BateryPin = A0;

bool BateryRequest = false;

int bateryLevel()
{
  // read the value from the batery
  //return analogRead(BateryPin);
  return 1024;
}

void setup() 
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // Set pins to input signals.
  pinMode(openEnd, INPUT);
  pinMode(closeEnd, INPUT);
  pinMode(stopEnd, INPUT);

  // Set pins to output signals.
  pinMode(openPin, OUTPUT);
  pinMode(closePin, OUTPUT);
  pinMode(stopPin, OUTPUT);
  
  while (!Serial) 
  {
  // wait for serial port to connect. Needed for native USB port only
  }

  // set the data rate for the SoftwareSerial port
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
      case 'o':
        digitalWrite(closePin, LOW);
        digitalWrite(stopPin, LOW);
        digitalWrite(openPin, HIGH);
        delay(100);
        digitalWrite(openPin, LOW);
        Serial.println("o");
        break;
      // Case close
      case 'c':
        digitalWrite(openPin, LOW);
        digitalWrite(stopPin, LOW);
        digitalWrite(closePin, HIGH);
        delay(100);
        digitalWrite(closePin, LOW);
        Serial.println("c");
        break;
      // Case stop
      case 's':
        digitalWrite(openPin, LOW);
        digitalWrite(closePin, LOW);
        digitalWrite(stopPin, HIGH);
        delay(100);
        digitalWrite(stopPin, LOW);
        Serial.println("s");
        break;
      // Case batery request
      case 'b':
        BTslave.println(bateryLevel());
        Serial.println("b");
        break;
      default:
        digitalWrite(openPin, LOW);
        digitalWrite(closePin, LOW);
        digitalWrite(stopPin, HIGH);
        break;
    }
  }
}

