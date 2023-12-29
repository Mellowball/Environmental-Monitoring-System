#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_BMP280.h>    //Adafruit_BME280_Library by Adafruit
#include <SoftwareSerial.h>

const char* ssid = "";        // 와이파이 이름
const char* password = "";  // 와이파이 비밀번호
Adafruit_BMP280 bmp;                    // I2C
SoftwareSerial pmsSerial(D6, D5);       // RX, TX
unsigned char pms[32];
int PM1_0, PM2_5, PM10;

// 데이터베이스,와이파이 설정
#include <FirebaseESP8266.h>    //Firebase ESP8266 Client by Mobizt
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

// 파이어베이스 개인정보
#define DATABASE_URL ""
#define API_KEY ""
#define USER_EMAIL ""
#define USER_PASSWORD ""

// 파이어베이스 데이터 객체 설정
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;

void setup() {
  Serial.begin(115200);   // 시리얼 통신 시작
  pmsSerial.begin(9600);  // PMS 시리얼 통신
  delay(10);

  // 와이파이 연결 시작
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // 와이파이 연결 완료 시까지 대기
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // 와이파이 연결 완료 메시지 출력
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // BMP280 연결
  while (!Serial) delay(100); 
  Serial.println(F("BMP280 test"));
  unsigned status;
  status = bmp.begin();
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                     "try a different address!"));
    Serial.print("SensorID was: 0x");
    Serial.println(bmp.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  // Firebase 설정
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;
  Firebase.reconnectNetwork(true);
  fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);

  // Firebase 시작
  Firebase.begin(&config, &auth);
  Firebase.setDoubleDigits(5);

  Serial.println("Setup completed");
}
void loop() {
  // BMP280 센서값
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100;
  float altitude = bmp.readAltitude(1013.25);

  // PMS7003 센서값 읽기
  if (pmsSerial.available() >= 32) {
    for (int i = 0; i < 32; i++) {
      pms[i] = pmsSerial.read();
    }
    PM1_0 = (pms[10] << 8) | pms[11];
    PM2_5 = (pms[12] << 8) | pms[13];
    PM10 = (pms[14] << 8) | pms[15];
  }

  // 센서값 Firebase에 전송 및 시리얼 출력
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    Serial.printf("Push temperature... %s\n", Firebase.pushFloat(fbdo, F("/temperature"), temperature) ? String(temperature) : fbdo.errorReason().c_str());
    Serial.printf("Push preesure... %s\n", Firebase.pushFloat(fbdo, F("/pressure"), pressure) ? String(pressure) : fbdo.errorReason().c_str());
    Serial.printf("Push altitude... %s\n", Firebase.pushFloat(fbdo, F("/altitude"), altitude) ? String(altitude) : fbdo.errorReason().c_str());
    Serial.printf("Push PM1_0... %s\n", Firebase.pushInt(fbdo, "/PM1_0", PM1_0) ? String(PM1_0) : fbdo.errorReason().c_str());
    Serial.printf("Push PM2_5... %s\n", Firebase.pushInt(fbdo, "/PM2_5", PM2_5) ? String(PM2_5) : fbdo.errorReason().c_str());
    Serial.printf("Push PM10... %s\n", Firebase.pushInt(fbdo, "/PM10", PM10) ? String(PM10) : fbdo.errorReason().c_str());
    Serial.println();
  }
}
