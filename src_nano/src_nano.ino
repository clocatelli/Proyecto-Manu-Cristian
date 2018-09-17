#include <SoftwareSerial.h>

SoftwareSerial BTslave(3, 2); // RX, TX
const int openPin = 7;   // Pin to open shutter.
const int closePin = 8;  // Pin to close shutter.
const int stopPin = 9;   // Pin to stop shutter movement.

const int openEnd = 4;   // Pin to open shutter.
const int closeEnd = 5;  // Pin to close shutter.
const int stopEnd = 6;   // Pin to stop shutter movement.

char moveDir = 's';      // Set default state of move direction.

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
    Serial.write(BTslave.read());
    moveDir = BTslave.read();
    switch(moveDir)
    {
      case 'o':
        digitalWrite(closePin, LOW);
        digitalWrite(stopPin, LOW);
        digitalWrite(openPin, HIGH);
        Serial.println("o");
        break;
      case 'c':
        digitalWrite(openPin, LOW);
        digitalWrite(stopPin, LOW);
        digitalWrite(closePin, HIGH);
        Serial.println("c");
        break;
      case 's':
        digitalWrite(openPin, LOW);
        digitalWrite(closePin, LOW);
        digitalWrite(stopPin, HIGH);
        Serial.println("s");
        break;
      default:
        digitalWrite(openPin, LOW);
        digitalWrite(closePin, LOW);
        digitalWrite(stopPin, HIGH);
        break;
    }
  }
}

