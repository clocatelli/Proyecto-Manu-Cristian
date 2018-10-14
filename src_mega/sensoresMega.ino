#include <DHT.h>
#include <SFE_BMP180.h>
#include <Wire.h>

#define DHTTYPE DHT22             // DHT 22  (AM2302), AM2321
#define DHTPIN 5                  // what digital pin we're connected to

const int rainSensor = A0;
double rain;
double temperature;
double humidity;
double pressure;

DHT dht(DHTPIN, DHTTYPE);
SFE_BMP180 bmp180;
 
void setup(){
  pinMode(rainSensor, INPUT);     //definir pin como entrada
  Serial.begin(9600);             //iniciar puerto serie  
  dht.begin();
  bmp180.begin();
}
 
void loop(){
  rain = readRain();
  Serial.println(rain);

  temperature = readTemp();
  Serial.println(temperature);

  humidity = readHumidity();
  Serial.println(humidity);

  pressure = readPressure();
  Serial.println(pressure);

  Serial.println("");
  delay(2000);
}


double readRain(){
  int p = analogRead(rainSensor);
  return(p);  
}

double readHumidity(){
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  else{
    return(h);
  }
}

double readTemp(){
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  else{
    return(t);
  }
}

double readPressure(){
  char status;
  double bmpT;
  double bmpP;
 
  status = bmp180.startTemperature(); //Inicio de lectura de temperatura
  if (status != 0)
  {   
    delay(status); //Pausa para que finalice la lectura
    status = bmp180.getTemperature(bmpT); //Obtener la temperatura
    if (status != 0)
    {
      status = bmp180.startPressure(3); //Inicio lectura de presión
      if (status != 0)
      {        
        delay(status); //Pausa para que finalice la lectura        
        status = bmp180.getPressure(bmpP,bmpT); //Obtenemos la presión
        if (status != 0)
        {    
          return(bmpP);          
        }      
      }      
    }   
  } 
}

