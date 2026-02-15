#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Try 0x27 first. If display not working, change to 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define MQ135_PIN 34
#define GREEN_LED 18
#define RED_LED 23

void setup() {

  Serial.begin(115200);

  // Start I2C (Important for ESP32)
  Wire.begin(21, 22);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Startup message
  lcd.setCursor(0, 0);
  lcd.print("Vehicle Emission");
  lcd.setCursor(0, 1);
  lcd.print("Warming Sensor");
  delay(3000);
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

    // Red LED blinking in warning
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

  delay(800);
}