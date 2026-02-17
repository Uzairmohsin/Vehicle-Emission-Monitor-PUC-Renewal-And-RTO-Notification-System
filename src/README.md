publish the gas value to ThingSpeak Cloud using WiFi.



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
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ThingSpeak
String apiKey = "YOUR_WRITE_API_KEY";
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

  // Connect WiFi
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
  Serial.println(gasValue);

  lcd.setCursor(0, 0);

  if (gasValue < 1500) {

    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    lcd.print("NOx: SAFE     ");
  }

  else if (gasValue < 2500) {

    digitalWrite(GREEN_LED, LOW);

    digitalWrite(RED_LED, HIGH);
    delay(200);
    digitalWrite(RED_LED, LOW);

    lcd.print("NOx: WARNING  ");
  }

  else {

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    lcd.print("NOx: DANGER   ");
  }

  lcd.setCursor(0, 1);
  lcd.print("Value: ");
  lcd.print(gasValue);
  lcd.print("   ");

  // Send to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    String url = server;
    url += "?api_key=" + apiKey;
    url += "&field1=" + String(gasValue);

    http.begin(url);
    int httpResponseCode = http.GET();

    Serial.print("ThingSpeak Response: ");
    Serial.println(httpResponseCode);

    http.end();
  }

  delay(15000); // ThingSpeak requires minimum 15 seconds
}
