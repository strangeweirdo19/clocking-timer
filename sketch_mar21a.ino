#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800);

const int relay1Pin = 13;
const int relay2Pin = 14;

void setup() {
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  Wire.begin();
  rtc.begin();
  WiFi.begin("Kirti's iPhone", "Aerem@2019");
  // Sync time with NTP server
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
  }
  if (WiFi.status() == WL_CONNECTED) {
    timeClient.begin();
    while (!timeClient.update()) {
      timeClient.forceUpdate();
    }
    rtc.adjust(DateTime(timeClient.getEpochTime()));
  }
  digitalWrite(2, HIGH);
}

void loop() {
  DateTime now = rtc.now();
  int hour = now.hour();
  Serial.println(hour);
  if (hour = 6 && hour < 18) {
    digitalWrite(relay1Pin, HIGH);  // turn on relay1 from 12 pm until 8 pm
  } else {
    digitalWrite(relay1Pin, LOW);
  }

  if (hour >= 6 && hour < 14) {
    digitalWrite(relay2Pin, LOW);  // turn on relay2 from 12 pm until 12 am
  } else {
    digitalWrite(relay2Pin, HIGH);
  }

  delay(1000);  // wait for 1 second before checking the time again
}
