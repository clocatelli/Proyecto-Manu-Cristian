#define BTmaster Serial1

const int focoIn = 7;
const int focoOut = 8;
const int moveDer = 9;
const int moveIzq = 10;
const int parkCup = 11;
const int dimmer = 4;

char c;
int intensity = 255;

void setup() {
  // Setup interfaces
  pinMode(moveDer, OUTPUT);
  pinMode(moveIzq, OUTPUT);
  pinMode(parkCup, OUTPUT);
  pinMode(focoIn, OUTPUT);
  pinMode(focoOut, OUTPUT);
  pinMode(dimmer, OUTPUT);

  analogWrite(dimmer, 255);
  
  BTmaster.begin(9600);
  Serial.begin(9600);
  //Serial.setTimeout(100);
}

void loop() {

  if(Serial.available())
  {
    c = Serial.read();

    switch(c)
    {
      case 'a':
        BTmaster.print(c);
        delay(100);
        break;
      case 's':
        BTmaster.print(c);
        delay(100);
        break;
      case 'd':
        BTmaster.print(c);
        delay(100);
        break;
      case 'i':
        BTmaster.print(c);
        delay(100);
        break;
      case 'b':
        BTmaster.print(c);
        delay(100);
        break;
        
      case 'q':
        digitalWrite(moveIzq, HIGH);
        break;
      case 'e':
        digitalWrite(moveDer, HIGH);
        break;
      case 'w':
        digitalWrite(moveDer, LOW);
        digitalWrite(moveIzq, LOW);
        break;
      case 'p':
        digitalWrite(parkCup, HIGH);
        delay(100);
        digitalWrite(parkCup, LOW);
        break;
        
      case 'z':
        digitalWrite(focoIn, HIGH);
        break;
      case 'c':
        digitalWrite(focoOut, HIGH);
        break;
      case 'x':
        digitalWrite(focoIn, LOW);
        digitalWrite(focoOut, LOW);
        break;

      case '+':
        intensity -= 10;
        if(intensity < 0){
          intensity = 0;
        }
        Serial.println(intensity);
        analogWrite(dimmer, intensity);
        break;
      case '-':
        intensity += 10;
        if(intensity > 255){
          intensity = 255;
        }
        Serial.println(intensity);
        analogWrite(dimmer, intensity);
        break;
      case '*':;
        intensity = 255;
        analogWrite(dimmer, 255);
        break;
    }
    
  }

  if(BTmaster.available())
  {
    Serial.write(BTmaster.read());
  }
}

