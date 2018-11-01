#define BTmaster Serial1

const int focoIn = 7;
const int focoOut = 8;

const int moveDer = 11;
const int moveIzq = 9;
const int parkCup = 10;

const int dimmer = 4;

const int PowSwitch1 = 40;
const int PowSwitch2 = 42;
const int PowSwitch3 = 44;
const int PowSwitch4 = 46;

char c;
int intensity = 255;

int pulso = 0;

void setup() {
  // Setup interfaces
  pinMode(moveDer, OUTPUT);
  pinMode(moveIzq, OUTPUT);
  pinMode(parkCup, OUTPUT);
  
  pinMode(focoIn, OUTPUT);
  pinMode(focoOut, OUTPUT);
  
  pinMode(dimmer, OUTPUT);

  pinMode(PowSwitch1, OUTPUT);
  pinMode(PowSwitch2, OUTPUT);
  pinMode(PowSwitch3, OUTPUT);
  pinMode(PowSwitch4, OUTPUT);

  digitalWrite(PowSwitch1, HIGH);
  digitalWrite(PowSwitch2, HIGH);
  digitalWrite(PowSwitch3, HIGH);
  digitalWrite(PowSwitch4, HIGH);

  analogWrite(dimmer, 255);

  attachInterrupt(0, refPosition, RISING);
  attachInterrupt(1, encoder, RISING);
  
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
        
      case 'r':
        digitalWrite(PowSwitch1, LOW);
        break;
      case 'f':
        digitalWrite(PowSwitch1, HIGH);
        break;
      case 't':
        digitalWrite(PowSwitch2, LOW);
        break;
      case 'g':
        digitalWrite(PowSwitch2, HIGH);
        break;
      case 'y':
        digitalWrite(PowSwitch3, LOW);
        break;
      case 'h':
        digitalWrite(PowSwitch3, HIGH);
        break;
      case 'u':
        digitalWrite(PowSwitch4, LOW);
        break;
      case 'j':
        digitalWrite(PowSwitch4, HIGH);
        break;  
    }
    
  }

  if(BTmaster.available())
  {
    Serial.write(BTmaster.read());
  }
}

void refPosition()
{
  Serial.println("Posicion de referencia.");
  digitalWrite(moveDer, LOW);
  digitalWrite(moveIzq, LOW);
  pulso = 0;
  Serial.print("Posicion cupula: ");
  Serial.println(pulso);
  
}

void encoder()
{
  pulso += 1;
  Serial.print("Posicion cupula: ");
  Serial.println(pulso);
}

