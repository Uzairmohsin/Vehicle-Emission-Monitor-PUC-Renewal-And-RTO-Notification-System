#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <HardwareSerial.h>

// ================= LCD =================
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ================= GSM =================
HardwareSerial gsm(2);
String phoneNumber = "+917057741353";

// ================= PINS =================
#define MQ135_PIN 34
#define GREEN_LED 18
#define RED_LED 23

// ================= WiFi =================
const char* ssid = "MITWPU-EXAM";
const char* password = "MIT#wPu@EXam2603";

// ================= ThingSpeak =================
String apiKey = "EL02A2GTGJEAT4OW";
const char* server = "http://api.thingspeak.com/update";

// ================= STATE TRACKING =================
int lastState = -1;

// ================= SMS FUNCTION =================
void sendSMS(String message) {
  Serial.println("Sending SMS...");

  gsm.println("AT+CMGF=1");
  delay(1000);

  gsm.print("AT+CMGS=\"");
  gsm.print(phoneNumber);
  gsm.println("\"");

  delay(1000);

  gsm.print(message);
  delay(500);

  gsm.write(26); // CTRL+Z
  delay(5000);

  Serial.println("SMS Sent");
}

// ================= SETUP =================
void setup() {

  Serial.begin(115200);

  // I2C
  Wire.begin(21, 22);

  // GSM INIT
  gsm.begin(9600, SERIAL_8N1, 16, 17);
  delay(3000);

  gsm.println("AT");
  delay(1000);

  gsm.println("AT+CMGF=1");
  delay(1000);

  // LED SETUP
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  // LCD INIT
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Connecting WiFi");

  // WIFI CONNECT
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WiFi Connected");
  delay(2000);
  lcd.clear();
}

// ================= LOOP =================
void loop() {

  int gasValue = analogRead(MQ135_PIN);

  int greenStatus = 0;
  int redStatus = 0;
  int systemState = 0;   // 0=SAFE, 1=WARNING, 2=DANGER

  lcd.setCursor(0, 0);

  // ================= SAFE =================
  if (gasValue < 1500) {

    greenStatus = 1;
    redStatus = 0;
    systemState = 0;

    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);

    lcd.print("NOx: SAFE     ");

    lastState = 0;
  }

  // ================= WARNING =================
  else if (gasValue < 2500) {

    greenStatus = 0;
    redStatus = 1;
    systemState = 1;

    digitalWrite(GREEN_LED, LOW);

    digitalWrite(RED_LED, HIGH);
    delay(200);
    digitalWrite(RED_LED, LOW);

    lcd.print("NOx: WARNING  ");

    if (lastState != 1) {
      sendSMS("WARNING: Moderate vehicle emission detected. Please check at service station.");
      lastState = 1;
    }
  }

  // ================= DANGER =================
  else {

    greenStatus = 0;
    redStatus = 1;
    systemState = 2;

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    lcd.print("NOx: DANGER   ");

    if (lastState != 2) {
      sendSMS("ALERT! HIGH vehicle emission detected. Immediate action required!");
      lastState = 2;
    }
  }

  // ================= LCD DISPLAY =================
  lcd.setCursor(0, 1);
  lcd.print("Value: ");
  lcd.print(gasValue);
  lcd.print("   ");

  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  // ================= THINGSPEAK =================
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

  // ================= DELAY =================
  delay(15000);   // ThingSpeak limit
}