#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "NoiseMonitor"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>

char auth[] = "YourAuthToken";
char ssid[] = "YourWiFiName";
char pass[] = "YourWiFiPassword";

LiquidCrystal_I2C lcd(0x27, 16, 2);

int soundPin = 34;
int buzzer = 23;

void setup() {
  Serial.begin(115200);

  pinMode(buzzer, OUTPUT);

  lcd.init();
  lcd.backlight();

  Blynk.begin(auth, ssid, pass);

  lcd.setCursor(0,0);
  lcd.print("Noise Monitor");
}

void loop() {
  Blynk.run();

  int soundValue = analogRead(soundPin);

  lcd.clear();

  if(soundValue < 1000) {
    lcd.print("Noise Low");
    digitalWrite(buzzer, LOW);
  }
  else if(soundValue < 2500) {
    lcd.print("Noise Medium");
    digitalWrite(buzzer, LOW);
  }
  else {
    lcd.print("Noise HIGH!");

    digitalWrite(buzzer, HIGH);

    Blynk.logEvent("noise_alert", "High Noise Detected!");
  }

  delay(1000);
}