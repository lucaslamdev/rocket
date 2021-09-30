//Módulos Neo-7M(GPS) - bmp180(Barometro, Temperatura) - MPU6050 (Giroscópio, Temperatura)

#include <SoftwareSerial.h> //Biblioteca para simular entrada RX, TX em portas digitais para comunicação com módulo GPS
#include <Wire.h> //Biblioteca para funcionamento do I2c para comunicação com os módulos de pressão e giroscópio
#include <TinyGPS++.h> //Biblioteca para tradução facil dos dados do GPS
#include <MPU6050.h> //Biblioteca para facilitamento do uso do Giroscópico
#include <Adafruit_BMP085.h> //Biblioteca para facilitamento do uso do Barometro

static const int D5RXPin = 14, D6TXPin = 12;
static const uint32_t GPSBaud = 6900;

//TinyGPS++ objeto
TinyGPSPlus gps;

// Objeto para conexão serial com GPS
SoftwareSerial serialGPS(D5RXPin, D6TXPin);
  
void setup()
{
  Serial.begin(115200); //Inicializar Serial do Arduino
  serialGPS.begin(GPSBaud); //Inicializar Serial do GPS
}
  
void loop()
{
  
}
