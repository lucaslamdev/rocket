//Módulos Neo-7M(GPS) - bmp180(Barometro, Temperatura) - MPU6050 (Giroscópio, Temperatura) - SD card
//neo suporta - Serial (obter valores - http://arduiniana.org/libraries/tinygpsplus/)
//bmp suporta - SPI ou I2C
//mpu suporta -
//sd card suporta -
#include <SoftwareSerial.h>  //Biblioteca para simular entrada RX, TX em portas digitais para comunicação com módulo GPS
#include <Wire.h>            //Biblioteca para funcionamento do I2c para comunicação com os módulos de pressão e giroscópio
#include <TinyGPS++.h>       //Biblioteca para tradução facil dos dados do GPS
#include <MPU6050.h>         //Biblioteca para facilitamento do uso do Giroscópico
#include <Adafruit_BMP085.h> //Biblioteca para facilitamento do uso do Barometro
#include <WiFi.h>            //Biblioteca para uso do WiFi
#include <HTTPClient.h>      //Biblioteca para uso do HTTP - GET, POST...

//Constantes
static const int D5_RX_Pin = 14, D6_TX_Pin = 12; //SERIAL GPS
static const int D1_SDA_Pin = 5, D2_SCL_Pin = 4; //I2C BMP e MPU
static const uint32_t GPSBaud = 6900;
static const char *SSID = "SSID";
static const char *SENHA = "SENHA";
static const char *API_KEY = "SENHA";
static const char *API_LINK = "LINK";
static const unsigned int tempoDeDelay = 10000;
//temporizador
unsigned long ultimoTempo = 0;

//TinyGPS++ objeto
TinyGPSPlus gps;

// Objeto para conexão serial com GPS
SoftwareSerial serialGPS(D5_RX_Pin, D6_TX_Pin);

void setup()
{
  Serial.begin(115200);     //Inicializar Serial do Arduino
  serialGPS.begin(GPSBaud); //Inicializar Serial do GPS

  WiFi.begin(ssid, password);
  Serial.println("Conectando WIFI");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado no WIFI - IP Local: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  // Envia HTTP POST request a cada 10 segundos
  if ((millis() - ultimoTempo) > tempoDeDelay)
  {

    // Verifica se Wifi está conectado
    if (WiFi.status() == WL_CONNECTED)
    {
      WiFiClient client;
      HTTPClient http;

      //Inicializar conexão com o servidor
      http.begin(API_LINK);

      // Especificar content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      // Data to send with HTTP POST
      String httpRequestData = "api_key=" + API_KEY + "&temperatura_bmp=" + temperatura + "&pressao=" + pressao + "&altitude_bmp=" + altitude_bmp + "&pressao_nivel_mar=" + pressao_nivel_mar + "&altitude_real=" + altitude_real + "&acX=" + acX + "&acY=" + acY + "&acZ=" + acZ + "&gyX=" + gyX + "&gyY=" + gyY + "&gyZ=" + gyZ + "&temperatura_mpu=" + temperatura_mpu + "&velocidade_mpu=" + velocidade_mpu + "&qtd_satelites" + qtd_satelites + "&latitude=" + latitude + "&longitude=" + longitude + "&altitude_gps=" + altitude_gps + "&velocidade_gps=" + velocidade_gps + "&data_gps=" + data_gps;

      // envia HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      //imprime a resposta HTTP
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      //finaliza a conexão http
      http.end();
    }
    else
    {
      Serial.println("WIFI Desconectado!");
    }
    ultimoTempo = millis();
  }
}
