//Módulos Neo-7M(GPS) - bmp180(Barometro, Temperatura) - MPU6050 (Giroscópio, Temperatura) - SD card
//neo suporta - Serial (obter valores - http://arduiniana.org/libraries/tinygpsplus/)
//bmp suporta - SPI ou I2C
//mpu suporta - I2C - https://randomnerdtutorials.com/esp8266-nodemcu-mpu-6050-accelerometer-gyroscope-arduino/
//sd card suporta -
#include <SoftwareSerial.h>    //Biblioteca para simular entrada RX, TX em portas digitais para comunicação com módulo GPS
#include <Wire.h>              //Biblioteca para funcionamento do I2c para comunicação com os módulos de pressão e giroscópio
#include <TinyGPS++.h>         //Biblioteca para tradução facil dos dados do GPS
#include <Adafruit_MPU6050.h>  //Biblioteca para facilitamento do uso do giroscópio
#include <Adafruit_Sensor.h>   //Biblioteca para facilitamento do uso do giroscópio
#include <Adafruit_BMP085.h>   //Biblioteca para facilitamento do uso do Barometro
#include <ESP8266WiFi.h> //Biblioteca para funcionar WIFI
#include <ESP8266HTTPClient.h> //Biblioteca para uso do HTTP - GET, POST...

//Constantes
//Pinos
static const int D5_RX_Pin = 14, D6_TX_Pin = 12; //SERIAL GPS
static const int D1_SDA_Pin = 5, D2_SCL_Pin = 4; //I2C BMP e MPU

//Config GPS
static const uint32_t GPSBaud = 6900;

//Config Wifi
#define ssid "SSID"
#define senha "SENHA"

//API Config
const String API_KEY = "SENHA";
#define API_LINK "http://lucasmello.ga/API/insert/"

//Delay Envio (10 segundos)
static const unsigned int tempoDeDelay = 10000;

//Temporizador
unsigned long ultimoTempo = 0;

//TinyGPS++ objeto
TinyGPSPlus gps;

// Objeto para conexão serial com GPS
SoftwareSerial serialGPS(D5_RX_Pin, D6_TX_Pin);

// Objeto para iniciar BMP
Adafruit_BMP085 bmp;

// Objeto para iniciar MPU
Adafruit_MPU6050 mpu;

void setup()
{
  Serial.begin(115200);     //Inicializar Serial do Arduino
  serialGPS.begin(GPSBaud); //Inicializar Serial do GPS

  //inicializar GPS
  while (serialGPS.available() > 0)
  {
    int c = serialGPS.read();
    gps.encode(c);
  }

  //inicializar wifi
  WiFi.begin(ssid, senha);
  Serial.println("Conectando WIFI");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado no WIFI - IP Local: ");
  Serial.println(WiFi.localIP());

  //inicializar barometro
  if (!bmp.begin())
  {
    Serial.println("Sensor nao encontrado !!");
    while (1)
    {
      delay(10);
    }
  }

  //inicializar giroscopio
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
    {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange())
  {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange())
  {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth())
  {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
}

void loop()
{
  //Valor sensores nas variaveis

  //BMP
  float temperatura_bmp = bmp.readTemperature();
  unsigned int pressao = bmp.readPressure();
  float altitude_bmp = bmp.readAltitude();
  unsigned int pressao_nivel_mar = bmp.readSealevelPressure();
  float altitude_real = bmp.readAltitude(pressao_nivel_mar * 100);

  //MPU
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  float acX = a.acceleration.x;
  float acY = a.acceleration.y;
  float acZ = a.acceleration.z;
  float gyX = g.gyro.x;
  float gyY = g.gyro.y;
  float gyZ = g.gyro.z;
  float temperatura_mpu = temp.temperature;
  float velocidade_mpu = sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2));

  //GPS
  int qtd_satelites = gps.satellites.value();
  float latitude = gps.location.lat();
  float longitude = gps.location.lng();
  float altitude_gps = gps.altitude.meters();
  //float velocidade_gps = gps.speed.kmph(); //kilometros por hora
  float velocidade_gps = gps.speed.mps(); //metros por segundo
  unsigned int data_gps = gps.date.value();

  // Envia HTTP POST request a cada 10 segundos
  if ((millis() - ultimoTempo) > tempoDeDelay)
  {

    // Verifica se Wifi está conectado
    if (WiFi.status() == WL_CONNECTED)
    {
      WiFiClient client;
      HTTPClient http;

      //Inicializar conexão com o servidor
      http.begin(client, API_LINK);

      // Especificar content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      // Data to send with HTTP POST
      String httpRequestData = "api_key=" + API_KEY + "&temperatura_bmp=" + temperatura_bmp + "&pressao=" + pressao + "&altitude_bmp=" + altitude_bmp + "&pressao_nivel_mar=" + pressao_nivel_mar + "&altitude_real=" + altitude_real + "&acX=" + acX + "&acY=" + acY + "&acZ=" + acZ + "&gyX=" + gyX + "&gyY=" + gyY + "&gyZ=" + gyZ + "&temperatura_mpu=" + temperatura_mpu + "&velocidade_mpu=" + velocidade_mpu + "&qtd_satelites" + qtd_satelites + "&latitude=" + latitude + "&longitude=" + longitude + "&altitude_gps=" + altitude_gps + "&velocidade_gps=" + velocidade_gps + "&data_gps=" + data_gps;

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
