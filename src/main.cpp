// #include <Arduino.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>

// // Try 0x27 first. If display not working, change to 0x3F
// LiquidCrystal_I2C lcd(0x27, 16, 2);

// #define MQ135_PIN 34
// #define GREEN_LED 18
// #define RED_LED 23

// void setup() {

//   Serial.begin(115200);

//   // Start I2C (Important for ESP32)
//   Wire.begin(21, 22);

//   pinMode(GREEN_LED, OUTPUT);
//   pinMode(RED_LED, OUTPUT);

//   digitalWrite(GREEN_LED, LOW);
//   digitalWrite(RED_LED, LOW);

//   lcd.init();
//   lcd.backlight();
//   lcd.clear();

//   // Startup message
//   lcd.setCursor(0, 0);
//   lcd.print("Vehicle Emission");
//   lcd.setCursor(0, 1);
//   lcd.print("Warming Sensor");
//   delay(3000);
//   lcd.clear();
// }

// void loop() {

//   int gasValue = analogRead(MQ135_PIN);
//   Serial.println(gasValue);

//   lcd.setCursor(0, 0);

//   if (gasValue < 1500) {

//     digitalWrite(GREEN_LED, HIGH);
//     digitalWrite(RED_LED, LOW);

//     lcd.print("NOx: SAFE     ");
//   }

//   else if (gasValue < 2500) {

//     digitalWrite(GREEN_LED, LOW);

//     // Red LED blinking in warning
//     digitalWrite(RED_LED, HIGH);
//     delay(200);
//     digitalWrite(RED_LED, LOW);

//     lcd.print("NOx: WARNING  ");
//   }

//   else {

//     digitalWrite(GREEN_LED, LOW);
//     digitalWrite(RED_LED, HIGH);

//     lcd.print("NOx: DANGER   ");
//   }

//   lcd.setCursor(0, 1);
//   lcd.print("Value: ");
//   lcd.print(gasValue);
//   lcd.print("   ");

//   delay(800);
// }


#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pins
#define MQ135_PIN 34
#define GREEN_LED 18
#define RED_LED 23

// WiFi Credentials
const char* ssid = "MITWPU-EXAM";
const char* password = "WPU@mit#eXaM1002";

// ThingSpeak Settings
String apiKey = "H0U522DVFIPMJ192";
const char* server = "http://api.thingspeak.com/update";

void setup() {

  Serial.begin(115200);
  Wire.begin(21, 22);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Connecting WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi Connected!");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WiFi Connected");
  delay(2000);
  lcd.clear();
}

void loop() {

  int gasValue = analogRead(MQ135_PIN);

  int greenStatus = 0;
  int redStatus = 0;
  int systemState = 0;   // 0=SAFE, 1=WARNING, 2=DANGER

  lcd.setCursor(0, 0);

  if (gasValue < 1500) {

    greenStatus = 1;
    redStatus = 0;
    systemState = 0;

    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);

    lcd.print("NOx: SAFE     ");
  }

  else if (gasValue < 2500) {

    greenStatus = 0;
    redStatus = 1;
    systemState = 1;

    digitalWrite(GREEN_LED, LOW);

    digitalWrite(RED_LED, HIGH);
    delay(200);
    digitalWrite(RED_LED, LOW);

    lcd.print("NOx: WARNING  ");
  }

  else {

    greenStatus = 0;
    redStatus = 1;
    systemState = 2;

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    lcd.print("NOx: DANGER   ");
  }

  lcd.setCursor(0, 1);
  lcd.print("Value: ");
  lcd.print(gasValue);
  lcd.print("   ");

  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  // Upload to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    String url = server;
    url += "?api_key=" + apiKey;
    url += "&field1=" + String(gasValue);
    url += "&field2=" + String(systemState);
    url += "&field3=" + String(greenStatus);
    url += "&field4=" + String(redStatus);

    http.begin(url);
    int httpResponseCode = http.GET();

    Serial.print("ThingSpeak Response: ");
    Serial.println(httpResponseCode);

    http.end();
  }

  delay(15000);   // ThingSpeak minimum interval
}
