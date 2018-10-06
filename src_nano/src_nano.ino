#include <SoftwareSerial.h>

SoftwareSerial BTslave(3, 2); // RX, TX
const int stopPin = 7;   // Pin to open shutter.
const int openPin = 8;   // Pin to stop shutter movement.
const int closePin = 9;  // Pin to close shutter. 

const int openEnd = 4;   // Pin to control open end of stroke.
const int closeEnd = 5;   // Pin to control close end of stroke.

bool prevClose;
bool prevOpen;

char moveDir = 's';      // Set default state of move direction.

int BateryPin = A0;

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

  // init end of stroke pins.
  prevOpen == !(digitalRead(openEnd) == HIGH);
  prevClose == !(digitalRead(closeEnd) == HIGH);
  
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
        break;
      // Case close
      case 'c':
        digitalWrite(openPin, LOW);
        digitalWrite(stopPin, LOW);
        digitalWrite(closePin, HIGH);
        delay(100);
        digitalWrite(closePin, LOW);
        break;
      // Case stop
      case 's':
        digitalWrite(openPin, LOW);
        digitalWrite(closePin, LOW);
        digitalWrite(stopPin, HIGH);
        delay(100);
        digitalWrite(stopPin, LOW);
        break;
      // Case batery request
      case 'b':
        BTslave.println(bateryLevel());
        break;
    }
  }

  // VER LOS FINES DE CARRERA --->> NO ANDA

  // Reads the end of stroke pins, which tells us the state.
  if((digitalRead(openEnd) == HIGH) && (prevOpen == false))
  {
    Serial.println("Full open");
    //BTslave.println("Full open");
    prevOpen = true;
  }

  if((digitalRead(openEnd) == LOW) && (prevOpen == true))
  {
    Serial.println("Open");
    //BTslave.println("Full open");
    prevOpen = false;
  }

  if((digitalRead(closeEnd) == HIGH) && (prevClose == false))
  {
    Serial.println("Full close");
    //BTslave.println("Full close");
    prevClose = true;
  }

  if((digitalRead(closeEnd) == LOW) && (prevClose == true))
  {
    Serial.println("Open");
    //BTslave.println("Full close");
    prevClose = false;
  }


}

